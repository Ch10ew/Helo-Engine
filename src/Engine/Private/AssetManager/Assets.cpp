#include "AssetManager/Assets.hpp"

namespace he
{
    he::Assets* he::Assets::_instance = nullptr;

    Assets::Assets()
    {
    }

    Assets::~Assets()
    {
        delete _instance;
    }

    Assets* Assets::GetInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new Assets();
        }
        return _instance;
    }
} // namespace he
