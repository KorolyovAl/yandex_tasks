#include <iostream>
#include <map>
#include <set>
#include <vector>
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

    friend istream& operator>> (istream& input, Rational& r);
    friend ostream& operator<< (ostream& output, const Rational& r);
};

vector <Rational> CommonDenominator (const Rational& first, const Rational& second) {
	vector <Rational> temp(2);
	temp[0].num_1 = first.num_1 * second.den_1;
	temp[0].den_1 = first.den_1 * second.den_1;
	temp[1].num_1 = second.num_1 * first.den_1;
	temp[1].den_1 = first.den_1 * second.den_1;
	return temp;
}

void CheckingTheSign (Rational& temp) {
	if (temp.num_1 < 0 && temp.den_1 < 0) {
		temp.num_1 = abs(temp.num_1);
		temp.den_1 = abs(temp.den_1);
	} else if (temp.num_1 < 0 || temp.den_1 < 0) {
		temp.num_1 = -abs(temp.num_1);
		temp.den_1 = abs(temp.den_1);
	}
}

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

bool operator< (const Rational& first, const Rational& second) {
	vector <Rational> CommonTemp = CommonDenominator(first, second);
	if (CommonTemp[0].num_1 < CommonTemp[1].num_1) return true;
	else return false;
}
// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}

