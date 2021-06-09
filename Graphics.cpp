#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <cstring>
#include <ctime>
	using namespace std;	

const char g_szClassName[] = "myWindowClass";			// for windows program

string dictionary [100000];
int numWordsDictionary;

struct Statistics {
	int wordCount;
	int longestWord;
	int shortestWord;
	int numChars;
};

long long count;										// used to generate IDs for GUI controls

HWND hEditText;											// text box for editor

HWND hButtonOpen;										// button to open file
HWND hEditOpen;											// text field to specify filename to read from

HWND hButtonSaveAs;										// button to save file as
HWND hEditSaveAs;										// text field to specify filename to save to

HWND hButtonClear;										// button to clear editor and filenames

HWND hButtonSpellCheck1;								// button to spell check from beginning
HWND hButtonSpellCheck2;								// button to spell check from cursor
HWND hButtonSpellCheck3;								// button to spell check entire document

HWND hButtonFind1;										// button to search for word from beginning
HWND hButtonFind2;										// button to search for word from cursor
HWND hEditFind;											// button to specify word to search for

HWND hButtonProperties;									// button to display statistics

HWND hLabelFile;										// label for file operations
HWND hLabelSpelling;									// label for spell check operations
HWND hLabelSearch;										// label for search operations

WNDPROC oldEditProc;									// old callback for edit box

// Declarations of functions in GivenFunctions.cpp

void toCString (string s, char c[]);
void displayText (string message, string title);
void displayText2 (char s[], char title[]);

// Declarations of functions in Assignment2.cpp

void encrypt (char document[], char filename[]);
void decrypt (char document[], char filename[]);
int readWordsDictionary(string dictionary[]);
int checkSpelling (string dictionary[], int numWords, char document[], int start, char errorWord[]);
int checkSpellingAll (string dictionary[], int numWords, char document[], string errorWords[]);
int searchWord (char document[], int start, char keyWord[]);
Statistics getStatistics (char document[]);


void createControls(HWND hwnd) {
	
	count = 101;

    hEditText = CreateWindow (TEXT ("EDIT"), "",
                        WS_CHILD | WS_VISIBLE | WS_VSCROLL |
//                     	WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |
                        WS_BORDER | ES_LEFT | ES_MULTILINE,
//                      WS_BORDER | ES_LEFT | ES_MULTILINE |
//                      ES_AUTOHSCROLL | ES_AUTOVSCROLL,
                        25, 25, 495, 300, hwnd, (HMENU) count,
                        GetModuleHandle(NULL), NULL) ;
	
	count = 1000;
	
	hLabelFile = CreateWindow(TEXT("Static"), TEXT("File Operations: "), 
						WS_CHILD | WS_VISIBLE, 25, 350, 150, 30, hwnd, (HMENU)count, GetModuleHandle(NULL), NULL);
						
	hLabelSpelling = CreateWindow(TEXT("Static"), TEXT("Check Spelling: "), 
						WS_CHILD | WS_VISIBLE, 400, 350, 150, 30, hwnd, (HMENU)count, GetModuleHandle(NULL), NULL);
						
	hLabelSearch = CreateWindow(TEXT("Static"), TEXT("Search: "), 
						WS_CHILD | WS_VISIBLE, 550, 25, 120, 30, hwnd, (HMENU)count, GetModuleHandle(NULL), NULL);	
																	
    count = 201;
    
	hButtonOpen = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Open File ->",
                		WS_CHILD | WS_VISIBLE,
						25, 400, 125, 30,
                		hwnd, (HMENU) count, GetModuleHandle(NULL), NULL);
 
 	count = 102;
 	
    hEditOpen = CreateWindow (TEXT ("EDIT"), "",
                        WS_CHILD | WS_VISIBLE |
                        WS_BORDER | ES_LEFT | ES_MULTILINE,
                        160, 400, 200, 30, hwnd, (HMENU) count,
                        GetModuleHandle(NULL), NULL) ;     
						 
	count = 202;
	
    hButtonSaveAs = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Save File As ->",
                		WS_CHILD | WS_VISIBLE,
						25, 450, 125, 30,
                		hwnd, (HMENU) count, GetModuleHandle(NULL), NULL);   
 
 	count = 103;
 	
    hEditSaveAs = CreateWindow (TEXT ("EDIT"), "",
                        WS_CHILD | WS_VISIBLE |
                        WS_BORDER | ES_LEFT | ES_MULTILINE,
                        160, 450, 200, 30, hwnd, (HMENU) count,
                        GetModuleHandle(NULL), NULL) ;   
						 
	count = 203;
	
    hButtonClear = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Clear Editor",
                		WS_CHILD | WS_VISIBLE,
						25, 500, 125, 30,
                		hwnd, (HMENU) count, GetModuleHandle(NULL), NULL);
                				
	count = 205;
			
	hButtonFind1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "From Beginning",
                		WS_CHILD | WS_VISIBLE,
						550, 125, 150, 30,
                		hwnd, (HMENU) count, GetModuleHandle(NULL), NULL);		

	count = 215;
			
	hButtonFind2 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "From Cursor",
                		WS_CHILD | WS_VISIBLE,
						550, 175, 150, 30,
                		hwnd, (HMENU) count, GetModuleHandle(NULL), NULL);
												
	count = 206;
			
	hButtonProperties = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Statistics",
                		WS_CHILD | WS_VISIBLE,
						550, 295, 150, 30,
                		hwnd, (HMENU) count, GetModuleHandle(NULL), NULL);	  
				
	count = 211;
    
	hButtonSpellCheck1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "From Beginning",
                		WS_CHILD | WS_VISIBLE,
						400, 400, 125, 30,
                		hwnd, (HMENU) count, GetModuleHandle(NULL), NULL);	
				
	count = 212;
	
    hButtonSpellCheck2 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "From Cursor",
                		WS_CHILD | WS_VISIBLE,
						400, 450, 125, 30,
               			hwnd, (HMENU) count, GetModuleHandle(NULL), NULL); 				

	count = 213;
	
    hButtonSpellCheck3 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "All Words",
                		WS_CHILD | WS_VISIBLE,
						400, 500, 125, 30,
                		hwnd, (HMENU) count, GetModuleHandle(NULL), NULL);								 						               
																		
	hEditFind = CreateWindow (TEXT ("EDIT"), "",
                        WS_CHILD | WS_VISIBLE |
                        WS_BORDER | ES_LEFT | ES_MULTILINE,
                        550, 75, 200, 30, hwnd, (HMENU) count,
                        GetModuleHandle(NULL), NULL) ;             
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	COLORREF editText = RGB(255,255,255); 			// use RED for Background.
	COLORREF editBackground = RGB(255,0,255); 		// use RED for Background.
	COLORREF timerBackground = RGB(135,206,250); 	// use RED for Background.
	
	switch(msg)
	{
		case WM_CREATE:
		{

			createControls(hwnd);

			break;
		}

    	case WM_COMMAND:
  

    		if ((LOWORD(wParam) == 205) && (HIWORD(wParam) == BN_CLICKED)) {
	
				char buffer[10000];
				char mess[100];
				
				int start, end;
				
				int editSize;
				editSize = GetWindowTextLength(hEditText) + 1;		// Find amount of characters in text box (add 1 for terminating '\0')
				GetWindowText(hEditText, buffer, editSize);			// Read characters into buffer
			
				char key [25];
				char title [25];
				
				editSize = GetWindowTextLength(hEditFind) + 1;		// Find amount of characters in text box (add 1 for terminating '\0')
				GetWindowText(hEditFind, key, editSize);			// Read characters into buffer
				
				sprintf (title, "Search Value");
				displayText2(key, title);
				
				int result;
				result = searchWord (buffer, 0, key);
				//sprintf (mess, "Value of result = %d", result);
				//sprintf (title, "Result of Search");
				//displayText2 (mess, title);

				if (result == -1) {
					sprintf (mess, "'%s' not found in document", key);
					displayText2 (mess, title);
				}
				else {
					SendMessage(hEditText, EM_SETSEL, result, result+editSize-1);
				}
			
				SetFocus(hEditText);				
			}
			
			if ((LOWORD(wParam) == 206) && (HIWORD(wParam) == BN_CLICKED)) {
				char buffer[10000];
				char mess[200];
				char title[50];
				
				int start, end;
				
				int editSize;
				editSize = GetWindowTextLength(hEditText) + 1;		// Find amount of characters in text box (add 1 for terminating '\0')
				GetWindowText(hEditText, buffer, editSize);			// Read characters into buffer
				
				Statistics res = getStatistics (buffer);
				sprintf (mess, " Number of words: %d\n Longest Word: %d\n Shortest Word: %d\n Number of characters: %d",
						 res.wordCount, res.longestWord, res.shortestWord, res.numChars);
				sprintf (title, "Statistics");

				displayText2 (mess, title);
			}
			
    		if ((LOWORD(wParam) == 215) && (HIWORD(wParam) == BN_CLICKED)) {
				char buffer[10000];
				char mess[100];
				
				int start, end;
				
				int editSize;
				editSize = GetWindowTextLength(hEditText) + 1;		// Find amount of characters in text box (add 1 for terminating '\0')
				GetWindowText(hEditText, buffer, editSize);			// Read characters into buffer
				SendMessage(hEditText, EM_GETSEL, (WPARAM) &start, (LPARAM) &end);
			
				char key [25];
				char title [25];
				
				editSize = GetWindowTextLength(hEditFind) + 1;		// Find amount of characters in text box (add 1 for terminating '\0')
				GetWindowText(hEditFind, key, editSize);			// Read characters into buffer
				
				sprintf (title, "Search Value");
				displayText2(key, title);
				
				int result;
				result = searchWord (buffer, start, key);
				//sprintf (mess, "Value of result = %d", result);
				//sprintf (title, "Result of Search");
				//displayText2 (mess, title);

				if (result == -1) {
					sprintf (mess, "'%s' not found.", key);
					displayText2 (mess, title);
				}
				else {
					SendMessage(hEditText, EM_SETSEL, result, result+editSize-1);
				}

				SetFocus(hEditText);				
			}
			
    		if ((LOWORD(wParam) == 211) && (HIWORD(wParam) == BN_CLICKED)) {
    			MessageBox(NULL, "Check Words from Beginning", "Button", MB_ICONEXCLAMATION | MB_OK);
				char buffer[10000];
				
				int start, end;
				
				int editSize;
				editSize = GetWindowTextLength(hEditText) + 1;		// Find amount of characters in text box (add 1 for terminating '\0')
				GetWindowText(hEditText, buffer, editSize);			// Read characters into buffer
			
				char errorWord[50];
				int errorWordSize;
				
				int res = checkSpelling (dictionary, numWordsDictionary, buffer, 0, errorWord);
				
				char m[50];
				char t[50];
				//sprintf (m,"Returned. Value of res is %d and error is %s", res, errorWord);
				sprintf (t, "Spell Check");
				//displayText2 (m, t);
				
				if (res >= 0) {
					//sprintf (m, "About to select error word in passage");
					//displayText2 (m, t);
					errorWordSize = strlen(errorWord);
					SendMessage(hEditText, EM_SETSEL, res, res+errorWordSize);
					SetFocus(hEditText);
				}
				else {
					sprintf (m, "No spelling errors found.");
					displayText2 (m, t);
				}
				
			}			

    		if ((LOWORD(wParam) == 212) && (HIWORD(wParam) == BN_CLICKED)) {
    			MessageBox(NULL, "Check Words from Cursor Position", "Button", MB_ICONEXCLAMATION | MB_OK);
				char buffer[10000];
				
				int start, end;
				
				int editSize;
				editSize = GetWindowTextLength(hEditText) + 1;		// Find amount of characters in text box (add 1 for terminating '\0')
				GetWindowText(hEditText, buffer, editSize);			// Read characters into buffer
				SendMessage(hEditText, EM_GETSEL, (WPARAM) &start, (LPARAM) &end);
			
				char errorWord[50];
				int errorWordSize;
				
				int res = checkSpelling (dictionary, numWordsDictionary, buffer, start, errorWord);
				
				char m[50];
				char t[50];
				//sprintf (m,"Returned. Value of res is %d and error is %s", res, errorWord);
				sprintf (t, "Spell Check");
				//displayText2 (m, t);
				
				if (res >= 0) {
					//sprintf (m, "About to select error word in passage");
					//displayText2 (m, t);
					errorWordSize = strlen(errorWord);
					SendMessage(hEditText, EM_SETSEL, res, res+errorWordSize);
					SetFocus(hEditText);
				}
				else {
					sprintf (m, "No spelling errors found.");
					displayText2 (m, t);
				}
				
			}			

    		if ((LOWORD(wParam) == 213) && (HIWORD(wParam) == BN_CLICKED)) {
    			MessageBox(NULL, "Check All Words from Beginning", "Button", MB_ICONEXCLAMATION | MB_OK);
				char buffer[10000];
				
				int start, end;
				
				int editSize;
				editSize = GetWindowTextLength(hEditText) + 1;		// Find amount of characters in text box (add 1 for terminating '\0')
				GetWindowText(hEditText, buffer, editSize);			// Read characters into buffer
			
				string errorWords[50];
				int errorWordSize;
				
				int res = checkSpellingAll (dictionary, numWordsDictionary, buffer, errorWords);
				
				char errors[1000];
				errors[0] ='\0';
				char c[50];	
			
				for (int i=0; i<res; i++) {
					string s = errorWords[i];
					toCString (s, c);
					strcat(errors,"\n");
					strcat(errors, c);			
				}
				
				char m[100];
				char t[50];
				
				sprintf (t, "Spell Check");
				
				if (res > 0)
					sprintf (m, "There are %d words with spelling errors: %s",  res, errors);
				else
					sprintf (m, "No spelling errors found.");
					
				displayText2 (m, t);
			}			

    		if ((LOWORD(wParam) == 201) && (HIWORD(wParam) == BN_CLICKED)) {
				char buffer [10000];
				char filename [50];
				int filenameLength;
			
				MessageBox(NULL, "File open button clicked", "Button", MB_ICONEXCLAMATION | MB_OK);	
				
				filenameLength = GetWindowTextLength(hEditOpen) + 1;
				GetWindowText(hEditOpen, filename, filenameLength);
				
				buffer[0] = '\0';
					
				decrypt(buffer, filename);
			
				SetWindowText(hEditText, buffer);
				SetFocus(hEditText);
		
			}			

    		if ((LOWORD(wParam) == 202) && (HIWORD(wParam) == BN_CLICKED)) {
				 
				MessageBox(NULL, "Save As button clicked", "Button", MB_ICONEXCLAMATION | MB_OK);
			
				char buffer[10000];
				char filename[50];
				
				int editSize, filenameLength;
				editSize = GetWindowTextLength(hEditText) + 1;		// Find amount of characters in text box (add 1 for terminating '\0')
				GetWindowText(hEditText, buffer, editSize);			// Read characters into buffer
				
				filenameLength = GetWindowTextLength(hEditSaveAs) + 1;
				GetWindowText(hEditSaveAs, filename, filenameLength);
				
				encrypt(buffer, filename);
				
			}

    		if ((LOWORD(wParam) == 203) && (HIWORD(wParam) == BN_CLICKED)) {
				MessageBox(NULL, "Clear button clicked", "Button", MB_ICONEXCLAMATION | MB_OK);
				char mess[20];
				int i;
				string s = dictionary[0];
				char w[50];
				int l = s.length();
				for (i=0; i<l; i++)
					w[i] = s.at(i);
				w[l] = '\0';
				
				char buffer[10] = "\0";
				char filename[50];
				
				SetWindowText (hEditText, buffer);
				SetWindowText (hEditSaveAs, buffer);
				SetWindowText (hEditOpen, buffer);
				
			}	

			break;
			
 case WM_CTLCOLORSTATIC:
    {

	}
    
    break;

        case WM_LBUTTONDOWN:
        {            
        
        }
        break;
        
        case WM_RBUTTONDOWN:
        {
          
        }
        break;

		case WM_PAINT:
		{
 			HDC hdc;
 			PAINTSTRUCT ps;
 		
			hdc = BeginPaint(hwnd, &ps);
			
 			EndPaint(hwnd, &ps);
 			return 0;		    
 		}
 		break;

		case WM_CLOSE:
			DestroyWindow(hwnd);
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = 0;
	wc.lpfnWndProc	 = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		0,
		g_szClassName,
		"My Secret Editor",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, hInstance, NULL);

	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	numWordsDictionary = readWordsDictionary(dictionary);

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

