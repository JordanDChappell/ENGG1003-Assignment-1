/*
 * Assignment 1: a simple cryptographic system which implements Caeasr and Substitution ciphers.
 * Name: Jordan Chappell
 * Student No: c3230100
 * Date Created: 2/04/2019
 * File: FileReaderWriter.c
 * Description: Handles reading and writing of files required for Assignment 1.
*/

#include "Assignment1.h"

#define CAESAR_KEY 3
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
	/* Read the message to be encrypted or decrypted in the first line of the file */
	*inputText = malloc(MAX_LINE);
	if (fgets(*inputText, MAX_LINE, filePtr) == NULL) {		//read the first line in the file, check that some data was read
		printf("ERROR: reading plaintext/ciphertext line from %s, check file contents.\n", inputFileName);
		return -1;											//return a -1 to indicate a failure
	}
	(*inputText)[strlen(*inputText) - 1] = '\0';			//replace the \n at the end of string with \0
	/* Cover cases for different modes of operation */
	switch (mode) {
		/* Mode = 0: expects text and key in the file, key should be an integer between (0, 25) */
		case 0:	;
				*key = malloc(CAESAR_KEY);						//allocate enough memory for the key line
				if (fgets(*key, CAESAR_KEY, filePtr) == NULL) {	//read the next line, check that fgets read some data
					printf("ERROR: reading key line from %s, check file contents.\n", inputFileName);
					return -1;
				}  
				if (strlen(*key) > 2) {							//sanity check for a caesar cipher key, should be < 2 in length
					printf("strlen(key): %d\n", strlen(*key));
					printf("ERROR: during Caesar cipher read, unexpected key in %s, expected number (0, 25), recieved %s.\n", inputFileName, *key);
					return -1;
				}
				break;
		/* Mode = 1: expects text and key in file, key should be a string of unique alphabet characters, must include all letters */
		case 1: ;
				*key = malloc(SUB_KEY);							//allocate 27 bytes of memory, 26 letters in key + 1 for null terminal
				if (fgets(*key, SUB_KEY, filePtr) == NULL) {	//read the next line, check that fgets read some data
					printf("ERROR: reading key line from %s, check file contents.\n", inputFileName);
					return -1;
				}  
				if (strlen(*key) != 26) {						//sanity check for sub cipher key, should be exactly 26 characters
					printf("ERROR: During Substitution cipher read, unexpected key in %s, expected alphabet string, recieved %s.\n", inputFileName, *key);
					return -1;
				}
		/* Mode = 2, do nothing, already read the message in the file */
		case 2: break;
		/* Default, error handling, print message to error, return -1 to program */
		default: printf("ERROR: unexpected input to ReadFile(), expected mode: [0,2], recieved: %d", mode);
				 return -1;
				 break;
	}

	return 0;
}

/*
* Precondition: requires a pointer to a filename, a string of output and a key string
* Postcondition: writes the output text and key to a file named outputFileName, returns 0 on success, else returns -1
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
	if (fwrite("\n", 1, 1, filePtr) == 0) {							//write a newline to the file
		printf("\tERROR: Writing output file has failed\n");
		return -1;
	}
	if (fwrite(key, strlen(key), 1, filePtr) == 0) {				//write the key to the file, check that the data is written correctly
		printf("\tERROR: Writing output file has failed\n");
		return -1;
	} 

	return 0;
}