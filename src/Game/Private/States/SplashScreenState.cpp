#include "States/SplashScreenState.hpp"

#include "AssetManager/Assets.hpp"
#include "Components/Animation/AnimationState.hpp"
#include "Components/AnimationComponent.hpp"
#include "Components/ClickableComponent.hpp"
#include "Components/SpriteRendererComponent.hpp"
#include "Core/CoreGameData.hpp"
#include "Core/Entity.hpp"
#include "Core/EntityManager.hpp"
#include "Core/Wrapper/CallbackFunction.hpp"
#include "Core/Wrapper/CallbackMethod.hpp"
#include "Scripts/SpriteExpander.hpp"
#include "States/PlayingState.hpp"

#include <iostream>

namespace ttt
{
    SplashScreenState::SplashScreenState()
    {
        _coreGameData = he::CoreGameData::GetInstance();
        _assets = he::Assets::GetInstance();
    }

    void SplashScreenState::Update(float dt)
    {
        if (_clock.getElapsedTime().asMilliseconds() > SPLASH_TIME)
        {
            _coreGameData->stateMachine.AddState(std::unique_ptr<he::GameState>(new ttt::PlayingState()));
            _assets->textureManager.Unload("clickableTest");
        }
    }

    void SplashScreenState::FixedUpdate(float dt)
    {
    }

    void SplashScreenState::Init()
    {
        /*
        _circleShape.setRadius(30);
        _circleShape.setFillColor(sf::Color::Green);
        _circleShape.setPosition(200, 200);

        _assets->textureManager.Load("test", "data/plant.png");
        _test.setTexture(_assets->textureManager.Get("test"));
        */
        _assets->textureManager.Load("clickableTest", "data/clickableTest.png");
        _assets->textureManager.Load("playerSpritesheet", "data/Spritesheet-Player.png");

        se = std::make_shared<ttt::SpriteExpander>();

        std::shared_ptr<he::SpriteRendererComponent> src = std::make_shared<he::SpriteRendererComponent>("src1");
        src->sprite.setTexture(_assets->textureManager.Get("clickableTest"));

        std::shared_ptr<he::ClickableComponent> cc = std::make_shared<he::ClickableComponent>("cc1");
        cc->Callback = std::make_shared<he::CallbackMethod<ttt::SpriteExpander>>(se.get(), ttt::SpriteExpander::Callback);

        std::shared_ptr<he::AnimationComponent> ac = std::make_shared<he::AnimationComponent>("ac1");

        // Animation State 1 - Default
        he::AnimationState as1_default("as1_default");
        for (int i = 0; i < 12; ++i)
        {
            sf::Sprite as1Sprite;
            as1Sprite.setTexture(_assets->textureManager.Get("playerSpritesheet"));
            as1Sprite.setTextureRect(sf::IntRect((32 * i), 0, 32, 48));
            as1Sprite.setScale(sf::Vector2f(4.f, 4.f));
            as1_default.AddFrame(as1Sprite, 0.1f);
        }
        as1_default.isLoop = true;

        // Animation Component
        ac->AddState(as1_default);

        // Entity
        std::shared_ptr<he::Entity>
            testEntity = std::make_shared<he::Entity>("test1");
        testEntity->AddComponent(src);
        testEntity->AddComponent(cc);
        testEntity->AddComponent(ac);
        _coreGameData->entityManager.AddEntity(testEntity);

        testEntity->transform.position.x = 200;
        testEntity->transform.position.y = 200;
    }
} // namespace ttt
