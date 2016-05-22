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


void FamilyMap::remove(int level, string name) // delete node and chilren
{
	if (name == root->son->myName) {
		cout << "조상은 삭제 불가능합니다" << endl;
		return;
	}
	treeNode *pTemp = new treeNode;
	treeNode *sTemp = new treeNode;
	treeNode *temp = new treeNode;
	sTemp = find(root, name);
	if (sTemp == NULL) {
		cout << "해당 이름을 찾을 수 없습니다. " << endl;
		return;
	}
	if (sTemp->level != level) {
		cout << "세대가 맞지 않습니다. 다시 입력하세요." << endl;
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

void FamilyMap::search(string myName) {
	treeNode *temp = new treeNode;
	if (find(root, myName) == NULL)
	{
		cout << "검색 결과가 없습니다." << endl;
	}
	else {
		temp = find(root, myName);
		cout << "- 세대 : " << temp->level << endl;
		cout << "- 이름 : " << temp->myName << endl;
		cout << "- 부모 : " << temp->parentName << endl;
	}
}

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

void FamilyMap::search(int level, string myName) {
	treeNode *temp = new treeNode;
	treeNode *tempBro = new treeNode;		// 형제 찾기


	temp = find(root, myName);
	tempBro = find(root, temp->parentName)->son;	// 찾은 사람의 부모의 첫번째 아들
	if (temp == NULL) {
		cout << "해당 이름을 찾을 수 없습니다. " << endl;
		return;
	}
	if (temp->level != level) {
		cout << "세대가 맞지 않습니다. 다시 입력하세요." << endl;
		return;
	}
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
	cout << "1. 검색(이름)\t2. 검색(레벨)\t3.검색(레벨&이름)\t4.전체 출력\t5. 종료\t6. 삭제" << endl;
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
	cout << "--------------<사이버 족보 시스템>--------------" << endl;
	cout << "관리자 확인을 합니다. 아이디와 비밀번호를 입력하세요." << endl;
	while (1) {
		string _id, _password;
		string check_id = "4조", check_pw = "홍영식_교수님_사랑해요";
		cout << "아이디 : ";
		cin >> _id;
		cout << "비밀번호 : ";
		cin >> _password;
		if (_id.compare(check_id) == 0 && (_password.compare(check_pw)) == 0) {
			cout << "로그인 성공!" << endl;
			break;
		}
		else
			cout << "아이디 혹은 비밀번호가 올바르지 않습니다." << endl;
	}*/
	do {
		familyMap.printMenu();
		cout << "입력 : ";
		cin>>temp_n;

		n=temp_n[0];
		cin.clear();
		if (!isdigit(n)||strlen(temp_n)!=1)
		{
			cout << "입력이 잘못되었습니다." << endl;
		}
		else {
			switch (n) {
			case '1':
				cout << "검색할 이름 : ";
				cin >> name;
				familyMap.search(name);
				break;
			case '2':
				cout << "검색할 세대 : ";
				cin >> level;
				/*if (!isdigit(level))
				{
					cout << "숫자를 입력하세요" << endl; break;
				}
				else*/
					familyMap.search(level); break;
			case '3':
				cout << "검색할 사람의 이름과 세대를 입력하세요 : ";
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
				cout << "삭제(레벨, 이름)" << endl;
				cin >> level2 >> name2;
				familyMap.remove(level2, name2);
				familyMap.getMaxLevel(familyMap.getRoot());
				break;
			case '7':

				cout << "level과 name을 입력해 주세요. " << endl;
				cin >> _level >> _name >> _pname;
				if (getchar() == ' ') cin >> _wife;
				else _wife = "(미혼)";
				if (_level == 1)
					cout << "root에 추가할 수 없습니다." << endl;
				else
				{
					familyMap.insert(_level, _name, _pname, _wife);
				}
				break;
				//default:
					//cout << "에러임" << endl;
					//exit(0); break;
			}
		}
	} while (true);
	return 0;
}