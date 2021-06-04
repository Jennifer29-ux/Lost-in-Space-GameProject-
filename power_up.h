#ifndef LOST_IN_SPACE_POWER_UP
#define LOST_IN_SPACE_POWER_UP

enum power_up_options
{
    FUEL ,
    SHEILD,
    STAR,
    COIN,
    BATTERY,
    HEART
};
/**
 *  Using power_up struct to show power up
*   Using power up sprite to show the visual representation for power up
*   Using options to show what kind of power up it is
*/

struct power_up_data
{
    sprite power_up_sprite;
    power_up_options options;
};
/**
 * Initiate the power up and arrives at power up
 */
power_up_data new_power_up(double x, double y);

/**
* Draws the new power up to the screen
*
* @param power_up_draw   The powerup to draw to the screen
*/
void draw_power_up(const power_up_data &power_up_draw);

/**
 * Update of the power up by taking a step measure
 * 
 * @param power_up_update  The powerup is updated
 */
void update_power_up(power_up_data &power_up_update);

#endif
