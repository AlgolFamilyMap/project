#include "FamilyMap_LJH.h"

bool isDigit(string s) {
	int len = s.size();
	for (int i = 0; i<len; ++i) {

		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

int main(void) {
	FamilyMap familyMap("family.txt");
	string name;
	int level;
	char *temp_n = new char;
	char n;
	string check;
	string name2;
	int _level = 0;
	string _name = "", _pname = "", _wife = "";
	char saveFile;		// 변경사항 저장?

	cout << "--------------<사이버 족보 시스템>--------------" << endl;
	cout << "                    Menual                      " << endl;
	cout << "  * 부계 중심 족보" << endl;
	cout << "  * 족보 내에 동명이인 불가" << endl;
	cout << "  * 족보에서 삭제되면 자식들도 삭제" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "관리자 확인을 합니다. 아이디와 비밀번호를 입력하세요." << endl;
	/*while (1) {
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
		cin >> temp_n;

		n = temp_n[0];
		cin.clear();
		if (!isdigit(n) || strlen(temp_n) != 1)
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
				cin >> check;
				if (!isDigit(check)) {
					cout << "숫자를 입력하세요" << endl;
				}
				else {
					familyMap.search(stoi(check));
				}
				break;
			case '3':
				familyMap.printAll();
				break;
			case '4':
				cout << "삭제(이름)" << endl;
				cin >> name2;
				familyMap.remove(name2);
				familyMap.getMaxLevel(familyMap.getRoot());
				break;
			case '5':
				cout << "삽입할 사람의 [세대, 이름, 부모이름, 배우자(있으면)]을 입력해 주세요. " << endl;
				cin >> check >> _name >> _pname;
				if (getchar() == ' ') cin >> _wife;
				else _wife = "(미혼)";

				if (!isDigit(check)) {
					cout << "세대는 숫자를 입력하세요" << endl;
					break;
				}
				if (_level == 1)
					cout << "root에 추가할 수 없습니다." << endl;
				else
				{
					familyMap.insert(_level, _name, _pname, _wife);
				}
				break;
			case '6':
				cout << "수정할 사람의 이름과 배우자를 입력해주세요." << endl;
				cin >> _name;
				if (getchar() == ' ') cin >> _wife;
				else _wife = "(이혼)";
				familyMap.wifeModify(_name, _wife);
				break;
			case '7':
				cout << "변경사항을 저장하고 종료하시겠습니까? (Y or N)" << endl;
				cin >> saveFile;
				if (saveFile == 'Y' || saveFile == 'y')
					familyMap.writeFile();
				else if (saveFile == 'N' || saveFile == 'n')
					exit(0);
				else
					cout << "올바른 문자를 입력해주세요." << endl;
				break;
				//default:
				//cout << "에러임" << endl;
				//exit(0); break;
			}
		}
	} while (true);
	return 0;
}