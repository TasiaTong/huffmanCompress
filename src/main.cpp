#include "compress.hpp"
#include "uncompress.hpp"
#include <ctime>



void userInterface();



int main(void)
{
	
	userInterface();
	
	char fileName[200];
	
	int choice =0 ;
	cin>>choice ;
	
	clock_t start , end ;
	double endtime ;
	
	while(choice != 3)
	{
		start = end = 0 ;
		
		if(choice == 1)
		{
			cout<<"Please enter name of file to be compressed : ";
			cin>>fileName ;
			cout<<"\nPlease wait ......\n";
			
			start = clock() ;
			
			if(compress(fileName))
			{
				cout<<"compress complete ! And the compressed file and fconfig file are created !\n";
			
			    end = clock();
				endtime=(double)(end-start)/CLOCKS_PER_SEC;
				cout<<"It took "<<endtime<<" s in total !\n";
				
			}
		}
		else if(choice == 2)
		{
			cout<<"Please enter name of file to be Uncompressed : ";
			cin>>fileName ;
			
			cout<<"\nPlease wait ......\n";
			
			start = clock() ;
			
			if(uncompress(fileName))
			{
				
				cout<<"uncompress complete !\n";
				
				end = clock();
				endtime=(double)(end-start)/CLOCKS_PER_SEC;
				
				cout<<"It took "<<endtime<<" s in total !\n";
			}
		}else 
		{
			cout<<"\nWrong chioce! Please enter right choice next time !!!";
		}
		cin.clear();
		cin.sync();   //或者用cin.ignore(); 不然非法输入可能会造成死循环
		
		userInterface();
		cin>>choice ;
	}
	
	cout<<"BYE BYE ...........\n";

	return 0;
	
}


void userInterface()
{
	cout<<"\n************************************* Welcome to compress and Uncompress software ***************************************\n";
	cout<<"1. compress   file   "<<endl ;
	cout<<"2. Uncompress file   "<<endl ;
	cout<<"3. get out of here   "<<endl ;
	cout<<"please enter your choice: ";
	
}

