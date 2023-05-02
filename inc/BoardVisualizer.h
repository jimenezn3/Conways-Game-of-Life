#ifndef BOARDVISUALIZER_H_
#define BOARDVISUALIZER_H_

#include<TwoDCharArray.h>

/**
 * Class definition for the simple "board visualizer" we will use for
 * course assignments.  This allows the user to display a 2D array
 * of characters or update a specific position on the board.  It 
 * is just a simple wrapper around the ncurses library, so you will
 * have to link to ncurses on the command line (-lcurses).  You are
 * responsible for managing the "board" state externally, and I've
 * provided a convenience class for this (Two2CharArray).
 */
class BoardVisualizer {
public:
  // Board setup/shutdown operations
  void Open();
  void Close();

  // Board writing operations
  void DrawWholeBoard(TwoDCharArray *board, int width, int height);
  void DrawCharAt(const char element, int xpos, int ypos);
  void Clear();

  // Accessor methods
  int GetMaxHeight();
  int GetMaxWidth();
};

#endif //BOARDVISUALIZER_H_
