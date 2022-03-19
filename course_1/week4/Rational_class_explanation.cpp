#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>
using namespace std;

class Rational {
public:
    int num_1;
    int den_1;
    Rational() {
    	num = 0;
    	den = 1;
    	num_1 = 0;
    	den_1 = 1;
    }

    Rational(int numerator, int denominator) {
    	if (denominator == 0) throw invalid_argument("invalid_argument");
        // Реализуйте конструктор
    	num = numerator;
    	den = denominator;
    	num_1 = numerator;
    	den_1 = denominator;
    }
    int NOD (int num, int den) const {
		int a = num, b = den;
		if (num == 0) return b = 1;
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
    int num;
    int den;
};

// Вставьте сюда реализацию operator / для класса Rational
Rational operator / (const Rational& first, const Rational& second) {
	if (second.num_1 == 0) {
		throw domain_error("invalid_argument");
	}
	Rational temp;
    temp.num_1 = first.num_1 * second.den_1;
    temp.den_1 = first.den_1 * second.num_1;

	int nod = temp.NOD(temp.num_1, temp.den_1);
	temp.num_1 /= nod;
	temp.den_1 /= nod;
	return temp;
}

int main() {

    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (exception&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}

