
Installing GTest:

sudo aptitude install libgtest-dev
cd /usr/src/googletest/
sudo cmake .
sudo cmake --build . --target install

Building midicanon:

in midicanon/build/
rm -r *
cmake ..
make

Testing:

in midicanon/build/test
./Test


