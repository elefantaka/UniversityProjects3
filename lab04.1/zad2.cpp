/* ========================================
ZPO: laboratorium 4
WMP.SNS UKSW, Warszawa
========================================
*/
#include<iostream>
#include<fstream>
#include<string>
#include<limits>
#include<exception>
#include <iomanip>

using namespace std;

class Przepelnienie : public exception {
	char opis[100];
public:
	Przepelnienie(const char* o) { strcpy_s(opis, o); }
	const char* what() const throw() { return opis; };
};
class BrakDanych : public exception {
	char opis[100];
public:
	BrakDanych(const char* o) { strcpy_s(opis, o); }
	const char* what() const throw() { return opis; };
};

class Stos2 {
protected:
	static const int rozmiar = 10;
	double stos[rozmiar];
	int top;
public:
	int zajetosc() { return top; };
	Stos2() : top(0) {}
	virtual void push(const double& i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		stos[top++] = i;
	}
	virtual double pop() {
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());
		return stos[--top];
	}
};

class StosDrukujacy : public Stos2 {
public:
	virtual double pop() {
		cout << "Ilosc elementow: " << zajetosc() << endl;
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());
		double elem =  stos[--top];
		cout << "Element zdjety ze stosu" << elem << endl;
		return elem;
	}
};

class StosSumujacy : public Stos2 {
private:
	double suma;
public:
	StosSumujacy() { suma = 0; };
	virtual void push(const double& i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		stos[top++] = i;
		suma += i;
		cout.precision(5);
		cout << "Po dodaniu elementu nowa suma na stosie wynosi: " << fixed << suma << endl;
	}
	virtual double pop() {
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());
		double element = stos[--top];
		suma -= element;
		cout.precision(5);
		cout << "Po zdjeciu elementu nowa suma na stosie wynosi: " << fixed << suma << endl;
		return element;
	}
};

int main() {
	StosDrukujacy S1;
	StosSumujacy S2;

	S1.push(2.5);
	S1.push(5.5);
	S1.push(8.9);

	S2.push(3.6);
	S2.push(1.2);
	S2.push(1);

	while (S1.zajetosc() > 0) {
		S1.pop();
	}

	while (S2.zajetosc() > 0) {
		S2.pop();
	}
}