#include <iostream>
#include <windows.h>
#include <cstring>
#include<fstream>
	using namespace std;

// Declaration of struct for Statistics. Do not modify.

struct Statistics {
	int wordCount;
	int longestWord;
	int shortestWord;
	int numChars;
};

// Declarations of functions in GivenFunctions.cpp. Do not modify.

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

// Declarations of functions for Assignment #2. Do not modify.

void encrypt (char document[], char filename[]);
void decrypt (char document[], char filename[]);
int readWordsDictionary(string dictionary[]);
int checkSpelling (string dictionary[], int numWords, char document[], int start, char errorWord[]);
int checkSpellingAll (string dictionary[], int numWords, char document[], string errorWords[]);
int searchWord (char document[], int start, char keyWord[]);
Statistics getStatistics (char document[]);


// This function accepts two C-string parameters, document and filename.
// It opens the file specified by filename.  It then encrypts each character 
// in the document C-string using the encryption algorithm and stores it 
// in the file.

void encrypt (char document[], char filename[]) {

	displayText ("Encrypting ...", "Encrypt");
}


// This function accepts two C-strings as parameters, document and filename.
// It opens the file specified by filename. It reads each character from the
// file and stores it in the document C-string. The characters in the
// document C-string are then decrypted using an algorithm that reverses the
// encryption algorithm.
 
void decrypt (char document[], char filename[]) {
	
	displayText ("Decrypting ...", "Decrypt");
	
}


// This function accepts the dictionary (array of string) as its only
// parameter. It opens the dictionary file and reads all the words and
// stores them in the dictionary array. It returns the amount of words 
// stored in the dictionary array. All the words in the dictionary are 
// in lowercase.

int readWordsDictionary(string dictionary[]) {

	displayText ("Reading words from dictionary.txt ...", "Dictionary");
	
	return 0;
}


// This function accepts the dictionary as a parameter as well as a C-string containing
// the characters of the document. It checks the spelling of all the words that come after 
// location start in the document C-string. If an incorrectly spelt word is encountered, 
// it is copied to the C-string errorWord and the function terminates by returning the 
// starting location of the word that has been spelt incorrectly. If there are no spelling 
// errors, the function must return -1.

int checkSpelling (string dictionary[], int numWords, char document[], int start, char errorWord[]) {
    
	displayText ("Searching for spelling errors ...", "Check Spelling");

	return -1;
}


// This function is similar to the checkSpelling function. It searches the entire document 
// C-string for incorrectly spelt words. Whenever an incorrectly spelt word is encountered,
// it is inserted in the array of errorWords which was passed as a parameter. The function 
// returns the amount of words that were incorrectly spelt in the document.

int checkSpellingAll (string dictionary[], int numWords, char document[], string errorWords[]) {
    
	displayText ("Searching for spelling errors ...", "Check Spelling");

	return 0;
}


// This function searches the document C-string to find the 
// keyWord C-string, starting from location start. If the keyWord 
// substring is found in the document C-string, it returns the 
// starting location where it was found. Otherwise, it returns -1.

int searchWord (char document[], int start, char keyWord[]) {

	displayText ("Searching for word ...", "Search");
	
	return -1;
	
}


// This function accepts the document C-string as a parameter, analyses it, and stores 
// the results of the analysis in a Statistics struct. This struct is then returned to 
// the caller.

Statistics getStatistics (char document[]) {

    Statistics result;

	displayText ("Generating statistics ...", "Statistics");
	
	result.wordCount = 0;
	result.longestWord = 0;
	result.shortestWord = 0;
	result.numChars = 0;
	
	return result;
}
