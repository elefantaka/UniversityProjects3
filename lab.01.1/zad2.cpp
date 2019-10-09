#define _CRT_SECURE_NO_WARNINGS

#include "zad2.h"

#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>

#define DLUGOSC 60
const int maksTab = 1;

using namespace std;

//funkcja, ktora zapisuje dane do pliku, int flaga - tryb dostepu

void raport(Tablica<Dane, maksTab> &tab, char nazwaPliku[DLUGOSC], int flaga) {
	ofstream plik(nazwaPliku, flaga);

	if (plik.bad()) {
		cout << "Blad pliku. Nie sporzadzono raportu." << endl;
		return;
	}

	//naglowek:

	time_t now = time(0);
	char *napis = ctime(&now);
	plik << napis;

	char *nazwaKomputera = getenv("COMPUTERNAME");
	cout << nazwaKomputera << endl;
	plik << nazwaKomputera << endl;

	//tresc

	plik << "+------+----------+-------+-------+" << endl;
	plik << "|  ID  |  nazwa   |  temp.| pojemn|" << endl;
	plik << "+------+----------+-------+-------+" << endl;

	//stopka

	double sumaTemp = 0;
	double sumaPojemn = 0;

	for (int i = 0; i < maksTab; i++) {
		plik << tab[i] << endl;
		sumaTemp += tab[i].temp;
		sumaPojemn += tab[i].pojemn;
	}

	plik << "+------+----------+-------+-------+" << endl;
	plik << "|000000|          |" << setw(7) << sumaTemp << "|" << setw(6) << sumaPojemn << " |" << endl;
	plik << "+------+----------+-------+-------+" << endl;

	plik.close();
}

int main() {
	cout << "Program... Autor..." << endl;

	KolejkaFifo kf;
	Dane d1;

	char nazwaPliku[DLUGOSC];


	d1.id = 1;
	strcpy(d1.nazwa, "nazwa1");
	d1.pojemn = 1.1;
	d1.temp = 1.1;

	Tablica<Dane, maksTab> tab;

	kf.put(d1);
	Dane z = kf.get();

	tab[0] = z;

	cout << "Podaj nazwe pliku fo zapisu" << endl;

	cin >> nazwaPliku;

	raport(tab, nazwaPliku, ios::out);

	cout << "Koniec programu" << endl;
}