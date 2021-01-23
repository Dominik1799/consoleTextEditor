#ifndef CONSOLETEXTEDITOR_SESSIONMANAGER_H
#define CONSOLETEXTEDITOR_SESSIONMANAGER_H
#include <string>
#include <fstream>
#include <unordered_set>
#include "Session.h"

class SessionManager {
private:
    Session session;
    std::unordered_set<std::string> _print{"p","print", "pr", "P", "vypis"};
    std::unordered_set<std::string> _append{"a"};
    std::unordered_set<std::string> _change{"c","z"};
    std::unordered_set<std::string> _write{"w","z"};
    std::unordered_set<std::string> _quit{"q"};
    std::unordered_set<std::string> _delete{"d"};

    static std::vector<std::string> commandSplitter(std::string& command);
public:
    explicit SessionManager(std::string& filename);
    void processCommand(std::string& command);
};


#endif //CONSOLETEXTEDITOR_SESSIONMANAGER_H
