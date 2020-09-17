# Secure Password Generator

This password generator uses MS Windows rand_s function to generate secure seeds before providing new passwords to the user.\
\
It is a lightweight console based application which works on Windows XP and later.\
\
Users can choose to run this program by simply double-clicking its executable or to call it using a list of predefined parameters as shown below.

### Usage:

```
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
```

### Development:

Want to contribute? Great, Secure Password Generator is open-source!\
\
Please feel free to clone this repository, fork it, make changes to the code, submit pull requests, raise issues, and/or email me using the address below for any suggestions, questions or remarks you may have.

### Contact Information:

Author's email address: clementcampagna+github@gmail.com\
Author's website: https://clementcampagna.com
