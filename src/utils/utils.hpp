#ifndef UTILS_HPP
#define UTILS_HPP


#include <unordered_map>
#include <map>
#include <iostream>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace boost;

namespace utils {
    typedef enum modifiers {
        ENCasualTimeParser,
        ENCasualDateParser,
        ENDeadlineFormatParser,
    } Modifiers;

    typedef std::unordered_map<Modifiers, bool > Tags;

    static std::map<std::string, int> INTEGER_WORDS {
        {"one",    1},
        {"two",    2},
        {"three",  3},
        {"four",   4},
        {"five",   5},
        {"six",    6},
        {"seven",  7},
        {"eight",  8},
        {"nine",   9},
        {"ten",    10},
        {"eleven", 11},
        {"twelve", 12}
    };


}

#endif