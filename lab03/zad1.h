#define _CRT_SECURE_NO_WARNINGS

#ifndef zad1_h
#define zad1_h

#include <cassert>
#include <iostream>

using namespace std;

template<typename T>
class Konten
{
	enum { ssize = 100 };
	T stack[ssize];
	int top;
public:
	Konten() : top(0) {}
	void push(T i) {
		assert(top < ssize);  stack[top++] = i;
	};
	T pop() {
		assert(top > 0);  return stack[--top];
	};
	int rozmiar() { return top; };

	class iterator {
		Konten& s;
		int index;
	public:
		iterator(Konten& is) : s(is), index(0) {};
		iterator(Konten& is, bool) : s(is), index(s.top) {};
		T operator++() { // Prefix
			assert(index < s.top);
			return s.stack[++index];
		};
		T operator++(int) { // Postfix
			assert(index < s.top);
			return s.stack[index++];
		};
		T& operator*() const { return s.stack[index]; };
		iterator& operator=(const iterator& rv) {
			s = rv.s;
			index = rv.index;
			return *this;
		}

		bool operator!=(const iterator& rv) const {
			return index != rv.index;
		}
	};
	iterator begin() { return iterator(*this); };
	iterator end() { return iterator(*this, true); };

	friend class iterator;
};

template<typename T>
void Roznicuj(T i1, T i2, T i3) {
	while (i1 != i2) {
		*i1 = *i1 - *i3;
		i1++;
		i3++;
	}
};

template<typename T>
void DoKwadratu(T i1, T i2) {
	while (i1 != i2) {
		*i1 = *i1*(*i1);
		i1++;
	}
};

template<typename T1, typename T2>
void Sumuj(T1 i1, T1 i2, T2& a) {
	while (i1 != i2) {
		a = a + *i1;
		i1++;
	}
};

template<typename T>
void Wypisz(T i1, T i2) {
	while (i1 != i2) {
		cout << *i1 << endl;
		i1++;
	}
};

#endif
