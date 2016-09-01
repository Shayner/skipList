/*
 * skipList.h
 *
 *  Created on: 2016年8月31日
 *      Author: shayne
 */
#ifndef SKIPLIST_H_
#define SKIPLIST_H_
#include <cstddef>
#include <iostream>
#include "random.h"     //随机生成树函数

const int MAX_LEVEL = 16;   //定义最大层数
//定义key和value的类型
typedef int KeyType;
typedef int ValueType;

//定义结点数据结构
typedef struct nodeStructure{
    KeyType key;
    ValueType value;
    struct nodeStructure* forward[1];  //一个指针元素的数组，指针指向不同的数组大小
}* Node;
//定义跳跃表
typedef struct listStructure{
	int level;                    //记录跳跃表的当前最大层数
	struct nodeStructure* header;
}* List;

//定已跳跃表
class SkipList{
public:
	//初始化表结构
	SkipList():rand_(0xdeadbeef){
		NewList();   //分配内存空间
	}
	~SkipList(){
		FreeList();  //释放内存空间
	}

	//查找key,查找将值放于value中，并返回true;未找到返回false
	bool Search(const KeyType& key,ValueType& value);

	//插入key和value
	bool Insert(const KeyType& key,const ValueType& value);

	//删除key,将值放于value中，删除成功返回true;删除失败返回false
	bool Delete(const KeyType& key,ValueType& value);

	int size(){
		return size_;
	}

	//打印当前最大的leve
	int GetCurrentLevel(){
		return list_->level;
	}

	//打印当前列表信息
	void print();
private:
	void NewList();
	void FreeList();
	//创建一个新的结点，层数为level
	void NewNode(const int& level,Node& node);
	//随机生成一个层数
	int RandomLevel();
private:
	List list_;
	Node NUL_;     //结尾结点

	//链表中包含的几点个数
	size_t size_;
	Random rand_;
};
#endif /* SKIPLIST_H_ */
