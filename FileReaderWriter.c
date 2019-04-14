/*
 * Assignment 1: a simple cryptographic system which implements Caeasr and Substitution ciphers.
 * Name: Jordan Chappell
 * Student No: c3230100
 * Date Created: 2/04/2019
 * File: FileReaderWriter.c
 * Description: Handles reading and writing of files required for Assignment 1.
*/

#include "Assignment1.h"

#define CAESAR_KEY 2
#define SUB_KEY 26

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
	char buf[MAX_LINE];								//buffer to read lines into
	char header[4];									//used to hold the KEY: portion of the file header
	FILE *filePtr;									//initialize a pointer to a file
	filePtr = fopen(inputFileName, "r");			//open the file passed as an argument to this function in read only mode
	if (filePtr == NULL) {							//check that the file opened correctly
		printf("ERROR: Opening file \"%s\".", inputFileName);
		return -1;
	}

	/* Read the file header, should contain KEY: followed by the key, only read on ENCRYPT and DECRYPT operations */
	if (mode != 2) {
		if (fgets(buf, MAX_LINE, filePtr) == NULL) {
			printf("ERROR: reading key header in %s\n", inputFileName);
		}
	}

	/* Cover cases for different modes of operation */
	switch (mode) {
		/* Mode = 0: key should be an integer between (0, 25) */
		case 0:	;
				*key = malloc(CAESAR_KEY + 1);						//allocate enough memory for the key line
				sscanf(buf, "%s %s", header, *key);					//split the keyHeader string into the header and key portions
				if (strcmp(header, "KEY:")) {						//test that header == "KEY:"
					printf("ERROR: reading key header from file %s, expected KEY:..., recieved %s...\n", inputFileName, header);
				}
				if (strlen(*key) > 2) {								//sanity check for a caesar cipher key, should be < 2 in length
					printf("strlen(key): %d\n", strlen(*key));
					printf("ERROR: during Caesar cipher read, unexpected key in %s, expected number (0, 25), recieved %s.\n", inputFileName, *key);
					return -1;
				}
				break;
		/* Mode = 1: key should be a string of unique alphabet characters, must include all letters */
		case 1: ;
				*key = malloc(SUB_KEY + 1);							//allocate 27 bytes of memory, 26 letters in key + 1 for null terminal
				sscanf(buf, "%s %s", header, *key);
				if (strcmp(header, "KEY:")) {						//test that header == "KEY:"
					printf("ERROR: reading key header from file %s, expected KEY:..., recieved %s...\n", inputFileName, header);
				}
				printf("%d\n", strlen(*key));
				if (strlen(*key) != 26) {							//sanity check for sub cipher key, should be exactly 26 characters
					printf("ERROR: During Substitution cipher read, unexpected key in %s, expected alphabet string, recieved %s.\n", inputFileName, *key);
					return -1;
				}
		/* Mode = 2, do nothing, no key to allocate */
		case 2: break;
		/* Default, error handling, print message to error, return -1 to program */
		default: printf("ERROR: unexpected input to ReadFile(), expected mode: [0,2], recieved: %d", mode);
				 return -1;
				 break;
	}
	int currentPos = ftell(filePtr);							//save the current position of the cursor in filePtr
	fseek(filePtr, 0L, SEEK_END);								//move to the end of the file
  	int remainingSize = ftell(filePtr);							//store the end byte offset as the size of file
  	fseek(filePtr, currentPos, SEEK_SET); 						//move back to the line after key header
	/* Read the message to be encrypted or decrypted in the rest of the file */
	*inputText = malloc(remainingSize);							//allocate memory for message contents
	fread(*inputText, remainingSize, 1, filePtr);				//read all contents of file at once
	(*inputText)[strlen(*inputText) - 1] = '\0';				//replace the \n at the end of string with \0

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
	fprintf(filePtr, "%s%s\n", "KEY: ", key);
	if (fwrite(outputText, strlen(outputText), 1, filePtr) == 0) {	//write the outputText to the file, check that the data is written correctly
		printf("\tERROR: Writing output file has failed\n");
		return -1;
	} 

	return 0;
}