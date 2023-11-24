#include <stdbool.h>
#include <stdio.h>

/*
 * Description: This program is a strategic game called "HarvestSun", where
 *              you try to survive living in a farm land where unexpected
 *              calamities happen. You have the options to farm, shop (buy
 *              and sell), and to go home for the next day. Balancing resources
 *              is the key! Look out for "calamities" that challenges your very
 *              own tenacity. Play now and see what you're made of.
 * Programmed by:  Sadiarin, Edwin Jr. M., CCPROG1-S19A
 * Last modified: <date when last revision was made>
 * Version: 2
 * [Acknowledgements:
 * - stdbool.h library for boolean types
 * ]
 */

/* The program will end if:
 * (1) when the player starves for 3 consecutive days
 *    - which leads to death due to hunger and thirst
 *    - 4th day inevitable death
 * (2) when the user selects “Quit”.
 * (3) when player did not survive to a calamity (mystery)
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
 * This function displays the main menu options and current of the player.
 * ---
 * @note Precondition: The function assumes that the 'player' parameter is a
 * valid pointer to a struct of type 'PlayerStatus' containing information about
 * the player's current status, including gold, energy, and hunger.
 * ---
 * @param struct PlayerStatus *player: Pointer to a struct PlayerStatus
 * representing the player's status.
 */
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

/**
 * This function checks if the player is dead due to starvation and updates the
 * status. Provides warnings for each starved day.
 * ---
 * @note Precondition: The function assumes that the 'player' parameter is a
 * valid pointer to a struct of type 'PlayerStatus' containing information about
 * the player's current status, including gold and starvation status. The
 * 'isPlayerDead' parameter is a pointer to a boolean flag indicating whether
 * the player is dead.
 * ---
 * @param struct PlayerStatus *player: Pointer to a struct PlayerStatus
 * representing the player's status.
 * @param bool *isPlayerDead: Pointer to a boolean flag indicating whether the
 * player is dead.
 * ---
 * @return Always returns 0. The function modifies the 'isPlayerDead' flag and
 *         provides feedback through console output.
 */
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

int cancelAction(int inputAction) {
  // return 1 if cancelled, otherwise return 0;
  if (inputAction == 0) {
    printf("Cancelling action...\n");
    return 1;
  }
  return 0;
}

/* **************** FARM RELATED FUNCTIONS START ***************** */

/**
 * This function displays the farm status and available actions for the player
 * on the farm.
 * ---
 * @note Precondition: The function assumes that the 'player' and 'farm'
 * parameters are valid pointers to structs of type 'PlayerStatus' and
 * 'FarmStatus,' respectively, containing information about the player's and
 * farm's current status.
 * ---
 * @param struct PlayerStatus *player: Pointer to a struct PlayerStatus
 * representing the player's status.
 * @param struct FarmStatus *farm: Pointer to a struct FarmStatus representing
 * the farm's status.
 */
void displayFarmOptions(struct PlayerStatus *player, struct FarmStatus *farm) {
  char *bananaHarvestStatus =
      farm->bananaWaterAmount == 4 ? "Ready to harvest" : "not yet";
  char *mangoHarvestStatus =
      farm->mangoWaterAmount == 8 ? "Ready to harvest" : "not yet";
  char *cornHavestStatus =
      farm->cornWaterAmount == 6 ? "Ready to harvest" : "not yet";

  printf("\n----------------------------------------\n");
  printf("|    ***** Your Farm Status *****    |\n");
  printf("----------------------------------------\n");
  printf("Energy: %d/30\n", player->energy);
  printf("Gold: %dG\n", player->gold);
  printf("Banana Seeds (Bag): %d\n", player->bananaSeeds);
  printf("Mango Seeds (Bag): %d\n", player->mangoSeeds);
  printf("Corn Seeds (Bag): %d\n", player->cornSeeds);
  printf("Owned Banana Crops (kg): %d\n", player->bananaCrops);
  printf("Owned Mango Crops (kg): %d\n", player->mangoCrops);
  printf("Owned Corn Crops (kg): %d\n", player->cornCrops);
  printf("----------------------------------------\n");
  // show crops here (Banana, Mango, Corn)
  printf("Tilled plots: %d/30\n", farm->tilledPlots);
  printf("Untilled plots: %d/30\n", farm->untilledPlots);
  printf("Planted bananas: %d/30\n", farm->bananaPlots);
  printf("Planted mangoes: %d/30\n", farm->mangoPlots);
  printf("Planted corns: %d/30\n", farm->cornPlots);
  printf("----------------------------------------\n");
  printf("**** Harvest Status: ****\n");
  printf("Banana crops: %s | Water amount: %d/4\n", bananaHarvestStatus,
         farm->bananaWaterAmount);
  printf("Mango crops: %s | Water amount: %d/8\n", mangoHarvestStatus,
         farm->mangoWaterAmount);
  printf("Corn crops: %s | Water amount: %d/6\n", cornHavestStatus,
         farm->cornWaterAmount);
  printf("----------------------------------------\n");
  printf("Enter 1 - Till plots\n");
  printf("Enter 2 - Sow seeds\n");
  printf("Enter 3 - Water crops\n");
  printf("Enter 4 - Harvest crops\n");
  printf("Enter 5 - Go to main menu\n");
  printf("----------------------------------------\n");
}

/**
 * This function tills a specified number of untilled plots on the farm.
 * ---
 * @note Precondition: The function assumes that the 'player' and 'farm'
 * parameters are valid pointers to structs of type 'PlayerStatus' and
 * 'FarmStatus,' respectively, containing information about the player's and
 * farm's current status.
 * ---
 * @param struct PlayerStatus *player: Pointer to a struct PlayerStatus
 * representing the player's status.
 * @param struct FarmStatus *farm: Pointer to a struct FarmStatus representing
 * the farm's status.
 */
void tillPlots(struct PlayerStatus *player, struct FarmStatus *farm) {
  int plotsToTillAmount;
  int exitFlag = 0;

  // do while for error handling
  do {
    // error handle, prompts player again until correct conditions are met
    printf("Enter amount of plots to till (enter 0 to cancel): ");
    scanf(" %d", &plotsToTillAmount);

    while (plotsToTillAmount < 0) {
      printf("\n[ INVALID INPUT ] Your input amount is less than 0.\n");
      printf("Enter amount of plots to till (enter 0 to cancel): ");
      scanf(" %d", &plotsToTillAmount);
    }

    if (plotsToTillAmount == 0) {
      exitFlag = cancelAction(exitFlag);
    } else {
      // check if farm have enough untilledPlots to be tilledPlots
      if (farm->untilledPlots < plotsToTillAmount) {
        printf("\nNot enough untilled plots to till\n");
      }
      // check if player have enough energy
      if (player->energy < plotsToTillAmount) {
        printf("Energy is not sufficient.\n");
      }
      // if all conditions are met
      else {
        // terminate loop if conditions are met
        exitFlag = 1;

        // if player has enough energy then energy - plotsToTill
        player->energy -= plotsToTillAmount;

        // update tilledPlots based on plotsToTill input from player
        farm->tilledPlots += plotsToTillAmount;

        // update untilledPlots (subtract to how many are now tilledPlots)
        farm->untilledPlots -= plotsToTillAmount;
        printf("\nNOTICE: Farm has been updated\n");
      }
    }
  } while (!exitFlag);
}

/**
 * This function sows seeds on tilled plots in the farm.
 * ---
 * @note Precondition: The function assumes that the 'player' and 'farm'
 * parameters are valid pointers to structs of type 'PlayerStatus' and
 * 'FarmStatus,' respectively, containing information about the player's and
 * farm's current status.
 * ---
 * @param struct PlayerStatus *player: Pointer to a struct PlayerStatus
 * representing the player's status.
 * @param struct FarmStatus *farm: Pointer to a struct FarmStatus representing
 * the farm's status.
 */
void sowSeeds(struct PlayerStatus *player, struct FarmStatus *farm) {
  int seedsToSowAmount, seedType;
  int exitFlag = 0;

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
  }
  // if there are tilled plots proceed...
  else {
    do {
      // check type of seed to sow
      printf("\n ***** What type of seed? ***** \n");
      printf("\n1 for Banana Seeds");
      printf("\n2 for Mango Seeds");
      printf("\n3 for Corn Seeds");
      printf("\nEnter type of seed to sow (enter 0 to cancel): ");
      scanf(" %d", &seedType);

      // input validation
      while (seedType > 3 || seedType < 0) {
        printf("\n[ INVALID INPUT ] Enter 1-3 only. (enter 0 to cancel)");
        printf("\nEnter type of seed to sow (enter 0 to cancel): ");
        scanf(" %d", &seedType);
      }

      if (seedType == 0) {
        exitFlag = cancelAction(exitFlag);
      }
      // do action if not cancelled
      else {
        printf("\nEnter amount of seeds to sow: ");
        scanf(" %d", &seedsToSowAmount);

        // input validation
        while (seedsToSowAmount < 0) {
          printf("\n[ INVALID INPUT ] Your input amount is less than 0.");
          printf("\nEnter amount of seeds to sow: ");
          scanf(" %d", &seedsToSowAmount);
        }

        // CANCEL CONDITION: check if tilledPlots are enough
        if (seedsToSowAmount > farm->tilledPlots) {
          printf("Not enough tilled plots to sow %d seeds\n", seedsToSowAmount);
        }
        // do action for selected seed
        else {

          // banana seeds
          if (seedType == 1) {
            // CANCEL CONDITION: check if type of seed are already sown
            if (farm->bananaPlots > 0) {
              printf("Banana seeds are already sown. Harvest them first.\n");
              exitFlag = 1;
            }
            // CANCEL CONDITION: check if owned banana seeds are enough
            else if (seedsToSowAmount > player->bananaSeeds) {
              printf("Not enough bag of banana seeds.\n");
              printf("Buy in shop first.\n");
              exitFlag = 1;
            }
            // CANCEL CONDITION: check if energy is enough
            else if (seedsToSowAmount > player->energy) {
              printf("Not enough energy to sow %d banana seeds\n",
                     seedsToSowAmount);
              exitFlag = 1;
            }
            // if all conditions are met:
            else {
              // update bananaPlots
              farm->bananaPlots += seedsToSowAmount;
              // update bananaSeeds
              player->bananaSeeds -= seedsToSowAmount;
              if (player->bananaSeeds < 0) {
                player->bananaSeeds = 0;
              }
              // update energy
              player->energy -= seedsToSowAmount;
              printf("\nNOTICE: Farm has been updated\n");
              exitFlag = 1;
            }
          }

          // mango seeds
          if (seedType == 2) {
            // CANCEL CONDITION: check if type of seed are already sown
            if (farm->mangoPlots > 0) {
              printf("Mango seeds are already sown. Harvest them first.\n");
              exitFlag = 1;
            }
            // CANCEL CONDITION: check if owned mango seeds are enough
            else if (seedsToSowAmount > player->mangoSeeds) {
              printf("Not enough bag of mango seeds.\n");
              printf("Buy in shop first.\n");
              exitFlag = 1;
            }
            // CANCEL CONDITION: check if energy is enough
            else if (seedsToSowAmount > player->energy) {
              printf("Not enough energy to sow %d mango seeds\n",
                     seedsToSowAmount);
              exitFlag = 1;
            }
            // if all conditions are met:
            else {
              // update mangoPlots
              farm->mangoPlots += seedsToSowAmount;
              // update mangoSeeds
              player->mangoSeeds -= seedsToSowAmount;
              if (player->mangoSeeds < 0) {
                player->mangoSeeds = 0;
              }
              // update energy
              player->energy -= seedsToSowAmount;
              printf("\nNOTICE: Farm has been updated\n");
              exitFlag = 1;
            }
          }

          // corn seeds
          if (seedType == 3) {
            // CANCEL CONDITION: check if type of seed are already sown
            if (farm->cornPlots > 0) {
              printf("Corn seeds are already sown. Harvest them first.\n");
              exitFlag = 1;
            }
            // CANCEL CONDITION: check if owned corn seeds are enough
            else if (seedsToSowAmount > player->cornSeeds) {
              printf("Not enough bag of corn seeds.\n");
              printf("Buy in shop first.\n");
              exitFlag = 1;
            }
            // CANCEL CONDITION: check if energy is enough
            else if (seedsToSowAmount > player->energy) {
              printf("Not enough energy to sow %d corn seeds\n",
                     seedsToSowAmount);
              exitFlag = 1;
            }
            // if all conditions are met:
            else {
              // update cornPlots
              farm->cornPlots += seedsToSowAmount;
              // update cornSeeds
              player->cornSeeds -= seedsToSowAmount;
              if (player->cornSeeds < 0) {
                player->cornSeeds = 0;
              }
              // update energy
              player->energy -= seedsToSowAmount;
              printf("\nNOTICE: Farm has been updated\n");
              exitFlag = 1;
            }
          }
        }
      }
    } while (exitFlag == 0);
  }
}

/**
 * This function waters crops in the farm based on the player's choice.
 * ---
 * @note Precondition: The function assumes that the 'player' and 'farm'
 * parameters are valid pointers to structs of type 'PlayerStatus' and
 * 'FarmStatus,' respectively, containing information about the player's and
 * farm's current status.
 * ---
 * @param struct PlayerStatus *player: Pointer to a struct PlayerStatus
 * representing the player's status.
 * @param struct FarmStatus *farm: Pointer to a struct FarmStatus representing
 * the farm's status.
 */
void waterCrops(struct PlayerStatus *player, struct FarmStatus *farm) {
  int cropType;
  int exitFlag = 0;

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

  if (allWatered) {
    printf("All types of crops are watered. See you tomorrow\n");
  }
  // if there are crops available to water proceed...
  else {
    do {

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
        exitFlag = cancelAction(exitFlag);
      } else {

        // banana crops
        if (cropType == 1) {
          // CANCEL CONDITION: check if selected cropType is watered
          if (farm->isBananaWatered == true) {
            printf("\n\nBanana crops are already watered for the day.\n");
            printf("Go to the next day to water the same type of crop\n");
            exitFlag = 1;
          }
          // CANCEL CONDITION: check if there are planted bananas
          else if (farm->bananaPlots <= 0) {
            printf("\n\nThere are no planted banana plots to water.\n");
            exitFlag = 1;
          }
          // CANCEL CONDITION: check if energy is enough
          else if (player->energy < farm->bananaPlots) {
            printf("\n\nNot enough energy to water %d amount of crops\n",
                   farm->bananaPlots);
            exitFlag = 1;
          }
          // if all conditions are met:
          else {
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

            exitFlag = 1;
          }
        }

        // mango crops
        if (cropType == 2) {
          // CANCEL CONDITION: check if selected cropType is watered
          if (farm->isMangoWatered == true) {
            printf("\n\nMango crops are already watered for the day.\n");
            printf("Go to the next day to water the same type of crop\n");
            exitFlag = 1;
          }
          // CANCEL CONDITION: check if there are planted mangoes
          else if (farm->mangoPlots <= 0) {
            printf("\n\nThere are no planted mango plots to water.\n");
            exitFlag = 1;
          }
          // CANCEL CONDITION: check if energy is enough
          else if (player->energy < farm->mangoPlots) {
            printf("\n\nNot enough energy to water %d amount of crops\n",
                   farm->mangoPlots);
            exitFlag = 1;
          }
          // if all conditions are met:
          else {
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

            exitFlag = 1;
          }
        }

        // corn crops
        if (cropType == 3) {
          // CANCEL CONDITION: check if selected cropType is watered
          if (farm->isCornWatered == true) {
            printf("\n\nCorn crops are already watered for the day.\n");
            printf("Go to the next day to water the same type of crop\n");
            exitFlag = 1;
          }
          // CANCEL CONDITION: check if there are planted corns
          else if (farm->cornPlots <= 0) {
            printf("\n\nThere are no planted corn plots to water.\n");
            exitFlag = 1;
          }
          // CANCEL CONDITION: check if energy is enough
          else if (player->energy < farm->bananaPlots) {
            printf("\n\nNot enough energy to water %d amount of crops\n",
                   farm->bananaPlots);
            exitFlag = 1;
          }
          // if all conditions are met:
          else {
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

            exitFlag = 1;
          }
        }
      }
    } while (exitFlag == 0);
  }
}

/**
 * This function harvests crops in the farm based on the player's choice.
 * ---
 * @note Precondition: The function assumes that the 'player' and 'farm'
 * parameters are valid pointers to structs of type 'PlayerStatus' and
 * 'FarmStatus,' respectively, containing information about the player's and
 * farm's current status.
 * ---
 * @param struct PlayerStatus *player:  Pointer to a struct PlayerStatus
 * representing the player's status.
 * @param struct FarmStatus *farm: Pointer to a struct FarmStatus representing
 * the farm's status.
 */
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

/**
 * This function enters the farm management interface and allows the player to
 * perform various actions.
 * ---
 * @note Precondition: The function assumes that the 'player' and 'farm'
 * parameters are valid pointers to structs of type 'PlayerStatus' and
 * 'FarmStatus,' respectively, containing information about the player's and
 * farm's current status.
 * ---
 * @param struct PlayerStatus *player: Pointer to a struct PlayerStatus
 * representing the player's status.
 * @param struct FarmStatus *farm: Pointer to a struct FarmStatus representing
 * the farm's status.
 */
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

/**
 * This function simulates the player going home, advancing to the next day, and
 * handling daily tasks such as resetting energy, taxing gold for breakfast, and
 * updating crop watering status on the farm. It also checks if the player is
 * dead due to starvation using the 'checkIfDead' function.
 * ---
 * @note Precondition: The function assumes that the 'player' parameter is a
 * valid pointer to a struct of type 'PlayerStatus' containing information about
 * the player's current status, including gold, energy, and day. The 'farm'
 * parameter is a pointer to a struct 'FarmStatus' containing information about
 * crop watering. The 'isPlayerDead' parameter is a pointer to a boolean flag
 * indicating whether the player is dead.
 * ---
 * @param struct PlayerStatus *player: Pointer to a struct PlayerStatus
 * representing the player's status.
 * @param struct FarmStatus *farm: Pointer to a struct FarmStatus representing
 * the farm's status.
 * @param isPlayerDead Pointer to a boolean flag indicating whether the player
 * is dead.
 */
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

/**
 * This function allows the player to buy seeds of different types based on user
 * input. It updates the player's inventory and gold based on the type and
 * amount of seeds purchased.
 * ---
 * @note Precondition: The function assumes that the 'player' parameter is a
 * valid pointer to a struct of type 'PlayerStatus' containing information about
 * the player's current status, including gold and seed inventories.
 * ---
 * @param struct PlayerStatus *player: Pointer to a struct PlayerStatus
 * representing the player's status.
 */
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
    printf("\n1 for Banana Seeds (costs 3 gold)");
    printf("\n2 for Mango Seeds (costs 7 gold)");
    printf("\n3 for Corn Seeds (costs 5 gold)");
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

      player->bananaSeeds += seedAmount;
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
      printf("-%d gold\n", finalPrice);

      player->mangoSeeds += seedAmount;
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
      printf("-%d gold\n", finalPrice);

      player->cornSeeds += seedAmount;
      break;
    default:
      // checks if int input is valid
      printf("\n[ INVALID INPUT ] Enter numbers 1-3 only.\n");
    }

  } while (seedType != 0 || seedType < 0);
}

/**
 * This function allows the player to sell crops of different types based on
 * user input. It updates the player's inventory, specifically the crop
 * quantities and gold, based on the type and amount of crops sold.
 * ---
 * @note Precondition: The function assumes that the 'player' parameter is a
 * valid pointer to a struct of type 'PlayerStatus' containing information about
 * the player's current status, including gold and crop inventories.
 * ---
 * @param struct PlayerStatus *player: Pointer to a struct PlayerStatus
 * representing the player's status.
 */
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
    printf("\n1 for Banana Crops (sold for 4 gold)");
    printf("\n2 for Mango Crops (sold for 10 gold)");
    printf("\n3 for Corn Crops (sold for 7 gold)");
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

/**
 * This function allows the player to interact with the in-game shop for buying
 * seeds or selling crops.
 * ---
 * @note Precondition: The function assumes that the 'player' parameter is a
 * valid pointer to a struct of type 'PlayerStatus' containing information about
 * the player's current status, including gold, seed, and crop inventories.
 * ---
 * @param struct PlayerStatus *player: Pointer to a struct PlayerStatus
 * representing the player's status.
 */
void goToShop(struct PlayerStatus *player) {
  int playerChoice;
  do {
    printf("\n\n******* Welcome to the Shop! *******\n");
    printf("-------------------------------\n");
    printf("Enter 1 to Buy Seeds\n");
    printf("Enter 2 to Sell Crops\n");
    printf("Enter 3 to Go back to Main Menu\n");
    printf("-------------------------------\n");
    printf("\nEnter number of the action you want to do: ");
    scanf(" %d", &playerChoice);

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

/**
 * The main function for the Harvest Sun game.
 *
 * This function initializes the player and farm status, displays the welcome
 * message, and provides a menu for the player to choose actions such as going
 * home, going to the farm, going to the shop, or quitting the game. It calls
 * corresponding functions for each action and continues until the player
 * chooses to quit or the player's character dies.
 * ---
 * @note Precondition: The function initializes the player and farm structures
 * and uses various other functions (e.g., 'displayMainMenuOptions', 'goHome',
 * 'goToFarm', 'goToShop') to handle different game actions.
 * ---
 * @return The function returns 0 upon successful execution.
 */
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
      goToShop(&player);
      break;
    case 4:
      printf("\nThank you for playing Harvest Sun!\n");
      break;
    default:
      printf("\n[ INVALID INPUT ] Enter numbers 1-4 only.\n");
    }
  } while (playerChoice != 4 && isPlayerDead == false);

  return 0;
}
