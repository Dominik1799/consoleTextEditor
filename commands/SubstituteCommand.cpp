#include "SubstituteCommand.h"

SubstituteCommand *SubstituteCommand::instance = nullptr;

SubstituteCommand *SubstituteCommand::getInstance() {
    if (!instance)
        instance = new SubstituteCommand();
    return nullptr;
}

void SubstituteCommand::execute(const std::vector<std::string> &commands, Session &session, std::string& rawCommand) {
    if (commands.size() <  2) {
        std::cout << "Wrong input for command substitute.\n";
        return;
    }
    std::string possibleRange;
    std::string f = checkFilter(rawCommand, possibleRange);
    std::vector<std::string> filter = parseFilter(f);
    if (filter.empty()) {
        std::cout << "Wrong filter format for command substitute: " << f <<"\n";
        return;
    }
    std::vector<int> indexes;
    std::string mainBuffer;
    std::string occurrencesBuffer;
    if (!possibleRange.empty()) {
        indexes = processRange(possibleRange, session);
        if (indexes.empty())
            return;
        for (auto& i : indexes) {
            mainBuffer += session.buffer[i];
            mainBuffer += "\n";
        }
        occurrencesBuffer = mainBuffer;
    } else {
        for (auto& line : session.buffer) {
            mainBuffer += line;
            mainBuffer += "\n";
        }
        occurrencesBuffer = mainBuffer;
    }
    std::string pattern = filter[0];
    std::string replace = filter[1];
    std::string subForCounting = "<$" + replace + "?>";
    std::regex regex(pattern, std::regex::extended);
    mainBuffer = std::regex_replace(mainBuffer,regex, replace, std::regex_constants::match_any | std::regex_constants::format_sed);
    occurrencesBuffer = std::regex_replace(occurrencesBuffer,regex,subForCounting , std::regex_constants::match_any | std::regex_constants::format_sed);
    int numOfOccurrences = replaceAll(occurrencesBuffer, subForCounting, "");
    std::stringstream ss(mainBuffer);
    std::string line;
    std::vector<std::string> newContent;
    while (std::getline(ss,line, '\n'))
        newContent.push_back(line);
    if (indexes.empty()) {
        session.buffer = newContent;
        std::cout << numOfOccurrences << " matches\n";
        return;
    }
    size_t j{0};
    bool replacedAll{false};
    std::vector<std::string> resultContent;
    for (size_t i = 0; i < session.buffer.size(); i++) {
        if (j < indexes.size() && i == indexes[j]) {
            j++;
            if (replacedAll)
                continue;
            for (auto& s : newContent)
                resultContent.push_back(s);
            replacedAll = true;
            continue;
        }
        resultContent.push_back(session.buffer[i]);
    }
    session.buffer = resultContent;
    std::cout << numOfOccurrences << " matches\n";
}

int SubstituteCommand::replaceAll(std::string &data, const std::string &toSearch, const std::string &replaceStr) {
    int count{0};
    size_t pos = data.find(toSearch);
    while( pos != std::string::npos) {
        count++; //   \\n    \n
        if (pos != 0 && data[pos-1] != '\\') data.replace(pos, toSearch.size(), replaceStr);
        pos = data.find(toSearch, pos + replaceStr.size());
    }
    return count;
}

std::vector<std::string> SubstituteCommand::parseFilter(std::string &filter) {
    bool wasSuccess;
    std::unordered_set<char> specialChars{'.', '[', ']', '\\', '(', ')', '*', '+', '?', '{', '}', '|' , '^', '$'};
    replaceAll(filter, "\\n", "\n");
    std::string find;
    std::string replace;
    std::vector<std::string> result;
    bool isEscaped{false};
    int splitters{0};
    char last;
    for (auto& c : filter) {
        last = c;
        if (c == '/' && !isEscaped) {
            splitters++;
            continue;
        }
        if (splitters == 1) { // find-part of the filer
            if (c == '\\' && !isEscaped) {
                isEscaped = true;
                continue;
            }
            if (c == '\\' && isEscaped) {
                find += "\\\\";
                isEscaped = false;
                continue;
            }
            if (c == '/' && isEscaped) {
                find += "/";
                isEscaped = false;
                continue;
            }
            if (c == '*' && !isEscaped) {
                find += "(.*)";
                continue;
            }
            if (c == '*' && isEscaped) {
                find += "\\*";
                isEscaped = false;
                continue;
            }
            if (specialChars.count(c)) {
                find += "\\";
                find += c;
                continue;
            }
            find += c;
        }
        if (splitters == 2)
            replace += c;
    }
    wasSuccess = splitters == 3 && last == '/';
    if (wasSuccess) {
        result.push_back('(' + find + ')');
        result.push_back(replace);
    }
    return result;
}

std::string SubstituteCommand::checkFilter(std::string& rawCommand, std::string& possibleRange) {
    std::string result;
    std::string temp;
    int splitters{0};
    bool isEscaped{false};
    for (auto& c : rawCommand) {
        if (c == '/' && !isEscaped) {
            result += c;
            splitters++;
            continue;
        }
        if (splitters > 0 && splitters < 3) {
            result += c;
            if (c == '\\' && !isEscaped) {
                isEscaped = true;
                continue;
            }
            if (isEscaped) {
                isEscaped = false;
                continue;
            }
        }
        if (splitters >= 3 && c != ' ')
            possibleRange += c;

    }
    return result;
}



