#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "const.h"
#include "utils.h"
#include "TimedMidiMes.h"

TimedMidiMes::TimedMidiMes(
 std::vector < unsigned char > message,
 int delay) {
  if (message.size() != 3) {
    throw std::invalid_argument(
      "TimedMidiMes must be created with a "
      "message consisting of 3 bytes. It are "
      "not exactly 3 in this case."
    );
  }
  zStartTime =
   std::chrono::high_resolution_clock::now();
  zDelay = delay;
  zMessage = message;
}

TimedMidiMes::~TimedMidiMes() {

}

int TimedMidiMes::remaining_time() {
  return
   zDelay
   -
   std::chrono::duration_cast<std::chrono::microseconds>(
     std::chrono::high_resolution_clock::now()
     -
     zStartTime
   ).count();
}

int TimedMidiMes::time_has_elapsed() {
  return (
    remaining_time() <= 0
  ); 
}

std::vector < unsigned char > TimedMidiMes
 ::get_message() {
  return zMessage;
}
