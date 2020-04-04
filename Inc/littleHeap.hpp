#ifndef LITTLE_HEAP_H
#define LITTLE_HEAP_H

#include<iostream>


	
template <typename T>
class heap
{
private : 
	
	T *array;
	
	int size ;
	
	int maxsize ;
	
	
	private :
	
	
	bool swap(int first, int second) ;
	bool check(int pos) ;
	int parent(int pos) ;
	int leftChild(int pos) ;
	int rightChild(int pos) ;
	bool sitdown(int pos) ;
	void buildHeap();
	bool hasRight(int pos) ;
	
	public:
	
	
	heap(T a[], int length)
    {
		
		size = 0 ;
		maxsize = length +1 ;
    	array = new T[maxsize];
		for(int i = 0 ; i < length ; ++i) //完全拷贝
    	{
			array[i] = a[i];
    		size++ ;
    	}
		
    	buildHeap();
    }
    	
    ~heap()
    {
    	delete []array ;
	}

	
	
	int getSize();
	bool append(const T &value) ;
	bool isLeaf(int pos) ;
	bool insert(const T &value) ;

	T getValue(int pos)
	{   if(! check(pos))
		{
			std::cout<<"can not get value !\n";
			exit(-1);
		}
		return array[pos];
	}

	
    T remove(int pos) 
    {
    	if(! check(pos))
    		return 0 ;
    	
    	T temp = array[pos];
		
		if(pos == size-1)
		{
			--size ;
			return temp ;
		}
		
    	swap(pos,size-1) ;
		--size ;
		
		int PARENT = parent(pos) ;
		
		while(pos != 0 && *(array[PARENT]) > *(array[pos]))
		{
			swap(pos,PARENT) ;
			pos = PARENT;
		}
		if(size != 0)
			sitdown(pos);
			
    	return temp ;
	}
	
};



template <typename T>
int heap<T>::getSize() 
{
	return size ;
}


template <typename T>
bool heap<T>::swap(int first, int second)
{
	if(! check(first) || !check(second) )
		return false;
	T temp = array[first] ;
	array[first] = array[second];
	array[second] = temp ;
	return true ;
}
	
template <typename T>
bool heap<T>::check(int pos)
{
	return pos >= 0 && pos < size ;
}



template <typename T>
int heap<T>::parent(int pos)
{
	if(pos > 0 && pos < size)
		return (pos-1)/2 ;
	
	return -1 ;
}


template <typename T>
int heap<T>::leftChild(int pos)
{
	if(pos >= 0 && pos < size/2)
		return 2*pos +1 ; 
	
	return -1 ;
}


template <typename T>
int heap<T>::rightChild(int pos)
{
	if(pos >= 0 && pos < size/2)
		return 2*pos +2 ; 
	
	return -1 ;
}


template <typename T>
bool heap<T>::append(const T &value)
{
	if(size == maxsize)
	{
		std::cout<<"this heap is full !\n";
		return false;
	}
	array[size++] = value ;
	return true ;
}


template <typename T>
bool heap<T>::isLeaf(int pos)
{
	return pos >= size/2 && pos < size ;
}


template <typename T>
bool heap<T>::sitdown(int pos)
{
	
	if(! check(pos))
	{
		std::cout<<"position is wrong ! \n";
		return false;
	}
	while(! isLeaf(pos))
	{
		int littleChild = leftChild(pos) ;
		
		if( hasRight(pos))
		{
			if(*(array[littleChild]) > *(array[rightChild(pos)]) )
				littleChild = rightChild(pos);   
		}
		
		if(*(array[pos]) > *(array[littleChild]) )//需要重载Ｔ类型的 operator < ,> ==
			swap(pos,littleChild) ;        //对于哈夫曼树来讲，可比较 weight 
		
		pos = littleChild ;
	}
	return true ;
}

template <typename T>
void heap<T>::buildHeap()
{
	for(int i = size/2 -1 ; i >= 0  ; --i )
		sitdown(i);
}

template <typename T>
bool heap<T>::insert(const T &value)
{
	if(size == maxsize)
	{
		std::cout<<"this heap is full !\n";
		return false;
	}
	
	array[size++] = value ;
	int curr = size-1 ;
	int PARENT = parent(curr);
	
	while( PARENT != -1 && value < array[PARENT] )
	{
		swap(curr, PARENT);
		curr = PARENT; 
		PARENT = parent(curr);
	}
	
	
	return true ;
}


template <typename T>
bool heap<T>::hasRight(int pos)
{
	return pos*2 +2 < size ;
}



#endif
