#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>


using namespace std;

#ifndef zad2_h
#define zad2_h

struct Dane {
	int id;
	char nazwa[10];
	double temp;
	double pojemn;
};

//przeciazony operator strumienia '<<' do pisania

ostream &operator<<(ostream&os, const Dane &d) {
	os << "|" << setw(6) << setiosflags(ios::right) << d.id;
	os << "|" << setw(10) << setiosflags(ios::right) << d.nazwa;
	os << "|" << setw(7) << setiosflags(ios::right) << d.temp;
	os << "|" << setw(6) << setiosflags(ios::right) << d.pojemn;

	os << " |";

	return os;
}

struct Element {
	Dane d;
	Element *next;
};

class KolejkaFifo {
	Element *glowa;
public:
	//konstrukor
	KolejkaFifo(); //konstruktor
	void put(Dane noweDane); //dopisuja
	Dane get(); //zwraca dane
};

KolejkaFifo::KolejkaFifo() {
	glowa = NULL;
}

//dodawanie elemntu do kolejki

void KolejkaFifo::put(Dane noweDane) {
	Element *nowy = new Element;
	nowy->d = noweDane;
	nowy->next = NULL;
	if (glowa == NULL) {
		glowa = nowy;
	}
	else {
		Element *ostatni = glowa;
		//przechodzimy po liscie
		while (ostatni->next != NULL) {
			ostatni = ostatni->next;
		}
		ostatni->next = nowy;
	}
	cout << "Dodano do listy nowy element: " << nowy->d << endl;
}

//usuwanie elementu z kolejki

Dane KolejkaFifo::get() {
	if (glowa == NULL) {
		Dane puste;
		puste.id = 0;
		strcpy(puste.nazwa, "nazwa1");
		puste.pojemn = 0.0;
		puste.temp = 0.0;
		return puste;
	}
	Element *usuwany = glowa;
	glowa = glowa->next;
	Dane wynik = usuwany->d;
	delete usuwany;
	cout << "Usuwamy dane z kolejki FIFO: " << wynik << endl;
	return wynik;
}

template <typename T, int rozmiar>
class Tablica {
	T A[rozmiar];
public:
	T& operator[](int index);
};

template <typename T, int rozmiar>
T& Tablica<T, rozmiar>::operator[](int index)
{
	if (index >= rozmiar || index < 0)
		return A[0];
	else
		return A[index];
}

#endif