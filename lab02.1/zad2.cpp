#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class MojWyjatek {
private:
	string komunikat;
public:
	MojWyjatek(string k) { komunikat = k; }
	string getKomunikat() { return komunikat; };
};

class NiepoprawnyOperator :MojWyjatek {
private:
	char niepoprawnyZnak;
public:
	NiepoprawnyOperator(char z):MojWyjatek("Niepoprawny operator: " + z) { 
		niepoprawnyZnak = z;
	}
};

void wykrywanie(string nazwaTaga) {
	cout << "Wykryto tag: " << nazwaTaga << endl;
}

void sprawdzMo(string linia) {
	string ciagDalszy = linia.substr(4);
	if (ciagDalszy.substr(1) != "</mo>") {
		string komunikat = "Brak taga </mo>";
		throw komunikat;
	}
	if (ciagDalszy[0] == '+') {
		cout << "Wykryto operator +" << endl;
	}
	else if (ciagDalszy[0] == '-') {
		cout << "Wykryto operator -" << endl;
	}
	else if (ciagDalszy[0] == '*') {
		cout << "Wykryto operator *" << endl;
	}
	else if (ciagDalszy[0] == '/') {
		cout << "Wykryto operator /" << endl;
	}
	else if (ciagDalszy[0] == '=') {
		cout << "Wykryto operator =" << endl;
	}
	else {
		//string komunikat = "Niepoprawny operator: " + ciagDalszy[0];
		NiepoprawnyOperator blad(ciagDalszy[0]);
		throw blad;
	}
}

void sprawdzMi(string linia) {
	if (linia.substr(0, 4) != "<mi>") {
		string komunikat = "Brak taga <mi>";
		throw komunikat;
	}
	string ciagDalszy = linia.substr(4);
	if ((ciagDalszy.size() <= 5) || (ciagDalszy.substr(ciagDalszy.size() - 5) != "</mi>")) {
		string komunikat = "Brak taga </mi>";
		throw komunikat;
	}
	if (ciagDalszy[0] >= 'a' && ciagDalszy[0] <= 'z') {
		cout << "Wykryto identyfikator zaczynaja sie od malej litery" << endl;
	}
	else if (ciagDalszy[0] >= 'A' && ciagDalszy[0] <= 'Z') {
		cout << "Wykryto identyfikator zaczynajacy sie od duzej litery" << endl;
	}
	else {
		string komunikat = "Niepoprawny identyfikator: " + ciagDalszy[0];
		throw komunikat;
	}
}

void sprawdzMn(string linia) {
	if (linia.substr(0, 4) != "<mn>") {
		string komunikat = "Brak taga <mn>";
		throw komunikat;
	}
	string ciagDalszy = linia.substr(4);
	if ((ciagDalszy.size() <= 5) || (ciagDalszy.substr(ciagDalszy.size() - 5) != "</mn>")) {
		string komunikat = "Brak taga </mn>";
		throw komunikat;
	}
	if (ciagDalszy[0] >= '0' && ciagDalszy[0] <= '9') {
		cout << "Wykryto number zaczynaja sie od cyfry" << endl;
	}
	else {
		string komunikat = "Niepoprawny number: " + ciagDalszy[0];
		throw komunikat;
	}
}

void sprawdzMsup(string linia1, string linia2, string linia3) {
	if (linia3 != "</msup>") {
		string komunikat = "Brak taga </msup>";
		throw komunikat;
	}
	sprawdzMi(linia1);
	sprawdzMn(linia2);
}

//sprawdzanie zawartosci tagow:

void sprawdzTagi(string linia, ifstream &plik) {
	if (linia.substr(0, 4) == "<mi>") {
		wykrywanie("<mi>");
		sprawdzMi(linia);
	}
	else if (linia.substr(0, 4) == "<mo>") {
		wykrywanie("<mo>");
		sprawdzMo(linia);
	}
	else if (linia.substr(0, 4) == "<mn>") {
		wykrywanie("<mn>");
		sprawdzMn(linia);
	}
	else if (linia == "<msup>") {
		wykrywanie("<msup>");
		string linia1;
		string linia2;
		string linia3;
		getline(plik, linia1);
		cout << linia1 << endl;

		getline(plik, linia2);
		cout << linia2 << endl;

		getline(plik, linia3);
		cout << linia3 << endl;


		sprawdzMsup(linia1, linia2, linia3);
	}
	else {
		string komunikat = "Niepoprawny tag: " + linia;
		throw komunikat;
	}
}

bool czyMathStart(string linia) {
	string poczatek = linia.substr(0, 5); //podnapis
	if (poczatek.compare("<math") == 0) {
		wykrywanie("<math");
		return true;
	}
	else {
		cout << "Brak wymaganego tagu <math" << endl;
		return false;
	}
}

bool czyMathEnd(string linia) {
	if (linia == "</math>") {
		wykrywanie("</math>");
		return true;
	}
	else {
		return false;
	}
}

void sprawdz(ifstream &plik) {
	string linia;

	getline(plik, linia);
	printf("1: %s\n", linia.c_str());
	if (!czyMathStart(linia)) {
		string komunikat = "Blad: Brak taga poczatkowego <math";
		throw komunikat;
	}
	else {
		cout << "Poprawna pierwsza linia pliku" << endl;
	}
	getline(plik, linia);
	cout << "2: " << linia << endl;

	while ((!plik.eof()) && (!czyMathEnd(linia))) {

		sprawdzTagi(linia, plik);
		getline(plik, linia);
		cout << linia << endl;

	}
	if (linia != "</math>") {
		string komunikat = "Brak taga koncowego </math>";
		throw komunikat;
	}
	cout << "Zakonczono czytanie wyrazenia" << endl;
}

int main() {
	cout << "Program... Autor..." << endl;

	ifstream plik("a.txt");
	if ((plik.is_open()) && (!plik.bad())) {

		cout << "Plik zostal otwarty" << endl;
		try {
			sprawdz(plik);
		}
		catch (string komunikat) {
			cout << "Wyjatek:" << komunikat << endl;
		}
		catch(MojWyjatek w){
			cout << "Moj wyjatek: " << w.getKomunikat() << endl;
		}

		plik.close();
	}
	else {
		cout << "Brak pliku" << endl;
	}

	cout << "Koniec programu." << endl;
}