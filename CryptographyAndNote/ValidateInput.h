#ifndef VALIDATEINPUT_H
#define VALIDATEINPUT_H
#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
using namespace std;

struct ValidateInput{
	int getIntInRange(double startPoint, double endPoint, istream &os = cin);
	int getInteger(istream &os = cin);
	double getNum(istream &os = cin);
	int getIntPosNum(istream &os = cin);
	double getPosNum(istream &os = cin);
	string getOnlyAlpaStringWithSetSize(int sizeOfString, istream &os = cin);
	string getStringInLargeSize(int sizeOfString, istream &os = cin);
	string getLineWithCapitalized(istream &os = cin);
	char getTwoSpecificChar(char *first, char *second);
};
#endif // !VALIDATEINPUT_H
