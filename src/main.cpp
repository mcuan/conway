#include "game_engine.hpp"

int main(int argc, char* argv[]) {

    GameEngine game(SCREEN_WIDTH/SCALE_FACTOR, SCREEN_HEIGHT/SCALE_FACTOR);

    if (game.Construct(SCREEN_WIDTH, SCREEN_HEIGHT, PIXEL_SIZE, PIXEL_SIZE)) {
        game.Start();
    }

    return 0;
}
