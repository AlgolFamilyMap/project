#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FamilyMap_LJH.h"

using namespace std;

FamilyMap::FamilyMap() {
	dummy = new treeNode;
	dummy->level = 0;
	dummy->myName = "";
	dummy->parentName = "";
	dummy->wife = "";
	dummy->bro = NULL;
	dummy->son = NULL;
	root = dummy;
}

FamilyMap::~FamilyMap() {

}

void FamilyMap::insert(int level, string myName, string parentName, string wife) {
	treeNode *newChild = new treeNode;
	treeNode *p = root, *p2 = new treeNode; // p = 자식 찾기(son만 이동),  p2 = 형제 찾기(bro만 이동)
	newChild->parentName = parentName;
	newChild->myName = myName;
	newChild->level = level;
	newChild->wife = wife;
	newChild->bro = NULL;
	newChild->son = NULL;

	p = find(root, newChild->parentName);

	if (p->son == NULL) {	// 찾았는데 자식이 없으면ㅓ
		p->son = newChild;			// 자식만 넣음

	}
	else { // 자식이 있으면
		p2 = p->son;
		while (p2->bro != NULL)		// 형제 찾아 이동
			p2 = p2->bro;
		p2->bro = newChild;		// 형제 끝에 추가
	}
}

void FamilyMap::remove(int level, string myName) {

}

void FamilyMap::printAll() {
	treeNode *sonBro = new treeNode;		// 자식의 형제 출력을 위한 노드

	getMaxLevel(root);

	// 조상 출력
	cout << "< 1 세대 >" << endl;
	cout << root->son->myName << endl << endl;

	// 조상 아래
	for (int i = 2; i <= maxLevel; i++) {		// 최고 세대까지 반복
		printVector.clear();
		find(root, i - 1);		// 끝나면 printVector에 i 세대의 부모가 모두 들어가있음
								// i - 1 == i 세대의 부모

		cout << "< " << i << " 세대 >" << endl;

		for (int j = 0; j < printVector.size(); j++) {
			if (printVector[j]->son != NULL)	// 자식 있으면
				sonBro = printVector[j]->son;	// i 세대 첫번째 자식 가져옴
			else
				continue;

			cout << printVector[j]->myName << " : ";	// 부모 이름 출력

			while (sonBro != NULL) {		// 부모 자식들 모두 출력
				cout << sonBro->myName << " ";
				sonBro = sonBro->bro;
			}
			cout << endl;
		}
		cout << endl;
	}

}

void FamilyMap::search(string myName) {

}

void FamilyMap::search(int level) {

}

void FamilyMap::search(int level, string myName) {
	treeNode *temp = new treeNode;
	treeNode *tempBro = new treeNode;		// 형제 찾기

	temp = find(root, myName);
	tempBro = find(root, temp->parentName)->son;	// 찾은 사람의 부모의 첫번째 아들

	if ((level == temp->level) && (myName == temp->myName)) {
		// 공통(무조건 있는거)
		cout << "<검색 결과>" << endl;
		cout << " - 세대 : " << temp->level << endl;
		cout << " - 이름 : " << temp->myName << endl;

		// 부모이름
		if (temp->parentName != "")
			cout << " - 부모 이름 : " << temp->parentName << endl;
		else cout << " - 부모 없음" << endl;

		// 자식
		if (temp->son != NULL) {
			treeNode *sonBro = temp->son;
			cout << " - 자식 이름 : ";
			while (sonBro != NULL) {
				cout << sonBro->myName << " ";
				sonBro = sonBro->bro;
			}
			cout << endl;
		}
		else cout << " - 자식 없음" << endl;

		// 아내
		if (temp->wife != "")
			cout << " - 아내 이름 : " << temp->wife << endl;
		else cout << " - 아내 없음" << endl;


		if (tempBro->bro != NULL) {
			cout << " - 형제 이름 : ";

			while (tempBro != NULL) {
				if (tempBro->myName != myName)
					cout << tempBro->myName << " ";
				tempBro = tempBro->bro;
			}
		}
		else cout << " - 형제 없음" << endl;
	}

	cout << endl << endl;
}

treeNode* FamilyMap::find(treeNode *x, string myName) {
	treeNode *z = new treeNode;
	treeNode *z2 = new treeNode;

	if ((x != NULL) && (x->myName == myName))	// 찾으면 리턴
		return x;

	if (x != NULL) {		// 재귀
		z = find(x->son, myName);
		z2 = find(x->bro, myName);
	}

	if ((z != NULL) && (z->myName == myName))		// son에서 찾으면
		return z;
	else if ((z2 != NULL) && (z2->myName == myName))	// bro에서 찾으면
		return z2;
	else		// 못 찾음
		return 0;
}

void FamilyMap::find(treeNode *x, int level) {
	if (x != NULL && x->level == level) {	// 찾으려면 세대면 벡터에 저장
		printVector.push_back(x);
	}

	if (x != NULL) {		// 재귀
		find(x->son, level);
		find(x->bro, level);
	}
}

void FamilyMap::getMaxLevel(treeNode *x) {
	if (x != NULL && maxLevel < x->level)
		maxLevel = x->level;

	if (x != NULL) {		// 재귀
		getMaxLevel(x->son);
		getMaxLevel(x->bro);
	}
}

bool FamilyMap::isEmpty() {
	if (root == dummy)
		return true;
	else
		return false;
}

void FamilyMap::printMenu() {

}


treeNode* FamilyMap::getRoot() {
	return root;
}

int main(void) {
	FamilyMap familyMap;

	familyMap.insert(1, "조상", "", "아내1");
	familyMap.insert(2, "자식1", "조상");
	familyMap.insert(2, "자식2", "조상", "아내2");
	familyMap.insert(3, "손자1", "자식1", "아내3");
	familyMap.insert(2, "자식3", "조상");
	familyMap.insert(3, "손자2", "자식2", "아내4");
	familyMap.insert(3, "손자3", "자식1", "아내5");
	familyMap.insert(4, "증손자1", "손자3");
	familyMap.insert(4, "증손자2", "손자2");
	familyMap.insert(4, "증손자3", "손자3");
	familyMap.insert(3, "손자4", "자식2");
	familyMap.insert(4, "증손자4", "손자1");
	familyMap.insert(5, "고손자1", "증손자2");

	familyMap.printAll();

	cout << endl;
	familyMap.search(2, "자식3");
	familyMap.search(3, "손자3");
	familyMap.search(2, "자식2");
	familyMap.search(4, "증손자3");


	treeNode *yo = new treeNode;
	yo = familyMap.find(familyMap.getRoot(), "증손자4");
	cout << " find 예제 : " << yo->myName << endl;
	return 0;
}