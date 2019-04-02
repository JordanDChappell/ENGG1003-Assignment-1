/*
 * Assignment 1: a simple cryptographic system which implements Caeasr and Substitution ciphers.
 * Name: Jordan Chappell
 * Student No: c3230100
 * Date Created: 2/04/2019
 * File: Assignment1.h
 * Description: Assignment 1 Header File. Contains macro defines and function prototypes.
*/

#ifndef ASSIGNMENT_1_H
#define ASSIGNMENT_1_H

/* ------ INCLUDES ------ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* ------ MACRO DEFINITIONS ------ */
#define ENCRYPT 0
#define DECRYPT 1
#define CRACK 2
#define MAX_LINE 128

/* ------ FUNCTION PROTOTYPES ------ */

/* FileReaderWriter */
int ReadFile(char *inputFileName, int mode, char **inputText, char **key);
int WriteFile(char *outputFileName, char *outputText, char *key);


#endif