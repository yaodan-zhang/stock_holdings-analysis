#ifndef MY_STOCK_H
# define MY_STOCK_H
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <regex>
#include <memory>
#include"myList.h"
using std::string;
using std::ostream;
using std::ifstream;
using std::setw;
using std::fixed;
using std::setprecision;
using std::endl;
using std::invalid_argument;
using std::getline;
using std::regex;
using std::smatch;
using std::regex_match;
using std::string_view;
using std::stoi;
using std::stod;
using std::unique_ptr;

// Static member initialization
template<typename T>
int myList::listType<T>::fieldWidth = 10;

namespace myStock {
class stockType {
    public:
    // Default constructor
    stockType() = default;

    // A natural way of construct
    stockType(string t, double open, double close, double high, double low,
    double p_close, size_t v) : 
    ticker(t), t_open(open), t_close(close), t_high(high), t_low(low),
    prev_close(p_close), volume(v) {}

    // Copy constructor
    stockType(stockType const &) = default;

    // Print the stock info in (ticker open close high low prev_close percentage_gain volume)
    friend ostream& operator << (ostream&, stockType const &);
    friend ifstream& operator >> (ifstream&, stockType const &);

    // Calculate the percent gain from yesterday to today using closing prices
    double percent_gain() const 
    {
        return (t_close - prev_close) / prev_close * 100;
    }
    string ticker;
    double t_open;
    double t_close;
    double t_high;
    double t_low;
    double prev_close;
    size_t volume;
};

// Unique pointers comparison functions
bool comp_by_ticker_ptr (unique_ptr<stockType> const &a, unique_ptr<stockType> const &b) {
    return (a->ticker) < (b->ticker);
}

bool comp_by_gain_ptr (unique_ptr<stockType> const &a, unique_ptr<stockType> const &b) {
    return (a->percent_gain()) < (b->percent_gain());
}

// Print the stock info in format:
// symbol openingPrice closingPrice todayHigh todayLow prevClose percent_gain volume
// rounded to 2 decimal places.
ostream& operator << (ostream& os, stockType const & s) {
    // Set the fixed width for each field
    const int fieldWidth = myList::listType<stockType>::fieldWidth;
    os << setw(fieldWidth) << s.ticker
            << setw(fieldWidth) << fixed << setprecision(2) << s.t_open
            << setw(fieldWidth) << fixed << setprecision(2) << s.t_close
            << setw(fieldWidth) << fixed << setprecision(2) << s.t_high
            << setw(fieldWidth) << fixed << setprecision(2) << s.t_low
            << setw(fieldWidth) << fixed << setprecision(2) << s.prev_close
            << setw(fieldWidth) << fixed << setprecision(2) << s.percent_gain() << "%"
            << setw(fieldWidth) << s.volume << endl;;
}

// Allow file >> myStock where file is in format:
// symbol openingPrice closingPrice todayHigh todayLow prevClose volume
// For example, 
// MSMT 112.50 115.75 116.50 111.75 113.50 6723823
ifstream& operator >> (ifstream& infile, stockType & new_s) {
    if (infile.is_open()) {
        string line;
        regex pattern(R"((\w+) (\d+\.\d*) (\d+\.\d*) (\d+\.\d*) (\d+\.\d*) (\d+\.\d*) (\d+))");
        smatch matches;

        while (getline(infile, line)) {
            if (regex_match(line, matches, pattern)) {
                for (size_t i = 1; i < matches.size(); ++i) {
                    string_view matchedSubstring = matches[i].str();
                    switch (i)
                    {
                    case 1:
                        new_s.ticker = string(matchedSubstring);
                        break;
                    case 2:
                        new_s.t_open = stod(string(matchedSubstring));
                        break;
                    case 3:
                        new_s.t_close = stod(string(matchedSubstring));
                        break;
                    case 4:
                        new_s.t_high = stod(string(matchedSubstring));
                        break;
                    case 5:
                        new_s.t_low = stod(string(matchedSubstring));
                        break; 
                    case 6:
                        new_s.prev_close = stod(string(matchedSubstring));
                        break;
                    case 7:
                        new_s.volume = stoi(string(matchedSubstring));
                        break;
                    default:
                        throw invalid_argument("the file is ill-formed!");
                        break;
                    }
                }
            }
        }
    }
    throw invalid_argument("the file is not opened!");
}
}
#endif