#include <iostream>
#include <chrono>
#include "const.h"
#include "utils.h"
#include "TimedMidiMes.h"
#include "TimedMidiQueue.h"

TimedMidiQueue::TimedMidiQueue() {

}

TimedMidiQueue::~TimedMidiQueue() {
  zQueue.clear();
}

void TimedMidiQueue::push(
 TimedMidiMes timedmidimes) {
  int found = 0;
  if ( zQueue.size() == 0 ) {
    zQueue.push_back(timedmidimes);
  }
  else {
    int delay = timedmidimes.remaining_time();
    for ( 
      std::vector<TimedMidiMes>::iterator m = zQueue.begin();
      m != zQueue.end();
      m++
    ) {
      if ( ! found ) {
        if ( (*m).remaining_time() < delay ) {
          m = zQueue.insert(m, timedmidimes);
          found = 1;
        }
      }
    }
    if ( ! found ) {
      zQueue.push_back(timedmidimes);
    }
  }
}

int TimedMidiQueue::something_to_pull() {
  if ( zQueue.size() ) {
    return (*(zQueue.end()-1)).time_has_elapsed();
  }
  else {
    return 0;
  }
}

std::vector < unsigned char > TimedMidiQueue::pull() {
  if ( zQueue.size() ) {
    std::vector < unsigned char > output =
     zQueue.back().get_message();
    zQueue.pop_back();
    return output;
  }
  else {
    return std::vector < unsigned char > {};
  }
}
