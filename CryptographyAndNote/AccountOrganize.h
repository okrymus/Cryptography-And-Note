#ifndef ACCOUNTORGANIZE_H
#define ACCOUNTORGANIZE_H
#include "VigenereCipher.h"
#include "ValidateInput.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class AccountOrganize;

// Function Prototypes for Overloaded Stream Operators 
ostream &operator << (ostream &, const AccountOrganize &);
istream &operator >> (istream &, AccountOrganize &);

struct UserData
{
	string usernameCipher;
	string passwordCipher;
	string firstNameCipher;
	string lastNameCipher;
	int status;
};

class AccountOrganize{
private:
	bool verifiedPassword(string password);
	void invalidPassword(bool vLength, bool vDigit, bool vUpper, bool vLower, bool vAlpha, bool vSpecificChars, bool vSpecialChars);
	void invalidUsername(bool vLength, bool vAlpha, bool vSpecialChars);
	bool verifiedUsername(string username);
protected:
	static string password;
	static string username;
	static const string keyWord;
	UserData *person = new UserData;
	VigenereCipher *encode = new VigenereCipher(0);
	VigenereCipher *decode = new VigenereCipher(1);
	ValidateInput input;
public:
	AccountOrganize();

	void setPasswordCipher(string keyWord, string text);
	void setUsernameCipher(string keyWord, string text);
	void setFirstNameCipher(string keyWord, string text);
	void setLastNameCipher(string keyWord, string text);

	void createAccount();
	bool isExistedAccount();
	bool isUser();
	void setPassword(string password);

	virtual void printMenu();

	// Friends
	friend istream &operator >> (istream &, AccountOrganize *);
	friend ostream &operator << (ostream &, AccountOrganize *);
};

#endif