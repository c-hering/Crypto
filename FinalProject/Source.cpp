#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>
#include <stdlib.h>
using namespace std;

void encrypt();
void decrypt();
void ccipherE();
void atbashE();
void a1b2E();
void newAlphE();
void bifidE();
void ccipherD();
void atbashD();
void a1b2D();
void newAlphD();
void bifidD();
void combine(int coords[64]);
void loadingBar();
void print(char c, int ln);

char ud = 186;
char tlc = 201;
char blc = 200;
char trc = 187;
char brc = 188;
char tb = 205;
char tr = 204;
char tl = 185;

string input;
int ln;
int counter = 0;
int trans_coords[128];
char square[5][5] = {
	{ 'a','b','c','d','e' },
	{ 'f','g','h','i','k' },
	{ 'l','m','n','o','p' },
	{ 'q','r','s','t','u' },
	{ 'v','w','x','y','z' }
};

//USED TO CREATE LINES OF A CHAR FOR ANIMATIONS AND LOOKS
void print(char c, int ln) {
	for (int i = 0; i < ln; i++) {
		cout << c;
	}
}

//USED FOR THE LOADING BAR IN THE BEGINNING OF THE PROGRAM STARTUP
void loadingBar() {
	int length = 25;
	char c = 219;
	for (int i = 0; i < length; i++) {
		Sleep(300);
		cout << c;
	}
	cout << endl;
}


//THIS IS THE DECRYPTION METHOD FOR THE BIFID CIPHER
void bifidD() {
	int coords[128];
	int new_coords[64][2];
	int c1 = 0;
	int c2 = ln;
	int c = 0;

	cout << endl << endl;
	cin.ignore();
	cout << "please input a phrase that is from 0 - 64 chars long without spaces or puncuation: ";
	getline(cin, input);
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	for (int i = 0; i < ln; i++) {
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++) {
				if (input[i] == square[y][x]) {
					coords[c] = y;
					coords[c + 1] = x;
				}
			}
		}
		c += 2;
	}
	cout << endl;
	for (int o = 0; o < ln; o++) {
		new_coords[o][0] = coords[c1];
		new_coords[o][1] = coords[c2];
		c1++;
		c2++;
	}
	cout << endl << endl;
	cout << "Decrypted: ";
	for (int u = 0; u < ln; u++) {
		cout << square[new_coords[u][0]][new_coords[u][1]];
	}
	cout << endl;
	cout << endl << endl;
}

//THIS IS THE DECRYPTION METHOD FOR THE KEYWORD ALPHABET CIHPER
void newAlphD() {
	string key;
	string input;
	string alph = "abcdefghijklmnopqrstuvwxyz";
	string new_alph;
	string final;
	string decrypted;
	int input_ln;
	int key_ln;
	bool isInKey;
	int test;

	input = "";
	key = "";
	new_alph = "";
	final = "";
	decrypted = "";

	cout << endl << endl;
	cin.ignore();
	cout << "Phrase: ";
	getline(cin, input);
	cout << "Key: ";
	cin >> key;
	cin.ignore();
	key_ln = key.length();
	input_ln = input.length();
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	input.erase(remove(input.begin(), input.end(), ' '), input.end());
	for (int i = 0; i < 26; i++) {
		isInKey = false;
		for (int x = 0; x < key_ln; x++) {
			if (key[x] == alph[i]) {
				isInKey = true;
			}
		}
		if (isInKey == false) {
			new_alph += alph[i];
		}
	}
	final = key + new_alph;
	for (int i = 0; i < input_ln; i++) {
		for (int y = 0; y < 26; y++) {
			if (input[i] == final[y]) {
				decrypted += alph[y];
			}
		}
	}
	cout << endl << endl;
	cout << decrypted << endl;
	cout << endl << endl;
}

//THIS IS THE DECRYPTION METHOD FOR THE A-1, B-2... CIPHER
void a1b2D() {
	string input;
	string final;
	int ln;
	bool running = true;

	cout << endl << endl;
	cin.ignore();
	cout << "please input each number individualy, pressing enter after each and enter 'e' to end the phrase: ";
	while (running) {
		getline(cin, input);
		if (input == "e") {
			cout << "end" << endl;
			running = false;
		}
		else if (atoi(input.c_str()) > 26 || atoi(input.c_str()) < 1) {
			cout << "All numbers have to be less than or equal to 26 and greater than or equal to 1" << endl;
			cout << ": ";
		}
		else {
			final += static_cast<char>(96 + atoi(input.c_str()));
			cout << ": ";
		}
	}
	cout << endl << endl;
	cout << "Decrypted: ";
	cout << final << endl;
	cout << endl << endl;
}

//THIS IS THE DECRYPTION METHOD FOR THE ATBASH CIPHER
void atbashD() {
	string input;
	string output;
	int input_length;
	int subtractor;

	cout << endl << endl;
	cin.ignore();
	cout << "Enter phrase without spaces or puncuation: ";
	getline(cin, input);
	input_length = input.length();

	for (int i = 0; i < input_length; i++) {
		if (input[i] > 96 && input[i] < 123) {
			subtractor = 2 * (input[i] % 97);
			input[i] = input[i] + (25 - subtractor);
		}
		else if (input[i] > 64 && input[i] < 91) {
			subtractor = 2 * (input[i] % 65);
			input[i] = input[i] + (25 - subtractor);
		}
	}
	cout << endl << endl;
	cout << "Decrypted: ";
	cout << input << endl;
	cout << endl << endl;
}

//THIS IS THE DECRYPTION METHOD FOR THE CAESER CIPHER
void ccipherD() {
	string input;
	string output;
	int key;

	cout << endl << endl;
	cout << "Enter a negative shift key (number): ";
	cin >> key;
	cin.ignore();
	cout << "Enter a string without spaces or puncuation: ";
	getline(cin, input);

	int in_length = input.length();

	if (key > 26)
		key = key % 26;


	int fix = 0;

	for (int i = 0; i < in_length; i++) {
		if ((input[i] > 64 && input[i] < 91) || (input[i] > 96 && input[i] < 123)) {
			if ((input[i] + key) > 122 || ((input[i] + key) > 90 && (input[i] + key) < 97)) {
				fix = input[i] + key - 26;
				input[i] = fix;
			}
			else {
				input[i] += key;
			}
		}
	}

	cout << endl << endl;
	output = input;
	cout << "Decrypted: ";
	cout << output << endl;
	cout << endl << endl;
}

//THIS IS A METHOD THAT IS USED BY THE BIFID ENCRYPTION METHOD
void combine(int coords[64]) {
	for (int x = 0; x < ln; x++) {
		trans_coords[counter] = coords[x];
		counter++;
	}
}

//THIS IS THE ENCRYPTION METHOD FOR THE BIFID CIPHER
void bifidE() {
	char choice;
	int c1;
	int c2;
	int y_coords[64];
	int x_coords[64];
	int new_x;
	int new_y;
	int new_coords[64][2];
	char output[64];

	cout << endl << endl;
		counter = 0;
		fill(begin(y_coords), end(y_coords), 0);
		fill(begin(x_coords), end(x_coords), 0);
		c1 = 0;
		c2 = 1;
		cin.ignore();
		cout << "please input a phrase that is from 0 - 64 chars long without spaces or punctuation: ";
		getline(cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		ln = input.length();
		for (int i = 0; i < ln; i++) {
			for (int y = 0; y < 5; y++) {
				for (int x = 0; x < 5; x++) {
					if (input[i] == 'j') {
						input[i] == 'i';
					}
					if (input[i] == square[y][x]) {
						y_coords[i] = y;
						x_coords[i] = x;
					}
				}
			}
		}
		combine(y_coords);
		combine(x_coords);
		for (int o = 0; o < ln; o++) {
			new_coords[o][0] = trans_coords[c1];
			new_coords[o][1] = trans_coords[c2];
			c1 += 2;
			c2 += 2;
		}
		cout << endl << endl;
		cout << "Encrypted: ";
		for (int u = 0; u < ln; u++) {
			cout << square[new_coords[u][0]][new_coords[u][1]];
		}
		cout << endl;
		cout << endl << endl;
		counter = 0;
}

//THIS IS THE ENCRYPTION METHOD FOR THE KEYWORD ALPHABET CIPHER
void newAlphE() {
	string key;
	string input;
	string alph = "abcdefghijklmnopqrstuvwxyz";
	string new_alph;
	string final;
	string encrypted;
	int input_ln;
	int key_ln;
	bool isInKey;
	int test;

	input = "";
	key = "";
	new_alph = "";
	final = "";
	encrypted = "";

	cout << endl << endl;
	cin.ignore();
	cout << "Phrase (without spaces or puncuation: ";
	getline(cin, input);
	cout << "Key (word or string of letters without repeated letters): ";
	cin >> key;
	key_ln = key.length();
	input_ln = input.length();
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	input.erase(remove(input.begin(), input.end(), ' '), input.end());
	for (int i = 0; i < 26; i++) {
		isInKey = false;
		for (int x = 0; x < key_ln; x++) {
			if (key[x] == alph[i]) {
				isInKey = true;
			}
		}
		if (isInKey == false) {
			new_alph += alph[i];
		}
	}
	final = key + new_alph;
	cout << "New Alphabet: " << final << endl;

	for (int y = 0; y < input_ln; y++) {
		test = input[y] % 97;
		encrypted += final[test];
	}
	cout << endl << endl;
	cout << "Encrypted: ";
	cout << encrypted << endl;
	cout << endl << endl;
}

//THIS IS THE ENCRYPTION METHOD FOR THE A-1, B-2... CIPHER
void a1b2E() {
	string input;
	int input_length;
	int num;
	int output[64];

	cout << endl << endl;
		cin.ignore();
		fill(output, output + 64, 0);
		cout << "please input a phrase between 0 and 64 chars long (without using spaces and puncuation): ";
		getline(cin, input);
		input_length = input.length();
		transform(input.begin(), input.end(), input.begin(), ::tolower);

		for (int i = 0; i < input_length; i++) {
			if (input[i] > 96 && input[i] < 123) {
				num = (int)(input[i] % 96);
				output[i] = num;
			}
		}
		cout << endl << endl;
		cout << "Encrypted: ";
		for (int x = 0; x < input_length; x++) {
			if (output[x] == 0) {
				cout << input[x];
			}
			else {
				cout << output[x] << " - ";
			}
		}
		cout << endl;
		cout << endl << endl;
}

//THIS IS THE ENCRYPTION METHOD FOR THE ATBASH CIPHER
void atbashE() {
	string input;
	string output;
	int input_length;
	int subtractor;
	cout << endl << endl;
		cin.ignore();
		cout << "Enter phrase without spaces or puncuation: ";
		getline(cin, input);
		input_length = input.length();

		for (int i = 0; i < input_length; i++) {
			if (input[i] > 96 && input[i] < 123) {
				subtractor = 2 * (input[i] % 97);
				input[i] = input[i] + (25 - subtractor);
			}
			else if (input[i] > 64 && input[i] < 91) {
				subtractor = 2 * (input[i] % 65);
				input[i] = input[i] + (25 - subtractor);
			}
		}
		cout << endl << endl;
		cout << "Encrypted: ";
		cout << input << endl;
		cout << endl << endl;
}

//THIS IS THE ENCRYPTION METHOD FOR THE CAESER CIPHER
void ccipherE() {
	string input;
	string output;
	int key;

	cout << endl << endl;
		cout << "Enter a shift key (number): ";
		cin >> key;
		cin.ignore();
		cout << "Enter a string without spaces or puncuation: ";
		getline(cin, input);

		int in_length = input.length();

		if (key > 26)
			key = key % 26;


		int fix = 0;

		for (int i = 0; i < in_length; i++) {
			if ((input[i] > 64 && input[i] < 91) || (input[i] > 96 && input[i] < 123)) {
				if ((input[i] + key) > 122 || ((input[i] + key) > 90 && (input[i] + key) < 97)) {
					fix = input[i] + key - 26;
					input[i] = fix;
				}
				else {
					input[i] += key;
				}
			}
		}

		output = input;
		cout << endl << endl;
		cout << "Encrypted: ";
		cout << output << endl;
		cout << endl << endl;
}

//THIS IS A METHOD THAT ACTS AS A SUB MENU OF THE MAIN MENU, THIS MENU IS THE 'SWITCH' FOR ALL THE ENCRYPTION METHODS
void encrypt() {
	int in;
	bool running = true;
	cout << endl << endl;
	cout << tlc;
	print(tb, 43);
	cout << trc << endl;
	cout << ud << " What encryption would you like to choose? " << ud << endl;
	cout << blc;
	print(tb, 43);
	cout << brc << endl;
	while (running) {
		cout << tlc;
		print(tb, 43);
		cout << trc << endl;
		cout << ud << " (1)Caeser Cipher                          " << ud << endl << ud << " (2)Atbash                                 " << ud << endl << ud << " (3)A-1, B-2...                            " << ud << endl << ud << " (4)Keyword Alphabet                       " << ud << endl << ud << " (5)BIFID                                  " << ud << endl;
		cout << blc;
		print(tb, 43);
		cout << brc << endl << ">> ";
		cin >> in;
		switch (in) {
		case 1:
			ccipherE();
			running = false;
			break;
		case 2:
			atbashE();
			running = false;
			break;
		case 3:
			a1b2E();
			running = false;
			break;
		case 4:
			newAlphE();
			running = false;
			break;
		case 5:
			bifidE();
			running = false;
			break;
		default:
			cout << "please choose a valid option" << endl;
			break;
		}
	}
}

//THIS IS A METHOD THAT ACTS AS A SUB MENU OF THE MAIN MENU, THIS MENY IS THE 'SWITCH' FOR ALL DECRYPTION METHODS
void decrypt() {
	int in;
	bool running = true;
	cout << tlc;
	print(tb, 43);
	cout << trc << endl;
	cout << ud << " What decryption would you like to choose? " << ud << endl;
	cout << blc;
	print(tb, 43);
	cout << brc << endl;

	while (running) {
		cout << tlc;
		print(tb, 43);
		cout << trc << endl;
		cout << ud << " (1)Caeser Cipher                          " << ud << endl << ud << " (2)Atbash                                 " << ud << endl << ud << " (3)A-1, B-2...                            " << ud << endl << ud << " (4)Keyword Alphabet                       " << ud << endl << ud << " (5)BIFID                                  " << ud << endl;
		cout << blc;
		print(tb, 43);
		cout << brc << endl << ">> ";
		cin >> in;
		switch (in) {
		case 1:
			ccipherD();
			running = false;
			break;
		case 2:
			atbashD();
			running = false;
			break;
		case 3:
			a1b2D();
			running = false;
			break;
		case 4:
			newAlphD();
			running = false;
			break;
		case 5:
			bifidD();
			running = false;
			break;
		default:
			cout << "please choose a valid option" << endl;
			break;
		}
	}
}

//THIS IS THE MAIN METHOD THAT RUNS WHEN THE PROGAM STARTS UP, IT ALSO IS THE MAIN MENU
int main() {
	string in;
	bool running = true;
	for (int u = 0; u < 10; u++) {
		cout << endl;
	}
	cout << "                                                  -----LOADING CRYPTOx86-----" << endl << "                                                  ";
	loadingBar();
	system("CLS");
	Sleep(600);
	for (int u = 0; u < 10; u++) {
		cout << endl;
	}
	system("color 0a");
	cout << "                                        _____ ________   _______ _____ _____ " << endl;
	Sleep(550);
	system("color 0b");
	cout << "                                       /  __ \\| ___ \\ \\ / / ___ \\_   _|  _  |" << endl;
	Sleep(500);
	system("color 0c");
	cout << "                                       | /  \\/| |_/ /\\ V /| |_/ / | | | | | |" << endl;
	Sleep(450);
	system("color 0d");
	cout << "                                       | |    |    /  \\ / |  __/  | | | | | |" << endl;
	Sleep(400);
	system("color 0e");
	cout << "                                       | \\__/\\| |\\ \\  | | | |     | | \\ \\_/ /" << endl;
	Sleep(350);
	system("color 0f");
	cout << "                                        \\____/\\_| \\_| \\_/ \\_|     \\_/  \\___/ " << endl;
	Sleep(300);
	system("CLS");
	Sleep(600);
//	system("color 0f");
	cout << "          _____ ________   _______ _____ _____ " << endl;
//	Sleep(550);
//	system("color 0b");
	cout << "         /  __ \\| ___ \\ \\ / / ___ \\_   _|  _  |" << endl;
//	Sleep(500);
//	system("color 0c");
	cout << "         | /  \\/| |_/ /\\ V /| |_/ / | | | | | |" << endl;
//	Sleep(450);
//	system("color 0d");
	cout << "         | |    |    /  \\ / |  __/  | | | | | |" << endl;
//	Sleep(400);
//	system("color 0e");
	cout << "         | \\__/\\| |\\ \\  | | | |     | | \\ \\_/ /" << endl;
//	Sleep(350);
//	system("color 0f");
	cout << "          \\____/\\_| \\_| \\_/ \\_|     \\_/  \\___/ " << endl;
//	Sleep(300);
	cout << tlc;
	print(tb, 53);
	cout << trc;
	cout << endl << ud << " Welcome to Crypto, what would you like to do today? " << ud << endl;
	cout << blc;
	print(tb, 53);
	cout << brc << endl;
	while (running) {
		cout << tlc;
		print(tb, 53);
		cout << trc << endl;
		cout << ud << " (1)Encrypt                                          " << ud << endl << ud << " (2)Decrypt                                          " << ud << endl;
		cout << blc;
		print(tb, 53);
		cout << brc << endl << ">> ";
		cin >> in;
		if (in == "1") {
			encrypt();
		}
		else if (in == "2") {
			decrypt();
		}
		else {
			cout << endl << "        *****Please Enter A Valid Response*****" << endl;
		}
	}
}