#include "Note.h"

template<class T>
string dateAsStr(T mm, T dd, T yyyy){
	return to_string(mm) + "-" + to_string(dd) + "-" + to_string(yyyy);
}

//*******************************************************
// It combines folderName and fileName                  *
// Return a fineName which is idenified the directory   *
//*******************************************************
template<class T>
string fileName(T folderName, T fileName){
	return folderName + "//" + fileName + ".dat";
}

//*****************************
// Note class's constructor   *
//*****************************
Note::Note(string key, string folderName){
	this->key = key;
	this->folderName = folderName;
}

//************************************************************************
// Definition of Note::createNewNote. The parameters are the date that   *
// te user want to create a new note                                     *
// If a note on the date is existed, asked for replace it                *
// It lets user to write a note and saves the note to a file             *
//************************************************************************
void Note::createNewNote(int mm, int dd, int yyyy){
	string file = fileName(folderName, dateAsStr(mm, dd, yyyy));   // Set file name
	char YesOrNo;                                                  // To hold Y or N

	// If the file is existed, process it
	if (findExistedFile(file)){
		cout << "The note on the date " + dateAsStr(mm, dd, yyyy) << endl
			<< " is existed, please try with another date or replace it" << endl;
		cout << "Please type YES to replace or No: ";
		YesOrNo = getYorN();
		
		// If YesOrNo is Y, the user want to replace the note
		if (YesOrNo == 'Y' || YesOrNo == 'y'){
			// Asks for new note
			cout << "Enter your note: ";
			cin.getline(myNote.noteCipher, NOTE_SIZE);         // Get line

			// If the note is longer than "key" and less than "NOTE_SIZE", process it
			if (strlen(myNote.noteCipher) > key.length() && strlen(myNote.noteCipher) < NOTE_SIZE)
			{
				myNote.month = mm;
				myNote.day = dd;
				myNote.year = yyyy;

				decode.setAll(0, key, myNote.noteCipher);                             // Decode the note with the user's key

				strncpy_s(myNote.noteCipher, decode.getFinalText().c_str(), NOTE_SIZE);
				
				cout << myNote.noteCipher << endl;                                     // Display the note as cipher text

				fstream newUser(file, ios::out | ios::trunc | ios::binary);            // Create fstream's object
				
				newUser.write(reinterpret_cast<char *>(&myNote), sizeof(myNote));      // Write the structure to a file
				
				newUser.close();                                                       // Close the file
				
				cout << "Complete seved to the file" << endl;                          // Display complete to save the file
				system("pause");
			}
			else{
				// If the input note is invalid, display the messages
				cout << "!!Your note must has at least " << key.length() << " character";
				cout << "!! or must be shorter than " << NOTE_SIZE << " characters";
				system("pause");
			}
		}
	}
	else{
		// If the note on the date is not existed
		// Let user enter a note
		cout << "Enter your note: ";
		cin.getline(myNote.noteCipher, NOTE_SIZE);

		if (strlen(myNote.noteCipher) > key.length() && strlen(myNote.noteCipher) < NOTE_SIZE)
		{
			myNote.month = mm;
			myNote.day = dd;
			myNote.year = yyyy;
			
			decode.setAll(0, key, myNote.noteCipher);                              // Decode the note
			
			strncpy_s(myNote.noteCipher, decode.getFinalText().c_str(), NOTE_SIZE);
			cout << myNote.noteCipher << endl;      // Display note as cipher text
			
			fstream newUser(file, ios::out | ios::trunc | ios::binary);
			
			newUser.write(reinterpret_cast<char *>(&myNote), sizeof(myNote));      // Write the note to a file
			
			newUser.close();
			
			cout << "Complete seved to the file" << endl;                          // Complete seved message
			system("pause");
		}
		else{
			// If the note is not followed the structure, display it
			cout << "!!Your note must has at least " << key.length() << " character";
			cout << "!! or must be shorter than " << NOTE_SIZE << " characters";
			system("pause");
		}
	}
}

//*********************************************************************
// Definition of Note::findExistedFile. The parameters is fileName.   *
// It return true if the fileName is existed                          *
// Return false if it is not existed                                  *
//*********************************************************************
bool Note::findExistedFile(string fileName){
	ifstream nameFile;
	// Open the file.
	nameFile.open(fileName);
	// If the file successfully opened, process it.
	if (nameFile.fail())
		return false;
	else
		return true;

	nameFile.close();
}

//************************************************************************************
// Definition of Note::viewAndExportANote. The parameters are a date(mm,dd,yyyy)     *
// It displays the note on the date within a file and allow the user                 *
// to export the note to a new file.                                                 *
//************************************************************************************
void Note::viewAndExportANote(int mm, int dd, int yyyy){
	string newFileName, file;    // To hold file name
	char  YesOrNo;               // To hold Y or N
	ofstream newFile;

	file = fileName(folderName, dateAsStr(mm, dd, yyyy));  // Get filename 
	
	// If the "file" is existed, process it
	if (findExistedFile(file))
	{
		cout
			<< "\t                ******************************** " << endl
			<< "\t                *         Daily report         * " << endl
			<< "\t                ******************************** " << endl << endl;

		printWritedNote(dateAsStr(mm, dd, yyyy));
		
		// Ask for saving the note to a new file that the user can choose the file name
		cout
			<< endl
			<< "       __________________________________________________________________" << endl << endl
			<< "         Do you want to save the report? ";

		YesOrNo = getYorN();
		// If the user want to export the note
		if (YesOrNo == 'y' || YesOrNo == 'Y')
		{
			// Ask for a file name
			cout << "         What file do you want to output the report? ";
			getline(cin, newFileName);      // Get the file name

			file = newFileName;

			newFile.open(file);

			// Cheak the fileName is able to use create a file or not. While invalid name, process it
			while (!newFile)
			{
				cout
					<< "\tThe program failed to use the name file: \"" << newFileName << "\". " << endl
					<< "\tPlease enter another name: ";

				getline(cin, newFileName);
				file = newFileName;

				// Open a file
				newFile.open(file);
			}
			// Write to fileName
			newFile
				<< "\t                ******************************** " << endl
				<< "\t                *         Daily report         * " << endl
				<< "\t                ******************************** " << endl;

			// Calling printWritedNote(). It takes ofstream as its argumrment, so it is able to write the note to a new file
			printWritedNote(dateAsStr(mm, dd, yyyy), newFile);

			newFile.close();
		}
	}
	else{
		// If the input dateAsStr.txt is not existed, process it to show message
		cout
			<< "         !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl
			<< "         !!  Do not have any record on " << setw(9) << mm << "/" << dd << "/" << yyyy << "  !!" << endl
			<< "         !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

		cout << "\n         Hit ENTER to back to the main manu: ";
		cin.ignore();
	}
}

//***********************************************************************************
// Definition of Note::printWritedNote. The parameters are dateAsStr as string and  *
// ostream reference. If the ostream open, it will write a note to a file           *
// If not, it will print the note to the monitor                                    *
//***********************************************************************************
void Note::printWritedNote(string dateAsStr, ostream&os){
	fstream userData;
	userData.open(fileName(folderName, dateAsStr), ios::in | ios::binary);

	// UserDate cannot open, process it
	if (!userData){
		os << "\n\t!!!The program not found your note on " << dateAsStr;
	}
	else{
		userData.read(reinterpret_cast<char *>(&myNote), sizeof(myNote));    // Read structure form file
		os << "Record on " << dateAsStr << endl;
		encode.setAll(1, key, myNote.noteCipher);
		os << "\t" << encode.getFinalText() << endl << endl;
	}
	userData.close();
}

//*****************************************************************************
// Definition of Note::editSingleWord. The parameters are a date(mm,dd,yyyy)  * 
// The user can edit the note on the date and save the edited note            *
//*****************************************************************************
void Note::editSingleWord(int mm, int dd, int yyyy){
	fstream userData;
	string wordStr, noteStr = "";
	int count = 0;                               // To hold the number of words in a note
	int index = 0;                               // To hold the number of words which is repeating in the note
	char select, YesOrNo;
	
	SearchableVector<string> wordsTable(40);    // To hold words as string in the SearchableVector's object, its function is alike vector
	BinaryTree<string> wordsTree;               // Use to search for a word
	
	userData.open(fileName(folderName, dateAsStr(mm, dd, yyyy)), ios::in | ios::binary);    // Open a file to read
	
	if (!userData){
		cout << "\n\t!!!The program not found your note on " << dateAsStr(mm, dd, yyyy) << endl;
	}
	else{
		userData.read(reinterpret_cast<char *>(&myNote), sizeof(myNote));
		encode.setAll(1, key, myNote.noteCipher);
		
		
		istringstream is(encode.getFinalText());
		istream_iterator<string> isIter(is), end;

		// Store word by word in wordsTable[] and count for number of words
		for (; isIter != end; ++isIter){
			wordsTree.insertNode(*isIter);
			wordsTable[count] = *isIter;
			count++;
		}

		cout << endl;
		
		// Display the note
		cout << "These is your note:\n\20";
		for (int i = 0; i < count; i++)
			cout << wordsTable[i] << " ";

		// Ask for the wands that user want to edit
		cout << "\n\n   \20Which word do you want to edit: ";
		cin >> wordStr;  cin.ignore();
		system("cls");

		// If the word is in the note, process it
		if (wordsTree.searchNode(wordStr)){
			cout << endl;
			// Display how many time the word isrepeated in the note
			cout << "The word \""<< wordStr << "\" is repeating " << wordsTree.IsTheNodeRepeating(wordStr)
				<< (wordsTree.IsTheNodeRepeating(wordStr) > 1 ? " times" : " time") << " in the note" << endl << endl;
			
			// If the word is repeated more than 1 time, allow the user to select the word which is been looking for.
			if (wordsTree.IsTheNodeRepeating(wordStr) > 1){
				do{
					index = wordsTable.findItem(wordStr, index, count);
					if (index != -1){
						for (int i = 0; i < count; i++){
							if (i == index){
								cout << "[" << wordsTable[i] << "] ";    // Basket the select word
							}
							else
								cout << wordsTable[i] << " ";
						}

						// Hit enter to select another word, or type some thing to select the word
						cout << endl << "Hit ENTER to skip the word: ";
						cin.get(select);
						if (select == '\n'){
							index++;
						}
					}
					else if (index == -1){
						cout << "\t\aNo any word selected!!" << endl;
						index = 0;
					}
				} while (select == '\n');

				cin.ignore(80, '\n');

				cout << endl;

				// Ask for a new words to replace
				cout << "\20What is a new words you want to replace? ";
				getline(cin, wordStr);

				wordsTable[index] = wordStr;

				cout << endl;
				cout << "These is your note:\n\20";
				for (int i = 0; i < count; i++)
					cout << wordsTable[i] << " ";
			}
			// If the word appeared once, process it
			else if (wordsTree.IsTheNodeRepeating(wordStr) == 1){
				index = wordsTable.findItem(wordStr, index, count);
				
				cout << "\20What is a new words you want to replace? ";
				getline(cin, wordStr);
				
				wordsTable[index] = wordStr;
				
				cout << endl;
				cout << "These is your note:\n\20";
				
				for (int i = 0; i < count; i++)
					cout << wordsTable[i] << " ";

				cout << endl;

			// Ask for saving edited note
			}
			cout
				<< endl
				<< "       __________________________________________________________________" << endl << endl
				<< "         Do you want to save the changed? ";

			YesOrNo = getYorN();                          // Get Y or N from input
			if (YesOrNo == 'y' || YesOrNo == 'Y'){
				for (int i = 0; i <= count; i++){
					noteStr += wordsTable[i] + " ";
				}
				userData.close();
				
				fstream userData(fileName(folderName, dateAsStr(mm, dd, yyyy)), ios::out | ios::binary);
				
				decode.setAll(0, key, noteStr);                                        // Decode the note
				
				strncpy_s(myNote.noteCipher, decode.getFinalText().c_str(), NOTE_SIZE);		
				
				userData.write(reinterpret_cast<char *>(&myNote), sizeof(myNote));     // Write note structure to file
				
				// Display complete to save
				cout
					<< endl
					<< "          =====================" << endl
					<< "          =       SAVED       =" << endl
					<< "          =====================" << endl; 
			}
		}
		else
			cout << "The program cannot find \"" << wordStr << "\"in the note!! ";
	}
	cout << endl;
	system("pause");
	userData.close();
}

//**********************************************************************************
// Definition of Note::noteOnDateIsExist. The parameters are a date(mm,dd,yyyy)    *
// It calls findExistedFile() to checks the file on the date is existed or not     *
// Return true if the note on the date is existed.                                 *
// Return fasle if not                                                             *
//**********************************************************************************
bool Note::noteOnDateIsExist(int mm, int dd, int yyyy){
	return findExistedFile(fileName(folderName, dateAsStr(mm, dd, yyyy)));
}

//********************************************************
// Definition of Note::getYorN. It gets only 'Y', 'y',   *
// 'N',and 'n' character from input                      *
// Return Y or N                                         *
//********************************************************
char Note::getYorN()
{
	char select;

	cin >> select;  cin.ignore(80, '\n');

	// while a input character is not looking for characters, it is still asks for a right one
	while (!(select == 'y' || select == 'n' || select == 'Y' || select == 'N'))
	{
		cout << "\tPlease type only Yes or No :";
		cin >> select;  cin.ignore(80, '\n');
	}
	return select;
}

//***************************************************************************************
// Definition of Note::viewAndExportNotes. The parameters are a start date(mm,dd,yyyy)  *
// and end date (mm,dd,yyyy)                                                            *
// It displays the note between the dates within a file and allows the user             *
// to export the note to a new file.                                                    *
//***************************************************************************************
void Note::viewAndExportNotes(int sMonth, int sDate, int sYear, int eMonth, int eDate, int eYear){
	ofstream newFile;
	char  YesOrNo;                                               // To hold Y or N
	const int SIZE_OF_ARRAYS = 31;
	string file, aDate, newFileName;
	string dateFile[SIZE_OF_ARRAYS];
	string startDate = dateAsStr(sMonth, sDate, sYear),         // To hold start date and end date as strings
		endDate = dateAsStr(eMonth, eDate, eYear);

	int count = 0;
	int daysInMonths[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	for (int i = sYear; i <= eYear; i++){
		for (int f = sMonth; f <= eMonth; f++){
			for (int d = sDate; d <= daysInMonths[f - 1]; d++) {

				aDate = dateAsStr(f, d, i);
				file = fileName(folderName, dateAsStr(f, d, i));
				// If a note on the date is existed, keep the date in dateFile array
				if (findExistedFile(file)) {
					dateFile[count] = aDate;
					count++;
				}
			}
		}
	}

	// If no any record betwen the dates, process it
	if (count == 0){
		cout
			<< "          !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl
			<< "          !!  Do not have any record during " << setw(10) << startDate << " and " << endDate << "." << "  !!" << endl
			<< "          !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	}
	else{
		// Display how many record between the dates
		cout
			<< "\t               The program found " << setw(2) << count << (count == 1 ? " note " : " notes ") << "record." << endl
			<< "\t                   between " << startDate << " and " << endDate << "." << endl << endl;

		// Print all note between the dates
		for (int i = 0; i < count; i++){
			printWritedNote(dateFile[i]);
			cout << endl;
		}

		// Ask to save the report
		cout
			<< endl
			<< "       __________________________________________________________________" << endl << endl
			<< "         Do you want to save the report? ";

		YesOrNo = getYorN();
		if (YesOrNo == 'y' || YesOrNo == 'Y')
		{
			// Ask for the file name
			cout << "         What file do you want to output the report? ";
			getline(cin, newFileName);

			file = newFileName;

			newFile.open(file);

			// Cheak the fileName is able to use create a file or not. While invalid name, process it
			while (!newFile){
				cout
					<< "\tThe program failed to use the name file: \"" << newFileName << "\". " << endl
					<< "\tPlease enter another name: ";

				getline(cin, newFileName);
				file = newFileName;

				// Open a file
				newFile.open(file);
			}
			// Write to fileName
			newFile
				<< "\t             ****************************************** " << endl
				<< "\t             *    Report during" << setw(10) << startDate << " and " << endDate << "." << "  !!  *" << endl << endl
				<< "\t             ****************************************** " << endl;

			for (int i = 0; i < count; i++){
				printWritedNote(dateFile[i], newFile);
				cout << endl;
			}

			newFile.close();
			
			// Display compleate to save the file
			cout
				<< "\t                 ------------------------------" << endl
				<< "\t                 - Completed seve to the file -" << endl
				<< "\t                 ------------------------------" << endl << endl;
			system("pause");
		}
	}
}


