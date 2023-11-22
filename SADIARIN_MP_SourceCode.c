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

/* The program will end if:
 * (1) when the player starves for 3 consecutive days
 *    - which leads to death due to hunger and thirst
 *    - 4th day inevitable death
 * (2) when the user selects “Quit”.
 * (3) some calamity (mystery)
 */

// use struct so only 1 argument to be passed on functions
struct PlayerStatus {
  int gold;
  int energy;
  int day;
  int starvedDay;
  int bananaSeeds;
  int mangoSeeds;
  int cornSeeds;
  int bananaCrops;
  int mangoCrops;
  int cornCrops;
};

struct FarmStatus {
  int tilledPlots;
  int untilledPlots;
  int bananaPlots;
  int mangoPlots;
  int cornPlots;
  // for waterCrops
  bool isBananaWatered;
  bool isMangoWatered;
  bool isCornWatered;
  int bananaWaterAmount;
  int mangoWaterAmount;
  int cornWaterAmount;
  bool canHarvestBanana;
  bool canHarvestMango;
  bool canHarvestCorn;
};

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
}

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
void displayFarmOptions(struct PlayerStatus *player, struct FarmStatus *farm) {
  printf("\n\n----------------------------------------\n");
  printf("|    ***** Your Farm Status *****    |\n");
  printf("----------------------------------------\n");
  printf("Energy: %d/30\n", player->energy);
  printf("----------------------------------------\n");
  // show crops here (Banana, Mango, Corn)
  printf("Tilled plots: %d/30\n", farm->tilledPlots);
  printf("Untilled plots: %d/30\n", farm->untilledPlots);
  printf("Planted bananas: %d/30\n", farm->bananaPlots);
  printf("Planted mangoes: %d/30\n", farm->mangoPlots);
  printf("Planted corns: %d/30\n", farm->cornPlots);
  printf("----------------------------------------\n");
  printf("Enter 1 - Till plots\n");
  printf("Enter 2 - Sow seeds\n");
  printf("Enter 3 - Water crops\n");
  printf("Enter 4 - Harvest crops\n");
  printf("Enter 5 - Go to main menu\n");
  printf("----------------------------------------\n");
}

// int checkIfWateredForTheDay(struct FarmStatus *farm) {
//   if (farm->isBananaWatered == true)
// }

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

    while (seedType > 3 || seedType < 0) {
      printf("\n[ INVALID INPUT ] Enter 1-3 only. (enter 0 to cancel)");
      printf("\nEnter type of seed to sow (enter 0 to cancel): ");
      scanf(" %d", &seedType);
    }

    if (seedType == 0) {
      return;
    }

    printf("\nEnter amount of seeds to sow: ");
    scanf(" %d", &seedsToSowAmount);

    // CANCEL CONDITION: check if tilledPlots are enough
    if (seedsToSowAmount > farm->tilledPlots) {
      printf("Not enough tilled plots to sow %d seeds\n", seedsToSowAmount);
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
      printf("\nNOTICE: Farm has been updated\n");
      return;
    }

    // mango seeds
    if (seedType == 2) {
      // CANCEL CONDITION: check if type of seed are already sown
      if (farm->mangoPlots > 0) {
        printf("Mango seeds are already sown. Harvest them first.\n");
        return;
      }
      // CANCEL CONDITION: check if owned mango seeds are enough
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
      printf("\nNOTICE: Farm has been updated\n");
      return;
    }

    // corn seeds
    if (seedType == 3) {
      // CANCEL CONDITION: check if type of seed are already sown
      if (farm->cornPlots > 0) {
        printf("Corn seeds are already sown. Harvest them first.\n");
        return;
      }
      // CANCEL CONDITION: check if owned corn seeds are enough
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
      printf("\nNOTICE: Farm has been updated\n");
      return;
    }
  } while (seedType != 0 || seedsToSowAmount < 0);
}

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
void waterCrops(struct PlayerStatus *player, struct FarmStatus *farm) {
  int cropsToWaterAmount, cropType;

  char *bananaWateredStatus = farm->isBananaWatered ? "YES" : "not yet";
  char *mangoWateredStatus = farm->isMangoWatered ? "YES" : "not yet";
  char *cornWateredStatus = farm->isCornWatered ? "YES" : "not yet";

  bool allWatered = farm->isBananaWatered == true &&
                    farm->isMangoWatered == true && farm->isCornWatered == true;

  printf("----------------------------------------\n");
  printf("**** Farm Status: ****\n");
  printf("Tilled plots: %d/30\n", farm->tilledPlots);
  printf("Banana plots planted: %d | Watered status: %s\n", farm->bananaPlots,
         bananaWateredStatus);
  printf("Mango plots planted: %d | Watered status: %s\n", farm->mangoPlots,
         mangoWateredStatus);
  printf("Corn plots planted: %d | Watered status: %s\n", farm->cornPlots,
         cornWateredStatus);
  printf("----------------------------------------\n");

  do {
    // if (allWatered) {
    //   printf("All types of crops are watered. See you tomorrow\n");
    //   return;
    // }

    printf("\n ***** What type of crops to water? ***** \n");
    printf("\n1 for Banana Crops");
    printf("\n2 for Mango Crops");
    printf("\n3 for Corn Crops");
    printf("\nEnter type of crops to water (enter 0 to cancel): ");
    scanf(" %d", &cropType);

    while (cropType > 3 || cropType < 0) {
      printf("\n[ INVALID INPUT ] Enter 1-3 only. (enter 0 to cancel)");
      printf("\nEnter type of crops to water (enter 0 to cancel): ");
      scanf(" %d", &cropType);
    }

    if (cropType == 0) {
      return;
    }

    printf("\nEnter amount of crops to water (enter 0 to cancel): ");
    scanf(" %d", &cropsToWaterAmount);

    // banana crops
    if (cropType == 1) {
      // CANCEL CONDITION: check if selected cropType is watered
      if (farm->isBananaWatered == true) {
        printf("\n\nBanana crops are already watered for the day.\n");
        printf("Go to the next day to water the same type of crop\n");
        return;
      }

      // CANCEL CONDITION: check if energy is enough
      if (player->energy < cropsToWaterAmount) {
        printf("Not enough energy to water %d amount of crops\n",
               cropsToWaterAmount);
        return;
      }

      // CANCEL CONDITION: check if current bananaPlots are enough
      if (farm->bananaPlots < cropsToWaterAmount) {
        printf("Not enough banana plots.\n");
        return;
      }

      // update water crops and flag
      farm->bananaWaterAmount++;
      farm->isBananaWatered = true;
      printf("Successfully watered banana crops!\n");

      // ready to harvest
      if (farm->bananaWaterAmount == 4) {
        printf("\nYour banana crops are now ready to be harvested!\n");
        farm->canHarvestBanana = true;

        // put max limit for the water amount
        if (farm->bananaWaterAmount > 4) {
          farm->bananaWaterAmount = 4;
        }
      }

      return;
    }

    // mango crops
    if (cropType == 2) {
      // CANCEL CONDITION: check if selected cropType is watered
      if (farm->isMangoWatered == true) {
        printf("\n\nMango crops are already watered for the day.\n");
        printf("Go to the next day to water the same type of crop\n");
      }

      // CANCEL CONDITION: check if energy is enough
      if (player->energy < cropsToWaterAmount) {
        printf("Not enough energy to water %d amount of crops\n",
               cropsToWaterAmount);
      }

      // CANCEL CONDITION: check if current mangoPlots are enough
      if (farm->mangoPlots < cropsToWaterAmount) {
        printf("Not enough mango plots.\n");
      }

      // update water crops and flag
      farm->mangoWaterAmount++;
      farm->isMangoWatered = true;
      printf("Successfully watered mango crops!\n");

      // ready to harvest
      if (farm->mangoWaterAmount == 8) {
        printf("Your mango crops are now ready to be harvested!\n");
        farm->canHarvestMango = true;

        // put max limit for the water amount
        if (farm->mangoWaterAmount > 8) {
          farm->mangoWaterAmount = 8;
        }
      }

      return;
    }

    // corn crops
    if (cropType == 3) {
      // CANCEL CONDITION: check if selected cropType is watered
      if (farm->isCornWatered == true) {
        printf("\n\nCorn crops are already watered for the day.\n");
        printf("Go to the next day to water the same type of crop\n");
      }

      // CANCEL CONDITION: check if energy is enough
      if (player->energy < cropsToWaterAmount) {
        printf("Not enough energy to water %d amount of crops\n",
               cropsToWaterAmount);
      }

      // CANCEL CONDITION: check if current mangoPlots are enough
      if (farm->cornPlots < cropsToWaterAmount) {
        printf("Not enough corn plots.\n");
      }

      // update water crops and flag
      farm->cornWaterAmount++;
      farm->isCornWatered = true;
      printf("Successfully watered corn crops!\n");

      // ready to harvest
      if (farm->cornWaterAmount == 6) {
        printf("Your corn crops are now ready to be harvested!\n");
        farm->canHarvestCorn = true;

        // put max limit for the water amount
        if (farm->cornWaterAmount > 6) {
          farm->cornWaterAmount = 6;
        }
      }

      return;
    }
  } while (cropType != 0 || cropType < 0);
}

void harvestCrops(struct PlayerStatus *player, struct FarmStatus *farm) {
  int cropType;

  char *bananaHarvestStatus =
      farm->bananaWaterAmount == 4 ? "Ready to harvest" : "not yet";
  char *mangoHarvestStatus =
      farm->mangoWaterAmount == 8 ? "Ready to harvest" : "not yet";
  char *cornHavestStatus =
      farm->cornWaterAmount == 6 ? "Ready to harvest" : "not yet";

  printf("----------------------------------------\n");
  printf("**** Harvest Status: ****\n");
  printf("Banana crops: %s | Water amount: %d/4\n", bananaHarvestStatus,
         farm->bananaWaterAmount);
  printf("Mango crops: %s | Water amount: %d/8\n", mangoHarvestStatus,
         farm->mangoWaterAmount);
  printf("Corn crops: %s | Water amount: %d/6\n", cornHavestStatus,
         farm->cornWaterAmount);
  printf("----------------------------------------\n");

  do {
    printf("\n ***** What crop to harvest? ***** \n");
    printf("\n1 for Banana Crops");
    printf("\n2 for Mango Crops");
    printf("\n3 for Corn Crops");
    printf("\nEnter type of crops to water (enter 0 to cancel): ");
    scanf(" %d", &cropType);

    while (cropType > 3 || cropType < 0) {
      printf("\n[ INVALID INPUT ] Enter 1-3 only. (enter 0 to cancel)");
      printf("\nEnter type of crops to sow (enter 0 to cancel): ");
      scanf(" %d", &cropType);
    }

    if (cropType == 0) {
      return;
    }

    // update banana
    if (cropType == 1) {
      // CANCEL CONDITION: check if energy is enough
      if (player->energy < farm->bananaPlots) {
        printf("Not enough energy to harvest %d amount of crops\n",
               farm->bananaPlots);
      }

      if (farm->canHarvestBanana) {
        printf("Bountiful HARVEST!\n");
        printf("You harvested %d crops of banana\n", farm->bananaPlots);
        player->bananaCrops++;
        // update untilledPlots and tilledPlots to amount of plots to harvest
        farm->untilledPlots += farm->bananaPlots;
        farm->tilledPlots -= farm->bananaPlots;
        // update energy
        player->energy -= farm->bananaPlots;
        // update bananaPlots
        farm->bananaPlots = 0;
        // reset harvest flag
        farm->canHarvestBanana = false;
        return;
      }

      // if cannot harvest
      printf("Not enough water to harvest banana crops.\n");
      printf("Your banana crop water status: %d/4\n", farm->bananaWaterAmount);

      return;
    }

    // update mango
    if (cropType == 2) {
      // CANCEL CONDITION: check if energy is enough
      if (player->energy < farm->mangoPlots) {
        printf("Not enough energy to harvest %d amount of crops\n",
               farm->mangoPlots);
      }

      if (farm->canHarvestMango) {
        printf("Bountiful HARVEST!\n");
        printf("You harvested %d crops of mango\n", farm->mangoPlots);
        player->mangoCrops++;
        // update untilledPlots and tilledPlots to amount of plots to harvest
        farm->untilledPlots += farm->mangoPlots;
        farm->tilledPlots -= farm->mangoPlots;
        // update energy
        player->energy -= farm->mangoPlots;
        // update mangoPlots
        farm->mangoPlots = 0;
        // reset harvest flag
        farm->canHarvestMango = false;
        return;
      }

      // if cannot harvest
      printf("Not enough water to harvest mango crops.\n");
      printf("Your mango crop water status: %d/8\n", farm->mangoWaterAmount);

      return;
    }

    // update corn
    if (cropType == 3) {
      // CANCEL CONDITION: check if energy is enough
      if (player->energy < farm->cornPlots) {
        printf("Not enough energy to harvest %d amount of crops\n",
               farm->cornPlots);
      }

      if (farm->canHarvestCorn) {
        printf("Bountiful HARVEST!\n");
        printf("You harvested %d crops of corn\n", farm->cornPlots);
        player->cornCrops++;
        // update untilledPlots and tilledPlots to amount of plots to harvest
        farm->untilledPlots += farm->cornPlots;
        farm->tilledPlots -= farm->cornPlots;
        // update energy
        player->energy -= farm->cornPlots;
        // update cornPlots
        farm->cornPlots = 0;
        // reset harvest flag
        farm->canHarvestCorn = false;
        return;
      }

      // if cannot harvest
      printf("Not enough water to harvest corn crops.\n");
      printf("Your corn crop water status: %d/6\n", farm->cornWaterAmount);

      return;
    }
    // } while (cropType != 0);
  } while (cropType != 0 || cropType < 0);
}

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
      break;
    case 3:
      printf("\nYou chose to water crops!\n");
      waterCrops(player, farm);
      break;
    case 4:
      printf("\nYou chose to harvest crops!\n");
      harvestCrops(player, farm);
      break;
    case 5:
      printf("\nGoing back to main menu...\n");
      break;
    default:
      // checks if int input is valid
      printf("\n[ INVALID INPUT ] Enter numbers 1-5 only.\n");
    }
  } while (playerChoice != 5);
}

/* **************** FARM RELATED FUNCTIONS END ***************** */

/*
 * This function increments the day and resets fields (variables) at the start
 * of the new day
 *
 * Precondition:
 *
 * @param
 *
 * @return
 *
 * */
void goHome(struct PlayerStatus *player, struct FarmStatus *farm,
            bool *isPlayerDead) {

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

    // reset water status for each crop type
    farm->isBananaWatered = false;
    farm->isMangoWatered = false;
    farm->isCornWatered = false;
  }
}

void buySeeds(struct PlayerStatus *player) {
  int seedAmount, seedType;
  int bananaBuyPrice, mangoBuyPrice, cornBuyPrice, finalPrice;

  bananaBuyPrice = 3;
  mangoBuyPrice = 7;
  cornBuyPrice = 5;

  printf("----------------------------------------\n");
  printf("**** Inventory: ****\n");
  printf("Gold: %dG\n", player->gold);
  printf("Banana Seeds (Bag): %d\n", player->bananaSeeds);
  printf("Mango Seeds (Bag): %d\n", player->mangoSeeds);
  printf("Corn Seeds (Bag): %d\n", player->cornSeeds);
  printf("----------------------------------------\n");

  do {
    printf("\n What type of seed do you want to buy?\n");
    printf("Enter 1 ");
    printf("\n1 for Banana Seeds");
    printf("\n2 for Mango Seeds");
    printf("\n3 for Corn Seeds");
    printf("\nEnter number of the type of seed to buy (enter 0 to cancel): ");
    scanf(" %d", &seedType);

    while (seedType > 3 || seedType < 0) {
      printf("\n[ INVALID INPUT ] Enter 1-3 only. (enter 0 to cancel)");
      printf("\nEnter type of seed to buy (enter 0 to cancel): ");
      scanf(" %d", &seedType);
    }

    if (seedType == 0) {
      printf("\nGoing back to main menu...\n");
      return;
    }

    printf("\nEnter amount of bag of seeds to buy: ");
    scanf(" %d", &seedAmount);

    switch (seedType) {
    case 1:
      // banana - 3 gold

      finalPrice = bananaBuyPrice * seedAmount;

      // CANCEL CONDITION: if not have enough gold
      if (player->gold < finalPrice) {
        printf("\nNot enough gold to buy %d bag of seeds\n", seedAmount);
        return;
      }

      printf("\nYou successfully bought %d bag of banana seeds!\n", seedAmount);
      player->gold -= finalPrice;
      printf("-%d gold\n", finalPrice);
      break;
    case 2:
      // mango - 7 gold

      finalPrice = mangoBuyPrice * seedAmount;

      // CANCEL CONDITION: if not have enough gold
      if (player->gold < finalPrice) {
        printf("\nNot enough gold to buy %d bag of seeds", seedAmount);
        return;
      }

      printf("\nYou successfully bought %d bag of mango seeds!\n", seedAmount);
      player->gold -= finalPrice;
      break;
    case 3:
      // corn - 5 gold

      finalPrice = cornBuyPrice * seedAmount;

      // CANCEL CONDITION: if not have enough gold
      if (player->gold < finalPrice) {
        printf("\nNot enough gold to buy %d bag of seeds\n", seedAmount);
        return;
      }

      printf("\nYou successfully bought %d bag of corn seeds!\n", seedAmount);
      player->gold -= finalPrice;
      break;
    default:
      // checks if int input is valid
      printf("\n[ INVALID INPUT ] Enter numbers 1-3 only.\n");
    }

  } while (seedType != 0 || seedType < 0);
}

void sellCrops(struct PlayerStatus *player) {
  int cropsAmount, cropType;
  int bananaSellPrice, mangoSellPrice, cornSellPrice, finalSellPrice;

  bananaSellPrice = 4;
  mangoSellPrice = 10;
  cornSellPrice = 7;

  printf("----------------------------------------\n");
  printf("**** Inventory: ****\n");
  printf("Gold: %dG\n", player->gold);
  printf("Banana Crops (kg): %d\n", player->bananaCrops);
  printf("Mango Crops (kg): %d\n", player->mangoCrops);
  printf("Corn Crops (kg): %d\n", player->cornCrops);
  printf("----------------------------------------\n");

  do {
    printf("\n What type of seed do you want to sell?\n");
    printf("Enter 1 ");
    printf("\n1 for Banana Crops");
    printf("\n2 for Mango Crops");
    printf("\n3 for Corn Crops");
    printf("\nEnter number of the type of crop to sell (enter 0 to cancel): ");
    scanf(" %d", &cropType);

    while (cropType > 3 || cropType < 0) {
      printf("\n[ INVALID INPUT ] Enter 1-3 only. (enter 0 to cancel)");
      printf("\nEnter type of seed to buy (enter 0 to cancel): ");
      scanf(" %d", &cropType);
    }

    if (cropType == 0) {
      printf("\nGoing back to main menu...\n");
      return;
    }

    printf("\nEnter amount of kilograms (kg) of crops to sell: ");
    scanf(" %d", &cropsAmount);

    switch (cropType) {
    case 1:
      // banana - 4 gold

      // CANCEL CONDITION: if don't have enough selected crops
      if (player->bananaCrops < cropsAmount) {
        printf("Not enough banana crops to sell at that amount.\n");
        return;
      }

      player->bananaCrops -= cropsAmount;
      printf("\nYou successfully sold %d kg of banana crops!\n", cropsAmount);

      finalSellPrice = bananaSellPrice * cropsAmount;

      player->gold += finalSellPrice;
      printf("+%d gold acquired.\n", finalSellPrice);
      break;
    case 2:
      // mango - 10 gold

      // CANCEL CONDITION: if don't have enough selected crops
      if (player->mangoCrops < cropsAmount) {
        printf("Not enough mango crops to sell at that amount.\n");
        return;
      }

      player->mangoCrops -= cropsAmount;
      printf("\nYou successfully sold %d kg of mango crops!\n", cropsAmount);

      finalSellPrice = mangoSellPrice * cropsAmount;

      player->gold += finalSellPrice;
      printf("+%d gold acquired.\n", finalSellPrice);
      break;
    case 3:
      // corn - 7 gold

      // CANCEL CONDITION: if don't have enough selected crops
      if (player->cornCrops < cropsAmount) {
        printf("Not enough corn crops to sell at that amount.\n");
        return;
      }

      player->cornCrops -= cropsAmount;
      printf("\nYou successfully sold %d kg of corn crops!\n", cropsAmount);

      finalSellPrice = cornSellPrice * cropsAmount;

      player->gold += finalSellPrice;
      printf("+%d gold acquired.\n", finalSellPrice);
      break;
    default:
      // checks if int input is valid
      printf("\n[ INVALID INPUT ] Enter numbers 1-3 only.\n");
    }

  } while (cropType != 0 || cropType < 0);
}

void goToShop(struct PlayerStatus *player) {
  int playerChoice;
  do {
    printf("\n\n******* Welcome to the Shop! *******\n");
    printf("-------------------------------\n");
    printf("Enter 1 to Buy Seeds\n");
    printf("Enter 2 to Sell Crops\n");
    printf("Enter 3 to Go back to Main Menu\n");
    printf("-------------------------------\n");
    switch (playerChoice) {
    case 1:
      printf("\n\nBuying seeds...\n");
      buySeeds(player);
      break;
    case 2:
      printf("\n\nSelling crops...\n");
      sellCrops(player);
      break;
    case 3:
      printf("\nGoing back to main menu...\n");
      break;
    default:
      // checks if int input is valid
      printf("\n[ INVALID INPUT ] Enter numbers 1-3 only.\n");
    }
  } while (playerChoice != 3);
}

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
  player.bananaCrops = 0;
  player.mangoCrops = 0;
  player.cornCrops = 0;

  struct FarmStatus farm;
  farm.tilledPlots = 0;
  farm.untilledPlots = 30;
  farm.bananaPlots = 0;
  farm.mangoPlots = 0;
  farm.cornPlots = 0;
  farm.isBananaWatered = false;
  farm.isMangoWatered = false;
  farm.isCornWatered = false;
  farm.bananaWaterAmount = 0;
  farm.mangoWaterAmount = 0;
  farm.cornWaterAmount = 0;
  farm.canHarvestBanana = false;
  farm.canHarvestMango = false;
  farm.canHarvestCorn = false;

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
      goHome(&player, &farm, &isPlayerDead);
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
