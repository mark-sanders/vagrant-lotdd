#include "Soundex.h"

//  Replace consonants with digits as follows (after the first letter):
//  - b, f, p, v => 1
//  - c, g, j, k, q, s, x, z => 2
//  - d, t       => 3
//  - l          => 4
//  - m, n       => 5
//  - r          => 6
const std::map<char, const std::string> Soundex::CharToDigitMap {
    { 'b', "1" }, { 'f', "1" }, { 'p', "1" }, { 'v', "1" },
    { 'c', "2" }, { 'g', "2" }, { 'j', "2" }, { 'k', "2" }, { 'q', "2" }, { 's', "2" }, { 'x', "2" }, { 'z', "2" },
    { 'd', "3" }, { 't', "3" },
    { 'l', "4" },
    { 'm', "5" }, { 'n', "5" },
    { 'r', "6" },
    { 'h', "-" }, { 'w', "-" },
};