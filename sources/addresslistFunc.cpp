#include"addressList.h"

using std::ofstream;
using std::ifstream;
using std::ios;

/*******************************Item Methods*******************************/
void Item::setName() {
	cout << "请输入姓名 : ";
	std::getline(cin, _name);
	char* judgeName = new char[_name.length() + 1];
	_name.copy(judgeName, _name.length() + 1, 0);
	if (!_name.length() || judgeName[0] == ' ') {
		throw "你的输入错误，请按Enter键后重新尝试";
		delete judgeName;
	}
	delete judgeName;
};

void Item::setTelNum() {
	cout << "请输入电话号码 : ";
	std::getline(cin, _telNum);
};

void Item::setAddress() {
	cout << "请输入地址 : ";
	std::getline(cin, _address);
	cout << "输入成功！请按Enter键后继续" << endl;
};

string & Item::getName() {
	return _name;
};

string & Item::getTelNum() {
	return _telNum;
};

string & Item::getAddress() {
	return _address;
};

ostream & operator<<(ostream & os, Item & i) {
	os << i._name << "  ";
	os << i._telNum << "  ";
	os << i._address << endl;
	return os;
};

ofstream & operator<<(ofstream & ofs, Item & i) {
	ofs << i._name << "  ";
	ofs << i._telNum << "  ";
	ofs << i._address << endl;
	return ofs;
};
/**************************************************************************/


/*******************************Node Methods*******************************/
void Node::show() {
	cout << item;
};

void Node::save(ofstream & _fout) {
	_fout << item;
};
/**************************************************************************/


/*******************************List Methods*******************************/
void List::loginface() {
	cout << "\1********************************************************\1\n";
	cout << "\1*********          欢迎使用学生通讯录           ********\1\n";
	cout << "\1*********        班级：电子信息工程(4)班        ********\1\n";
	cout << "\1*********     制作团队：杨旸、潘铭津、邹晓瑜    ********\1\n";
	cout << "\1********************************************************\1\n";
	cout << endl;
	operationface();
	cout << endl;
};

void List::operationface() {
	cout << "\1****************** 请使用以下的操作：*******************\1\n";
	cout << endl;
	cout << "按 1：添加（增加一个人的记录到通信录中）" << endl;
	cout << "按 2：显示（在屏幕上显示所有通信录中的人员信息）" << endl;
	cout << "按 3：存储（将通讯录信息保存在一个文件中）" << endl;
	cout << "按 4：装入（将文件中的信息读入程序）" << endl;
	cout << "按 5：查询（可根据姓名查找某人的相关信息，若找到显示其姓名、地址、电话号码）" << endl;
	cout << "按 6：修改（可修改一个人的除姓名外其它信息）" << endl;
	cout << "按 7：退出" << endl;
	cout << endl;
	cout << "\1********************************************************\1\n";
	cout << endl;

	int choice = 7;
	string input;

	try {
		std::getline(cin, input);
		choice = judgeinput(input);
	}
	catch (const char* err) {
		cout << err << endl;
		getchar();
		operationface();
	}

	switch (choice) {
		cout << endl;
	case 1:
		add();
		getchar();
		operationface();
		break;
	case 2:
		show();
		getchar();
		operationface();
		break;
	case 3:
		save();
		getchar();
		operationface();
		break;
	case 4:
		load();
		getchar();
		operationface();
		break;
	case 5:
		try {
			search();
			getchar();
			operationface();
		}
		catch (const char* err) {
			cout << err << endl;
			getchar();
			operationface();
		}
		break;
	case 6:
		try {
			change();
			getchar();
			operationface();
		}
		catch (const char* err) {
			cout << err << endl;
			getchar();
			operationface();
		}
		break;
	case 7:
		cout << "感谢您的使用!" << endl;
		break;
	default:
		cout << "您的输入有误，请按Enter键后重新输入" << endl;
		getchar();
		operationface();
		break;
	}
};

void List::add() {
	Item data;
	try {
		data.setName();
	}
	catch (const char* err) {
		cout << err << endl;
		getchar();
		operationface();
	}
	data.setTelNum();
	data.setAddress();
	if (length == 0) {
		head = tail = new Node(data);
		if (head == NULL)
			throw "错误：该内容无法被添加";
	}
	else {
		tail->next = new Node(data);
		if (tail->next == NULL)
			throw "错误：该内容无法被添加";
		tail = tail->next;
	}
	length += 1;
};

void List::show() {
	if (length == 0) {
		cout << endl;
		cout << "列表为空！请按Enter键后继续" << endl;
		cout << endl;
	}
	else {
		Node *pn = head;
		cout << "地址列表" << endl;
		cout << "姓名" << "      " << "电话号码" << "       " << "地址" << endl;
		for (int i = 0;i < length;i++) {
			pn->show();
			pn = pn->next;
		};
		cout << endl << "以上为新添加通讯录成员。请按Enter键继续。" << endl;
	}
};

void List::save() {
	if (length == 0) {
		cout << endl;
		cout << "您未添加任何联系人。请按Enter键重新选择操作。" << endl;
	}
	else {
		ofstream fout("通讯录存档.txt", ios::app);
		Node *pn = head;
		for (int i = 0;i < length;i++) {
			pn->save(fout);
			pn = pn->next;
		};
		fout.close();
		cout << "系添加联系人已储存完毕。请按Enter键继续。" << endl;
	}
};

void List::load() {
	string fileName = "通讯录存档.txt";
	ifstream ifs(fileName.c_str(), ios::in);

	if (!ifs)
		cout << "通讯录存档.txt读取失败，请按Enter键重新选择操作。" << endl;
	else {
		string temp;
		if (ifs.eof())
			cout << "通讯录存档.txt无内容。请按Enter键重新选择操作。" << endl;
		else {
			while (!ifs.eof()) {
				getline(ifs, temp);
				cout << temp << endl;
			}
			cout << "通讯录存档载入完成。请按Enter键继续。" << endl;
		}
	}
	ifs.close();
};

void List::search() {
	if (length == 0) {
		cout << endl;
		cout << "列表为空！请按Enter键后继续" << endl;
		cout << endl;
	}
	else {
		string searchName;
		cout << "请输入要查找的姓名: ";
		std::getline(cin, searchName);

		if (!searchName.length()) {
			cout << endl;
			throw "您尚未输入该姓名.请再次尝试";
			cout << endl;
		}
		else {
			Node* pn = findposition(searchName);
			if (searchName == pn->item.getName()) {
				cout << "您所查找的人员:" << endl;
				pn->show();
				cout << "查找完成，请按Enter键返回至上一层" << endl;
			}
			else {
				cout << "您所查找的人员不存在." << endl;
				cout << endl;

			}
		}
	}
};

void List::change() {
	if (length == 0) {
		cout << "列表为空！请按Enter键后继续" << endl;
		cout << endl;

	}
	else {
		cout << "请输入您想更改的人员姓名: ";
		string searchName;
		string changeTelNum, changeAddress;
		std::getline(cin, searchName);

		if (!searchName.length()) {
			throw "您尚未输入该姓名，请再次尝试.";
		}
		else {
			Node* pn = findposition(searchName);
			if (searchName == pn->item.getName()) {
				cout << "更改的电话号码" << endl;
				pn->item.setTelNum();
				cout << "更改的地址" << endl;
				pn->item.setAddress();
			}
			else {
				cout << "您所查找的人员不存在.请按Enter键返回" << endl;
				cout << endl;
			}
		}
	}
};

Node* List::findposition(const string & _searchName) {
	Node* pn = head;
	while (_searchName != pn->item.getName() && pn != tail)
		pn = pn->next;
	return pn;
};

int List::judgeinput(string & _input) {
	int len = _input.length() + 1;
	char* judgeChoice = new char[len];
	_input.copy(judgeChoice, len, 0);
	for (int i = 0;i < _input.length();i++) {
		if (judgeChoice[i]<'0' || judgeChoice[i]>'9') {
			throw "你的选择有误，请按Enter键后再次尝试";
			cout << endl;
			delete judgeChoice;
			break;
		}
	}
	return atoi(judgeChoice);
};