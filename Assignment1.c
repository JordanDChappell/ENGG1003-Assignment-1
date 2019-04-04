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
	if (argc != 3) {
		printf("ERROR: unexpected command line arguments.");
		return -1;
	}

	char *inputFileName = argv[1];		//the first argument to command line
	char *outputFileName = argv[2];		//the second argument to command line

	char *plaintext;					//holds the text that is read from the inputFile
	char *ciphertext;
	char *key;							//holds the key that is read from the inputFile

	if (ReadFile(inputFileName, 0, &plaintext, &key) != 0) {
		return -1;
	}

	printf("Text in file (mode 0/1): %s\n", plaintext);
	printf("Key in file: %s\n", key);

	printf("CaesarCipher test:\n");
	if (CaesarEncrypt(plaintext, (int) *key - 48, &ciphertext)) {
		return -1;
	} 
	printf("%s encrypted with k=1 -> %s\n", plaintext, ciphertext);
	if (CaesarDecrypt(ciphertext, (int) *key - 48, &plaintext)) {
		return -1;
	}
	printf("%s decypted with k=1 -> %s\n", ciphertext, plaintext);

	if (WriteFile(outputFileName, ciphertext, key) != 0) {
		return -1;
	}

	free(plaintext);
	free(ciphertext);
	free(key);

	return 0;
}