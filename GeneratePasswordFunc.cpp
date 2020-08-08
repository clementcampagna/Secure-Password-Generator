#define _CRT_RAND_S

#include <iostream>
#include <string>

using namespace std;

inline char _generatePassword(string charset)
{
	errno_t err;
	unsigned int seed;
	char newPasswordChar;

	//generates a new secure pseudorandom (unsigned int) number stored in seed, err will return != 0 if rand_s function fails
	err = rand_s(&seed);

	if (err == 0)
	{
		//the next line picks a char in the range [0, length of charset] determined using the seed's value
		newPasswordChar = charset[(unsigned int)((double)seed / ((double)UINT_MAX + 1) * (charset.length()))];

		return newPasswordChar;
	}
	else
	{
		cout << endl << "Error: unable to generate new password. The rand_s function failed!"
			<< endl << endl << "Exiting now.";
		exit(EXIT_FAILURE);
	}
}

string generatePassword(const int passwordLength, const bool excludeSymbols, const bool excludeNumbers, const bool excludeLowerCaseCharacters, const bool excludeUpperCaseCharacters, const bool excludeSimilarCharacters, const bool excludeAmbiguousCharacters)
{
	string newPassword(passwordLength, 0), charset = "";

	if (!excludeSymbols)
		charset = "!@#$%&*+-=";

	if (!excludeNumbers && !excludeSimilarCharacters)
		charset += "0123456789";

	if (!excludeNumbers && excludeSimilarCharacters)
		charset += "23456789";

	if (!excludeLowerCaseCharacters && !excludeSimilarCharacters)
		charset += "abcdefghijklmnopqrstuvwxyz";

	if (!excludeLowerCaseCharacters && excludeSimilarCharacters)
		charset += "abcdefghjkmnpqrstuvwxyz";

	if (!excludeUpperCaseCharacters && !excludeSimilarCharacters)
		charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (!excludeUpperCaseCharacters && excludeSimilarCharacters)
		charset += "ABCDEFGHJKMNPQRSTUVWXYZ";

	if (!excludeAmbiguousCharacters)
		charset += "{}[]()/?|\\'\"`~,;:.^<>";

	for (int i = 0; i < passwordLength; i++) //repeats the following instructions until full length of the password has been generated
			newPassword[i] += _generatePassword(charset);
	
	return newPassword;
}
