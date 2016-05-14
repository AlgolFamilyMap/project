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
	treeNode *p = root, *p2 = new treeNode; // p = �ڽ� ã��(son�� �̵�),  p2 = ���� ã��(bro�� �̵�)
	newChild->parentName = parentName;
	newChild->myName = myName;
	newChild->level = level;
	newChild->wife = wife;
	newChild->bro = NULL;
	newChild->son = NULL;
	newChild->next = NULL;

	p = root;
	while ((p->myName != newChild->parentName) && (p->son != NULL)) {// �θ𿡼� ã��
		p2 = p;
		while ((p2->myName != newChild->parentName) && (p2->next != NULL)) {	// ���뿡�� ã��
			p2 = p2->next;
		}
		if (p2->myName == newChild->parentName) {
			p = p2;
			break;
		}
		p = p->son;
	}

	if (p->son == NULL) {	// ã�Ҵµ� �ڽ��� ������
		p->son = newChild;	// �ڽ��� ����

		p2 = p->son;			// ���� ���
		while (p2->next != NULL)
			p2 = p2->next;
		if (newChild != p2)
			p2->next = newChild;
	}
	else { // �ڽ��� ������
		p2 = p->son;
		while (p2->bro != NULL)		// ���� ã�� �̵�
			p2 = p2->bro;
		p2->bro = newChild;		// ���� ���� �߰�

		p2 = p->son;			// ���� ���
		while (p2->next != NULL)
			p2 = p2->next;
		if (newChild != p2)
			p2->next = newChild;
	}


}

void FamilyMap::remove(int level, string myName) {

}

void FamilyMap::printAll() {
	treeNode *tempPrint = root->son;		// ����� ����
	treeNode *tempPrintParent = root;		// ����� ������ �θ� ����

	while (tempPrint != NULL) {
		treeNode *tempBro = tempPrintParent;		// ����� ������ �θ� ����(���� ã��)

		cout << "<" << tempPrint->level << " ����> " << endl;
		cout << tempPrint->parentName << " : ";

		while (tempBro != NULL) {
			treeNode *tempBro2 = tempBro->son;		// ����� ����->�θ𼼴�->�ڽ�(���� ã��)
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
		treeNode *tempBro = temp;	// ���� ã��
		treeNode *tempPrint = temp;		// ���� ó������ ���

		while (tempBro != NULL) {
			if ((level == tempBro->level) && (myName == tempBro->myName)) {
				cout << "<�˻� ���>" << endl;
				cout << " - ���� : " << tempBro->level << endl;
				cout << " - �̸� : " << tempBro->myName << endl;
				if (tempBro->parentName != "")
					cout << " - �θ� �̸� : " << tempBro->parentName << endl;
				else cout << " - �θ� ����" << endl;

				if (tempBro->son != NULL) {
					treeNode *sonBro = tempBro->son;
					cout << " - �ڽ� �̸� : ";
					while (sonBro != NULL) {
						cout << sonBro->myName << " ";
						sonBro = sonBro->bro;
					}
					cout << endl;
				}
				else cout << " - �ڽ� ����" << endl;

				if (tempBro->wife != "")
					cout << " - �Ƴ� �̸� : " << tempBro->wife << endl;
				else cout << " - �Ƴ� ����" << endl;

				treeNode *otherBro = tempPrint;
				if (tempPrint->bro != NULL) {
					cout << " - ���� �̸� : ";

					while (tempPrint != NULL) {
						if (tempPrint->myName != myName)
							cout << tempPrint->myName << " ";
						tempPrint = tempPrint->bro;
					}
				}
				else cout << " - ���� ����" << endl;
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

	familyMap.insert(1, "����", "", "�Ƴ�1");
	familyMap.insert(2, "�ڽ�1", "����");
	familyMap.insert(2, "�ڽ�2", "����", "�Ƴ�2");
	familyMap.insert(3, "����1", "�ڽ�1", "�Ƴ�3");
	familyMap.insert(2, "�ڽ�3", "����");
	familyMap.insert(3, "����2", "�ڽ�2", "�Ƴ�4");
	familyMap.insert(3, "����3", "�ڽ�1", "�Ƴ�5");
	familyMap.insert(4, "������1", "����3");
	familyMap.insert(4, "������2", "����2");
	familyMap.insert(4, "������3", "����3");
	familyMap.insert(3, "����4", "�ڽ�2");
	familyMap.insert(4, "������4", "����1");
	familyMap.insert(5, "�����1", "������2");

	familyMap.printAll();

	cout << endl;
	familyMap.search(2, "�ڽ�3");
	familyMap.search(3, "����3");
	familyMap.search(2, "�ڽ�2");
	familyMap.search(4, "������3");
	return 0;
}