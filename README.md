# My Secret Editor

--- 

## Table of Contents
- [Overview](#overview)
- [Description](#description)
- [Lanaguages tools and technologies](#lanaguages-tools-and-technologies)
- [Project](#project)
- [Author Info](#author-info)

---

## Overview 

The my secret editor program uses the C++ programming language to generate a graphical user interface to the user, which allows the user the type text into the text editor. The user can then encrypt and save the text into a file by the click of a button. The user can then fetch and decrpyt the text from to file and display the text into the text editor if needed. The user has the ability to search for any incorrectly spelt word from the beginning of the text or from the location of the cursor. The all words buttons displays all the incorrectly spelt words in the text editor to the user. The program also searches for a user specified word from the beginning of the text, or from the location of the cursor on the text editor. Lastly the user can obtain the statistics of the text in the text editor which includes:
* Number of words
* Longest word
* Shortest word
* Number of characters

--- 

## Description
* The user creates a document by typing characters into the editor. When the user is ready to save the document to a file, the file name must be entered in the field to the right of the Save File As button. The Save File As button is then clicked. The encrypt function is called by the user interface. When called, the characters in the document are passed as a C-string parameter, document, to the encrypt function. The name of the file is also passed as a C-string parameter. The encrypt function opens the file. Each character in the document C-string is then encrypted and stored in the file.
* If the user wishes to open a file, the file name must be entered in the field to the right of the Open File button. The Open File button is then clicked. The decrypt function is called by the user interface. When called, a C-string, document, is passed as a parameter to the decrypt function. A C-string containing the name of the file is also passed as a parameter. The decrypt function opens the file. Each character from the file is then read, decrypted, and inserted in the document C-string which was passed as a parameter.
* The readWordsDictionary function reads all the words from the dictionary file, dictionary.txt, and stores them in dictionary, an array of string passed as a parameter. It returns the amount of words in the dictionary. All the words in the dictionary are in lowercase. The function is called as soon as the program starts.
* The checkSpelling function accepts the dictionary as a parameter as well as a C-string containing the characters of the document. It checks the spelling of all the words that come after location start in the document C-string. If an incorrectly spelt word is encountered, it is copied to the C-string errorWord and the function terminates by returning the starting location of the word that has been spelt incorrectly. If there are no spelling errors, the function return -1.
* The checkSpellingAll function is similar to the checkSpelling function. However, it searches the entire document C-string for incorrectly spelt words. Whenever an incorrectly spelt word is encountered, it is inserted in the array of errorWords which was passed as a parameter. The function returns the amount of words that were incorrectly spelt in the document.
* The searchWord function searches the document C-string to find the keyWord C-string, starting from location start. If the keyWord substring is found in the document C-string, the function returns the starting location where it was found. Otherwise, return -1.
* The  getStatistics function accepts the document C-string, analyses it, and stores the result in a Statistics struct which is returned to the caller.

---

## Lanaguages tools and technologies
* C++
* Data structures

---

## Project
![Screenshot (631)](https://user-images.githubusercontent.com/77646306/124192327-18706980-da93-11eb-9ffa-154e7f7a227a.png)

---

## Author Info
* [Linkedin](https://www.linkedin.com/in/tamika-ramkissoon-1a2622214/)

