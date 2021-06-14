#include <iostream>
#include <windows.h>
#include <cstring>
#include<fstream>
#include <string>

using namespace std;

// Declaration of struct for Statistics. 

struct Statistics {
	int wordCount;
	int longestWord;
	int shortestWord;
	int numChars;
};

// Declarations of functions in GivenFunctions.cpp.

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
	
	int length = 0, shift = 0, i = 0;
	char add;
	int bits[8];
	int temp;
	char ch;
	
	ofstream out;
	out.open(filename); 
			
	length = strlen(document);
	shift = length % 4 + 1;
	
	for (i = 0; i < length; i = i + 1){
		add = document[i] + shift;
		
		charToByte (bits, add);
		temp = bits[3]; 
		bits[3] = bits[4]; 
		bits[4] = temp;
		
		ch = byteToChar (bits);
		
		out << ch ;
		
	}
	out << endl;	
	out.close();

	displayText ("Encrypting ...", "Encrypt");
}


// This function accepts two C-strings as parameters, document and filename.
// It opens the file specified by filename. It reads each character from the
// file and stores it in the document C-string. The characters in the
// document C-string are then decrypted using an algorithm that reverses the
// encryption algorithm.
 
void decrypt (char document[], char filename[]) {
	
	int length = 0, i;
	int bits[8];
	int shift = 0;
	char ch;
	int temp = 0;
	
	ifstream in;
	in.open(filename);
	
	// if statement to check whether the input file was successfully opened.
	if (!in.is_open())
	{
		displayText ("File not found ...", "Error");
		exit(1);
	}
	
	length = 0;
	in >> ch;
	while(!in.eof())
	{
    	document[length] = ch;
    	in >> ch;
		length = length + 1;
	}
	
	document[length] = '\0';
	shift = length % 4 + 1;
	
	for (i = 0; i < length; i = i + 1){
		
		charToByte (bits, document[i]);
		temp = bits[3]; 
		bits[3] = bits[4]; 
		bits[4] = temp;
		
		ch = byteToChar (bits);
		document[i] = ch - shift;
	}
	
	in.close();
	displayText ("Decrypting ...", "Decrypt");
	
}


// This function accepts the dictionary (array of string) as its only
// parameter. It opens the dictionary file and reads all the words and
// stores them in the dictionary array. It returns the amount of words 
// stored in the dictionary array. All the words in the dictionary are 
// in lowercase.

int readWordsDictionary(string dictionary[]) {
	
	string words;
	ifstream in;
	in.open("dictionary.txt");
		
	// if statement to check whether the input file was successfully opened.
	
	if (!in.is_open())
	{
		displayText ("File not found ...", "Error");
		exit(1);
	}
	int i = 0;
	
	in >> words;
	
	while (!in.eof()){
		
		dictionary[i] = words;
		in >> words;
		i = i + 1;
	}
	
	displayText ("Reading words from dictionary.txt ...", "Dictionary");
	
	in.close();
	
	return i;
}


// This function accepts the dictionary as a parameter as well as a C-string containing
// the characters of the document. It checks the spelling of all the words that come after 
// location start in the document C-string. If an incorrectly spelt word is encountered, 
// it is copied to the C-string errorWord and the function terminates by returning the 
// starting location of the word that has been spelt incorrectly. If there are no spelling 
// errors, the function must return -1.

int checkSpelling (string dictionary[], int numWords, char document[], int start, char errorWord[]) { 
	
	int i =0, length = 0 , lenKey = 0, j = 0, position = 0, lenErr = 0, compare = 0;
	char word[100];
	char error[100];
	 
	
	length = strlen(document);
	
	 
	start = getWord(document, start, word);
	toLowerCase(word);
	while (start > 0) {
		
		string SWord(word);
		lenKey = SWord.length();;
		
		for (i = 0; i < numWords; i = i + 1){
			
			if (SWord != dictionary[i]  && (i + 1 == numWords)){
				position = start - lenKey;
			
				toCString (SWord, error);
				lenErr = strlen(error);
				for (j = 0; j < lenErr; j = j + 1)
					errorWord[j] = error[j];
					
				return position;
			} else if(SWord == dictionary[i]){
				break;
			}
		}
		start = getWord(document, start, word);
		toLowerCase(word);
	}

	displayText ("Searching for spelling errors ...", "Check Spelling");

	return -1;
}


// This function is similar to the checkSpelling function. It searches the entire document 
// C-string for incorrectly spelt words. Whenever an incorrectly spelt word is encountered,
// it is inserted in the array of errorWords which was passed as a parameter. The function 
// returns the amount of words that were incorrectly spelt in the document.

int checkSpellingAll (string dictionary[], int numWords, char document[], string errorWords[]) {
        
    int i =0, length = 0 , lenKey = 0, j = 0, position = 0, lenErr = 0, compare = 0, start = 0, count = 0;
	char word[100];
	char error[100];
	 
	
	length = strlen(document);
	 
	start = getWord(document, start, word);
	toLowerCase(word);
	while (start > 0) {
		
		string SWord(word);
		lenKey = SWord.length();;
		
		for (i = 0; i < numWords; i = i + 1){
			
			if (SWord != dictionary[i]  && (i + 1 == numWords)){
				position = start - lenKey;
			
				errorWords[count] = SWord;
				count = count + 1;
					
			} else if(SWord == dictionary[i]){
				break;
			}
		}
		start = getWord(document, start, word);
		toLowerCase(word);
	}

	displayText ("Searching for spelling errors ...", "Check Spelling");

	return count ;
}


// This function searches the document C-string to find the 
// keyWord C-string, starting from location start. If the keyWord 
// substring is found in the document C-string, it returns the 
// starting location where it was found. Otherwise, it returns -1.

int searchWord (char document[], int start, char keyWord[]) { 

 int i =0, length = 0 , lenKey = 0, j = 0, position = 0;
 char word[100];
 
 
 length = strlen(document);
 lenKey = strlen(keyWord);
 
 	start = getWord(document, start, word);
	while (start > 0) {
	
		toLowerCase(keyWord);
		toLowerCase(word);
		if (strcmp(word, keyWord) == 0){
	
				position = start - lenKey;
			
			return position;
			
		 }else
			start = getWord(document, start, word);
			
		}
	
	displayText ("Searching for word ...", "Search");
	
	return -1;
	
}


// This function accepts the document C-string as a parameter, analyses it, and stores 
// the results of the analysis in a Statistics struct. This struct is then returned to 
// the caller.

Statistics getStatistics (char document[]) {

    Statistics result;
    int i =0, start = 0, length = 0, numWords = 0,wordLen =0, longest = INT_MIN, shortest = INT_MAX;
	char word[100];
	int end = 0;
	char prev = ' ';
	
	displayText ("Generating statistics ...", "Statistics");
	
	result.wordCount = 0; 
	result.longestWord = 0; 
	result.shortestWord = 0;
	result.numChars = 0; 
	
	length = strlen(document);
	
	for(int j = 0; j < length; j = j + 1){
		if(document[j] != ' ' && prev == ' '){
			numWords = numWords + 1;
		}	
       
        prev = document[j];
	}
	
	while (i < length){
		start = getWord (document, start, word);
		wordLen = strlen(word);
		
		
			
		wordLen = strlen(word);
		if (wordLen > longest){
			longest = wordLen;
		}
		if (wordLen < shortest){
			shortest = wordLen;
		}
		
		i = i + 1;
	}
		
	if (numWords == 0 ){
		numWords = 0;
		longest = 0;
		shortest = 0;
		i = 0;
	}	
		
	result.wordCount = numWords;
	result.longestWord = longest;
	result.shortestWord = shortest;
	result.numChars = i;	

	return result;
}


