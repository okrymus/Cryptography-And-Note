#include "ValidateInput.h"

// Pre condition:  endPoint > startPoint and It has istream as its argument, and has cin object as its default
// Post condition: Return a integer number which is in the range
//                 it does NOT crashes for non-numeric input
//                 removes everything else from the cin
int ValidateInput::getIntInRange(double startPoint, double endPoint, istream &os)
{
	int number = getInteger(os);

	while (number < startPoint || number > endPoint)
	{
		cout << "\t" << "Your number must be ";
		if (number < startPoint)
			cout << "greater than or equal " << startPoint;
		else
			cout << "less than or equal " << endPoint;

		cout << ". Try again: ";
		number = getInteger(os);
	}
	return (int)number;
}

// Pre condition:  It has istream as its argument, and has cin object as its default
// Post condition: Return a valid integer value  
//                 it does NOT crashes for non-numeric input
//                 removes everything else from the cin
int ValidateInput::getInteger(istream &os)
{
	double number = getNum(os);

	while (number != (int)number)
	{
		cout << "\t" << number << " is NOT an integer. Try again: ";
		number = getNum(os);
	}
	return int(number);
}

// Pre condition:  It has istream as its argument, and has cin object as its default
// Post condition: Return a valid double number
//                 it does not crashes for non-numeric input   
//                 removes everything else from the cin
double ValidateInput::getNum(istream &os)
{
	double number;
	while (!(os >> number))
	{
		cout << "\tNo letters please. Try again: ";
		os.clear();
		os.ignore(80, '\n');
	}
	os.ignore(80, '\n');
	return number;
}

// Pre condition:  It has istream as its argument, and has cin object as its default
// Post condition: Return a valid positive integer
//                 it does NOT crashes for non-numeric input
//                 removes everything else from the cin
int ValidateInput::getIntPosNum(istream &os)
{
	int number = getInteger(os);

	while (number <= 0)
	{
		cout << "\t" << number << " is NOT an positive. Try again: ";
		number = getInteger(os);
	}
	return number;
}

// Pre condition:  It has istream as its argument, and has cin object as its default
// Post condition: Return a valid positive double
//                 it does NOT crashes for non-numeric input
//                 removes everything else from the cin
double ValidateInput::getPosNum(istream &os)
{
	double number = getNum(os);

	while (number <= 0)
	{
		cout << "\t" << number << " is NOT an positive. Try again: ";
		number = getNum();
	}
	return number;
}

string ValidateInput::getStringInLargeSize(int sizeOfString, istream &os){
	string aStr;
	getline(os, aStr);
	while (aStr.length() < (signed)sizeOfString){
		cout
			<< "\a\t!!The input must be longer than or equal to " << sizeOfString << " letters," << endl
			<< "\ttry agian: ";
		getline(os, aStr);
	}
	return aStr;
}

string ValidateInput::getOnlyAlpaStringWithSetSize(int sizeOfString, istream &os){
	string aStr;
	bool allIsLetters = true;
	do {
		if (!allIsLetters){
			cout << "\tYour input must be only alphabet, try again: ";
		}
		aStr = getStringInLargeSize(sizeOfString, os);

		allIsLetters = true;

		for (int index = 0; index < (signed)aStr.length(); index++)
			if (!isalpha(aStr.at(index)))
				allIsLetters = false;
	} while (!allIsLetters);

	return aStr;
}

string ValidateInput::getLineWithCapitalized(istream &os)
{
	string word;
	char chrWord;

	getline(os, word);

	int num = word.size();

	for (int index = 0; index<num; index++)
	{
		if (index == 0)
		{
			chrWord = toupper(word[index]);
			word[index] = chrWord;
		}
		else if (index != 0)
		{
			chrWord = tolower(word[index]);
			word[index] = chrWord;
		}
		else if (isspace(word[index]))
		{
			chrWord = toupper(word[index + 1]);
			word[index + 1] = chrWord;
		}
	}
	return word;
}

