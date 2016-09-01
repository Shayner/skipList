/*
 * SkipList.cpp
 *
 *  Created on: 2016年8月31日
 *      Author: shayne
 */

#include  "skipList.h"
#include <cstdlib>
#include <assert.h>


void SkipList::NewList(){
	//设置结尾结点
	NewNode(MAX_LEVEL,NUL_);
	NUL_->key = 0x7fffffff;           //设置为最大数

	list_ = (List)malloc(sizeof(listStructure));
	list_->level = 0;

	//设置头结点
	NewNode(MAX_LEVEL,list_->header);
	for(int i = 0; i < MAX_LEVEL; i++){
		list_->header->forward[i] = NUL_;
	}

	size_ = 0;
}
void SkipList::FreeList(){
	Node cur = list_->header;
	Node q;
	while(cur != NUL_){
		q = cur->forward[0];
		free(cur);
		cur = q;
	}
	free(cur);
	free(list_);
}

void SkipList::NewNode(const int& level,Node& node){
	//结点需要的总空间
	int total_size = sizeof(nodeStructure) + level*sizeof(Node);
	//申请空间
	node = (Node)malloc(total_size);

	assert(node != NULL);
}

bool SkipList::Search(const KeyType &key, ValueType &value){
	Node cur = list_->header;

	int i;
	//从最高层开始往下
	int stop = -1;
	for(i = list_->level;i >= 0; i--){
		if(stop != -1 ) break;
		while(cur->forward[i] && cur->forward[i]->key <=  key){
			if(cur->forward[i]->key == key){
				stop = i;
				break;                                     //在仔细考虑
                        }
                        cur = cur->forward[i];
		}
	}

	cur = cur->forward[stop];

	if(cur->key == key){
		value = cur->value;
		return true;
	}else
		return false;
}
/*
 * 1、查找需要插入的位置
 * 2、申请内存空间
 * 3、更新指针，用update数组来记录需要更新的指针
 */
bool SkipList::Insert(const KeyType& key, const ValueType& value){
	Node update[MAX_LEVEL];

	Node cur = list_->header;
	int i;
	for(i = list_->level; i>= 0; i--){
		while(cur->forward[i] && cur->forward[i]->key < key){
			cur = cur->forward[i];
		}
		update[i] = cur;
	}

	cur = cur->forward[0];

	if(cur->key == key){
		//如何已经存在
		cur->value = value;
		return false;
	}else{
		//随机生成层数
		int level = RandomLevel();

		//分配空间
		Node newNode;
		NewNode(level, newNode);
		newNode->key = key;
		newNode->value = value;

		//随机产生的level大于当前的最大level时
		if(level > list_->level){
			level = ++list_->level;
			update[level] = list_->header;
		}

		//更新指针
		int i;
		Node prev;
		for(i = level; i >= 0 ; i--){
			prev = update[i];
			newNode->forward[i] = prev->forward[i];
			prev->forward[i] = newNode;
		}
		++size_;
		return true;
	}
}
/*
 * 1、找到要删除的节点
 * 2、调整指针
 * 3、删除节点
 */
bool SkipList::Delete(const KeyType& key,ValueType& value){
	   Node update[MAX_LEVEL];

	   //寻找要删除的节点前一个节点
		Node cur = list_->header;
		int i;
		for(i = list_->level; i>= 0; i--){
			while(cur->forward[i] && cur->forward[i]->key < key){
				cur = cur->forward[i];
			}
			update[i] = cur;
		}

		cur = cur->forward[0];
		if(cur->key != key){
			return false;
		}else{
			value = cur->value;

			//调整指针
			int i;
			for(i = list_->level; i >= 0; i--){
				if(update[i]->forward[i] == cur)
					update[i]->forward[i] = cur->forward[i];
			}
			free(cur);
			//调整list_->level
			while(list_->level > 0 &&
					list_->header->forward[list_->level] == NUL_)
				--list_->level;
			size_--;
			return true;
		}
}

int SkipList::RandomLevel(){
	int level = static_cast<int>(rand_.Uniform(MAX_LEVEL));

	if(level == 0)
		level = 1;

	return level;
}

void SkipList::print(){
	Node head = list_->header;
	int i;
	for(i = list_->level; i >= 0; i--){
		std::cout << "header--->";
		Node cur = head;
		while(cur->forward[i] != NUL_){
			std::cout << "<"<<cur->forward[i]->key<<","<<cur->forward[i]->value << ">" << "--->";
			cur = cur->forward[i];
		}
		std::cout << "tail" << std::endl;
	}
}
