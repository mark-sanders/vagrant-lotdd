#include "Soundex.h"

const std::string Soundex::NotEncoded { "" };
const std::string Soundex::Ignore { "-" };

//  Replace consonants with digits as follows (after the first letter):
//  - b, f, p, v => 1
//  - c, g, j, k, q, s, x, z => 2
//  - d, t       => 3
//  - l          => 4
//  - m, n       => 5
//  - r          => 6
const std::map<char, const std::string> Soundex::CharToDigitMap {
    { 'B', "1" }, { 'F', "1" }, { 'P', "1" }, { 'V', "1" },
    { 'C', "2" }, { 'G', "2" }, { 'J', "2" }, { 'K', "2" }, { 'Q', "2" }, { 'S', "2" }, { 'X', "2" }, { 'Z', "2" },
    { 'D', "3" }, { 'T', "3" },
    { 'L', "4" },
    { 'M', "5" }, { 'N', "5" },
    { 'R', "6" },
    { 'H', Soundex::Ignore }, { 'W', Soundex::Ignore },
};