#include "numbers.dat"
#include <iostream>
using namespace std;

#define MAX 100000

int isPrimeNumber(int n)
{
	if (n < 2) return 0;
	if (n == 2) return 1; // 2 - простое
	if (n % 2 == 0) return 0; // четное -> не простое
	int d = 3; // начальный делитель
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
		int start = std::atoi(argv[i]);
		if ((start < 0) || (start > MAX))
			return -1;
		int finish = std::atoi(argv[i + 1]);
		if ((finish < 0) || (finish > MAX))
			return -1;
		int count = 0;
		for (int j = 0 ; j < Size; j++) {
			if (Data[j] < start)
				continue;
			if (Data[j] > finish)
				break;
			if (isPrimeNumber(Data[j]))
				count++;
		}
		std::cout << count << endl;
	}
	return 0;
}
