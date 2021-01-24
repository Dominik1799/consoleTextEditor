#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
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
    generateAliases(printAlias, _print);
    generateAliases(appendAlias, _append);
    generateAliases(writeAlias, _write);
    generateAliases(changeAlias, _change);
    generateAliases(quitAlias, _quit);
    generateAliases(deleteAlias, _delete);
    generateAliases(substituteAlias, _substitute);

    commandMap["p"] = printAlias;
    commandMap["a"] = appendAlias;
    commandMap["w"] = writeAlias;
    commandMap["c"] = changeAlias;
    commandMap["q"] = quitAlias;
    commandMap["d"] = deleteAlias;
    commandMap["s"] = substituteAlias;
}


void SessionManager::processCommand(std::string &command) {
    removeBegWhitespace(command);
    std::vector<std::string> commands = commandSplitter(command);
    if (commands.empty()) return;
    if (command.at(0) == '!') {
        command.erase(0,1);
        std::system(command.c_str());
        return;
    }
    std::string invoker = commands[0];
    std::transform(invoker.begin(), invoker.end(), invoker.begin(),
                             [](unsigned char c){ return std::tolower(c); });
    std::vector<std::string> possibleCommands;
    if (_print.count(invoker)) possibleCommands.emplace_back("p");
    if (_write.count(invoker)) possibleCommands.emplace_back("w");
    if (_append.count(invoker)) possibleCommands.emplace_back("a");
    if (_delete.count(invoker)) possibleCommands.emplace_back("d");
    if (_change.count(invoker)) possibleCommands.emplace_back("c");
    if (_quit.count(invoker)) possibleCommands.emplace_back("q");
    if (_substitute.count(invoker)) possibleCommands.emplace_back("s");
    if (possibleCommands.size() > 1) {
        std::cout << "Ambiguous command " << invoker << ", could be { ";
        possibleCommands = filterPossibleCommands(possibleCommands, invoker);
        for (size_t i = 0; i < possibleCommands.size(); i++) {
            std::cout << possibleCommands[i];
            if (i != possibleCommands.size() - 1) std::cout << " / ";
        }
        std::cout << " }\n";
        return;
    } else if (possibleCommands.empty()) {
        std::cout << "Unknown command " << invoker << "\n";
        return;
    }
    if (possibleCommands[0] == "p") PrintCommand::getInstance()->execute(commands, session);
    if (possibleCommands[0] == "w") WriteCommand::getInstance()->execute(commands, session);
    if (possibleCommands[0] == "a") AppendCommand::getInstance()->execute(commands, session);
    if (possibleCommands[0] == "d") DeleteCommand::getInstance()->execute(commands, session);
    if (possibleCommands[0] == "c") ChangeCommand::getInstance()->execute(commands, session);
    if (possibleCommands[0] == "q") QuitCommand::getInstance()->execute(commands, session);

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

void SessionManager::removeBegWhitespace(std::string &command) {
    bool hasStarted{false};
    std::string result;
    for (auto& c : command) {
        if (std::isspace(c) && !hasStarted) continue;
        hasStarted = true;
        result += c;
    }
    command = result;
}

void SessionManager::generateAliases(std::vector<std::string> &base, std::unordered_set<std::string> &command) {
    for (auto& alias : base) {
        for (int i = 1; i <= alias.length(); i++) {
            if (!command.count(alias.substr(0,i))) {
                command.emplace(alias.substr(0,i));
                if (std::count(quitAlias.begin(),quitAlias.end(), "quit"))
                    command.emplace(alias.substr(0,i) + '!');
            }

        }
    }
}

std::vector<std::string> SessionManager::filterPossibleCommands(std::vector<std::string>& commands, std::string& invoker) {
    std::vector<std::string> result;
    for (auto& com : commands) {
        auto aliases = commandMap[com];
        for (auto& a : aliases) {
            if (a.rfind(invoker, 0) == 0)
                result.push_back(a);
        }
    }
    return result;
}
