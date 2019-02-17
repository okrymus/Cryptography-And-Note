#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "VigenereCipher.h"
#include "Binarytree.h"
#include "SearchableVector.h"

struct MyNote
{
	int day;
	int month;
	int year;
	char noteCipher[120];
};

class Note{
private:
	const int NOTE_SIZE = 120;
	string key;
	string folderName;
	MyNote myNote;
	VigenereCipher encode;
	VigenereCipher decode;
	char getYorN();
public:
	Note(string key, string folderName);

	void createNewNote(int mm, int dd, int yyyy);
	bool findExistedFile(string fileName);
	void viewAndExportANote(int mm, int dd, int yyyy);
	void printWritedNote(string dateAsStr, ostream&os = cout);
	bool noteOnDateIsExist(int mm, int dd, int yyyy);
	void viewAndExportNotes(int sMonth, int sDate, int sYear, int eMonth, int eDate, int eYear);
	void replaceNote(int mm, int dd, int yyyy);
	void getNoteFromFile(){

	}
	void editSingleWord(int mm, int dd, int yyyy);
};