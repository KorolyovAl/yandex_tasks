#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
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

// Реализуйте для класса Rational операторы << и >>
ostream& operator<< (ostream& output, const Rational& r) {
	Rational temp;
	temp.num_1 = r.num;
	temp.den_1 = r.den;
	int nod = temp.NOD(temp.num_1, temp.den_1);
	temp.num_1 /= nod;
	temp.den_1 /= nod;
	CheckingTheSign(temp);
	output << temp.num_1 << "/" << temp.den_1;
	return output;
}

bool CheckStream(istream& input) {
	string line;
	input.seekg(0);
	getline(input, line);
	for (const auto& x : line) {
		if (isdigit(x) || x == '/' || x == ' ' || x == '-' || x == '+') continue;
		else {
			return false;
		}
	}
	return true;
}

istream& operator>> (istream& input, Rational& r) {
	bool is_good;
	int place = 0;
	place = input.tellg();
	is_good = CheckStream(input);
	input.seekg(place);
	if (is_good == true) {
		int num = 0, denom = 1;
		input >> num;
		if (input.peek() == ' ') {
			input.ignore(1);
		}
		else if (input.peek() != '/' || input.fail()) {
			return input;
		}
		if (input.peek() == '/') {
			input.ignore(1);
		}
		else return input;
		if (!input || input.eof()) {
			return input;
		}
		input >> denom;
		Rational temp(num,denom);
		CheckingTheSign (temp);
		r = temp;
	}
	return input;
}

int main() {

/*        istringstream input("");
        Rational r1, r2, r3, r4, r5, r6;
        input >> r1 >> r2 >> r3 >> r4 >> r5 >> r6;
        cout << r1 << endl
        	<< r2 << endl
			<< r3 << endl
			<< r4 << endl
			<< r5 << endl
			<< r6 << endl;
*/
	Rational r;
	string a;
	cin >> a;
	cout << a;
	cin >> r;
	cout << r;

    return 0;
}
