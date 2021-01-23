#ifndef CONSOLETEXTEDITOR_SESSION_H
#define CONSOLETEXTEDITOR_SESSION_H
#include <string>
#include <vector>

struct Session {
    std::string fileName;
    std::vector<std::string> buffer;
    bool changesFlag{false};
};

#endif //CONSOLETEXTEDITOR_SESSION_H
