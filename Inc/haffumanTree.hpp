#ifndef HAFFUMAN_TREE_H
#define HAFFUMAN_TREE_H

#include "littleHeap.hpp"

template <typename T>
class haffuNode
{ 

	protected :
	
	int weight ;
	
	public: 
	
	haffuNode(int weight): weight(weight) {}
	
	int getWeight() const 	{ return weight; }
	
	virtual bool isLeaf() = 0 ;
	
};



template <typename T>
class haffuLeaf: public haffuNode<T> 
{
	private: 
	
	T value ;
	
	public: 
	
	haffuLeaf(T &val,int Weight): value(val), haffuNode<T>(Weight){} // 只能有这一种构造函数
	
	
	T getValue() const
	{
		return value ;
	}
	
	bool isLeaf() 
	{
		return true ;
	}
	
};




template <typename T>
class internalNode: public haffuNode<T>
{
	
	private: 
	
	haffuNode<T>* left ;
	haffuNode<T>* right ;
	
	
	public: 
	
	
	// 只能有这一种构造函数 ,理论上left 和right 不能同时为 NULL
	internalNode(haffuNode<T>* left = NULL, haffuNode<T>* right = NULL)
	: left(left), right(right), haffuNode<T>(left->getWeight() + right->getWeight()) {}
	
	
	~internalNode()
	{
		
	}
	
	haffuNode<T>* getLeft() const 
	{
		return left ;
	}
	
	haffuNode<T>* getRight() const
	{
		return right ;
	}	
	
	void setLeft(haffuNode<T>* leftNode)
	{
		left = leftNode ;
	}
	
	void setRight(haffuNode<T>* rightNode)	
	{
		right = rightNode ;
	}
	
	bool isLeaf()
	{
		return false ;
	}
	
	
	
};





template <typename T>
class haffumanTree
{
	private: 
	
	haffuNode<T>* root ;
	
	
	public:
	
	haffumanTree(haffuNode<T>* &root): root(root) {}
	
	haffumanTree(T &value, int weight)
	{
		root = new haffuLeaf<T>(value, weight);
	}
	
	haffumanTree(haffumanTree* left, haffumanTree* right)
	{
		root = new internalNode<T>(left->root,right->root);
	}
	
	
	int getWeight() const
	{
		return root->getWeight() ;
	}
	
	haffuNode<T>* getRoot()
	{
		return root ;
	}
	
	
	
	bool operator >(haffumanTree<T>& another)
	{
		return  this->getWeight() > another.getRoot()->getWeight();
	}
	
	
	
	void clear()
	{
		clearRecur(root);
	}
	
	
	void clearRecur(haffuNode<T>* root)
	{
		if(root == nullptr )
			return ;
		
		if(root->isLeaf())
		{
			delete root ;
			return ;
		}
		
		clearRecur((dynamic_cast<internalNode<T>*>(root))->getLeft());
		clearRecur((dynamic_cast<internalNode<T>*>(root))->getRight());
		
	}
	
};



#endif