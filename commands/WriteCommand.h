#ifndef CONSOLETEXTEDITOR_WRITECOMMAND_H
#define CONSOLETEXTEDITOR_WRITECOMMAND_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include "../Session.h"

class WriteCommand {
    WriteCommand() = default;
    WriteCommand(WriteCommand const&) = default;
    static WriteCommand* instance;

public:
    static WriteCommand* getInstance();
    void execute(const std::vector<std::string>& commands, Session& session);
};


#endif //CONSOLETEXTEDITOR_WRITECOMMAND_H
