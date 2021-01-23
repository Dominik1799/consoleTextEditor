cmake_minimum_required(VERSION 3.17)
project(consoleTextEditor)

set(CMAKE_CXX_STANDARD 17)

add_executable(consoleTextEditor main.cpp SessionManager.cpp SessionManager.h Session.h commands/PrintCommand.cpp commands/PrintCommand.h commands/Command.h)