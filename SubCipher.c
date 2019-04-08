/*
 * Assignment 1: a simple cryptographic system which implements Caeasr and Substitution ciphers.
 * Name: Jordan Chappell
 * Student No: c3230100
 * Date Created: 5/04/2019
 * File: SubCipher.c
 * Description: Implement a substitution cipher, a direct 1:1 mapping from one alphabet letter to another.
*/

#include "Assignment1.h"

int testUniqueChars(char *string);

/* 
* Precondition: requires two strings "plaintext" and "key", and a pointer to a string to store the ciphertext in
* Postcondition: "ciphertext" should now point to allocated memory containing the encrypted message, returns 0 on a success, else -1
*/
int SubEncrypt(char *plaintext, char *key, char **ciphertext) {
	if (testUniqueChars(key) == 0) {
		printf("ERROR: key for substitution cipher contains duplicate letter mappings.\n");
		return -1;
	}
	return 0;
}

/* 
* Precondition: requires two strings "ciphertext" and "key", and a pointer to a string to store the decrypted plaintext in
* Postcondition: "plaintext" should now point to allocated memory containing the decrypted message, returns 0 on a success, else -1
*/
int SubDecrypt(char *ciphertext, char *key, char **plaintext) {

	return 0;
}

/* 
* Precondition: requires a string "ciphertext" to decrypt, and a pointer to a string to store the plaintext in
* Postcondition: "plaintext" should now point to allocated memory containing the decrypted message, returns 0 on a success, else -1
*/
int SubCrack(char *ciphertext, char **plaintext) {

	return 0;
}

/* 
* Precondition: single argument should be a string
* Postcondition: checks all characters in input string, returns 0 if duplicate letters detected, else 1
*/
int testUniqueChars(char *string) {
	for (int i = 0; i < strlen(string) - 1; i++) {
		for (int j = i + 1; j < strlen(string); j++) {
			if (string[i] == string[j]) {
				return 0;
			}
		}
	}
	return 1;
}
