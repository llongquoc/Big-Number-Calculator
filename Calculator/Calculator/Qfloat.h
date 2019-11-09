#pragma once
#define _USE_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#define ui unsigned int
#define ovl "Overload"
#define udl "Underload"
#define NaN "None a number"
#define inf "Infinity"

using namespace std;

class Qfloat
{
protected:
	ui a[4];
	void onBit(int x);							//bat bit thu x
	bool ss(string x, string y);				//true neu x >= y
	string div2(string s, bool c = true);		//chia so thuc cho 2
	string multi2(string s);					//nhan so thuc cho 2
	string sum1(string s);						//cong 1 cho so nguyen
	string sumb(string x, string y);			//cong nhi phan nguyen
	string subb(string x, string y);			//tru nhi phan nguyen
	string mulb(string x, string y);			//nhan nhi phan nguyen
	string divb(string x, string y);			//chia nhi phan nguyen
	string round(string s, int x);					//lam tron 30 chu so thap phan
	bool is0();
public:
	Qfloat();
	~Qfloat();

	void scanQfloat(string s = "");				//doc so thuc he thap phan
	string printQfloat(int x = 30);				//tra ve so thuc he thap phan, lam trong x chu so thap phan

	void binToDec(string bit);					//doc so thuc he nhi phan
	string decToBin();							//tra ve so thuc he nhi phan

	string operator + (Qfloat x);				//cong 2 so thuc tra ve nhi phan
	string operator - (Qfloat x);				//tru 2 so thuc tra ve nhi phan
	string operator * (Qfloat x);				//nhan 2 so thuc tra ve nhi phan
	string operator / (Qfloat x);				//chia 2 so thuc tra ve nhi phan
};

