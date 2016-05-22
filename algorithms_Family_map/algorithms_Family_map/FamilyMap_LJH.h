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
	vector<treeNode*> printVector;		// (��ü ��� ��) Ư�� ������ �θ� ��� ����Ǵ� �迭
	int maxLevel;	// ���� ���� ����
	string fileName;
public:
	FamilyMap(string fileName);
	~FamilyMap();
	void insert(int level, string myName, string parentName = "", string wife = "");
	void remove(int level, string myName);
	void wifeModify(string myName, string wife);
	void printAll();
	void search(string myName);			// search �� ���õ� �� ����ϴ� �Ű�
	void search(int level);
	void search(int level, string myName);
	treeNode* find(treeNode *x, string myName);		// find�� �ش� ��� ã�� �Լ� (�̸����� ã��)
	void find(treeNode *x, int level);				// �ش� ���� ��� ã�Ƽ� vector�� �߰�
	void getMaxLevel(treeNode *x);		// �ִ� ����
	void writeFile();
	bool isEmpty();
	void printMenu();
	treeNode* getRoot();		// root ��ȯ
};