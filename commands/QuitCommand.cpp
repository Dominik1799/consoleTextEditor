#include "QuitCommand.h"



void QuitCommand::execute(const std::vector<std::string> &commands, const Session &session) {
    if (commands.size() > 1) {
        std::cout <<  "Wrong input for command print.\n";
        return;
    }
    std::string c = commands[0];
    if (session.changesFlag) {
        if (c.back() == '!')
            exit(0);
        std::cout << "Your changes are not saved to the disk. Please use the write command first"
                     " or quit! command to override this warning.\n";
    } else {
        exit(0);
    }
}
