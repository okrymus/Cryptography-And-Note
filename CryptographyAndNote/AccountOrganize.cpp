#include "AccountOrganize.h"

string AccountOrganize::password = password;
string AccountOrganize::username = username;
const string AccountOrganize::keyWord = "AZYX";

AccountOrganize::AccountOrganize(){
	VigenereCipher *encode = new VigenereCipher(0);
	VigenereCipher *decode = new VigenereCipher(1);
};

void AccountOrganize::printMenu(){
	cout
		<< "\t\t_________________________________" << endl
		<< "\t\t*      1] LOG IN                *" << endl
		<< "\t\t*      2] CREATE A NEW ACCOUNT  *" << endl
		<< "\t\t*      3] EXIT PROGRAM          *" << endl;

	cout << "\t\t Please choose the option: ";
}

void AccountOrganize::setPasswordCipher(string keyWord, string text){
	encode->setAll(0, keyWord, text);
	person->passwordCipher = encode->getFinalText();
}

void AccountOrganize::setUsernameCipher(string keyWord, string text){
	encode->setAll(0, keyWord, text);
	person->usernameCipher = encode->getFinalText();
}

void AccountOrganize::setFirstNameCipher(string keyWord, string text){
	encode->setAll(0, keyWord, text);
	person->firstNameCipher = encode->getFinalText();
}

void AccountOrganize::setLastNameCipher(string keyWord, string text){
	encode->setAll(0, keyWord, text);
	person->lastNameCipher = encode->getFinalText();
}

void AccountOrganize::createAccount(){
	string firstname, lastname, username, password;
	char status;
	do{
		cout << "\20Enter first name: ";
		firstname = input.getLineWithCapitalized();
		cout << "\20Enter last name: ";
		lastname = input.getLineWithCapitalized();
		cout << "\20Enter username: ";
		getline(cin, username);
		while (!verifiedUsername(username)){
			// Create empty lines
			cout << endl << endl;
			// Ask for re-enter username
			cout << " Re-Enter Username: ";
			getline(cin, username);
			// Create empty lines
			cout << endl << endl;
		}
		cout << "\20Enter password: ";
		getline(cin, password);
		while (!verifiedPassword(password)){
			// Create empty lines
			cout << endl << endl;
			// Ask for re-enter password
			cout << " Re-Enter Password: ";
			getline(cin, password);
			// Create empty lines
			cout << endl << endl;
		}
		cout << "\20Enter status User or Developer: ";
		cin >> status;  cin.ignore(80, '\n');

		// while a input character is not looking for characters, it is still asks for a right one
		while (!(status == 'u' || status == 'd' || status == 'D' || status == 'U'))
		{
			cout << "\tPlease type only Yes or No :";
			cin >> status;  cin.ignore(80, '\n');
		}

		status == 'D' ? person->status = 1 : person->status = 0;
		
		setUsernameCipher(keyWord, username);
		setPasswordCipher(keyWord, password);
		setFirstNameCipher(keyWord, firstname);
		setLastNameCipher(keyWord, lastname);

	} while (isExistedAccount());

	// Create a new directory by using nameInput as name of a folder
	string quote = "\"";
	string commandString = "mkdir " + quote + person->usernameCipher + "\"";
	system(commandString.c_str());
	fstream newUser("userData.dat", ios::out | ios::app | ios::binary);
	//velifyUser() ? cout << "The account is existed, try again\n" : cout << "Created your account"
	newUser.write(reinterpret_cast<char *>(&*person), sizeof(*person));
	newUser.close();
}

bool AccountOrganize::isExistedAccount(){
	string usernameCipher, passwordCipher, firstNameCipher, lastNameCipher;
	string currectPass = person->passwordCipher,
		currectUser = person->usernameCipher,
		currectFirstname = person->firstNameCipher,
		currectLastname = person->lastNameCipher;
	int currectStatus = person->status;
	int status;

	fstream userData;
	userData.open("userData.dat", ios::in | ios::binary);
	bool matchUser = false, matchPass = false;

	if (!userData){
		return false;
	}
	userData.read(reinterpret_cast<char *>(&*person), sizeof(*person));

	while (!userData.eof() && !(matchUser && matchPass)){
		usernameCipher = person->usernameCipher;
		passwordCipher = person->passwordCipher;
		firstNameCipher = person->firstNameCipher;
		lastNameCipher = person->lastNameCipher;
		status = person->status;
		if (currectUser.compare(usernameCipher) == 0){
			matchUser = true;
		}

		if (currectPass.compare(passwordCipher) == 0)
			matchPass = true;

		if (matchUser && matchPass){
			person->firstNameCipher = firstNameCipher;
			person->lastNameCipher = lastNameCipher;
			person->status = status;
			userData.close();
			return true;
		}
		userData.read(reinterpret_cast<char *>(&*person), sizeof(*person));
	}
	userData.close();

	person->usernameCipher = currectUser;
	person->passwordCipher = currectPass;
	person->firstNameCipher = currectFirstname;
	person->lastNameCipher = currectLastname;
	person->status = currectStatus;
	return false;
}

bool AccountOrganize::isUser(){
	if (person->status == 0)
		return true;
	else
		return false;
}

void AccountOrganize::setPassword(string password){
	this->password = password;
}

bool AccountOrganize::verifiedUsername(string username){
	int length = username.length();
	bool vLength = false, vAlpha = false, vSpecialChars = true;

	if (length >= 6)
		vLength = true;

	for (int count = 0; count < length; count++)
	{
		switch (username.at(count))
		{
			//  Check the password contains at least one letter
			// Check the password contains at least one uppercase and at at least one lowercase letter
		case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':case 'g':case 'h':
		case 'i':case 'j':case 'k':case 'l':case 'm':case 'n':case 'o':case 'p':
		case 'q':case 'r':case 's':case 't':case 'u':case 'v':case 'w':case 'x':
		case 'y':case 'z':
		case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':
		case 'I':case 'J':case 'K':case 'L':case 'M':case 'N':case 'O':case 'P':
		case 'Q':case 'R':case 'S':case 'T':case 'U':case 'V':case 'W':case 'X':
		case 'Y':case 'Z':  vAlpha = true;  break;
			// Check the password contains at least one digit
		case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':
		case '8':case '9':  break;
		default: vSpecialChars = false;
		}

	}
	// The program displays a message telling the user why the password does not meet the criteria.
	invalidUsername(vLength, vAlpha, vSpecialChars);

	// If any the variables is false, return false, or if all are true, return true
	return vLength && vAlpha && vSpecialChars;
}

void AccountOrganize::invalidUsername(bool vLength, bool vAlpha, bool vSpecialChars)
{
	// If any the variables is false, process it
	if (vLength == false || vAlpha == false || vSpecialChars == false)
	{
		// Display invalid username
		cout
			<< endl
			<< "\t\t        ======================== " << endl
			<< "\t\t        !!! Invalid Username !!! " << endl
			<< "\t\t        ======================== " << endl << endl;

		cout << "\a" << "\t     Your username DOES NOT contain the following: \n\n";
	}

	// Show the reason why it is invalid
	if (vLength == false)
		cout << "\t\t* At least 6 characters long! \n";
	if (vAlpha == false)
		cout << "\t\t* At least one letter. \n";
	if (vSpecialChars == false)
		cout << "\t\t* No special character. \n";

	return;
}

bool AccountOrganize::verifiedPassword(string password){
	int length = password.length();
	bool vLength = false,
		vUpper = false,
		vLower = false,
		vDigit = false,
		vAlpha = false,
		vSpecificChars = false,
		vSpecialChars = true;

	// Check the password is at least 6 characters long and if it is larger than 6, vLength = true
	if (length >= 6)
		vLength = true;

	for (int count = 0; count < length; count++)
	{
		switch (password.at(count))
		{
			//  Check the password contains at least one letter
			// Check the password contains at least one uppercase and at at least one lowercase letter
		case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':case 'g':case 'h':
		case 'i':case 'j':case 'k':case 'l':case 'm':case 'n':case 'o':case 'p':
		case 'q':case 'r':case 's':case 't':case 'u':case 'v':case 'w':case 'x':
		case 'y':case 'z':  vLower = true; vAlpha = true; break;
		case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':
		case 'I':case 'J':case 'K':case 'L':case 'M':case 'N':case 'O':case 'P':
		case 'Q':case 'R':case 'S':case 'T':case 'U':case 'V':case 'W':case 'X':
		case 'Y':case 'Z':  vUpper = true;  vAlpha = true;  break;
			// Check the password contains at least one digit
		case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':
		case '8':case '9':  vDigit = true;
			// Check the password contains one of the following characters: !@ # $ %
		case '!': vSpecificChars = true;    break;
		case '@': vSpecificChars = true;    break;
		case '#': vSpecificChars = true;    break;
		case '$': vSpecificChars = true;    break;
		case '%': vSpecificChars = true;    break;
		default: vSpecialChars = false;    break;
		}
	}

	// The program displays a message telling the user why the password does not meet the criteria.
	invalidPassword(vLength, vDigit, vUpper, vLower, vAlpha, vSpecificChars, vSpecialChars);

	// If any the variables is false, return false, or if all are true, return true
	return vLength && vUpper && vLower && vDigit && vAlpha && vSpecificChars && vSpecialChars;
}

void AccountOrganize::invalidPassword(bool vLength, bool vDigit, bool vUpper, bool vLower, bool vAlpha, bool vSpecificChars, bool vSpecialChars)
{
	// If any the variables is false, process it
	if (vLength == false || vDigit == false || vUpper == false || vLower == false || vAlpha == false || vSpecificChars == false || vSpecialChars == false)
	{
		// Display invalid password
		cout
			<< endl
			<< "\t\t        ======================== " << endl
			<< "\t\t        !!! Invalid Password !!! " << endl
			<< "\t\t        ======================== " << endl << endl;

		cout << "\a" << "\t     Your password DOES NOT contain the following: \n\n";
	}

	// Show the reason why it is invalid
	if (vLength == false)
		cout << "\t\t* At least 6 characters long! \n";
	if (vAlpha == false)
		cout << "\t\t* At least one letter. \n";
	if (vDigit == false)
		cout << "\t\t* At least one numerical digit. \n";
	if (vLower == false)
		cout << "\t\t* At least one lower case letter. \n";
	if (vUpper == false)
		cout << "\t\t* At least one upper case letter. \n";
	if (vSpecificChars == false)
		cout << "\t\t* At least one \"! @ # $ %\" character. \n";
	if (vSpecialChars == false)
		cout << "\t\t* No special character. \n";

	return;
}

istream &operator >> (istream &strm, AccountOrganize *obj){
	string password, username;
	cout << "\20Enter username: ";
	obj->username = obj->input.getStringInLargeSize(6, strm);

	cout << "\20Enter password: ";
	obj->password = obj->input.getStringInLargeSize(6, strm);

	obj->setUsernameCipher(obj->keyWord, obj->username);
	obj->setPasswordCipher(obj->keyWord, obj->password);

	return strm;
}

ostream &operator << (ostream &strm, AccountOrganize *obj){

	obj->decode->setAll(1, obj->keyWord, obj->person->firstNameCipher);
	string firstname = obj->decode->getFinalText();

	obj->decode->setAll(1, obj->keyWord, obj->person->lastNameCipher);
	string lastname = obj->decode->getFinalText();

	strm <<""<< firstname << " ";
	strm << lastname << endl;
	strm << "\tStatus: " << (obj->person->status == 0 ? "User" : "Developer") << endl;
	return strm;
}

