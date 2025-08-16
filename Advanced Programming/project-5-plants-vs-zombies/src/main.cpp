#include "../includes/system.hpp"

int main(){
    System* game = new System(WIDTH, HEIGHT);
    game->start();
    delete game;
    return 0;
}