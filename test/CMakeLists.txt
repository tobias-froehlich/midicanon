find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable( Test 
  test.cpp 
  ../src/utils.cpp
  ../src/Parameters.cpp
  ../src/TimedMidiMes.cpp
  ../src/TimedMidiQueue.cpp
  ../src/Singer.cpp
  ../src/Choir.cpp
)
target_link_libraries(Test ${GTEST_LIBRARIES} pthread)
