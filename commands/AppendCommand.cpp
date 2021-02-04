#include <regex>
#include "AppendCommand.h"



void AppendCommand::execute(const std::vector<std::string> &commands, Session &session) {
    std::regex singleLinePattern(Command::singleLinePattern);
    if (commands.size() == 1 || (commands.size() == 2 && std::regex_match(commands[1],singleLinePattern)))
        session.changesFlag = regularAppend(commands,session); // not a one-liner
    else
        session.changesFlag = onelinerAppend(commands,session);

}

bool AppendCommand::regularAppend(const std::vector<std::string> &commands, Session &session) {
    std::vector<std::string> writeBuffer;
    std::string inputLine;
    int index{-1};
    if (commands.size() == 2) {
        try {
            index = std::stoi(commands[1]);
            if (index < 0)
                throw std::exception();
        } catch (std::exception& e) {
            std::cout <<  "Wrong input for command print.\n";
            return false;
        }
    }
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
            while (++counter <= index)
                temp.emplace_back("");
            for (const auto& line : writeBuffer)
                temp.push_back(line);
        }
        session.buffer = temp;
    }
    return true;
}

bool AppendCommand::onelinerAppend(const std::vector<std::string> &commands, Session &session) {
    std::regex singleLinePattern(Command::singleLinePattern);
    if (!std::regex_match(commands[1], singleLinePattern)) { // oneliner without line number
        std::string builder;
        for (size_t i = 1; i < commands.size(); i++) {
            builder += commands[i];
            if (i != commands.size() - 1) builder += " ";
        }
        session.buffer.push_back(builder);
        return true;
    }
    int index = std::stoi(commands[1]);
    bool appended = false;
    std::vector<std::string> temp;
    std::string builder;
    for (size_t i = 2; i < commands.size(); i++) {
        builder += commands[i];
        if (i != commands.size() - 1) builder += " ";
    }
    for (size_t i = 0; i < session.buffer.size(); i++) {
        if (i == index) {
            appended = true;
            temp.push_back(builder);
        }
        temp.push_back(session.buffer[i]);
    }
    if (!appended) {
        size_t counter{temp.size()};
        while (++counter <= index)
            temp.emplace_back("");
        temp.push_back(builder);
    }
    session.buffer = temp;

    return true;
}
