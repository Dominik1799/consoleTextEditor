#ifndef CONSOLETEXTEDITOR_COMMAND_H
#define CONSOLETEXTEDITOR_COMMAND_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "../Session.h"

class Command {
protected:
    static std::string rangePattern;
    static std::string singleLinePattern;
    // vrati:
    // prazdny vektor: chyba
    // inak vracia riadky ktore zahrna dany range
    std::vector<int> processRange(std::string& range, const Session& session) {
        std::vector<int> result;
        if (range.find(',') == std::string::npos) { // nenasla sa ciarka, je to jedno cislo
            try {
                int lineNum = std::stoi(range) - 1;
                if (lineNum < 0 || lineNum > session.buffer.size() - 1) {
                    std::cout << "Line number " << range << " not present in current file.\n";
                    return result;
                }
                result.push_back(lineNum);
                return result;
            } catch (std::exception& e) {
                std::cout << "Wrong range format " << range << ".\n";
                return result;
            }
        } else { // nasla sa ciarka, je to range nejaky
            if (range.front() == ',')
                range = "1" + range;
            if (range.back() == ',')
                range = range + std::to_string(session.buffer.size());
            std::istringstream iss(range);
            std::string buffer;
            std::getline(iss, buffer, ',');
            int a = std::stoi(buffer);
            std::getline(iss,buffer,',');
            int b = std::stoi(buffer);
            if (a > b) {
                std::cout << "Unsupported range " << range << ". First number must be less than or equal to the second number.\n";
                return result;
            }
            if (a < 1 || a > session.buffer.size() || b < 1 || b > session.buffer.size()) {
                std::cout << "Unsupported range " << range << ".\n";
                return result;
            }
            for (int i = a-1; i <= b-1; i++)
                result.push_back(i);
            return result;
        }
    }
};



#endif //CONSOLETEXTEDITOR_COMMAND_H
