#ifndef CONWAYLIFE_H_
#define CONWAYLIFE_H_

#include<string>

#include<BoardVisualizer.h>
#include<TwoDCharArray.h>
#include<Rule.h>

using namespace std;

/**
 * Class definition for objects that implement the CA rules for
 * Conway's Game of Life.  This maintains two fields:  The "main"
 * field is the current state of the simulation.  The "next"
 * field is where state changes are written to.  This object
 * holds a copy of the board visualizer and is responsible for
 * setting it up and closing it properly.  A ConwayLife object
 * should know how big the fields are based on the size of the
 * terminal screen (which it can get from the visualizer).
 *
 * Students will be given this header, but will have to write the
 * body code.
 */
class ConwayLife {
public:
  // Conway's Life setup/shutdown operations

  //Constructor:
  ConwayLife(const int width, const int height);

  //Destructor
  ~ConwayLife();

  //void Initialize(const int width, const int height);

  void ReadFromFile(const string filename);
  void Close();

  // Step Operations
  void LifeStepUpdate(const Rule *rule);
  void SwitchLifeFields();
  void ViewLifeField();

  // Accessor methods
  int GetMaxHeight();
  int GetMaxWidth();

protected:
  int CountLiveNeighbors(const int row, const int col);

private:
  TwoDCharArray* mainlifefield_;
  TwoDCharArray* nextlifefield_;
  BoardVisualizer visualizer_;
  int maxWidth_;
  int maxHeight_;
};

#endif //CONWAYLIFE_H_
