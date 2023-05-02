#include <algorithm>
#include <iostream>
#include <ConwayLife.h>
#include <ctype.h>


// RPW:  Move the initialize into a constructor for project 3.
//       This is slightly more complicated than it sounds because
//       We'll need to treat the TwoDCharArrays dynamically now.
//       You'll also want to make sure you have a proper destructor.

/**
 *  Setup the visualizer and the fields for Conway's life.
 *  All cells are initially set to dead.
 */

//Constructor
ConwayLife::ConwayLife(const int width, const int height) {

  maxWidth_ = width;
  maxHeight_ = height;

  visualizer_.Open();

  mainlifefield_ = new TwoDCharArray(GetMaxWidth(), GetMaxHeight(), DEAD_CELL);
  nextlifefield_ = new TwoDCharArray(GetMaxWidth(), GetMaxHeight(), DEAD_CELL);


}

//Destructor
ConwayLife::~ConwayLife() {
  delete mainlifefield_;
  delete nextlifefield_;
}

/*
void ConwayLife::Initialize(const int width, const int height) {
  // Set the width and height of the simulation
  maxWidth_ = width;
  maxHeight_ = height;

  // Open the visualizer
  visualizer_.Open();

  // RPW:  Actually, this time we will move all of this up into a
  //       constructor for TwoDCharArray, as well.
  
  // Initialize the main board and the board we are using to update
  mainlifefield_.Initialize(GetMaxWidth(), GetMaxHeight(), DEAD_CELL);
  nextlifefield_.Initialize(GetMaxWidth(), GetMaxHeight(), DEAD_CELL);
}
*/

/**
 * Seed the initial board state from a file.  Interpret alphabetic
 * characters as LIVE_CELL, otherwise assume the cell is a DEAD_CELL.
 *
 * @param filename The name of a file to read as a seed.
 */
void ConwayLife::ReadFromFile(const string filename) {
  // Create a temporary array to read the file into
  TwoDCharArray tempArray(GetMaxWidth(), GetMaxHeight(), DEAD_CELL);
  //tempArray.Initialize(GetMaxWidth(), GetMaxHeight(), DEAD_CELL);
  tempArray.ReadFromFile(filename);

  // Sping through the temporary array, but only set
  // "live" cells in the real array of the character as
  // an alphabetic character.
  for (int row=0; row<GetMaxHeight(); row++)
    for (int col=0; col<GetMaxWidth(); col++) {
      if ( isalpha(tempArray.GetCharAt(row, col, DEAD_CELL)) )
     	  mainlifefield_->SetCharAt(row, col, LIVE_CELL);
    } // end for column loop
}


/**
 * This routine passes on the "close" to the visualizer, which
 * resolves the ncurses screen writing.  If you don't do this,
 * the terminal might be left in a funny state.
 */
void ConwayLife::Close() {
  visualizer_.Close();
}


/**
 *  Apply the rules of Life for a single step:
 *    1) A live cell with fewer than two neighbors or more than three will die;
 *    2) A dead cell with precisely three neighbers will come to life;
 *    3) Otherwise, the cell dies.
 */
void ConwayLife::LifeStepUpdate(const Rule *rule) {
  for (int row=0; row<GetMaxHeight(); row++)
    for (int col=0; col<GetMaxWidth(); col++) {
      // Use the rule to get the next state
      char next = rule->GetNextCellState(mainlifefield_->GetCharAt(row,col,DEAD_CELL),
                                         CountLiveNeighbors(row,col));

      // Set the cell's next state in the next life field
      nextlifefield_->SetCharAt(row, col, next);
    } // end for jdx
}



/**
 *  Copy the "next" field that we've been updating to
 *  back to the main life field.
 */
void ConwayLife::SwitchLifeFields() {
  // Make a deep copye of the next field to the main field, clear the next field
  mainlifefield_->DeepCopy(nextlifefield_);
}



/**
 *  Draw the entire main life field to the screen in ASCII.
 */
void ConwayLife::ViewLifeField() {
  visualizer_.DrawWholeBoard(mainlifefield_, GetMaxWidth(), GetMaxHeight());
}


/**
 *  Return the height of the life field, which is the smaller of
 *  the hard-coded LIFEFIELD_SPAN and the height of the text display.
 *
 *  @return The maximum height of the Life CA field
 */
int ConwayLife::GetMaxHeight() {
  return (maxHeight_);
}


/**
 *  Return the width of the life field, which is the smaller of
 *  the hard-coded LIFEFIELD_SPAN and the width of the text display.
 *
 *  @return The maximum width of the Life CA field
 */
int ConwayLife::GetMaxWidth() {
  return (maxWidth_);
}


/**
 *  Spin through the 8 Moore neighbors and count how many are
 *  alive.  Ignore the current position.  This is tauroidal,
 *  meaning it will wrap around the sides of the field.
 *
 * @param row The row position of the cell being considered
 * @param col The column position of the cell being considered
 * @return The number of live immediate neighbors (between 0 and 8)
 */
int ConwayLife::CountLiveNeighbors(const int row, const int col) {
  int rx, ry;
  int liveCellCount = 0;

  // Loop through all the neighbers +/- 1 in radius
  for (int idx=-1; idx<=1; idx++)
    for (int jdx=-1; jdx<=1; jdx++)
      if ( (idx != 0) || (jdx != 0) ) {  // Ignore the current row-by-col
        rx = col+idx;
        ry = row+jdx;

        // Wrap around edges of the width
        if (rx >= GetMaxWidth()) rx = (rx % GetMaxWidth());
        if (rx < 0)              rx = GetMaxWidth() + rx;

        // Wrap around edges of the height
        if (ry >= GetMaxHeight()) ry = (ry % GetMaxHeight());
        if (ry < 0)               ry = GetMaxHeight() + ry;

        // Increment the counter if the cell is alive (recall: row-by-col)
        if (mainlifefield_->GetCharAt(ry, rx, DEAD_CELL) == LIVE_CELL)
          liveCellCount++;
      } // end if not on this exact cell

  return liveCellCount;
}
