#include <string>

class Soundex 
{
public:
    std::string encode(const std::string& word) const {
        return zeroPad(head(word) + encodeDigits(word));
    }

private:

    static const size_t MAX_CODE_LENGTH { 4 };

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
        if (letter == 'c' || letter == 'g') {
            return "2";
        } else {
            return "1";
        }
    }

    std::string zeroPad(const std::string& word) const {
        auto zerosNeeded = MAX_CODE_LENGTH - word.length();
        return word + std::string(zerosNeeded, '0');
    }
};
