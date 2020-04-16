#include <iostream>
#include <vector>
#include <chrono>
#include "const.h"
#include "utils.h"
#include "Parameters.h"
#include "TimedMidiMes.h"
#include "TimedMidiQueue.h"
#include "Singer.h"
#include "Choir.h"

Choir::Choir() {

}

Choir::~Choir() {
  zSingers.clear();
}

void Choir::read_file(std::string filename) {
  float tempo;
  Parameters* parameters;
  parameters = new Parameters();

  zSingers.clear();
  parameters->read_file(filename);
  
  tempo = std::stof(
    parameters->get_values("tempo").front()
  );

  zSingers.push_back(Singer());
  zSingers.back().set_notes(
    parameters->get_values("cf_notes"),
    parameters->get_values("cf_notes")
  );
  if (parameters->name_occurs("cf_channel")) {
    zSingers.back().set_channel(std::stoi(parameters->get_values("cf_channel").front()) - 1);
  }
  zSingers.back().set_delay(0);
  std::cout << "Cantus Firmus at channel " << zSingers.back().get_channel() + 1 << "\n";

  std::string parametername("");
  int found = 1;
  int cp_number = 0;
  std::string str_cp("cp");
  std::string str_notes("_notes");
  std::string str_delay("_delay");
  std::string str_channel("_channel");

  while (found) {
    cp_number += 1;
    parametername = 
     str_cp +
     std::to_string(cp_number) +
     str_notes;
    if (parameters->name_occurs(parametername)) {
      zSingers.push_back(Singer());
      zSingers.back().set_notes(parameters->get_values("cf_notes"), parameters->get_values(parametername));
      parametername = 
       str_cp +
       std::to_string(cp_number) +
       str_delay;
      zSingers.back().set_delay(
        std::stof(parameters->get_values(parametername).front())/(float)tempo*60.0*1000000
      );
      parametername = 
       str_cp +
       std::to_string(cp_number) +
       str_channel;
      if (parameters->name_occurs(parametername)) {
        zSingers.back().set_channel(std::stoi(parameters->get_values(parametername).front()) - 1);
      }
      std::cout << "Singer with delay " << zSingers.back().get_delay() << " on channel " << zSingers.back().get_channel() + 1 << ".\n";
    }
    else {
      found = 0;
    }
  }

  delete parameters;
}

void Choir::push(
 std::vector < unsigned char > message) {
  for(Singer singer : zSingers) {
    zTimedMidiQueue.push(
      singer.make_timedmidimes(message)
    );
  }
}

int Choir::something_to_pull() {
  return zTimedMidiQueue.something_to_pull();
}

std::vector < unsigned char > Choir::pull() {
  return zTimedMidiQueue.pull();
}
