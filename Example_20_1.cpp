#include <stdio.h>
#include <tchar.h>
#include <iostream>

using namespace std;


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
int dell(BNode<T> *r)
{
	if (r == NULL) return 0;
	delete r->left;
	r->left = NULL;
	return 1;
}

template<class T>
int vnumber(BNode<T> *r)
{
	int c = 0;
	if (r == NULL) return c;
	if (r->left->left != NULL) ++c;
	if (r->left->right != NULL) ++c;
	if (r->right->left != NULL) ++c;
	if (r->right->right != NULL) ++c;
	return c;
}

template<class T>
BNode<T>* newRoot(BNode<T> * old_r, BNode<T> * new_r) {
	new_r->left = old_r;
	return new_r;
}

template<class T>
void leftTurn(BNode<T> *r) {
	if (r != NULL) {
		BNode<T> *tmp = r->right;
	    r->right = r->left;
	    r->left = tmp;
	    leftTurn(r->right);
	    leftTurn(r->left);
	}
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

	cout << "Number of sons: "<< count1(tree1) << endl; //посчитать число сыновей корня
	cout << "Number of vnukov: "<< vnumber(tree1) << endl;
	
	BNode<int> * tree2 = new BNode<int>(10);
	tree1 = newRoot(tree1, tree2);
	
	print(tree1);
	
	cout << "\n##########################\n";
	
	leftTurn(tree1);
	print(tree1);
	
	cout << "\n##########################\n";

	dell(tree1); 	
	print(tree1); //удаляет левого сына


	//Задание:
	//1) Написать функцию, принимающую в качестве параметра дерево и возвращающую число внуков корня (если
	//дерево пустое или у корня нет внуков, вернуть 0).
	//2) Написать функцию, вставляющую в дерево новый корень (старый корень становится правым сыном нового, а
	//левого сына у нового корня не будет).Данные нового узла передаются в качестве параметра.
	//3) Написать функцию, осуществляющую левый поворот в корне.

	return 0;
}
