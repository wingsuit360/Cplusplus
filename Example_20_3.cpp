#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template<class T>
struct Stack {
	vector<T> sv;
	void push(T t) {
		sv.insert(sv.begin(), t);
	}
	T pop() {
		T tmp = sv.front();
		sv.erase(sv.begin());
		return tmp;
	}
	bool empty() {
		return sv.empty();
	}
};

template<class T>
struct Queue {
	vector<T> qv;
	void push(T t) {
		qv.push_back(t);
	}
	T pop() {
		T tmp = qv.front();
		qv.erase(qv.begin());
		return tmp;
	}
	bool empty() {
		return qv.empty();
	}
};

template<class T>
struct BNode
{
	T data;
	BNode<T> *left, *right;

	BNode(T dd, BNode<T> *l = NULL, BNode<T> *r = NULL) :
		data(dd), left(l), right(r)
	{}
};

template<class T>
void print(BNode<T> *r, int offset = 0)
{
	if (r == NULL) return;
	print(r->right, offset + 3);
	for (int i = 0; i<offset; i++)
		cout << " ";
	cout << r->data << endl;
	print(r->left, offset + 3);
}

template<class T>
int count1(BNode<T> *r)
{
	int c = 0;
	if (r == NULL) return c;
	if (r->left != NULL) c++;
	if (r->right != NULL) c++;
	return c;
}

template<class T>
int count_depth(BNode<T> *p)
{
	if (p == NULL) return 0;
	return 1 + count_depth(p->left) + count_depth(p->right);
}

template<class T>
int count_depth2(BNode<T> *p)
{
	int c = 0;
	Stack<BNode<T>*> S;
	BNode<T> *t;
	if (p == NULL) return 0;
	S.push(p);
	while (!S.empty())
	{
		c++;
		t = S.pop();
		if (t->left != NULL) S.push(t->left);
		if (t->right != NULL) S.push(t->right);
	}
	return c;
}

template<class T>
int count_width(BNode<T> *p)
{
	int c = 0;
	Queue<BNode<T>*> S;
	BNode<T> *t;
	if (p == NULL) return 0;
	S.push(p);
	while (!S.empty())
	{
		c++;
		t = S.pop();
		if (t->left != NULL) S.push(t->left);
		if (t->right != NULL) S.push(t->right);
	}
	return c;
}

template<class T>
T total(BNode<T> *p) {
	if (p == NULL) return 0;
	return p->data + total(p->left) + total(p->right);
}

template<class T>
int height(BNode<T> *p) {
	if (p == NULL) return 0;
	return 1 + max(height(p->left), height(p->right));
}

template<class T>
T min(BNode<T> *p) {
	if (p->left == NULL) {
		if (p->right == NULL || min(p->right) >= p->data) return p->data;
		else return min(p->right);
	} else if (p->right == NULL) {
		if (min(p->left) >= p->data) return p->data;
		else return min(p->left);
	} else if (p->data <= min(p->left) && p->data <= min(p->right)) return p->data;
	else if (p->data >= min(p->left) && min(p->left) <= min(p->right)) return min(p->left);
	else return min(p->right);
}

int main()
{
	BNode<int> *tree1 = new BNode<int>(1,
		new BNode<int>(2,
			new BNode<int>(4),
			new BNode<int>(5)),
		new BNode<int>(3,
			new BNode<int>(6)));

	print(tree1);

	cout << "Number of nodes: " << count_depth(tree1) << endl; //посчитать число узлов дерева
	cout << "Number of nodes: " << count_depth2(tree1) << endl;
	cout << "Number of nodes: " << count_width(tree1) << endl;
	cout << "Total: " << total(tree1) << endl;
	cout << "Height: " << height(tree1) << endl;
	cout << "Min: " << min(tree1) << endl;

	//Задания:
	//1) Реализовать стек для нерекурсивного обхода в глубину  
	//2) Реализовать очередь для нерекурсивного обхода в глубину
	//3) Написать функции:
	//total, возвращающую сумму всех данных в узлах дерева.
	//height, возвращающую высоту дерева.
	//min, возвращающую минимальное значение данных в узлах дерева

	return 0;
}
