#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "const.h"
#include "utils.h"
#include "TimedMidiMes.h"
#include "Singer.h"

Singer::Singer() {

}

Singer::~Singer() {

}

void Singer::set_notes(
 std::vector < std::string > cantus_firmis_notes,
 std::vector < std::string > my_notes) {
  if (cantus_firmis_notes.size()!=my_notes.size()) {
    throw std::invalid_argument(
      "All voices must have the same number of "
      "Notes in their scale!"
    );
  }
  zMidiCodes.clear();
  for ( int i=0; i<128; i++) {
    zMidiCodes.push_back((unsigned char)128);
  }
  std::string notename1;
  std::string notename2;
  for ( int j=0; j<my_notes.size(); j++) {
    notename1 = cantus_firmis_notes[j];
    notename2 = my_notes[j];
    zMidiCodes[utils::notename_to_midicode(notename1)] = 
     utils::notename_to_midicode(notename2);
  }
  for ( int j=0; j<128; j++ ) {
    if (zMidiCodes[j] != 128) {
      for ( int i=0; i<128; i++ ) {
        if ((zMidiCodes[i] == 128) && (j % 12 == i % 12)) {
          zMidiCodes[i] = zMidiCodes[j] + (i - j);
          if ( zMidiCodes[i] > 128 ) {
            zMidiCodes[i] = 128;
          }
        }
      }
    }
  }
}

unsigned char Singer::get_midicode(
 unsigned char index) {
  if (index < 128) {
    return zMidiCodes[index];
  }
  else {
    throw std::invalid_argument(
      "There are only 128 midi codes for the "
      "note number (0 ... 127)!"
    );
  }
}

void Singer::set_delay(int delay) {
  zDelay = delay;
}

int Singer::get_delay() {
  return zDelay;
}

TimedMidiMes Singer::make_timedmidimes(
 std::vector < unsigned char > message) {
  std::cout << message.size() << "\n";
  message[1] = get_midicode(message[1]);
  std::cout << "* " << (int)message[0] << ", " << (int)message[1] << ", " << (int)message[2] << "*\n";
  return TimedMidiMes(message, zDelay);
}
