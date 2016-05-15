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
	treeNode *p = root, *p2 = new treeNode; // p = �ڽ� ã��(son�� �̵�),  p2 = ���� ã��(bro�� �̵�)
	newChild->parentName = parentName;
	newChild->myName = myName;
	newChild->level = level;
	newChild->wife = wife;
	newChild->bro = NULL;
	newChild->son = NULL;

	p = find(root, newChild->parentName);

	if (p->son == NULL) {	// ã�Ҵµ� �ڽ��� �������
		p->son = newChild;			// �ڽĸ� ����

	}
	else { // �ڽ��� ������
		p2 = p->son;
		while (p2->bro != NULL)		// ���� ã�� �̵�
			p2 = p2->bro;
		p2->bro = newChild;		// ���� ���� �߰�
	}
}

void FamilyMap::remove(int level, string myName) {

}

void FamilyMap::printAll() {
	treeNode *sonBro = new treeNode;		// �ڽ��� ���� ����� ���� ���

	getMaxLevel(root);

	// ���� ���
	cout << "< 1 ���� >" << endl;
	cout << root->son->myName << endl << endl;

	// ���� �Ʒ�
	for (int i = 2; i <= maxLevel; i++) {		// �ְ� ������� �ݺ�
		printVector.clear();
		find(root, i - 1);		// ������ printVector�� i ������ �θ� ��� ������
								// i - 1 == i ������ �θ�

		cout << "< " << i << " ���� >" << endl;

		for (int j = 0; j < printVector.size(); j++) {
			if (printVector[j]->son != NULL)	// �ڽ� ������
				sonBro = printVector[j]->son;	// i ���� ù��° �ڽ� ������
			else
				continue;

			cout << printVector[j]->myName << " : ";	// �θ� �̸� ���

			while (sonBro != NULL) {		// �θ� �ڽĵ� ��� ���
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
	treeNode *tempBro = new treeNode;		// ���� ã��

	temp = find(root, myName);
	tempBro = find(root, temp->parentName)->son;	// ã�� ����� �θ��� ù��° �Ƶ�

	if ((level == temp->level) && (myName == temp->myName)) {
		// ����(������ �ִ°�)
		cout << "<�˻� ���>" << endl;
		cout << " - ���� : " << temp->level << endl;
		cout << " - �̸� : " << temp->myName << endl;

		// �θ��̸�
		if (temp->parentName != "")
			cout << " - �θ� �̸� : " << temp->parentName << endl;
		else cout << " - �θ� ����" << endl;

		// �ڽ�
		if (temp->son != NULL) {
			treeNode *sonBro = temp->son;
			cout << " - �ڽ� �̸� : ";
			while (sonBro != NULL) {
				cout << sonBro->myName << " ";
				sonBro = sonBro->bro;
			}
			cout << endl;
		}
		else cout << " - �ڽ� ����" << endl;

		// �Ƴ�
		if (temp->wife != "")
			cout << " - �Ƴ� �̸� : " << temp->wife << endl;
		else cout << " - �Ƴ� ����" << endl;


		if (tempBro->bro != NULL) {
			cout << " - ���� �̸� : ";

			while (tempBro != NULL) {
				if (tempBro->myName != myName)
					cout << tempBro->myName << " ";
				tempBro = tempBro->bro;
			}
		}
		else cout << " - ���� ����" << endl;
	}

	cout << endl << endl;
}

treeNode* FamilyMap::find(treeNode *x, string myName) {
	treeNode *z = new treeNode;
	treeNode *z2 = new treeNode;

	if ((x != NULL) && (x->myName == myName))	// ã���� ����
		return x;

	if (x != NULL) {		// ���
		z = find(x->son, myName);
		z2 = find(x->bro, myName);
	}

	if ((z != NULL) && (z->myName == myName))		// son���� ã����
		return z;
	else if ((z2 != NULL) && (z2->myName == myName))	// bro���� ã����
		return z2;
	else		// �� ã��
		return 0;
}

void FamilyMap::find(treeNode *x, int level) {
	if (x != NULL && x->level == level) {	// ã������ ����� ���Ϳ� ����
		printVector.push_back(x);
	}

	if (x != NULL) {		// ���
		find(x->son, level);
		find(x->bro, level);
	}
}

void FamilyMap::getMaxLevel(treeNode *x) {
	if (x != NULL && maxLevel < x->level)
		maxLevel = x->level;

	if (x != NULL) {		// ���
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


	treeNode *yo = new treeNode;
	yo = familyMap.find(familyMap.getRoot(), "������4");
	cout << " find ���� : " << yo->myName << endl;
	return 0;
}