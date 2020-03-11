#ifndef TIMEDMIDIQUEUE_H_
#define TIMEDMIDIQUEUE_H_

class TimedMidiQueue {
  private:
    std::vector < TimedMidiMes > zQueue{};
  public:
    TimedMidiQueue();
    ~TimedMidiQueue();
    void push(TimedMidiMes timedmidimes);
    int something_to_pull();
    std::vector < unsigned char > pull();
};

#endif
