#include "numbers.dat"
#include <iostream>
using namespace std;

int isprostoe(int n)
{
	int d;
	if (n < 2) return 0;
	if (n == 2) return 1; // 2 - простое
	if (n % 2 == 0) return 0; // четное -> не простое
	d = 3; // начальный делитель
	while (d * d <= n) {
		if (n % d == 0) return 0;
			d += 2; // следующий делитель
	}
	return 1; // делителей не найдено -> простое
}

int main(int argc, char* argv[])
{
	if ((! (argc % 2)) || (argc < 3))
		return -1;
	for (int i = 1; i < argc; i += 2) {
		int s = std::atoi(argv[i]);
		if ((s < 0) || (s > 100000))
			return -1;
		int f = std::atoi(argv[i + 1]);
		if ((f < 0) || (f > 100000))
			return -1;
		int count = 0;
		for (int j = 0 ; j < sizeof(Data); j++) {
			if (Data[j] < s)
				continue;
			if (Data[j] > f)
				break;
			if (isprostoe(Data[j]))
				count++;
		}
		std::cout << count << endl;
	}
	return 0;
}
