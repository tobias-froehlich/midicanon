#include <unistd.h>
#include "../src/TimedMidiQueue.h"

TEST ( TimedMidiQueue, create_and_delete ) {
  TimedMidiQueue* timedmidiqueue;
  timedmidiqueue = new TimedMidiQueue();
  delete timedmidiqueue;
}

TEST ( TimedMidiQueue, push_and_pull ) {
  TimedMidiQueue* timedmidiqueue;
  TimedMidiMes timedmidimes(
    std::vector< unsigned char >{1, 2, 3},
    100000
  );
  timedmidiqueue = new TimedMidiQueue();
  ASSERT_FALSE(timedmidiqueue->something_to_pull());
  timedmidiqueue->push(timedmidimes);
  ASSERT_FALSE(timedmidiqueue->something_to_pull());
  usleep(110000);
  ASSERT_TRUE(timedmidiqueue->something_to_pull());
  std::vector < unsigned char > message{1, 2, 3};
  ASSERT_EQ(
    timedmidiqueue->pull(),
    message
  );
  message.clear();
  ASSERT_EQ(
    timedmidiqueue->pull(),
    message
  );

  std::vector < unsigned char > message1{1, 1, 1};
  std::vector < unsigned char > message2{2, 2, 2};
  std::vector < unsigned char > message3{3, 3, 3};
  std::vector < unsigned char > message4{4, 4, 4};

  TimedMidiMes timedmidimes1(message1, 100000);
  TimedMidiMes timedmidimes2(message2, 200000);
  TimedMidiMes timedmidimes3(message3, 300000);
  TimedMidiMes timedmidimes4(message4, 400000);

  timedmidiqueue->push(timedmidimes1);
  timedmidiqueue->push(timedmidimes3);
  timedmidiqueue->push(timedmidimes4);
  timedmidiqueue->push(timedmidimes2);

  ASSERT_EQ(timedmidiqueue->pull(), message1);
  ASSERT_EQ(timedmidiqueue->pull(), message2);
  ASSERT_EQ(timedmidiqueue->pull(), message3);
  ASSERT_EQ(timedmidiqueue->pull(), message4);

  delete timedmidiqueue;
}
