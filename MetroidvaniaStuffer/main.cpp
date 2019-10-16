#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Game.hpp"
#include "Window.hpp"

using namespace std;

int main(int, char const**)
{
    Game game;
    
    while(game.isRunning())
    {
        game.captureInput();
        game.update();
        game.lateUpdate();
        game.draw();
        game.calculateDeltaTime();
    }
    return 0;
}
