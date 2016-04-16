#include <iostream>
#include <fstream>
#include <string>
#include "FamilyMap_LJH.h"
using namespace std;

FamilyMap::FamilyMap() {
	root->level = 0;
	root->myName = "";
	root->parentName = "";
	root->wife = "";
	root->bro = NULL;
	root->son = NULL;
	dummy = root;
}

FamilyMap::~FamilyMap() {
	
}

void FamilyMap::insert(int level, string myName, string parentName, string wife) {

}

void FamilyMap::remove(int level, string myName) {

}

void FamilyMap::printAll() {

}

void FamilyMap::search(string myName) {

}

void FamilyMap::search(int level) {

}

void FamilyMap::search(int level, string myName) {

}

bool FamilyMap::isEmpty() {
	if (root == dummy)
		return true;
	else
		return false;
}

void FamilyMap::printMenu() {

}


int main(void) {


	return 0;
}