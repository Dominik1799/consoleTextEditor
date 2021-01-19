#include <iostream>
#include "SessionManager.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Wrong number of arguments.";
        exit(1);
    }
    std::string fileName = argv[1];
    SessionManager manager{fileName};
    std::string command;
    while (true) {
        std::cout << "* ";
        std::getline(std::cin, command);
        manager.processCommand(command);
        if (command == "q")
            break;
    }
    return 0;
}
