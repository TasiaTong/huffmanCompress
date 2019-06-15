#ifndef UNCOMPRESS_H
#define UMCOMPRESS_H

#include<iostream>
#include<fstream>
#include "haffumanTree.hpp"

using namespace std ;



/*
 * Name         : GenHuffTreeByConfigFile
 *
 * Synopsis     :  GenHuffTreeByConfigFile(char information[], int &infoIndex, int &ascllIndex)  *
 * Arguments    : char  information : 已经先将配置文件中的信息先读到一个字符数组
 *              : int &infoIndex    :哈夫曼编码树的树结构信息索引,因为递归调用，要递增地改变值，传的是引用
 *              : int &ascllIndex   :叶子节点信息(ascll code)索引，因为递归调用，要递增地改变值，传的是引用
 *
 * Description  : 根据配置文件信息，建立哈夫曼编码树
 * 
 * Returns      : haffuNode<char>*
 */
haffuNode<char>* GenHuffTreeByConfigFile(char information[], int &infoIndex, int &ascllIndex) ;


/*
 * Name         : uncompress
 *
 * Synopsis     : bool uncompress(const char* filename)  *
 * Arguments    : const char * filename : 用户传入一个文件名
 *
 * Description  : 读取配置文件从而建立哈夫曼树，每次读取压缩文件一个BYTE,
 *                根据编码树(前序遍历)找到对应字符，然后每一次写一个BYTE进解压缩文件，
 *                然后解压缩成功，则返回true 
 * 
 * Returns      : bool 
 */
bool uncompress(const char* filename) ;



#endif
