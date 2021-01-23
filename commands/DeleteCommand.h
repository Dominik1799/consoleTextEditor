#ifndef CONSOLETEXTEDITOR_DELETECOMMAND_H
#define CONSOLETEXTEDITOR_DELETECOMMAND_H


#include "Command.h"

class DeleteCommand : public Command {
    DeleteCommand() = default;
    DeleteCommand(DeleteCommand const&) = default;
    static DeleteCommand* instance;

public:
    static DeleteCommand* getInstance();
    void execute(const std::vector<std::string>& commands, Session& session);
};


#endif //CONSOLETEXTEDITOR_DELETECOMMAND_H
