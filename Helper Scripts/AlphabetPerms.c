/*
 * Name: Jordan Chappell
 * Student No: c3230100
 * Date Created: 2/04/2019
 * File: AlphabetPerms.c
 * Description: Simple script to generate an alphabet permutation for use as a substitution cipher key.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char current;
	char swap;

	srand(time(0));						//seed random number generator for this session using time

	/* Randomly swap characters in the alphabet string */
	for (int i = 0; i < 26; i++) {
		int ranIndex = rand() % 25;
		current = alphabet[i];			//grab the current index
		swap = alphabet[ranIndex];		//swap is the random index
		alphabet[i] = swap;				//swap values
		alphabet[ranIndex] = current;
				
	}

	printf("%s\n", alphabet);

}