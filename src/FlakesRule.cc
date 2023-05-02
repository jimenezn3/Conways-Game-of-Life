#include <FlakesRule.h>

char FlakesRule::GetNextCellState(char currentCellState, int liveNeighborCount) const {
  char nextState = DEAD_CELL;

  //Flakes rule for live cells
  if((currentCellState == LIVE_CELL) && (liveNeighborCount > -1) && (liveNeighborCount < 10)) {
	nextState == LIVE_CELL;
  }

  //Flakes rule for dead cells
  else if((currentCellState == DEAD_CELL) && (liveNeighborCount > 2) && (liveNeighborCount < 4)) {
	nextState == LIVE_CELL;
  }


  return nextState;
}
