#include "WriteCommand.h"

WriteCommand *WriteCommand::instance = nullptr;

WriteCommand *WriteCommand::getInstance() {
    if (!instance)
        instance = new WriteCommand();
    return instance;
}

void WriteCommand::execute(const std::vector<std::string> &commands, Session &session) {
    std::ofstream writer(session.fileName);
    if (!writer.is_open()) {
        std::cout << "Cannot write to a file. It might be deleted or opened by another application.\n";
        return;
    }
    for (size_t i = 0; i< session.buffer.size(); i++) {
        writer << session.buffer[i];
        if (i != session.buffer.size() - 1 || session.endsWithNewline)
            writer << "\n";
    }
    writer.close();
    std::ifstream in(session.fileName, std::ifstream::ate | std::ifstream::binary);
    struct stat stat_buf{};
    int rc = stat(session.fileName.c_str(), &stat_buf);
    std::cout << (rc == 0 ? stat_buf.st_size : -1) << " B\n";
    session.changesFlag = false;
}

