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
	fileIn.open(fileName); // 파일 열기
	if (!fileIn.is_open()) { // 파일 열기 오류 체크
		cout << "File Open error!" << endl;
		exit(1);
	}
	//파일 입력
	treeNode itemTable[100];
	int tableSize = 0;
	string buffer, strTemp[4];
	// 파일 읽기 및 itemTable에 저장
	while (!fileIn.eof()) {
		getline(fileIn, buffer); // buffer에 저장
		if (buffer.size() < 1)
			break;

		// 토큰 분리
		int index = -1, beginIndex = 0;
		for (int i = 0; i < 3; i++) {
			index = buffer.find('\t', ++index); // "\t" 찾기
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
			itemTable[tableSize - 1].wife = "(미혼)";
	}

	// itemTable 오름차순 정렬
	quickSort(itemTable, 0, tableSize - 1);

	// 트리에 삽입
	for (int i = 0; i < tableSize; i++)
		insert(itemTable[i].level, itemTable[i].myName, itemTable[i].parentName, itemTable[i].wife);

	fileIn.close();
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

	if (parentName != "root")
		p = find(root, newChild->parentName);
	if (p == NULL) {
		cout << "부모 이름을 찾을 수 없습니다. 제대로 입력하세요." << endl;
		return;
	}
	if (find(root, myName) != NULL)
	{
		cout << "동명이인이 존재하거나 올바른 이름이 아닙니다." << endl;
		return;
	}
	if ((level - 1) != p->level) {
		cout << "추가하려는 세대와 부모의 세대는 1 차이여야 합니다." << endl;
		return;
	}
	if (p->son == NULL) {	// 찾았는데 자식이 없으면
		p->son = newChild;			// 자식만 넣음

	}
	else { // 자식이 있으면
		p2 = p->son;
		while (p2->bro != NULL)		// 형제 찾아 이동
			p2 = p2->bro;
		p2->bro = newChild;		// 형제 끝에 추가
	}
}


void FamilyMap::remove(string name) // delete node and chilren
{
	if (name == root->son->myName) {
		cout << "조상은 삭제 불가능합니다" << endl;
		return;
	}
	treeNode *pTemp = new treeNode;
	treeNode *sTemp = new treeNode;
	treeNode *temp = new treeNode;
	sTemp = find(root, name); //삭제할 노드
	if (sTemp == NULL) { //삭제할 노드가 존재하지 않으면 종료
		cout << "해당 이름을 찾을 수 없습니다. " << endl;
		return;
	}

	pTemp = find(root, sTemp->parentName); //삭제할 노드의 부모노드
	temp = pTemp->son; //그 부모의 첫번째 자식

	//삭제할 노드가 첫번째 자식인경우
	if (temp->myName == sTemp->myName) {
		if (sTemp->bro != NULL) { //형제가 없는경우
			pTemp->son = sTemp->bro;
		}
		else { //형제가 존재하는 경우
			pTemp->son = NULL;
		}
	}
	else { //삭제할 노드가 첫번째 자식이 아닌경우
		while (temp->bro != sTemp) {
			temp = temp->bro;
		}
		if (sTemp->bro != NULL) { //형제가 존재하는 경우
		temp->bro = sTemp->bro;
		}
		else { //형제가 없는경우
			temp->bro = NULL;
		}
	}

	delete sTemp;
}


void FamilyMap::wifeModify(string myName, string wife) {
	treeNode *temp = new treeNode;

	temp = find(root, myName);
	if (temp == NULL) {
		cout << "해당 이름이 없습니다." << endl;
		return;
	}
	else {
		if (temp->wife == "(미혼)")
		{
			temp->wife = wife;
		}
		else
			temp->wife = wife + "(재혼)";
	}
}

void FamilyMap::printAll() {
	treeNode *sonBro = new treeNode;		// 자식의 형제 출력을 위한 노드

	getMaxLevel(root);

	// 조상 출력
	//cout << "< 1 세대 >" << endl;
	cout << root->son->level << " " << root->son->myName << " " <<
		root->son->parentName << " " << root->son->wife << endl << endl;

	// 조상 아래4
	for (int i = 2; i <= maxLevel; i++) {		// 최고 세대까지 반복
		printVector.clear();
		find(root, i - 1);		// 끝나면 printVector에 i 세대의 부모가 모두 들어가있음
								// i - 1 == i 세대의 부모
								/*if(printVector.size() >0)
								cout << "< " << i << " 세대 >" << endl;
								else break;*/

		for (int j = 0; j < printVector.size(); j++) {
			if (printVector[j]->son != NULL)	// 자식 있으면
				sonBro = printVector[j]->son;	// i 세대 첫번째 자식 가져옴
			else
				continue;

			//cout << printVector[j]->myName << " : ";	// 부모 이름 출력

			while (sonBro != NULL) {		// 부모 자식들 모두 출력
				cout << sonBro->level << " " << sonBro->myName << " " <<
					sonBro->parentName << " " << sonBro->wife << endl;
				sonBro = sonBro->bro;
			}

		}
		cout << endl;
	}

}

//void FamilyMap::search(string myName) {
//	treeNode *temp = new treeNode;
//	if (find(root, myName) == NULL)
//	{
//		cout << "검색 결과가 없습니다." << endl;
//	}
//	else {
//		temp = find(root, myName);
//		cout << "- 세대 : " << temp->level << endl;
//		cout << "- 이름 : " << temp->myName << endl;
//		cout << "- 부모 : " << temp->parentName << endl;
//	}
//}

void FamilyMap::search(int level) {
	printVector.clear();
	find(root, level);
	if (printVector.empty())
	{
		cout << "검색결과가 없습니다." << endl;
	}
	else {
		cout << "<검색 결과>" << endl;
		cout << level << " 세대" << endl;
		for (int i = 0; i < printVector.size(); i++)
		{
			cout << "- 이름 : " << printVector[i]->myName << endl;
		}
	}
}

void FamilyMap::search(string myName) {
	treeNode *temp = new treeNode;
	treeNode *tempBro = new treeNode;		// 형제 찾기


	temp = find(root, myName);
	if (temp == NULL) {
		cout << "해당 이름을 찾을 수 없습니다. " << endl;
		return;
	}
	tempBro = find(root, temp->parentName)->son;	// 찾은 사람의 부모의 첫번째 아들
	
	if (myName == temp->myName) {
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

		// 배우자
		if (temp->wife != "")
			cout << " - 배우자 이름 : " << temp->wife << endl;
		else cout << " - 배우자 없음" << endl;


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

void FamilyMap::writeFile() {
	ofstream fileOut;
	fileName = "family.txt";
	fileOut.open(fileName);
	if (!fileOut.is_open()) {
		cout << "File Writer Error!" << endl;
		exit(1);
	}

	treeNode *sonBro = new treeNode;		// 자식의 형제 출력을 위한 노드

	getMaxLevel(root);
	// 조상 출력
	//cout << "< 1 세대 >" << endl;

	fileOut << root->son->level << "\t" << root->son->myName << "\t" <<
		root->son->parentName << "\t" << root->son->wife << endl;

	// 조상 아래4
	for (int i = 2; i <= maxLevel; i++) {		// 최고 세대까지 반복
		printVector.clear();
		find(root, i - 1);		// 끝나면 printVector에 i 세대의 부모가 모두 들어가있음
								// i - 1 == i 세대의 부모
								/*if(printVector.size() >0)
								cout << "< " << i << " 세대 >" << endl;
								else break;*/

		for (int j = 0; j < printVector.size(); j++) {
			if (printVector[j]->son != NULL)	// 자식 있으면
				sonBro = printVector[j]->son;	// i 세대 첫번째 자식 가져옴
			else
				continue;

			//cout << printVector[j]->myName << " : ";	// 부모 이름 출력

			while (sonBro != NULL) {		// 부모 자식들 모두 출력
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
	cout << "1. 검색(이름)\t2. 검색(레벨)\t3. 전체 출력\t4. 삭제\n5. 삽입\t\t6. 배우자 수정\t7. 종료" << endl;
}


treeNode* FamilyMap::getRoot() {
	return root;
}
