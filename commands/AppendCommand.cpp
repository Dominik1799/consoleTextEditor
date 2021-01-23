#include <regex>
#include "AppendCommand.h"

AppendCommand *AppendCommand::instance = nullptr;


AppendCommand *AppendCommand::getInstance() {
    if (!instance)
        instance = new AppendCommand();
    return instance;
}

void AppendCommand::execute(const std::vector<std::string> &commands, Session &session) {
    session.changesFlag = true;
    regularAppend(commands,session); // not a one-liner

}

void AppendCommand::regularAppend(const std::vector<std::string> &commands, Session &session) {
    std::vector<std::string> writeBuffer;
    std::string inputLine;
    while (true) {
        std::getline(std::cin, inputLine);
        if (inputLine == ".")
            break;
        writeBuffer.push_back(inputLine);
    }
    if (commands.size() == 1) {
        for (auto& line : writeBuffer) {
            session.buffer.push_back(line);
        }
    } else {
        bool appended = false;
        int index = std::stoi(commands[1]);
        std::vector<std::string> temp;
        for (size_t i = 0; i < session.buffer.size(); i++) {
            if (i == index) {
                appended = true;
                for (const auto& line : writeBuffer)
                    temp.push_back(line);
            }
            temp.push_back(session.buffer[i]);
        }
        if (!appended) {
            size_t counter{temp.size()};
            while (++counter != index)
                temp.emplace_back("");
            for (const auto& line : writeBuffer)
                temp.push_back(line);
        }
        session.buffer = temp;
    }
}
