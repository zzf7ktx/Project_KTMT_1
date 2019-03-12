# Project_KTMT_1
...
P1: INT
  DecToBin() // v
  BinToDec() // v
  BinToHex() // v
  HexToBin() // v
  
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
    BigInt& operator-(); // Hoàn thành
	  BigInt& operator*(const BigInt&); // x
  	BigInt& operator/(const BigInt&); // x

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
    
P2: ...
