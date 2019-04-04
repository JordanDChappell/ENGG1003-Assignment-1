/*
 * Assignment 1: a simple cryptographic system which implements Caeasr and Substitution ciphers.
 * Name: Jordan Chappell
 * Student No: c3230100
 * Date Created: 2/04/2019
 * File: CaesarCipher.c
 * Description: Implement the rotational cipher algorithm, shift an alphabet by n.
*/

#include "Assignment1.h"

/* 
* Precondition:
* Postcondition: encrypts the given plaintext, using key, allocates memory and points to the ciphertext, returns 0 on succeed, else -1
*/
int CaesarEncrypt(char *plaintext, int key, char **ciphertext) {
	if (key < 0 || key > 25) {										//error checking for an invalid key
		printf("ERROR: CaesarEncrypt expects a key in range(0,25), recieved %d\n", key);
		return -1;													//return -1 allows error to bubble up the program
	}
	*ciphertext = malloc(strlen(plaintext));						//allocate memory for the ciphertext, +1 for the null terminating character
	for (int i = 0; i < strlen(plaintext); i++) {
		if (plaintext[i] >= 65 && plaintext[i] <= 90) {				//in the UPPERCASE ASCII range
			(*ciphertext)[i] = (plaintext[i] - 65 + key) % 26;		//encrypt the plaintext using the key
			(*ciphertext)[i] += 65;									// -65 moves the ascii into the 0 - 26 range, need to correct this by adding 65
		} else if (plaintext[i] >= 97 && plaintext[i] <= 122) {		//in the lowercase ASCII range
			(*ciphertext)[i] = (plaintext[i] - 32 - 65 + key) % 26;	//convert to UPPERCASE ASCII and encrypt using key
			(*ciphertext)[i] += 65;
		} else {													//outside the alphabet range
			(*ciphertext)[i] = plaintext[i];						//do not encrypt
		}
	}
	(*ciphertext)[strlen(plaintext)] = '\0';						//null terminating character
	return 0;
}

/* 
* Precondition:
* Postcondition: decrypts the given ciphertext, using key, allocates memory and points to the plaintext, returns 0 on succeed, else -1
*/
int CaesarDecrypt(char *ciphertext, int key, char **plaintext) {
	if (key < 0 || key > 25) {										//error checking, key should be in range (0, 25)
		printf("ERROR: CaesarDecrypt expects a key in range [0,25], recieved %d\n", key);
		return -1;
	}	
	*plaintext = malloc(strlen(ciphertext) + 1);					//allocate memory for the ciphertext, +1 for the null terminating character
	for (int i = 0; i < strlen(ciphertext); i++) {
		if (ciphertext[i] >= 65 && ciphertext[i] <= 90) {			//in the UPPERCASE ASCII range
			(*plaintext)[i] = (ciphertext[i] - 65 - key) % 26;		//decrypt the plaintext using the key
			(*plaintext)[i] += 65;									// -65 moves the ascii into the 0 - 26 range, need to correct this by adding 65
		} else if (ciphertext[i] >= 97 && ciphertext[i] <= 122) {	//in the lowercase ASCII range
			(*plaintext)[i] = (ciphertext[i] - 32 - 65 - key) % 26;	//convert to UPPERCASE ASCII and encrypt using key
			(*plaintext)[i] += 65;
		} else {													//outside the alphabet range
			(*plaintext)[i] = ciphertext[i];						//do not encrypt
		}
	}
	(*plaintext)[strlen(ciphertext)] = '\0';						//null terminating character
	return 0;
}

/* 
* Precondition:
* Postcondition: decrypts the given ciphertext, no key (crack/break), allocates memory and points to the plaintext
*/
int CaesarCrack(char *ciphertext, char **plaintext) {

}