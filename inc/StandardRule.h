#ifndef STANDARDRULE_H_
#define STANDARDRULE_H_

#include<string>

#include<Rule.h>

using namespace std;

/**
 * This class inherits from the base Rule class and implements
 * John Conway's stard rule for the Life simulation.
 */
class StandardRule : public Rule {
public:
  // Chain the constructor ...
  StandardRule() : Rule("Standard") {}

  char GetNextCellState(char currentCellState,
                        int liveNeighborCount) const;
};

#endif
