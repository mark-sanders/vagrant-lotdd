#include <string>

class Soundex 
{
public:
    std::string encode(const std::string& word) const {
        return zeroPad(head(word) + encodeDigits(word));
    }

private:

    static const size_t MAX_CODE_LENGTH { 4 };

    //  Replace consonants with digits as follows (after the first letter):
    //  - b, f, p, v => 1
    //  - c, g, j, k, q, s, x, z => 2
    //  - d, t       => 3
    //  - l          => 4
    //  - m, n       => 5
    //  - r          => 6
    const std::map<char, const std::string> charToDigitMap = {
        { 'b', "1" }, { 'f', "1" }, { 'p', "1" }, { 'v', "1" },
        { 'c', "2" }, { 'g', "2" }, { 'j', "2" }, { 'k', "2" }, { 'q', "2" }, { 's', "2" }, { 'x', "2" }, { 'z', "2" },
        { 'd', "3" }, { 't', "3" },
        { 'l', "4" },
        { 'm', "5" }, { 'n', "5" },
        { 'r', "6" },
    };

    std::string head(const std::string& word) const {
        return word.substr(0, 1);
    }

    std::string encodeDigits(const std::string& word) const {
        if (word.length() > 1) {
            return encodeDigit(word[1]);
        } else {
            return "";
        }
    }

    std::string encodeDigit(char letter) const {
        auto it = charToDigitMap.find(letter);
        if (it == charToDigitMap.end()) {
            return "";
        } else {
            return it->second;
        }
    }

    std::string zeroPad(const std::string& word) const {
        auto zerosNeeded = MAX_CODE_LENGTH - word.length();
        return word + std::string(zerosNeeded, '0');
    }
};
