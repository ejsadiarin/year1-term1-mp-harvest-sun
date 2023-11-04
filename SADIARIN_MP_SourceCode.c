#include <stdio.h>

/*
  Description: <Describe what this program does briefly>
  Programmed by: Sadiarin, Edwin Jr. M., CCPROG1-S19A
  Last modified: <date when last revision was made>
  Version: 1
  [Acknowledgements: <list of sites or borrowed libraries and sources>]
*/

// The program will end
// ● when the player starves for 3 consecutive days which leads to death due to
// hunger and thirst; or, ● when the user selects “Quit”.

/*
 * START:
 * - Day 1:
 *    int gold = 50
 *    int energy = 30
 *    int day = 1
 * - these values are the "global variables" defined in the main function (or in
 * #define?)
 * */

/*
 * starveCounter() --> checks if player did not eat, call this function everyday
 * (at start of next day)
 * - has variable to mutate:
 *   int straveDay = 0;
 * if gold > 10: --> since breakfast costs 10 gold
 *  - increment/mutate starveDay variable:
 *       starveDay++;
 *  - then nested conditions:
 *    if starveDay == 1:
 *      - then warning for player
 *    if starveDay == 2:
 *      - then warning for player
 *    if starveDay == 3:
 *      - inform that player dies/loses/starves
 *      - force quit game (call quit() function)
 * */

/*
 * This function displays the main menu options
 *
 * Precondition:
 *
 * @param
 *
 * @return
 *
 * */
void displayMainMenuOptions() {
  int playerChoice;

  printf("***** Choose your Action *****\n");
  printf("---------------------------------\n");
  printf("Enter the number of your desired action:\n");
  printf("---------------------------------\n");
  printf("Enter 1 - Go Home\n");
  printf("Enter 2 - Go to the Farm\n");
  printf("Enter 3 - Go to Shop\n");
  printf("Enter 4 - Quit\n");
  printf("---------------------------------\n");
  scanf("%d\n", &playerChoice);

  switch (playerChoice) {
  case 1:
    printf("test");
    break;
  case 2:
    printf("test");
    break;
  case 3:
    printf("test");
    break;
  case 4:
    printf("test");
    break;
  default:
    printf("default");
  }

  /*
   * - can use switch for option prompts (1, 2, 3, etc.)
   *
   *
   * Home
   * - automatically sleep (go to next day, day++)
   * - increments day (day++)
   * - restores full energy for the FOLLOWING DAY ()
   * - eats breakfast:
   *   - costs 10 gold (automatically charged at start of the day)
   *
   * Farm
   * - every action in the farm consumes energy
   * - if no energy, they cannot go to farm (so this checks for energy value)
   * - have option to go back to main menu
   * - has 4 player actions/options:
   *   (1) Till Plots
   *   (2) Sow Seeds
   *   (3) Water Crops
   *   (4) Harvest Crops
   *   (5) Go back to main menu
   *
   * Shop
   * - can buy seeds
   * - can sell crops
   * - does NOT CONSUME energy
   * - actions/options:
   *   (1) Buy Seeds
   *   (2) Sell Crops
   *   (3) Go back to main menu
   *
   * Quit
   * - print "thank you for playing!"
   * - terminates program (return 0?)
   *
   * */
}

int main() {
  int gold, energy, day;

  printf("******* WELCOME TO HARVEST SUN *******");

  return 0;
}
