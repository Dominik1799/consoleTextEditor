#include "ChangeCommand.h"

ChangeCommand *ChangeCommand::instance = nullptr;


ChangeCommand *ChangeCommand::getInstance() {
    if (!instance)
        instance = new ChangeCommand;
    return instance;
}

void ChangeCommand::execute(const std::vector<std::string> &commands, Session &session) {
    session.changesFlag = true;
    regularChange(commands,session); // not a oneline
}

void ChangeCommand::regularChange(const std::vector<std::string> &commands, Session &session) {
    std::vector<std::string> writeBuffer;
    std::string inputLine;
    if (commands.size() == 1) {
        while (true) {
            std::getline(std::cin, inputLine);
            if (inputLine == ".")
                break;
            writeBuffer.push_back(inputLine);
        }
        session.buffer = writeBuffer;
    } else {
        std::vector<int> range;
        std::string r = commands[1];
        range = processRange(r,session);
        if (range.empty()) {
            return;
        }
        while (true) {
            std::getline(std::cin, inputLine);
            if (inputLine == ".")
                break;
            writeBuffer.push_back(inputLine);
        }
        size_t j{0};
        std::vector<std::string> tempBuffer;
        bool wasAltered{false};
        for (int i = 0; i < session.buffer.size(); i++) {
            if (i == range[j]) {
                if (j != range.size()-1) j++;
                if (!wasAltered) {
                    for (auto& line : writeBuffer)
                        tempBuffer.push_back(line);
                    wasAltered = true;
                }
                continue;
            }
            tempBuffer.push_back(session.buffer[i]);
        }
        session.buffer = tempBuffer;

    }
}
