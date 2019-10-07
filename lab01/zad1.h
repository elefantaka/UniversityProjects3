#include <cstdio>
#include <fstream>
#include <iomanip>


using namespace std;

#ifndef zad1_h
#define zad1_h

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