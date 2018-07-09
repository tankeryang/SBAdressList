#ifndef ADDRESSLIST_H_
#define ADDRESSLIST_H_

#include<iostream>
#include<fstream>
#include<string>
#include<ios>

using std::istream;
using std::ostream;
using std::ofstream;
using std::ifstream;
using std::string;
using std::cin;
using std::cout;
using std::endl;

/***********************************Item类****************************************/
class Item{
private:
	string _name;                                                      //姓名
	string _telNum;                                                    //号码
	string _address;                                                   //地址
public:
	Item(){};                                                          //构造函数
	Item(const char* name,const string & telNum,const string & address)//初始化构造函数
		:_name(name),_telNum(telNum),_address(address){};
	~Item(){                                                           //析构函数
		_name.clear();                                                 //清空姓名字符串
		_telNum.clear();                                               //清空号码字符串
		_address.clear();                                              //清空地址字符串
	};

	//功能函数
	void setName();                                                    //设置姓名
	void setTelNum();                                                  //设置号码
	void setAddress();                                                 //设置地址
	string & getName();                                                //获取姓名内容
	string & getTelNum();                                              //获取号码内容
	string & getAddress();                                             //获取地址内容
	friend ostream & operator<<(ostream & os,Item & i);                //输出Item类对象
	friend ofstream & operator<<(ofstream & ofs,Item & i);             //将Item类对象写入文件
};
/**********************************************************************************/


/************************************Node类****************************************/
class Node{
public:
	Item item;                   //Item类成员
	Node* next;                  //Node类型指针，指向下一个Node类型对象

	Node(){};                    //构造函数
	Node(Item & i){              //初始化构造函数
		item = i;
		next = NULL;
	};

	//功能函数
	void show();                 //输出item成员
	void save(ofstream & _fout); //将item成员写入文件
};
/**********************************************************************************/


/************************************List类****************************************/
class List:public Node{
private:
	Node *head,*tail;			                    //Node类型的头指针、尾指针
	int length;                                     //链表长度
public:
	List(){                                         //初始化List对象
		head = tail = NULL;
		length = 0;
		loginface();
	};

	//功能函数
	void loginface();                               //登录界面
	void operationface();                           //操作面板
	void add();                                     //添加功能
	void show();                                    //显示功能
	void save();                                    //保存到文件功能
	void load();                                    //从文件载入功能
	void search();                                  //查询功能
	void change();                                  //修改功能

	//辅助函数
	Node* findposition(const string & _searchName); //获取当前姓名所在位置
	int judgeinput(string & _input);                //判断用户功能选择输入
};

#endif