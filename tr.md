
  /* MainMenu
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
