#include <string>
#include <map>


class Soundex 
{
public:
    std::string encode(const std::string& raw) const {

        const std::string& word = toUpperAlpha(raw);

        if (word.empty()) {
            return "";
        } else {
            return zeroPad(head(word) + wordsToDigits(word));
        }
    }

private:
    static const size_t MaxEncodedDigits { 3 };
    static const size_t MaxDigitsLength { 1 + MaxEncodedDigits };

    // vowels are not encoded but separate characters encoded with different digits
    static const std::string NotEncoded;

    // 'H' or 'W' are not encoded and do not separate characters encoded with different digits
    static const std::string Ignore;

    // map from an (uppercase) character to the digit it encodes (or Ignore if 'H' or 'W')
    static const std::map<char, const std::string> CharToDigitMap;

    std::string toUpperAlpha(const std::string& raw) const {
        std::string word;
        for (auto iter = raw.begin(); iter != raw.end(); ++iter) {
            char c = *iter;
            if (::isalpha(c)) {
                word += ::toupper(c);
            }
        }

        return word;
    }

    std::string head(const std::string& word) const {
        return word.substr(0, 1);
    }

    std::string wordsToDigits(const std::string& word) const {
        auto iter = word.begin();
        std::string previousDigit = charToDigit(*iter++);

        std::string digits;
        while (iter != word.end() && digits.length() < MaxEncodedDigits) {

            std::string digit = charToDigit(*iter++);
            
            if (digit != NotEncoded && digit != Ignore && digit != previousDigit) {
                digits += digit;
            }
            
            if (digit != Ignore) {
                previousDigit = digit;
            }
        }

        return digits;
    }

    std::string charToDigit(char letter) const {
        auto it = CharToDigitMap.find(letter);

        if (it == CharToDigitMap.end()) {
            return NotEncoded;
        } else {
            return it->second;
        }
    }

    std::string zeroPad(const std::string& encoded) const {
        auto zerosNeeded = MaxDigitsLength - encoded.length();
        return encoded + std::string(zerosNeeded, '0');
    }
};
