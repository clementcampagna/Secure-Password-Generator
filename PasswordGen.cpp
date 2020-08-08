/*
	.NOTES
	===========================================================================
	Created with: Microsoft Visual Studio Enterprise 2019
	Created on: 01-Sep-19 09:02 P.M.
	Created by: Clement Campagna (https://github.com/clementcampagna)
	Tested on: Microsoft Windows 10 Professional 1903 (x64)
	Project name: Secure Password Generator
	Internal name: PasswordGen
	License: MIT License

	Copyright(c) 2019 Clement Campagna

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

	===========================================================================
	.DESCRIPTION
	This password generator uses MS Windows rand_s function to generate secure seeds before
	providing new passwords to the user. It is a lightweight console based application which
	works on Windows XP and later. Users can choose to run this program by simply double-clicking
	its executable or to call it using a list of predefined parameters shown below:

	--passwordlength <int>, -pl <int> ( e.g. 8, minimum: 6, default: 16 )
	usage: PasswordGen.exe --passwordlength 8
	or
	usage: PasswordGen.exe -pl 8

	--excludesymbols, -es ( i.e. !@#$%&*+-= )
	usage: PasswordGen.exe --excludesymbols
	or
	usage: PasswordGen.exe -es

	--excludenumbers, -en ( i.e. 0123456789 )
	usage: PasswordGen.exe --excludenumbers
	or
	usage: PasswordGen.exe -en

	--excludelowercasecharacters, -elcc ( e.g. abcdefgh )
	usage: PasswordGen.exe --excludelowercasecharacters
	or
	usage: PasswordGen.exe -elcc

	--excludeuppercasecharacters, -eucc ( e.g. ABCDEFGH )
	usage: PasswordGen.exe --excludeuppercasecharacters
	or
	usage: PasswordGen.exe -eucc

	--excludesimilarcharacters, -esc ( i.e. i, l, I, L, 1, o, O, 0 )
	usage: PasswordGen.exe --excludesimilarcharacters
	or
	usage: PasswordGen.exe -esc

	--excludeambiguouscharacters, -eac ( i.e. {}[]()/?|\\'\"`~,;:.^<> )
	usage: PasswordGen.exe --excludeambiguouscharacters
	or
	usage: PasswordGen.exe -eac

	--help, -h ( displays this list of commands in console )
	usage: PasswordGen.exe --help
	or
	usage: PasswordGen.exe -h

	Example: to generate a new password comprised of 10 characters which exclude both
	numbers and symbols but include everything else, you would use:

	PasswordGen.exe --passwordlength 10 --excludenumbers --excludesymbols
	or
	PasswordGen.exe -pl 10 -en -es
*/

#include <iostream>
#include <string>
#include "PasswordGenFunc.h"
#include "GeneratePasswordFunc.h"

using namespace std;

inline bool caseInsCharCompareN(char a, char b) {
	return(toupper(a) == toupper(b));
}

bool caseInsCompare(const string& s1, const string& s2) {
	return((s1.size() == s2.size()) &&
		equal(s1.begin(), s1.end(), s2.begin(), caseInsCharCompareN));
}

bool is_number(const string& s)
{
	string::const_iterator it = s.begin();

	while (it != s.end() && isdigit(*it))
		++it;

	return !s.empty() && it == s.end();
}

int main(int argc, char* argv[])
{
	int passwordLength = 16; //default password length, can be changed by either using the --passwordlength or -pl parameters, or by calling PasswordGen.exe without any extra parameters
	bool excludeSymbols = false,
		excludeNumbers = false,
		excludeLowerCaseCharacters = false,
		excludeUpperCaseCharacters = false,
		excludeSimilarCharacters = false,
		excludeAmbiguousCharacters = false;

	cout << "Welcome to Secure Password Generator!" << endl;

	if (argc == 1) //no parameters other than the program name were passed, asking user for required information
	{
		string userInput;

		int keepGoing;
		do
		{
			do
			{
				cout << endl << "Enter new password length ( e.g. 8, minimum: 6 ): ";
				if (!(cin >> passwordLength))
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			} while (passwordLength < 6);

			do
			{
				cout << endl << "Exclude symbols ( i.e. !@#$%&*+-= ) <yes|no>: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> userInput;
			} while (!caseInsCompare(userInput, "yes") && !caseInsCompare(userInput, "no")); //caseInsCompare is used for case-insensitive comparisons

			if (caseInsCompare(userInput, "yes"))
				excludeSymbols = true;
			else
				excludeSymbols = false;

			do
			{
				cout << endl << "Exclude numbers ( i.e. 0123456789 ) <yes|no>: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> userInput;
			} while (!caseInsCompare(userInput, "yes") && !caseInsCompare(userInput, "no"));

			if (caseInsCompare(userInput, "yes"))
				excludeNumbers = true;
			else
				excludeNumbers = false;

			do
			{
				cout << endl << "Exclude lower case characters ( e.g. abcdefgh ) <yes|no>: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> userInput;
			} while (!caseInsCompare(userInput, "yes") && !caseInsCompare(userInput, "no"));

			if (caseInsCompare(userInput, "yes"))
				excludeLowerCaseCharacters = true;
			else
				excludeLowerCaseCharacters = false;

			do
			{
				cout << endl << "Exclude upper case characters ( e.g. ABCDEFGH ) <yes|no>: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> userInput;
			} while (!caseInsCompare(userInput, "yes") && !caseInsCompare(userInput, "no"));

			if (caseInsCompare(userInput, "yes"))
				excludeUpperCaseCharacters = true;
			else
				excludeUpperCaseCharacters = false;

			do
			{
				cout << endl << "Exclude similar characters ( i.e. i, l, I, L, 1, o, O, 0 ) <yes|no>: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> userInput;
			} while (!caseInsCompare(userInput, "yes") && !caseInsCompare(userInput, "no"));

			if (caseInsCompare(userInput, "yes"))
				excludeSimilarCharacters = true;
			else
				excludeSimilarCharacters = false;

			do
			{
				cout << endl << "Exclude ambiguous characters ( i.e. {}[]()/?|\\'\"`~,;:.^<> ) <yes|no>: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> userInput;
			} while (!caseInsCompare(userInput, "yes") && !caseInsCompare(userInput, "no"));

			if (caseInsCompare(userInput, "yes"))
				excludeAmbiguousCharacters = true;
			else
				excludeAmbiguousCharacters = false;

			if (excludeSymbols && excludeNumbers && excludeLowerCaseCharacters && excludeUpperCaseCharacters && excludeAmbiguousCharacters)
				cout << endl << "Error: you must select at least one character set!" << endl << endl;
			else
				cout << endl << "Your new password is: " << generatePassword(passwordLength, excludeSymbols, excludeNumbers, excludeLowerCaseCharacters, excludeUpperCaseCharacters, excludeSimilarCharacters, excludeAmbiguousCharacters) << endl << endl;

			cout << "To generate another password type 1, to quit type anything else: ";
			cin >> keepGoing;

		} while (keepGoing == 1);
	}
	else
	{
		for (int i = 1; i < argc; i++) //starts i at 1 to skip program name stored at argv[0]
		{
			if (_stricmp(argv[i], "--help") == 0 //_stricmp is used for case-insensitive comparisons
				|| _stricmp(argv[i], "-h") == 0)
			{
				displayHelp();
				exit(EXIT_SUCCESS);
			}

			if (_stricmp(argv[i], "--passwordlength") == 0
				|| _stricmp(argv[i], "-pl") == 0) 
			{
				if (argv[i + 1] != NULL && is_number(argv[i + 1]) && atoi(argv[i + 1]) >= 6) //checks that password length provided by user is a valid integer and greater than 5
					passwordLength = atoi(argv[i + 1]); //assigns value of argv[i + 1] to integer variable passwordLength
				else
				{
					cout << endl << "Error: incorrect use of the password length parameter!" << endl
						<< "For help, type " << argv[0] << " --help or " << argv[0] << " -h" << endl;
					exit(EXIT_FAILURE);
				}

				i++; //skips the next argument as it is the password length which has been assigned to int passwordLenght above
			}
			else
				if (_stricmp(argv[i], "--excludesymbols") == 0
					|| _stricmp(argv[i], "-es") == 0)
					excludeSymbols = true;
				else
					if (_stricmp(argv[i], "--excludenumbers") == 0
						|| _stricmp(argv[i], "-en") == 0)
						excludeNumbers = true;
					else
						if (_stricmp(argv[i], "--excludelowercasecharacters") == 0
							|| _stricmp(argv[i], "-elcc") == 0)
							excludeLowerCaseCharacters = true;
						else
							if (_stricmp(argv[i], "--excludeuppercasecharacters") == 0
								|| _stricmp(argv[i], "-eucc") == 0)
								excludeUpperCaseCharacters = true;
							else
								if (_stricmp(argv[i], "--excludesimilarcharacters") == 0
									|| _stricmp(argv[i], "-esc") == 0)
									excludeSimilarCharacters = true;
								else
									if (_stricmp(argv[i], "--excludeambiguouscharacters") == 0
										|| _stricmp(argv[i], "-eac") == 0)
										excludeAmbiguousCharacters = true;
									else
									{
										cout << endl << "Error: " << argv[i] << " is not a valid parameter!" << endl
											<< "For help, type " << argv[0] << " --help or " << argv[0] << " -h" << endl;
										exit(EXIT_FAILURE);
									}
		}

		if (excludeSymbols && excludeNumbers && excludeLowerCaseCharacters && excludeUpperCaseCharacters && excludeAmbiguousCharacters)
		{
			cout << endl << "Error: you must select at least one character set!" << endl << endl
				<< "For help, type " << argv[0] << " --help or " << argv[0] << " -h" << endl;
			exit(EXIT_FAILURE);
		}
		else
			cout << endl << "Your new password is: " << generatePassword(passwordLength, excludeSymbols, excludeNumbers, excludeLowerCaseCharacters, excludeUpperCaseCharacters, excludeSimilarCharacters, excludeAmbiguousCharacters) << endl;
	}

	cout << endl << "Goodbye!" << endl;

	return 0;
}
