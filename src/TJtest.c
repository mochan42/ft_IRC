#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include "../inc/Message.hpp"


int main(int argc, char **argv) {
	if(argc==2){
    	std::string userInput = argv[1];
    	Message msg(userInput);
    	processIRCCommand(msg);
	}
    return 0;
}
