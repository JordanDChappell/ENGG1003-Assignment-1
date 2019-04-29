/*
 * Assignment 1: a simple cryptographic system which implements Caeasr and Substitution ciphers.
 * Name: Jordan Chappell
 * Student No: c3230100
 * Date Created: 27/04/2019
 * File: CrackingTools.c
 * Description: Some letter frequency analysis and sorting functions
*/

#include "Assignment1.h"

/*
* Precondition: requires a string "ciphertext" as argument
* Postcondition: returns an array with index corresponding to letter counts e.g. [0] = count(A), [1] = count(B)
*/
int * LetterFreqAnalysis(char *ciphertext) {
	static int letterFreq[26] = {0};		//initilize array of 26 integers to 0
	char letter;							//char to calculate a letters index
	/* Count occurrences of each letter in the ciphertext message */
	for (int i = 0; i < strlen(ciphertext); i++) {
		if (ciphertext[i] >= 65 && ciphertext[i] <= 90) {			//in the UPPERCASE ASCII range
			letter = ciphertext[i] - 65;							//letter is now a representation of an alphabet letter from [0, 26]
		} else if (ciphertext[i] >= 97 && ciphertext[i] <= 122) {	//in the lowercase ASCII range
			letter = ciphertext[i] - 32 - 65;
		}
		letterFreq[letter] = letterFreq[letter] + 1;
	}
	return letterFreq;
}

/*
* Precondition: requires two array arguments and an integer n to determine array length
* Postcondition: sorts both arrays by the freqArr in descending order
*/
void BubbleSort(int *freqArr, char *letterArr, int n) { 
	//sort two arrays at the same time by the first array
	for (int i = 0; i < (n - 1); i++) {    
		// Last i elements are already in place     
		for (int j = 0; j < n - i - 1; j++) {  
			if (freqArr[j] < freqArr[j + 1]) {		//comparison between current position and next position
				int temp = freqArr[j];				//a temp value to swap the current indices
				freqArr[j] = freqArr[j + 1];		//swap the current position and next pos
				freqArr[j + 1] = temp;				//next pos is now temp (current pos)		
				char temp2 = letterArr[j];			//repeat for the letter array
				letterArr[j] = letterArr[j + 1];
				letterArr[j + 1] = temp2;
			}
		}
	}
} 