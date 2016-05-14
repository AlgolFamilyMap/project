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
	struct TreeNode *next;	// ������ �ƴ����� ���� ����
} treeNode;

class FamilyMap {
	treeNode *root, *dummy;
public:
	FamilyMap();
	~FamilyMap();
	void insert(int level, string myName, string parentName = "", string wife = "");
	void remove(int level, string myName);
	void printAll();
	void search(string myName);
	void search(int level);
	void search(int level, string myName);
	bool isEmpty();
	void printMenu();
};