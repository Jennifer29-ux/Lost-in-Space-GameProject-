#ifndef LOST_IN_SPACE_
#define LOST_IN_SPACE_

#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include <vector>

using namespace std;
using std::vector;

struct game_data
{
  player_data player;
  vector<power_up_data> power_ups;
};
/**
 * Creates a new game 
 * 
 * @returns     The new game data
**/
game_data new_game();
/**
 * Draws the game to the screen. 
 * 
 * @param game_draw    The player to draw to the screen
 */
void draw_game(const game_data &game_draw);

/**
 * Actions a step update of the game.
 * 
 * @param game_to_update      The game being updated
 */
void update_game(game_data &game_to_update);
/**
 * Add a power up to the game.
 * 
 * @param game      The game to which power up is to be added
 */
void add_power_up(game_data &game);
/**
 * Apply the feature of the power up to the player after collision
 * 
 * @param game      The game 
 * @param powerup_kind  Power up which has to applied
 */
void apply_power_up(game_data &game, power_up_data &power_up);
/**
 * Removes the a specific power up from the power ups vector
 * 
 * @param power_ups      vector of all the power ups
 * @param index            Index of the power up which has to be removed 
 */
void remove_power_up(vector<power_up_data> &power_ups, int i);
/**
 * Checks the collision between player's ship and power up
 * 
 * @param game      The game for which collision has to checked
 */
void check_collision(game_data &game);
/**
 * Draws the heads up display for the game
 * 
 * @param g      The game for which heads up display is to be drawn
 */
void draw_hud(const game_data &g);

/**
 * Draws the Mini Map of all power ups inside Heads Up Display
 * 
 * @param game      The vector of all power ups for which for which mini map has to be created
 */
void draw_mini_map(const vector<power_up_data> &power_ups);

#endif