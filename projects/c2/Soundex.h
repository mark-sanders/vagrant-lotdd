#include <algorithm>
#include <string>
#include <map>

// #include <iostream>

class Soundex 
{
public:
    std::string encode(const std::string& word) const {
        if (word.empty()) {
            return "";
        } else {
            return zeroPad(head(word) + encodeDigits(word));
        }
    }

private:
    static const size_t MaxEncodedDigits { 3 };
    static const size_t MaxDigitsLength { 1 + MaxEncodedDigits };
    static const std::map<char, const std::string> CharToDigitMap;

    std::string head(const std::string& word) const {
        char c = ::toupper(word[0]);
        std::string head(1, c);
        return head;
    }

    std::string encodeDigits(const std::string& word) const {
        std::string digits;
        auto iter = word.begin();
        std::string lastDigit = encodeDigit(*iter++);

        while (iter != word.end() && digits.length() < MaxEncodedDigits) {

            std::string digit = encodeDigit(*iter++);
            
            if (!digit.empty() && digit != "-" && digit != lastDigit) {
                digits += digit;
            }
            
            if (digit != "-") {
                lastDigit = digit;
            }
        }

        return digits;
    }

    std::string encodeDigit(char letter) const {
        auto it = CharToDigitMap.find(::tolower(letter));

        if (it == CharToDigitMap.end()) {
            return "";
        } else {
            return it->second;
        }
    }

    std::string zeroPad(const std::string& encoded) const {
        auto zerosNeeded = MaxDigitsLength - encoded.length();
        return encoded + std::string(zerosNeeded, '0');
    }
};
