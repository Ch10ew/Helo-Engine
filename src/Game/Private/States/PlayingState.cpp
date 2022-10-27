#include "States/PlayingState.hpp"

namespace ttt
{
    PlayingState::PlayingState()
    {
    }

    void PlayingState::ProcessInput(sf::Event event)
    {
    }

    void PlayingState::Update(float dt)
    {
    }

    void PlayingState::Render(float dt)
    {
    }

    void PlayingState::Init()
    {
        _yourPiece = ttt::Piece::X;
    }

    void PlayingState::Pause()
    {
    }

    void PlayingState::Resume()
    {
    }
} // namespace ttt
