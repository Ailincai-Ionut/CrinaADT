#include "Matrix.h"
#include <exception>
using namespace std;

// Complexity O(1)
Matrix::Matrix(int nrLines, int nrCols) {

  head = new Node;
  head->next = nullptr;

  nr_lines = nrLines;
  nr_col = nrCols;
}
// Best case: thetha(1) when the Matrix is full of NULL_TELEM
// Worst case: thetha(nr_lines*nr_col) when the Matrix is full of distinct
// elements
// Complexity O(nr_lines*nr_col)
Matrix::~Matrix() {
  Node *curr = head->next;
  Node *prev = head;
  while (curr != nullptr) {
    delete prev;
    prev = curr;
    curr = curr->next;
  }
	delete prev;
}

// Complexity O(1)
int Matrix::nrLines() const { return nr_lines; }

// Complexity O(1)
int Matrix::nrColumns() const { return nr_col; }

// Best case thetha(1) when the i and j are invalid
//  Worst case thetha(number of non-zero elements) when the element at (i,j) is
//  NULL_TELEM
// Complexity O(number of non-zero elements)
TElem Matrix::element(int i, int j) const {

  if (i < 0 || i >= nr_lines || j < 0 || j >= nr_col)
    throw exception();

  Node *curr = head->next;
  while (curr != nullptr) {
    if (curr->line == i && curr->column == j)
      return curr->value;
    curr = curr->next;
  }
  return NULL_TELEM;
}

// Best case thetha(1) when the i and j are invalid
// Worst case thetha(number of non-zero elements) when the given element needs
// to be added last
// Complexity O(number of non-zero elements)

TElem Matrix::modify(int i, int j, TElem e) {

  if (i < 0 || i >= nr_lines || j < 0 || j >= nr_col)
    throw exception();

  Node *curr = head->next;
  Node *prev = head;
  TElem old_value;

  while (curr != nullptr) {
    old_value = curr->value;

    if (curr->line == i) {
      if (curr->column == j) {
        // we found the value
        if (e == NULL_TELEM) {
          // we need to delete it from the list
          prev->next = curr->next;
          delete curr;
          return old_value;
        } else {
          curr->value = e;
          return old_value;
        }
      } else if (curr->column > j)
        break;
      // we stop because we found the correct pos for inserting
    } else if (curr->line > i)
      break;
    // we stop because we found the correct pos for inserting

    prev = curr;
    curr = curr->next;
  }

  Node *new_node = new Node;
  new_node->line = i;
  new_node->column = j;
  new_node->value = e;
  prev->next = new_node;

  if (curr == nullptr) {
    new_node->next = nullptr;
  } else {
    new_node->next = curr;
  }
  return NULL_TELEM;
}
