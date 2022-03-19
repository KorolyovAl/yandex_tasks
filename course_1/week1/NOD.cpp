#include <iostream>
using namespace std;

int main() {
	int a, b, ng, vg;
	cin >> a >> b;
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
	cout << o2;
	return 0;
}
