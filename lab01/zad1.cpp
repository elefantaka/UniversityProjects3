#define _CRT_SECURE_NO_WARNINGS

#include "zad1.h"

#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>

#define DLUGOSC 60
const int maksTab = 5;

using namespace std;

//funkcja do wypelniania tablicy rozsadnymi wartosciami

void inicjujElementy(Dane elementy[maksTab]) {
	elementy[0].id = 0;
	strcpy(elementy[0].nazwa, "Ala");
	elementy[0].pojemn= 0.0;
	elementy[0].temp = 0.0;

	elementy[1].id = 1;
	strcpy(elementy[1].nazwa, "Basia");
	elementy[1].pojemn = 1.1;
	elementy[1].temp = 1.1;

	elementy[2].id = 2;
	strcpy(elementy[2].nazwa, "Kamil");
	elementy[2].pojemn = 2.2;
	elementy[2].temp = 2.2;

	elementy[3].id = 3;
	strcpy(elementy[3].nazwa, "Eryk");
	elementy[3].pojemn = 3.3;
	elementy[3].temp = 3.3;

	elementy[4].id = 4;
	strcpy(elementy[4].nazwa, "Ewa");
	elementy[4].pojemn = 4.4;
	elementy[4].temp = 4.4;
}

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
	plik << "|000000|          |" << setw(7) << sumaTemp << "|" << setw(6) << sumaPojemn<< " |" << endl;
	plik << "+------+----------+-------+-------+" << endl;

	plik.close();
}

int main() {
	cout << "Program... Autor..." << endl;

	Tablica<Dane, maksTab> tab;

	Dane elementy[maksTab];

	char nazwaPliku[DLUGOSC];

	inicjujElementy(elementy);

	//przypisanie wartosci z tablicy elementy do tablicy, ktora zostala utworzona z szablonu

	for (int i = 0; i < maksTab; i++) {
		tab[i] = elementy[i];
		cout << elementy[i] << endl;
		cout << tab[i] << endl;
	}

	cout << "Podaj nazwe pliku fo zapisu" << endl;

	cin >> nazwaPliku;

	raport(tab, nazwaPliku, ios::out);

	cout << "Koniec programu" << endl;
}