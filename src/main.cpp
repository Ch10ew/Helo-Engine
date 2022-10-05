#include <SFML/Graphics.hpp>

#include "Core/CoreGameData.hpp"
#include "Core/Game.hpp"
#include "Core/GameState.hpp"
#include "TicTacToe/SplashScreenState.hpp"

#include <memory>

int main()
{
    he::Game game("test title");
    game.SetInitialState(std::unique_ptr<he::GameState>(new ttt::SplashScreenState()));
    game.Run();

    return 0;
}
