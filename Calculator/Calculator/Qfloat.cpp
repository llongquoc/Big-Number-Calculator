#include"stdafx.h"
#include "Qfloat.h"

Qfloat::Qfloat()
{
	a[0] = a[1] = a[2] = a[3] = 0;
}

Qfloat::~Qfloat()
{
}

bool Qfloat::is0()
{
	if (a[1] == 0 && a[2] == 0 && a[3] == 0 && (a[0] == 0 || a[0] == 1 << 31))
		return true;
	return false;
}

void Qfloat::onBit(int x)
{
	a[x / 32] = a[x / 32] | (1 << (31 - (x % 32)));
}

bool Qfloat::ss(string x, string y)
{
	while (x.size() < y.size())
		x = "0" + x;
	while (x.size() > y.size())
		y = "0" + y;
	return (x >= y);
}

string Qfloat::div2(string s, bool c)
{
	int nho = 0, tong;
	bool check = false;
	string res = "";

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '.') {
			res += ".";
			check = true;
			continue;
		}
		tong = nho * 10 + s[i] - 48;
		res += (char)48 + tong / 2;
		nho = tong % 2;
	}
	
	if (c && nho > 0) {
		if (check)
			res = res + "5";
		else
			res = res + ".5";
	}

	while (res.size() > 1 && res[0] == '0')
		res.erase(0, 1);
	
	int dem = 0;
	for (int i = 0; i < s.size(); i++)
		if (s[i] == '0' || s[i] == '.')
			dem++;
		else
			break;

	if (dem == s.size())
		res = "0";

	if (res[0] == '.')
		res = '0' + res;

	return res;
}

string Qfloat::multi2(string s)
{
	int nho = 0, tong;
	bool check = false;
	string res = "";

	for (int i = s.size() - 1; i >= 0; i--) {
		if (s[i] == '.') {
			res = "." + res;
			continue;
		}
		tong = nho + (s[i] - 48) * 2;
		res = char(48 + tong % 10) + res;
		nho = tong / 10;
	}

	if (nho > 0)
		res = char(nho + 48) + res;

	int dem = 0;
	for (int i = 0; i < s.size(); i++)
		if (s[i] == '0' || s[i] == '.')
			dem++;
		else
			break;

	if (dem == s.size())
		res = "0";

	if (res[0] == '.')
		res = '0' + res;

	return res;
}

string Qfloat::sum1(string s)
{
	string res = s;
	int i;
	for (i = res.size() - 1; i >= -1; i--)
		if (i == -1 || res[i] < '9')
			break;

	for (int j = i + 1; j < res.size(); j++)
		res[j] = '0';
	if (i == -1)
		res = "1" + res;
	else
		res[i] += 1;

	return res;
}

string Qfloat::sumb(string x, string y)
{
	while (x.size() < y.size())
		x = "0" + x;
	while (x.size() > y.size())
		y = "0" + y;

	int nho = 0, tong;
	string res = "";
	for (int i = x.size() - 1; i >= 0; i--) {
		tong = (x[i] == '1') + (y[i] == '1') + nho;
		res = char(48 + tong % 2) + res;
		nho = tong / 2;
	}

	if (nho > 0) 
		res = "1" + res;

	return res;
}

string Qfloat::subb(string x, string y)
{
	while (x.size() < y.size())
		x = "0" + x;
	while (x.size() > y.size())
		y = "0" + y;

	int nho = 0, tong;
	string res = "";
	for (int i = x.size() - 1; i >= 0; i--) {
		tong = (x[i] == '1') - (y[i] == '1') - nho;
		if (tong < 0) {
			tong += 2;
			nho = 1;
		}
		else
			nho = 0;
		res = char(48 + tong % 2) + res;
	}

	return res;
}

string Qfloat::mulb(string x, string y)
{
	string res = "";

	for (int i = y.size() - 1; i >= 0; i--) {
		if (y[i] == '1')
			res = sumb(res, x);
		x = x + "0";
	}

	return res;
}

string Qfloat::divb(string x, string y)
{
	string res = "", t = "";

	for (int i = 0; i < x.size(); i++) {
		t = t + x[i];
		if (ss(t, y)) {
			t = subb(t, y);
			while (t.size() > 0 && t[0] == '0')
				t.erase(0, 1);
			res = res + "1";
		}
		else
			res = res + "0";
	}

	res = res + ".";

	for (int i = 0; i < 120; i++) {
		t = t + "0";
		if (ss(t, y)) {
			t = subb(t, y);
			while (t.size() > 0 && t[0] == '0')
				t.erase(0, 1);
			res = res + "1";
		}
		else
			res = res + "0";
	}

	while (res.size() > 2 && res[0] == '0' && res[1] != '.')
		res.erase(0, 1);

	return res;
}

string Qfloat::round(string s, int x)					//lam tron 30 chu so thap phan
{
	int d = -1;
	for (int i = 0; i < s.size(); i++)
		if (s[i] == '.') {
			d = i;
			break;
		}

	if (d == -1 || s.size() - d < x + 2)
		return s;

	string res = s.substr(0, d + x + 1);
	
	int k = s[d + x + 1] - 48;

	bool check = false;

	while (k > 4) {
		if (res[res.size() - 1] == '.') {
			res.erase(res.size() - 1, 1);
			check = true;
			break;
		}

		if (res[res.size() - 1] == '9') 
			res.erase(res.size() - 1, 1);
		else {
			res[res.size() - 1]++;
			break;
		}
	}

	if (check) {
		if (res[0] == '-') {
			res.erase(0, 1);
			res = sum1(res);
			res = '-' + res;
		}
		else
			res = sum1(res);
	}

	return res;
}

void Qfloat::scanQfloat(string s)
{
	a[0] = a[1] = a[2] = a[3] = 0;

	string s1 = "", s2 = "";
	if (s == "")
		cin >> s;

	bool check = false;		//co phan thuc (co dau ')
	char dau;					//dau (+, -)
	if (s[0] == '+' || s[0] == '-') {
		dau = s[0];
		s.erase(0, 1);
	}
	else
		dau = '+';

	for (int i = 0; i < s.size(); i++)
		if (s[i] == '.') {
			check = true;
			s1 = s.substr(0, i);
			s2 = s.substr(i + 1, s.size() - i - 1);
			break;
		}

	if (!check) {
		s1 = s;
		s2 = "0";
	}
	while (s1.size() > 1 && s1[0] == '0')
		s1.erase(0, 1);
	while (s2.size() > 1 && s2[s2.size() - 1] == '0')
		s2.erase(s2.size() - 1, 1);

	if (s1 == "0" && s2 == "0") {
		a[0] = a[1] = a[2] = a[3] = 0;
		return;
	}

	string b = "", b1 = "", b2 = "";	//bieu dien nhi phan
	
	if (s1 == "0")
		b = "0";
	else
		while (s1 != "0") {
			b1 = char(48 + (s1[s1.size() - 1]) % 2) + b1;
			s1 = div2(s1, false);
		}

	s2 = "0." + s2;

	int sl = 1 << 14, i1 = 0, i2 = 0;

	while (i1 < sl && i2 < 200) {
		s2 = multi2(s2);
		b2 += char(48 + (s2[0] == '1'));
		if (i2 > 0 || s2[0] == '1')
			i2++;
		s2[0] = '0';
		if (s2 == "0")
			break;
		i1++;
	}

	int mu, k = (1 << 14) - 1;

	if (b1[0] == '1') {
		mu = b1.size() - 1 + k;
		b = b1 + b2;
		b.erase(0, 1);
	}
	else {
		b = b2;
		for (int i = 0; i < b2.size(); i++)
			if (b2[i] == '1') {
				mu = i;
				break;
			}
		if (-(mu + 1) > -k) {
			b.erase(0, mu + 1);
			mu = -mu - 1 + k;
		}
		else {
			b.erase(0, k - 1);
			mu = 0;
		}
	}

	if (dau == '-')
		onBit(0);

	for (int i = 1; i <= 15; i++) {
		if (((mu >> (15 - i)) & 1) == 1)
			onBit(i);
	}

	for (int i = 0; i < b.size(); i++) {
		if (b[i] == '1') 
			onBit(i + 16);
		if (i == 111)
			break;
	}
}

string Qfloat::printQfloat(int x)
{
	if (is0()) {
		return "0";
	}

	ui dau = (a[0] >> 31) & 1;
	int mu = (a[0] >> 16) & ((1 << 15) - 1);

	string b = "", b1 = "", b2 = "";

	if (mu != 0) {
		mu -= ((1 << 14) - 1);
		b1 = "1";
	}
	else {
		b1 = "0";
		mu = -(1 << 14) + 2;
	}

	for (int i = 17; i <= 32; i++)
		b2 += char(48 + ((a[0] >> (32 - i)) & 1));
	for (int i = 1; i < 4; i++)
		for (int j = 1; j <= 32; j++)
			b2 += char(48 + ((a[i] >> (32 - j)) & 1));

	if (b1 == "1") {
		b = b1 + b2;
		mu++;
	}
	else
		b = b2;

	for (int i = b.size() - 1; i >= 0; i--)
		if (b[i] == '1') {
			mu = mu - (i + 1);
			b.erase(i + 1, b.size() - (i + 1));
			break;
		}

	string res = "0";
	for (int i = 0; i < b.size(); i++) {
		res = multi2(res);
		if (b[i] == '1')
			res = sum1(res);
	}

	if (mu < 0) 
		for (int i = 0; i < abs(mu); i++) 
			res = div2(res);
	
	if (mu > 0)
		for (int i = 0; i < mu; i++) 
			res = multi2(res);

	if (res[0] == '.')
		res = '0' + res;

	if (a[0] >= 1 << 31)
		res = '-' + res;
	
	return round(res, x);
}

void Qfloat::binToDec(string bit)
{
	a[0] = a[1] = a[2] = a[3] = 0;
	for (int i = 0; i < min((int)bit.size(), 128); i++)
		if (bit[i] == '1')
			onBit(i);
}

string Qfloat::decToBin()
{
	string bit;
	for (int i = 0; i < 4; i++)
		for (int j = 31; j >= 0; j--)
			bit = bit + char(48 + ((a[i] >> j) & 1));
	return bit;
}

string Qfloat::operator + (Qfloat x)
{
	if (is0()) {
		return x.decToBin();
	}
	if (x.is0()) {
		return decToBin();
	}

	string res;

	string s1 = decToBin(), s2 = x.decToBin();

	char d1 = s1[0], d2 = s2[0];	
	int mu1 = 0, mu2 = 0, k = (1 << 14) - 1;
	for (int i = 1; i <= 15; i++) {
		if (s1[i] == '1')
			mu1 = mu1 | (1 << (15 - i));
		if (s2[i] == '1')
			mu2 = mu2 | (1 << (15 - i));
	}

	s1.erase(0, 16);
	s2.erase(0, 16);

	bool chuan = true;

	if (mu1 < mu2) {
		swap(mu1, mu2);
		swap(d1, d2);
		swap(s1, s2);
	}

	if (mu1 != 0) {
		s1 = '1' + s1;
		mu1 -= k;
	}
	else {
		s1 = '0' + s1;
		mu1 = -k + 1;
		chuan = false;
	}

	if (mu2 != 0) {
		s2 = '1' + s2;
		mu2 -= k;
	}
	else {
		s2 = '0' + s2;
		mu2 = -k + 1;
	}

	while (mu2 < mu1) {
		mu2++;
		s2 = "0" + s2;
		s2.erase(s2.size() - 1, 1);
	}

	string s;
	Qfloat r;

	if (d1 == d2) {
		s = sumb(s1, s2);
		if (s.size() > 113) {
			s.erase(s.size() - 1, 1);
			mu1++;
		}

		if (s[0] == '1' && !chuan)
			chuan = true;
		s.erase(0, 1);

		if (chuan)
			mu1 += k;
		else
			mu1 = 0;

		if (mu1 >= (1 << 15) - 1) {
			return ovl;
		}

	}
	else {
		if (s1 < s2) {
			swap(s1, s2);
			swap(d1, d2);
		}

		s = subb(s1, s2);

		if (s[0] == '0') {
			s.erase(0, 1);
			while (s.size() > 0 && s[0] == '0') {
				s.erase(0, 1);
				mu1--;
			}
			if (s == "") {
				return r.decToBin();
			}
			mu1--;
		}

		s.erase(0, 1);

		if (mu1 > -k + 1)
			mu1 += k;

		if (mu1 == -k + 1)
			mu1 = 0;

		if (mu1 < - k + 1) {
			s = "1" + s;
			mu1++;
			while (mu1 < - k + 1) {
				mu1++;
				s = s + "0";
			}
			mu1 = 0;
		}
	}

	string mu = "";
	for (int i = 0; i < 15; i++)
		mu = mu + char(48 + ((mu1 >> (14 - i)) & 1));

	res = d1 + mu + s;	

	if (res.size() > 128)
		res.erase(128, res.size() - 128);

	return res;
}

string Qfloat::operator - (Qfloat x)
{
	x.a[0] = x.a[0] ^ (1 << 31);
	return *this + x;
}

string Qfloat::operator * (Qfloat x)
{
	if (is0() || x.is0()) {
		return "0";
	}

	string res = "";

	string s, s1 = decToBin(), s2 = x.decToBin();

	char d1 = s1[0], d2 = s2[0];
	int mu1 = 0, mu2 = 0, k = (1 << 14) - 1;
	for (int i = 1; i <= 15; i++) {
		if (s1[i] == '1')
			mu1 = mu1 | (1 << (15 - i));
		if (s2[i] == '1')
			mu2 = mu2 | (1 << (15 - i));
	}

	s1.erase(0, 16);
	s2.erase(0, 16);

	if (mu1 != 0) {
		s1 = "1" + s1;
		mu1 -= k;
	}
	else {
		s1 = "0" + s1;
		mu1 = -k + 1;
	}

	if (mu2 != 0) {
		s2 = "1" + s2;
		mu2 -= k;
	}
	else {
		s2 = "0" + s2;
		mu2 = -k + 1;
	}

	mu1 += mu2;

	if (mu1 > k)
		return ovl;
	if (mu1 < -k + 1)
		return udl;

	s = mulb(s1, s2);

	if (s.size() == 113 * 2)
		mu1++;

	s.erase(0, 1);

	mu1 += k;

	string mu = "";
	for (int i = 0; i < 15; i++)
		mu = mu + char(48 + ((mu1 >> (14 - i)) & 1));

	if (d1 == d2)
		d1 = '0';
	else
		d1 = '1';

	res = d1 + mu + s;

	if (res.size() > 128)
		res.erase(128, res.size() - 128);

	return res;
}

string Qfloat::operator / (Qfloat x)
{
	if (x.is0()) {
		return inf;
	}

	if (is0()) {
		return "0";
	}

	string res = "";

	string s, s1 = decToBin(), s2 = x.decToBin();

	char d1 = s1[0], d2 = s2[0];
	int mu1 = 0, mu2 = 0, k = (1 << 14) - 1;
	for (int i = 1; i <= 15; i++) {
		if (s1[i] == '1')
			mu1 = mu1 | (1 << (15 - i));
		if (s2[i] == '1')
			mu2 = mu2 | (1 << (15 - i));
	}

	s1.erase(0, 16);
	s2.erase(0, 16);

	if (mu1 != 0) {
		s1 = "1" + s1;
		mu1 -= k;
	}
	else {
		s1 = "0" + s1;
		mu1 = -k + 1;
	}

	if (mu2 != 0) {
		s2 = "1" + s2;
		mu2 -= k;
	}
	else {
		s2 = "0" + s2;
		mu2 = -k + 1;
	}

	mu1 -= mu2;

	if (mu1 > k)
		return ovl;

	if (mu1 < -k + 1)
		return udl;

	s = divb(s1, s2);

	if (s[0] == '0' && s[1] == '.') {
		s.erase(0, 2);
		for (int i = 0; i < s.size(); i++)
			if (s[i] == '1') {
				mu1 = mu1 - i - 1;
				s.erase(0, i + 1);
				break;
			}
	}
	else 
		for (int i = 0; i < s.size(); i++) 
			if (s[i] == '.') {
				mu1 = mu1 + i - 1;
				s.erase(i, 1);
				s.erase(0, 1);
				break;
			}

	if (mu1 > -k + 1)
		mu1 += k;

	if (mu1 == -k + 1)
		mu1 = 0;

	if (mu1 < -k + 1) {
		s = "1" + s;
		mu1++;
		while (mu1 < -k + 1) {
			mu1++;
			s = s + "0";
		}
		mu1 = 0;
	}

	string mu = "";
	for (int i = 0; i < 15; i++)
		mu = mu + char(48 + ((mu1 >> (14 - i)) & 1));

	if (d1 == d2)
		d1 = '0';
	else
		d1 = '1';

	res = d1 + mu + s;

	if (res.size() > 128)
		res.erase(128, res.size() - 128);

	return res;
}