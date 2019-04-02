/*
 * Assignment 1: a simple cryptographic system which implements Caeasr and Substitution ciphers.
 * Name: Jordan Chappell
 * Student No: c3230100
 * Date Created: 2/04/2019
 * File: FileReaderWriter.c
 * Description: Handles reading and writing of files required for Assignment 1.
*/

#include "Assignment1.h"

#define KEY_MAX 27
#define CAESAR_KEY 2
#define SUB_KEY 27

/*
* Precondition: -> some arguments passed by pointer (mutation of the value is now possible).
*				-> inputFileName: pointer to string containing the file to be openend.
*				-> mode: an integer used to determine the mode of the current read, should be in range [0,2].
*				-> inputText: pointer to a string to read plain/cipher text into.
*				-> key: pointer to a char to read the key into.
* Postcondition: -> inputText points to a string in memory.
*				 -> key points to a single digit for caesar and a string for substitution.
*				 -> returns 0 on success, -1 on a failure.
*/
int ReadFile(char *inputFileName, int mode, char **inputText, char **key) {
	FILE *filePtr;									//initialize a pointer to a file
	filePtr = fopen(inputFileName, "r");			//open the file passed as an argument to this function in read only mode
	if (filePtr == NULL) {							//check that the file opened correctly
		printf("ERROR: Opening file \"%s\".", inputFileName);
		return -1;
	}
	switch (mode) {
		//mode = 0: expects text and key in the file, encryption and decryption
		case 0:
		case 1: ;
				*inputText = malloc(MAX_LINE);							//allocate enough memory for the text line
				if (fgets(*inputText, MAX_LINE, filePtr) == NULL) {		//read the first line in the file, check that some data was read
					printf("ERROR: reading plain/ciphertext line from %s, check file contents.\n", inputFileName);
					return -1;											//return a -1 to indicate a failure
				}
				(*inputText)[strlen(*inputText) - 1] = '\0';			//replace the \n at the end of string with \0
				*key = malloc(KEY_MAX);									//allocate enough memory for the key line
				if (fgets(*key, KEY_MAX, filePtr) == NULL) {			//read the next line, check that fgets read some data
					printf("ERROR: reading key line from %s, check file contents.\n", inputFileName);
					return -1;
				}  
				//test that keylength matches expected input
				if (strlen(*key) != 1 && strlen(*key) != 26) {
					printf("ERROR: unexpected key length in %s, check file contents.\n", inputFileName);
					return -1;
				}
				break;
		//mode = 2: expects only a ciphertext in the file, cracking
		case 2: *inputText = malloc(MAX_LINE);
				if (fgets(*inputText, MAX_LINE, filePtr) == NULL) {		//read the first line in the file, check that some data was read
					printf("ERROR: reading ciphertext line from %s, check file contents.\n", inputFileName);
					return -1;											//return a -1 to indicate a failure
				}
				(*inputText)[strlen(*inputText) - 1] = '\0';			//replace the \n at the end of string with \0
				break;
		default: printf("ERROR: unexpected input to ReadFile(), expected mode: [0,2], recieved: %d", mode);
				break;
	}
	return 0;
}

/*
* Precondition: requires a pointer to a filename
* Postcondition:
*/
int WriteFile(char *outputFileName, char *outputText, char *key) {
	FILE *filePtr;
	filePtr = fopen(outputFileName, "w");			//open the given file in write mode
	if (filePtr == NULL) {							//check that the file opened correctly
		printf("ERROR: Opening file \"%s\".", outputFileName);
		return -1;
	}
	if (fwrite(outputText, strlen(outputText), 1, filePtr) == 0) {	//write the outputText to the file, check that the data is written correctly
		printf("\tERROR: Writing output file has failed\n");
		return -1;
	} 

	return 0;
}