#ifndef CHOIR_H_
#define CHOIR_H_

class Choir {
  private:
    std::vector < Singer > zSingers{};
    TimedMidiQueue zTimedMidiQueue;
  public:
    Choir();
    ~Choir();
    void read_file(std::string filename);
    void push(std::vector < unsigned char > message);
    int something_to_pull();
    std::vector < unsigned char > pull();
};

#endif
