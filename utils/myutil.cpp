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
