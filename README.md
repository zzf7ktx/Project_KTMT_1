# Project_KTMT_1
...

v: complete
x:

P1: INT
 
  class BigInt
  
  {
  
  private:
  
	  int Seg[4] = { 0 };
  
  public:
  
	  int Scanf(int); // v
	  int Scanf(string); // v
	  void Printf(int); // v
	  void Printf(string, int); // v
	  
	  BigInt& operator+(const BigInt&); // v
	  BigInt& operator-(BigInt&); // v
	  BigInt& operator-(); // v
	  BigInt& operator*(const BigInt&); // v
	  BigInt& operator/(const BigInt&); // Cai cuoi
	  
	  bool operator==(const BigInt&); // v
	  bool operator<=(const BigInt&); // v
	  bool operator>=(const BigInt&); // v
	  bool operator<(const BigInt&); // v
	  bool operator>(const BigInt&); // v
	  BigInt& operator=(const BigInt&); // v

	  BigInt& operator&(const BigInt&); // v
	  BigInt& operator|(const BigInt&); // v
	  BigInt& operator<<(const int&); // v
	  BigInt& operator>>(const int&); // v
	  BigInt& operator^(const BigInt&); // v
	  BigInt& operator~(); // v

};
	
	DecToBin() // v
  	BinToDec() // v
  	BinToHex() // v
  	HexToBin() // v
P2: ...
