#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <limits>
using namespace std;

// global constants;
const int MAX = 1000; // problem specific
const double INFTY = std::numeric_limits<double>::infinity();

/* Singly-linked list structure used for adjacency lists */
typedef struct NODE *LIST;
struct NODE {
    int key; // index of node in GRAPH
    double weight; // edge weight from source node
    LIST next = nullptr; // next pointer in predecessor list
};

/* A node in the collaboration graph */

struct GRAPH_NODE {
    std::string artist_name = "";
    double dist;
    LIST successors = nullptr; //adjacency list
    int pred_ptr; // points to previous node in shortest path (index in G)
    int to_pq; // points at corresponding priority queue node
};

/* An array of nodes representing the full graph */
typedef struct GRAPH_NODE GRAPH[MAX];

/* A heap structure used to maintain a min-heap for Dijkstra's algorithm */
struct HEAP{
    int arr[MAX + 1]; // values represent node index in graph
    int length = MAX;
};

/* A pointer to a heap structure used for min-heap */
typedef struct HEAP* PRIORITY_QUEUE;

/* Function: Swap
 * ------------------
 * Swaps the values at idx_a and idx_b in the PRIORITY_QUEUE. Makes a
 * corresponding switch to the to_pq members in the GRAPH nodes whose
 * index in the GRAPH is stored at idx_a and idx_b in the PRIORITY_QUEUE.
 *
 * @param idx_a int index of one value to swap in the priority queue
 * @param idx_b int index of other value to swap in the priority queue
 * @param g GRAPH& corresponding nodes are updated here to reflect swap in
 * PRIORITY_QUEUE
 * @param pq PRIORITY_QUEUE& provides arr member where swap occurs
 * @return no value
 */
void Swap(int idx_a, int idx_b, GRAPH& g, PRIORITY_QUEUE& pq);

/* Function: Priority
 * ------------------
 * Returns the priority (shortest distance from a source node) for the
 * GRAPH node located at index idx.
 *
 * @param idx int index of graph node in the priority queue
 * @param g GRAPH& provides distance of graph nodes from source
 * @param pq PRIORITY_QUEUE& contains positions of graph nodes in min-heap
 * @return no value
 */
double Priority(int idx, GRAPH& g, PRIORITY_QUEUE& pq);

/* Function: MoveUp
 * ------------------
 * Moves the PRIORITY_QUEUE element at index idx up the min-heap
 * to restore the min-heap property by swapping with the node's
 * parent.
 *
 * @param idx int index of the value to swap to restore min-heap property
 * @param g GRAPH& provides distance of graph nodes from source
 * @param pq PRIORITY_QUEUE& updated to restore PRIORITY_QUEUE to min-heap
 * @return no value
 */
void MoveUp(int idx, GRAPH& g, PRIORITY_QUEUE& pq);

/* Function: MoveDown
 * ------------------
 * Moves the PRIORITY_QUEUE element at index idx down the min-heap
 * to restore the min-heap property by swapping with the node's
 * children.
 *
 * @param idx int index of the value to swap to restore min-heap property
 * @param g GRAPH& provides distance of graph nodes from source
 * @param pq PRIORITY_QUEUE& updated to restore PRIORITY_QUEUE to min-heap
 * @return no value
 */
void MoveDown(int idx, GRAPH& g, PRIORITY_QUEUE& pq);

/* Function: Initialize
 * -------------------------
 * Initializes the graph and priority queue prior to running the Dijkstra
 * algorithm. This function performs the following operations:
 *
 * 1) Sets the distance member of each node in the GRAPH to infinity.
 * 2) Sets the to_pq member to 1 greater than the node's index in the GRAPH.
 * 3) Sets the pred_ptr member of every graph node to -1.
 * 4) Sets the length member of the PRIORITY_QUEUE to the number of nodes in
 * the GRAPH (a node will be in the graph when the artist_name member is
 * assigned a name)
 * 5) Sets the value of each element in the arr member of the PRIORITY_QUEUE
 * to that element's index in the minus 1. Element at index 0 is not assigned
 * a value.
 * 6) Sets the dist member of the source node (source_idx) to 0.
 * 7) Swaps the value at index 1 of the priority with the index of the source
 * node if the source node is not at index 0 in the GRAPH.
 *
 * @param g GRAPH& the graph to be initialized
 * @param pq PRIORITY_QUEUE& the priority queue to be initialized
 * @param source_idx int the index of the source node for Dijkstra
 * @return no value
 */

void Initialize(GRAPH& g, PRIORITY_QUEUE& pq, int source_idx);

/* Function: Dijkstra
 * -----------------------
 * Deletes the memory allocated for a GRAPH. This requires deleting
 * all of the memory used to create the NODEs in the adjacency lists
 * in the graph. Each successors pointer in the graph will be set to
 * the nullptr after this function terminates.
 *
 * @param g GRAPH& the GRAPH used to store the adjacency representation of
 * the nodes in the GRAPH.
 * @param pq PRIORITY_QUEUE& the PRIORITY_QUEUE used for choosing the next
 * node to visit.
 * @return no value
 */
void Dijkstra(GRAPH& g, PRIORITY_QUEUE& pq);

/* Function: ReleaseMemory
 * -----------------------
 * Deletes the memory allocated for a GRAPH. This requires deleting
 * all of the memory used to create the NODEs in the adjacency lists
 * in the graph. Each successors pointer in the graph will be set to
 * the nullptr after this function terminates.
 *
 * @param g GRAPH& the GRAPH struct whose memory will be deleted
 * @return no value
 */
void ReleaseMemory(GRAPH& g);

/* Function: ReleaseMemory
 * -----------------------
 * Deletes the memory allocated for a PRIORITY_QUEUE. The memory should only
 * be deleted if the PRIORITY_QUEUE points to a HEAP structure. In this case,
 * the memory for the HEAP struct which the PRIORITY_QUEUE points to
 * will be deleted. The PRIORITY_QUEUE parameter will be set to the
 * nullptr.
 *
 * @param pq PRIORITY_QUEUE& the HEAP pointer used to delete memory
 * @return no value
 */
void ReleaseMemory(PRIORITY_QUEUE& pq);

/* Function: BuildGraph
 * --------------------
 * Builds adjacency list representation of a graph for the artist collaboration
 * graph. The second paramter of the function is an STL map. This map uses
 * an STL pair of two strings as a key and an int as a value. Each pair
 * represents a collaboration between two artists. The int value represents
 * the number of collaborations between the artists. Each collaboration
 * between artists "Artist1" and "Artist2" will be represented twice in the
 * collaborations map. Once with "Artist1" in the first position and "Artist2"
 * in the second position of the pair and once with "Artist2" in the first
 * position and "Artist1" in the second position. The number of collaborations
 * will be the same for both entries in the map.
 *
 * Each artist will be assigned an index in the graph as collaborations are
 * processed. The next available index will be used and assigned to an
 * artist that has not yet been added to the graph. The index in the graph
 * where the artist is added will be assigned the name of the artist. The index
 * will be used as the key data member whenever this artist's NODE is present
 * in the adjacency list of another graph node.
 *
 * Each collaboration represents a weighted edge in the adjacency list of the
 * graph node corresponding to the first artist in the pair. A new NODE
 * will be added to the adjacency list for the graph node by allocating
 * memory for the new NODE and adding it to the end of the adjacency list of
 * the adjacent node in the graph.  The weight data memember is calculated as
 * the inverse of the number of collaborations between the two artists
 * (1.0/num_collaborations). Because this is an undirected graph, this weight
 * will be represented twice in the graph (in two difference adjacency lists).
 *
 * @param g GRAPH& the graph that will be constructed using adjacency lists
 * @param collaborations std::map the map of artist collaborations
 * @return no value
 */
void BuildGraph(GRAPH& g,
      std::map<std::pair<std::string, std::string>, int >& collaborations);


#endif
