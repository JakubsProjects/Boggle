
#include <iostream>
#include <stdio.h>
#include <time.h> 
#include <fstream>    // For file input and output
#include <cassert> 
#include <cstring> // For the assert statement

using namespace std;
const int NumberOfWords = 263533;   // Number of dictionary words
const int WordLength = 17;	    // Max word size + 1 for null 

								//Game Instructions
void printInformationAndInstructions() {

	cout << "Jakub Glebocki"
		<< "Program: #5, Boggle " << endl
		<< "TA: Minh Tues 11-11:50 " << endl
		<< "Nov 5, 2016" << endl

		<< "Welcome to the game of Boggle, where you play against the clock" << endl
		<< "to see how many words you can find using adjacent letters on the" << endl
		<< "board.  Each letter can be used only once for a given word." << endl

		<< "When prompted to provide input you may also:" << endl
		<< "Enter 'r' to reset the board to user-defined values." << endl
		<< "Enter 's' to solve the board and display all possible words." << endl
		<< "Enter 't' to toggle the timer off/on." << endl
		<< "Enter 'x' to exit the program." << endl << endl;

}

//Displaying the board
void displayBoard(char board[])
{
	printf("\n");
	printf("\n");
	printf("       %c %c %c %c %c %c\n ", board[0], board[1], board[2], board[3], board[4], board[5]);
	printf("      %c %c %c %c %c %c\n ", board[6], board[7], board[8], board[9], board[10], board[11]);
	printf("      %c %c %c %c %c %c\n ", board[12], board[13], board[14], board[15], board[16], board[17]);
	printf("      %c %c %c %c %c %c\n ", board[18], board[19], board[20], board[21], board[22], board[23]);
	printf("      %c %c %c %c %c %c\n ", board[24], board[25], board[26], board[27], board[28], board[29]);
	printf("      %c %c %c %c %c %c\n ", board[30], board[31], board[32], board[33], board[34], board[35]);
	printf("\n");
}//end displayBoard()

 //Initializing the board
void initializeBoard(char board[])
{
	//List of how frequent a letter from the alphabet appears
	double list[26] = {
		0.07680,  //  a
		0.09485,  //  b
		0.13527,  //  c
		0.16824,  //  d
		0.28129,  //  e
		0.29299,  //  f
		0.32033,  //  g
		0.34499,  //  h
		0.43625,  //  i
		0.43783,  //  j
		0.44627,  //  k
		0.49865,  //  l
		0.52743,  //  m
		0.59567,  //  n
		0.66222,  //  o
		0.69246,  //  p
		0.69246,  //  q
		0.76380,  //  r
		0.86042,  //  s
		0.92666,  //  t
		0.95963,  //  u
		0.96892,  //  v
		0.97616,  //  w
		0.97892,  //  x
		0.99510,  //  y
		1.00000 }; //  z

				   //Generating random Number between 0 and 1
	srand(time(NULL));

	//initializing variables
	int i, j;

	//For evey board position get a random character
	for (i = 0; i < 36; i++) {

		//Generating random Number between 0 and 1
		double myRandomNumber = ((double)rand() / RAND_MAX);

		// For the current position find a random character
		for (j = 0; j < 26; j++) {
			//Generated number makes letter on board
			if (myRandomNumber < list[j]) {
				board[i] = 'a' + j;
				break;
			}
		}
		//Setting the borders of board to "*"
		board[0] = board[6] = board[12] = board[18] = board[24] = board[30] = '*';
		board[0] = board[1] = board[2] = board[3] = board[4] = board[5] = '*';
		board[30] = board[31] = board[32] = board[33] = board[34] = board[35] = '*';
		board[11] = board[17] = board[23] = board[29] = '*';
	}
}

//Allocate memory
void allocateArray(char ** & matrix)
{
	// Allocate space for large array of C-style strings
	matrix = new char*[NumberOfWords];

	// For each array entry, allocate space for the string to be stored there
	for (int i = 0; i < NumberOfWords; i++) {
		matrix[i] = new char[WordLength];

		// just to be safe, initialize C-string to all null characters 
		for (int j = 0; j < WordLength; j++) {
			matrix[i][j] = '\0';
		}//end for (int j=0...
	}//end for (int i...
}//end allocateArray()

 //Read in the words/dictionary
char ** readInWords(char ** dictionary, char * filename)
{
	// Now read the words from the dictionary
	ifstream inStream;                          // declare an input stream for my use
	int wordRow = 0;                            // Row for the current word
	inStream.open("dictionary.txt");
	assert(!inStream.fail());  // make sure file open was OK

	char tempArray[81];
	// Keep repeating while input from the file yields a word
	while (inStream >> tempArray)
	{


		// 	cout << tempArray << endl;
		//Check the size, if it's right then copy from temp array into the words

		if ((strlen(tempArray) <= 16) && strlen(tempArray) >= 3)
		{

			int i = 0;
			while (i < strlen(tempArray))
			{
				//	char c = tempArray[i];
				tempArray[i] = tolower(tempArray[i]);
				// strcpy( dictionary[wordRow], tempArray[i]);
				i++;
			}

			strcpy(dictionary[wordRow], tempArray);
			//cout << dictionary[ wordRow] << endl;

			wordRow++;

		}
	}
	//Number of words read in
	cout << wordRow << " words were read in (between length 3 and 16)." << endl;

	return dictionary;
}

//Binary search function
int binarySearch(char * searchWord, 				  // word to be looked up
	char  ** dictionary,	  // the dictionary of words
	int numberOfDictionaryWords)		      // number of words in the dictionary
{
	int low, mid, high;     // array indices for binary search
	int searchResult = -1;  // Stores index of word if search succeeded, else -1

							// Binary search for word
	low = 0;
	high = numberOfDictionaryWords - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		// searchResult negative value means word is to the left, positive value means
		// word is to the right, value of 0 means word was found 
		searchResult = strcmp(searchWord, dictionary[mid]);

		if (searchResult == 0)
		{
			// Word IS in dictionary, so return the index where the word was found
			return mid;
		}
		else if (searchResult < 0)
		{
			high = mid - 1; // word should be located prior to mid location
		}
		else
		{
			low = mid + 1; // word should be located after mid location
		}
	}
	// Word was not found
	return -1;
}//end binarySearch()

 //Recursive function that finds the ALL characters
int findNextCharacter(char board[], char userInput[], int &CurrentBoardIndex, int &counter, int &PreviousUserInputIndex) {
	int moveArray[8] = { -7, -6, -5, -1, 1, 5, 6, 7 };
	int previousPosition = 0;

	//cout << "Counter:" << counter << "    " << "UserInputLtter:" << userInput[PreviousUserInputIndex] << "    " << "Board Inex: " << CurrentBoardIndex;
	for (int i = 0; i < 8; i++) {

		//If the word letter is found on the board(checks neighbors) and is not a star do the following
		if ((userInput[PreviousUserInputIndex] == board[moveArray[i] + CurrentBoardIndex]) && (board[moveArray[i] + CurrentBoardIndex] != previousPosition)) {

			//Set previousPosition on he board
			previousPosition = CurrentBoardIndex;

			//Current board gets updated to whereveer the next letter is
			CurrentBoardIndex = moveArray[i] + CurrentBoardIndex;

			//User in put index gets incremented(indicated which letter we are on)
			PreviousUserInputIndex = 1 + PreviousUserInputIndex;
			//Increment's counter
			counter = counter + 1;

			//if counter is elss than length of word, do a recursive call
			if (counter < strlen(userInput)) {

				findNextCharacter(board, userInput, CurrentBoardIndex, counter, PreviousUserInputIndex);
			}
		}

		//If length of word is equal to length of found characters then break
		if (counter == strlen(userInput)) {
			break;
		}
	}
	//return counter
	return counter;
}

//Increase score on board
int boardScore(int &score, char userInput[]) {

	//Add one point for length word of 3
	if (strlen(userInput) == 3) {
		cout << "One point for word found" << endl;
		score = score + 1;
	}
	//Add two point for length word of 4
	else if (strlen(userInput) == 4) {
		cout << "Two point for word found" << endl;
		score = score + 2;
	}
	//Add four point for length word of 5
	else if (strlen(userInput) == 5) {
		cout << "Four point for word found" << endl;
		score = score + 4;
	}
	//Add length points for length word of word
	else {
		score = score + strlen(userInput);
		cout << strlen(userInput) << " point for word found";
	}
	//return the score to be displayed
	return score;
}

//Checks each character on the board
int checkWordsBoard(char board[], char userInput[], int binaryPosition, bool trackWordsFound[], int &score, char variable) {
	//Initialzing variables
	int i = 0;
	int CurrentBoardIndex = 7;
	int checkResult = 0;
	//counter starts from 1 when 1 letter on board of word is found
	int counter = 1;
	//Where we are in the word(userinput[1])
	int PreviousUserInputIndex = 1;
	int counterResult = 0;

	//Looping throught whole board, it's a 6x6
	for (i = 7; i < 30; i++)
	{
		//Finding First letter of word on board
		if (userInput[0] == board[i])
		{
			//incrementing variables to pass into function
			counter = 1;
			PreviousUserInputIndex = 1;
			CurrentBoardIndex = i;

			// Make function to check the next character of UserInput
			counterResult = findNextCharacter(board, userInput, CurrentBoardIndex, counter, PreviousUserInputIndex);
		}
		// If count matches word length then do the following
		if (counterResult == strlen(userInput)) {
			//if bool array is already true, word is already found
			if (trackWordsFound[binaryPosition] == 1) {
				//If user chose s, do not display this message
				if (variable != 's') {
					cout << "Word Already on board";
				}
				//return 3 to not increment game score
				return 3;
			}
			//set boolean array to true
			trackWordsFound[binaryPosition] = 1;
			//if user did not type in s then do the following
			if (variable != 's') {
				//Adds score to game
				boardScore(score, userInput);
				cout << "Word Found Successfully";
			}
			//exit function
			return 0;
		}
	}
	//if user did not type in s then display the following
	if (variable != 's') {
		cout << " Word Not Found on board ";
	}
	//return this value if word was not found
	return -1;
}

//function to make bool array false
bool* setBoolToFalse(bool trackWordsFound[]) {

	for (int i = 0; i < NumberOfWords; i++) {
		trackWordsFound[i] = 0;
		//cout << trackWordsFound[i];
	}
	return trackWordsFound;
}

//User selects r to put in letters
void userDefinedValues(char* board) {
	int i = 0;

	//Goes through the board
	for (i = 7; i < 30; i++) {

		//If it doesnt equal borders
		if (board[i] != board[11] || board[i] != board[12] || board[i] != board[17] || board[i] != board[18] || board[i] != board[23] || board[i] != board[24] || board[i] != board[29] || board[i] != board[30]) {
			cout << "Please enter desired user-values(16 letters only):  ";
			//Let user input letters to be stored on board
			cin >> board[i];
			displayBoard(board);
		}
	}
}

int main() {
	//Declaring many variables
	int moveNumber = 1;
	int score = 0;
	char userInput[16];
	char **dictionary;
	char filename[] = "dictionary.txt";
	int i = 0;
	int functionReturnValue = 0;
	int binaryPosition = 0;
	bool trackWordsFound[NumberOfWords];
	time_t startTime = time(NULL);
	int actualTimeRun = 60;
	int playTimeLeft = 0;
	char variable = 'a';
	bool timeSwitch = false;
	int lettersInWord = 3;
	//int timeSwitch = 0;
	int min, max = 0;

	//Declaring the board
	char board[36] = { '*','*', '*', '*', '*','*',
		'*','.', '.', '.', '.','*',
		'*','.', '.', '.', '.','*',
		'*','.', '.', '.', '.','*',
		'*', '.','.', '.', '.','*',
		'*', '*','*', '*', '*','*', };
	//Function call to print all information
	printInformationAndInstructions();
	//Function to allocate memory
	allocateArray(dictionary);
	//Function to read in the word
	readInWords(dictionary, filename);
	// Fcuntion to randomize the board
	initializeBoard(board);
	// Function to set bool array to false
	setBoolToFalse(trackWordsFound);

	//While true do the following
	while (true) {

		//Shows board
		displayBoard(board);

		//prints out score 
		cout << "Score: " << score << endl;

		//Prints out words found so far
		cout << "Words found so far: ";
		//Goes through all length of words
		for (int j = 3; j <= 16; j++) {
			//Goes through all 259,709 dictionary words
			for (int i = 0; i < NumberOfWords; i++) {
				if (strlen(dictionary[i]) == j && trackWordsFound[i] == 1) {
					//prints the word
					cout << dictionary[i] << "  ";
				}
			}
		}

		//Shows playtime left
		playTimeLeft = actualTimeRun - (time(NULL) - startTime);

		//Show time is timeswitch is set to false
		if (timeSwitch == false) {
			cout << endl << " Time: " << playTimeLeft;
			//If 60 seconds pass by, exit the program
			if ((int)playTimeLeft < 0) {
				exit(0);
			}
		}

		//show move number on board
		cout << endl << moveNumber << "." << "Enter a word: ";

		//reads in user word
		cin >> userInput;

		// if user inputs only 1 charcter
		if (strlen(userInput) == 1) {

			//Toggles time on and off
			if (userInput[0] == 't') {
				if (timeSwitch == false) {
					timeSwitch = true;
				}
				else {
					timeSwitch = false;
				}
			}

			//Exits the program if user chooses x
			if (userInput[0] == 'x') {
				cout << "Exiting..." << endl;
				exit(0);
			}

			//Randomize board to user defined values
			if (userInput[0] == 'r') {
				userDefinedValues(board);
			}

			//Show all solutions for board
			if (userInput[0] == 's') {
				variable = 's';
				cout << " Enter length of Words to be displayed  ";
				cin >> min;
				cin >> max;
				//Goes through all words
				for (int i = 0; i < NumberOfWords; i++) {
					checkWordsBoard(board, dictionary[i], i, trackWordsFound, score, variable);
				}
				//Goes and finds min and max(user values) to show words of that length
				for (int j = min; j <= max; j++) {
					for (int i = 0; i < NumberOfWords; i++) {
						if (strlen(dictionary[i]) == j && trackWordsFound[i] == 1) {
							cout << dictionary[i] << "  ";
						}
					}
				}
				//Exit program
				exit(0);
			}
		}

		//Binary search returns -1 if word was not found
		if (binarySearch(userInput, dictionary, NumberOfWords) == -1)
		{
			cout << "Sorry, that word is not in the dictionary.";
		}

		else
		{
			//word was found so get binary position
			binaryPosition = (binarySearch(userInput, dictionary, NumberOfWords));

			//Enter function to find if word is on the board
			functionReturnValue = checkWordsBoard(board, userInput, binaryPosition, trackWordsFound, score, variable);

			//If function returns -3, do not increment game(Move Number)
			if (functionReturnValue != 3)
				moveNumber++;
		}
	}
}
