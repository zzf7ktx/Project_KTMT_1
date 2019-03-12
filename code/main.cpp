#include <iostream>
#include <string>

#define MAX 128

using namespace std;

class BigInt
{
private:
	int Seg[4] = { 0 };
public:
	int Scanf(int);
	int Scanf(string);
	void Printf(int);
	void Printf(string, int);

	BigInt& operator+(const BigInt&);
	BigInt& operator-(const BigInt&);
	BigInt& operator*(const BigInt&);
	BigInt& operator/(const BigInt&);

	bool operator==(const BigInt&); //
	bool operator<=(const BigInt&); //
	bool operator>=(const BigInt&); //
	bool operator<(const BigInt&); //
	bool operator>(const BigInt&); //
	BigInt& operator=(const BigInt&); //

	BigInt& operator&(const BigInt&); //
	BigInt& operator|(const BigInt&); //
	BigInt& operator<<(const int&); //
	BigInt& operator>>(const int&); //
	BigInt& operator^(const BigInt&); //
	BigInt& operator~(); //

};

int BigInt::Scanf(int base)
{
	string temp;
	int i;
	getline(cin, temp);

	switch (base)
	{
	case 2:
		for (i = 0; i < temp.length() ; i++)
		{
			Seg[(MAX - 1 - i) / 32] = Seg[(MAX - 1 - i) / 32] | (temp[temp.length() - i - 1] - 48)*(1 << (i) % 32);
		}

		
	}

	// 11100
	// 000100
	// 000100
	return 1;
}
//0 0 0 0 0 0 0 0    0 0 0 0 0 0 0 0
void BigInt::Printf(int base)
{
	int i;
	int temp;
	switch (base)
	{
	case 2:
		for (i = 0; i < MAX; i++)
		{
			temp = (Seg[i / 32] >> ((MAX - 1 - i) % 32)) & 1;
			cout << temp;
		}
	}
}

BigInt& BigInt::operator&(const BigInt& B)
{
	BigInt temp;
	
	temp.Seg[0] = Seg[0] & B.Seg[0];
	temp.Seg[1] = Seg[1] & B.Seg[1];
	temp.Seg[2] = Seg[2] & B.Seg[2];
	temp.Seg[3] = Seg[3] & B.Seg[3];

	return temp;
}

BigInt& BigInt::operator|(const BigInt& B)
{
	BigInt temp;

	temp.Seg[0] = Seg[0] | B.Seg[0];
	temp.Seg[1] = Seg[1] | B.Seg[1];
	temp.Seg[2] = Seg[2] | B.Seg[2];
	temp.Seg[3] = Seg[3] | B.Seg[3];

	return temp;
}

BigInt& BigInt::operator^(const BigInt& B)
{
	BigInt temp;

	temp.Seg[0] = Seg[0] ^ B.Seg[0];
	temp.Seg[1] = Seg[1] ^ B.Seg[1];
	temp.Seg[2] = Seg[2] ^ B.Seg[2];
	temp.Seg[3] = Seg[3] ^ B.Seg[3];

	return temp;
}

BigInt& BigInt::operator~()
{
	BigInt temp;

	temp.Seg[0] = ~Seg[0];
	temp.Seg[1] = ~Seg[1];
	temp.Seg[2] = ~Seg[2];
	temp.Seg[3] = ~Seg[3];

	return temp;
}

BigInt& BigInt::operator=(const BigInt& B)
{
	Seg[0] = B.Seg[0];
	Seg[1] = B.Seg[1];
	Seg[2] = B.Seg[2];
	Seg[3] = B.Seg[3];

	return *this;
}

bool BigInt::operator<(const BigInt& B)
{
	if (Seg[0] < B.Seg[0]) return 1;
	if (Seg[1] < B.Seg[1]) return 1;
	if (Seg[2] < B.Seg[2]) return 1;
	if (Seg[3] < B.Seg[3]) return 1;
	return 0;
}

bool BigInt::operator>(const BigInt& B)
{
	if (Seg[0] > B.Seg[0]) return 1;
	if (Seg[1] > B.Seg[1]) return 1;
	if (Seg[2] > B.Seg[2]) return 1;
	if (Seg[3] > B.Seg[3]) return 1;
	return 0;
}

bool BigInt::operator==(const BigInt& B)
{
	if (Seg[0] == B.Seg[0]) return 1;
	if (Seg[1] == B.Seg[1]) return 1;
	if (Seg[2] == B.Seg[2]) return 1;
	if (Seg[3] == B.Seg[3]) return 1;
	return 0;
}

bool BigInt::operator<=(const BigInt& B)
{
	if (*this < B || *this == B) return 1;
	return 0;
}

bool BigInt::operator>=(const BigInt& B)
{
	if (*this > B || *this == B) return 1;
	return 0;
}

BigInt& BigInt::operator<<(const int& num)
{
	BigInt temp = *this;
	//temp.Seg[0] = Seg[0] << num;
	for (int i = 0; i < num; i++)
	{
		temp.Seg[0] = temp.Seg[0] << 1;
		temp.Seg[0] = temp.Seg[0] | (temp.Seg[1] >> 31);

		temp.Seg[1] = temp.Seg[1] << 1;
		temp.Seg[1] = temp.Seg[1] | (temp.Seg[2] >> 31);

		temp.Seg[2] = temp.Seg[2] << 1;
		temp.Seg[2] = temp.Seg[2] | (temp.Seg[3] >> 31);

		temp.Seg[3] = temp.Seg[3] << 1;
		
	}
	return temp;
}

BigInt& BigInt::operator>>(const int& num)
{
	BigInt temp = *this;
	//temp.Seg[0] = Seg[0] << num;
	for (int i = 0; i < num; i++)
	{
		temp.Seg[3] = temp.Seg[3] >> 1;
		temp.Seg[3] = temp.Seg[3] | (temp.Seg[2] & 1);

		temp.Seg[2] = temp.Seg[2] >> 1;
		temp.Seg[2] = temp.Seg[2] | (temp.Seg[1] & 1);

		temp.Seg[1] = temp.Seg[1] >> 1;
		temp.Seg[1] = temp.Seg[1] | (temp.Seg[0] & 1);

		temp.Seg[0] = temp.Seg[0] >> 1;

	}
	return temp;
}

int main()
{
	BigInt A;
	A.Scanf(2);
	BigInt B = A;
	A.Printf(2);
	cout << endl;
	B.Printf(2);
	if (A >= B) cout << "aa\n";
	else cout << "bb";
	BigInt C = B >> 1;
	C.Printf(2);

	while(1);
	
}