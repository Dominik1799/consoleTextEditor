#ifndef CONSOLETEXTEDITOR_SESSIONMANAGER_H
#define CONSOLETEXTEDITOR_SESSIONMANAGER_H
#include <string>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include "Session.h"
#include "commands/PrintCommand.h"
#include "commands/WriteCommand.h"
#include "commands/AppendCommand.h"
#include "commands/ChangeCommand.h"
#include "commands/DeleteCommand.h"
#include "commands/SubstituteCommand.h"
#include "commands/QuitCommand.h"

class SessionManager {
private:
    Session session;
    PrintCommand PRINT_COMMAND;
    WriteCommand WRITE_COMMAND;
    AppendCommand APPEND_COMMAND;
    ChangeCommand CHANGE_COMMAND;
    DeleteCommand DELETE_COMMAND;
    SubstituteCommand SUBSTITUTE_COMMAND;
    PrintCommand QUIT_COMMAND;
    std::unordered_map<std::string, std::vector<std::string>> commandMap;
    std::unordered_set<std::string> _print;
    std::unordered_set<std::string> _append;
    std::unordered_set<std::string> _change;
    std::unordered_set<std::string> _write;
    std::unordered_set<std::string> _quit;
    std::unordered_set<std::string> _delete;
    std::unordered_set<std::string> _substitute;
    std::vector<std::string> printAlias{"print", "vypis", "ukaz", "show", "vytlac"};
    std::vector<std::string> appendAlias{"append", "paste", "dopis"};
    std::vector<std::string> writeAlias{"write", "zapis", "save", "uloz"};
    std::vector<std::string> changeAlias{"change", "zmenit", "modify", "vymen"};
    std::vector<std::string> quitAlias{"quit", "odist", "ukoncit", "exit"};
    std::vector<std::string> deleteAlias{"delete", "zmazat", "odstran", "wipe"};
    std::vector<std::string> substituteAlias{"substitute"};
    void generateAliases(std::vector<std::string>& base, std::unordered_set<std::string>& command);
    static void removeBegWhitespace(std::string& command);
    std::vector<std::string> filterPossibleCommands(std::vector<std::string>& commands, std::string& invoker);


    static std::vector<std::string> commandSplitter(std::string& command);
public:
    explicit SessionManager(std::string& filename);
    void processCommand(std::string& command);

};


#endif //CONSOLETEXTEDITOR_SESSIONMANAGER_H
