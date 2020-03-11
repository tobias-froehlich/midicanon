#ifndef TIMEDMIDIMES_H_
#define TIMEDMIDIMES_H_

class TimedMidiMes {
  private:
    std::vector < unsigned char > zMessage{};
    std::chrono::high_resolution_clock::time_point
     zStartTime;
    int zDelay; // microseconds
  public:
    TimedMidiMes(
      std::vector < unsigned char > message,
      int delay  
    );
    ~TimedMidiMes();
    int remaining_time();
    int time_has_elapsed();
    std::vector < unsigned char > get_message();
};

#endif

