//
// Created by  Slava Senchenko on 2017-01-14.
//

#include "myutil.h"

#include <unistd.h>
#include <iostream>

using std::istream;
using std::string;
using std::endl;
using std::cerr;
using std::cin;

// check and get input number
int getInteger () {

    bool bOK = false;
    int iInputNumber(0);
    string sInputNumber("");

    while (!bOK) {
        getline(std::cin, sInputNumber);

        if (cin.fail()) {
            cerr << scGetlineError << endl;
            cin.clear();
        }

        try {
            iInputNumber = getInteger(sInputNumber);
            bOK = true;
        }
        catch (std::domain_error e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return iInputNumber;
}

// check and get input number
int getInteger (string sInputNumber) throw(WrongIntInput) {

    int iInputNumber(0);
    std::size_t found, start = 0;

    // clear new line symbols
    found = sInputNumber.find_first_of(scNewLine);
    if (found != string::npos)
        sInputNumber.erase(sInputNumber.begin() + found);

    // check if number is negative
    found = sInputNumber.find("-", 0, 1); // check only the 1st character
    if (found != string::npos)
        start = 1; //offset for the next check
    // check that there are no non-digit characters
    found = sInputNumber.find_first_not_of(scDigits, start);
    if (found != string::npos) throw WrongIntInput(scWrongNumber + " " + sInputNumber);
    else iInputNumber = std::stoi(sInputNumber);

    return iInputNumber;
}

// get current directory
std::string getCwd() {
    int const SIZE = 255;
    char buffer[SIZE];
    char *pcCwd = getcwd(buffer, sizeof(buffer));
    string sCwd;
    if (pcCwd)
        sCwd = pcCwd;
    return sCwd;
}

// get an integer array from the string
std::vector<int> parse_string(std::string s, std::string delimeter){
    std::vector<int> numbers;

    std::string::size_type cur_pos = 0, found = std::string::npos;
    int num = 0;
    std::string tmp;

    found = s.find(delimeter, cur_pos);
    while (found != std::string::npos) {
        tmp = s.substr(cur_pos, found - cur_pos);
        try {
            num = getInteger(tmp);
            numbers.push_back(num);
        }
        catch (std::domain_error e) {
            std::cerr << e.what() << std::endl;
        }
        cur_pos = found + 1;
        found = s.find(delimeter, cur_pos);
    }
    // get the last number
    tmp = s.substr(cur_pos, found - 1);
    found = tmp.find_first_of(scDigits);
    if (found != std::string::npos) {
        try {
            num = getInteger(tmp);
            numbers.push_back(num);
        }
        catch (WrongIntInput e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return numbers;
}

// use this function if parsed string contains more than 1 delimiter
std::vector<std::string> preparse_string(std::string s, std::string delimeter) {

    std::vector<string> tuples;
    std::string::size_type cur_pos = 0, found = std::string::npos;

    found = s.find(delimeter, cur_pos);
    while (found != std::string::npos) {
        tuples.push_back(s.substr(cur_pos, found - cur_pos));
        cur_pos = found + 1;
        found = s.find(delimeter, cur_pos);
    }
    // get the last tuple
    string tmp = s.substr(cur_pos, found - 1);
    found = s.substr(cur_pos, found - 1).find_first_of(scDigits);
    if (found != std::string::npos) {
        tuples.push_back(tmp);
    }

    return tuples;
}

// check and get input number
long getLong (string sInputNumber) throw(WrongIntInput) {

    long iInputNumber(0);
    std::size_t found, start = 0;

    // clear new line symbols
    found = sInputNumber.find_first_of(scNewLine);
    if (found != string::npos)
        sInputNumber.erase(sInputNumber.begin() + found);

    // check if number is negative
    found = sInputNumber.find("-", 0, 1); // check only the 1st character
    if (found != string::npos)
        start = 1; //offset for the next check
    // check that there are no non-digit characters
    found = sInputNumber.find_first_not_of(scDigits, start);
    if (found != string::npos) throw WrongIntInput(scWrongNumber + " " + sInputNumber);
    else
        iInputNumber = std::stol(sInputNumber);

    return iInputNumber;
}

// get an long array from the string which contains ONLY 1 delimiter
std::vector<long> parse_for_long(std::string s, std::string delimeter) {
    std::vector<long> numbers;

    std::string::size_type cur_pos = 0, found = std::string::npos;
    long num = 0;
    std::string tmp;

    found = s.find(delimeter, cur_pos);
    while (found != std::string::npos) {
        tmp = s.substr(cur_pos, found - cur_pos);
        try {
            num = getLong(tmp);
            numbers.push_back(num);
        }
        catch (std::domain_error e) {
            std::cerr << e.what() << std::endl;
        }
        cur_pos = found + 1;
        found = s.find(delimeter, cur_pos);
    }
    // get the last number
    tmp = s.substr(cur_pos, found - 1);
    found = tmp.find_first_of(scDigits);
    if (found != std::string::npos) {
        try {
            num = getLong(tmp);
            numbers.push_back(num);
        }
        catch (WrongIntInput e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return numbers;
}

// get an long array from the string which contains ONLY 1 delimiter
std::vector<int> parse_for_int(std::string s, std::string delimeter) {
    return parse_string(s, delimeter);
}

// get an long array from the string which contains ONLY 1 delimiter
std::vector<std::string> parse_for_string(std::string s, std::string delimeter) {
    return preparse_string(s, delimeter);
}

double getDouble(std::string sInputNumber) throw (WrongIntInput) {
    double iInputNumber(0.0);
    std::size_t found, start = 0;

    // clear new line symbols
    found = sInputNumber.find_first_of(scNewLine);
    if (found != string::npos)
        sInputNumber.erase(sInputNumber.begin() + found);

    // check if number is negative
    found = sInputNumber.find("-", 0, 1); // check only the 1st character
    if (found != string::npos)
        start = 1; //offset for the next check
    // check that there are no non-digit characters
    string const scDoubleDigits = scDigits + scTenthDelim;
    found = sInputNumber.find_first_not_of(scDoubleDigits, start);
    // check that there is only one '.' and it's not last symbol
    if (found == string::npos) {
        found = sInputNumber.find(scTenthDelim); // look for '.'
        if (found != string::npos) { // there is '.'
            if (found != sInputNumber.size() - 1) { // '.' is not last symbol
                string s = sInputNumber.substr(found + 1);
                found = s.find(scTenthDelim);
            }
        }
    }
    
    if (found != string::npos) throw WrongIntInput(scWrongNumber + " " + sInputNumber);
    else iInputNumber = std::stod(sInputNumber);

    return iInputNumber;
}

std::vector<double> parse_for_double(std::string s, std::string delimeter) {
    std::vector<double> numbers;

    std::string::size_type cur_pos = 0, found = std::string::npos;
    double num = 0;
    std::string tmp;

    found = s.find(delimeter, cur_pos);
    while (found != std::string::npos) {
        tmp = s.substr(cur_pos, found - cur_pos);
        try {
            num = getDouble(tmp);
            numbers.push_back(num);
        }
        catch (std::domain_error e) {
            std::cerr << e.what() << std::endl;
        }
        cur_pos = found + 1;
        found = s.find(delimeter, cur_pos);
    }
    // get the last number
    tmp = s.substr(cur_pos, found - 1);
    found = tmp.find_first_of(scDigits);
    if (found != std::string::npos) {
        try {
            num = getDouble(tmp);
            numbers.push_back(num);
        }
        catch (WrongIntInput e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return numbers;
}
