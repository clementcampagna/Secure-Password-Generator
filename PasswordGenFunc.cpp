#include <iostream>

using namespace std;

void displayHelp(void)
{
	cout << "\nThis password generator uses MS Windows rand_s function to generate secure seeds before "
		<< "providing new passwords to the user. It is a lightweight console based application which "
		<< "works on Windows XP and later. Users can choose to run this program by simply double-clicking "
		<< "its executable or to call it using a list of predefined parameters shown below:";

	cout << "\n\n--passwordlength <int>, -pl <int> ( e.g. 8, minimum: 6, default: 16 )" << endl
		<< "usage: PasswordGen.exe --passwordlength 8" << endl
		<< "or" << endl
		<< "usage: PasswordGen.exe -pl 8" << endl << endl;

	cout << "--excludesymbols, -es ( i.e. !@#$%&*+-= )" << endl
		<< "usage: PasswordGen.exe --excludesymbols" << endl
		<< "or" << endl
		<< "usage: PasswordGen.exe -es" << endl << endl;

	cout << "--excludenumbers, -en ( i.e. 0123456789 )" << endl
		<< "usage: PasswordGen.exe --excludenumbers" << endl
		<< "or" << endl
		<< "usage: PasswordGen.exe -en" << endl << endl;

	cout << "--excludelowercasecharacters, -elcc ( e.g. abcdefgh )" << endl
		<< "usage: PasswordGen.exe --excludelowercasecharacters" << endl
		<< "or" << endl
		<< "usage: PasswordGen.exe -elcc" << endl << endl;

	cout << "--excludeuppercasecharacters, -eucc ( e.g. ABCDEFGH )" << endl
		<< "usage: PasswordGen.exe --excludeuppercasecharacters" << endl
		<< "or" << endl
		<< "usage: PasswordGen.exe -eucc" << endl << endl;

	cout << "--excludesimilarcharacters, -esc (i.e. i, l, I, L, 1, o, O, 0)" << endl
		<< "usage: PasswordGen.exe --excludesimilarcharacters" << endl
		<< "or" << endl
		<< "usage: PasswordGen.exe -esc" << endl << endl;
		
	cout << "--excludeambiguouscharacters, -eac ( i.e. {}[]()/?|\\'\"`~,;:.^<> )" << endl
		<< "usage: PasswordGen.exe --excludeambiguouscharacters" << endl
		<< "or" << endl
		<< "usage: PasswordGen.exe -eac" << endl << endl;

	cout << "--help, -h ( displays this list of commands in console )" << endl
		<< "usage: PasswordGen.exe --help" << endl
		<< "or" << endl
		<< "usage: PasswordGen.exe -h" << endl << endl;

	cout << "Example: to generate a new password comprised of 10 characters which exclude both "
		<< "numbers and symbols but include everything else, you would use:" << endl << endl

		<< "PasswordGen.exe --passwordlength 10 --excludenumbers --excludesymbols" << endl
		<< "or" << endl
		<< "PasswordGen.exe -pl 10 -en -es";
}
