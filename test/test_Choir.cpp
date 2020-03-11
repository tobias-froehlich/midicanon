#include "../src/Choir.h"

TEST ( Choir, create_and_delete ) {
  Choir* choir;
  choir = new Choir();
  delete choir;
}

TEST ( Choir, read_file ) {
  Choir* choir;
  choir = new Choir();

  choir->read_file(
    "../test/testfiles/parameters3.txt"
  );

  delete choir;
}

TEST ( Choir, push ) {
  Choir* choir;
  choir = new Choir();

  std::vector < unsigned char > message{1, 2, 3};
  choir->push(message);
  delete choir;
}
