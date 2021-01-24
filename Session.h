#ifndef CONSOLETEXTEDITOR_SESSION_H
#define CONSOLETEXTEDITOR_SESSION_H
#include <string>
#include <vector>

struct Session {
    std::string fileName;
    std::vector<std::string> buffer;
    bool changesFlag{false};
    bool endsWithNewline{false};
};

#endif //CONSOLETEXTEDITOR_SESSION_H
