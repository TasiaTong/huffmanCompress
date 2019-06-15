#ifndef COMPRESS_H
#define COMPRESS_H

#include<iostream>
#include<fstream>
#include "haffumanTree.hpp"

using namespace std ;



/*
 * Name         : textInfo
 *
 * Synopsis     : bool textInfo(int information[256], const char* filename, long &total)  *
 * Arguments    : int  information : 存放字符频数的数组
 *                const char * filename : 用户传入的文件名
 *                long &total   : 计算文件的大小 以BYTE计算
 *
 * Description  : 统计文本文件字符的频数信息
 *    			  由于每一次读取一个字节(unsigned char 0~255)，则每个字节都能在256大小的数组找到位置
 *                这里我是用的是将字符数组的索引当作相应的字符，对于非英文也会将其放置在数组某一个位置(不会影响后面的操作)
 *                统计成功便返回true
 * 
 * Returns      : bool 
 */
bool textInfo(int information[256], const char* filename, long &total) ;

/*
 * Name         : generateHuffmanTree
 *
 * Synopsis     : generateHuffmanTree(char arr[], int length, int &leafNumber) *
 * Arguments    : char  arr : 统计好的字符频数数组
 *                int  length : 默认是256
 *
 * Description  : 通过字符数组，过滤掉其中频数为0的字符，同时统计叶节点的个数，建立哈夫曼堆，创建哈夫曼树
 * 
 * Returns      : haffumanTree<int>*
 */

haffumanTree<int>* generateHuffmanTree(char arr[], int length, int &leafNumber);


/*
 * Name         : treeInfo
 *
 * Synopsis     : void treeInfo(haffuNode<int>* tree, char infoAndAscll[], int &infoIndex, int &ascllIndex, 
			  string codeArray[], string code, int flag)  *
 * Arguments    : haffuNode<int>* tree ： 提取创建好的哈夫曼树的根节点，便于递归调用
 *                char  infoAndAscll : 写配置文件的字符数组，前2*leafNumber-1个字符是树的结构信息，后leafNumber个字符是对应的ascll信息 
 *                string  codeArray : 在递归过程中将每一个字符的code写到对应的string数组位置
 *                string  code : 用于动态地得到每一个字符的code,返回递归要回到原来的值，必须传值
 *                int  flag : 用于标记是当前子树在左子树还是在右子树位置
 *                int & : 每一次递增地将对应每一个节点结构信息写进数组里面去，必须使用传值
 *                int &asclIndex : 和infoIndex同样的道理
 *
 * Description  : 这一个函数可谓一举多得，一次前序遍历树就可以完成三件事情
 * 
 */



void treeInfo(haffuNode<int>* tree, char infoAndAscll[], int &infoIndex, int &ascllIndex, 
			  string codeArray[], string code, int flag) ;

			  			  
/*
 * Name         : compress
 *
 * Synopsis     : bool compress(const char* filename)  *
 * Arguments    : const char * filename : 用户的文件名
 *
 * Description  : 压缩成功返回true
 * 
 * Returns      : bool 
 */
bool compress(const char* filename) ; //根据文件路径压缩文件





#endif
