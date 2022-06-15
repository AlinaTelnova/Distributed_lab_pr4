#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cstring>
using namespace std;
int sundaram(int n)
{
	int* a = new int[n], i, j, k;
	memset(a, 0, sizeof(int) * n);
	for (i = 1; 3 * i + 1 < n; i++)
	{
		for (j = 1; (k = i + j + 2 * i * j) < n && j <= i; j++)
			a[k] = 1;
	}
	for (i = n - 1; i >= 1; i--)
		if (a[i] == 0)
		{
			return (2 * i + 1);
			break;
		}
	delete[] a;
}
int gcd(int a, int b)
{
	int c;
	while (b)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return abs(a);
}
int main()
{
	cout << "Please wait... Key generation procces." << endl << endl;
	srand((unsigned)time(NULL));
	int p = rand() % 100;
	int q = rand() % 100;
	int p_prime = sundaram(p);
	int q_prime = sundaram(q);
	unsigned int n = p_prime * q_prime;
	int e, e_prime = 0;
	while (e_prime != 1)
	{
		e= rand() % 100;
		e_prime = gcd(e, ((p_prime - 1) * (q_prime - 1)));
	}
	unsigned int d = 0, d_prime = 0;
	while (d_prime != 1)
	{
		d+= 1;
		d_prime = (e * d) % ((p_prime - 1) * (q_prime - 1));
	}
	cout << n << ',' << e << " - Your open key"<< endl;
	cout << n << ',' << d << " - Your private key"<< endl;
	const int MAX = 100;
	char* Text = new char[MAX];
	cout << "Please enter the Text. Use <Enter> button when done." << endl;
	cin.get(Text, MAX);
	unsigned int* CryptoText = new unsigned int[MAX];
	unsigned int* Tdecrypt = new unsigned int[MAX];
	int b = 301;
	int c;
	cout << endl << setw(5) << "Text" << setw(6) << "ASCII"<< setw(20) << "CryptoText/Block#" << setw(14) << "ASCIIdecrypt" << setw(14) << "Text decrypt" << endl<< " " << endl;
	for (int j = 0; j < MAX; j++)
	{
		c = 1;
		unsigned int i = 0;
		int ASCIIcode = (static_cast<int>(Text[j])) + b;
		while (i < e)
		{
			c = c * ASCIIcode;
			c = c % n;
			i++;
		}
		CryptoText[j] = c;
		b += 1;
	}
	b = 301;
	int m;
	for (int j = 0; j < MAX; j++)
	{
		m = 1;
		unsigned int i = 0;
		while (i < d)
		{
			m = m * CryptoText[j];
			m = m % n;
			i++;
		}
		m = m - b;
		Tdecrypt[j] = m;
		b += 1;
	}
	for (int j = 0; j < MAX; j++)
	{
		cout << setw(5) << Text[j] << setw(6) << static_cast<int>(Text[j]) <<
			setw(20) << CryptoText[j] << setw(14) << Tdecrypt[j] << setw(14) <<
			static_cast<char>(Tdecrypt[j]) << endl;
	}
	delete[] Text;
	delete[] CryptoText;
	delete[] Tdecrypt;
	return 0;
}
