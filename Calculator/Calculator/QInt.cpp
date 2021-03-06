#include"stdafx.h"
#include "QInt.h"



// DECIMAL string manipulation
string div2(const string &dec)
{
	if (dec == "1") return "0";
	string ans = "";
	int x = 0, len = int(dec.size());
	for (int i = 0; i < len; ++i) {
		int k = (x * 10 + dec[i] - '0');
		if (k / 2 || i)
			ans += k / 2 + '0';
		x = k % 2;
	}
	return ans;
}
string multi2(const string &dec)
{
	string ans = "";
	int add = 0, len = int(dec.size());;
	for (int i = len - 1; i >= 0; --i) {
		int k = 2 * (dec[i] - '0') + add;
		add = k / 10;
		k %= 10;
		ans = char(k + '0') + ans;
		if (i == 0 && add)
			ans = char(add + '0') + ans;
	}
	return ans;
}
void plus1(string &dec)
{
	int add = 1, len = int(dec.size());
	for (int i = len - 1; i >= 0 && add; --i) {
		char c = dec[i] + add;
		if (c > '9') dec[i] = c % ('9' + 1) + '0';
		else dec[i] = c;
		add = (c - '0') / 10;
		if (i == 0 && add)
			dec = "1" + dec;
	}
}
string subtract(const string &dec1, const string &dec2) // dec1 - dec2, dec2 > dec1
{
	// Case: dec2 > dec1
	string tmp = dec2;
	int d = 0, i, j;
	for (j = int(tmp.size()) - 1, i = int(dec1.size()) - 1; j >= 0; --j, --i) {
		int c;
		if (i < 0) c = tmp[j] - '0' - d;
		else c = tmp[j] - dec1[i] - d;
		if (c < 0) c += 10, d = 1;
		else d = 0;
		tmp[j] = c + '0';
	}
	i = 0;
	while (i < tmp.length() && tmp[i] == '0') i++;
	if (i >= tmp.length()) return "0";
	return "-" + tmp.substr(i, int(tmp.length()) - i);
}


// BINARY string manipulation
string sumBin(const string& bin1, const string& bin2)
{
	string b1 = bin1, b2 = bin2;
	if (b1.size() < b2.size()) swap(b1, b2);
	int d = 0, i, j;
	for (i = int(b1.size()) - 1, j = int(b2.size()) - 1; i >= 0; --i, --j) {
		char c = b1[i] - '0' + d;
		if (j >= 0) c += b2[j] - '0';
		b1[i] = c % 2 + '0';
		d = c / 2;
		if (i == 0 && d) b1 = "1" + b1;
	}
	if (b1.length() > Kbit) b1 = b1.substr(1, Kbit);
	return b1;
}
string subtractBin(const string& bin1, const string& bin2)
{
	string b1 = bin1, b2 = bin2;
	while (b1.size() < b2.size()) b1 = "0" + b1;
	while (b1.size() > b2.size()) b2 = "0" + b2;
	int d = 0, i;
	for (i = int(b1.length()) - 1; i >= 0; --i) {
		char c = b1[i] - b2[i] - d;
		if (c < 0) c += 2, d = 1;
		else d = 0;
		b1[i] = c + '0';
	}
	if (d) while (b1.length() < Kbit) b1 = "1" + b1;
	return b1;
}
void rightShBin(string& bin, int const& p)
{
	char c = '0';
	if (bin.size() == Kbit && bin[0] == '1') c = '1';
	int len = int(bin.length());
	for (int i = 0; i < p; ++i)
		bin = c + bin;
	bin = bin.substr(0, len);
}
void leftShBin(string& bin, int const& p)
{
	char c = '0';
	int len = int(bin.length());
	for (int i = 0; i < p; ++i)
		bin += c;
	if (len + p > Kbit) bin = bin.substr(p, len);
}
void makePositiveBin(string &bin)
{
	int i;
	bin = subtractBin(bin, "1");
	for (i = 0; i < bin.length(); ++i) {
		if (bin[i] == '0') bin[i] = '1';
		else bin[i] = '0';
	}
	i = 0;
	while (i < bin.length() && bin[i] == '0') i++;
	if (i >= bin.length()) {
		bin = "0";
		return;
	}
	bin = bin.substr(i, bin.length() - i);
}
void makeNegativeBin(string &bin)
{
	for (size_t i = 0; i < bin.size(); ++i) {
		if (bin[i] == '0') bin[i] = '1';
		else bin[i] = '0';
	}
	while (bin.length() < Kbit) bin = "1" + bin;
	bin = sumBin(bin, "1");
}

// Constructor
QInt::QInt()
{
	data[0] = 0;
	data[1] = 0;
}


// Create data from string
void QInt::readBinary(string& bin)
{
	int count = 0;
	int64_t ch;
	for (int i = int(bin.size()) - 1; i >= 0; --i) {
		ch = bin[i] - '0';
		if (ch == 1) {
			if (count < 64) data[1] = data[1] | (ch << count);
			else data[0] = data[0] | (ch << (count - 64));
		}
		count++;
	}
}
void QInt::readDecimal(string& dec)
{
	string positive_n = dec;
	bool negative = false;
	if (dec[0] == '-') {
		positive_n = dec.substr(1, dec.length() - 1);
		negative = true;
	}
	string bin = "";
	char ch;
	int count = 0;
	while (positive_n != "0" && count < Kbit) {
		ch = (positive_n[positive_n.size() - 1] - '0') % 2 + '0';
		bin = ch + bin;
		positive_n = div2(positive_n);
	}
	if (negative) makeNegativeBin(bin);
	readBinary(bin);
}
void QInt::readHexa(string& hex)
{
	map<char, string> hb;
	hb['0'] = "0000"; hb['1'] = "0001"; hb['2'] = "0010"; hb['3'] = "0011";
	hb['4'] = "0100"; hb['5'] = "0101"; hb['6'] = "0110"; hb['7'] = "0111";
	hb['8'] = "1000"; hb['9'] = "1001"; hb['A'] = "1010"; hb['B'] = "1011";
	hb['C'] = "1100"; hb['D'] = "1101"; hb['E'] = "1110"; hb['F'] = "1111";
	string bin = "";
	for (size_t i = 0; i < hex.size(); ++i)
		bin += hb.at(hex[i]);
	readBinary(bin);
}


// Input data
void QInt::Scan(int base, const string &st) 
{
	data[0] = data[1] = 0;
	string s = st;
	if (base == 2) readBinary(s);
	else if (base == 10) readDecimal(s);
	else if (base == 16) readHexa(s);
}


// Conversion
string QInt::ToBin() const
{
	if (data[0] == 0 && data[1] == 0)
		return "0";
	string bin = "";
	int64_t tmp[2];
	tmp[0] = data[0];
	tmp[1] = data[1];

	// Note: For negative number, 'Right Shift' still keep the sign bit
	int count;
	char c;
	if (tmp[0] == 0) {
		if (tmp[1] >= 0) {
			while (tmp[1]) {
				c = (tmp[1] & 1) + '0';
				bin = c + bin;
				tmp[1] >>= 1;
			}
		}
		else {
			count = 64;
			while (count--) {
				c = (tmp[1] & 1) + '0';
				bin = c + bin;
				tmp[1] >>= 1;
			}
		}
	}
	else {
		count = 64;
		while (count--) {
			c = (tmp[1] & 1) + '0';
			bin = c + bin;
			tmp[1] >>= 1;
		}
		if (tmp[0] >= 0) {
			while (tmp[0]) {
				c = (tmp[0] & 1) + '0';
				bin = c + bin;
				tmp[0] >>= 1;
			}
		}
		else {
			count = 64;
			while (count--) {
				c = (tmp[0] & 1) + '0';
				bin = c + bin;
				tmp[0] >>= 1;
			}
		}
	}
	return bin;
}
string QInt::ToDec() const
{
	string dec = "0";
	for (int i = 62; i >= 0; --i) {
		dec = multi2(dec);
		int c = (data[0] >> i) & 1;
		if (c) plus1(dec);
	}
	for (int i = 63; i >= 0; --i) {
		dec = multi2(dec);
		int c = (data[1] >> i) & 1;
		if (c) plus1(dec);
	}
	if ((data[0] >> 63) & 1) {
		string p = "170141183460469231731687303715884105728"; // 2^127
		dec = subtract(dec, p);
	}
	return dec;
}
string QInt::ToHex() const
{
	if (data[0] == 0 && data[1] == 0)
		return "0";
	string H = "0123456789ABCDEF", ans = "";
	int64_t tmp[2];
	tmp[0] = data[0];
	tmp[1] = data[1];
	int count = 16, i;
	while (count--) {
		i = (tmp[1] & 1) + ((tmp[1] >> 1) & 1) * 2 + ((tmp[1] >> 2) & 1) * 4 + ((tmp[1] >> 3) & 1) * 8;
		ans = H[i] + ans;
		tmp[1] >>= 4;
	}
	count = 16;
	while (count--) {
		i = (tmp[0] & 1) + ((tmp[0] >> 1) & 1) * 2 + ((tmp[0] >> 2) & 1) * 4 + ((tmp[0] >> 3) & 1) * 8;
		ans = H[i] + ans;
		tmp[0] >>= 4;
	}
	i = 0;
	while (ans[i] == '0') i++;
	ans = ans.substr(i, ans.length() - i);
	return ans;
}



// Print data
void QInt::Print()
{
	cout << data[0] << " " << data[1] << '\n';
	cout << "BIN: " << ToBin() << '\n';
	cout << "DEC: " << ToDec() << '\n';
	cout << "HEX: " << ToHex() << '\n';
}


// Operations
QInt QInt::operator +(const QInt& other)
{
	string a = ToBin();
	string b = other.ToBin();
	a = sumBin(a, b);
	QInt res;
	res.Scan(2, a);
	return res;
}
QInt QInt::operator -(const QInt& other)
{
	string a = ToBin();
	string b = other.ToBin();
	a = subtractBin(a, b);
	QInt res;
	res.Scan(2, a);
	return res;
}
QInt QInt::operator *(const QInt& other)
{
	QInt ans;
	if ((other.data[0] == 0 && other.data[1] == 0) || (data[0] == 0 && data[1] == 0))
		return ans;
	string A = "", Q = other.ToBin(), M = ToBin();
	if (Q.size() < Kbit) Q = "0" + Q;
	if (M.size() < Kbit) M = "0" + M;
	int n = max(int(Q.length()), int(M.length())), count = n;
	while (Q.size() < n) Q = "0" + Q;
	while (M.size() < n) M = "0" + M;
	while (A.size() < n) A += "0";
	string res = A + Q + "0";
	int len = int(res.length());
	do {
		if (res[len - 2] != res[len - 1]) {
			A = res.substr(0, n);
			if (res[len - 2] == '1' && res[len - 1] == '0')
				A = subtractBin(A, M);
			else A = sumBin(A, M);
			A = A.substr(A.size() - n, n);
			for (int i = 0; i < n; ++i) res[i] = A[i];
		}	
		// shift right 1
		if (res[0] == '1') res = "1" + res;
		else res = "0" + res;
		res = res.substr(0, len);
		//
		count--;
	} while (count);
	len = min(2 * n, Kbit);
	res = res.substr(2 * n - len, len);
	ans.Scan(2, res);
	return ans;
}
QInt QInt::operator /(const QInt& other)
{ // Q div M = res
	QInt ans;
	if (other.data[0] == 0 && other.data[1] == 0) {
		cout << "Invalid Dividend!";
		return ans;
	}
	if (data[0] == 0 && data[1] == 0) return ans;
	string A = "", Q = ToBin(), M = other.ToBin();
	// Handle negative numbers
	if (data[0] < 0) makePositiveBin(Q);
	if (other.data[0] < 0) makePositiveBin(M);
	//
	if (Q.size() < Kbit) Q = "0" + Q;
	if (M.size() < Kbit) M = "0" + M;
	int n = max(int(Q.length()), int(M.length())), count = n;
	while (Q.size() < n) Q = "0" + Q;
	while (M.size() < n) M = "0" + M;
	while (A.size() < n) A += "0";
	string res = A + Q;
	int len = 2 * n;
	do {
		// shift left 1
		res += "0" ;
		res = res.substr(1, len);
		//
		A = res.substr(0, n);
		A = subtractBin(A, M);
		A = A.substr(A.size() - n, n);
		if (A[0] == '1') {
			res[len - 1] = '0';
			A = sumBin(A, M);
			A = A.substr(A.size() - n, n);
		}
		else res[len - 1] = '1';
		for (int i = 0; i < n; ++i) res[i] = A[i];
		count--;
	} while (count);
	res = res.substr(n, n);
	if ((data[0] < 0 && other.data[0] >= 0) || (data[0] >= 0 && other.data[0] < 0))
		makeNegativeBin(res);
	ans.Scan(2, res);
	return ans;
}


// Comparision
bool QInt::operator >(const QInt& other)
{
	if (data[0] == other.data[0]) {
		if (data[1] >= 0 && other.data[1] < 0) return 1;
		if ((data[1] < 0 && other.data[1] < 0) || (data[1] >= 0 && other.data[1] >= 0))
			return data[1] > other.data[1];
		return 0;
	}
	if (data[0] >= 0 && other.data[0] < 0) return 1;
	if ((data[0] < 0 && other.data[0] < 0) || (data[0] >= 0 && other.data[0] >= 0))
		return data[0] > other.data[0];
	return 0;
}
bool QInt::operator ==(const QInt& other)
{
	return (data[0] == other.data[0] && data[1] == other.data[1]);
}
bool QInt::operator !=(const QInt& other)
{
	return (data[0] != other.data[0] || data[1] != other.data[1]);
}
bool QInt::operator <(const QInt& other)
{
	if (*this == other || *this > other) return 0;
	return 1;
}
bool QInt::operator >=(const QInt& other)
{
	if (*this < other) return 0;
	return 1;
}
bool QInt::operator <=(const QInt& other)
{
	if (*this > other) return 0;
	return 1;
}


// Assignment
QInt& QInt::operator =(const QInt& other)
{
	data[0] = other.data[0];
	data[1] = other.data[1];
	return *this;
}


// Bitwise operator
QInt QInt::operator ~()
{
	QInt res = *this;
	res.data[0] = ~data[0];
	res.data[1] = ~data[1];
	return res;
}
QInt QInt::operator &(const QInt& other)
{
	QInt res = *this;
	res.data[0] = data[0] & other.data[0];
	res.data[1] = data[1] & other.data[1];
	return res;
}
QInt QInt::operator |(const QInt& other)
{
	QInt res = *this;
	res.data[0] = data[0] | other.data[0];
	res.data[1] = data[1] | other.data[1];
	return res;
}
QInt QInt::operator ^(const QInt& other)
{
	QInt res = *this;
	res.data[0] = data[0] ^ other.data[0];
	res.data[1] = data[1] ^ other.data[1];
	return res;
}

// Shift and Rotate bit
QInt QInt::operator >>(const QInt& other)
{
	string tmp = ToBin();
	int p = int(other.data[1] % 129);
	if (p < 0) leftShBin(tmp, 0-p);
	else rightShBin(tmp, p);
	QInt res;
	res.Scan(2, tmp);
	return res;
}
QInt QInt::operator <<(const QInt& other)
{
	string tmp = ToBin();
	int p = int(other.data[1] % 129);
	if (p < 0) rightShBin(tmp, 0-p);
	else leftShBin(tmp, p);
	QInt res;
	res.Scan(2, tmp);
	return res;
}
QInt QInt::rol(const QInt& other)
{
	string tmp = ToBin();
	int p = int(other.data[1] % 129);
	while (tmp.size() < Kbit) tmp = "0" + tmp;
	int i = p;
	while (i--) {
		tmp = tmp + tmp[0];
		tmp = tmp.substr(1, Kbit);
	}
	QInt res;
	res.Scan(2, tmp);
	return res;
}
QInt QInt::ror(const QInt& other)
{
	string tmp = ToBin();
	int p = int(other.data[1] % 129);
	while (tmp.size() < Kbit) tmp = "0" + tmp;
	int i = p;
	while (i--) {
		tmp = tmp[tmp.size() - 1] + tmp;
		tmp = tmp.substr(0, Kbit);
	}
	QInt res;
	res.Scan(2, tmp);
	return res;
}


// Destructor
QInt::~QInt()
{
}
