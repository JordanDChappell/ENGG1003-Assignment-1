/*
 * Assignment 1: a simple cryptographic system which implements Caeasr and Substitution ciphers.
 * Name: Jordan Chappell
 * Student No: c3230100
 * Date Created: 2/04/2019
 * File: Assignment1.c
 * Description: Main project file, runs the assignment.
*/

#include "Assignment1.h"

int main(int argc, char *argv[]) {	
	if (argc != 3) {
		printf("ERROR: unexpected command line arguments.");
		return -1;
	}

	char *inputFileName = argv[1];		//the first argument to command line
	char *outputFileName = argv[2];		//the second argument to command line

	char *inputText;					//holds the text that is read from the inputFile
	char *key;							//holds the key that is read from the inputFile

	if (ReadFile(inputFileName, 0, &inputText, &key) != 0) {
		return -1;
	}

	printf("Text in file (mode 0/1): %s\n", inputText);
	printf("Key in file: %s\n", key);

	if (WriteFile(outputFileName, 0, inputText) != 0) {
		return -1;
	}

	free(inputText);
	free(key);

	if (ReadFile(inputFileName, 2, &inputText, &key) != 0) {
		return -1;
	}

	printf("Ciphertext in file (mode 2): %s\n", inputText);

	free (inputText);

	return 0;
}