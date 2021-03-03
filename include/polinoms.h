#include "utlist.h"
#include "iostream"

class Polinom;

class Monom {
public:
	double coeff;
	int deg;
	Monom(double _coeff = 0, int _deg = -1) : coeff(_coeff), deg(_deg) {
		if (OverflowingDegree()) throw "Error: overflowing degree";
	}
	Monom(const Monom& mon) : coeff(mon.coeff), deg(mon.deg) {}
	bool OverflowingDegree();
	Monom operator+(Monom mon);
	Monom operator*(Monom mon);
	Polinom operator*(const Polinom& pol);
	bool operator== (const Monom& mon) const;
	bool operator!= (const Monom& mon) const;
};

class Polinom : public List<Monom> {
public:
	Polinom();
	Polinom(const Polinom& pol);
	Polinom operator+(const Polinom& pol);
	Polinom operator*(Polinom pol);
	bool operator==(const Polinom lst) const;
};

bool Monom::OverflowingDegree() {
	if (((deg / 100) >= 10) || (((deg / 10) % 10) >= 10) || ((deg % 10) >= 10)) return 1;
	else return 0;
}

Monom Monom::operator+( Monom mon) {
	if (deg != mon.deg) throw "Error: monomials have different degrees";
	else {
		Monom res(coeff + mon.coeff, deg);
		return res;
	}
}

Monom Monom::operator*( Monom mon) {
	Monom res(coeff*mon.coeff, deg + mon.deg);
	if (OverflowingDegree()) throw "Too great degree";
	return res;
}

Polinom Monom::operator*(const Polinom& pol) {
	Polinom res;
	Node<Monom>* current = nullptr;
	for (Polinom::Iterator it = pol.begin(); it != pol.end(); ++it) {
		current = res.Insert(*this * it->data, current);
	}
	return res;
}

bool Monom::operator==(const Monom& mon) const{
	if ((mon.coeff == coeff) && (mon.deg == deg)) return 1;
	else return 0;
}

bool Monom::operator!=(const Monom& mon) const{
	return !(*this == mon);
}

Polinom::Polinom() : List<Monom>() {
}
Polinom::Polinom(const Polinom& pol) : List<Monom>() {
}
Polinom Polinom::operator+(const Polinom& pol) {
	Polinom res;
	Polinom::Iterator it1 = begin();
	Polinom::Iterator it2 = pol.begin();
	Node<Monom>* curr = nullptr;
	while (it1 != end() && it2 != pol.end()) {
		if (it1->data.deg < it2->data.deg) {
			curr = res.Insert(it1->data, curr);
			++it1;
		}
		else if (it1->data.deg == it2->data.deg) {
			if ((it1->data + it2->data).coeff != 0) curr = res.Insert(it1->data + it2->data, curr);
			++it1;
			++it2;
		}
		else if (it1->data.deg > it2->data.deg) {
			curr = res.Insert(it2->data, curr);
			++it2;
		}
	}
	if (it1 == end()) {
		for (; it2 != pol.end(); ++it2)
			curr = res.Insert(it2->data, curr);
	}
	if (it2 == pol.end()) {
		for (; it1 != end(); ++it1)
			curr = res.Insert(it1->data, curr);
	}
	return res;
}

Polinom Polinom::operator*(Polinom pol) {
	Polinom res;
	for (Polinom::Iterator it = pol.begin(); it != pol.end(); ++it) {
		res = res + it->data * *this;
	}
	return res;
}

bool Polinom::operator==(const Polinom lst) const {
	Polinom::Iterator it1 = begin();
	Polinom::Iterator it2 = lst.begin();
	while (true) {
		if (it1 == end()) {
			if (it2 != end())
				return false;
			else return true;
		}
		if (it2 == end()) {
			if (it1 != end())
				return false;
			else return true;
		}
		if (!(it1->data == it2->data)) return false;
		++it1;
		++it2;
	}
}