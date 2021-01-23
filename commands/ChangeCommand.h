#ifndef CONSOLETEXTEDITOR_CHANGECOMMAND_H
#define CONSOLETEXTEDITOR_CHANGECOMMAND_H


#include "Command.h"

class ChangeCommand  : public Command  {
    ChangeCommand() = default;
    ChangeCommand(ChangeCommand const&) = default;
    static ChangeCommand* instance;

public:
    static ChangeCommand* getInstance();
    void execute(const std::vector<std::string>& commands, Session& session);
    void regularChange(const std::vector<std::string>& commands, Session& session);
};


#endif //CONSOLETEXTEDITOR_CHANGECOMMAND_H
