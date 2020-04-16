#ifndef UTILS_H_
#define UTILS_H_

namespace utils {
  std::vector< std::string > split(std::string str, char delimiter);
    // Splits str into words, seperated by delimiter. Several delimeters
    // occuring in a group are treated as one. Delimiters at beginning or end
    // are ignored.
  std::vector< std::string > split_equal(std::string str, int size);
    // Splits str into words of length size. If length of str is not
    // a multiple of size, then the last word is shorter.
  std::vector< std::vector< int > > rearrange_to_2index(
    std::vector< int > values,
    int nrows,
    int ncols
  ); // Fills the 1-index array "values" to a 2-index array.
     // The length of the 1-index array must be nrows x ncols.
     // Otherwise invalid_argument.
  std::string remove_comment(std::string line);
      // removes everything from the string from the first comment tag.
      // Which character this is, is specified in const.h (zCommentTag).
  float square(float number);
      // Calculates the square of a float. Just to avoid calculating
      // the number twice like (some caclulation) * (same calculation).
  int float_equal(float a, float b);
      // Tests whether a and b differ less than cFloatDelta (in const.h).

  unsigned char notename_to_midicode(std::string notename);
  
  std::string midicode_to_notename(unsigned char midicode);

  StatusByteType status_byte_type(
   std::vector< unsigned char > message);

  unsigned int channel(std::vector< unsigned char > message);


}

#endif
