/* Tests for the MyTunes Queue Lab */
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "queue.hpp"
#include <iostream>

TEST_CASE( "Create a new queue", "[queue]" ) {
  QUEUE *q = new QUEUE;

  Initialize(q);

  REQUIRE( IsEmpty(q) == true );
  Delete(q);
  //REQUIRE( q == NULL  );
}

TEST_CASE( "Add a song", "[queue]" ) {
  QUEUE *q = new QUEUE;

  Initialize(q);

  AddElement(q, "Random Song");
  REQUIRE (GetLength(q) == 1);
  Delete(q);
}

TEST_CASE( "Add multiple songs", "[queue]") {
  QUEUE *q = new QUEUE;

  Initialize(q);
  string songs[] = {"Song1", "Song2", "Song3"};
  int num_added = AddElements(q, songs, 3);

  REQUIRE (num_added == 3);
  REQUIRE (GetLength(q) == num_added);
  Delete(q);
}

TEST_CASE( "Add multiple songs until full", "[queue]") {
  QUEUE *q = new QUEUE;

  Initialize(q);
  q->rear = MAX_SIZE - 3;
  string songs[] = {"Song1", "Song2", "Song3"};
  int num_added = AddElements(q, songs, 3);

  REQUIRE (num_added == 1);
  Delete(q);
}

TEST_CASE( "FindElement returns index of element in queue", "[queue]") {
  QUEUE *q = new QUEUE;

  Initialize(q);

  string songs[] = {"Song1", "Song2", "Song3"};
  AddElements(q, songs, 3);

  int idx = FindElement(q, "Song3");

  REQUIRE(idx == 2);
  Delete(q);
}

TEST_CASE( "FindElement returns -1 for element not in queue", "[queue]") {
  QUEUE *q = new QUEUE;

  Initialize(q);

  string songs[] = {"Song1", "Song2", "Song3"};
  AddElements(q, songs, 3);

  int idx = FindElement(q, "Song4");

  REQUIRE(idx == -1);
  Delete(q);
}

TEST_CASE( "Remove an element from queue", "[queue]") {
  QUEUE *q = new QUEUE;

  Initialize(q);

  string songs[] = {"Song1", "Song2", "Song3"};
  AddElements(q, songs, 3);

  int idx = FindElement(q, "Song2");
  REQUIRE(idx == 1);
  REQUIRE(RemoveElement(q, idx) == true);
  REQUIRE(GetLength(q) == 2);
  REQUIRE(q->elements[0] == "Song1");
  REQUIRE(q->elements[1] == "Song3");
  Delete(q);
}

TEST_CASE( "Remove nothing when song not in queue", "[queue]") {
  QUEUE *q = new QUEUE;

  Initialize(q);

  REQUIRE(RemoveElement(q, 1) == false);
  Delete(q);
}

TEST_CASE( "Swap with invalid indices does not work", "[queue]") {
  QUEUE *q = new QUEUE;

  Initialize(q);

  string songs[] = {"Song1", "Song2", "Song3"};
  AddElements(q, songs, 3);

  REQUIRE(SwapElements(q, -1, 0) == false);
  REQUIRE(SwapElements(q, 0, 5) == false);
  Delete(q);
}

TEST_CASE( "Swap elements with valid indices", "[queue]") {
  QUEUE *q = new QUEUE;

  Initialize(q);

  string songs[] = {"Song1", "Song2", "Song3"};
  AddElements(q, songs, 3);

  REQUIRE(SwapElements(q, 0, 1) == true);
  REQUIRE(q->elements[0] == "Song2");
  REQUIRE(q->elements[1] == "Song1");
  Delete(q);
}
