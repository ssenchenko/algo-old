//
// Created by  Slava Senchenko on 2017-01-14.
//

#ifndef HUGEINT_MYUTIL_H
#define HUGEINT_MYUTIL_H

#include <string>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <ios>

std::string const scDataPath("../../test_data/");

std::string const scDigits("0123456789");
std::string const scNewLine("\r\n");
std::string const scTenthDelim(".");

std::string const scWrongNumber = "Wrong number. Please try again";
std::string const scNoFileName = "No file with such a name... :(";
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
double getDouble(std::string sInputString) throw (WrongIntInput);

// get an long array from the string which contains ONLY 1 delimiter
std::vector<long> parse_for_long(std::string s, std::string delimeter = "\t");

// get an long array from the string which contains ONLY 1 delimiter
std::vector<int> parse_for_int(std::string s, std::string delimeter = "\t");

// get double array from the string which contains only 1 delimiter
std::vector<double> parse_for_double(std::string s, std::string delimeter = "\t");

// if a string contains more than one delimiter, first it has to be parsed to get strings
std::vector<std::string> parse_for_string(std::string s, std::string delimeter = "\t");

// get current directory
std::string getCwd();

// ----------------------------- DON'T USE ANY MORE --------------------------------------
// get an integer array from the string which contains ONLY 1 delimiter
// USE parse_for_int instead
std::vector<int> parse_string(std::string s, std::string delimeter = "\t");
// get a string array from the string
// use this function if parsed string contains more than 1 delimiter
// or if you need to get strings instead of integers
// USE parse_for_string
std::vector<std::string> preparse_string(std::string s, std::string delimeter = "\t");

#endif //HUGEINT_MYUTIL_H
