#ifndef RULE_H_
#define RULE_H_

#include<string>

#define LIVE_CELL 'O'
#define DEAD_CELL ' '

using namespace std;

/**
 * Abstract class representing a rule.  You will need
 * to provide derived classes implementing specific
 * rules.  At the very least, you must implement the
 * GetNextCellState() method, which returns the next
 * cell state based on the current state and the count
 * of live neighbors.  Also don't forget to chain your
 * constructor to set the name of the rule.  This is
 * used in SimulationMain to present the user with a
 * choice.
 */
class Rule {
public:
  Rule(string name) : rulename_(name) {}

  virtual char GetNextCellState(char currentCellState,
                                int liveNeighborCount) const = 0;

  string GetRuleName() { return rulename_; }

protected:
  string rulename_;
};

#endif
