#ifndef TWODCHARARRAY_H_
#define TWODCHARARRAY_H_

#include<string>

using namespace std;

/**
 * This reflects one solution to project 2.  You will need to
 * take care of *deallocation* via a destructor.
 *
 * I left this here so the program shell would compile without
 * error; however, project two involves *replacing* this class
 * with something more dynamic.  You will either have to
 * throw this away, or heavily modify it for your purposes.
 *
 * -----
 *
 * Class definition for the simple way to manage 2D character
 * arrays.  This class treats it as one large single string,
 * and calculates the offest into that string as though it
 * were a 2D structure.  It does this to avoid the pointer
 * to pointers structure with which students may be less
 * familiar.
 *
 * Ideally, we would size the character string dynamically
 * and deal with copy methods and deep vs. shallow copies.
 * Those are subjects for later in the class.  For now, just
 * know that you *must* pass the *pointer* of an instance,
 * not the actual instance.
 */
class TwoDCharArray {
public:
  // Array setup/shutdown operations

  //Constructor
  TwoDCharArray(int maxWidth, int maxHeight, char emptyChar);

  //Destructor
  ~TwoDCharArray();

  //void Initialize(int maxWidth, int maxHeight, char emptyChar);
  void ReadFromFile(const string filename);
  void DeepCopy(TwoDCharArray *otherArray);

  // Accessor methods
  char GetCharAt(int row, int col, char defaultChar);
  void SetCharAt(int row, int col, char myChar);
  int GetMaxHeight();
  int GetMaxWidth();
  int GetArraySize();

 private:
  int maxWidth_;
  int maxHeight_;
  int arraySize_;
  char *charMatrix_;
  // This can now be called many times, so represents a serious memory leak.
  // You will need to make sure it gets deallocated.
};

#endif //TWODCHARARRAY_H_
