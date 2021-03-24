#pragma once

#include "ast.hpp"

// General utility functions

union {
        uint32_t num;
        float fnum;
} singleIEEE754Float;

std::string generateUniqueLabel(const std::string &labelName);

// uses t6 as temporary
void regToVar(std::ostream &assemblyOut, Frame* frame, const std::string& reg, const std::string& var, const std::string& reg_2 = "");

// uses t6 as temporary
void varToReg(std::ostream &assemblyOut, Frame* frame, const std::string& reg, const std::string& var);
// uses t6 as temporary
void varAddressToReg(std::ostream &assemblyOut, Frame* frame, const std::string& reg, const std::string& var);

// for global variables
void valueToVarLabel(std::ostream &assemblyOut, int value, std::string varLabel);
void valueToVarLabel(std::ostream &assemblyOut, float value, std::string varLabel);

// check if string ends with suffix
bool hasEnding(const std::string &fullString, const std::string &ending);
