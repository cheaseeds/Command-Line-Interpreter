#include <pthread.h>
#include <cstring>
#include <iostream>
#include "Executor.hpp"
#include "Parser.hpp"
using namespace std;
//
int main()
{
	// TODO: Your code here
	//string command;
	Parser parse;
	Executor execute;

	const int MAX_INPUT_LENGTH = 256;
	char inputBuffer[MAX_INPUT_LENGTH];

	cout << "Welcome to my Command Line Interpreter. (aka shell)\n";
	cout << "Written by Alexander Chea\n";
	

	do {
	cout << "Enter next command. \n";
	
	std::cin.getline(inputBuffer, MAX_INPUT_LENGTH, '\n');
	
	if (strcmp(inputBuffer, "exit") == 0) {
        break;
    }

	vector<string> parts = parse.parseCommand(inputBuffer);
	
	if (parse.isCommandEmpty(parts)) {
		cout << "Command is empty.\n";
		continue;
	}

	if (!parse.isValidProgram(parts)) {
		cout << "Invalid Program!\n";
		break;
	}
	parse.printParts(parts);
	string result = parse.recombineParts(parts);

	pthread_t threadId;
	int returnValue = pthread_create(&threadId, NULL, Executor::threadRunner, (void*) result.c_str());
	if (returnValue) {
		cerr << "Error creating thread: " << returnValue << endl;
		break;
	}	
	pthread_join(threadId, NULL);
	} while (strcmp(inputBuffer, "exit") != 0);

	cout << "Thank you for using my command line interpreter.\n";

	return 0;
}