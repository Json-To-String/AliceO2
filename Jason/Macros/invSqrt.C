#include<iostream>

using namespace std;

Double_t Q_rsqrt(Double_t number )
{
	Double_t y = number;
	Double_t x2 = y * 0.5;
	std::int64_t i = *(std::int64_t *) &y;

	i = 0x5fe6eb50c7b537a9 - (i >> 1);
	y = *(Double_t *) &i;
	y = y * (1.5 - (x2 * y * y));
	y = y * (1.5 - (x2 * y * y));
	return y;
}

void invSqrt() {
	Double_t n = .25;
	cout<<Q_rsqrt(n)<<"\n";
}
