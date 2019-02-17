#include "User.h"

//***************************************************
// User::User is the user class's constructor       *
//***************************************************
User::User(){
	setUserKeyword();              // Calling setUserKeyWord() to set user's private key
	setUsernameCipher();           // Calling setUsernameCipher() to set usernameCipher for advance using
}

//***********************************************************
// Definition of User::printMenu. It prints the user menu   *
// to the monitor                                           *
//***********************************************************
void User::printMenu(){
	cout
		<< "\t\t             ~  MAIN MENU ~         " << endl
		<< "\t\t     -------------------------------" << endl
		<< "\t\t     |    1] VIEW CALENDAR         |" << endl
		<< "\t\t     |    2] CREATE NEW NOTE       |" << endl
		<< "\t\t     |    3] VIEW & EXPORT NOTE(s) |" << endl
		<< "\t\t     |    4] EDIT NOTE             |" << endl
		<< "\t\t     |    5] LOG OUT               |" << endl;
	cout << "\t\t     Please choose an option: ";
}

//***************************************************************
// Definition of User::setUserKeyword. It sets the specific     *
// key for only  the person which is used for decyption         *
// and encyption the person's note                              *
//***************************************************************
void User::setUserKeyword(){
	string finalText = "";                  // To hold the final text is used for the user's keyword to read the user's note
	char ch;                                // To hold a character 

	// For loop to get only letters in the password and capitalize them
	for (int index = 0; index < (signed)password.length(); index++){
		if (isalpha(password.at(index))) {
			ch = password.at(index);
			finalText += toupper(ch);
		}
	}
	userKeyWord = finalText;               // set userKeyWord is finalText
}
 
//********************************************************************
// Definition of User::setUsernameCipher. It sets the username as a  *  
// cipher text which is used for advance using such as a folder name *
//********************************************************************
void User::setUsernameCipher(){
	decode->setAll(0, keyWord, username);                 // Decode the username with the keyWord
	usernameCipher = decode->getFinalText();
	cout << usernameCipher << endl;
}

//************************************************************************
// Definition of User::userCreateNote. It asks for input date            *
// Then, It calls creteNewNote in the note class to create a new note.   *
//************************************************************************
void User::userCreateNote(){
	Note note(userKeyWord, usernameCipher);
	Date date;
	
	// Asks for input date
	cout << "\20Enter the date" << endl;                  
	cin >> date;
	
	// Calling createNewNote() to create a new note on the date as its arguments
	note.createNewNote(date.getMonth(), date.getDay(), date.getYear());   
}

//****************************************************************************
// Definition of User::userCreateNote. The parameter is the input option    *
// that the user want how the program presents to the monitor. For example,  *
// printing all note in a month.                                             *
//****************************************************************************
void User::viewAndExportNote(char option){
	Note note(userKeyWord, usernameCipher);   // Create a note's object to use functions in the note
	Date date;                                // Create a date's object
	int month, year;
	int daysInMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	switch (option)
	{
	case 1:// 3.1 Daily report (open dateAsStr.txt to print on the monitor and allows to write the record to a file
		cout << endl << "  Please enter the date which you want to get a report" << endl << endl;
		cin >> date;                          // Get date from input
		
		// Calling viewAndExportANote(mm,dd,yyyy) to view a note on the date as in arguments
		note.viewAndExportANote(date.getMonth(), date.getDay(), date.getYear());
		break;
	case 2:
		// 3.2 Monthly report (open \\dateAsStr.txt in the input month of a year to print on the monitor and allows to write the record to a file
		cout << endl << "  Please enter the month and the year which you want to get a report" << endl << endl;

		cout << "  Month(mm): ";
		cin >> month; cin.ignore();      // Get month from input
		date.setMonth(month);            // Calling setMonth(mm) to set month in the date's object

		cout << "  Year(yyyy): ";
		cin >> year; cin.ignore();        // Get year from input
		date.setYear(year);               // Calling setYear(mm) to set year in the date's object
		
		// If the input year is leap year, let second month has 29 days
		if (date.isLeap())
			daysInMonths[1] = 29;    

		// Calling viewAndExportNotes() to display and export all note in a month
		note.viewAndExportNotes(date.getMonth(), 1, date.getYear(), date.getMonth(), daysInMonths[date.getMonth()-1], date.getYear());
		
		break;
	default:
		break;
	}
}

//************************************************************************************************
// Definition of User::printUserCalendar. The parameters are a month and a year as               *
// an integer. It prints out the days in the month after the header for each month and idenify   * 
// which date is current day or on a date has note                                               *
//************************************************************************************************
void User::printUserCalendar(int month, int year) {
	Note note(userKeyWord, usernameCipher);
	Date date;

	date.setMonth(1);             // Set month is 1 for defult
	date.setMonth(month);         // Set month with the function's argument
	date.setYear(year);           // Set year by the funcion's argument

	int daysInMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (date.isLeap())
		daysInMonths[1] = 29;
	int numOfDay;
	int currentMonth = 1;
	int firstDayInCurrentMonth = date.firstDayofNewYearAndMonth(year);
	
	// The calendar's header
	cout
		<< "\t\t\t   ********************" << endl
		<< "\t\t\t   *"<< setw(9) << date.monthOfYear(month) << " " << year << "    *"  << endl
		<< "\t\t\t   ********************" << endl;
	
	cout << "\t\t   S     M     T     W     T     F     S" << endl;
	cout << "\t\t________________________________________" << endl;


	while (currentMonth <= month) {
		numOfDay = daysInMonths[currentMonth - 1];
		if (currentMonth == month){
			int day = 1;
			cout << "\t\t";

			// Calling skipToDay() to create spaces for the first day is matched with a day in week
			date.skipToDay(firstDayInCurrentMonth);
			while (day <= numOfDay) {
				// If day has a note is existed, prints the day with star sign
				if (note.noteOnDateIsExist(date.getMonth(), day, date.getYear()))
					cout << setw(2) << "*" << setw(2) << day << setw(2) << " ";
				// If day is the current day, prints the day with basket
				else if (day == date.getCurreectDay() && date.getYear() == date.getCurreectYear() && date.getMonth() == date.getCurreectMonth())
					cout << setw(2) << "[" << setw(2) << day << setw(2) << "] ";
				else
					cout << setw(4) << day << setw(2) << " ";
				
				// To skip the line
				if (firstDayInCurrentMonth == 6){
					cout << endl << "\t\t";
					firstDayInCurrentMonth = 0;
				}
				else firstDayInCurrentMonth = firstDayInCurrentMonth + 1;
				day = day + 1;
			}
			cout << endl << endl << endl;
			currentMonth = currentMonth + 1;
		}
		else{
			int day = 1;
			while (day <= numOfDay) {
				if (firstDayInCurrentMonth == 6){
					firstDayInCurrentMonth = 0;
				}
				else firstDayInCurrentMonth = firstDayInCurrentMonth + 1;
				day = day + 1;
			}
			currentMonth = currentMonth + 1;
		}
	}
}

//**************************************************************************************
// Definition of User::editNote. The parameters are a month, a day and a year as       *
// an integer. They are used to open the file on the input date and allow the user to  *
// edit the note by calling editSingleWord() in the note class's object                *
//**************************************************************************************
void User::editNote(int mm, int dd, int yyyy){
	Note note(userKeyWord, usernameCipher);
	note.editSingleWord(mm, dd, yyyy);
}

//***********************************************************************************
// Definition of User::viewNote. The parameters are a month, a day and a year as   *
// an integer. They are used to open the file on the input date and print it.       *
//***********************************************************************************
void User::viewNote(int mm, int dd, int yyyy){
	Note note(userKeyWord, usernameCipher);
	note.viewAndExportANote(mm, dd, yyyy);
}
