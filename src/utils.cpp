#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "const.h"
#include "utils.h"


std::vector< std::string > utils::split(std::string str, char delimiter) {
    std::vector< std::string > words{};
    std::string word = "";
    for (char& c : str) {
      if (c != delimiter) {
        word.append(1, c);
      }
      else if (word.size() > 0) {
        words.push_back(word);
        word = "";
      }
    }
    if (word.size() > 0) {
      words.push_back(word);
      word = "";
    }
    return words;
}

std::vector< std::string > utils::split_equal(std::string str, int size) {
  std::string word = "";
  std::vector< std::string > words{};
  int i = 0;

  for (char& c : str) {
    i += 1;  
    word.append(1, c);
    if ((i % size) == 0) {
      words.push_back(word);
      word = "";
    }
  }
  if (word.size() > 0) {
    words.push_back(word);
  }
  return words;
}

std::vector< std::vector< int > > utils::rearrange_to_2index(
  std::vector< int > values,
  int nrows,
  int ncols
  ) {

  int i = 0;
  std::vector< std::vector< int > > result{};

  if (nrows * ncols != values.size()) {
    throw std::invalid_argument("Number of elements does not fit to number of rows and cols.");
  }

  for (int irow=0; irow<nrows; irow++) {
    result.push_back(std::vector< int >{});
    for (int icol=0; icol<ncols; icol++) {
      result.back().push_back(values[i]);
      i += 1;
    }
  }
  return result;
}

std::string utils::remove_comment(std::string line) {
  int first_pos = line.find(cCommentTag);
  return line.substr(0, first_pos);
}

float utils::square(float number) {
  return number * number;
}

int utils::float_equal(float a, float b) {
  return (std::abs(a - b) < cFloatDelta);
}

unsigned char utils::notename_to_midicode(
 std::string notename) {
  for (int i = 0; i < 128; i++) {
    if (cNotenames[i] == notename) {
      return (unsigned char)i;
    }
  }
  throw std::invalid_argument("Invalid note name");
}

std::string utils::midicode_to_notename(
 unsigned char midicode) {
 return cNotenames[midicode];
}

StatusByteType utils::status_byte_type(
 std::vector< unsigned char > message) {
  if (message.size() == 3) {
    unsigned char byte = message[0];
    if ((144 <= byte) && (byte < 160)) {
      return note_on;
    }
    else if ((128 <= byte) && (byte < 144)) {
      return note_off;
    }
    else if ((176 <= byte) && (byte < 192)) {
      if (message[1] == 64) {
        if (message[2] > 64) {
          return pedal_pressed;
        }
        else {
          return pedal_released;
        }
      }
      else {
        return unknown;
      }
    }
    else {
      return unknown;
    }
  }
  else {
    return unknown;
  }
}

unsigned int utils::channel(std::vector< unsigned char > message) {
  StatusByteType type = status_byte_type(message);
  if (type == note_on) {
    return message[0] - 144;
  }
  else if (type == note_off) {
    return message[0] - 128;
  }
  else if (type == pedal_pressed) {
    return message[0] - 176;
  }
  else if (type == pedal_released) {
    return message[0] - 176;
  }
  else {
    return 0;
  }
}
