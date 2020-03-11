#include <iostream>
#include <chrono>
#include <gtest/gtest.h>
#include "test_utils.cpp"
#include "test_Parameters.cpp"
#include "test_TimedMidiMes.cpp"
#include "test_TimedMidiQueue.cpp"
#include "test_Singer.cpp"
#include "test_Choir.cpp"



int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
