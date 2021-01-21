#include <iostream>
#include <sstream>
#include <regex>
#include "SessionManager.h"

SessionManager::SessionManager(std::string& filename) {
    session.fileName = filename;
    std::ifstream f(session.fileName);
    if (!f.good()) { // file not exists
        f.close();
        std::ofstream creatingFile(session.fileName);
        creatingFile.close();
        return;
    }
    std::string buffer;
    while (std::getline(f,buffer)) {
        session.buffer.push_back(buffer);
    }
}

void SessionManager::processCommand(std::string &command) {
    std::vector commands = commandSplitter(command);
    if (commands.empty()) return;
    std::string invoker = commands[0];
    std::regex rangePattern("^([0-9]?,[0-9]?)$");
    std::vector<std::string> possibleCommands;
    if (_print.count(invoker)) possibleCommands.emplace_back("print / tlac");
    if (_write.count(invoker)) possibleCommands.emplace_back("write / zapis");
    if (_append.count(invoker)) possibleCommands.emplace_back("append / pridaj");
    if (_delete.count(invoker)) possibleCommands.emplace_back("delete / vymaz");
    if (commands.size() == 2) {
        bool match = std::regex_match(commands[1],rangePattern);
        std::cout << match;
    }

}

std::vector<std::string> SessionManager::commandSplitter(std::string &command) {
    std::istringstream iss(command);
    std::string buffer;
    std::vector<std::string> result;
    while (std::getline(iss, buffer, ' ')) {
        result.push_back(buffer);
    }
    return result;
}
