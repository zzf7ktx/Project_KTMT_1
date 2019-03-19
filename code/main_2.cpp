#include <iostream>
#include <string>

#define MAX 128
#define E 15
#define BIAS 16383

using namespace std;

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
	int i;
	string res = "0";
	string mul = "0";
	string temp = A;


	for (i = 0; i < temp.length(); i++)
	{
		if (temp[i] ^ 48)
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
/*
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
	*/
	return res;
}

string decToBin_q(string& A)
{
	int i = 0;
	int neg = 0;
	int s;
	int p;
	string res;
	string tempFrac;
	string temp2;
	
	// Phan dau
	if (A[i] == '-')
	{
		i++;
		neg = 1;
		res += '1';
	}
	else
	{
		res += '0';
	}

	// So dac biet

	if (A == "-inf")
	{
		res += '1';
		for (i = 0; i < E; i++)
		{
			res += '1';
		}
		for (i = 0; i < MAX - E - 1; i++)
		{
			res += '0';
		}
		return res;
	}
	else if(A == "+inf" && A == "inf")
	{
		res += '0';
		for (i = 0; i < E; i++)
		{
			res += '1';
		}
		for (i = 0; i < MAX - E - 1; i++)
		{
			res += '0';
		}
		return res;
	}

	// Phan nguyen
	while (A[i] != '.' && i < A.length())
	{
		tempFrac += A[i];
		i++;
	}

	// Chuyen sang co so 2
	tempFrac = decToBin(tempFrac);
	i++;

	// Phan mu
	int lcur = 0;

	// Phan mu sau khi xac dinh
	lcur = tempFrac.length() - 1;

	// Phan thap phan
	while (i < A.length())
	{
		temp2 += A[i];
		i++;
	}
	
	if ((lcur == 0) && tempFrac[0] == '0')
	{
		int lcur2 = temp2.length();

		while (temp2.length() <= lcur2)
		{
			string oldtemp2 = temp2;
			temp2 = decMulTwo(temp2);
			if (temp2 == oldtemp2)
			{
				if (tempFrac == "0")
				{
					lcur -= BIAS;
				}
				break;
			}
			lcur--;
		}

		temp2.erase(0, 1);
	}

	lcur += BIAS; // Lech
	for (int j = 0; j < E; j++)
	{
		res = res + (char)(((lcur >> (E - j - 1)) & 1) + 48);
	}

	int lcur2 = temp2.length();

	if (lcur - BIAS >= 0)
	{
		res += tempFrac.substr(1, tempFrac.length());
	}

	for (int j = 0 + (lcur - BIAS < 0 ? 0 : lcur - BIAS); j < MAX - 1 - E; j++)
	{
		
		temp2 = decMulTwo(temp2);
		if (temp2.length() > lcur2)
		{
			res += '1';
			temp2.erase(0, 1);
		}
		else
		{
			res += '0';
		}
		
	}
	// 111.1
	return res;
}

string tenPowDec(int index)
{
	string res;
	res += '1';

	for (int i = 0; i < index; i++)
	{
		res += '0';
	}

	return res;
}

string decDivTwoPow(string&A, int index)
{
	string res = A;

	for (int i = 0; i < index; i++)
	{
		res = decDivTwo(res);
	}

	return res;
}

string binToDec_q(string& A)
{
	int i;
	int exp;
	string res;
	string s;
	string p;
	string temp;
	string temp2;
	string B;
	int checkE = 0;

	// Kiem tra so dac biet
	for (i = 1; i < 16; i++)
	{
		checkE += A[i] - 48;
	}

	for (i = 0; i < A.length(); i++)
	{
		if (A[i] != 0)
		{
			break;
		}
	}

	if (i != A.length() - 1)
	{
		if (checkE == 0)
		{
			return "0";
		}
		else if(checkE == 15)
		{
			if (A[0] == '0')
			{
				return "inf";
			}
			else
			{
				return "-inf";
			}
		}
	}
	else
	{
		if (checkE == 15)
		{
			return "nan";
		}
	}

	// Phan dau
	i = 0;
	if (A[0] == '1')
	{
		res += '-';
		i++;
	}

	// Phan mu
	exp = 0;
	for (int j = 0; j < E; j++)
	{
		exp = exp | (1 << j)*(A[E - j] - 48);
	}
	/*
	if (A[1] == '1')
	{
		exp = ~exp;
		for (int j = 0; j < E; j++)
		{
			exp = exp ^ (1 << j)*(A[E - j] == 48);
		}
	}
	else
	{
		
	}*/

	// BIAS
	exp -= BIAS;
	
	// Dua vao mang B so o dang nhi phan khong dau
	for (int j = E + 1; j < A.length(); j++)
	{
		B += A[j];
	}

	B = '1' + B;

	if (exp < 0)
	{
		for (int j = exp; j < -1; j++)
		{
			B = '0' + B;
		}
		B = "0." + B;
	}
	else
	{
		B.insert(B.begin() + exp + 1, '.');
	}

	// Lay phan duong
	while (B[i] != '.')
	{
		s += B[i];
		i++;
	}

	// Chuyen sang so thap phan
	res += binToDec(s);

	// Them cham
	res += '.';
	i++;
	
	// Lay phan thap phan
	while (i < B.length())
	{
		p += B[i];
		i++;
	}

	// Do dai phan thap phan
	int z = p.length();
	while (p[z] == '1')
	{
		z--;
	}
	
	// Chuyen sang so thap phan
	s = "0";
	temp = tenPowDec(z);
	temp2 = decDivTwoPow(temp, 1);
	
	for (i = 0; i < z; i++)
	{
		if (p[i] == '1')
		{
			
			for (int j = 0; j < temp2.length() - p.length(); j++)
			{
				temp2 = '0' + temp2;
			}
			s = decPlusDec(s, temp2);
		}
		temp2 = decDivTwoPow(temp2, 1);	
	}

	res += s;
	
	return res;
}

class Quad
{
private:
	unsigned int Seg[4] = { 0 };
public:
	void Scanf(int);
	void Scanf(int, string);
	void Printf(int);
	void Printf(int, string);
};

void Quad::Scanf(int base)
{
	int i;
	string input;
	getline(cin, input);

	if (base == 10)
	{
		input = decToBin_q(input);
	}

	for (i = 0; i < input.length(); i++)
	{
		Seg[(MAX - 1 - i) / 32] = Seg[(MAX - 1 - i) / 32] | (input[input.length() - i - 1] - 48)*(1 << (i) % 32);
	}
}

void Quad::Printf(int base)
{
	int i;
	int bit;
	string output;

	for (i = 0; i < MAX; i++)
	{
		bit = (Seg[i / 32] >> ((MAX - 1 - i) % 32)) & 1;
		output += (char)(bit + 48);
	}

	if (base == 10)
	{
		output = binToDec_q(output);
	}
	cout << output;
}

int main()
{
	Quad A;
	A.Scanf(10);
	A.Printf(2);
	cout << endl;
	A.Printf(10);

	cin.ignore();
	cin.get();
	return 0;
}
