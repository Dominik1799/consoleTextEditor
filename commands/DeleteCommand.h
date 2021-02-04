#ifndef CONSOLETEXTEDITOR_DELETECOMMAND_H
#define CONSOLETEXTEDITOR_DELETECOMMAND_H


#include "Command.h"

class DeleteCommand : public Command {
public:
    void execute(const std::vector<std::string>& commands, Session& session);
};


#endif //CONSOLETEXTEDITOR_DELETECOMMAND_H
