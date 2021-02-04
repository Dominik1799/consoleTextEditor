#ifndef CONSOLETEXTEDITOR_WRITECOMMAND_H
#define CONSOLETEXTEDITOR_WRITECOMMAND_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include "../Session.h"

class WriteCommand {
public:
    void execute(const std::vector<std::string>& commands, Session& session);
};


#endif //CONSOLETEXTEDITOR_WRITECOMMAND_H
