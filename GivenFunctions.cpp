#include <iostream>
#include <windows.h>
#include <cstring>
#include<fstream>
	using namespace std;

void toCString (string s, char c[]);
void displayText (string message, string title);
void displayText2 (char s[], char title[]);
bool isLetter (char ch);
void toUpperCase(char s[]);
void toLowerCase(char s[]);
int getCharacters(char data[], char filename[]);
int getWord (char data[], int start, char word[]);
char byteToChar (int bits[]);
void charToByte (int bits[], char ch);


// This function converts a variable of type string to a C-string.

void toCString (string s, char c[]) {

	int length = s.length();
	
	for (int i=0; i<length; i=i+1) 
		c[i] = s[i];
	
	c[length] = '\0';
}


// This function displays the message passed as a parameter on a
// pop-up window. The message is of type string.

void displayText (string m, string t) {
	char message[100];
	char title[100];
	
	toCString(m, message);
	toCString(m, title); 
	
	MessageBox(NULL, message, title, MB_ICONEXCLAMATION | MB_OK);
}


// This function displays the message passed as a parameter on a
// pop-up window. The message is a C-string.

void displayText2 (char message[], char title[]) {
	
	MessageBox(NULL, message, title, MB_ICONEXCLAMATION | MB_OK);
}
 

// This function returns true if the character passed as a 
// parameter is a letter, or false, otherwise.

bool isLetter (char ch) {

	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return true;
	else
		return false;
}


// This function accepts a C-string as a parameter and converts
// all the lowercase letters (if any) to uppercase letters.

void toUpperCase(char s[]) {
   int i;
   
   i = 0;
   while (s[i] != '\0') {
   		if (s[i] >= 'a' && s[i] <= 'z')
   			s[i] = s[i] - ' ';
   		i = i + 1;
   	}
}


// This function accepts a C-string as a parameter and converts
// all the uppercase letters (if any) to lowercase letters.

void toLowerCase(char s[]) {
   int i;
   
   i = 0;
   while (s[i] != '\0') {
   		if (s[i] >= 'A' && s[i] <= 'Z')
   			s[i] = s[i] + ' ';
   		i = i + 1;
   	}
}


// This function accepts two C-strings as parameters, data and 
// filename. It opens the file with the given name and reads all
// the characters in the file and stores them in the data C-string.

int getCharacters(char data[], char filename[]) {
 
 	ifstream encryptedFile;
 	char ch;
 	int i;

 	encryptedFile.open(filename);
 	
	if (!encryptedFile.is_open()) {
		string message = "File could not be opened for reading.";
		string title = "File Error";
		displayText(message, title);
		return -1;
	}

	i = 0;
	encryptedFile >> noskipws;
	
	encryptedFile >> ch;
	while (!encryptedFile.eof()) {
		data[i] = ch;
		i = i + 1;
		encryptedFile >> ch;
	}
	
	data[i] = '\0';
	
	encryptedFile.close();
	
	return i;
}


// This function accepts two C-strings, data and word, as
// parameters. It also accepts an integer, start, as a
// parameter. From location start, it finds the first word 
// in data and stores it in word. It returns the location of
// the character that comes after the word in the data C-string.
// If it does not find a word, it returns 0.

int getWord (char data[], int start, char word[]) {

    int i, j, size;
    
    size = strlen(data);
    
    i = start;
    
    while (i < size && (!isLetter(data[i])))
          i = i + 1;      

    if (i == size)
          return 0;

    j = 0;
    while (isLetter(data[i])) {
          word[j]= data[i];
          i = i + 1;
          j = j + 1;
    }      

    word[j]= '\0';
    
    return i;
}


// This function accepts an integer array of eight 1's and 0's
// containing the byte representation of an ASCII character
// and returns the actual ASCII character.

char byteToChar (int bits[]) {
	int i, sum, power2;
	
	sum = 0;
	power2 = 1;
	
	for (i=0; i<8; i=i+1) {
		sum = sum + bits[i] * power2;
		power2 = power2 * 2;
	}
	
	return sum;
}


// This function accepts an ASCII character as a parameter
// and finds the 8-bit (byte) representation of the character.
// The byte representation is stored in the bits array.

void charToByte (int bits[], char ch) {
	int charValue, i, remainder;
	
	charValue = ch;
	
	for (i=0; i<8; i=i+1)
		bits[i] = 0;
		
	i = 0;
	
	while (charValue != 0) {
		remainder = charValue % 2;
		charValue = charValue / 2;
		bits [i] = remainder;
		i = i + 1;
	}
}
