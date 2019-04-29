# ENGG1003-Assignment-1
A very simple cryptographic system that implements Encryption and Decryption for Caesar and Substitution ciphers.
Also has a cipher Cracking mode that attempts to break a ciphertext without a key.

# How To Use 
- compile by "gcc *.c"
- commands are issued by <cipher-type> <mode> <input-file> <output-file>
- cipher-type arguments: caesar (rotation), substitution
- mode arguments: encrypt, decrypt, crack
- input-file: for encrypt and decrypt the first line should read KEY: ####, with either a number from 0 - 25 for caesar, or an alphabet string for substitution.
- cracking: to crack a caesar cipher without a key the program analyses single letter frequencies in the input-file and attempts to find a suitable key for the most occuring letter frequencies. The program will output the attempt at a cracked message to the user and ask for verification of legibility of the message.
