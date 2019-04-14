/*
 * Assignment 1: a simple cryptographic system which implements Caeasr and Substitution ciphers.
 * Name: Jordan Chappell
 * Student No: c3230100
 * Date Created: 5/04/2019
 * File: SubCipher.c
 * Description: Implement a substitution cipher, a direct 1:1 mapping from one alphabet letter to another.
*/

#include "Assignment1.h"

int TestUniqueChars(char *string);
int GetIndexOf(char *string, char c);
int LetterDistAnalysis(char *string);

char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/* 
* Precondition: requires two strings "plaintext" and "key", and a pointer to a string to store the ciphertext in
* Postcondition: "ciphertext" should now point to allocated memory containing the encrypted message, returns 0 on a success, else -1
*/
int SubEncrypt(char *plaintext, char *key, char **ciphertext) {
	if (TestUniqueChars(key) == 0) {														//the input key should be a string of unique characters
		printf("ERROR: key for substitution cipher contains duplicate letter mappings.\n");
		return -1;
	}
	*ciphertext = malloc(strlen(plaintext) + 1);											//allocate memory for the encrypted message
	for (int i = 0; i < strlen(plaintext); i++) {											//loop over the entire plaintext
		if (plaintext[i] >= 65 && plaintext[i] <= 90) {										//test ASCII ranges, uppercase just encrypt
			(*ciphertext)[i] = key[plaintext[i] - 65];										//encrypt by lookup in the keystring, subtract 65 to get [0, 25]
		} else if (plaintext[i] >= 97 && plaintext[i] <= 122) {								//lowercase can simply subtract 32 from the letter
			(*ciphertext)[i] = key[plaintext[i] - 65 - 32];
		} else {																			//case covers non-letter characters, don't encrypt
			(*ciphertext)[i] = plaintext[i];					
		}
	}																						//e.g. key[0] = key[A] = first element of key string
	(*ciphertext)[strlen(plaintext)] = '\0';												//null terminating char at end of string
	return 0;
}

/* 
* Precondition: requires two strings "ciphertext" and "key", and a pointer to a string to store the decrypted plaintext in
* Postcondition: "plaintext" should now point to allocated memory containing the decrypted message, returns 0 on a success, else -1
*/
int SubDecrypt(char *ciphertext, char *key, char **plaintext) {
	if (TestUniqueChars(key) == 0) {
		printf("ERROR: key for substitution cipher contains duplicate letter mappings.\n");
		return -1;
	}
	char current;																			//holds current ciphertext character for searching in key string
	*plaintext = malloc(strlen(ciphertext) + 1);											//allocate strlen() + 1 for null terminal '\0'
	for (int i = 0; i < strlen(ciphertext); i++) {
		current = ciphertext[i];
		if (current >= 65 && current <= 90) {							
			(*plaintext)[i] = alphabet[GetIndexOf(key, current)];							//search the key for index of ciphertext character
		} else if (current >= 97 && current <= 122) {										//use that index to lookup the correct letter
			current -= 32;	
			(*plaintext)[i] = alphabet[GetIndexOf(key, current)];
		} else {													
			(*plaintext)[i] = current;					
		}
	}																						
	return 0;
}

/* 
* Precondition: requires a string "ciphertext" to decrypt, and a pointer to a string to store the plaintext in
* Postcondition: "plaintext" should now point to allocated memory containing the decrypted message, returns 0 on a success, else -1
*/
int SubCrack(char *ciphertext, char **plaintext) {
	printf("NOT IMPLEMENTED\n");
	return -1;
}

/* 
* Precondition: single argument should be a string
* Postcondition: checks all characters in input string, returns 0 if duplicate letters detected, else 1
*/
int TestUniqueChars(char *string) {
	for (int i = 0; i < strlen(string) - 1; i++) {
		for (int j = i + 1; j < strlen(string); j++) {
			if (string[i] == string[j]) {
				return 0;
			}
		}
	}
	return 1;
}

/* 
* Precondition: arguments should be a string 'string' and a char 'c' to search index of
* Postcondition: returns the index that c occurs in string
*/
int GetIndexOf(char *string, char c) {
	int index;							//declare integer to hold index of c
	char *found;						//found is a pointer used to calculate the index of c in string
	found = strchr(string, c);			//strchr() returns a pointer to first occurence of c in string
	index = (int)(found - string);		//index is determined by subracting the memory address of string from found
	return index;						//if string = ABC, pointers to chars are allocated in memory contiguously, B - A = index of B
}