#include <stdbool.h>
#include <stdio.h>

/*
  Description: <Describe what this program does briefly>
  Programmed by: Sadiarin, Edwin Jr. M., CCPROG1-S19A
  Last modified: <date when last revision was made>
  Version: 1
  [Acknowledgements:
  - stdbool.h library for boolean types

  ]
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

// use struct so only 1 argument to be passed on functions
struct PlayerStatus {
  int gold;
  int energy;
  int day;
  int starvedDay;
  int bananaSeeds;
  int mangoSeeds;
  int cornSeeds;
};

struct FarmStatus {
  int tilledPlots;
  int untilledPlots;
  int bananaPlots;
  int mangoPlots;
  int cornPlots;
};

void displayMainMenuOptions(struct PlayerStatus *player) {

  printf("----------------------------------------\n");
  printf("|    ***** Choose your Action *****    |\n");
  printf("----------------------------------------\n");
  printf("Current Status:\n");
  printf("Gold: %dG\n", player->gold);
  printf("Energy: %d/30\n", player->energy);
  printf("Hunger: %d/3\n", player->starvedDay);
  printf("----------------------------------------\n");
  printf("Enter 1 - Go Home\n");
  printf("Enter 2 - Go to the Farm\n");
  printf("Enter 3 - Go to Shop\n");
  printf("Enter 4 - Quit\n");
  printf("----------------------------------------\n");
  printf("Enter the number of your desired action: ");
  /*
   * - can use switch for option prompts (1, 2, 3, etc.)
   * - use do while loop here? or do while loop outside and calling this
   * function
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
 *      - then warning for player
 *    if starveDay == 4:
 *      - inform that player dies/loses/starves
 *      - force quit game (call quit() function)
 * */
/*
 * This function
 *
 * Precondition:
 *
 * @param
 *
 * @return
 *
 * */
int checkIfDead(struct PlayerStatus *player, bool *isPlayerDead) {
  // if 3/3 starvedDay not die, next day: die (die at 4th day when starving)
  // this is passed by value, so it copies it into a new variable (not modifies
  // the original):
  // int starvedDay = player->starvedDay;

  if (player->gold < 10) {
    player->starvedDay += 1;
  }

  switch (player->starvedDay) {
  case 1:
    printf("\n\n\n!!!!!!! >>>>>>>>>>>>>> WARNING <<<<<<<<<<<<<<<<< !!!!!!!\n");
    printf("[ STARVATION WARNING ]: your hunger status increased!\n");
    printf("[ REMINDER ]: Make sure to have enough gold (10g) to eat breakfast "
           "next day\n");
    printf("[ REMINDER ]: If your hunger becomes 3/3, you will INEVITABLY DIE "
           "the next day\n");
    break;
  case 2:
    printf("\n\n\n!!!!!!! >>>>>>>>>>>>>> WARNING <<<<<<<<<<<<<<<<< !!!!!!!\n");
    printf("[ STARVATION WARNING ]: your hunger status increased to 2/3!\n");
    printf("[ STARVATION CRISIS ]: EARN 10 GOLD NOW TO EAT BREAKFAST\n");
    break;
  case 3:
    printf("\n\n\n!!!!!!! >>>>>>>>>>>>>> WARNING <<<<<<<<<<<<<<<<< !!!!!!!\n");
    printf("[ STARVATION DISASTER ]: YOUR HUNGER IS NOW 3/3, you will "
           "INEVITABLY DIE the next day.\n");
    break;
  case 4:
    printf("\nYou died due to starvation. Git gud!\n");
    *isPlayerDead = true;
    break;
  default:
    break;
  }

  return 0;
}

/* **************** FARM RELATED FUNCTIONS START ***************** */

void displayFarmOptions(struct PlayerStatus *player, struct FarmStatus *farm) {
  printf("----------------------------------------\n");
  printf("|    ***** Your Farm Status *****    |\n");
  printf("----------------------------------------\n");
  printf("Energy: %d/30\n", player->energy);
  printf("----------------------------------------\n");
  // show crops here (Banana, Mango, Corn)
  printf("Tilled plots: %d/30\n", farm->tilledPlots);
  printf("Untilled plots: %d/30\n", farm->untilledPlots);
  printf("Planted bananas: %d/30\n", farm->bananaPlots);
  printf("Planted mangoes: %d/30\n", farm->mangoPlots);
  printf("Planted corn: %d/30\n", farm->cornPlots);
  printf("----------------------------------------\n");
  printf("Enter 1 - Till plots\n");
  printf("Enter 2 - Sow seeds\n");
  printf("Enter 3 - Water crops\n");
  printf("Enter 4 - Harvest crops\n");
  printf("Enter 5 - Go to main menu\n");
  printf("----------------------------------------\n");
}

void tillPlots(struct PlayerStatus *player, struct FarmStatus *farm) {
  int plotsToTillAmount;

  do {
    // error handle, prompts player again until correct conditions are met
    printf("Enter amount of plots to till (enter 0 to cancel): ");
    scanf(" %d", &plotsToTillAmount);

    if (plotsToTillAmount == 0) {
      return;
    }

    // check if player have enough energy
    if (player->energy < plotsToTillAmount) {
      printf("\nEnergy is not sufficient.\n");
    }
    // check if farm have enough untilledPlots to be tilledPlots
    if (farm->untilledPlots < plotsToTillAmount) {
      printf("Not enough untilled plots to till\n");
    }
  } while (player->energy < plotsToTillAmount ||
           farm->untilledPlots < plotsToTillAmount);

  // if player has enough energy then energy - plotsToTill
  player->energy -= plotsToTillAmount;

  // update tilledPlots based on plotsToTill input from player
  farm->tilledPlots += plotsToTillAmount;

  // update untilledPlots (subtract to how many are now tilledPlots)
  farm->untilledPlots -= plotsToTillAmount;

  printf("\nNOTICE: Farm has been updated\n");
}

void sowSeeds(struct PlayerStatus *player, struct FarmStatus *farm) {
  int seedsToSowAmount, seedType;

  printf("----------------------------------------\n");
  printf("**** Inventory: ****\n");
  printf("Banana Seeds (Bag): %d\n", player->bananaSeeds);
  printf("Mango Seeds (Bag): %d\n", player->mangoSeeds);
  printf("Corn Seeds (Bag): %d\n", player->cornSeeds);
  printf("----------------------------------------\n");
  printf("**** Farm Status: ****\n");
  printf("Tilled plots: %d/30\n", farm->tilledPlots);
  printf("Banana plots planted: %d\n", farm->bananaPlots);
  printf("Mango plots planted: %d\n", farm->mangoPlots);
  printf("Corn plots planted: %d\n", farm->cornPlots);
  printf("----------------------------------------\n");

  // check if there are tilled plots
  if (farm->tilledPlots < 1) {
    printf("\nThere are no tilled plots. Till plots first to sow seeds.\n");
    return;
  }

  do {
    // check type of seed to sow
    printf("\n ***** What type of seed? ***** \n");
    printf("\n1 for Banana Seeds");
    printf("\n2 for Mango Seeds");
    printf("\n3 for Corn Seeds");
    printf("\nEnter type of seed to sow (enter 0 to cancel): ");
    scanf(" %d", &seedType);

    if (seedType == 0) {
      return;
    }

    printf("\nEnter amount of seeds to sow: ");
    scanf(" %d", &seedsToSowAmount);

    // CANCEL CONDITION: check if tilledPlots are enough
    if (seedsToSowAmount > farm->tilledPlots) {
      printf("Not enough tilled plots to sow %d seeds", seedsToSowAmount);
      return;
    }

    // banana seeds
    if (seedType == 1) {
      // CANCEL CONDITION: check if type of seed are already sown
      if (farm->bananaPlots > 0) {
        printf("Banana seeds are already sown. Harvest them first.\n");
        return;
      }
      // CANCEL CONDITION: check if owned banana seeds are enough
      if (seedsToSowAmount > player->bananaSeeds) {
        printf("Not enough bag of banana seeds.\n");
        printf("Buy in shop first.\n");
        return;
      }
      // CANCEL CONDITION: check if energy is enough
      if (seedsToSowAmount > player->energy) {
        printf("Not enough energy to sow %d banana seeds\n", seedsToSowAmount);
        return;
      }

      // update bananaPlots
      farm->bananaPlots += seedsToSowAmount;
      // update bananaSeeds
      player->bananaSeeds -= seedsToSowAmount;
      // update energy
      player->energy -= seedsToSowAmount;
    }

    // mango seeds
    if (seedType == 2) {
      // CANCEL CONDITION: check if type of seed are already sown
      if (farm->mangoPlots > 0) {
        printf("Mango seeds are already sown. Harvest them first.\n");
        return;
      }
      // CANCEL CONDITION: check if owned banana seeds are enough
      if (seedsToSowAmount > player->mangoSeeds) {
        printf("Not enough bag of mango seeds.\n");
        printf("Buy in shop first.\n");
        return;
      }
      // CANCEL CONDITION: check if energy is enough
      if (seedsToSowAmount > player->energy) {
        printf("Not enough energy to sow %d mango seeds\n", seedsToSowAmount);
        return;
      }

      // update mangoPlots
      farm->mangoPlots += seedsToSowAmount;
      // update mangoSeeds
      player->mangoSeeds -= seedsToSowAmount;
      // update energy
      player->energy -= seedsToSowAmount;
    }

    // corn seeds
    if (seedType == 3) {
      // CANCEL CONDITION: check if type of seed are already sown
      if (farm->cornPlots > 0) {
        printf("Corn seeds are already sown. Harvest them first.\n");
        return;
      }
      // CANCEL CONDITION: check if owned banana seeds are enough
      if (seedsToSowAmount > player->cornSeeds) {
        printf("Not enough bag of corn seeds.\n");
        printf("Buy in shop first.\n");
        return;
      }
      // CANCEL CONDITION: check if energy is enough
      if (seedsToSowAmount > player->energy) {
        printf("Not enough energy to sow %d corn seeds\n", seedsToSowAmount);
        return;
      }

      // update cornPlots
      farm->cornPlots += seedsToSowAmount;
      // update cornSeeds
      player->cornSeeds -= seedsToSowAmount;
      // update energy
      player->energy -= seedsToSowAmount;
    }
  } while (seedType != 0 || seedsToSowAmount < 0);

  printf("\nNOTICE: Farm has been updated\n");
}

/*
 * Farm function
 * - every action in the farm consumes energy
 * - if no energy, they cannot go to farm (so this checks for energy value)
 *
 * (1) Till Plots
 * - 30 plots in total
 * - ask player how many to till (prompt)
 * - 1 plot = 1 energy consumed
 * - plot = "untilled" --turn into---> plot = "tilled"
 *
 * (2) Sow Seeds
 * - 1 bag of seed per tilled plot
 * - only way to get bag of seed is to buy seed at shop
 * - 3 seeds:
 *   (1) Banana
 *   (2) Corn
 *   (3) Mango
 * - can only perform this action if plot is "tilled"
 *   - check if plot is tilled
 * - cannot sow seeds if same type of seed is planted and not yet harvested
 *   - For example, if bananas are already planted and not yet harvested, it
 *     cannot be planted again yet
 *   - check if same type of seed is planted
 *
 *
 * - check if bags of seed are "enough" (TODO: limit: ?)
 *
 * - check if energy is enough to sow seeds on tilled plots
 *   - 1 energy consumed = 1 sow seed on a tilled plot
 *   - For example, if 10 bags of mango seeds will be sown on 10 tilled plots,
 *     then 10 energy will be consumed.
 *
 *  How to get bag of seed?
 * - buy from shop using gold
 *
 * (3) Water Crops
 * - can only water the same type of crops once a day
 *  - prompt player what type of crops to water
 *  - check if type of crops is not yet "watered",
 *    - if "watered" then display "it is watered, go next day to water again"
 * message
 *    - if not, check if player has enough energy to water (all same type of
 *      crop will be watered)
 *      - example: if 20 plot with banana planted = 20 energy will be consumed
 *
 * (4) Harvest Crops
 * - player can harvest if crop is watered certain number of times
 *   - prompt user what to harvest
 *   - then check if it ready to be harvested
 *   Banana - 4 water times to be harvested
 *   Corn - 6 ...
 *   Mango - 8 ...
 *
 * - 1 kg of crop harvest = 1 plot
 * - 1 plot harvest = 1 energy will be consumed
 *
 * (5) Go back to main menu
 *
 * */
void goToFarm(struct PlayerStatus *player, struct FarmStatus *farm) {

  int playerChoice;

  do {
    displayFarmOptions(player, farm);

    printf("Enter the number of your desired action: ");
    scanf("%d", &playerChoice);

    switch (playerChoice) {
    case 1:
      printf("\nYou chose to till plots\n");
      tillPlots(player, farm);
      break;
    case 2:
      printf("\nYou chose to sow seeds\n");
      sowSeeds(player, farm);
      // function here
      break;
    case 3:
      printf("\nYou chose to water crops!\n");
      // function here
      break;
    case 4:
      printf("\nYou chose to harvest crops!\n");
      // function here
      break;
    case 5:
      printf("\nGoing back to main menu...\n");
      // no need since this goToFarm function is inside another switch case that
      // have a do while loop displayMainMenuOptions(player);
      break;
    default:
      // checks if int input is valid
      printf("\nInvalid input! Enter numbers 1-5 only.\n");
    }
  } while (playerChoice != 5);
}

/* **************** FARM RELATED FUNCTIONS END ***************** */

/*
 * This function
 *
 * Precondition:
 *
 * @param
 *
 * @return
 *
 * */
void goHome(struct PlayerStatus *player, bool *isPlayerDead) {

  checkIfDead(player, isPlayerDead);

  if (*isPlayerDead == false) {

    // increment day (sleep)
    player->day += 1;

    printf("\n********************************* ");
    printf("Day %d", player->day);
    printf(" *********************************\n\n");

    // reset energy to full
    printf("REJUVENATED! Energy has been reset to full\n");
    player->energy = 30;

    // tax gold for breakfast & update hunger status
    printf("-10 gold for eating breakfast\n");
    printf("Eating breakfast... nom nom nom\n\n");

    player->gold -= 10;
  }
}

/* Shop function
 * - display "Welcome to Shop"
 *   (1) Buy Seeds
 *   - ask type of seed and how many they want to buy
 *   Banana - 3 gold per bag of banana seeds
 *   Corn - 5 ...
 *   Mango - 7 ...
 *   - For example:
 *    - player chose Mango and 15 bags = 7 * 15 = 105 gold needed to buy 15 bags
 *      of mango seeds
 *
 *   (2) Sell Crops
 *   - player can sell harvested crops
 *   - ask type of crops and how many to sell
 *   Banana - 4 gold per bag of banana seeds
 *   Corn - 7 ...
 *   Mango - 10 ...
 *   - check if player has enough quantity of crops in their "inventory" to sell
 *   - For example:
 *    - player chose Corn and 30 kg of corn to sell,
 *    - check first if player has 30 kg of corn
 *    - if yes, then:
 *      - 10 gold * 30 kilos or kg = 300 gold acquired
 *
 *   (3) Go back to main menu
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

int main() {
  struct PlayerStatus player;
  player.gold = 50;
  player.energy = 30;
  player.day = 1;
  player.starvedDay = 0;
  player.bananaSeeds = 0;
  player.mangoSeeds = 0;
  player.cornSeeds = 0;

  struct FarmStatus farm;
  farm.tilledPlots = 0;
  farm.untilledPlots = 30;
  farm.bananaPlots = 0;
  farm.mangoPlots = 0;
  farm.cornPlots = 0;

  int playerChoice;
  bool isPlayerDead = false;

  printf("******* WELCOME TO HARVEST SUN *******\n");
  printf(" _   _                           _     _____             \n");
  printf("| | | |                         | |   /  ___|            \n");
  printf("| |_| | __ _ _ ____   _____  ___| |_  \\ `--. _   _ _ __  \n");
  printf("|  _  |/ _` | '__\\ \\ / / _ \\/ __| __|  `--. \\ | | | '_ \\ \n");
  printf("| | | | (_| | |   \\ V /  __/\\__ \\ |_  /\\__/ / |_| | | | |\n");
  printf("\\_| |_/\\__,_|_|    \\_/ \\___||___/\\__| \\____/ \\__,_|_| |_|\n");
  printf("                                                         \n");
  printf("                                                         \n");
  do {
    displayMainMenuOptions(&player);
    scanf("%d", &playerChoice);

    switch (playerChoice) {
    case 1:
      printf("\nYou chose to Go Home. Have a wonderful rest!\n");
      goHome(&player, &isPlayerDead);
      break;
    case 2:
      printf("\nYou chose to Go to the Farm!\n");
      goToFarm(&player, &farm);
      break;
    case 3:
      printf("\nYou chose to Go to Shop!\n");
      // function here
      break;
    case 4:
      printf("\nThank you for playing Harvest Sun!\n");
      break;
    default:
      printf("\nInvalid input! Enter numbers 1-4 only.\n");
    }
  } while (playerChoice != 4 && isPlayerDead == false);

  return 0;
}
