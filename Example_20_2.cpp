#include <stdio.h>
#include <tchar.h>
#include <iostream>

using namespace std;


template<class T>
struct ANode
{
	T data;
	ANode<T> *down, *right;
	ANode(T dd, ANode<T> *d = NULL, ANode<T> *r = NULL) :
		data(dd), down(d), right(r) {}
};

template<class T>
void print(ANode<T> *r, int offset = 0)
{
	if (r == NULL) return;
	for (int i = 0; i<offset; i++)
		cout << " ";
	cout << r->data << endl;
	print(r->down, offset + 3);
	print(r->right, offset);
}

template<class T>
int count2(ANode<T> *r)
{
	int c = 0;
	if (r == NULL) return c;
	r = r->down;
	while (r != NULL)
	{
		c++;
		r = r->right;
	}
	return c;
}

template<class T>
ANode<T> * first(ANode<T> * r, T d1, T d2) {
	if (r == NULL) return NULL;
	r = r->down;
	while(r != NULL) {
		if (r->data == d1) {
			ANode<T> * s = r->down;
			while (s != NULL) {
				if (s->data == d2) return r;
				s = s->right;
			}
		}
		r = r->right;
	}
	return NULL;
}

template<class T>
void newSon(ANode<T> * r, T d) {
	ANode<T> * new_son = new ANode<T>(d);
	new_son->right = r->down;
	r->down = new_son;
}

template<class T>
void del(ANode<T> * r) {
	if (r != NULL && r->down != NULL) {
		ANode<T> * tmp = r->down;
	    r->down = tmp->right;
	    ANode<T> * v = r->down->down;
	    if (v == NULL) r->down->down = tmp->down;
	    else {
	    	while(v->right != NULL) {
	    		v = v->right;
			}
			v->right = tmp->down;
		}
	}
}

int main()
{
	ANode<int> *tree2 = new ANode<int>(1,
		new ANode<int>(2,
			new ANode<int>(5,
				NULL,
				new ANode<int>(6,
					NULL,
					new ANode<int>(7))),
			new ANode<int>(3,
				new ANode<int>(8),
				new ANode<int>(4,
					new ANode<int>(9,
						NULL,
						new ANode<int>(10))))));

	print(tree2);

	cout << "Number: " << count2(tree2) << endl; //посчитать число сыновей
	
	cout << "\n##########################\n";
	
	print(first(tree2, 2, 6));
	
	cout << "\n##########################\n";
	
	del(tree2);
	print(tree2);
	
	cout << "\n##########################\n";
	
	newSon(tree2, 25);
	print(tree2);
	

	//Задание:
	//1) Написать функцию, возвращающую указатель на первого сына корня с данными d1, у которого есть сын с
	//данными d2(d1 и d2 — параметры функции).
	//2) Написать процедуру, вставляющую в дерево первого сына корня с данными, переданными в качестве параметра
	//3) Написать процедуру, удаляющую первого сына корня (его сыновья, если такие были, становятся сыновьями
	//корня перед бывшим вторым сыном корня).


	return 0;
}
