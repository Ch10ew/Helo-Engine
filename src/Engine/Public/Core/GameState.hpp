#ifndef HE_GAME_STATE_HPP
#define HE_GAME_STATE_HPP

#include <SFML/Graphics.hpp>

namespace he
{
    /**
     * Abstract class for game states.
     *
     * Inherit from this class to make a game state.
     */
    class GameState
    {
    public:
        GameState(){};
        GameState(const GameState&) = delete;
        GameState& operator=(const GameState&) = delete;

    public:
        virtual void ProcessInput(sf::Event) = 0;
        virtual void Update(float) = 0;
        virtual void Render(float) = 0;

    public:
        virtual void Init() = 0;
        virtual void Pause(){};
        virtual void Resume(){};
    };
} // namespace he

#endif // HE_GAME_STATE_HPP
