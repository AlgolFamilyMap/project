#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FamilyMap_LJH.h"

using namespace std;

FamilyMap::FamilyMap(string fileName) {
	dummy = new treeNode;
	dummy->level = 0;
	dummy->myName = "";
	dummy->parentName = "";
	dummy->wife = "";
	dummy->bro = NULL;
	dummy->son = NULL;
	root = dummy;
	this->fileName = fileName;

	ifstream fileIn;
	fileIn.open(fileName); // ���� ����
	if (!fileIn.is_open()) { // ���� ���� ���� üũ
		cout << "File Open error!" << endl;
		exit(1);
	}
	//���� �Է�
	treeNode itemTable[100];
	int tableSize = 0;
	string buffer, strTemp[4];
	// ���� �б� �� itemTable�� ����
	while (!fileIn.eof()) {
		getline(fileIn, buffer); // buffer�� ����
		if (buffer.size() < 1)
			break;

		// ��ū �и�
		int index = -1, beginIndex = 0;
		for (int i = 0; i < 3; i++) {
			index = buffer.find('\t', ++index); // "\t" ã��
			strTemp[i] = buffer.substr(beginIndex, index - beginIndex);
			beginIndex = index + 1;
		}
		strTemp[3] = buffer.substr(beginIndex);

		tableSize++;
		itemTable[tableSize - 1].level = stoi(strTemp[0]);
		itemTable[tableSize - 1].myName = strTemp[1];
		itemTable[tableSize - 1].parentName = strTemp[2];
		itemTable[tableSize - 1].wife = strTemp[3];
	}

	// Ʈ���� ����
	for (int i = 0; i < tableSize; i++)
		insert(itemTable[i].level, itemTable[i].myName, itemTable[i].parentName, itemTable[i].wife);

	fileIn.close();
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
	if (parentName != "root")
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


void FamilyMap::remove(int level, string name) // delete node and chilren
{
	treeNode *pTemp = new treeNode;
	treeNode *sTemp = new treeNode;
	treeNode *temp = new treeNode;
	sTemp = find(root, name);
	pTemp = find(root, sTemp->parentName);
	temp = pTemp->son;

	if (temp->myName == sTemp->myName) {
		if (sTemp->bro != NULL) {
			pTemp->son = sTemp->bro;
		}
		else {
			pTemp->son = NULL;
		}
	}
	else {
		while (temp->bro != sTemp){
			temp = temp->bro;
		}
		if (sTemp->bro != NULL) {
			temp->bro = sTemp->bro;
		}
		else {
			temp->bro = NULL;
		}
	}
	
	delete sTemp;
}

void FamilyMap::printAll() {
	treeNode *sonBro = new treeNode;		// �ڽ��� ���� ����� ���� ���

	getMaxLevel(root);

	// ���� ���
	//cout << "< 1 ���� >" << endl;
	cout << root->son->myName << endl << endl;

	// ���� �Ʒ�
	for (int i = 2; i <= maxLevel; i++) {		// �ְ� ������� �ݺ�
		printVector.clear();
		find(root, i - 1);		// ������ printVector�� i ������ �θ� ��� ������
								// i - 1 == i ������ �θ�
		/*if(printVector.size() >0) 
			cout << "< " << i << " ���� >" << endl;
		else break;*/

		for (int j = 0; j < printVector.size(); j++) {
			if (printVector[j]->son != NULL)	// �ڽ� ������
				sonBro = printVector[j]->son;	// i ���� ù��° �ڽ� ������
			else
				continue;

			//cout << printVector[j]->myName << " : ";	// �θ� �̸� ���

			while (sonBro != NULL) {		// �θ� �ڽĵ� ��� ���
				cout << sonBro->level << " " <<  sonBro->myName << " " <<
					sonBro->parentName << " " << sonBro->wife << endl;
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
	printVector.clear();
	find(root, level);
	if (printVector.empty())
	{
		cout << "�˻������ �����ϴ�." << endl;
	}
	else {
		cout << "<�˻� ���>" << endl;
		for (int i = 0; i < printVector.size(); i++)
		{
			cout << "- ���� : " << printVector[i]->level << endl;
			cout << "- �̸� : " << printVector[i]->myName << endl;
		}
	}
}

void FamilyMap::search(int level, string myName) {
	treeNode *temp = new treeNode;
	treeNode *tempBro = new treeNode;		// ���� ã��
	if (find(root, myName) == NULL)
	{
		cout << "�˻� ����� �����ϴ�." << endl;
	}
	else {
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

void FamilyMap::writeFile() {
	ofstream fileOut;
	fileName = "ouput.txt";
	fileOut.open(fileName);
	if (!fileOut.is_open()) {
		cout << "File Writer Error!" << endl;
		exit(1);
	}

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
		if (printVector.size() >0)
			cout << "< " << i << " ���� >" << endl;
		else break;

		for (int j = 0; j < printVector.size(); j++) {
			if (printVector[j]->son != NULL)	// �ڽ� ������
				sonBro = printVector[j]->son;	// i ���� ù��° �ڽ� ������
			else
				continue;

			cout << printVector[j]->myName << " : ";	// �θ� �̸� ���
			fileOut << printVector[j]->level << '\t' << printVector[j]->myName << '\t' <<
				printVector[j]->parentName << '\t' << printVector[j]->wife << endl;
			while (sonBro != NULL) {		// �θ� �ڽĵ� ��� ���
				cout << sonBro->myName << " ";
				fileOut << sonBro->level << '\t' << sonBro->myName << '\t' <<
					sonBro->parentName << '\t' << sonBro->wife << endl;
				sonBro = sonBro->bro;
			}
			cout << endl;
		}
		cout << endl;
	}

		


	fileOut.close();
}

bool FamilyMap::isEmpty() {
	if (root == dummy)
		return true;
	else
		return false;
}

void FamilyMap::printMenu() {
	cout << "1. �˻�(�̸�)\t2. �˻�(����)\t3.�˻�(����&�̸�)\t4.��ü ���\t5. ����\t6. ����" << endl;
}


treeNode* FamilyMap::getRoot() {
	return root;
}

int main(void) {
	FamilyMap familyMap("Family.txt");
	string name;
	int level;
	int n= 0;
	int level2;
	string name2;
	do {
		familyMap.printMenu();
		cout << "�Է� : ";
		cin >> n;
		switch (n) {
		case 1:
			cout << "�˻��� �̸� : ";
			cin >> name;
			familyMap.search(name);
			break;
		case 2:
			cout << "�˻��� ���� : ";
			cin >> level; 
			familyMap.search(level);
			break;
		case 3:
			cout << "�˻��� ����� �̸��� ���븦 �Է��ϼ��� : ";
			cin >> name >> level;
			familyMap.search(level,name);
			break;
		case 4:
			familyMap.printAll();
			break;
		case 5:
			familyMap.writeFile();
			break;
		case 6:
			cout << "����(����, �̸�)" << endl;
			cin >> level2 >> name2;
			familyMap.remove(level2, name2);
			familyMap.getMaxLevel(familyMap.getRoot());
			break;
		default:
			cout << "������" << endl;
			exit(0); break;
		}
	} while (n != 5);
	return 0;
}