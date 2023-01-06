#include "States/PlayingState.hpp"

#include "Components/AudioListenerComponent.hpp"
#include "Components/AudioSourceComponent.hpp"
#include "Components/ClickableComponent.hpp"
#include "Components/ColliderComponent.hpp"
#include "Components/SpriteRendererComponent.hpp"
#include "Core/Entity.hpp"
#include "Core/Wrapper/CallbackFunction.hpp"
#include "Core/Wrapper/CallbackMethod.hpp"
#include "Scripts/BoardUpdater.hpp"
#include "TicTacToe/Board.hpp"

namespace ttt
{
    PlayingState::PlayingState()
    {
    }

    void PlayingState::Update(float dt)
    {
        if (!_board->IsPlaying())
        {
            /*_coreGameData->window.close();
            for (int i = 0; i < 9; ++i)
            {
                he::ClickableComponent* cc = dynamic_cast<he::ClickableComponent*>(_coreGameData->GetInstance()->entityManager.GetComponentById("cc" + std::to_string(i + 1)));
                if (cc)
                {
                    cc->enabled = false;
                }
            }*/
        }
    }

    void PlayingState::FixedUpdate(float dt)
    {
    }

    void PlayingState::Init()
    {
        // Get pointers
        _coreGameData = he::CoreGameData::GetInstance();
        _assets = he::Assets::GetInstance();
        _board = Board::GetInstance();

        // Load assets
        _assets->textureManager.Load("grid", "data/Sprites/grid.png");
        _assets->textureManager.Load("pieces", "data/Sprites/pieces.png");
        _assets->soundManager.Load("click", "data/Audio/click.wav");

        // Clear the entity manager
        _coreGameData->GetInstance()->entityManager.Clear();

        // Create entity for the playfield grid
        std::shared_ptr<he::SpriteRendererComponent> srcGrid = std::make_shared<he::SpriteRendererComponent>("srcGrid");
        srcGrid->sprite.setTexture(_assets->textureManager.Get("grid"));
        std::shared_ptr<he::AudioListenerComponent> alcGrid = std::make_shared<he::AudioListenerComponent>("alcGrid");
        std::shared_ptr<he::ColliderComponent> colGrid = std::make_shared<he::ColliderComponent>("colGrid");
        std::shared_ptr<he::Entity> grid = std::make_shared<he::Entity>("grid");
        grid->AddComponent(srcGrid);
        grid->AddComponent(alcGrid);
        grid->AddComponent(colGrid);
        grid->transform.position = sf::Vector2f(srcGrid->sprite.getGlobalBounds().width / 2, srcGrid->sprite.getGlobalBounds().height / 2);
        _coreGameData->GetInstance()->entityManager.AddEntity(grid);

        // Create entities for each square in the playfield
        for (int i = 0; i < 9; ++i)
        {
            std::shared_ptr<he::SpriteRendererComponent> src1 = std::make_shared<he::SpriteRendererComponent>("src" + std::to_string(i + 1));
            src1->sprite.setTexture(_assets->textureManager.Get("pieces"));
            src1->sprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
            src1->layer = 5;
            std::shared_ptr<he::ClickableComponent> cc1 = std::make_shared<he::ClickableComponent>("cc" + std::to_string(i + 1));
            switch (i)
            {
            case 0:
                cc1->Callback = std::make_shared<he::CallbackMethod<ttt::BoardUpdater>>(boardUpdater.get(), ttt::BoardUpdater::Fill1);
                break;
            case 1:
                cc1->Callback = std::make_shared<he::CallbackMethod<ttt::BoardUpdater>>(boardUpdater.get(), ttt::BoardUpdater::Fill2);
                break;
            case 2:
                cc1->Callback = std::make_shared<he::CallbackMethod<ttt::BoardUpdater>>(boardUpdater.get(), ttt::BoardUpdater::Fill3);
                break;
            case 3:
                cc1->Callback = std::make_shared<he::CallbackMethod<ttt::BoardUpdater>>(boardUpdater.get(), ttt::BoardUpdater::Fill4);
                break;
            case 4:
                cc1->Callback = std::make_shared<he::CallbackMethod<ttt::BoardUpdater>>(boardUpdater.get(), ttt::BoardUpdater::Fill5);
                break;
            case 5:
                cc1->Callback = std::make_shared<he::CallbackMethod<ttt::BoardUpdater>>(boardUpdater.get(), ttt::BoardUpdater::Fill6);
                break;
            case 6:
                cc1->Callback = std::make_shared<he::CallbackMethod<ttt::BoardUpdater>>(boardUpdater.get(), ttt::BoardUpdater::Fill7);
                break;
            case 7:
                cc1->Callback = std::make_shared<he::CallbackMethod<ttt::BoardUpdater>>(boardUpdater.get(), ttt::BoardUpdater::Fill8);
                break;
            case 8:
                cc1->Callback = std::make_shared<he::CallbackMethod<ttt::BoardUpdater>>(boardUpdater.get(), ttt::BoardUpdater::Fill9);
                break;
            }
            std::shared_ptr<he::AudioSourceComponent> asc1 = std::make_shared<he::AudioSourceComponent>("alc" + std::to_string(i + 1));
            asc1->sound.setBuffer(_assets->soundManager.Get("click"));
            std::shared_ptr<he::ColliderComponent> colGrid1 = std::make_shared<he::ColliderComponent>("colGrid" + std::to_string(i + 1));
            std::shared_ptr<he::Entity> grid1 = std::make_shared<he::Entity>("grid" + std::to_string(i + 1));
            grid1->AddComponent(src1);
            grid1->AddComponent(cc1);
            grid1->AddComponent(asc1);
            grid1->AddComponent(colGrid1);
            grid1->transform.position = sf::Vector2f(132 + 256 * (i % 3) + 16 * (i % 3), 132 + 256 * (i / 3) + 16 * (i / 3));
            _coreGameData->GetInstance()->entityManager.AddEntity(grid1);
        }

        /*
        _coreGameData->GetInstance()->entityManager.RemoveEntity("grid1");
        _coreGameData->GetInstance()->entityManager.RemoveEntity("grid2");
        _coreGameData->GetInstance()->entityManager.RemoveEntity("grid3");
        _coreGameData->GetInstance()->entityManager.RemoveEntity("grid4");
        _coreGameData->GetInstance()->entityManager.RemoveEntity("grid5");
        _coreGameData->GetInstance()->entityManager.RemoveEntity("grid6");
        _coreGameData->GetInstance()->entityManager.RemoveEntity("grid7");
        _coreGameData->GetInstance()->entityManager.RemoveEntity("grid8");
        _coreGameData->GetInstance()->entityManager.GetEntityById("grid9")->transform.position = sf::Vector2f(-300.f, -300.f);
        */

        // Backend setup
        _board->ResetBoard();
        _yourPiece = ttt::Piece::X;
    }

    void PlayingState::Pause()
    {
    }

    void PlayingState::Resume()
    {
    }
} // namespace ttt
