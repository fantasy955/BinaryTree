
/*
* vs2017
* 2018.10.30
*/



#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;

#define FILE_ROOT "E:\\HuffManCode.txt"

class tTree
{
private:
	string str;
	string flag;
	struct node
	{
		int leftChild;
		int rightChild;
		int parentNode;
		int w;
		char c;
		bool flag;
	};
	node * base;
	int top;
	int root;
public:
	tTree();
	~tTree();
	void WriteToFile();
	void toCode(int n, string &str);
protected:
	void CreateTree();
	void Find(int &n1, int &n2);
};

tTree::tTree()
{
	cin >> str;
	root = -1;
	top = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i]<'a' || str[i]>'z') {
			cout << "please input correct English characters" << endl;
			return;
		}
	}
	base = (node *)malloc(sizeof(node)*(2 * str.length() - 1));//若有个叶节点则总节点数数为2n-1，实际上字母会有重复，用不了这么多空间，此处只是为了方便
	for (int i = 0; i < str.length(); i++) {
		int temp = flag.find(str[i]);
		if (temp >= 0) {                 //该字母已经添加过
			base[temp].w++;            //权值加1
		}
		else {
			base[top].c = str[i];
			base[top].w = 1;
			base[top].leftChild = -1;
			base[top].parentNode = -1;
			base[top].flag = false;
			base[top].rightChild = -1;
			flag.push_back(str[i]);   //把字母添加到string flag中
			top++;
		}
	}
	CreateTree();
}

tTree::~tTree()
{

}


void tTree::CreateTree() {
	int temp1 = -1;  //temp1 temp2用于指向权值最小的两个节点
	int temp2 = -1;
	if (str.length() == 0) return;
	for (int i = 0; i < flag.length() - 1; i++) {
		Find(temp1, temp2);
		if (temp1 == -1 || temp2 == -1) {
			cout << "error" << endl;
			return;
		}
		base[top].leftChild = temp1;
		base[top].rightChild = temp2;
		base[top].w = base[temp1].w + base[temp2].w;
		base[temp1].parentNode = top;
		base[temp2].parentNode = top;
		base[top].flag = false;
		top++;
	}
	root = top - 1;
}



void tTree::Find(int &n1, int &n2)   //找到权值最小的两个点
{
	bool flag = true;
	for (int i = 0; i < top; i++) {
		if (!base[i].flag) {
			n1 = i;
		}
	}
	for (int i = 0; i < top; i++) {
		if (base[i].w < base[n1].w && !base[i].flag)
		{
			n1 = i;
		}
	}
	base[n1].flag = true;                     //将找到的节点标记成已参与构造哈夫曼树
	for (int i = 0; i < top; i++) {
		if (!base[i].flag) {
			n2 = i;
		}
	}
	for (int i = 0; i < top; i++) {
		if (base[i].w < base[n2].w && !base[i].flag)
		{
			n2 = i;
		}
	}
	base[n2].flag = true;
}

void tTree::WriteToFile()
{
	string s;
	if (root == -1) return;
	this->toCode(root, s);
}

void tTree::toCode(int n, string & s)
{
	if (base[n].leftChild != -1)
	{
		s.push_back('0');
		toCode(base[n].leftChild, s);
	}
	if (base[n].rightChild != -1)
	{
		s.pop_back();
		s.push_back('1');
		toCode(base[n].rightChild, s);
	}
	if (base[n].rightChild == -1) {
		ofstream o;
		o.open(FILE_ROOT, ios::app);
		o << s << ' ' << base[n].c << endl;
		o.close();
		return;
	}
	s.pop_back();
}


int main() {
	ofstream o;
	o.open(FILE_ROOT, ios::trunc);
	o.close();
	tTree t1;
	t1.WriteToFile();
	ifstream i;
	i.open(FILE_ROOT, ios::in);
	string str;
	string code;
	char c;
	while (i >> c) {
		str.push_back(c);
		if (!(c >= 'a'&&c <= 'z')) {
			cout << c;
		}
		else {
			cout <<' '<< c << endl;
		}
	}
	if (str.length() == 0) return 0;
	cout << "please input code:";
	while (cin >> code)
	{
		unsigned i = str.find(code);
		//判断输入的编码是否是对应一个字母
		if (i == string::npos || str[i + code.length()]<'a' || str[i + code.length()]>'z' || (i > 0 && (str[i - 1]<'a' || str[i - 1]>'z'))) {
			cout << "code error" << endl;
			cout << "please input code:";
			continue;
		}
		else {
			cout << str[i + code.length()] << endl;
		}
		cout << "please input code:";
	}
	return 0;
}