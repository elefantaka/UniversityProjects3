#define _CRT_SECURE_NO_WARNINGS

#include <cmath>
#include <ctime>
#include <numeric>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

//#define ILE 1000
const int ILE = 1000;

using namespace std;

void losujPtaki(multiset<int> &x) {
	for (int i = 0; i < ILE; i++) {
		x.insert(rand() % 10);
	}
}

vector<int> sumujPtaki(multiset<int> x) {
	vector<int> v;

	typedef multiset<int>::iterator X_it;

	X_it x_iter = x.begin();

	cout << "Rozpoczecie sumuj ptaki" << endl;
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

double obliczChiKwadrat(vector<int> x, vector<int> y) {
	double wynik = 0;

	vector<int>::iterator iterX, iterY;

	for (iterX = x.begin(), iterY = y.begin(); iterX != x.end(); iterX++, iterY++) {
		if ((*iterX + *iterY) != 0) {
			double element = (*iterX - *iterY)*(*iterX - *iterY) / (double)(*iterX + *iterY);
			wynik += element;
		}
		else {
			cout << "Dzielenie przez zero, ktore ignorujemy" << endl;
		}
	}

	return wynik;
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

void drukujVector(vector<int> x) {
	cout << "Wektor: " << endl;
	vector<int>::iterator x_it;

	x_it = x.begin();

	while (x_it != x.end()) {
		cout << *x_it << ", ";
		x_it++;
	}
	cout << endl;
}

int main() {
	cout << "Program... Autor..." << endl;

	srand(time(NULL));

	// bufor do zapisywania obserwacji
	multiset<int> r; 
	multiset<int> s;

	losujPtaki(r);
	losujPtaki(s);

	drukujMultiset(r);
	drukujMultiset(s);

	vector<int> vR;
	vector<int> vS;

	vR = sumujPtaki(r);
	drukujVector(vR);

	vS = sumujPtaki(s);
	drukujVector(vS);

	double wynik = obliczChiKwadrat(vS, vR);

	cout << "Wynik CHi kwadtrat: " << wynik << endl;

	cout << "Koniec programu." << endl;
}