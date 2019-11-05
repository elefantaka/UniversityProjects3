#define _CRT_SECURE_NO_WARNINGS

#include "zad1.h"

#include <iostream>
#include <string>
#include <time.h>
#include <math.h>

#define ILE 4

using namespace std;

double randdouble()
{
	return 10* (rand() / (double(RAND_MAX) + 1));
}

int main() {
	cout << "Program... Autor..." << endl << endl;

	srand(time(NULL));

	Konten<double> kontener1;
	Konten<double> kontener2;

	double temp; //zmienna pomocnicza do sumowania zawartosci kontenera

	for (int i = 0; i < ILE; i++) {
		kontener1.push(randdouble());
		kontener2.push(randdouble());
	}

	cout << "Zawartosc kontenera1: " << endl;
	Wypisz<Konten<double>::iterator>(kontener1.begin(), kontener1.end());
	cout << endl;

	cout << "Zawartosc kontenera2: " << endl;
	Wypisz<Konten<double>::iterator>(kontener2.begin(), kontener2.end());
	cout << endl;

	cout << "Roznicowanie (kontener1 - kontener2):" << endl;
	Roznicuj <Konten<double>::iterator>(kontener1.begin(), kontener1.end(), kontener2.begin());
	Wypisz<Konten<double>::iterator>(kontener1.begin(), kontener1.end());
	cout << endl;

	cout << "Podnoszenie do kwadratu kontener1:" << endl;
	DoKwadratu <Konten<double>::iterator>(kontener1.begin(), kontener1.end());
	Wypisz<Konten<double>::iterator>(kontener1.begin(), kontener1.end());
	cout << endl;

	cout << "Sumowanie kontener1:" << endl;
	Sumuj <Konten<double>::iterator, double>(kontener1.begin(), kontener1.end(), temp);
	cout << "Suma kontener1: " << temp << endl;
	cout << endl;

	cout << "Obliczanie pierwiastka:" << endl;
	cout << "Pierwiastek: " << sqrt(temp) << endl << endl;

	cout << "Koniec programu" << endl;
}