#include "splashkit.h"
#include "power_up.h"

using std::string;
using namespace std;

/**
 * The power_up bitmap function converts a power_up options into a
 * bitmap that can be used.
 *
 * Not exposed by the header.
 *
 * @param options  The kind of ship you want the bitmap of
 * @return      The bitmap matching this power-up
 */
bitmap power_up_bitmap(power_up_options options)
{
  switch (options)
  {
  case FUEL:
    return bitmap_named("fuel");
  case SHEILD:
    return bitmap_named("shield");
  case STAR:
    return bitmap_named("star");
  case COIN:
    return bitmap_named("coin");
  case BATTERY:
    return bitmap_named("battery");
  case HEART:
    return bitmap_named("heart");
  default:
   return bitmap_named("fuel");
  }
}
power_up_data new_power_up(double x, double y)
{
  power_up_data result;
  //construct the sprite for new power up
  result.options = static_cast<power_up_options>(rnd(6));
  result.power_up_sprite = create_sprite(power_up_bitmap(result.options));

  //coordinate the position of power up in the desiginated x,y positions
  sprite_set_x(result.power_up_sprite, x);
  sprite_set_y(result.power_up_sprite, y);

  //commence power up small stochastic velcoity
  sprite_set_dx(result.power_up_sprite, rnd() * 4 - 2);
  sprite_set_dy(result.power_up_sprite, rnd() * 4 - 2);
  //write_line(sprite_dx(result.power_up_sprite));

  return result;
}

void draw_power_up( const power_up_data &power_up_draw)
{
  draw_sprite(power_up_draw.power_up_sprite);
}
void update_power_up(power_up_data &power_up_update)
{
  update_sprite(power_up_update.power_up_sprite);
}