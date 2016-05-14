#include <iostream>
#include <fstream>
#include <string>
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
	dummy->next = NULL;
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
	newChild->next = NULL;

	p = root;
	while ((p->myName != newChild->parentName) && (p->son != NULL)) {// 부모에서 찾기
		p2 = p;
		while ((p2->myName != newChild->parentName) && (p2->next != NULL)) {	// 세대에서 찾기
			p2 = p2->next;
		}
		if (p2->myName == newChild->parentName) {
			p = p2;
			break;
		}
		p = p->son;
	}

	if (p->son == NULL) {	// 찾았는데 자식이 없으면
		p->son = newChild;	// 자식을 넣음

		p2 = p->son;			// 세대 등록
		while (p2->next != NULL)
			p2 = p2->next;
		if (newChild != p2)
			p2->next = newChild;
	}
	else { // 자식이 있으면
		p2 = p->son;
		while (p2->bro != NULL)		// 형제 찾아 이동
			p2 = p2->bro;
		p2->bro = newChild;		// 형제 끝에 추가

		p2 = p->son;			// 세대 등록
		while (p2->next != NULL)
			p2 = p2->next;
		if (newChild != p2)
			p2->next = newChild;
	}


}

void FamilyMap::remove(int level, string myName) {

}

void FamilyMap::printAll() {
	treeNode *tempPrint = root->son;		// 출력할 세대
	treeNode *tempPrintParent = root;		// 출력할 세대의 부모 세대

	while (tempPrint != NULL) {
		treeNode *tempBro = tempPrintParent;		// 출력할 세대의 부모 세대(형제 찾기)

		cout << "<" << tempPrint->level << " 세대> " << endl;
		cout << tempPrint->parentName << " : ";

		while (tempBro != NULL) {
			treeNode *tempBro2 = tempBro->son;		// 출력할 세대->부모세대->자식(형제 찾기)
			while (tempBro2 != NULL) {
				cout << tempBro2->myName << " ";
				tempBro2 = tempBro2->bro;
			}
			tempBro = tempBro->next;
			if (tempBro != NULL && tempBro->son != NULL)
				cout << endl << tempBro->son->parentName << " : ";
		}

		cout << endl << endl;
		tempPrint = tempPrint->son;

		tempPrintParent = tempPrintParent->son;
	}
}

void FamilyMap::search(string myName) {

}

void FamilyMap::search(int level) {

}

void FamilyMap::search(int level, string myName) {
	treeNode *temp = root;
	for (int i = 0; i < level - 1; i++) {
		temp = temp->son;
	}

	while (temp != NULL) {
		treeNode *tempBro = temp;	// 형제 찾기
		treeNode *tempPrint = temp;		// 형제 처음부터 출력

		while (tempBro != NULL) {
			if ((level == tempBro->level) && (myName == tempBro->myName)) {
				cout << "<검색 결과>" << endl;
				cout << " - 세대 : " << tempBro->level << endl;
				cout << " - 이름 : " << tempBro->myName << endl;
				if (tempBro->parentName != "")
					cout << " - 부모 이름 : " << tempBro->parentName << endl;
				else cout << " - 부모 없음" << endl;

				if (tempBro->son != NULL) {
					treeNode *sonBro = tempBro->son;
					cout << " - 자식 이름 : ";
					while (sonBro != NULL) {
						cout << sonBro->myName << " ";
						sonBro = sonBro->bro;
					}
					cout << endl;
				}
				else cout << " - 자식 없음" << endl;

				if (tempBro->wife != "")
					cout << " - 아내 이름 : " << tempBro->wife << endl;
				else cout << " - 아내 없음" << endl;

				treeNode *otherBro = tempPrint;
				if (tempPrint->bro != NULL) {
					cout << " - 형제 이름 : ";

					while (tempPrint != NULL) {
						if (tempPrint->myName != myName)
							cout << tempPrint->myName << " ";
						tempPrint = tempPrint->bro;
					}
				}
				else cout << " - 형제 없음" << endl;
			}

			tempBro = tempBro->next;
		}

		temp = temp->son;
	}
	cout << endl << endl;
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
	return 0;
}