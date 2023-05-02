#include<iostream>
#include<string>
#include<vector>

#include<ConwayLife.h>
#include<StandardRule.h>
// You'll need to add your headers here, too ...
#include<ExplodingRule.h>
#include<FlakesRule.h>

// The sleep function is in a different header in Windows,
// so we'll need to get that header, depending on the OS.
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;


/**
 *  Get information from the user for the simulation.
 *   @param width The maximum width of the simulated board
 *   @param height The maximum height of the simulated board
 *   @param iterations The maximum number of iterations of the simulation
 *   @param seedfilename The name of the file to read for a seed board
 *   @return The rule to use for the simulation.
 **/
Rule *GetUserInformation(int &width,
                         int &height,
                         int &iterations,
                         string &seedfilename,
                         vector<Rule*> potentialRuleList) {
  cout << "Width: ";
  cin >> width;

  cout << "Height: ";
  cin >> height;

  cout << "Max Iterations: ";
  cin >> iterations;

  cout << "Seed Filename: ";
  cin >> seedfilename;

  // Present the menu to the user
  cout << "Here are the possible rules available:" << endl;
  for (int idx=0; idx < potentialRuleList.size(); idx++) {
    cout << "  " << (idx+1) << ". "
         << potentialRuleList[idx]->GetRuleName() << endl;
  }

  // Get their choice as an integer
  int whichRule;
  cout << "Select which would like to use: " << endl;
  cin >> whichRule;

  // Vectors index at 0, but we presented the user
  // options starting at 1.  So we have to subtract 1.
  return potentialRuleList[whichRule-1];
}


/**
 * This is the main code for running the simulation for Conway's Life CA.
 */
int main(void) {
  // Variables for user-specified options
  int width, height, iterations;
  string seedfilename;
  vector<Rule*> potentialRuleList;
  bool done = false;

  // Give the user their option of rules:
  potentialRuleList.push_back(new StandardRule);
  // Push back at least two more  here ...
  potentialRuleList.push_back(new ExplodingRule);
  potentialRuleList.push_back(new FlakesRule);

  do {
    // Get input from the user to setup the simulation
    Rule *rule = GetUserInformation(width, height, iterations,
                                    seedfilename, potentialRuleList);

    ConwayLife lifesim(width, height);

    // Initialize the life simulator and read the seed in from the file
    //lifesim.Initialize(width, height); // Move into constructor
    lifesim.ReadFromFile(seedfilename);

    // Step 100 times, with a small delay
    for (int time=0; time<iterations; time++) {
      lifesim.ViewLifeField();    // Display the main field
      lifesim.LifeStepUpdate(rule);   // Update the next field based on CA rules
      lifesim.SwitchLifeFields(); // Replace the main field with the updated field
      usleep(100000); // Delay 100K microseconds (10th of a second)
    }

    lifesim.Close();

    // Ask if the user wants to go again ...
    string another = "No way, I'm outa here!";
    cout << endl << "Run another simulation (y/n)? ";
    cin >> another;
    char firstChar = another[0];
    done = (firstChar != 'Y') && (firstChar != 'y');
  } while (!done);

  // Probably we should clean up the allocation of the rules in
  // the vector, but since this is the last line of the program,
  // I will be lazy.
}
