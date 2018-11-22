
/*
* vs2017
* 2018.10.28
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
		node * leftChild;
		node * rightChild;
		int w;
		char c;
		bool flag;
	};
	node * base;
	int top;
	node * root;
public:
	tTree();
	~tTree();
	void writeToFile();
	void toCode(node * n,string &str);
	void createTree();
	bool huffmanDecode(string str,string &str1);
protected:
	void Find(node * &n1, node * &n2);
};

tTree::tTree()
{
	root = NULL;
	cin >> str;
	top = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i]<'a' || str[i]>'z') {
			cout << "please input correct English characters" << endl;
			return;
		}
	}
	base = (node *)malloc(sizeof(node)*(2*str.length()-1));//若有个叶节点则总节点数数为2n-1，实际上字母会有重复，用不了这么多空间，此处只是为了方便
	for (int i = 0; i < str.length(); i++) {
		int temp = flag.find(str[i]);         
		if (temp>=0) {                 //该字母已经添加过
			base[temp].w++;            //权值加1
		}
		else {
			base[top].c = str[i];
			base[top].w=1;
			base[top].leftChild = NULL;
			base[top].flag = false;
			base[top].rightChild = NULL;
			flag.push_back(str[i]);   //把字母添加到string flag中
			top++;
		}
	}
	createTree();
}

tTree::~tTree()
{
	
}


void tTree::createTree() {
	node * temp1=NULL;  //temp1 temp2用于指向权值最小的两个节点
	node * temp2=NULL;
	if (str.length() == 0) {
		tTree();
	}
	for (int i = 0; i < flag.length() - 1; i++) {
		Find(temp1, temp2);
		if (temp1 == NULL || temp2 == NULL) {
			cout << "error" << endl;
			return;
		}
		base[top].leftChild = temp1;
		base[top].rightChild = temp2;
		base[top].w = temp1->w + temp2->w;
		base[top].flag = false;
		top++;
	}
	root = &base[top - 1];
}

bool tTree::huffmanDecode(string str, string &str1)
{
	int i;
	if (root)
	{
		i = 0;      // 计数已解码01串的长度
		while (i < str.length())
		{
			node * tempNode = root;
			while (tempNode->leftChild != NULL && tempNode->rightChild != NULL)
			{
				if (str[i] == '0')
				{
					if (tempNode->leftChild == NULL) return false;
					tempNode = tempNode->leftChild;
				}
				else if(str[i]=='1')
				{
					if (tempNode->rightChild == NULL) return false;
					tempNode = tempNode->rightChild;
				}
				else {
					return false;
				}
				++i;
			}
			str1.push_back(tempNode->c);     
		}
	}
	return true;
}



void tTree::Find(node * &n1, node * &n2)   //找到权值最小的两个点
{
	bool flag = true;
	for (int i=0; i < top; i++) {
		if (!base[i].flag) {
			n1 = &base[i];
		}
	}
	for (int i =0; i < top; i++) {
		if (base[i].w < n1->w && !base[i].flag )
		{
			n1 = &base[i];
		}
	}
	n1->flag = true;                     //将找到的节点标记成已参与构造哈夫曼树
	for (int i = 0; i < top; i++) {
		if (!base[i].flag) {
			n2 = &base[i];
		}
	}
	for (int i = 0; i < top; i++) {
		if (base[i].w < n2->w && !base[i].flag)
		{
			n2 = &base[i];
		}
	}
	n2->flag = true;
}

void tTree::writeToFile()
{
	string s;
	if (root == NULL) return;
	this->toCode(root, s);
}

void tTree::toCode(node * n,string & s)
{
	if (n->leftChild != NULL)
	{
		s.push_back('0');
		toCode(n->leftChild,s);
	}
	if (n->rightChild != NULL)
	{
		s.pop_back();
		s.push_back('1');
		toCode(n->rightChild, s);
	}
	if (n->rightChild == NULL) {
		ofstream o;
		o.open(FILE_ROOT, ios::app);
		o << s << ' ' << n->c << endl;
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
	t1.writeToFile();
	ifstream i;
	i.open(FILE_ROOT, ios::in);
	string code;
	char c;
	string str;
	while (i>>c) {
		str.push_back(c);
		if (!(c >= 'a'&&c <= 'z')){
			cout << c;
		}
		else {
			cout <<' '<<c<< endl;
		}
	}
	cout << "please inpute code:";
	while (cin >> code)
	{
		string str;
		bool flag = t1.huffmanDecode(code, str);
		if (flag) cout << str<<endl;
		else cout << "please input correct code" << endl;
		cout << "please inpute code:";
	}
	return 0;
}