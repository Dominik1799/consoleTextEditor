#ifndef CONSOLETEXTEDITOR_SUBSTITUTECOMMAND_H
#define CONSOLETEXTEDITOR_SUBSTITUTECOMMAND_H


#include "../Session.h"
#include "Command.h"
#include <vector>
#include <string>
#include <regex>

class SubstituteCommand : public Command {
    SubstituteCommand() = default;
    SubstituteCommand(SubstituteCommand const&) = default;
    static SubstituteCommand* instance;

public:
    static SubstituteCommand* getInstance();
    void execute(const std::vector<std::string>& commands, Session& session);
};


#endif //CONSOLETEXTEDITOR_SUBSTITUTECOMMAND_H
