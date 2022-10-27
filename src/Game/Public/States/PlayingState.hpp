#ifndef TTT_PLAYING_STATE_HPP
#define TTT_PLAYING_STATE_HPP

#include "AssetManager/Assets.hpp"
#include "Core/CoreGameData.hpp"
#include "Core/GameState.hpp"
#include "TicTacToe/Board.hpp"

#include <SFML/Graphics.hpp>

namespace ttt
{
    class PlayingState : public he::GameState
    {
    public:
        PlayingState();

    public:
        void ProcessInput(sf::Event event);
        void Update(float dt);
        void Render(float dt);

    public:
        void Init();
        void Pause();
        void Resume();

    private:
        he::CoreGameData* _coreGameData;
        he::Assets* _assets;

    private:
        Board _board;

    private:
        sf::Sprite _piece;
        ttt::Piece _yourPiece;

    private:
        sf::Clock _clock;
    };
} // namespace ttt

#endif // TTT_PLAYING_STATE_HPP
