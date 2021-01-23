#include "PrintCommand.h"

PrintCommand* PrintCommand::instance = nullptr;

PrintCommand *PrintCommand::getInstance() {
    if (!instance)
        instance = new PrintCommand();
    return instance;
}

void PrintCommand::execute(const std::vector<std::string>& commands, const Session& session) {
    std::regex rangePattern(Command::rangePattern);
    std::vector<int> range;
    if (commands.size() == 2 && std::regex_match(commands[1], rangePattern)) {
        std::string r = commands[1];
        range = processRange(r, session);
        if (range.empty())
            return;
        for (auto& index : range)
            std::cout << session.buffer[index] << "\n";
        return;
    }
    if (commands.size() == 1) {
        for (auto& line : session.buffer)
            std::cout << line << "\n";
        return;
    }
    std::cout << "Wrong input for command print." << "\n";
}


