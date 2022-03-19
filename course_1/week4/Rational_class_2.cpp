#include <iostream>
using namespace std;

class Rational {
public:
    Rational() {
        // Реализуйте конструктор по умолчанию
    	num = 0;
    	den = 1;
    }

    Rational(int numerator, int denominator) {
        // Реализуйте конструктор
    	num = numerator;
    	den = denominator;
    }
    int NOD (int num, int den) const {
		int a = num, b = den;
		int ng, vg;
		if (a >= b) {	// определение границ расчёта
			ng = b;
			vg = a;
		}
		else {
			ng = a;
			vg = b;
		}
		int o1, o2, o3;
		o1 = vg;
		o2 = ng;
		o3 = vg % ng;
		while (o3 != 0) {
			o1 = o2;
			o2 = o3;
			o3 = o1 % o2;
		}
		return o2;
    }
    int Numerator() const {
        // Реализуйте этот метод
    	int chisl;
    	if (num != 0) {
    		chisl = num / NOD(num, den);
    	}
    	else chisl = 0;
    	if ((num > 0 && den < 0) || (num < 0 && den > 0)) {
    		if ((num < 0 || den < 0) && chisl > 0) chisl *= -1;
    	}
    	return chisl;
    }

    int Denominator() const {
    	// Реализуйте этот метод
    	int znam;
    	if (num != 0) {
    		znam = den / NOD(num, den);
    	}
    	else znam = 1;
    	if ((num > 0 && den < 0) || (num < 0 && den > 0)) {
    		if ((num < 0 || den < 0) && znam < 0) znam *= -1;
    	}
    	return znam;
    }

    Rational BCD (Rational first, Rational second) {
    	Rational temp;

    	return temp;
    }
    bool operator == (const Rational& other) {
    	double first = (this->num / this->den);
    	double second = (other.num / other.den);
    	return first == second;
    }

    Rational operator + (const Rational& other) {
    	Rational temp;
    	int first_one, first_two;
    	int second_one;
    	first_one = this -> num * other.den;
    	second_one = other.num * this -> den;
    	first_two = this -> den * other.den;

    	temp.num = first_one + second_one;
    	temp.den = first_two;

    	int nod = NOD(temp.num, temp.den);
    	temp.num /= nod;
    	temp.den /= nod;
    	return temp;
    }

    Rational operator - (const Rational& other) {
    	Rational temp;
       	int first_one, first_two;
        int second_one;
        first_one = this -> num * other.den;
        second_one = other.num * this -> den;
        first_two = this -> den * other.den;

        temp.num = first_one - second_one;
        temp.den = first_two;

    	int nod = NOD(temp.num, temp.den);
    	temp.num /= nod;
    	temp.den /= nod;
    	return temp;
    }
private:
    // Добавьте поля
    int num;
    int den;
};

// Реализуйте для класса Rational операторы ==, + и -

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}

