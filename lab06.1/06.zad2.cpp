#define _CRT_SECURE_NO_WARNINGS

#include <cmath>
#include <ctime>
#include <numeric>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

const int ILE = 100;

using namespace std;

multiset<int> losujLiczby() {
	multiset<int> m;

	int wylosowanaLiczba;

	for (int i = 0; i < ILE; i++) {
		wylosowanaLiczba = rand() % 10;
		switch (wylosowanaLiczba) {
		case 0:
			m.insert(1);
			break;
		case 1:
			m.insert(2);
			break;
		case 2:
		case 3:
			m.insert(3);
			break;

		case 4:
		case 5:
			m.insert(4);
			break;
		case 6:
		case 7:
		case 8:
			m.insert(5);
			break;
		case 9:
			m.insert(6);
			break;
		}
	}

	return m;
}

vector<int> sumujLiczby(multiset<int> x) {
	vector<int> v;

	typedef multiset<int>::iterator X_it;

	X_it x_iter = x.begin();

	cout << "Rozpoczecie sumuj liczby na kostce." << endl;
	while (x_iter != x.end())
	{
		pair<X_it, X_it> para = x.equal_range(*x_iter);
		int count = distance(para.first, para.second);
		cout << *x_iter << " " << count << endl;
		x_iter = para.second; //zamiast iter++, przejscie iteratora do nastepnego elementu
		v.push_back(count);
	}
	cout << endl;

	return v;
}

vector<double> utworzDystrybuante(vector<int> v) {
	vector<double> vD;
	double suma = 0;

	vD.push_back(suma);

	for (int i = 0; i < v.size(); i++) {
		suma += v[i] / (double)ILE;
		vD.push_back(suma);
	}

	return vD;
}

void drukujMultiset(multiset<int> x) {
	cout << "Multiset: " << endl;

	typedef multiset<int>::iterator X_it;
	X_it x_iter = x.begin();

	while (x_iter != x.end()) {
		cout << *x_iter << ", ";
		x_iter++;
	}
	cout << endl;
}

template<class Typ>
void drukujVector(vector<Typ> x) {
	cout << "Wektor: " << endl;

	typedef vector<Typ>::iterator X_it;
	X_it x_it;

	x_it = x.begin();

	while (x_it != x.end()) {
		cout << *x_it << ", ";
		x_it++;
	}
	cout << endl;
}

int main() {
	srand(time(NULL));

	multiset<int> m;
	vector<int> v;
	vector<double> vD;

	m = losujLiczby();

	v = sumujLiczby(m);

	drukujMultiset(m);
	drukujVector(v);

	vD = utworzDystrybuante(v);

	drukujVector(vD);
}