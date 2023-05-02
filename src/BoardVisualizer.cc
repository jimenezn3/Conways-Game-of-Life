#include <curses.h>
#include <stdlib.h>
#include <iostream>

#include <BoardVisualizer.h>

/**
 *  Create the ncurses board text visualization field to use.
 */
void BoardVisualizer::Open() {
  initscr();  // ncurses: Determine terminal type, setup ncurses
  cbreak();   // ncurses: Disable line buffering
  noecho();   // ncurses: Don't echo input back to the screen

  Clear();    
}


/**
 * Destroy the ncurses board text visualization field to use.
 */
void BoardVisualizer::Close() {
  endwin();  // ncurses: Return the terminal to normal control   
}


/**
 * Draw the row-by-col matrix of characters into the text field.
 *
 * @param board  This is a 2D character array containing board elements
 * @param width  The length of the arrays representing board width
 * @param height The length of the arrays representing board height
 */
void BoardVisualizer::DrawWholeBoard(TwoDCharArray *board, int width, int height) {
  for (int row=0; row<height; row++) 
    for (int col=0; col<width; col++)
      mvaddch(row+1, col+1, board->GetCharAt(row, col, ' '));  // ncurses:  draw character
  
  refresh();  // ncurses: refresh the screen
}


/**
 * Draw a particular character in a particular location.
 *
 * @param element  The character to draw
 * @param xpos     The column position
 * @param ypos     The row position
 */
void BoardVisualizer::DrawCharAt(const char element, int xpos, int ypos) {
  // Only draw if it will actually fit on the terminal.
  if ( (xpos < GetMaxWidth()) && (ypos < GetMaxHeight()) &&
       (xpos >= 0) && (ypos >=0) ) {
    mvaddch(ypos+1, xpos+1, element);   // ncurses:  draw character
    refresh();  // ncurses: refresh the screen
  }
}



/**
 * Clear the whole text screen so that it is a blank slate.
 */
void BoardVisualizer::Clear() {
  clear();  // ncurses: Clear the screen
}


/**
 * Return the maximum height the board can be based on the
 * currently available number of lines in the terminal.
 *
 * @returns Returns an integer representing the maximum height the board 
 *          can be based on terminal height.
 */
int BoardVisualizer::GetMaxHeight() {
  return (LINES-1);  // ncurses:  LINES is the number of lines available in terminal
}


/**
 * Return the maximum width the board can be based on the
 * currently available number of columns in the terminal.
 *
 * @returns Returns an integer representing the maximum width the board 
 *          can be based on terminal width.
 */
int BoardVisualizer::GetMaxWidth()  {
  return (COLS-1);  // ncurses:  COLS is the number of lines available in terminal
}


