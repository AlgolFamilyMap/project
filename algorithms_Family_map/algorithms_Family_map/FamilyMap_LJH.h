#pragma once

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef struct TreeNode {
	int level;
	string myName;
	string parentName;
	string wife;
	struct TreeNode *bro, *son;
} treeNode;

class FamilyMap {
	treeNode *root, *dummy;
	vector<treeNode*> printVector;		// (전체 출력 시) 특정 세대의 부모가 모두 저장되는 배열
	int maxLevel;	// 가장 높은 세대
	string fileName;
public:
	FamilyMap(string fileName);
	~FamilyMap();
	void insert(int level, string myName, string parentName = "", string wife = "");
	void remove(int level, string myName);
	void wifeModify(string myName, string wife);
	void printAll();
	void search(string myName);			// search 는 관련된 거 출력하는 거고
	void search(int level);
	void search(int level, string myName);
	treeNode* find(treeNode *x, string myName);		// find는 해당 노드 찾는 함수 (이름으로 찾기)
	void find(treeNode *x, int level);				// 해당 세대 모두 찾아서 vector에 추가
	void getMaxLevel(treeNode *x);		// 최대 레벨
	void writeFile();
	bool isEmpty();
	void printMenu();
	treeNode* getRoot();		// root 반환
};