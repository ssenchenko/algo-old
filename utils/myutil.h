//
// Created by  Slava Senchenko on 2017-01-14.
//

#ifndef HUGEINT_MYUTIL_H
#define HUGEINT_MYUTIL_H

#include <string>
#include <stdexcept>
#include <vector>

std::string const scDataPath("../../test_data/");

std::string const scDigits("0123456789");
std::string const scNewLine("\r\n");

std::string const scWrongNumber = "Wrong number. Please try again";
std::string const scGetlineError = "Error reading a string";
std::string const scUnexpectedEOF = "Unexpected end of file";

// exception for the wrong integer input
class WrongIntInput : public std::domain_error {
public:
    WrongIntInput(std::string s) : std::domain_error(s) {};
};

// check and get input number
int getInteger ();
// check and get input number
int getInteger (std::string sInputString) throw (WrongIntInput);
long getLong (std::string sInputString) throw (WrongIntInput);

// get an integer array from the string which contains ONLY 1 delimiter
std::vector<int> parse_string(std::string s, std::string delimeter = "\t");
// get a string array from the string
// use this function if parsed string contains more than 1 delimiter
// or if you need to get strings instead of integers
std::vector<std::string> preparse_string(std::string s, std::string delimeter = "\t");

// get current directory
std::string getCwd();

#endif //HUGEINT_MYUTIL_H
