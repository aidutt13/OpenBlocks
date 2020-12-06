#define OLC_PGE_APPLICATION

#include "GameCore.hpp"

int main() {

    GameCore game;

    if (game.Construct(512, 512, 1, 1))
        game.Start();

    return 0;
}