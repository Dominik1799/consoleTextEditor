#ifndef CONSOLETEXTEDITOR_APPENDCOMMAND_H
#define CONSOLETEXTEDITOR_APPENDCOMMAND_H

#include "../Session.h"
#include "Command.h"
#include <iostream>
#include <vector>
#include <string>

class AppendCommand : public Command {
    bool regularAppend(const std::vector<std::string>& commands, Session& session);
    bool onelinerAppend(const std::vector<std::string>& commands, Session& session);

public:
    void execute(const std::vector<std::string>& commands, Session& session);
};


#endif //CONSOLETEXTEDITOR_APPENDCOMMAND_H
