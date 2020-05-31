#include "queue.hpp"

void Initialize(QUEUE *q) {
  q->front = 0;
  q->rear = -1;
}

void Delete(QUEUE *q) {
  delete q;
  q = NULL;
}

bool IsEmpty(QUEUE *q) {
  if (q->front > q->rear)
    return true;
  else
    return false;
}

bool IsFull(QUEUE *q) {
  if (q->rear == (MAX_SIZE - 1))
    return true;
  else
    return false;
}

int GetLength(QUEUE *q) {
  if (IsEmpty(q))
    return (q->rear + 1);
  else
    return (q->rear + 1);
}

bool AddElement(QUEUE *q, string new_element) {
  if (IsFull (q)) {
    return false;
  }
  else {
    q->elements[q->rear + 1] = new_element;
    q->rear++;
    return true;
  }
}

int AddElements(QUEUE *q, string new_elements[], int array_count) {
  int m;
  for (m = 0; m < array_count; m++) {
    AddElement (q, new_elements[m]);
    if (IsFull(q))
      return m;
  }
  return m;
}

bool RemoveElement(QUEUE *q, int r_idx) {
  if(IsEmpty(q))
    return false;
  if(r_idx > q->rear && r_idx < q->front)
    return false;
  for(r_idx; r_idx < q->rear; r_idx++){
    q->elements[r_idx] = q->elements[r_idx + 1];
  }
  q->rear--;
  return true;
}


int FindElement(QUEUE *q, string element) {
  if(IsEmpty(q))
    return -1;
  int c = q->front;
  while(c <= q->rear) {
    if(q->elements[c] == element) {
      return c;
    }
    c++;
  }
  return -1;
}

bool SwapElements(QUEUE *q, int first, int second) {
  string tmp;
  if(first < q->front || first > q->rear)
    return false;
  if(second < q->front || second > q->rear)
    return false;
  tmp = q->elements[first];
  q->elements[first] = q->elements[second];
  q->elements[second] = tmp;
  return true;
}
