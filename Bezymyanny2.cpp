#include <iostream>
#include <vector>

using namespace std;

struct NYPresent {		
	string name;
	double price;
	int weight;
	virtual int joy() = 0;
	virtual ~ NYPresent() {}
};

struct NYPig : NYPresent {
	int strength;
	vector<bool> lifes;
	int joy() {
		int count = 0;
		for (int i = 0; i < lifes.size(); ++i) if (lifes[i]) ++count;
		return weight*count;
	}
};

struct NYBird : NYPresent{
	int speed;
	int joy() {return weight*speed;}
};

struct NYBox {
	vector<NYPig> presentsP;
	vector<NYBird> presentsB;
	int joy() {
		int count = 0;
		for (int i = 0; i < presentsP.size(); ++i) count += presentsP[i].joy();
		for (int i = 0; i < presentsB.size(); ++i) count += presentsB[i].joy();
		return count;
	}
};

void operator>>(istream& is, NYPresent & p) {
	cout << "Enter name: ";
	is >> p.name;
	cout << "Enter price: ";
	is >> p.price;
	cout << "Enter weight: ";
	is >> p.weight;
}

void operator<<(ostream& os, NYPresent & p) {
	os << p.name;
	os << p.price;
	os << p.weight;
}

void operator>>(istream& is, NYPig & p) {
	cout << "Enter name: ";
	is >> p.name;
	cout << "Enter price: ";
	is >> p.price;
	cout << "Enter weight: ";
	is >> p.weight;
	cout << "Enter strength: ";
	is >> p.strength;
	p.lifes.resize(p.strength);
	cout << "Enter pig's lifes: ";
	for (int i = 0; i < p.lifes.size(); ++i) {
		int n;
		is >> n;
		p.lifes[i] = (bool)(n);
	}
}

void operator<<(ostream& os, NYPig & p) {
	os << p.name;
	os << p.price;
	os << p.weight;
	os << p.strength;
	for (int i = 0; i < p.lifes.size(); ++i) os << (int)(p.lifes[i]);
}

void operator>>(istream& is, NYBird & p) {
	cout << "Enter name: ";
	is >> p.name;
	cout << "Enter price: ";
	is >> p.price;
	cout << "Enter weight: ";
	is >> p.weight;
	cout << "Enter speed: ";
	is >> p.speed;
}

void operator<<(ostream& os, NYBird & p) {
	os << p.name;
	os << p.price;
	os << p.weight;
	os << p.speed;
}

void operator>>(istream& is, NYBox & p) {
	int n, m;
	cout << "Enter number of your Pig and Bird presents: ";
	is >> n >> m;
	p.presentsP.resize(n);
	p.presentsB.resize(m);
	cout << "Enter your presents: " << endl;
	for (int i = 0; i < n; ++i) is >> p.presentsP[i];
	for (int i = 0; i < m; ++i) is >> p.presentsB[i];
}

ostream& operator<<(ostream& os, NYBox & p) {
	os << p.presentsP.size() << p.presentsB.size() << endl;;
	for (int i = 0; i < p.presentsP.size(); ++i) {
		os << p.presentsP[i];
		cout << endl;
	}
	os << endl;
	for (int i = 0; i < p.presentsB.size(); ++i) {
		os << p.presentsB[i];
		cout << endl;
	}
}

int main() {
	NYBox box;
	cin >> box;
	cout << endl << box.joy() << endl;
	system("pause");
	return 0;
}
