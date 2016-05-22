#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FamilyMap_LJH.h"
#include "sort.h"
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
		if (strTemp[3] != "")
			itemTable[tableSize - 1].wife = strTemp[3];
		else
			itemTable[tableSize - 1].wife = "(��ȥ)";
	}

	// itemTable �������� ����
	quickSort(itemTable, 0, tableSize - 1);

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

	if (p == NULL) {
		cout << "�θ� �̸��� ã�� �� �����ϴ�. ����� �Է��ϼ���." << endl;
		return;
	}
	if (p->son == NULL) {	// ã�Ҵµ� �ڽ��� ������
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
	if (name == root->son->myName) {
		cout << "������ ���� �Ұ����մϴ�" << endl;
		return;
	}
	treeNode *pTemp = new treeNode;
	treeNode *sTemp = new treeNode;
	treeNode *temp = new treeNode;
	sTemp = find(root, name);
	if (sTemp == NULL) {
		cout << "�ش� �̸��� ã�� �� �����ϴ�. " << endl;
		return;
	}
	if (sTemp->level != level) {
		cout << "���밡 ���� �ʽ��ϴ�. �ٽ� �Է��ϼ���." << endl;
		return;
	}

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
		while (temp->bro != sTemp) {
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
	cout << root->son->level << " " << root->son->myName << " " <<
		root->son->parentName << " " << root->son->wife << endl << endl;

	// ���� �Ʒ�4
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
				cout << sonBro->level << " " << sonBro->myName << " " <<
					sonBro->parentName << " " << sonBro->wife << endl;
				sonBro = sonBro->bro;
			}

		}
		cout << endl;
	}

}

void FamilyMap::search(string myName) {
	treeNode *temp = new treeNode;
	if (find(root, myName) == NULL)
	{
		cout << "�˻� ����� �����ϴ�." << endl;
	}
	else {
		temp = find(root, myName);
		cout << "- ���� : " << temp->level << endl;
		cout << "- �̸� : " << temp->myName << endl;
		cout << "- �θ� : " << temp->parentName << endl;
	}
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
		cout << level << " ����" << endl;
		for (int i = 0; i < printVector.size(); i++)
		{
			cout << "- �̸� : " << printVector[i]->myName << endl;
		}
	}
}

void FamilyMap::search(int level, string myName) {
	treeNode *temp = new treeNode;
	treeNode *tempBro = new treeNode;		// ���� ã��


	temp = find(root, myName);
	tempBro = find(root, temp->parentName)->son;	// ã�� ����� �θ��� ù��° �Ƶ�
	if (temp == NULL) {
		cout << "�ش� �̸��� ã�� �� �����ϴ�. " << endl;
		return;
	}
	if (temp->level != level) {
		cout << "���밡 ���� �ʽ��ϴ�. �ٽ� �Է��ϼ���." << endl;
		return;
	}
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

void FamilyMap::writeFile() {
	ofstream fileOut;
	fileName = "family.txt";
	fileOut.open(fileName);
	if (!fileOut.is_open()) {
		cout << "File Writer Error!" << endl;
		exit(1);
	}

	treeNode *sonBro = new treeNode;		// �ڽ��� ���� ����� ���� ���

	getMaxLevel(root);
	// ���� ���
	//cout << "< 1 ���� >" << endl;

	fileOut << root->son->level << "\t" << root->son->myName << "\t" <<
		root->son->parentName << "\t" << root->son->wife << endl;

	// ���� �Ʒ�4
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
				fileOut << sonBro->level << "\t" << sonBro->myName << "\t" <<
					sonBro->parentName << "\t" << sonBro->wife << endl;
				sonBro = sonBro->bro;
			}
		}
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
	FamilyMap familyMap("family.txt");
	string name;
	int level;
	char *temp_n = new char;
	char n;
	int level2;
	string name2;
	int _level = 0;
	string _name = "", _pname = "", _wife = "";
	/*
	cout << "--------------<���̹� ���� �ý���>--------------" << endl;
	cout << "������ Ȯ���� �մϴ�. ���̵�� ��й�ȣ�� �Է��ϼ���." << endl;
	while (1) {
		string _id, _password;
		string check_id = "4��", check_pw = "ȫ����_������_����ؿ�";
		cout << "���̵� : ";
		cin >> _id;
		cout << "��й�ȣ : ";
		cin >> _password;
		if (_id.compare(check_id) == 0 && (_password.compare(check_pw)) == 0) {
			cout << "�α��� ����!" << endl;
			break;
		}
		else
			cout << "���̵� Ȥ�� ��й�ȣ�� �ùٸ��� �ʽ��ϴ�." << endl;
	}*/
	do {
		familyMap.printMenu();
		cout << "�Է� : ";
		cin>>temp_n;

		n=temp_n[0];
		cin.clear();
		if (!isdigit(n)||strlen(temp_n)!=1)
		{
			cout << "�Է��� �߸��Ǿ����ϴ�." << endl;
		}
		else {
			switch (n) {
			case '1':
				cout << "�˻��� �̸� : ";
				cin >> name;
				familyMap.search(name);
				break;
			case '2':
				cout << "�˻��� ���� : ";
				cin >> level;
				/*if (!isdigit(level))
				{
					cout << "���ڸ� �Է��ϼ���" << endl; break;
				}
				else*/
					familyMap.search(level); break;
			case '3':
				cout << "�˻��� ����� �̸��� ���븦 �Է��ϼ��� : ";
				cin >> name >> level;
				familyMap.search(level, name);
				break;
			case '4':
				familyMap.printAll();
				break;
			case '5':
				familyMap.writeFile();
				exit(0);
				break;
			case '6':
				cout << "����(����, �̸�)" << endl;
				cin >> level2 >> name2;
				familyMap.remove(level2, name2);
				familyMap.getMaxLevel(familyMap.getRoot());
				break;
			case '7':

				cout << "level�� name�� �Է��� �ּ���. " << endl;
				cin >> _level >> _name >> _pname;
				if (getchar() == ' ') cin >> _wife;
				else _wife = "(��ȥ)";
				if (_level == 1)
					cout << "root�� �߰��� �� �����ϴ�." << endl;
				else
				{
					familyMap.insert(_level, _name, _pname, _wife);
				}
				break;
				//default:
					//cout << "������" << endl;
					//exit(0); break;
			}
		}
	} while (true);
	return 0;
}