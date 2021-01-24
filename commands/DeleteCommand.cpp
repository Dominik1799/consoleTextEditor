#include "DeleteCommand.h"

DeleteCommand *DeleteCommand::instance = nullptr;

DeleteCommand *DeleteCommand::getInstance() {
    if (!instance)
        instance = new DeleteCommand();
    return instance;
}

void DeleteCommand::execute(const std::vector<std::string> &commands, Session &session) {
    std::vector<int> range;
    if (commands.size() > 2) {
        std::cout << "Wrong input for command print.\n";
        return;
    }
    if (commands.size() == 2) {
        std::string r = commands[1];
        range = processRange(r, session);
        if (range.empty())
            return;
    }
    std::vector<std::string> tempBuffer;
    if (commands.size() == 1) {
        session.buffer = tempBuffer;
        session.changesFlag = true;
        return;
    }
    size_t j{0};
    for (int i = 0; i < session.buffer.size(); i++) {
        if (i == range[j]) {
            if (j != range.size()-1) j++;
            continue;
        }
        tempBuffer.push_back(session.buffer[i]);
    }
    session.buffer = tempBuffer;
    session.changesFlag = true;
}
