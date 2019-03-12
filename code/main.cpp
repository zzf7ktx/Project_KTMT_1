#include <iostream>
#include <string>

#define MAX 128

using namespace std;

string binToHex(string& A)
{
	string res;
	int i;
	int temp = 0;

	for (i = 0; i < A.length(); i++)
	{
		temp = temp | ((A[A.length() - 1 - i] - 48) << (i % 4));

		if ((i + 1) % 4 == 0 || i == A.length() - 1)
		{
			if (temp <= 9)
			{

				res = (char)(temp + 48) + res;
			}
			else
			{
				switch (temp)
				{
				case 10: res = 'A' + res; break;
				case 11: res = 'B' + res; break;
				case 12: res = 'C' + res; break;
				case 13: res = 'D' + res; break;
				case 14: res = 'E' + res; break;
				case 15: res = 'F' + res; break;
				}
			}

			temp = 0;
		}
	}

	return res;
}

string decPlusDec(string& A, string& B)
{
	int na = A.length() - 1;
	int nb = B.length() - 1;

	int temp;
	int sur = 0;

	string C;

	while (1)
	{
		if (na > -1 && nb > -1)
		{
			temp = A[na] + B[nb] - 48 - 48 + sur;
			sur = temp / 10;
			temp = temp % 10;
			C = (char)(temp + 48) + C;
		}
		if (na > -1 && nb <= -1)
		{
			temp = A[na] - 48 + sur;
			sur = temp / 10;
			temp = temp % 10;
			C = (char)(temp + 48) + C;
		}
		if (na <= -1 && nb > -1)
		{
			temp = B[nb] - 48 + sur;
			sur = temp / 10;
			temp = temp % 10;
			C = (char)(temp + 48) + C;
		}
		if (na <= -1 && nb <= -1)
		{
			if (sur > 0)
			{
				C = (char)(sur + 48) + C;
			}
			break;
		}

		na--;
		nb--;
	}

	return C;
}

string decMulTwo(string& A)
{
	string B = decPlusDec(A, A);

	return B;
}

string twoPowDec(int index)
{
	int i;
	string numberTwo = "2";
	string res = "1";

	for (i = 0; i < index; i++)
	{
		res = decMulTwo(res);
	}

	return res;
}

string binToDec(string& A)
{
	string res = "0";
	string mul = "0";
	int i;

	for (i = 0; i < A.length(); i++)
	{
		if (A[i] ^ 48)
		{
			mul = twoPowDec(A.length() - i - 1);
			res = decPlusDec(res, mul);
		}
	}

	return res;
}

string decDivTwo(string& A)
{
	string res;
	int sur = 0;
	int temp;

	if (A == "0" || A == "1")
	{
		res = "0";
	}

	for (int i = 0; i < A.length(); i++)
	{
		temp = (A[i] - 48) + 10 * sur;
		sur = temp % 2;

		if (temp / 2 > 0 || i > 0)
		{
			res = res + (char)(temp / 2 + 48);
		}
	}

	return res;
}

string binPlusOne(string& A)
{
	int sur = 1;
	int temp;
	string res = A;
	
	for (int i = 0; i < A.length() - 1; i++)
	{
		temp = res[res.length() - 1 - i] - 48;
		res[res.length() - 1 - i] = (sur != temp) + 48;
		sur = temp && sur;
	}

	if (sur == 1)
	{
		res = res + '0';
	}

	return res;
}

string decToBin(string& A)
{
	int neg = 0;
	int sur;
	string res;
	string temp = A;
	
	if (A[0] == '-')
	{
		neg = 1;
		temp.erase(0, 1);
	}

	while (temp != "0" && temp != "1")
	{
		res = (char)(((temp[temp.length() - 1] - 48) % 2) + 48) + res;
		temp = decDivTwo(temp);
	}

	res = temp + res;
	
	int nc = res.length();

	for (int i = 0; i < MAX - nc; i++)
	{
		res = '0' + res;
	}

	if (neg == 1)
	{
		for (int i = 0; i < res.length(); i++)
		{
			res[i] = (res[i] == 48) + 48;
		}

		res = binPlusOne(res);
	}

	return res;
}

string decToHex(string& A)
{
	string temp = decToBin(A);
	string res = binToHex(temp);
	
	return res;
}

string hexToBin(string& A)
{
	string res;

	for (int i = 0; i < A.length(); i++)
	{
		switch (A[i])
		{
		case '0': res += "0000"; break;
		case '1': res += "0001"; break;
		case '2': res += "0010"; break;
		case '3': res += "0011"; break;
		case '4': res += "0100"; break;
		case '5': res += "0101"; break;
		case '6': res += "0110"; break;
		case '7': res += "0111"; break;
		case '8': res += "1000"; break;
		case '9': res += "1001"; break;
		case 'A': res += "1010"; break;
		case 'B': res += "1011"; break;
		case 'C': res += "1100"; break;
		case 'D': res += "1101"; break;
		case 'E': res += "1110"; break;
		case 'F': res += "1111"; break;
		}
	}

	return res;
}

class BigInt
{
private:
	int Seg[4] = { 0 };
public:
	int Scanf(int); //
	int Scanf(string);
	void Printf(int); //
	void Printf(string, int);

	BigInt& operator+(const BigInt&); //
	BigInt& operator-(BigInt&); // 
	BigInt& operator-(); //
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
		break;
	case 10:
		temp = decToBin(temp);
		break;
	case 16:
		temp = hexToBin(temp);
		break;
	}

	for (i = 0; i < temp.length(); i++)
	{
		Seg[(MAX - 1 - i) / 32] = Seg[(MAX - 1 - i) / 32] | (temp[temp.length() - i - 1] - 48)*(1 << (i) % 32);
	}

	// 11100
	// 000100
	// 000100
	return 1;
}

void BigInt::Printf(int base)
{
	int i;
	int temp;
	string res;

	for (i = 0; i < MAX; i++)
	{
		temp = (Seg[i / 32] >> ((MAX - 1 - i) % 32)) & 1;
		res += (char)(temp + 48);
	}

	switch (base)
	{
	case 2:
		break;
	case 10:
		res = binToDec(res);
		break;
	case 16:
		res = binToHex(res);
		break;
	}

	cout << res;
}

BigInt& BigInt::operator&(const BigInt& B)
{
	BigInt* temp = new BigInt;
	
	temp->Seg[0] = Seg[0] & B.Seg[0];
	temp->Seg[1] = Seg[1] & B.Seg[1];
	temp->Seg[2] = Seg[2] & B.Seg[2];
	temp->Seg[3] = Seg[3] & B.Seg[3];

	return *temp;
}

BigInt& BigInt::operator|(const BigInt& B)
{
	BigInt* temp = new BigInt;

	temp->Seg[0] = Seg[0] | B.Seg[0];
	temp->Seg[1] = Seg[1] | B.Seg[1];
	temp->Seg[2] = Seg[2] | B.Seg[2];
	temp->Seg[3] = Seg[3] | B.Seg[3];

	return *temp;
}

BigInt& BigInt::operator^(const BigInt& B)
{
	BigInt* temp = new BigInt;

	temp->Seg[0] = Seg[0] ^ B.Seg[0];
	temp->Seg[1] = Seg[1] ^ B.Seg[1];
	temp->Seg[2] = Seg[2] ^ B.Seg[2];
	temp->Seg[3] = Seg[3] ^ B.Seg[3];

	return *temp;
}

BigInt& BigInt::operator~()
{
	BigInt* temp = new BigInt;

	temp->Seg[0] = ~Seg[0];
	temp->Seg[1] = ~Seg[1];
	temp->Seg[2] = ~Seg[2];
	temp->Seg[3] = ~Seg[3];

	return *temp;
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
	if (*this < B || *this == B)
	{
		return 1;
	}

	return 0;
}

bool BigInt::operator>=(const BigInt& B)
{
	if (*this > B || *this == B)
	{
		return 1;
	}

	return 0;
}

BigInt& BigInt::operator<<(const int& num)
{
	BigInt* temp = new BigInt;
	*temp = *this;
	
	for (int i = 0; i < num; i++)
	{
		temp->Seg[0] = temp->Seg[0] << 1;
		temp->Seg[0] = temp->Seg[0] | (temp->Seg[1] >> 31);

		temp->Seg[1] = temp->Seg[1] << 1;
		temp->Seg[1] = temp->Seg[1] | (temp->Seg[2] >> 31);

		temp->Seg[2] = temp->Seg[2] << 1;
		temp->Seg[2] = temp->Seg[2] | (temp->Seg[3] >> 31);

		temp->Seg[3] = temp->Seg[3] << 1;
		
	}

	return *temp;
}

BigInt& BigInt::operator>>(const int& num)
{
	BigInt* temp = new BigInt;
	*temp = *this;
	
	for (int i = 0; i < num; i++)
	{
		temp->Seg[3] = temp->Seg[3] >> 1;
		temp->Seg[3] = temp->Seg[3] | (temp->Seg[2] & 1);

		temp->Seg[2] = temp->Seg[2] >> 1;
		temp->Seg[2] = temp->Seg[2] | (temp->Seg[1] & 1);

		temp->Seg[1] = temp->Seg[1] >> 1;
		temp->Seg[1] = temp->Seg[1] | (temp->Seg[0] & 1);

		temp->Seg[0] = temp->Seg[0] >> 1;

	}

	return *temp;
}

BigInt& BigInt::operator+(const BigInt& B)
{
	int i;
	int index;
	int sur = 0;
	BigInt* C = new BigInt;

	for (i = 0; i < MAX; i++)
	{
		index = (MAX - i - 1) / 32;
		if (!(Seg[index] | B.Seg[index]))
		{
			C->Seg[index] += sur;
			break;
		}

		int l = (Seg[index] >> (i % 32)) & 1;
		int r = (B.Seg[index] >> (i % 32)) & 1;
		C->Seg[index] = C->Seg[index] | ((l ^ r ^ sur) << (i % 32));
		sur = (l & r) | (sur & l) | (sur & r);
	}

	return *C;
}

BigInt& BigInt::operator-()
{
	BigInt* C = new BigInt;
	BigInt numberOne;
	numberOne.Seg[3] = 1;

	*C = ~(*this) + numberOne;

	return *C;
}

BigInt& BigInt::operator-(BigInt& B)
{
	BigInt* C = new BigInt;
	BigInt numberOne;
	numberOne.Seg[3] = 1;
	
	*C = *this + (-B);

	return *C;
}

int main()
{
	BigInt* A = new BigInt;

	A->Scanf(10);
	A->Printf(16);

	cin.ignore();
	cin.get();

	return 0;
}