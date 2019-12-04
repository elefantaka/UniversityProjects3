#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<queue>

using namespace std;

//obiekt fukcyjny do porownywania dlugosci slow
class Porownanie {
public:
	bool operator() (const string& x, const string& y) const {
		return (strlen(x.c_str()) > strlen(y.c_str()));
	};
};



//kolejka priorytetowa
typedef priority_queue<string, vector<string>, Porownanie> Kolejka;

class PorownanieKolejek {
public:
	bool operator() (const Kolejka& x, const Kolejka& y) const {
		return (x.size() > y.size());
	};
};

//przeciazony operator
ostream &operator<<(ostream &os, Kolejka mojaKolejka)
{
	while (!mojaKolejka.empty()) {
		string element = mojaKolejka.top();
		mojaKolejka.pop(); //usuwanie elementu z kolejki
		os << element << " ";
	}

	os << endl;

	return os;
}

class Mikser : public list<Kolejka> {
public:
	Mikser() {};
	Mikser(string nazwaPliku);
	~Mikser();
	void open(string nazwaPliku);
	void execute();
	void write(string nazwaPliku);
};

void Mikser::open(string nazwaPliku) {
	ifstream plik(nazwaPliku);

	if (plik.is_open()) {
		cout << "Plik zostal otwarty" << endl;

		string linia;
		while (getline(plik, linia)) {
			if (linia.size() > 0) {
				cout << "Linia: " << linia << endl;

				Kolejka q;

				int pozycja = linia.find(" ");

				while (pozycja != string::npos) {
					string wyraz = linia.substr(0, pozycja);
					linia = linia.substr(pozycja + 1);

					//cout << "Wyraz: <" << wyraz << ">" << endl;
					//cout << "Pozostala linia" << linia << endl;

					q.push(wyraz);

					pozycja = linia.find(" ");
				}

				if (linia.size() > 0 && linia[0] != ' ') {
					q.push(linia);
					//cout << "Wyraz: <" << linia << ">" << endl;
				}

				

				push_back(q);

				cout << q << endl;
				//cout << this << endl;
			}
		}
		
	}
	else {
		cout << "Blad otwarcia pliku" << endl;
	}

	plik.close();
}

void Mikser::execute() {
	sort(PorownanieKolejek());
}

void Mikser::write(string nazwaPliku) {
	ofstream plik(nazwaPliku);

	for (iterator i = begin(); i != end(); i++) {
		plik << (*i).size();
		plik << ": ";
		plik << (*i);
	}

	plik.close();
}

//kostruktor argumentowy
Mikser::Mikser(string nazwaPliku){
	open(nazwaPliku);
}

//destruktor
Mikser::~Mikser() {
	erase(begin(), end());
}

int main() {
	cout << "Program... Autor..." << endl;

	Mikser obiekt("mistrz.txt");

	obiekt.execute();
	obiekt.write("nowy1.txt");

	cout << "Koniec programu" << endl;
}