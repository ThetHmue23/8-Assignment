cmake_minimum_required(VERSION 3.21)
project(Bank_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Bank_Project main.cpp bank.cpp bank.h BankDatabase.cpp BankDatabase.h)
