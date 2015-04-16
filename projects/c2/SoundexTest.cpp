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

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigist)
{
    ASSERT_THAT(soundex.encode("I"), Eq("I000"));
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits)
{
    EXPECT_THAT(soundex.encode("Ab"), Eq("A100"));
    EXPECT_THAT(soundex.encode("Ap"), Eq("A100"));

    EXPECT_THAT(soundex.encode("Ac"), Eq("A200"));
    EXPECT_THAT(soundex.encode("Ag"), Eq("A200"));

    EXPECT_THAT(soundex.encode("Ad"), Eq("A300"));
    EXPECT_THAT(soundex.encode("At"), Eq("A300"));
    
    EXPECT_THAT(soundex.encode("Al"), Eq("A400"));

    EXPECT_THAT(soundex.encode("Am"), Eq("A500"));
    EXPECT_THAT(soundex.encode("An"), Eq("A500"));

    EXPECT_THAT(soundex.encode("Ar"), Eq("A600"));
}