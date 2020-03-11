#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <unistd.h>
#include <Stk.h>
#include <RtMidi.h>
#include "const.h"
#include "utils.h"
#include "Parameters.h"
#include "TimedMidiMes.h"
#include "TimedMidiQueue.h"
#include "Singer.h"
#include "Choir.h"

int main(int argc, char** argv) {
  RtMidiIn* midiin = 0;
  RtMidiOut* midiout = 0;

  try {
    midiin = new RtMidiIn(RtMidi::UNSPECIFIED, "midicanon in");
  } catch (RtMidiError &error) {
    error.printMessage();
    exit( EXIT_FAILURE );
  }

  try {
    midiout = new RtMidiOut(RtMidi::UNSPECIFIED, "midicanon out");
  } catch (RtMidiError &error) {
    error.printMessage();
    exit( EXIT_FAILURE );
  }

  midiin->openVirtualPort();
  midiin->ignoreTypes(true, true, true);
  midiout->openVirtualPort();

  Choir* choir;
  choir = new Choir();
  choir->read_file("parameters.txt");

  int running = 1;
  double stamp;
  std::vector<unsigned char> message;
  int nBytes;
  while (running) {
    usleep(1000);
    message.clear();
    stamp = midiin->getMessage(&message);
    nBytes = message.size();
    if (nBytes >= 3) {
      std::cout << " [";
      for (unsigned char byte : message) {
        std::cout << (int)byte << ", ";
      }
      std::cout << "]->\n";
    
      if ((message[1] == cNoteForExit) && (message[2] == 0)) {
        running = 0;
        for (int i=0; i<128; i++) {
          message.clear();
          message.push_back(128);
          message.push_back((unsigned char)i);
          std::cout << i << " ";
          message.push_back(0);
          midiout->sendMessage(&message);
          usleep(1000);
        };
      }
      choir->push(message);
    }
    if (choir->something_to_pull()) {
      message = choir->pull();
      if (message.size() > 0) {
        std::cout << "             ->[";
        for (unsigned char byte : message) {
          std::cout << (int)byte << ", ";
        }
        std::cout << "]\n";          
        midiout->sendMessage(&message);
      }
    }
    usleep(10000);
  }

  midiout->closePort();
  midiin->closePort();

  delete midiout;
  delete midiin;
  delete choir;
}
