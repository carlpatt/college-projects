/* Tests for the MyTunes Queue Lab */
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "artist.hpp"
#include <iostream>
#include <map>
#include <vector>

std::vector<std::string> split(std::string s, string delimiter){
    vector<std::string> list;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);
    return list;
}

TEST_CASE( "Create and delete hash table", "[hash_table]" ) {
  const int INITIAL_SIZE = 100;
  HASHTABLE_OA *table = new HASHTABLE_OA[INITIAL_SIZE];

  Initialize(table, INITIAL_SIZE);
  Clear(table, INITIAL_SIZE);
  delete [] table;
}

TEST_CASE( "Test hash functions", "[hashing]" ) {

  REQUIRE(HashFunc1("hello") >= 0);
  REQUIRE(HashFunc2("hello") >= 0);
  REQUIRE(HashFunc1("hello") != HashFunc2("hello"));
}

TEST_CASE( "Add artist and songs to hash table", "[hash_table]" ) {
  const int INITIAL_SIZE = 100;
  int table_size = INITIAL_SIZE;
  HASHTABLE_OA *table = new HASHTABLE_OA[INITIAL_SIZE];
  Initialize(table, INITIAL_SIZE);

  ARTIST *art = new ARTIST;
  std::set<std::string> songs1, songs2;

  art->name = "Prince";
  songs1.insert("When Doves Cry");
  songs1.insert("Purple Rain");
  songs1.insert("Diamonds and Pearls");
  art->songs = songs1;

  REQUIRE(Insert(table, table_size, art) == true);
  art = Search(table, INITIAL_SIZE, art->name);
  REQUIRE(art != nullptr);

  Clear(table, INITIAL_SIZE);
  delete [] table;
}

TEST_CASE( "Update artist and songs in hash table", "[hash_table]" ) {
  const int INITIAL_SIZE = 100;
  int table_size = INITIAL_SIZE;
  HASHTABLE_OA *table = new HASHTABLE_OA[INITIAL_SIZE];
  Initialize(table, INITIAL_SIZE);

  ARTIST *art = new ARTIST;
  std::set<std::string> songs1, songs2;

  art->name = "Prince";
  songs1.insert("When Doves Cry");
  songs1.insert("Purple Rain");
  songs1.insert("Diamonds and Pearls");
  art->songs = songs1;

  REQUIRE(Insert(table, table_size, art) == true);
  art = Search(table, INITIAL_SIZE, art->name);
  REQUIRE(art != nullptr);

  ARTIST *art2 = new ARTIST;
  art2->name = "Prince";
  songs2.insert("When Doves Cry");
  songs2.insert("Purple Rain");
  art2->songs = songs2;

  unsigned long i = HashFunc1(art2->name) % table_size;
  REQUIRE(Insert(table, table_size, art2) == true);
  REQUIRE(table[i]->art->songs.size() == 2);

  Clear(table, INITIAL_SIZE);
  delete [] table;
}

TEST_CASE( "Remove artist and songs from hash table", "[hash_table]" ) {
  const int INITIAL_SIZE = 100;
  int table_size = INITIAL_SIZE;
  HASHTABLE_OA *table = new HASHTABLE_OA[INITIAL_SIZE];
  Initialize(table, INITIAL_SIZE);

  ARTIST *art = new ARTIST;
  std::set<std::string> songs;

  art->name = "Prince";
  songs.insert("When Doves Cry");
  songs.insert("Purple Rain");
  songs.insert("Diamonds and Pearls");
  art->songs = songs;

  Insert(table, table_size, art);
  REQUIRE(Remove(table, table_size, "MC Hammer") == false);
  REQUIRE(Remove(table, table_size, art->name) == true);

  Clear(table, INITIAL_SIZE);
  delete [] table;
}

TEST_CASE( "Add many artist records", "[hash_table]" ) {
  /* sqlite> SELECT count(distinct(artist_name)) FROM songs WHERE title!="" AND title
 != " -start ID-" AND track_id NOT IN (SELECT track_id FROM songs WHERE artist_n
ame GLOB ('*[^'||char(1,45,127)||']*') OR title GLOB ('*[^'||char(1,45,127)||']*'));
4207 */

  const int INITIAL_SIZE = 6000;
  int table_size = INITIAL_SIZE;
  HASHTABLE_OA *table = new HASHTABLE_OA[INITIAL_SIZE];
  std::ifstream file("artist_song.txt");
  std::string str;
  std::map<std::string, std::set<std::string> > song_map;
  std::map<std::string, std::set<std::string> >::iterator iter;
  std::set<int> used_buckets;

  Initialize(table, INITIAL_SIZE);

  ARTIST *art = new ARTIST;
  std::set<std::string> songs;

  // associate artists and songs
  while (std::getline(file, str)) {
    std::vector<std::string> tokens = split(str, "|");
    std::string artist = tokens[0];
    std::string song = tokens[1];
    song_map[artist].insert(song);
  }

  // add artists and songs to hash table
  for (iter = song_map.begin(); iter != song_map.end(); iter++) {
    ARTIST *art = new ARTIST;
    art->name = iter->first;
    art->songs = iter->second;
    Insert(table, table_size, art);
    REQUIRE(Search(table, table_size, art->name) != nullptr);
    unsigned long hv1 = HashFunc1(art->name);
    unsigned long hv2 = HashFunc2(art->name);

    int probe_num = 0;
    unsigned long long bucket = probe_num * hv2;
    bucket += hv1;
    bucket = bucket % table_size;

    while (used_buckets.count(bucket) == 1) {
      probe_num++;
      bucket = probe_num * hv2;
      bucket += hv1;
      bucket = bucket % table_size;
    }

    REQUIRE(table[bucket]->art != NULL);
    REQUIRE(table[bucket]->art->name == art->name);
    used_buckets.insert(bucket);
  }


  Clear(table, INITIAL_SIZE);
  delete [] table;
}


TEST_CASE( "Test remove and search after collisions", "[hash_table]" ) {

  const int INITIAL_SIZE = 6000;
  int table_size = INITIAL_SIZE;
  HASHTABLE_OA *table = new HASHTABLE_OA[INITIAL_SIZE];
  std::ifstream file("artist_song.txt");
  std::string str;
  std::map<std::string, std::set<std::string> > song_map;
  std::map<std::string, std::set<std::string> >::iterator iter;
  std::set<int> used_buckets;

  Initialize(table, INITIAL_SIZE);

  ARTIST *art = new ARTIST;
  std::set<std::string> songs;

  // associate artists and songs
  while (std::getline(file, str)) {
    std::vector<std::string> tokens = split(str, "|");
    std::string artist = tokens[0];
    std::string song = tokens[1];
    song_map[artist].insert(song);
  }

  // add artists and songs to hash table
  for (iter = song_map.begin(); iter != song_map.end(); iter++) {
    ARTIST *art = new ARTIST;
    art->name = iter->first;
    art->songs = iter->second;
    Insert(table, table_size, art);
    REQUIRE(Search(table, table_size, art->name) != nullptr);
    unsigned long hv1 = HashFunc1(art->name);
    unsigned long hv2 = HashFunc2(art->name);

    int probe_num = 0;
    unsigned long long bucket = probe_num * hv2;
    bucket += hv1;
    bucket = bucket % table_size;

    while (used_buckets.count(bucket) == 1) {
      probe_num++;
      bucket = probe_num * hv2;
      bucket += hv1;
      bucket = bucket % table_size;
    }

    REQUIRE(table[bucket]->art != NULL);
    REQUIRE(table[bucket]->art->name == art->name);
    used_buckets.insert(bucket);
  }


  Clear(table, INITIAL_SIZE);
  delete [] table;
}
