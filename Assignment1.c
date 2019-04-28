/*
 * Assignment 1: a simple cryptographic system which implements Caeasr and Substitution ciphers.
 * Name: Jordan Chappell
 * Student No: c3230100
 * Date Created: 2/04/2019
 * File: Assignment1.c
 * Description: Main project file, runs the assignment.
*/

#include "Assignment1.h"

/*
* Requires 3 commandline arguments:
* 		-> argv[1]: encrypt/decrypt/crack, should simply be a string to indicate job to perform.
*		-> argv[2]: encyption method, should be rotation/caesar or substitution.
*		-> argv[2]: filename, the input filename which has the required information.
*/
int main(int argc, char *argv[]) {	
	/* Sanity check, make sure user has entered 2 command line args (3 = 2 + run command) */
	if (argc != 5) {
		printf("ERROR: unexpected command line arguments, expected <cipher> <mode> <(input).txt> <(output).txt>.");
		return -1;
	}

	/* Variable initialization */
	char *cipherString = argv[1];		//first argument is the cipher type
	char *modeString = argv[2];			//second argument is mode
	char *inputFileName = argv[3];		//the third argument to command line
	char *outputFileName = argv[4];		//the fourth argument to command line
	char *inputText;					//holds the text that is read from the inputFile
	char *outputText;					//holds message to output
	char *key;							//holds the key that is read from the inputFile
	int cipher;							//flag to determine which cipher will be used
	int mode;							//flag to determine which mode will be run

	/* Sanity checks for cipher type command line argument */
	if (strcmp(cipherString, "substitution") == 0) {
		cipher = 1;
	} else if (strcmp(cipherString, "caesar") == 0 || strcmp(cipherString, "rotation") == 0) {
		cipher = 0;
	} else {
		printf("Unexpected cipher argument, expected caesar/substitution, recieved %s\n", cipherString);
	}
	
	/* Sanity checks for mode command line argument */
	if (strcmp(modeString, "encrypt") == 0) {
		mode = ENCRYPT;
	} else if (strcmp(modeString, "decrypt") == 0) {
		mode = DECRYPT;
	} else if (strcmp(modeString, "crack") == 0) {
		mode = CRACK;
	} else {
		printf("Unexpected mode argument, expected encrypt/decrypt/crack, recieved %s\n", modeString);
		return -1;
	}

	/* Main method body - do something here */
	if (ReadFile(inputFileName, mode, cipher, &inputText, &key) != 0) {		//error checking for ReadFile function, on success should be 0
		return -1;
	}

	switch (cipher) {
		/* CIPHER = CAESAR/ROTATIONAL */
		case 0:
				if (mode == 0) {
					printf("Caesar Cipher: (Encrypt)\n");
					if (CaesarEncrypt(inputText, atoi(key), &outputText) != 0) {
						return -1;
					}
					WriteFile(outputFileName, outputText, key);
					printf("Key: %5s\nMessage:\n%s\n\nEncrypted Message:\n%s\n", key, inputText, outputText);
				} else if (mode == 1) {
					printf("Caesar Cipher: (Decrypt)\n");
					if (CaesarDecrypt(inputText, atoi(key), &outputText) != 0) {
						return -1;
					}
					WriteFile(outputFileName, outputText, key);
					printf("Key: %5s\nMessage:\n%s\n\nDecrypted Message:\n%s\n", key, inputText, outputText);
				} else if (mode == 2) {
					if (CaesarCrack(inputText, &outputText, &key) != 0) {
						return -1;
					}
					WriteFile(outputFileName, outputText, key);
				} else {
					printf("ERROR: unexpected value for MODE variable, exiting application\n");
					return -1;
				}
				break;
		/* CIPHER = Substitution */
		case 1: 
				if (mode == 0) {
					printf("Substitution Cipher: (Encrypt)\n");
					if (SubEncrypt(inputText, key, &outputText) != 0) {
						return -1;
					}
					WriteFile(outputFileName, outputText, key);
					printf("Key: %5s\nMessage:\n%s\n\nEncrypted Message:\n%s\n", key, inputText, outputText);
				} else if (mode == 1) {
					printf("Substitution Cipher: (Decrypt)\n");
					if (SubDecrypt(inputText, key, &outputText) != 0) {
						return -1;
					}
					WriteFile(outputFileName, outputText, key);
					printf("Key: %5s\nMessage:\n%s\n\nDecrypted Message:\n%s\n", key, inputText, outputText);
				} else if (mode == 2) {
					if (SubCrack(inputText, &outputText, &key) != 0) {
						return -1;
					}
					WriteFile(outputFileName, outputText, key);
				} else {
					printf("ERROR: unexpected value for MODE variable, exiting application\n");
					return -1;
				}
				break;

		default:
				printf("ERROR: unexpected value for CIPHER variable, exiting application\n"); 
				return -1;
				break;
	}
	
	/* Free allocated memory before end of program */
	free(inputText);
	free(outputText);
	free(key);

	return 0;
}