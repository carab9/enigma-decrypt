# enigma-decrypt
This project is a Enigma-2 cryptographic machine decryption program. It reads a encrypted text, encrypt.txt, ecrypted by Enigma machine with two rotors, and no plug-board, stores it in a database, and then decrypts it to the original text and prints the decrypted text to stdout.

![image](https://github.com/carab9/enigma-decrypt/blob/main/enigma_machine1.png?raw=true)

![image](https://github.com/carab9/enigma-decrypt/blob/main/enigma_machine2.png?raw=true)

## Architecture

The main program uses a FileIO class object to read a encrypted text file and stores the data in a DataBase class object. Then it uses a Decrypt class object to decrypt the encrypted text and a UI class object to print the decrypted text to stdout.

## Requirements
C++ and C++ libraries: iostream, string, fstream, vector, map, tuple, algorithm

## Technical Skills
Decryption algorithm for Enigma-2 machine using C++ STL containers, such as vector, map, and tuple and a few function in STL algorithms.

## Results
The decrypted text printed in stdout.

![image](https://github.com/carab9/enigma-decrypt/blob/main/enigma_decrypted.png?raw=true)
