#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <numeric> 
#include <sstream> 
#include <math.h>

#define ILE 100

using namespace std;

class DystrybucjaNormalna {
private:
	double srednia;
	double odchylenie;
protected:
	
public:
	DystrybucjaNormalna(double srednia, double odchylenie);
	double operator()();
};

class DystrybucjaNormalna1:public DystrybucjaNormalna {
public:
	
	DystrybucjaNormalna1() :DystrybucjaNormalna(0, 10) { };
};

class DystrybucjaNormalna2 : public DystrybucjaNormalna {
public:
	DystrybucjaNormalna2() :DystrybucjaNormalna(10, 10) {};
};

DystrybucjaNormalna::DystrybucjaNormalna(double srednia, double odchylenie) {
	this->srednia = srednia;
	this->odchylenie = odchylenie;
}

double DystrybucjaNormalna::operator()() {
	static default_random_engine generator((unsigned int)time(NULL));
	normal_distribution<double> d(srednia, odchylenie);
	return d(generator);
}

template <class Dystrybucja, int N>
class PunktLosowy {
	vector<double> wspolrzedne;
public:
	PunktLosowy();
	void drukuj();
	void zeruj();
	void dziel(int n);
	PunktLosowy operator+(PunktLosowy p2);
	vector<double> getwspolrzedne() { return wspolrzedne; }
};

template <class Dystrybucja, int N>
void PunktLosowy<Dystrybucja, N>::zeruj() {
	vector<double> wspolrzedne2(N);
	generate(wspolrzedne2.begin(), wspolrzedne2.end(), [](){ return 0; });
	wspolrzedne = wspolrzedne2;
}

double myproduct(double x, double y) {
	return x + y;
}

vector<double> myaccumulator(vector<double> v, double liczba) {
	v.push_back(liczba);
	return v;
}

template <class Dystrybucja, int N>
PunktLosowy<Dystrybucja, N> PunktLosowy<Dystrybucja, N>::operator+(PunktLosowy<Dystrybucja, N> p2) {
	PunktLosowy<Dystrybucja, N> p3;
	//generate(p3.wspolrzedne.begin(), p3.wspolrzedne.end(), []() { return (wspolrzedne[i] + p2.wspolrzedne[i]); });
	vector<double> pusty;
	vector<double> v = inner_product(wspolrzedne.begin(), wspolrzedne.begin() + N, p2.wspolrzedne.begin(), pusty, myaccumulator, myproduct);
	p3.wspolrzedne = v;
	return p3;
}

void pisz(double liczba) {
	cout << liczba << ", ";
}

template <class Dystrybucja, int N>
void PunktLosowy<Dystrybucja, N>::drukuj() {
	cout << "(";
	for_each(wspolrzedne.begin(), wspolrzedne.end(), pisz);
	cout << ")";
}

template <class Dystrybucja, int N>
PunktLosowy<Dystrybucja, N>::PunktLosowy() {
	vector<double> wspolrzedne2(N);
	std::generate(wspolrzedne2.begin(), wspolrzedne2.end(), Dystrybucja());
	wspolrzedne = wspolrzedne2;
}

template <class Punkt, int Rozmiar>
class Chmura {
private:
	vector<Punkt> punkty;
public:
	Chmura();
	void drukuj();
	Punkt centroid();
};

template <class Punkt>
Punkt dodajDwaPunkty(Punkt p1, Punkt p2) {
	Punkt p3;
	p3 = p1 + p2;
	return p3;
}


class Dziel {
public:
	int Rozmiar2;
	Dziel(int n) { Rozmiar2 = n; }
	vector<double> v;
	void operator() (double d) { d = d / Rozmiar2; v.push_back(d); cout << d << endl; };
};

template <class Dystrybucja, int N>
void PunktLosowy<Dystrybucja, N>::dziel(int n) {
	//vector<double> wspolrzedne2(N);
	//generate(wspolrzedne2.begin(), wspolrzedne2.end(), []() { return 0; });
	Dziel d(n);
	d = for_each(wspolrzedne.begin(), wspolrzedne.end(), d);
	wspolrzedne = d.v;
}

template <class Punkt, int Rozmiar>
Punkt Chmura<Punkt, Rozmiar>::centroid() {
	Punkt zero;
	zero.zeruj();
	Punkt sum = accumulate(punkty.begin(), punkty.end(), zero, dodajDwaPunkty<Punkt>);
	sum.dziel(Rozmiar);
	return sum;
}

template <class Punkt, int Rozmiar>
Chmura<Punkt, Rozmiar>::Chmura(){
	vector<Punkt> punkty2(Rozmiar);
	//std::generate(punkty2.begin(), punkty2.end(), Punkt);
	punkty = punkty2;
}

template <class Punkt>
void piszPunkt(Punkt p) {
	p.drukuj();
}

template <class Punkt, int Rozmiar>
void Chmura<Punkt, Rozmiar>::drukuj() {
	cout << "Chmura: " << endl;
	cout << "{";
	for_each(punkty.begin(), punkty.end(), piszPunkt<Punkt>);
	cout << "}";
	cout << endl;
}

double myaccumulator1(double x, double y) {
	return x + y;
}

double myproduct1(double x, double y) {
	return (x - y)*(x - y);
}

template<class Punkt1>
double odlegloscEuklidesowa(Punkt1 p1, Punkt1 p2) {
	double wynik = inner_product(p1.getwspolrzedne().begin(), p1.getwspolrzedne().end(), p2.getwspolrzedne().begin(), 0, myaccumulator1, myproduct1);
	wynik = sqrt(wynik);
	return wynik;
}

int main() {
	cout << "Program... Autor..." << endl;

	PunktLosowy<DystrybucjaNormalna1, 7> p1;
	PunktLosowy<DystrybucjaNormalna2, 2> p2;

	p1.drukuj();
	p2.drukuj();

	cout << endl;

	Chmura <PunktLosowy<DystrybucjaNormalna1, 5>, 3> chmura1;
	Chmura <PunktLosowy<DystrybucjaNormalna1, 5>, 10> chmura2;

	chmura1.drukuj();
	chmura2.drukuj();


	PunktLosowy<DystrybucjaNormalna1, 5> c1 = chmura1.centroid();
	PunktLosowy<DystrybucjaNormalna1, 5> c2 = chmura2.centroid();

	cout << "Centroidy: "<<endl;

	c1.drukuj();
	c2.drukuj();

	double wynik = odlegloscEuklidesowa<PunktLosowy<DystrybucjaNormalna1, 5>> (c1, c2);


	cout << "Odleglosc euklidesowa wynosi: " << wynik;
}

