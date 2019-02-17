#ifndef DEVELOPTOOL_H
#define DEVELOPTOOL_H
#include "AccountOrganize.h"

class DevelopTool :public AccountOrganize{
public:
	void printMenu();
	void searchUserInfo(string username);
	bool confirmDev(string pin);
	string getFinalTextMiniVigenereCipher(int mode, string keyWord, string text);
};
#endif