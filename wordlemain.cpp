/*
 * wordlemain.cpp
 *
 *  Created on: Sep 1, 2022
 *      Author: Rana Tuncer
 */
/********************************************************************************************/
/*Name: Rana Tuncer
/********************************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
using namespace std;
string ans_list[12];
int ans_ct;
void testingdoWordsMatch(string s1, string s2);
void testingfindGs(string s1,string s2, char chararr[], bool foundarr[]);
void testingfindYs(string s1,string s2, char chararr[], bool foundarr[]);
int getSize(string fn);
void readFile(string fn, string arr[], int num_words);
void playGame(int num_words, string arr[]);
string getWord(int num, string arr[]);
bool startGuessing(string curr_word);
void printResults();
bool checkWord(string guess, string curr_word);
bool doWordsMatch(string guess, string curr_word);
void findGs(string guess, string curr_word,char ans[], bool found[]);
void findYs(string guess, string curr_word,char ans[], bool found[]);
void reset_ans_list();
int main() {
//********************************************************************************
// Testing doWordsMatch:
//	testingdoWordsMatch("match","match");
//	testingdoWordsMatch("match","matcy");
//	testingdoWordsMatch("match", "gummy");
//	testingdoWordsMatch("matcy","match");
//
// Output should be:
//  match and match are matches!! :-)
//  match and matcy do not match :-(
//  match and gummy do not match :-(
//  matcy and match do not match :-(
//********************************************************************************
// Testing findGs:
//	cout <<endl<<endl<<"Part 1b"<<endl<< "**********************************" << endl;
//	char chararr[5] = {' ',' ',' ',' ',' '};
//	bool foundarr[5]={0,0,0,0,0};
//	testingfindGs("match","match",chararr,foundarr);
//	testingfindGs("match","walsh",chararr,foundarr);
//	testingfindGs("match","amaze",chararr,foundarr);
//	testingfindGs("match","mooch",chararr,foundarr);

// Output should be:
// Part 1b
// ***********************************
// m a t c h
// m a t c h
// G G G G G
// 1 1 1 1 1
// **********************************
// m a t c h
// w a l s h
//   G     G
// 0 1 0 0 1
// **********************************
// m a t c h
// a m a z e
//
// 0 0 0 0 0
// **********************************
// m a t c h
// m o o c h
// G     G G
// 1 0 0 1 1
// **********************************
//*********************************************************************************
// Testing findYs:
//	cout << endl<<endl<<"Part 1c"<<endl<<"**********************************" << endl;
//	char a1[] = {'G','G',' ',' ','G'};
//	bool f1[] = {1,1,0,0,1};
//	testingfindYs("match","marsh",a1,f1);
//	char a2[] = {' ',' ',' ',' ',' '};
//	bool f2[] = {0,0,0,0,0};
//	testingfindYs("enter","rests",a2,f2);
//	char a3[] = {' ',' ',' ',' ',' '};
//	bool f3[] = {0,0,0,0,0};
//	testingfindYs("rests","enter",a3,f3);
//	char a4[] = {' ',' ',' ',' ',' '};
//	bool f4[] = {0,0,0,0,0};
//	testingfindYs("enter","teeth",a4,f4);
//	char a5[] = {' ',' ','G',' ',' '};
//	bool f5[] = {0,0,1,0,0};
//	testingfindYs("mommy","simon",a5,f5);

// Output should be:
// Part 1c
// **********************************
// m a t c h
// m a r s h
// G G     G
// 1 1 0 0 1
// **********************************
// e n t e r
// r e s t s
// Y   Y   Y
// 1 1 0 1 0
// **********************************
// r e s t s
// e n t e r
// Y Y   Y
// 1 0 1 0 1
// **********************************
// e n t e r
// t e e t h
// Y   Y Y
// 1 1 1 0 0
// **********************************
// m o m m y
// s i m o n
//   Y G
// 0 0 1 1 0
// **********************************
//*********************************************************************************
	srand(time(NULL)); //for random numbers
	int num_words = getSize("wordlist.txt");
	string arr[num_words];
	readFile("wordlist.txt", arr, num_words);
	playGame(num_words, arr);
	return 0;
}
/*******************HERE IS WHERE THE CODE GOES! **********************************/
bool doWordsMatch(string guess, string curr_word) {
	/**
	 * doWordsMatch: Takes as input 2 strings (both 5 letters long),
	 * and returns a boolean value indicating whether the two strings match.
	 *
	 * Params:
	 * guess (string) - the word user enters as a guess attempt
	 * curr_word (string) - the word the user is trying to figure out
	 *
	 * Returns:
	 * bool - whether the guess and the correct word match or not
	 */
	bool match = true;
	for (int letter=0; letter<5 ; letter++){
		if (guess[letter] != curr_word[letter]){
			match = false;
		}
	}
	return match;
}

void findGs(string guess, string curr_word,char ans[], bool found[]) {
	/*
	 * findGs: Takes as input 2 strings (both 5 letters long),
	 * an array of characters (5 chars long), and an array of boolean values (5 long).
	 * The function places a 'G' in the char array everywhere that
	 * the two strings have identical characters in the identical indices.
	 * It also places a True (1) in the boolean array at that same index.
	 *
	 * (Example) if the two strings were "match" and "harsh", the char
	 * array would place a 'G' at index 1 & index 4. The bool array would
	 * place a True (aka 1) at index 1 & index 4 also.
	 *
	 * Params:
	 * guess (string) - the word user enters as a guess attempt
	 * curr_word (string) - the word the user is trying to figure out
	 * ans (char[]) - array that displays which letters are in the correct position
	 * found (bool[]) - array that records which letters are in right position
	 */
	for (int letter=0; letter<5; letter++){
		if (guess[letter] == curr_word[letter]){
			ans[letter] = 'G';
			found[letter] = 1;
		}
		else {
			found[letter] = 0;
		}
	}

}

void findYs(string guess, string curr_word,char ans[], bool found[]) {
	/*
	 * This function looks for matching letters that ARE NOT in the right place
	 * between two strings. If a letter in 1st string occurs in the 2nd string
	 * in an index other than where it is in the 1st string, a 1 is placed in
	 * the found arr at the index of the letter in the 2nd string, and a 'y' is
	 * placed in the ans arr at the index of the letter in the 1st string.
	 *
	 * (Example) in "match"(str 1) and "llama" (str 2), m and a both
	 * occur in both words, but not in the same place. ans array would be
	 * {'Y','Y',' ',' ',' '} (matching the indices for m and a in
	 * "match"), and found arr would be {0 0 1 1 0} (matching the indices of
	 * a and m in "llama".
	 *
	 * Params:
	 * guess (string) - the word user enters as a guess attempt
	 * curr_word (string) - the word the user is trying to figure out
	 * ans (char[]) - array that displays which letters are in the correct position
	 * found (bool[]) - array that records which letters are in right position
	 */
	for (int letter=0; letter<5; letter++){
		for (int a_letter=0; a_letter<5; a_letter++){
			if ( (guess[letter] == curr_word[a_letter]) and (letter != a_letter) and
			(found[a_letter] != 1) ){
				found[a_letter] = 1;
				ans[letter] = 'Y';
				break;
			}
		}
	}
}

/***************************************************************************/
void testingdoWordsMatch(string s1, string s2) {
	if (doWordsMatch(s1, s2)) {
		cout << s1 << " and "<< s2 << " are matches!! :-)" << endl;
	}
	else {
		cout << s1 << " and "<< s2 << " do not match :-( " << endl;
	}
}

void testingfindGs(string s1,string s2, char chararr[], bool foundarr[]) {
	findGs(s1,s2,chararr,foundarr);
	for (int i = 0; i < 5; i++){
		cout << s1[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++){
		cout << s2[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++){
		cout << chararr[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++){
		cout << foundarr[i] << " ";
	}
	cout << endl;
	cout << "**********************************" << endl;
	for (int i = 0; i < 5; i++ ) {
		chararr[i] = ' ';
		foundarr[i] = 0;
	}
}

void testingfindYs(string s1,string s2, char chararr[], bool foundarr[]) {
	findYs(s1,s2,chararr,foundarr);
	for (int i = 0; i < 5; i++){
		cout << s1[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++){
		cout << s2[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++){
		cout << chararr[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++){
		cout << foundarr[i] << " ";
	}
	cout << endl;
	cout << "**********************************" << endl;
	for (int i = 0; i < 5; i++ ) {
		chararr[i] = ' ';
		foundarr[i] = 0;
	}
}

void playGame(int num_words, string arr[]) {
	/*
	 * This function allows players to replay the wordle game or exit
	 * depending on the user's choice
	 *
	 * Params:
	 * num_words (int) - number of words that can be used for the game
	 * arr (string[]) - arr of possible words that can be used for the game
	 */
	string keepPlaying = "Y";
	while ((keepPlaying == "Y") || (keepPlaying == "y")) {
		reset_ans_list();
		string curr_word = getWord(num_words, arr);
		//cout << curr_word<< endl;
		bool f = startGuessing(curr_word);
		if (f) {
			cout << "You won!! You guessed: " << curr_word << endl;
			cout << endl;
		}
		else {
			cout << "Sorry, you did not win. The word was: " << curr_word << endl;
			cout << endl;
		}
		cout << "Play Again (Y\\N)? ";
		cin >> keepPlaying;
	}
	cout << "Thanks for playing! " << endl;
}

bool startGuessing(string curr_word) {
	bool flag = false;
	int i = 0;
	while (i < 5 && !flag) {
		string s;
		cout << "Guess a 5-letter word: ";
		cin >> s;
		flag = checkWord(s, curr_word);
		i++;
	}
	return flag;
}

bool checkWord(string guess, string curr_word) {
	if (doWordsMatch(guess,curr_word)) {
		return true;
	}
	else {
		char ans[5] = {' ',' ',' ',' ',' '};
		// ans is 5 chars long, initialized to blank characters.
		// if the guessed word has a char identical to the curr_word and in
		// the same place as the curr_word, the ans array's char space will get a 'G'
		// If the guess has a character that is in the curr_word, but isn't in
		// the correct location, the corresponding space will get a 'Y'.

		// (Example)
		// curr_word: adept
		// guess: sleep
		// ans: {' ',' ','G',' ','Y'}
		bool found[5] = {0,0,0,0,0};
		// found marks each letter in the curr_word that corresponds to a letter
		// in the guessed word with a 1 so that the same letter isn't rematch-ed
		// more than once.

		// (Example)
		// curr_word: prose
		// guess: sleep
		// ans: {'Y',' ','Y',' ','Y'}
		// found: {1,0,1,0,1}
		// found doesn't make the second e in sleep be an out-of-place letter in the curr_word.
		// there's only one e in prose, so both e's in sleep should not get a yellow 'Y' char
		findGs(guess, curr_word,ans, found);
		findYs(guess, curr_word, ans, found);
		ans_list[ans_ct*2] = guess;
		ans_list[ans_ct*2 + 1] = ans;
		ans_ct++;
		printResults();
	}
	return false;
}

void printResults() {
	for (int j = 0; j < ans_ct*2; j+=2) {
		for (int i = 0; i < 5; i++) {
			if (ans_list[j+1][i] == ' ') {
				//system("Color EF");
				cout << ans_list[j][i] << " ";
			}
			else if (ans_list[j+1][i] == 'G') {
				//system("Color AE");
				cout << ans_list[j][i] << " ";
			}
			else {
				//system("Color AD");
				cout << ans_list[j][i] << " ";
			}
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << ans_list[j+1][i] << " ";
		}
		cout << endl;
	}
}

string getWord(int num, string arr[]) {
	int x = rand() % num;
	string word;
	word = arr[x];
	return word;
}

void readFile(string fn, string arr[], int num_words) {
	ifstream infile(fn.c_str(),ios::in);
	string size;
	infile>>size;
	for (int i = 0; i < num_words; i++) {
		infile>>arr[i];
	}
	infile.close();
}

int getSize(string fn) {
	ifstream infile(fn.c_str(),ios::in);
	string size;
	infile>>size;
	int size_int = stoi(size);
	infile.close();
	return size_int;
}

void reset_ans_list() {
	for (int i = 0; i < 12; i++) {
		ans_list[i] = "";
	}
	ans_ct = 0;
}
