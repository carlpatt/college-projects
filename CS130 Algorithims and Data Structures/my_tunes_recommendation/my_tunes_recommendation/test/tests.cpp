/* Tests for the MyTunes Recommendation Lab */
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "graph.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>     /* srand, rand */
#include <ctime>
using namespace std;

TEST_CASE( "Create a new graph", "[graph]" ) {
  GRAPH g;
  LIST ps;

  // add a node to graph
  g[0].successors = new NODE;
  g[0].artist_name = "Artist0";
  g[0].dist = INFTY;
  g[0].pred_ptr = -1;
  g[0].to_pq = 1;

  // add a second node to graph

  g[1].successors = new NODE;
  g[1].artist_name = "Artist1";
  g[1].dist = INFTY;
  g[1].pred_ptr = -1;
  g[1].to_pq = 2;

  // add edge between node 0 and 1
  ps = g[0].successors;
  ps->weight = 0.5;
  ps->key = 1;
  ps->next = nullptr;

  ps = g[1].successors;
  ps->weight = 0.5;
  ps->key = 0;
  ps->next = nullptr;

  ReleaseMemory(g);


  for (int i = 0; i < MAX; i++) {
    REQUIRE(g[i].successors == nullptr);
  }

}

TEST_CASE( "Create priority queue", "[graph]" ) {
  PRIORITY_QUEUE pq = new HEAP;

  for (int i = 0; i < MAX; i++) {
    pq->arr[i+1] = i;
  }

  ReleaseMemory(pq);

  REQUIRE(pq == nullptr);
}

TEST_CASE( "Build graph from collaborations", "[graph]") {
  srand (time(NULL));
  GRAPH g;
  int num_collaborations;
  NODE* ps = nullptr;
  const int NUM_ARTISTS = 100;

  std::vector<std::string> artists(NUM_ARTISTS);
  std::map<std::pair<std::string, std::string>, int> collaborations;

  for (int i = 0; i < NUM_ARTISTS; i++) {
    artists[i] = "Artist" + std::to_string(i);
  }

  for (int i = 0; i < NUM_ARTISTS; i++) {
    for (int j = 0; j < NUM_ARTISTS; j++) {
      if (i != j) {
        // assign random number to determine if collaboration exists
        if (rand() % 10 == 1) { // 10% have collaborated
          std::pair<std::string, std::string> p = std::make_pair(artists[i], artists[j]);
          num_collaborations = rand() % 5 + 1; // number of collaborations
          collaborations[p] = num_collaborations;
          p = std::make_pair(artists[j], artists[i]);
          collaborations[p] = num_collaborations;
        }
      }
    }
  }

  BuildGraph(g, collaborations);

  for(int i = 0; i < MAX; i++) {
    ps = g[i].successors;
    while (ps != nullptr) {
      std::string adj_artist = g[ps->key].artist_name;
      std::pair<std::string, std::string> p1 = std::make_pair(g[i].artist_name, adj_artist);
      std::pair<std::string, std::string> p2 = std::make_pair(adj_artist, g[i].artist_name);
      REQUIRE(((ps->weight == 1.0/collaborations[p1])
                || (ps->weight == 1.0/collaborations[p2])));
      ps = ps->next;
    }
  }
  ReleaseMemory(g);
}

TEST_CASE( "Initialize pre-Dijkstra", "[graph]" ) {
  GRAPH g;
  PRIORITY_QUEUE pq = new HEAP;

  for (int i = 0; i < 250; i++) {
    g[i].artist_name = "Artist";
  }

  Initialize(g, pq, 4);

  REQUIRE(pq->length == 250);
  REQUIRE(pq->arr[5] == 0);
  REQUIRE(pq->arr[1] == 4);
  REQUIRE(g[4].dist == 0);

  for (int i = 0; i < 250; i++) {
    if (i != 4 && i != 0) {
      REQUIRE(pq->arr[i + 1] == i);
      REQUIRE(g[i].to_pq == i + 1);
    }
    if (i != 4) {
      REQUIRE(g[i].dist == INFTY);
    }
    REQUIRE(g[i].pred_ptr == -1);
  }

  REQUIRE(g[0].to_pq == 5);
  REQUIRE(g[4].to_pq == 1);

  ReleaseMemory(pq);
  ReleaseMemory(g);
}


TEST_CASE( "Run dijkstra", "[graph]") {
  srand (time(NULL));
  GRAPH g;
  PRIORITY_QUEUE pq = new HEAP;
  int num_collaborations;
  NODE* ps = nullptr;
  const int NUM_ARTISTS = 100;
  int pred_idx;
  std::pair<std::string, std::string> p;

  std::vector<std::string> artists(NUM_ARTISTS);
  std::map<std::pair<std::string, std::string>, int> collaborations;

  for (int i = 0; i < NUM_ARTISTS; i++) {
    artists[i] = "Artist" + std::to_string(i);
  }

  for (int i = 0; i < NUM_ARTISTS; i++) {
    for (int j = 0; j < NUM_ARTISTS; j++) {
      if (i != j) {
        // assign random number to determine if collaboration exists
        if (rand() % 10 == 1) { // 10% have collaborated
          p = std::make_pair(artists[i], artists[j]);
          num_collaborations = rand() % 5 + 1; // number of collaborations
          collaborations[p] = num_collaborations;
          p = std::make_pair(artists[j], artists[i]);
          collaborations[p] = num_collaborations;
        }
      }
    }
  }

  BuildGraph(g, collaborations);

  Dijkstra(g, pq);


  for (int i = 0; i < MAX; i++) {
    if (g[i].artist_name == "")
      break;

    int succ_idx = i;
    pred_idx = g[i].pred_ptr;
    if (g[i].dist != INFTY) {
      while (pred_idx != -1) {
        p = std::make_pair(g[succ_idx].artist_name, g[pred_idx].artist_name);
        REQUIRE(collaborations.find(p) != collaborations.end());
        succ_idx = pred_idx;
        pred_idx = g[pred_idx].pred_ptr;
      }
    }
  }

  ReleaseMemory(pq);
  ReleaseMemory(g);
}
