#include <iostream>
#include <sstream>
#include "commands/PrintCommand.h"
#include "commands/WriteCommand.h"
#include "commands/AppendCommand.h"
#include "commands/ChangeCommand.h"
#include "commands/DeleteCommand.h"
#include "SessionManager.h"
#include "commands/QuitCommand.h"

SessionManager::SessionManager(std::string& filename) {
    session.fileName = filename;
    std::ifstream f(session.fileName);
    if (!f.good()) { // file does not exists
        f.close();
        std::ofstream creatingFile(session.fileName);
        creatingFile.close();
        return;
    }
    std::string buffer;
    while (std::getline(f,buffer)) {
        session.buffer.push_back(buffer);
    }
    f.close();
    std::ifstream newlineCheck(session.fileName, std::ios::binary);
    newlineCheck.seekg(-1,std::ios_base::end);
    char c;
    newlineCheck.get(c);
    if(c=='\n')
        session.endsWithNewline = true;
}

void SessionManager::processCommand(std::string &command) {
    std::vector<std::string> commands = commandSplitter(command);
    if (commands.empty()) return;
    std::string invoker = commands[0];
    std::vector<std::string> possibleCommands;
    if (_print.count(invoker)) possibleCommands.emplace_back("print/tlac");
    if (_write.count(invoker)) possibleCommands.emplace_back("write/zapis");
    if (_append.count(invoker)) possibleCommands.emplace_back("append/pridaj");
    if (_delete.count(invoker)) possibleCommands.emplace_back("delete/vymaz");
    if (_change.count(invoker)) possibleCommands.emplace_back("change/zmen");
    if (_quit.count(invoker)) possibleCommands.emplace_back("quit/skonci");
    if (possibleCommands.size() > 1) {
        std::cout << "Ambiguous command " << invoker << ", could be { ";
        for (auto& comm : possibleCommands)
            std::cout << comm << " ";
        std::cout << "}\n";
        return;
    } else if (possibleCommands.empty()) {
        std::cout << "Unknown command " << invoker << "\n";
        return;
    }
    if (possibleCommands[0] == "print/tlac") PrintCommand::getInstance()->execute(commands, session);
    if (possibleCommands[0] == "write/zapis") WriteCommand::getInstance()->execute(commands, session);
    if (possibleCommands[0] == "append/pridaj") AppendCommand::getInstance()->execute(commands, session);
    if (possibleCommands[0] == "delete/vymaz") DeleteCommand::getInstance()->execute(commands, session);
    if (possibleCommands[0] == "change/zmen") ChangeCommand::getInstance()->execute(commands, session);
    if (possibleCommands[0] == "quit/skonci") QuitCommand::getInstance()->execute(commands, session);

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
