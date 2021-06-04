#include "splashkit.h"
#include "lost_in_space.h"
#include "player.h"
#include "power_up.h"

#include "vector"

using std::vector;
using namespace std;

const int MIN = -1500;
const int MAX = 1500;

game_data new_game()
{
    game_data new_game;
    new_game.player = new_player();
    return new_game;
}
void add_power_up(game_data &game)
{
    power_up_data new_power_up1;

    double x = (rand() % (MAX - MIN + 1)) + MIN;
    double y = (rand() % (MAX - MIN + 1)) + MIN;
    new_power_up1 = new_power_up(x, y);
    game.power_ups.push_back(new_power_up1);
}
void remove_power_up(vector<power_up_data> &power_ups, int index)
{
    int last = power_ups.size() - 1;
    power_ups[index] = power_ups[last];
    power_ups.pop_back();
}

point_2d mini_map_coordinate(const power_up_data &po)
{
    point_2d temp;
    float x = sprite_x(po.power_up_sprite);
    float y = sprite_y(po.power_up_sprite);
    double mini_map_x((x + 1500) / 3000 * 100 + 10);
    double mini_map_y((y + 1500) / 3000 * 100 + 10);
    temp = point_at(mini_map_x, mini_map_y);
    return temp;
}
void draw_minimap(const vector<power_up_data> &power_ups)
{
    for (int i = power_ups.size() - 1; i >= 0; i--)
    {
        point_2d temp;
        temp = mini_map_coordinate(power_ups[i]);
        draw_pixel(COLOR_BLUE, temp, option_to_screen());
    }
}

void apply_power_up(game_data &g, power_up_data &power_up)
{
    switch (power_up.options)
    {
    case FUEL:
        g.player.fuel_pct = 1;
        break;

    case SHEILD:
        g.player.shield_str = 1;
        break;

    case BATTERY:
        g.player.battery++;
        break;

    case STAR:
        if (g.player.star < 0.75)
        {
            g.player.star = g.player.star * 1.25;
        }
        break;

    case COIN:
        g.player.coins++;
        break;

    case HEART:
        g.player.heart = 1;
        break;
    }
}
void draw_player_in_map(const player_data &player)
{
    point_2d player_coordinate;
    color for_player;
    for_player = COLOR_BLACK;
    player_coordinate = point_at(((sprite_x(player.player_sprite) + 1500) / 3000 * 100 + 10), ((sprite_y(player.player_sprite) + 1500) / 3000 * 100 + 10));
    if (sprite_x(player.player_sprite) < MAX && sprite_x(player.player_sprite) > MIN && sprite_y(player.player_sprite) < 1500 && sprite_y(player.player_sprite) > -1500)
    {
        draw_pixel(for_player, player_coordinate, option_to_screen());
    }
}
void draw_hud(const game_data &g)
{
    // Redraw everything
    //clear_screen(COLOR_WHITE_SMOKE);
    //background for the minimap bar
    fill_rectangle(COLOR_PLUM, 0, 0, 150, 150, option_to_screen());
    //displaying  for the minimap
    draw_minimap(g.power_ups);
    draw_player_in_map(g.player);

    draw_text("LOCATION: " + point_to_string(center_point(g.player.player_sprite)), COLOR_WHITE, 200, 30, option_to_screen());
    draw_text("SCORE: ", COLOR_WHITE, 200, 10, option_to_screen());
    //draw_text(to_string(game.player.score), COLOR_WHITE, 0, 10, option_to_screen());

    //displaying  for fuel
    draw_text("FUEL: ", COLOR_WHITE, 200, 60, option_to_screen());
    load_bitmap("empty", "empty.png");
    draw_bitmap("empty", 300, 40, option_to_screen());
    load_bitmap("full", "full.png");
    draw_bitmap("full", 300, 40, option_part_bmp(0, 0, bitmap_width("full") * g.player.fuel_pct, bitmap_height("full"), option_to_screen()));
    //displaying for battery level
    draw_text("BATTERY LEVEL: ", COLOR_WHITE, 200, 100, option_to_screen());
    load_bitmap("Batterylevel", "blue_bar_bubbles.png");
    draw_bitmap("Batterylevel", 300, 80, option_to_screen());
}
void check_collision(game_data &game)
{
    bool check_player;

    for (int i = game.power_ups.size() - 1; i >= 0; i--)
    {

        check_player = sprite_collision(game.power_ups[i].power_up_sprite, game.player.player_sprite);
        if (check_player)
        {
            apply_power_up(game, game.power_ups[i]);
            remove_power_up(game.power_ups, i);
            add_power_up(game);
        }
        // if (rnd() < 10)
        // {
        //     add_power_up(game);
        // }
        // game.player.score += 5;
    }
}
void draw_game(const game_data &game_draw)
{
    int n;
    int i;
    clear_screen(COLOR_BLACK);

    draw_player(game_draw.player);

    n = game_draw.power_ups.size();
    draw_hud(game_draw);
    for (i = 0; i < n; i++)
    {
        draw_power_up(game_draw.power_ups[i]);
    }

    refresh_screen(60);
}
void update_game(game_data &game_to_update)
{
    int n;
    int i;

    update_player(game_to_update.player);

    // while (rnd() < 0.75)
    // {
    //     if (game_to_update.power_ups.size() < 6)
    //     {
    //         add_power_up(game_to_update);
    //     }
    // }
    // do
    // {
    if (rnd() < 0.05)
        add_power_up(game_to_update);

    // } while (game_to_update.power_ups.size() < 6);

    n = game_to_update.power_ups.size();
    for (i = 0; i < n; i++)
    {
        update_power_up(game_to_update.power_ups[i]);
    }
    check_collision(game_to_update);
}
