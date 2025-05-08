#ifndef TTT_PLAYING_STATE_HPP
#define TTT_PLAYING_STATE_HPP

#include "AssetManager/Assets.hpp"
#include "Core/CoreGameData.hpp"
#include "Core/GameState.hpp"
#include "Components/ClickableComponent.hpp"

#include "Scripts/BoardUpdater.hpp"
#include "TicTacToe/Board.hpp"

#include <SFML/Graphics.hpp>

#include <map>

namespace ttt
{
    class PlayingState : public he::GameState
    {
    public:
        PlayingState();

    public:
        void ProcessInput(sf::Event& event);
        void Update(float dt);
        void FixedUpdate(float dt);

    public:
        void Init();
        void Pause();
        void Resume();

    private:
        he::CoreGameData* _coreGameData;
        he::Assets* _assets;

    private:
        Board* _board;
        std::shared_ptr<ttt::BoardUpdater> boardUpdater;

    private:
        ttt::Piece _yourPiece;
        std::map<int, std::shared_ptr<he::ClickableComponent>> _pieceClickableComponentMap;

    private:
        sf::Clock _clock;
    };
} // namespace ttt

#endif // TTT_PLAYING_STATE_HPP
