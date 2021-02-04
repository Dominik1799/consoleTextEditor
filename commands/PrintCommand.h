#ifndef CONSOLETEXTEDITOR_PRINTCOMMAND_H
#define CONSOLETEXTEDITOR_PRINTCOMMAND_H

#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include "./Command.h"
#include "../Session.h"

class PrintCommand : public Command {
public:
    void execute(const std::vector<std::string>& commands, const Session& session);


};


#endif //CONSOLETEXTEDITOR_PRINTCOMMAND_H
