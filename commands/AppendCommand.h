#ifndef CONSOLETEXTEDITOR_APPENDCOMMAND_H
#define CONSOLETEXTEDITOR_APPENDCOMMAND_H

#include "../Session.h"
#include "Command.h"
#include <iostream>
#include <vector>
#include <string>

class AppendCommand : public Command {
    AppendCommand() = default;
    AppendCommand(AppendCommand const&) = default;
    static AppendCommand* instance;
    void regularAppend(const std::vector<std::string>& commands, Session& session);

public:
    static AppendCommand* getInstance();
    void execute(const std::vector<std::string>& commands, Session& session);
};


#endif //CONSOLETEXTEDITOR_APPENDCOMMAND_H
