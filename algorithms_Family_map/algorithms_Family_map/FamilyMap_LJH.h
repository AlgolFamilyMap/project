#pragma once

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct treeNode {
	int level;
	string myName;
	string parentName;
	string wife;
	treeNode *bro;
	treeNode *son;
};

class FamilyMap {
	treeNode *root;
	treeNode *dummy;
public:
	FamilyMap();
	~FamilyMap();
	void insert(int level, string myName, string parentName, string wife = "");
	void remove(int level, string myName);
	void printAll();
	void search(string myName);
	void search(int level);
	void search(int level, string myName);
	bool isEmpty();
	void printMenu();
};