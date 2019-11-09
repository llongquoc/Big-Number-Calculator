#ifndef QINT_H
#define QINT_H

#include "Header.h"
#include <map>
#include <math.h>
#include <algorithm>
#define Kbit 128


class QInt
{
private:
	int64_t data[2];

	// Create data from string
	void readBinary(string&);
	void readDecimal(string&);
	void readHexa(string&);


public:
	// Constructor
	QInt();

	// Input data: base, string
	void Scan(int, const string&);

	// Print data
	void Print();

	// Conversion
	string ToBin() const;
	string ToDec() const;
	string ToHex() const;

	// Operations
	QInt operator +(const QInt&);
	QInt operator -(const QInt&);
	QInt operator *(const QInt&);
	QInt operator /(const QInt&);

	// Comparision
	bool operator >(const QInt&);
	bool operator ==(const QInt&);
	bool operator !=(const QInt&);
	bool operator <(const QInt&);
	bool operator >=(const QInt&);
	bool operator <=(const QInt&);

	// Assignment
	QInt& operator =(const QInt&);

	// Bitwise operations
	QInt operator ~();
	QInt operator &(const QInt&);
	QInt operator |(const QInt&);
	QInt operator ^(const QInt&);

	// Shift and Rotate bit
	QInt operator >>(const QInt& p);
	QInt operator <<(const QInt& p);
	QInt rol(const QInt& p);
	QInt ror(const QInt& p);

	// Destructor
	~QInt();
};


// Helper functions

 // DECIMAL string manipulation
string div2(const string&);
string multi2(const string&);
void plus1(string&);
string subtract(const string&, const string&);

 // BINARY string manipulation
string sumBin(const string&, const string&);
string subtractBin(const string&, const string&);
void rightShBin(string&, int const&);
void leftShBin(string&, int const&);



#endif QINT_H
