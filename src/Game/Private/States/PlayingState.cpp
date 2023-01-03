#include "States/PlayingState.hpp"

#include "Components/SpriteRendererComponent.hpp"
#include "Core/Entity.hpp"
#include "TicTacToe/Board.hpp"

namespace ttt
{
    PlayingState::PlayingState()
    {
    }

    void PlayingState::Update(float dt)
    {
    }

    void PlayingState::FixedUpdate(float dt)
    {
    }

    void PlayingState::Init()
    {
        // Get pointers
        _coreGameData = he::CoreGameData::GetInstance();
        _assets = he::Assets::GetInstance();

        // Load assets
        _assets->textureManager.Load("grid", "data/grid.png");
        _assets->textureManager.Load("pieces", "data/pieces.png");

        // Clear the entity manager
        _coreGameData->GetInstance()->entityManager.Clear();

        // Create entity for the playfield grid
        std::shared_ptr<he::SpriteRendererComponent> srcGrid = std::make_shared<he::SpriteRendererComponent>("srcGrid");
        srcGrid->sprite.setTexture(_assets->textureManager.Get("grid"));
        std::shared_ptr<he::Entity> grid = std::make_shared<he::Entity>("grid1");
        grid->AddComponent(srcGrid);
        grid->transform.position = sf::Vector2f(srcGrid->sprite.getGlobalBounds().width / 2, srcGrid->sprite.getGlobalBounds().height / 2);
        _coreGameData->GetInstance()->entityManager.AddEntity(grid);

        // Create entities for each square in the playfield
        std::shared_ptr<he::SpriteRendererComponent> src1 = std::make_shared<he::SpriteRendererComponent>("src1");
        src1->sprite.setTexture(_assets->textureManager.Get("pieces"));
        src1->sprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
        std::shared_ptr<he::Entity> grid1 = std::make_shared<he::Entity>("grid1");
        grid1->AddComponent(src1);
        grid1->transform.position = sf::Vector2f(30, 30);
        _coreGameData->GetInstance()->entityManager.AddEntity(grid1);

        // Backend setup
        _board.ResetBoard();
        _yourPiece = ttt::Piece::X;
    }

    void PlayingState::Pause()
    {
    }

    void PlayingState::Resume()
    {
    }
} // namespace ttt
