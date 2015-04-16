#include "gmock/gmock.h"
#include "Soundex.h"

using ::testing::Eq;
class SoundexEncoding: public testing::Test {
public:
    Soundex soundex;
};


TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord)
{
    ASSERT_THAT(soundex.encode("A"), Eq("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits)
{
    ASSERT_THAT(soundex.encode("I"), Eq("I000"));
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits)
{
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
}

TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithAppropriateDigits)
{
    EXPECT_THAT(soundex.encode("Abc"), Eq("A120"));
    EXPECT_THAT(soundex.encode("Abcd"), Eq("A123"));
    EXPECT_THAT(soundex.encode("Atl"), Eq("A340"));

    EXPECT_THAT(soundex.encode("Abcdl"), Eq("A123"));
}

TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithUpToThreeDigits)
{
    ASSERT_THAT(soundex.encode("Abcdl"), Eq("A123"));
    ASSERT_THAT(soundex.encode("Abcdlm"), Eq("A123"));
}

TEST_F(SoundexEncoding, DropVowelLikeLettersBeyondFirst)
{
    ASSERT_THAT(soundex.encode("Aar"), Eq("A600"));
    ASSERT_THAT(soundex.encode("Far"), Eq("F600"));
}

TEST_F(SoundexEncoding, TwoAdjacentConsonantsWithSameEncodingAreElided)
{
    ASSERT_THAT(soundex.encode("Agg"), Eq("A200"));
    ASSERT_THAT(soundex.encode("Arr"), Eq("A600"));
}

TEST_F(SoundexEncoding, TwoAdjacentConsonantsWithSameEncodingAreElidedEvenWhenIntial)
{
    ASSERT_THAT(soundex.encode("Pfister"), Eq("P236"));

}

TEST_F(SoundexEncoding, ThreeAdjacentConsonantsWithSameEncodingAreElided)
{
    ASSERT_THAT(soundex.encode("Arrr"), Eq("A600"));
    ASSERT_THAT(soundex.encode("Acks"), Eq("A200"));
}

TEST_F(SoundexEncoding, TwoConsonantsSeparatedByVowelAreNotElided)
{
    EXPECT_THAT(soundex.encode("Agog"), Eq("A220"));
    EXPECT_THAT(soundex.encode("Stat"), Eq("S330"));
    EXPECT_THAT(soundex.encode("Tymczak"), Eq("T522"));

    EXPECT_THAT(soundex.encode("Gog"), Eq("G200"));
    EXPECT_THAT(soundex.encode("Cac"), Eq("C200"));
}

TEST_F(SoundexEncoding, TwoConsonantsSeparatedBy_H_Or_W_AreElided)
{
    EXPECT_THAT(soundex.encode("Aghg"), Eq("A200"));
    EXPECT_THAT(soundex.encode("Agwg"), Eq("A200"));

    EXPECT_THAT(soundex.encode("Ashcroft"), Eq("A261"));
    EXPECT_THAT(soundex.encode("Ashcraft"), Eq("A261"));
}

TEST_F(SoundexEncoding, TwoConsonantsSeparatedBy_H_Or_W_AreElidedIncludingInitial)
{
    ASSERT_THAT(soundex.encode("Ghg"), Eq("G000"));
    ASSERT_THAT(soundex.encode("Cwc"), Eq("C000"));
}


TEST_F(SoundexEncoding, Examples)
{
    ASSERT_THAT(soundex.encode("Robert"), Eq("R163"));
    ASSERT_THAT(soundex.encode("Rupert"), Eq("R163"));
}


TEST_F(SoundexEncoding, EmptyStringEncodesAsEmptyString)
{
    ASSERT_THAT(soundex.encode(""), Eq(""));
}

TEST_F(SoundexEncoding, SoleNonAlphabeticalCharactersAreIgnored)
{
    ASSERT_THAT(soundex.encode("-"), Eq(""));
    ASSERT_THAT(soundex.encode("*"), Eq(""));
    ASSERT_THAT(soundex.encode("!!!"), Eq(""));
}

TEST_F(SoundexEncoding, InitialNonAlphabeticalCharactersAreIgnored)
{
    ASSERT_THAT(soundex.encode("-Robert"), Eq("R163"));
    ASSERT_THAT(soundex.encode("*Rupert"), Eq("R163"));
    ASSERT_THAT(soundex.encode("!!!Rupert"), Eq("R163"));
}

TEST_F(SoundexEncoding, OtherNonAlphabeticalCharactersAreIgnored)
{
    ASSERT_THAT(soundex.encode("ONeill"), Eq("O540"));
    ASSERT_THAT(soundex.encode("O'Neil"), Eq("O540"));
    ASSERT_THAT(soundex.encode("O'''Neil"), Eq("O540"));
    ASSERT_THAT(soundex.encode("Smith-Jones"), Eq("S532"));
}