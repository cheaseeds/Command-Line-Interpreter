#include <iostream>
#include <string.h>
#include <cstring>
#include <vector>
#include "Parser.hpp"
#include <algorithm>

Parser::Parser() {}

std::vector<std::string> Parser::parseCommand(const char * command)
{
	// TODO: Your code here
    std::vector<std::string> parts;
    bool hasQuotes = false;
    bool quoteOpen = false;
    std::string token = "";

    size_t length = strlen(command);
    for (size_t i = 0; i < length; i++) {
        char c = command[i];

        if (c == '\\') {
            if (command[i + 1] != '\0') {
                token += command[i + 1];
                i++;
            } else if (command[i+1] == '\0') {
                std::cout << "Error: backslash at end of command." << std::endl;
                throw std::runtime_error("Error: backslash at end of command.");
            }
        }
        else if (c == '\"') {
            hasQuotes = true;
            quoteOpen = !quoteOpen;
        }
        else if (c == ' ' && !quoteOpen) {
            if (!token.empty()) {
                parts.push_back(token);
                token = "";
            }
        }
        else {
            token += c;
        }
    }

    if (hasQuotes && quoteOpen) {
        std::cout << "Error: unterminated quote." << std::endl;
        throw std::runtime_error("Error: unterminated quote.");
    }

    if (!token.empty()) {
        parts.push_back(token);
    }

    if (parts.empty()) {
        std::cout << "Error: empty command." << std::endl;
    }

    return parts;
	
}

std::string Parser::recombineParts(const std::vector<std::string>& parts)
{

	std::string command = "";

    if (parts.empty()) {
    std::cerr << "Error: no command provided" << std::endl;
    return "";
}

    command += parts[0];
    for (size_t i = 1; i < parts.size(); i++) {
        std::string token = parts[i];

        

        if (i >= 1) {
            command += " \"";
        } else {
            command += "\"";
        }

        for (size_t j = 0; j < token.size(); j++) {
            char c = token[j];
            if (c == '\"' || c == '\\') {
                command += "\\";
            }
            command += c;
        }

        if (i < parts.size() - 1) {
            command += "\"";
        } else {
            command += "\"";
        }
}
    
    

    return command;
}

bool Parser::isCommandEmpty(const std::vector<std::string>& parts)
{

	if (parts.empty()) {
		return true;
	}
	if (parts[0].empty()) {
		return true;
	}
	return false;
}

bool Parser::isValidProgram(std::string program)
{
    
	std::vector<std::string> commands = { "ls", "df", "pwd", "ps", "gedit", "echo", "ping"};
	return std::find(commands.begin(), commands.end(), program) != commands.end();

}


bool Parser::isValidProgram(const std::vector<std::string>& parts)
{
	if ( !parts.empty() ) {
		return Parser::isValidProgram(parts[0]);
	}
	
	return false;
}


bool Parser::isValidProgram(const char * program) { return Parser::isValidProgram(std::string(program)); }

void Parser::printParts(const std::vector<std::string>& parts)
{
	// TODO: Your code here
	std::cout << "Parts:\n";
	for (int i = 0; i < parts.size(); i++) {
		std::cout << "> [" << i << "] == " << parts[i] << std::endl;
	}
}