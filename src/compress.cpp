#include "compress.hpp"
#include<iostream>
#include<fstream>
#include "haffumanTree.hpp"

using namespace std ;


bool textInfo(int Infoarray[256], const char* filename, long &total)
{
	ifstream is(filename, ios::binary);
	
	if (! is)
	{
		cout << "Error opening file\n";
		return false;
	}
	
	unsigned char getOnechar ;
	
	total = 0 ;
	
	while(! is.eof())
	{
		is.read(reinterpret_cast<char*>(&getOnechar), sizeof(char)); 
		++Infoarray[getOnechar];
		++total ;
	}
	
	is.close();
	return true ;
}


haffumanTree<int>* generateHuffmanTree(int arr[], int length, int &leafNumber) // 这里T是int型(后面转成char), arr是原始数组 length = 256 
{
	haffumanTree<int>* array[length];
		
	leafNumber = 0 ;
	
	for(int i = 0 ; i < length ;++i)
	{
		if(arr[i] != 0) //过滤掉没有出现过的字符
			array[leafNumber++] = new haffumanTree<int>(i, arr[i]); //i是ascll信息， arr[i]是频数
	}

	
	heap<haffumanTree<int>*>* forest = new heap<haffumanTree<int>*>(array, leafNumber);
    
    while(forest->getSize() > 1)
    	forest->insert(new haffumanTree<int>(forest->remove(0),forest->remove(0)));
    
    return forest->getValue(0) ;
}




void treeInfo(haffuNode<int>* root, unsigned char infoAndAscll[], int &infoIndex, int &ascllIndex,
			   string codeArray[], string code, int flag) 
{
	if(flag == 1)
		code += "1";
	else if(flag == 0)
		code += "0";
	
	if(root->isLeaf())
	{
		
		int value = dynamic_cast<haffuLeaf<int>*>(root)->getValue() ; // value就是字母
		
		infoAndAscll[infoIndex++] = '0' ;   //叶节点以 0 标记
		infoAndAscll[ascllIndex++] = value; //字母信息 0 ~255 
		codeArray[value] = code;  
		return ;
	}
	infoAndAscll[infoIndex] = '1' ;
	++infoIndex ;
	
	treeInfo(dynamic_cast<internalNode<int>*>(root)->getLeft(), infoAndAscll, infoIndex, ascllIndex, codeArray, code,0);
	treeInfo(dynamic_cast<internalNode<int>*>(root)->getRight(), infoAndAscll, infoIndex, ascllIndex, codeArray, code,1);
}

bool compress(const char* filename)
{
	int Infoarray[256] = {0}; // 0~127个字符(注意：虽然声明是int型数组，但是他的index很有用，可以当作相应的字母)
	
	long total = 0;
	 
	if(false ==  textInfo(Infoarray,filename, total))  // 在这个函数里面计算 
	{
		cout<<"can not complete that, please check yourself!\n";
		return false ;
	}
	
	//step1 complete*****************************************************************************************************
	
	
	int leafNumber = 0 ;

	//下面开始建树
	haffumanTree<int>* tree = generateHuffmanTree(Infoarray, 256, leafNumber); 

	string codeArray[256];//为每一个字母编码 : 同样的道理，索引就是字母，对应的值就是编码
	
	// unsigned char infoAndAscll[767] ;
	unsigned char infoAndAscll[3*leafNumber-1] ;// 完全树 结构信息(n + n-1), n个ascll码 一个字节存储(后面写的时候要求只占一个字节)前2*leafNumber-1 字符是结构信息， 后leafNumber 字符是assic码
	
	int infoIndex = 0 ; //偏移量
	int ascllIndex = 2*leafNumber-1;  // 偏移量


	// 这里只需要前序遍历一次树就可以同时完成三件事情 1 . 2. 已经构建完成配置信息  3. 同时完成字母信息 
	//这里有一个问题，在极端情况下，文件里一种字符，这时候，root是一个叶节点，flag应该为1 ，所以更改一下flag 
	
	treeInfo(tree->getRoot(),infoAndAscll,infoIndex,ascllIndex,codeArray,string(),leafNumber);
	
	tree->clear();
	
	//将leafNumber 和infoAndascll中的信息按顺序写到配置文件中
	
	ofstream os("fConfig.dat",ios::binary); // 这里的文件路径自己设置
	if(! os)
	{
		cout<<"open file error!\n";
		return false;
	}
	
	
	int nodeNumber = 2*leafNumber-1 ;
	
	os.write(reinterpret_cast<char*>(&total),sizeof(long)); //sizeof(long)个字节写入总字数，便于后面解压缩
	os.write(reinterpret_cast<char*>(&nodeNumber), sizeof(int)); // 4个字节
	os.write(reinterpret_cast<char*>(infoAndAscll), (3*leafNumber-1)*sizeof(char)); //( 3*leafNumber-1 )个字节

	os.close();
	
	//step2 complete*******************************************************************************************************
	
	//开始一个一个字节的压缩
	ifstream sourceFile(filename,ios::binary);
	ofstream compressFile("compressed.zip",ios::binary);
	 
	if(!sourceFile || !compressFile )
	{
		cout<<"wrong\n";
		return false;
	}

	unsigned char getOnechar ;

	string code ;
	
	int pos = 0 ;
	unsigned char value  = 0;
	
	 
	while(! sourceFile.eof())
	{
		sourceFile.read(reinterpret_cast<char*>(&getOnechar), sizeof(char)); //先一个一个读
		
		code = codeArray[getOnechar] ;//找到对应的编码
		
		for(unsigned int i = 0 ; i < code.size(); ++i)
		{
			value <<=  1 ;
			
			if(code[i] == '1')
				value |= 1 ;
			
			
			if(++pos == 8)
			{
				compressFile.write(reinterpret_cast<char*>(&value), sizeof(char));
				pos = 0 ;
				value = 0 ;
			}
		}
		
	}
	
	
	if(pos)
	{
		value = value<<(8-pos);
		compressFile.write(reinterpret_cast<char*>(&value), sizeof(char));
	}
	
	
	
	compressFile.close();
	sourceFile.close();
	
	//final step complete***************************************************************************************************
	
	return true ;
}
 
