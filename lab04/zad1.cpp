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

using namespace std;

class Bazowe_Cechy {
public:
	static const bool _jest_liczba = false;
	static const bool _nalezy_do_przedzialu = false;
	static const bool _jest_liczba_calkowita = false;
	static const int _dolna_granica_przedzialu = 0;
	static const int _gorna_granica_przedzialu = 0;
};

template<typename T>
class Cechy : public Bazowe_Cechy {
public:
	static const double dolna_granica_przedzialu() { return 0; };
	static const double gorna_granica_przedzialu() { return 0; };
};

class temperatura_wody {
	double t;
public:
	temperatura_wody(double temp = 50) : t(temp) {};
	double operator()() { return t; };
	temperatura_wody& operator=(double temp) { t = temp; return *this; };
};

template<>
class Cechy<temperatura_wody> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const double dolna_granica_przedzialu() { return 0; };
	static const double gorna_granica_przedzialu() { return 100; };
};

class kostka_do_gry {
	int n;
public:
	kostka_do_gry(int num = 1) : n(num) {};
	int operator()() { return n; };
	kostka_do_gry& operator=(int num) { n = num; return *this; };
};

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

//Srednica Opony

class SrednicaOpony {
	int f;
public:
	SrednicaOpony(double noweD = 10) : f(noweD) {};
	int operator()() { return f; };
	SrednicaOpony& operator=(double noweD) { f = noweD; return *this; };
};

template<>
class Cechy<SrednicaOpony> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const double _dolna_granica_przedzialu() { return 10; };
	static const double _gorna_granica_przedzialu() { return 24; };
};

//Czestotliwosc radiofonii

class Czestotliwosc {
	int f;
public:
	Czestotliwosc(double noweF = 87.5) : f(noweF) {};
	int operator()() { return f; };
	Czestotliwosc& operator=(double noweF) { f = noweF; return *this; };
};

template<>
class Cechy<Czestotliwosc> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const double _dolna_granica_przedzialu() { return 87.5; };
	static const double _gorna_granica_przedzialu() { return 108; };
};

//Rozmiar buta

class RozmiarButa {
	int rozmiar;
public:
	RozmiarButa(double nowyRozmiar = 20) : rozmiar(nowyRozmiar) {};
	int operator()() { return rozmiar; };
	RozmiarButa& operator=(double nowyRozmiar) { rozmiar = nowyRozmiar; return *this; };
};

template<>
class Cechy<RozmiarButa> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const double _dolna_granica_przedzialu() { return 20; };
	static const double _gorna_granica_przedzialu() { return 46; }
};

//Pojemnosc karty MicorSD

class LiczbaPierwsza {
	int liczba;
public:
	LiczbaPierwsza(double nowaPoj = 1) : liczba(nowaPoj) {};
	int operator()() { return liczba; };
	LiczbaPierwsza& operator=(double nowaPoj) { liczba = nowaPoj; return *this; };
};

template<>
class Cechy<LiczbaPierwsza> : public Bazowe_Cechy {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const int _dolna_granica_przedzialu = 1;
	static const int _gorna_granica_przedzialu = 128;
};

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
				if ((Cechy<T>::_dolna_granica_przedzialu <= i) && (i <= Cechy<T>::_gorna_granica_przedzialu))
					stos[top++] = i;
			}
			else
				stos[top++] = i;
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
};

int main() {
	SzablonStosu<string, 5> K1;
	SzablonStosu<temperatura_wody, 10> K2;
	SzablonStosu<kostka_do_gry, 10> K3;

	// zapelnianie stosu
	ifstream fi("qv-lab4.txt");
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
	cout << "Danych na stosie K1: " << K1.zajetosc() << endl;

	K2.push(temperatura_wody());
	K2.push(temperatura_wody(36.6));
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
		while (true)
			K2.pop();
	}
	catch (BrakDanych& e) {
		cout << "K2 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			K3.pop();
	}
	catch (BrakDanych& e) {
		cout << "K3 pusty: " << e.what() << endl;
	}

	system("pause");
	return 0;
}