#include "uncompress.hpp"
#include "haffumanTree.hpp"
#include<iostream>
#include<fstream>

using namespace std ;



haffuNode<char>* GenHuffTreeByConfigFile(char information[], int &infoIndex, int &ascllIndex) 
{   
	
	if (information == NULL )
		return NULL;
	
	char ch = information[infoIndex++];
	
	if( ch!='0' && ch!='1' )
		return NULL ;
	
	haffuNode<char>* root ;
	
	if (ch =='0') //叶节点
	{
	    root = new haffuLeaf<char>(information[ascllIndex++],0);//这个时候权值没用了，随便设置
	    return root;
	}
	else if(ch == '1') //根节点，需要递归调用
		root = new internalNode<char>( GenHuffTreeByConfigFile(information, infoIndex, ascllIndex),
									   GenHuffTreeByConfigFile(information, infoIndex, ascllIndex) );
	
	return root;                 
   
}

bool uncompress(const char* filename) 
{	

	//读取配置文件	
	ifstream config("fConfig.dat",ios::binary); //对应的文件名字自己设置
	
	if (!config) 
	{
		cout << "Can not find the config file !!!\n" << endl;
		return false;
	}	
	

	//将配置文件中的信息还原得到Huffman树
	
	long total = 0 ;
	int nodeNumber = 0 ;
	
	
	config.read(reinterpret_cast<char*>(&total), sizeof(long));
	config.read(reinterpret_cast<char*>(&nodeNumber),sizeof(int));
	

	//直接将数据读出来,读到information数组,前面是树结构信息，后面是ascll
	
	int space = ((nodeNumber+1)/2)*3-1 ; 
	char information[767] ;  // 767
	
	int i = 0 ;
	char getOneChar ;
	for(int i = 0 ; (! config.eof() ) && i < space ; ++i)
	{
		config.read(reinterpret_cast<char*>(&getOneChar),sizeof(char)); 
		information[i] = getOneChar ;
	}

	//同理也需要两个index： infoIndex , ascllIndex 传引用,分别有偏移量
	
	
	config.close();
	
	
	int infoIndex = 0 ;
	int ascllIndex = nodeNumber;
	
	haffuNode<char> * root = GenHuffTreeByConfigFile(information, infoIndex, ascllIndex) ;
	haffumanTree<char>* tree =new haffumanTree<char>(root);
	
	//***************************************************************************
	
	ifstream fCompress(filename, ios::binary); 
	
	if ( !fCompress ) 
	{
		cout << "Can not find the compressed file !!!\n" << endl;
		return false;
	}	
	
	ofstream fUnCompress("uncompress.txt",ios::binary); // 将要写的txt文件
	
	if(! fUnCompress)
	{
		cout << "Can not open the file to be uncompressed !!!\n" << endl;
		return false;
	}
	
	haffuNode<char>* cur = tree->getRoot(); // 保存root节点
	
	
	
	unsigned char getOneByte ;
	unsigned char writeOneChar ;
	int pos = 8;
	
	fCompress.read(reinterpret_cast<char*>(&getOneByte),sizeof(char)); //先从压缩文件中读取一个字节
	
	// 解释一下为什么要在外面写if else语句,在里面判断的话代价更高，要比较total次, 在外面虽然丧失了一点阅读体验,但是值得
	
	if(nodeNumber == 1) //这里 nodeNumber = leafNumber = 1  
	{
		writeOneChar = dynamic_cast<haffuLeaf<char>*>(cur)->getValue() ; 
		// 已经确定了这一个字符，树结构是 1 value, 所以压缩文件的一个bit就代表一个字符
		
		while(true)   
		{
			--pos;
			
			fUnCompress.write(reinterpret_cast<char*>(&writeOneChar),sizeof(char)); //每一次都写
			total--;
			
			
			if(pos == 0)
			{
				fCompress.read(reinterpret_cast<char*>(&getOneByte),sizeof(char));
				pos = 8;
			}
			if(total == 1) { //不读取压缩时为了凑够一个字节而加进去的比特位  
				break;                               
			}				
		}  
	}
	else{
		
		while(true)  
		{
			--pos;
			
			if((getOneByte >> pos) & 1)   // 这里只能处理 leafNumber > 1 的情况
				cur = (dynamic_cast<internalNode<char>*>(cur))->getRight();
			else 
				cur = (dynamic_cast<internalNode<char>*>(cur))->getLeft();

			
			if(cur->isLeaf())
			{
				writeOneChar = dynamic_cast<haffuLeaf<char>*>(cur)->getValue();
				fUnCompress.write(reinterpret_cast<char*>(&writeOneChar),sizeof(char));
				cur = tree->getRoot();   //再次从根节点遍历  
				total--;
			}
			if(pos == 0)
			{
				fCompress.read(reinterpret_cast<char*>(&getOneByte),sizeof(char));
				pos = 8;
			}
			if(total == 1) { //不读取压缩时为了凑够一个字节而加进去的比特位  
				break;                               
			}				
		}  
		
	}
	

	
	tree->clear();//清空Huffman树
	
	fCompress.close();
	fUnCompress.close();
	
	return true;
}

