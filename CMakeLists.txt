cmake_minimum_required(VERSION 3.17)
project(consoleTextEditor)

set(CMAKE_CXX_STANDARD 17)

add_executable(consoleTextEditor main.cpp SessionManager.cpp SessionManager.h Session.h commands/PrintCommand.cpp commands/PrintCommand.h commands/Command.h commands/WriteCommand.cpp commands/WriteCommand.h commands/AppendCommand.cpp commands/AppendCommand.h commands/ChangeCommand.cpp commands/ChangeCommand.h commands/DeleteCommand.cpp commands/DeleteCommand.h commands/QuitCommand.cpp commands/QuitCommand.h)