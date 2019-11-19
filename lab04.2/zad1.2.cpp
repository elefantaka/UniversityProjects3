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

class Bazowe_Cechy {
public:
	static const bool _jest_liczba = false;
	static const bool _nalezy_do_przedzialu = false;
	static const bool _jest_liczba_calkowita = false;
	static const int _dolna_granica_przedzialu = 0;
	static const int _gorna_granica_przedzialu = 0;
	static const int iloscCyfrPoPrzecinku = 1;
};

template<typename T>
class Cechy : public Bazowe_Cechy {
public:
	static const double dolna_granica_przedzialu() { return 0; };
	static const double gorna_granica_przedzialu() { return 0; };
};

template<typename T>
class CechyLiczby : public Cechy<T> {
public:
	static const bool czyJestPierwsza = false;
};

class temperatura_wody {
	double t;
public:
	temperatura_wody(double temp = 50) : t(temp) {};
	double operator()() { return t; };
	temperatura_wody& operator=(double temp) { t = temp; return *this; };
	friend ostream& operator<<(ostream& os, temperatura_wody temp);
};



template<>
class Cechy<temperatura_wody> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const int iloscCyfrPoPrzecinku = 5;
	static const double dolna_granica_przedzialu() { return 0; };
	static const double gorna_granica_przedzialu() { return 100; };
};

ostream& operator<<(ostream& os, temperatura_wody temp) {
	os.precision(Cechy<temperatura_wody>::iloscCyfrPoPrzecinku);
	os << "Temperatura wody to " << fixed << temp() << "stopni" << endl;
	return os;
}

class kostka_do_gry {
	int n;
public:
	kostka_do_gry(int num = 1) : n(num) {};
	int operator()() { return n; };
	kostka_do_gry& operator=(int num) { n = num; return *this; };
	friend ostream& operator<<(ostream& os, kostka_do_gry kos);
};

ostream& operator<<(ostream& os, kostka_do_gry kos) {
	os << "Ilosc oczek na kostce do gry to " << kos() << endl;
	return os;
}

template<>
class Cechy<kostka_do_gry> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const int _dolna_granica_przedzialu = 1;
	static const int _gorna_granica_przedzialu = 6;
};

//moj kod:

//Minuta dnia

class MinutaDnia {
	int minuta;
public:
	MinutaDnia(int nowaMinuta = 0) : minuta(nowaMinuta) {};
	int operator()() { return minuta; };
	MinutaDnia& operator=(int nowaMinuta) { minuta = nowaMinuta; return *this; };
	friend ostream& operator<<(ostream& os, MinutaDnia min);
};

ostream& operator<<(ostream& os, MinutaDnia min) {
	os << "Jest " << min() << " minuta" <<  endl;
	return os;
}

template<>
class Cechy<MinutaDnia> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const int _dolna_granica_przedzialu = 0; 
	static const int _gorna_granica_przedzialu = 1439;
};

//Liczba sekund

class AktualnaGodzina {
	int godzina;
public:
	AktualnaGodzina(int nowaGodzina = 1) : godzina(nowaGodzina) {};
	double operator()() { return godzina*0.8+(godzina-1)*1.2; };
	AktualnaGodzina& operator=(int nowaGodzina) { godzina = nowaGodzina; return *this; };
	friend ostream& operator<<(ostream& os, AktualnaGodzina ak);
};

ostream& operator<<(ostream& os, AktualnaGodzina ak) {
	os << "Aktualna godzina wybija sie " << ak() << " sekund" << endl;
	return os;
}



template<>
class Cechy<AktualnaGodzina> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const int _dolna_granica_przedzialu = 1;
	static const int _gorna_granica_przedzialu = 12;
};

//Ilosc piwa

class IloscPiwa {
	int ilosc;
public:
	IloscPiwa(int nowaIlosc = 1) : ilosc(nowaIlosc) {};
	int operator()() { return ilosc*568; };
	IloscPiwa& operator=(int nowaIlosc) { ilosc = nowaIlosc; return *this; };
	friend ostream& operator<<(ostream& os, IloscPiwa il);
};

ostream& operator<<(ostream& os, IloscPiwa il) {
	os << "Ilosc piwa to " << il() << " ml" << endl;
	return os;
}

template<>
class Cechy<IloscPiwa> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const int _dolna_granica_przedzialu = 1;
	static const int _gorna_granica_przedzialu = 1000; 
};

//Liczba pierwsza

class LiczbaPierwsza {
	int liczba;
public:
	LiczbaPierwsza(int nowaLiczba = 2) : liczba(nowaLiczba) {};
	int operator()() { return liczba; };
	LiczbaPierwsza& operator=(int nowaLiczba) { liczba = nowaLiczba; return *this; };
	friend ostream& operator<<(ostream& os, LiczbaPierwsza li);
};

ostream& operator<<(ostream& os, LiczbaPierwsza li) {
	os << "Liczba pierwsza to " << li() << endl;
	return os;
}

template<>
class CechyLiczby<LiczbaPierwsza> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = false;
	static const bool _jest_liczba_calkowita = true;
	static const bool czyJestPierwsza = true;
	static const int _dolna_granica_przedzialu = 2;
};

//czy liczba jest pierwsza

bool czyPierwsza(int x) {
	if (x < 2) {
		return false;
	}
	for (int i = 2; (i*i) < x; i++) {
		if (x%i == 0) {
			return false;
		}
	}
	return true;
}

//koniec mojego kodu

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


template<typename T, int rozmiar, class _Cechy = Cechy<T>>
class SzablonStosu {
	T stos[rozmiar];
	int top;
public:
	int zajetosc() { return top; };
	SzablonStosu() : top(0) {}
	void push(const T& i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		stos[top++] = i;
	}
	void push(int i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());

		// walidacja warto�ci przekazanej do zapisu
		if (Cechy<T>::_jest_liczba && Cechy<T>::_jest_liczba_calkowita) {
			if (Cechy<T>::_nalezy_do_przedzialu) {
				if ((Cechy<T>::_dolna_granica_przedzialu <= i) && (i <= Cechy<T>::_gorna_granica_przedzialu)) {

					if (CechyLiczby<T>::czyJestPierwsza) {
						if (czyPierwsza(i)) {
							stos[top++] = i;
						}
						else {
							cout << "Liczba nie spelnila warunku: nie jest pierwsza" << endl;
						}
					}

					else {
						stos[top++] = i;
					}
				}
				else
					cout << "Liczba nie spelnila przedzialu" << endl;
			}
			else
				stos[top++] = i;
		}
		else {
			cout << "Liczba nie zostala dodana, gdyz nie spelnia cech" << endl;
		}
	}
	void push(double i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());

		// walidacja warto�ci przekazanej do zapisu
		if (Cechy<T>::_jest_liczba && !Cechy<T>::_jest_liczba_calkowita) {
			if (Cechy<T>::_nalezy_do_przedzialu) {
				if ((Cechy<T>::dolna_granica_przedzialu() <= i) && (i <= Cechy<T>::gorna_granica_przedzialu()))
					stos[top++] = i;
				else
					cout << "Liczba nie spelnila przedzialu" << endl;
			}
			else
				stos[top++] = i;
		}
	}
	T pop() {
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());

		return stos[--top];
	}

	void drukujKontener() {
		cout << "Kontener: ";
		for (int i = 0; i < top; i++) {
			cout << stos[i] << ", ";
		}
		cout << endl;
	}

};

template<int rozmiar>
void wypelnijKontener(SzablonStosu<AktualnaGodzina, rozmiar>& K) {
	K.push(AktualnaGodzina());
	K.push(AktualnaGodzina(4));
	K.push(13);
}

template<int rozmiar>
void wypelnijKontener(SzablonStosu<LiczbaPierwsza, rozmiar>& K) {
	K.push(LiczbaPierwsza());
	K.push(4);
	K.push(LiczbaPierwsza(13));
}

template<int rozmiar>
void wypelnijKontener(SzablonStosu<IloscPiwa, rozmiar>& K) {
	K.push(IloscPiwa());
	K.push(4);
}

template<int rozmiar>
void wypelnijKontener(SzablonStosu<MinutaDnia, rozmiar>& K) {
	K.push(MinutaDnia());
	K.push(4);
}

int main() {
	SzablonStosu<string, 5> K1;
	SzablonStosu<temperatura_wody, 10> K2;
	SzablonStosu<kostka_do_gry, 10> K3;
	SzablonStosu<MinutaDnia, 10> K4;
	SzablonStosu<AktualnaGodzina, 10> K5;
	SzablonStosu<IloscPiwa, 10> K6;
	SzablonStosu<LiczbaPierwsza, 10> K7;

	wypelnijKontener(K5);
	wypelnijKontener(K7);
	wypelnijKontener(K4);
	wypelnijKontener(K6);


	K5.drukujKontener();
	K7.drukujKontener();
	K4.drukujKontener();
	K6.drukujKontener();


	// zapelnianie stosu
	ifstream fi("qv-lab4.txt");

	if (fi.is_open()) {

		cout << "Plik zostal otwarty" << endl;

		string s;
		try {
			K1.push("Henryk");
			K1.push("Sienkiewicz");
			while (fi) {
				fi >> s;
				K1.push(s);
				fi.seekg(ios::beg);
				fi.clear();
				cout << '*';
			};
		}
		catch (Przepelnienie& e) {
			cout << "K1 gotowy: " << e.what() << endl;
		};
	}
	else {
		cout << "Brak pliku" << endl;
	}
	cout << "Danych na stosie K1: " << K1.zajetosc() << endl;

	K2.push(temperatura_wody());
	K2.push(temperatura_wody(36.66666));
	K2.push(40);
	K2.push(71.2);
	cout << "Danych na stosie K2: " << K2.zajetosc() << endl;

	K3.push(kostka_do_gry(3));
	K3.push(kostka_do_gry());
	K3.push(4);
	K3.push(6);
	K3.push(10);
	cout << "Danych na stosie K3: " << K3.zajetosc() << endl;

	// opr�nianie stosu
	try {
		while (true)
			K1.pop();
	}
	catch (BrakDanych& e) {
		cout << "K1 pusty: " << e.what() << endl;
	}
	try {
		while (true) {
			temperatura_wody elStosu = K2.pop();
			cout << "Usunieto ze stosu temperature wody " << elStosu << endl;
		}

	}
	catch (BrakDanych& e) {
		cout << "K2 pusty: " << e.what() << endl;
	}
	try {
		while (true) {
			kostka_do_gry el = K3.pop();
			cout << "Usunieto ze stosu kostke do gry: " << el << endl;
		}
	}
	catch (BrakDanych& e) {
		cout << "K3 pusty: " << e.what() << endl;
	}

	system("pause");
	return 0;
}