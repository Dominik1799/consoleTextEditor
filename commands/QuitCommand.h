#ifndef CONSOLETEXTEDITOR_QUITCOMMAND_H
#define CONSOLETEXTEDITOR_QUITCOMMAND_H


#include "Command.h"

class QuitCommand : public Command {
    QuitCommand() = default;
    QuitCommand(QuitCommand const&) = default;
    static QuitCommand* instance;

public:
    static QuitCommand* getInstance();
    void execute(const std::vector<std::string>& commands, const Session& session);
};


#endif //CONSOLETEXTEDITOR_QUITCOMMAND_H
