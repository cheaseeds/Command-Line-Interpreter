
/**
 * TODO:
 * You will need to implement the methods listed here.
 */

//
#include "Executor.hpp"
#include "Parser.hpp"
#include <iostream>
using namespace std;

Executor::Executor(){}


//
bool Executor::executeCommand(char * command)
{

    Parser parser;
    vector<string> parts = parser.parseCommand(command);


    if (parser.isCommandEmpty(parts)) {
        cout << "Empty command!" << endl;
        return false;
    }


    if (!parser.isValidProgram(parts)) {
        cout << "Invalid Program!" << endl;
        return false;
    }


    string commandString = parser.recombineParts(parts);
    int result = system(commandString.c_str());
	
    return true;
}


//
void* Executor::threadRunner(void* param)
{

	Executor execute;
    char* command = (char*) param;
    bool success = execute.executeCommand(command);
    pthread_exit(NULL);

}
