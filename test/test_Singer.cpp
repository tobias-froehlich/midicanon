#include "../src/TimedMidiMes.h"
#include "../src/Singer.h"

TEST ( Singer, create_and_delete ) {
  Singer* singer;
  singer = new Singer();
  delete singer;
}

TEST ( Singer, set_notes ) {
  Singer * singer;
  singer = new Singer();
  ASSERT_THROW(
    singer->set_notes({"c4", "d4", "e4"}, {"c4", "d4"}),
    std::invalid_argument
  );
  singer->set_notes({"c4", "d4"}, {"d4", "e4"});

  ASSERT_THROW(
    singer->get_midicode(128),
    std::invalid_argument
  );
  ASSERT_EQ(singer->get_midicode(60), 62);
  ASSERT_EQ(singer->get_midicode(62), 64);
  ASSERT_EQ(singer->get_midicode(61), 128);
  ASSERT_EQ(singer->get_midicode(60-12), 62-12);
  ASSERT_EQ(singer->get_midicode(60+12), 62+12);

  delete singer;
}

TEST ( Singer, set_delay_make_timedmidimes ) {
  Singer* singer;
  singer = new Singer();
  singer->set_delay(10000);
  singer->set_notes(
    std::vector< std::string > {"c4", "d4", "e4"},
    std::vector< std::string > {"d4", "e4", "f4"}
  );
  ASSERT_EQ(singer->get_delay(), 10000);
  std::vector < unsigned char > message{1, 2, 3};
  TimedMidiMes timedmidimes = singer->make_timedmidimes(message);
  message[1] = 4;
  ASSERT_EQ(
    timedmidimes.get_message(),
    message
  );
  ASSERT_FALSE(timedmidimes.time_has_elapsed());
  usleep(11000);
  ASSERT_TRUE(timedmidimes.time_has_elapsed());

  delete singer;
}
