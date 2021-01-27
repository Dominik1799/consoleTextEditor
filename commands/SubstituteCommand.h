#ifndef CONSOLETEXTEDITOR_SUBSTITUTECOMMAND_H
#define CONSOLETEXTEDITOR_SUBSTITUTECOMMAND_H


#include "../Session.h"
#include "Command.h"
#include <vector>
#include <string>
#include <regex>
#include <sstream>
#include <unordered_set>

class SubstituteCommand : public Command {
    SubstituteCommand() = default;
    SubstituteCommand(SubstituteCommand const&) = default;
    int replaceAll(std::string& data, const std::string& toSearch, const std::string& replaceStr);
    static SubstituteCommand* instance;
    void checkFilter(std::string& commands);

public:
    static SubstituteCommand* getInstance();
    void execute(const std::vector<std::string>& commands, Session& session);
    std::string parseFilter(std::vector<std::string>& filter);
};


#endif //CONSOLETEXTEDITOR_SUBSTITUTECOMMAND_H
