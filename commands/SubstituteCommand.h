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
    int replaceAll(std::string& data, const std::string& toSearch, const std::string& replaceStr, bool isCounting = false);
    std::string checkFilter(std::string& rawCommand, std::string& possibleRange);

public:
    void execute(const std::vector<std::string>& commands, Session& session, std::string& rawCommand);
    std::vector<std::string> parseFilter(std::string &filter);
};


#endif //CONSOLETEXTEDITOR_SUBSTITUTECOMMAND_H
