#include "VigenereCipher.h"

VigenereCipher::VigenereCipher(int mode) {
	this->mode = ((mode == 1) ? DECRYPT : ENCRYPT);
	fillAlpha();
	fillTableCode();
}

VigenereCipher::VigenereCipher(){
	this->mode = DECRYPT;
	fillAlpha();
	fillTableCode();
}

void VigenereCipher::fillAlpha() {
	for (int index = 0; index < sizeOfAlpha; index++)
		alphabet[index] = (char)('A' + index);
}

void VigenereCipher::fillTableCode() {
	for (int index = 0; index < sizeOfAlpha; index++) {
		int counter = index;
		for (int index1 = 0; index1 < sizeOfAlpha; index1++) {
			codeTable[index][index1] = alphabet[counter++];
			if (counter > 25)
				counter = 0;
		}
	}
}

int VigenereCipher::findIndexOfLetter(char ch) {
	int index = -1;
	for (int i = 0; i < (signed)strlen(alphabet); i++) {
		if (alphabet[i] == ch)
			index = i;
	}
	return index;
}

string VigenereCipher::getFinalText() {
	string finalText = "";
	int intText, intKey;
	char ch;

	try {
		if (mode == ENCRYPT) {
			for (int index = 0; index < (signed)text.length(); index++)
			{
				if (isupper(text.at(index))) {
					intText = findIndexOfLetter(text.at(index));
					intKey = findIndexOfLetter(keyWord.at(index));
					ch = codeTable[intText][intKey];
					finalText += ch;
				}
				else if (islower(text.at(index))){
					intText = findIndexOfLetter(toupper(text.at(index)));
					intKey = findIndexOfLetter(keyWord.at(index));
					ch = codeTable[intText][intKey];
					finalText += tolower(ch);
				}
				else {
					finalText += text.at(index);
				}
			}
		}
		else if (mode == DECRYPT) {
			for (int index = 0; index < (signed)text.length(); index++)
			{
				if (isupper(text.at(index))) {
					intKey = findIndexOfLetter(keyWord.at(index));
					for (int index1 = 0; index1 < sizeOfAlpha; index1++)
						if (codeTable[intKey][index1] == text.at(index))
							finalText += alphabet[index1];
				}
				else if (islower(text.at(index))) {
					intKey = findIndexOfLetter(keyWord.at(index));
					for (int index1 = 0; index1 < sizeOfAlpha; index1++)
						if (codeTable[intKey][index1] == toupper(text.at(index)))
							finalText += tolower(alphabet[index1]);
				}
				else {
					finalText += text.at(index);
				}
			}
		}
	}
	catch (string exceptionString) {
		finalText = "Process failed..";
	}
	return finalText;
}

void VigenereCipher::printTableCode() {
	for (int index = 0; index < sizeOfAlpha; index++) {
		for (int index1 = 0; index1 < sizeOfAlpha; index1++) {
			cout << codeTable[index][index1] << " ";
		}
		cout << endl;
	}
}

void VigenereCipher::setKeyWord(string keyWord) {
	//keyWord = keyWord.toUpperCase();
	//String text = (mode == DECRYPT ? cipherText : plainText);

	int multiple = text.length() / keyWord.length();
	int leftOver = text.length() % keyWord.length();
	for (int index = 0; index < multiple - 1; index++)
		keyWord += keyWord;
	keyWord += keyWord.substr(0, leftOver);
	this->keyWord = keyWord;
}

void VigenereCipher::setAll(int mode, string keyWord, string text){
	setMode(mode);
	setText(text);
	setKeyWord(keyWord);
}