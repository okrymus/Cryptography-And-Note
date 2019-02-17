#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;

class VigenereCipher {
private:
	enum { ENCRYPT = 0, DECRYPT = 1 };
	string text = "", keyWord = "";
	int mode = ENCRYPT;

	// Cipher Table
	static const int sizeOfAlpha = 26;
	char codeTable[sizeOfAlpha][sizeOfAlpha];
	char alphabet[sizeOfAlpha];

	void fillAlpha();
	void fillTableCode();
	int findIndexOfLetter(char ch);

public:
	VigenereCipher();
	VigenereCipher(int mode);

	// Getters
	string getText() { return text; }
	string getKeyWord() { return keyWord; }
	int getMode() { return mode; }

	// Setters
	void setText(string text) {
		//text = text.toUpperCase();
		this->text = text;
	}

	void setMode(int mode) {
		this->mode = ((mode == 1) ? DECRYPT : ENCRYPT);
	}

	void setAll(int mode, string keyWord, string text);
	void setKeyWord(string keyWord);
	string getFinalText();
	void printTableCode();
};
#endif