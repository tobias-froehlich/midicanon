#ifndef SINGER_H_
#define SINGER_H_

class Singer {
  private:
    std::vector < unsigned char > zMidiCodes{};
    int zDelay = 0;
  public:
    Singer();
    ~Singer();
    void set_notes(
     std::vector < std::string > cantus_firmis_notes,
     std::vector < std::string > my_notes);
    unsigned char get_midicode(
     unsigned char index);
    void set_delay(int delay);
    int get_delay();
    TimedMidiMes make_timedmidimes(
     std::vector < unsigned char > message);
};

#endif
