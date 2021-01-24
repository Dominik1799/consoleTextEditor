#include "SubstituteCommand.h"

SubstituteCommand *SubstituteCommand::instance = nullptr;

SubstituteCommand *SubstituteCommand::getInstance() {
    if (!instance)
        instance = new SubstituteCommand();
    return nullptr;
}

void SubstituteCommand::execute(const std::vector<std::string> &commands, Session &session) {

}
