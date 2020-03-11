#include <chrono>
#include <unistd.h>
#include "../src/TimedMidiMes.h"

TEST ( TimedMidiMes, create_and_delete) {
  TimedMidiMes* timedmidimes;
  std::vector < unsigned char > message{};
  message.push_back(1);
  message.push_back(2);
  ASSERT_THROW(
    timedmidimes = new TimedMidiMes(message, 1000),
    std::invalid_argument
  );
  message.push_back(3);
  message.push_back(4);
  ASSERT_THROW(
    timedmidimes = new TimedMidiMes(message, 1000),
    std::invalid_argument
  );
  message.clear();
  message.push_back(1);
  message.push_back(2);
  message.push_back(3);
  timedmidimes = new TimedMidiMes(message, 1000);
  std::vector < unsigned char > result{1, 2, 3};
  ASSERT_EQ(timedmidimes->get_message(), result);
  delete timedmidimes;
}

TEST ( TimedMidiMes, timing) {
  TimedMidiMes* timedmidimes;
  std::vector < unsigned char > message{};
  message.push_back(1);
  message.push_back(2);
  message.push_back(3);
  timedmidimes = new TimedMidiMes(message, 100000);
  ASSERT_FALSE(timedmidimes->time_has_elapsed());
  usleep(90000);
  ASSERT_FALSE(timedmidimes->time_has_elapsed());
  usleep(20000);
  ASSERT_TRUE(timedmidimes->time_has_elapsed());
  delete timedmidimes;
}
