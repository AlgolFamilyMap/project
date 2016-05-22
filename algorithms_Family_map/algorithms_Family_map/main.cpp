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
	char saveFile;		// ������� ����?

	cout << "--------------<���̹� ���� �ý���>--------------" << endl;
	cout << "                    Menual                      " << endl;
	cout << "  * �ΰ� �߽� ����" << endl;
	cout << "  * ���� ���� �������� �Ұ�" << endl;
	cout << "  * �������� �����Ǹ� �ڽĵ鵵 ����" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "������ Ȯ���� �մϴ�. ���̵�� ��й�ȣ�� �Է��ϼ���." << endl;
	/*while (1) {
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
		cin >> temp_n;

		n = temp_n[0];
		cin.clear();
		if (!isdigit(n) || strlen(temp_n) != 1)
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
				cin >> check;
				if (!isDigit(check)) {
					cout << "���ڸ� �Է��ϼ���" << endl;
				}
				else {
					familyMap.search(stoi(check));
				}
				break;
			case '3':
				familyMap.printAll();
				break;
			case '4':
				cout << "����(�̸�)" << endl;
				cin >> name2;
				familyMap.remove(name2);
				familyMap.getMaxLevel(familyMap.getRoot());
				break;
			case '5':
				cout << "������ ����� [����, �̸�, �θ��̸�, �����(������)]�� �Է��� �ּ���. " << endl;
				cin >> check >> _name >> _pname;
				if (getchar() == ' ') cin >> _wife;
				else _wife = "(��ȥ)";

				if (!isDigit(check)) {
					cout << "����� ���ڸ� �Է��ϼ���" << endl;
					break;
				}
				if (_level == 1)
					cout << "root�� �߰��� �� �����ϴ�." << endl;
				else
				{
					familyMap.insert(_level, _name, _pname, _wife);
				}
				break;
			case '6':
				cout << "������ ����� �̸��� ����ڸ� �Է����ּ���." << endl;
				cin >> _name;
				if (getchar() == ' ') cin >> _wife;
				else _wife = "(��ȥ)";
				familyMap.wifeModify(_name, _wife);
				break;
			case '7':
				cout << "��������� �����ϰ� �����Ͻðڽ��ϱ�? (Y or N)" << endl;
				cin >> saveFile;
				if (saveFile == 'Y' || saveFile == 'y')
					familyMap.writeFile();
				else if (saveFile == 'N' || saveFile == 'n')
					exit(0);
				else
					cout << "�ùٸ� ���ڸ� �Է����ּ���." << endl;
				break;
				//default:
				//cout << "������" << endl;
				//exit(0); break;
			}
		}
	} while (true);
	return 0;
}