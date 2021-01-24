#include <regex>
#include "ChangeCommand.h"

ChangeCommand *ChangeCommand::instance = nullptr;


ChangeCommand *ChangeCommand::getInstance() {
    if (!instance)
        instance = new ChangeCommand;
    return instance;
}

void ChangeCommand::execute(const std::vector<std::string> &commands, Session &session) {
    std::regex range(Command::rangePattern);
    if (commands.size() == 1 || (commands.size() == 2 && std::regex_match(commands[1],range)))
        session.changesFlag = regularChange(commands,session); // not a oneline
    else
        session.changesFlag = onelinerChange(commands,session); // not a oneline
}

bool ChangeCommand::regularChange(const std::vector<std::string> &commands, Session &session) {
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
            return false;
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
    return true;
}

bool ChangeCommand::onelinerChange(const std::vector<std::string> &commands, Session &session) {
    std::regex range(Command::rangePattern);
    std::vector<std::string> tempBuffer;
    if (std::regex_match(commands[1], range)) { // range is present
        std::string r = commands[1];
        std::vector linesRange = processRange(r, session);
        if (linesRange.empty())
            return false;
        std::string data;
        for (size_t i = 2; i < commands.size(); i++) {
            data += commands[i];
            if (i != commands.size() - 1) data += " ";
        }
        size_t j{0};
        bool wasAltered{false};
        for (size_t i = 0; i < session.buffer.size(); i++) {
            if (i == linesRange[j]) {
                if (j != linesRange.size()-1) j++;
                if (!wasAltered) {
                    tempBuffer.push_back(data);
                    wasAltered = true;
                }
                continue;
            }
            tempBuffer.push_back(session.buffer[i]);
        }
        session.buffer = tempBuffer;
        return true;
    }
    std::string data;
    for (size_t i = 1; i < commands.size(); i++) {
        data += commands[i];
        if (i != commands.size() - 1) data += " ";
    }
    session.buffer.clear();
    session.buffer.push_back(data);
    return true;
}
