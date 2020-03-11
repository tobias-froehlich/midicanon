#include "../src/const.h"
#include "../src/utils.h"

TEST(utils, split) {
  std::string str;
  std::vector< std::string > words;


  str = "eins zwei drei";
  words = {"eins", "zwei", "drei"};
  ASSERT_EQ(utils::split(str, ' '), words);

  str = " eins  zwei   drei ";
  words = {"eins", "zwei", "drei"};
  ASSERT_EQ(utils::split(str, ' '), words);

  str = "eins,zwei,drei";
  words = {"eins", "zwei", "drei"};
  ASSERT_EQ(utils::split(str, ','), words);
}

TEST(utils, split_equal) {
  std::string str;
  std::vector< std::string > words;

  str = "abcdef";
  words = {"abc", "def"};
  ASSERT_EQ(utils::split_equal(str, 3), words);

  str = "abcdef";
  words = {"ab", "cd", "ef"};
  ASSERT_EQ(utils::split_equal(str, 2), words);

  str = "abcdef";
  words = {"abcd", "ef"};
  ASSERT_EQ(utils::split_equal(str, 4), words);

  str = "";
  words = {};
  ASSERT_EQ(utils::split_equal(str, 4), words);
}

TEST(utils, rearrange_to_2index) {
  std::vector< int > values { 1, 2, 3, 4, 5 };
  ASSERT_THROW(utils::rearrange_to_2index(values, 2, 3), std::invalid_argument);
  ASSERT_THROW(utils::rearrange_to_2index(values, 2, 2), std::invalid_argument);
  
  values = { 1, 2, 3, 4, 5, 6};
  std::vector< std::vector< int > > result {{1, 2}, {3, 4}, {5, 6}};
  ASSERT_EQ(utils::rearrange_to_2index(values, 3, 2), result);
 

  values = { 1, 2, 3, 4, 5, 6};
  result = {{1, 2, 3}, {4, 5, 6}};
  ASSERT_EQ(utils::rearrange_to_2index(values, 2, 3), result);

}

TEST(utils, remove_comment) {
  std::string line = "hallo du \% da \% huhu";
  ASSERT_EQ(utils::remove_comment(line), "hallo du ");
  line = "hallo du ";
  ASSERT_EQ(utils::remove_comment(line), "hallo du ");
}

TEST(utils, square) {
  ASSERT_FLOAT_EQ(utils::square(3.0), 9.0);
  ASSERT_FLOAT_EQ(utils::square(-4.0), 16.0);
}

TEST(utils, float_equal) {
  ASSERT_TRUE(utils::float_equal(1.2345, 1.2345));
  ASSERT_FALSE(utils::float_equal(1.2345, 1.2346));
  ASSERT_TRUE(utils::float_equal(1.0, 1.0));
}

TEST(utils, midicode_to_notename_and_vice_versa) {
  
  ASSERT_EQ(utils::midicode_to_notename(0), "c-1");
  ASSERT_EQ(utils::midicode_to_notename(21), "a0");
  ASSERT_EQ(utils::midicode_to_notename(60), "c4");
  ASSERT_EQ(utils::midicode_to_notename(61), "c#4");
  ASSERT_EQ(utils::midicode_to_notename(108), "c8");
  ASSERT_EQ(utils::midicode_to_notename(127), "g9");

  ASSERT_EQ(utils::notename_to_midicode("c-1"), 0);
  ASSERT_EQ(utils::notename_to_midicode("a0"), 21);
  ASSERT_EQ(utils::notename_to_midicode("c4"), 60);
  ASSERT_EQ(utils::notename_to_midicode("c#4"), 61);
  ASSERT_EQ(utils::notename_to_midicode("c8"), 108);
  ASSERT_EQ(utils::notename_to_midicode("g9"), 127);

  ASSERT_THROW(
    utils::notename_to_midicode("blabla"),
    std::invalid_argument
  );

}
