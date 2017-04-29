#include <iostream>
#include <cmath>
using namespace std;
double avg(int array[], int len)
{
	double sum = 0.0;
	for (int i = 0; i < len; ++i)
	{
		sum += array[i];
	}
	return sum / len;
}
double sd(int array[], int len, double avg)
{
	double sd = 0.0;
	for (int i = 0; i < len; ++i)
		sd += pow(static_cast<double>(array[i]) - avg, 2);
	cout << "sum: " << sd << "\n";
	return sqrt(sd / len);
}
int main(int argc, char const *argv[])
{
	int num;
	cin >> num;
	int* array = new int[num];
	for (int i = 0; i < num; ++i)
	{
		cin >> array[i];
	}
	cout << "AVG: " << avg(array, num);
	cout << "SD: " << sd(array, num, avg(array, num));

	return 0;
}
