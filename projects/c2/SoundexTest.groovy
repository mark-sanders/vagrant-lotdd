@Grab(group='commons-codec', module='commons-codec', version='1.10') 

import org.apache.commons.codec.language.Soundex

class Encoder {
    def encoder = new Soundex()

    def encode(s) {
        def result = encoder.encode(s)
        println "$s => $result"
        result
    }
}

def soundex = new Encoder()

println soundex.encode("B")

def Eq(s) { s }

def ASSERT_THAT(actual, expected) { assert actual == expected }
def EXPECT_THAT(actual, expected) { assert actual == expected }

// (SoundexEncoding, RetainsSoleLetterOfOneLetterWord)
// 
    ASSERT_THAT(soundex.encode("A"), Eq("A000"));
//

// (SoundexEncoding, PadsWithZerosToEnsureThreeDigits)
// 
    ASSERT_THAT(soundex.encode("I"), Eq("I000"));
// 

// (SoundexEncoding, ReplacesConsonantsWithAppropriateDigits)
// 
    EXPECT_THAT(soundex.encode("Ab"), Eq("A100"));
    EXPECT_THAT(soundex.encode("Ap"), Eq("A100"));

    EXPECT_THAT(soundex.encode("ac"), Eq("A200"));
    EXPECT_THAT(soundex.encode("ag"), Eq("A200"));

    EXPECT_THAT(soundex.encode("AD"), Eq("A300"));
    EXPECT_THAT(soundex.encode("AT"), Eq("A300"));
    
    EXPECT_THAT(soundex.encode("al"), Eq("A400"));

    EXPECT_THAT(soundex.encode("aM"), Eq("A500"));
    EXPECT_THAT(soundex.encode("an"), Eq("A500"));

    EXPECT_THAT(soundex.encode("AR"), Eq("A600"));
// 

// (SoundexEncoding, ReplacesMultipleConsonantsWithAppropriateDigits)
// 
    EXPECT_THAT(soundex.encode("Abc"), Eq("A120"));
    EXPECT_THAT(soundex.encode("Abcd"), Eq("A123"));
    EXPECT_THAT(soundex.encode("Atl"), Eq("A340"));

    EXPECT_THAT(soundex.encode("Abcdl"), Eq("A123"));
// 

// (SoundexEncoding, ReplacesMultipleConsonantsWithUpToThreeDigits)
// 
    EXPECT_THAT(soundex.encode("Abcdl"), Eq("A123"));
    EXPECT_THAT(soundex.encode("Abcdlm"), Eq("A123"));
// 

// (SoundexEncoding, DropVowelLikeLettersBeyondFirst)
// 
    EXPECT_THAT(soundex.encode("Aar"), Eq("A600"));
    EXPECT_THAT(soundex.encode("Far"), Eq("F600"));
// 

// (SoundexEncoding, TwoAdjacentConsonantsWithSameEncodingAreElided)
// 
    EXPECT_THAT(soundex.encode("Agg"), Eq("A200"));
    EXPECT_THAT(soundex.encode("Arr"), Eq("A600"));
// 

// (SoundexEncoding, TwoAdjacentConsonantsWithSameEncodingAreElidedEvenWhenIntial)
// 
    EXPECT_THAT(soundex.encode("Pfister"), Eq("P236"));

// 

// (SoundexEncoding, ThreeAdjacentConsonantsWithSameEncodingAreElided)
// 
    EXPECT_THAT(soundex.encode("Arrr"), Eq("A600"));
    EXPECT_THAT(soundex.encode("Acks"), Eq("A200"));
// 

// (SoundexEncoding, TwoConsonantsSeparatedByVowelAreNotElided)
// 
    EXPECT_THAT(soundex.encode("Agog"), Eq("A220"));
    EXPECT_THAT(soundex.encode("Stat"), Eq("S330"));
    EXPECT_THAT(soundex.encode("Tymczak"), Eq("T522"));
// 

// (SoundexEncoding, TwoConsonantsSeparatedBy_H_Or_W_AreElided)
// 
    EXPECT_THAT(soundex.encode("Aghg"), Eq("A200"));
    EXPECT_THAT(soundex.encode("Agwg"), Eq("A200"));

    EXPECT_THAT(soundex.encode("Ashcroft"), Eq("A261"));
    EXPECT_THAT(soundex.encode("Ashcraft"), Eq("A261"));
// 


// (SoundexEncoding, Examples)
// 
    EXPECT_THAT(soundex.encode("Robert"), Eq("R163"));
    EXPECT_THAT(soundex.encode("Rupert"), Eq("R163"));
// 

    EXPECT_THAT(soundex.encode("Ghg"), Eq("G000"));
    EXPECT_THAT(soundex.encode("Cwc"), Eq("C000"));

    EXPECT_THAT(soundex.encode("Gog"), Eq("G200"));
    EXPECT_THAT(soundex.encode("Cac"), Eq("C200"));
