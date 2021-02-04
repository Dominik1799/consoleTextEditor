#ifndef CONSOLETEXTEDITOR_QUITCOMMAND_H
#define CONSOLETEXTEDITOR_QUITCOMMAND_H


#include "Command.h"

class QuitCommand : public Command {
public:
    void execute(const std::vector<std::string>& commands, const Session& session);
};


#endif //CONSOLETEXTEDITOR_QUITCOMMAND_H
