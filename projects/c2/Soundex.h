#include <string>
#include <map>

class Soundex 
{
public:
    std::string encode(const std::string& word) const {
        return zeroPad(head(word) + encodeDigits(word));
    }

private:
    static const size_t MAX_ENCODED_DIGITS { 3 };
    static const size_t MAX_CODE_LENGTH { 1 + MAX_ENCODED_DIGITS };
    static const std::map<char, const std::string> CHAR_TO_DIGIT_MAP;

    std::string head(const std::string& word) const {
        return word.substr(0, 1);
    }

    std::string encodeDigits(const std::string& word) const {
        std::string digits;
        std::string last = "";
        for (auto iter = word.begin() + 1; iter != word.end() && digits.length() < MAX_ENCODED_DIGITS; iter++) {
            std::string digit = encodeDigit(*iter);
            if (digit != last) {
                digits += digit;
                last = digit;
            }
        }

        return digits;
    }

    std::string encodeDigit(char letter) const {
        auto it = CHAR_TO_DIGIT_MAP.find(letter);

        if (it == CHAR_TO_DIGIT_MAP.end()) {
            return "";
        } else {
            return it->second;
        }
    }

    std::string zeroPad(const std::string& encoded) const {
        auto zerosNeeded = MAX_CODE_LENGTH - encoded.length();
        return encoded + std::string(zerosNeeded, '0');
    }
};
