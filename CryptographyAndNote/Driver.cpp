// Cryptography and Note
// The program demonstrtes the basic crypyoghaphy by using Vigenere cipher and adapts it for hidding the information such as a note
// Last modified: 
// Programmer: Panupong Leenawarat

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "Date.h"
#include "VigenereCipher.h"
#include "AccountOrganize.h"
#include "ValidateInput.h"
#include "User.h"
#include "DevelopTool.h"
using namespace std;

void printTitle();

int main(){
	string username, password;                         // To hold password and username
	AccountOrganize *account = new AccountOrganize;    // Create AccountOrganize's object as a pointer
	ValidateInput input;                               // Create ValidateInput's object to get only valid input
	char select;                                       // To hold selection from the user
	int month, year, day;                              // To hold month, day and year from input
	Date date;                                         // Create Date's object to get local date or setDate

start:
	system("cls");
	printTitle();                                      // Calling printTitle() function to print Program's title

	account->printMenu();                              // Print the account menu
	select = input.getIntInRange(1, 3);                // Get selection from input object
start2:
	// If the selection is matched a case, process it
	switch (select)
	{
	case 1:
		system("cls");
		// LOGIN TITTLE
		cout
			<< endl
			<< "                     ********************************* " << endl
			<< "                     *            LOGIN              * " << endl
			<< "                     *  ENTER username and password  * " << endl
			<< "                     ********************************* " << endl << endl;

		cin >> account;                                  // cin stream to account object to set username and password

		// If the program cannot find the username, process it to display a message by calling isExistedAccount() in the account object to check
		if (!(account->isExistedAccount())){
			cout
				<< endl
				<< "                 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl
				<< "                 !! The program cannot find the account, !!" << endl
				<< "                 !!      please create a new account     !!" << endl
				<< "                 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl << endl;

			cout << "\a                 ";
			system("pause");
			goto start;                                  // Go to start
		}
		// Else if the program fround the username and password, process it
		else{			
			//If the input account is user, process it
			if (account->isUser()){
			
//////////////////////////////////////////////////////////////// USER ////////////////////////////////////////////////////////////////////////////
				User *person = new User;                              // Create User class's object as a pointer

				while (true){
					system("cls");
					// Display user information
					cout << "\n\t\20Welcome!! " << account << endl;


					// Display current calendar by calling printUserCalendar() in the User's object
					person->printUserCalendar(date.getCurreectMonth(), date.getCurreectYear());

					// Calling printMenu fron the User class's object
					person->printMenu();

					// Get a selection from the user
					select = input.getIntInRange(1, 5);

					// While the selection is greater than 0, process it
					while (select > 0){
						// Switch to the case which is matched with the selection
						switch (select)
						{
						case 1:
							system("cls");
							printTitle();                            // Print Program's title

							cout << "\t\20Enter month: ";
							month = input.getIntInRange(1, 12);      // Calling getIntInRange() to get only number 1 - 12
							date.setMonth(month);                    // Calling setMonth() in the date object to set the month and check it 
							cout << "\t\20Enter year: ";

							year = input.getIntInRange(1900, 2200);  // Calling getIntInRange() to get only number 1900 - 2200
							date.setYear(year);                      // Calling setYear() in the date object to set the year and check it 
							
							cout << endl;
							person->printUserCalendar(date.getMonth(), date.getYear());    // Calling printUserCalendar() in the user object to print the calendar
							
							// Calendar information
							cout << "\t (*): has record on the date" << endl
								<< "\t ([]): the current date" << endl << endl;

							cout << "\t\20Enter the date you want to view: ";               // Ask for a date the user want to view the note
							day = input.getIntInRange(1, 31);                               // Get date from user "day"
							date.setDay(day);                                               // Calling setDay() to check valid input date and store the date in its class

							cout << endl;
							// Calling the viewNote() function in the user class to view a note
							person->viewNote(date.getMonth(),date.getDay(),date.getYear());
							system("pause");
							select = 0;     break;
						case 2:
							system("cls");
							printTitle();                                    // Print Program's title
							
							person->userCreateNote();                        // Calling userCreateNote function in the User's object to create or replace the note

							select = 0;     break;
						case 3:
							system("cls");
							// Display the user note and allow the user to export them to a file
							cout
								<< endl
								<< "\t                    View and Export options " << endl
								<< "\t                    ======================= " << endl << endl;
							// Display the view and export options
							cout
								<< "\t                 *****************************" << endl
								<< "\t                 *     1] Daily Report       *" << endl
								<< "\t                 *     2] Monthly Report     *" << endl
								<< "\t                 *     3] Back to menu       *" << endl
								<< "\t                 *****************************" << endl << endl
								<< "\t                  Please choose the options: ";

							// Get the selection from validationInput's object
							select = input.getIntInRange(1, 3);

							// If the selection is not 3, process it
							if (select != 3)
								person->viewAndExportNote(select);      // Calling the viewAndExportNote() function from the User's object
							select = 0;     break;
						case 4:
							system("cls");
							cout
								<< endl
								<< "               ********************************** " << endl
								<< "               *  EDIT NOTE, PLEASE ENTER DATE  * " << endl
								<< "               ********************************** " << endl << endl;
							
							cin >> date;                                 // Get date from input

							person->editNote(date.getMonth(), date.getDay(), date.getYear());   // Calling the editNote() function to edit a note on the date as its arguments
							select = 0;     break;
						
						case 5:
							// Display and let the user to confirm again
							cout
								<< endl
								<< "             *************************************************** " << endl
								<< "             *  Please hit ENTER to LOG OUT or select another  * " << endl
								<< "             *************************************************** " << endl << endl
								<< "                         Please choose the options: ";
							cin.get(select);
							// If a user hit enter, exit the program
							if (select == '\n'){
								delete person;     // Delete the User's object pointer
								goto start;        // Go to strat
							}
							cin.putback(select);
							// Get the selection from validationInput's object
							select = input.getIntInRange(1, 5);
						}
					}
				}
			}
			else
			{
////////////////////////////////////////////////////////////////////////// DEVELOPER ///////////////////////////////////////////////////////////////////////////////
			
				DevelopTool *developer = new DevelopTool;       // Create the developer's object
				string username, text, key;                 
				int mode;                                       // To hold a mode for decrypt or encrypt
				char modeChar;

				while (true){
					system("cls");
					// Display the developer information
					cout << "\n\t\20Welcome!! " << account << endl;

					developer->printMenu();                                 // Display the printMenu() from the developer object
					select = input.getIntInRange(1, 3);				        // Get the selection from validationInput's object

					// While the selection is greater than zero, process it
					while (select > 0){
						// Switch to the case which matches the selection
						switch (select)
						{
						case 1:
							system("cls");
							cout
								<< endl
								<< "               ***************************** " << endl
								<< "               *       SEARCHING USER      * " << endl
								<< "               ***************************** " << endl << endl;
							
							cout << "\20Enter username for searching: ";       //Display and get a username for searching the user
							getline(cin, username);                          

							developer->searchUserInfo(username);               // Calling the searchUserInfo() function to search and print out user's information

							system("cls");
							select = 0;     break;
						case 2:
							// Mini Vigenere Cipher is a tool to try to decrypt and encrypt
							cout
								<< endl
								<< "               ********************************** " << endl
								<< "               *      MINI VIGENERE CIPHER      * " << endl
								<< "               ********************************** " << endl << endl;

							cout << "\t\20Enter Encrypt or Decrypt: ";                
							cin >> modeChar; cin.ignore();                                 // Get mode form input
							
							// While the mode is incorrect, try to get the correct mode
							while (!(modeChar == 'E' || modeChar == 'e' || modeChar == 'D' || modeChar == 'd'))
							{
								cout << "\t\20Please type only Encrypt or Decrypt :";       
								cin >> modeChar;  cin.ignore(80, '\n');
							}
							
							modeChar == 'E' || modeChar == 'e' ? mode = 0 : mode = 1;

							do {
								if (text.length() < key.length()){
									cout << "\t\20The text message must be longer than keyword" << endl;
								}
								cout << "\20Enter a text message: ";               // Display ask for a text
								getline(cin, text);

								cout << "\20Enter key word: ";                     // Display ask for a keyword
								getline(cin, key);
							} while (text.length() < key.length());

							// Print the final text either plain text or cipher text

							if (mode == 0)
								cout << " The cipher text is ";
							else if (mode == 1)
								cout << " The plain text is ";
							cout << developer->getFinalTextMiniVigenereCipher(mode, key, text) << endl;

							system("pause");
							system("cls");
							select = 0;     break;
						case 3:
							// Display and let the developer to confirm again
							cout
								<< endl
								<< "             *************************************************** " << endl
								<< "             *  Please hit ENTER to LOG OUT or select another  * " << endl
								<< "             *************************************************** " << endl << endl
								<< "                         Please choose the options: ";
							cin.get(select);
							// If a user hit enter, exit the develop part
							if (select == '\n'){
								delete developer;         // Delete the Developer's pointer
								goto start;               // Go to start
							}
							cin.putback(select);      
							select = input.getIntInRange(1, 5);     // Accept only selection
						}
					}
				}
			}
		}
	case 2: 
		system("cls");
		// Create an account title
		cout
			<< endl
			<< "           ******************************************************** " << endl
			<< "           *   CREATE NEW ACCOUNT PLEASE ENTER YOUR INFORMATION   * " << endl
			<< "           ******************************************************** " << endl << endl;
		
		account->createAccount();    // Calling createAccount() function to create AccountOrganize's object
		select = 1;
		goto start;
	case 3:
		// Display a message to confirm to exit the program
		cout
			<< endl
			<< "               ************************************************ " << endl
			<< "               *  Please hit ENTER to exit or select another  * " << endl
			<< "               ************************************************ " << endl << endl
			<< "                         Please choose the options: ";

		cin.get(select);
		// If a user hit enter, exit the program
		if (select == '\n')
			exit(0);

		cin.putback(select);
		select = input.getIntInRange(1, 3);
		goto start2;
	}

	delete account;           // Delete the AccountOrganize's object
	system("pause");
	return EXIT_SUCCESS;
}


// The program's title
void printTitle(){
	cout
		<< endl
		<< "\t\t -------------------------------" << endl
		<< "\t\t - CRYPTOGRAPHY & SIMPLE NOTE  -" << endl
		<< "\t\t -      BY LEE. PANUPONG       -" << endl 
		<< "\t\t -------------------------------"<< endl << endl;
}
