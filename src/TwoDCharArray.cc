#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <TwoDCharArray.h>

// RPW:  Move the initialize functionality up into a constructor.
//       Make sure you have a proper destructor to deallocate many
//       space you are dynamically allocating.

/**
 * Clear the 2D array by setting all positions to
 * the emtpy char.
 *
 * @param maxWidth The maximum width of the 2D character matrix
 * @param maxHeight The maximum height of the 2D character matrix
 * @param emptyChar  The character to use for clearing the board
 */

//Constructor
TwoDCharArray::TwoDCharArray(int maxWidth, int maxHeight, char emptyChar){

  maxWidth_ = maxWidth;
  maxHeight_ = maxHeight;

  if (maxWidth_ <  0)
    maxWidth_ = 0;

  if (maxHeight_ <  0)
    maxHeight_ = 0;

  arraySize_ = GetMaxWidth() * GetMaxHeight();
  charMatrix_ = new char[arraySize_]; //DEALLOCATE THIS IN DESTRUCTOR

  for (int idx=0; idx<GetArraySize(); idx++)
    charMatrix_[idx] = '\0';

  for (int row=0; row<GetMaxHeight(); row++)
    for (int col=0; col<GetMaxWidth(); col++)
      SetCharAt(row, col, emptyChar);

}

//Destructor
TwoDCharArray::~TwoDCharArray() {
  delete [] charMatrix_;
  charMatrix_ = NULL;
}

/*
void TwoDCharArray::Initialize(int maxWidth, int maxHeight, char emptyChar) {
  // Set internal member variables
  maxWidth_ = maxWidth;
  maxHeight_ = maxHeight;

  // Check that member variables aren't too big or small
  if (maxWidth_ <  0)
    maxWidth_ = 0;

  if (maxHeight_ <  0)
    maxHeight_ = 0;

  // Allocate the array and save its size
  arraySize_ = GetMaxWidth() * GetMaxHeight();
  charMatrix_ = new char[arraySize_]; // <-- You are allocating space here ...
                                      //     Somewhere, it must be deallocated

  // Set the whole character string to \0 (end str)
  for (int idx=0; idx<GetArraySize(); idx++)
    charMatrix_[idx] = '\0';

  // Set the whole string to the emptyChar
  for (int row=0; row<GetMaxHeight(); row++)
    for (int col=0; col<GetMaxWidth(); col++)
      SetCharAt(row, col, emptyChar);
}
*/

/**
 * This routine reads the contents of a text file into the
 * 2D array.  It is simple and very brittle, so be careful.
 *
 * @param filename The filename of the file to be read into the character matrix
 */
void TwoDCharArray::ReadFromFile(const string filename) {
  fstream initializeFile;
  string line;

  initializeFile.open(filename, std::ios::in);
  if (initializeFile.is_open()) {
    int row = 0;
    while (std::getline(initializeFile, line)) {

      // Add all contents of the string to the char array
      for (int col=0; col<line.length(); col++)
	      SetCharAt(row, col, line[col]);

      row++;  // Increment to the next row
    } // end while not EOF loop

    initializeFile.close();
  } // end check if file open
}


/**
 * Copy the entire contents of another array into this one.
 *
 * @param otherArray The TwoDCharArray to use as source for the deep copy
 */
void TwoDCharArray::DeepCopy(TwoDCharArray *otherArray) {
  maxWidth_ = otherArray->maxWidth_;
  maxHeight_ = otherArray->maxHeight_;
  arraySize_ = otherArray->arraySize_;

  // Set the whole character string to \0 (end str)
  for (int idx=0; idx<GetArraySize(); idx++)
    charMatrix_[idx] = otherArray->charMatrix_[idx];
}



/**
 * If the row-by-col address is correct, return the value of that
 * position in the character array.  The array is one big string,
 * so thi routine calculates the 2D address.
 *
 * @param row    The row to set the character
 * @param col    The col to set the character
 * @return The character at the requested position
 */
char TwoDCharArray::GetCharAt(int row, int col, char defaultChar) {
  char returnChar = defaultChar;

  // row-0 | <--- max width ---> |
  // row-1 |    col-?            |
  //   So the position is the row*width + col
  if ( (row >=0) && (row < GetMaxHeight()) &&
       (col >=0) && (col < GetMaxWidth()) )
    returnChar = charMatrix_[row*GetMaxWidth() + col];

  return(returnChar);
}


/**
 * If the row-by-col address is correct, set the value of that
 * position in the character array.  The array is one big string,
 * so thi routine calculates the 2D address.
 *
 * @param row    The row to set the character
 * @param col    The col to set the character
 * @param myChar The character to set
 */
void TwoDCharArray::SetCharAt(int row, int col, char myChar) {
  // row-0 | <--- max width ---> |
  // row-1 |    col-?            |
  //   So the position is the row*width + col
  if ( (row >=0) && (row < GetMaxHeight()) &&
       (col >=0) && (col < GetMaxWidth()) )
    charMatrix_[row*GetMaxWidth() + col] = myChar;
}


/**
 * Return the maximum height the 2D array.
 *
 * @return Returns an integer representing the maximum height the board can be based on terminal height.
 */
int TwoDCharArray::GetMaxHeight() {
  return (maxHeight_);
}


/**
 * Return the maximum height the 2D array.
 *
 * @return Returns an integer representing the maximum width the board can be based on terminal height.
 */
int TwoDCharArray::GetMaxWidth() {
  return (maxWidth_);
}


/**
 * Return the size of the storage array.
 *
 * @return Returns an integer representing the size of the array allocated for storing the board.
 */
int TwoDCharArray::GetArraySize() {
  return (arraySize_);
}
