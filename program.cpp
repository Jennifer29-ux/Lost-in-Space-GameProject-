#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include "lost_in_space.h"


using std::string;
using namespace std;

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

int main()
{

    open_window("Lost In Space", 800, 800);
    load_resources();
    

    // creating a new game
    game_data game;
    game = new_game();
    add_power_up(game);

    while ( not quit_requested() )
    {
         // Redraw everything
        //clear_screen(COLOR_PLUM);

        // Handle input to adjust player movement
        process_events();
        handle_input(game.player);

        // Perform movement and update the game
        update_game(game);

        // draws the game
        draw_game(game);

    }

    return 0;
}