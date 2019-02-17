#include "DevelopTool.h"

//******************************************************************
// Definition of DevelopTool::printMenu. It prints the user menu   *
// to the monitor                                                  *
//******************************************************************
void DevelopTool::printMenu(){
	cout
		<< "\t      ~  DEVELOP  TOOL ~       " << endl
		<< "\t-------------------------------" << endl
		<< "\t|    1] SEARCH A USER         |" << endl
		<< "\t|    2] VIGENERE CIPHER       |" << endl
		<< "\t|    3] LOG OUT               |" << endl;
	cout << "\tPlease choose an option: ";
}


//**********************************************************************************
// Definition of DevelopTool::searchUserInfo. Its parameter is a string username   *
// It searches for the input username's information such as name and password      *
//**********************************************************************************
void DevelopTool::searchUserInfo(string username){
	string pin;                                         // To hold develop's pin

	cout << "Testing key "<< keyWord << endl;           // For testing the program
	cout << "Enter Develop's pin: ";
	getline(cin, pin);

	decode->setAll(0, pin, username);                   // Decode the username 
	username = decode->getFinalText();

	// Compare the keyword and pin
	while (pin.compare(keyWord) != 0 && pin.compare("Exit") != 0){
		cout << "\a\tIncorrect!! Enter Develop's pin: ";
		getline(cin, pin);
	}

	// If the develop identified himself, process it
	if (confirmDev(pin)){
		string usernameChipher, passwordChipher, firstNameChipher, lastNameChipher;
		string currectPass = person->passwordCipher,
			currectUser = person->usernameCipher,
			currectFirstname = person->firstNameCipher,
			currectLastname = person->lastNameCipher;
		int currectStatus = person->status;
		int status;

		fstream userData;
		userData.open("userData.dat", ios::in | ios::binary);
		bool matchUser = false;
		if (userData){

			userData.read(reinterpret_cast<char *>(&*person), sizeof(*person));
			// Read from the file until matchUser is true or no more data in file
			while (!userData.eof() && !(matchUser)){
				usernameChipher = person->usernameCipher;
				passwordChipher = person->passwordCipher;
				firstNameChipher = person->firstNameCipher;
				lastNameChipher = person->lastNameCipher;
				status = person->status;

				if (username.compare(usernameChipher) == 0){
					matchUser = true;
				}

				// If matchUser, get all information for the user and display it
				if (matchUser){
					decode->setAll(1, pin, usernameChipher);
					cout << "  Userneme: " << decode->getFinalText() << endl;

					decode->setAll(1, pin, passwordChipher);
					cout << "  Password: " << decode->getFinalText() << endl;

					decode->setAll(1, pin, firstNameChipher);
					cout << "  First neme: " << decode->getFinalText() << endl;

					decode->setAll(1, pin, lastNameChipher);
					cout << "  Last neme: " << decode->getFinalText() << endl;

					person->status = status;
					userData.close();

					cout
						<< endl
						<< "               !!!!!!!!!!!!!!!!!!!!!!!!!" << endl
						<< "               !! PRIVATE INFORMATION !!" << endl
						<< "               !!!!!!!!!!!!!!!!!!!!!!!!!" << endl << endl;

					// Reset person structure with previous information
					person->usernameCipher = currectUser;
					person->passwordCipher = currectPass;
					person->firstNameCipher = currectFirstname;
					person->lastNameCipher = currectLastname;
					person->status = currectStatus;
					system("pause");
					return;
				}
				userData.read(reinterpret_cast<char *>(&*person), sizeof(*person));
			}
			userData.close();

			// Display it, if cannot find the user
			if (!matchUser){
				encode->setAll(1, pin, username);
				cout << "\tCannot find the username is " << encode->getFinalText() << "." << endl;
				system("pause");
			}
			person->usernameCipher = currectUser;
			person->passwordCipher = currectPass;
			person->firstNameCipher = currectFirstname;
			person->lastNameCipher = currectLastname;
			person->status = currectStatus;
		}
	}
	return;
}

//***************************************************************************
// Definition of DevelopTool::confirmDev. It compares developer's pin and   *
// keyWord. If they are same, return true. If not, return false             *
//***************************************************************************
bool DevelopTool::confirmDev(string pin){
	if (pin.compare(keyWord) == 0)
		return true;
	else
		return false;

}

//*****************************************************************
// Defintion of DevelopTool::getFinalTextMiniVigenereCipher       *
// The mode is 0 or 1 and text must be longer than keyWord        *
// It does the text to cipher text or cipher text to plain text   *
//*****************************************************************
string DevelopTool::getFinalTextMiniVigenereCipher(int mode, string keyWord, string text){
	if (mode == 0){
		encode->setAll(mode, keyWord, text);
		return  encode->getFinalText();
	}
	else{
		decode->setAll(mode, keyWord, text);
		return decode->getFinalText();
	}
}


