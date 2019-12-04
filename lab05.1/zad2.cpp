#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;




class ListaSlow : public list<string> {
public:
	template <typename T> struct less : binary_function <T, T, bool> {
		bool operator() (const T& x, const T& y) const {
			return x.size() < y.size();
		};
	};
	template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	void parsuj(string & l) {
		stringstream linestream(l);
		string slowo;
		clear();
		while (linestream >> slowo)
			push_back(slowo);
	}

	ostream & pisz(ostream & os) {
		list<string>::iterator i = begin();
		while (i != end()) {
			cout << *i << " ";
			os << *(i++) << " ";
		}

		return os;
	}
};


template<typename T>
class Domieszka1 : public ListaSlow {
public:

	ostream & pisz(ostream & os) {
		sort(less<string>());
		os << size() << ": ";
		ListaSlow::pisz(os);
		cout << endl;
		return os;
	}
};

ostream &operator<<(ostream &os, Domieszka1<ListaSlow> mojaKolejka)
{
	while (!mojaKolejka.empty()) {
		string element = mojaKolejka.front();
		mojaKolejka.pop_front(); //usuwanie elementu z kolejki
		os << element << " ";
	}

	os << endl;

	return os;
}

class PorownanieKolejek {
public:
	bool operator() (const Domieszka1<ListaSlow>& x, const Domieszka1<ListaSlow>& y) const {
		return (x.size() > y.size());
	};
};

class Mikser : public list<Domieszka1<ListaSlow>> {
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

				Domieszka1<ListaSlow> q;

				int pozycja = linia.find(" ");

				while (pozycja != string::npos) {
					string wyraz = linia.substr(0, pozycja);
					linia = linia.substr(pozycja + 1);

					//cout << "Wyraz: <" << wyraz << ">" << endl;
					//cout << "Pozostala linia" << linia << endl;

					q.push_back(wyraz);

					pozycja = linia.find(" ");
				}

				if (linia.size() > 0 && linia[0] != ' ') {
					q.push_back(linia);
					//cout << "Wyraz: <" << linia << ">" << endl;
				}



				push_back(q);

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
Mikser::Mikser(string nazwaPliku) {
	open(nazwaPliku);
}

//destruktor
Mikser::~Mikser() {
	erase(begin(), end());
}


int main() {
	setlocale(LC_ALL, "");
	ifstream plik_in;
	//plik_in.open("mustafa.txt", ios_base::in);
	ofstream plik_out;
	//plik_out.open("out2.txt", ios_base::out);
	Mikser obj;


	string linia;

	obj.open("mistrz.txt");
	//while (getline(plik_in, linia)) {
	//	if (linia == "\0")
	//		continue;
		//obj.parsuj(linia);
		//obj.pisz(plik_out);
	//}

	obj.execute();
	obj.write("nowy1.txt");

	plik_in.close();
	plik_out.close();
	system("pause");
	return 0;
}