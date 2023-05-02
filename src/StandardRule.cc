#include<StandardRule.h>

char StandardRule::GetNextCellState(char currentCellState,
                                    int liveNeighborCount) const {
  char nextState = DEAD_CELL;

  // Conway's rule for live cells
  if ( (currentCellState == LIVE_CELL) &&
       (liveNeighborCount > 1) && (liveNeighborCount < 4) )
    nextState = LIVE_CELL;

  // Conway's rule for dead cells
  else if ( (currentCellState == DEAD_CELL) &&
            (liveNeighborCount == 3) )
    nextState = LIVE_CELL;

  // Otherwise, the cell dies
  return nextState;
}
