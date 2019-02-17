#ifndef USER_H
#define USER_H
#include "AccountOrganize.h"
#include "Date.h"
#include "Note.h"

class User : public AccountOrganize {
private:
	string userKeyWord, usernameCipher;
	Note note(string userKeyWord, string usernameCipher);
public:
	User();
	
	void printMenu();
	void setUserKeyword();
	void setUsernameCipher();

	void userCreateNote();
	void viewAndExportNote(char option);
	void viewNote(int mm, int dd, int yyyy);
	void printUserCalendar(int month, int year);
	void editNote(int mm, int dd, int yyyy);
};
#endif 