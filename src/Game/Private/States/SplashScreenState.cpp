#include "States/SplashScreenState.hpp"

#include "AssetManager/Assets.hpp"
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
            _circleShape.setFillColor(sf::Color::Blue);
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

        std::shared_ptr<ttt::SpriteExpander> se = std::make_shared<ttt::SpriteExpander>();

        std::shared_ptr<he::SpriteRendererComponent> src = std::make_shared<he::SpriteRendererComponent>("src1");
        _assets->textureManager.Load("clickableTest", "data/clickableTest.png");
        src->sprite.setTexture(_assets->textureManager.Get("clickableTest"));

        std::shared_ptr<he::ClickableComponent> cc = std::make_shared<he::ClickableComponent>("cc1");
        cc->Callback = std::make_shared<he::CallbackMethod<ttt::SpriteExpander>>(se.get(), ttt::SpriteExpander::Callback);

        std::shared_ptr<he::Entity> testEntity = std::make_shared<he::Entity>("test1");
        testEntity->AddComponent(src);
        testEntity->AddComponent(cc);
        _coreGameData->entityManager.AddEntity(testEntity);

        testEntity->transform.position.x = 200;
        testEntity->transform.position.y = 200;
    }

    void SplashScreenState::Pause()
    {
    }

    void SplashScreenState::Resume()
    {
    }
} // namespace ttt
