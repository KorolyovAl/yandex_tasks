#include <iostream>
#include <vector>
using namespace std;

class Rational {
public:
    int num_1;
    int den_1;
    Rational() {
        // Реализуйте конструктор по умолчанию
    	num = 0;
    	den = 1;
    }

    Rational(int numerator, int denominator) {
        // Реализуйте конструктор
    	num = numerator;
    	den = denominator;
    	num_1 = numerator;
    	den_1 = denominator;
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

private:
    // Добавьте поля
    int num;
    int den;
};

vector <Rational> CommonDenominator (const Rational& first, const Rational& second) {
	vector <Rational> temp(2);
	temp[0].num_1 = first.num_1 * second.den_1;
	temp[0].den_1 = first.den_1 * second.den_1;
	temp[1].num_1 = second.num_1 * first.den_1;
	temp[1].den_1 = first.den_1 * second.den_1;
	return temp;
}

// Реализуйте для класса Rational операторы ==, + и -
Rational operator / (const Rational& first, const Rational& second) {
	Rational temp;
    temp.num_1 = first.num_1 * second.den_1;
    temp.den_1 = first.den_1 * second.num_1;

	int nod = temp.NOD(temp.num_1, temp.den_1);
	temp.num_1 /= nod;
	temp.den_1 /= nod;
	return temp;
}

Rational operator * (const Rational& first, const Rational& second) {
	Rational temp;
    temp.num_1 = first.num_1 * second.num_1;
    temp.den_1 = first.den_1 * second.den_1;

	int nod = temp.NOD(temp.num_1, temp.den_1);
	temp.num_1 /= nod;
	temp.den_1 /= nod;
	return temp;
}

bool operator == (const Rational& first, const Rational& second) {
	vector <Rational> CommonTemp = CommonDenominator(first, second);
	return (CommonTemp[0].num_1 == CommonTemp[1].num_1) && (CommonTemp[0].den_1 == CommonTemp[1].den_1);
}
// Реализуйте для класса Rational операторы * и /

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
