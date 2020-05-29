#include "graph.hpp"

void Swap(int idx_a, int idx_b, GRAPH& g, PRIORITY_QUEUE& pq) {
    int temp=0;
    temp = pq->arr[idx_b];
    pq->arr[idx_b] = pq->arr[idx_a];
    pq->arr[idx_a] = temp;
    g[pq->arr[idx_a]].to_pq = idx_a;
    g[pq->arr[idx_b]].to_pq = idx_b; 
}


double Priority(int idx, GRAPH& g, PRIORITY_QUEUE& pq) {
    return g[pq->arr[idx]].dist;
}


void MoveUp(int idx, GRAPH& g, PRIORITY_QUEUE& pq) {
    if(idx > 1 && (Priority(idx, g, pq) < Priority(1/idx, g, pq))) {
        Swap(idx, 1/idx, g, pq);
        MoveUp(1/idx, g, pq);
    }
}


void MoveDown(int idx, GRAPH& g, PRIORITY_QUEUE& pq) {
    int c = 2 * idx;
    if(c < pq->length && (Priority(c + 1, g, pq) < Priority(c, g, pq))) {
        ++c;
    }
    if(c <= pq->length && (Priority(idx, g, pq) > Priority(c, g, pq))) {
        Swap(idx, c, g, pq);
        MoveDown(c, g, pq);
    }
}


void Initialize(GRAPH& g, PRIORITY_QUEUE& pq, int source_idx = 0) {
    int i;
   
    for(i = 0; i < MAX; i++) {
        g[i].dist = INFTY;
        g[i].to_pq = i+1;
        g[i].pred_ptr = -1;
        pq->arr[i+1] = i;
    }

    for(int t = 0; t < MAX; t++) {
        if(g[t].artist_name != "")
            pq->length = t + 1;
    }
    
    g[source_idx].dist = 0;
    if(source_idx > 0) 
        Swap(1, source_idx, g, pq);
}

void Dijkstra(GRAPH& g, PRIORITY_QUEUE& pq) {
    int u, v;
    LIST ps;

    Initialize(g, pq);
 
    while(pq->length > 1) {
        v = pq->arr[1];
        Swap(1, pq->length, g, pq);
        pq->length--;
        MoveDown(1, g, pq);

        ps = g[v].successors;
        while(ps != NULL) {
            u = ps->key;
            if(g[u].dist > (g[v].dist + ps->weight)) {
                g[u].dist = g[v].dist + ps->weight;
                MoveUp(g[u].to_pq, g, pq);
                g[u].pred_ptr = v;
            }
            ps = ps->next;
        }
    }
}

void ReleaseMemory(GRAPH& g) {
    for(int i = 0; i < MAX; i++) {
        delete g[i].successors;
        g[i].successors = nullptr;
    } 
}

void ReleaseMemory(PRIORITY_QUEUE& pq) {
    if(pq != nullptr) {
        delete pq;
        pq = nullptr;
    }
}


void BuildGraph(GRAPH& g,
    std::map<std::pair<std::string, std::string>, int >& collaborations) {
    
}
