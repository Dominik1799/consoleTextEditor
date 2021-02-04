#include "WriteCommand.h"



void WriteCommand::execute(const std::vector<std::string> &commands, Session &session) {
    std::ofstream writer(session.fileName);
    if (!writer.is_open()) {
        std::cout << "Cannot write to a file. It might be deleted, opened by another application or read only.\n";
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
    auto size = rc == 0 ? stat_buf.st_size : -1;
    if (size == -1) {
        session.changesFlag = false;
        std::cout << "Something went wrong when retrieving the file size. Please check the integrity of the file.\n";
        return;
    }
    float kb = size / 1024.0f;
    float mb = kb / 1024.0f;
    float gb = mb / 1024.0f;
    if (gb >= 1.0f) printf("%.2f GB\n",gb);
    else if (mb >= 1.0f) printf("%.2f MB\n",mb);
    else if (kb >= 1.0f) printf("%.2f KB\n",kb);
    else  printf("%d B\n",size);
    session.changesFlag = false;
}

