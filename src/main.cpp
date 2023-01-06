#include <SFML/Graphics.hpp>

#include "Core/CoreGameData.hpp"
#include "Core/Game.hpp"
#include "Core/GameState.hpp"
#include "States/SplashScreenState.hpp"

#include <memory>

int main()
{
    he::Game game(800, 800, "test title");
    game.SetInitialState(std::unique_ptr<he::GameState>(new ttt::SplashScreenState()));
    game.Run();

    return 0;
}
