#include <ExplodingRule.h>

char ExplodingRule::GetNextCellState(char currentCellState, int liveNeighborCount) const {
  char nextState = DEAD_CELL;

  //Exploding rule for live cells
  if((currentCellState == LIVE_CELL) && (liveNeighborCount > 2) && (liveNeighborCount < 5)) {
	nextState = LIVE_CELL;
  }

  //Exploding rule for dead cells
  else if((currentCellState == DEAD_CELL) && (liveNeighborCount > 2) && (liveNeighborCount < 5)) {
	nextState = LIVE_CELL;
  }

  return nextState;
}
