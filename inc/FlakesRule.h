#ifndef FLAKESRULE_H_
#define FLAKESRULE_H_

#include <string>
#include <Rule.h>

using namespace std;

class FlakesRule : public Rule {

  public:
	FlakesRule() : Rule("Flakes") {}

	char GetNextCellState(char currentCellState, int liveNeighborCount) const;
};

#endif // FLAKESRULE_H_
