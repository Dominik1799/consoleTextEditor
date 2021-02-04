#ifndef CONSOLETEXTEDITOR_CHANGECOMMAND_H
#define CONSOLETEXTEDITOR_CHANGECOMMAND_H


#include "Command.h"

class ChangeCommand  : public Command  {
public:
    void execute(const std::vector<std::string>& commands, Session& session);
    bool regularChange(const std::vector<std::string>& commands, Session& session);
    bool onelinerChange(const std::vector<std::string> &commands, Session &session);
};


#endif //CONSOLETEXTEDITOR_CHANGECOMMAND_H
