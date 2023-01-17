#include "AssetManager/Assets.hpp"

namespace he
{
    Assets::Assets()
    {
    }

    Assets::~Assets()
    {
    }

    Assets& Assets::GetInstance()
    {
        static Assets _instance;
        return _instance;
    }
} // namespace he
