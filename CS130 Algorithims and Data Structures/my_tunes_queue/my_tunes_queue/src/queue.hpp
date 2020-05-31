#include <string>
using namespace std;

#define MAX_SIZE 2000

struct QUEUE {
    string elements[MAX_SIZE];
    int front;
    int rear;
};

/* Function: Initialize
 * --------
 * This function accepts a previously allocated QUEUE* as a
 * function parameter and initializes the queue to be empty
 * by setting the queue's front index member to 0 and the
 * queue's rear index member to -1.
 */
void Initialize(QUEUE *q);

/* Function: Delete
 * --------
 * This function accepts a previously allocated QUEUE* as a function
 * parameter and deletes the memory for the queue and assigns NULL to
 * the QUEUE* parameter.
 */
void Delete(QUEUE *q);

/* Function: IsEmpty
 * ---------
 * This function accepts a QUEUE* parameter as a function parameter
 * and returns true if the queue is empty and false otherwise. A queue
 * is empty when the front index of the queue follows the rear index of
 * the queue in a circular sense. For example, if front is set to 23 and
 * rear is set to 22, the queue is empty. Likewise, if front is set to 0
 * and rear is set to MAX_SIZE - 1, the queue is also empty because
 * 0 follows MAX_SIZE - 1 in the circular sense.
 */
bool IsEmpty(QUEUE *q);

/* Function: IsFull
 * ---------
 * This function accepts a QUEUE* function parameter and returns true
 * if the queue is full and \textit{false} otherwise. A queue is full
 * if it contains MAX_SIZE - 1 elements.
 */
bool IsFull(QUEUE *q);

/* Function: GetLength
 * ---------
 * This function accepts a QUEUE* function parameter and returns
 * the number of elements currently contained in the queue.
 */
int GetLength(QUEUE *q);

/* Function: AddElement
 * ---------
 * This function accepts a QUEUE* function parameter and an string
 * function parameter new_element. new_element is added to the end
 * of the queue if it is not full. The function returns true if
 * new_element successfully added and false otherwise.
 */
bool AddElement(QUEUE *q, string new_element);

/* Function: AddElements
 * ---------
 * This function accepts a QUEUE*, an array of strings (elements), and
 * the length of the array of strings (array_count) as function parameters.
 * The elements are added to the end of the queue. If the queue does not
 * have the capacity to hold all of the elements, elements are
 * added to the queue until it is full. The function returns the number
 * of elements from the new_elements array that were added to the queue.
 * Therefore, if new_elements contains m elements and all elements are
 * added to the array, m is returned by this function.
 */
int AddElements(QUEUE *q, string new_elements[], int array_count);

/* Function: FindElement
 * ---------
 * This function accepts a QUEUE* and a string, element, as function
 * parameters. It returns the index of element if element is in the
 * queue and returns −1 if element is not in the queue. This function
 * must implement an algorithm that has an asymptotic runtime of
 * O(log n).
 */
int FindElement(QUEUE *q, string element);

/* Function: RemoveElement
 * ---------
 * This function accepts a QUEUE* and an int, r idx, as function parameters.
 * If r_idx references a valid index in the queue, the element located at
 * r_idx is removed from the queue, any elements in the queue after the
 * removed element are moved 1 index closer to the front of the queue, the
 * rear index is decreased by 1, and the function returns true. If element
 * is not in the queue, the function returns false and no changes are made
 * to the queue.
 */
bool RemoveElement(QUEUE *q, int r_idx);

/* Function: SwapElements
 * ---------
 * This function accepts a QUEUE*, an int (first), and an int (second) as
 * function parameters. If both indices are between front and rear, the
 * position of the elements are swapped so that after this function
 * executes the element previously at second will be located at first and
 * the element previously at first will be located at second. If the swap
 * is successfully performed, the function returns true, otherwise, the
 * function returns false.
 */
bool SwapElements(QUEUE *q, int first, int second);
