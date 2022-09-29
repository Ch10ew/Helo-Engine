#include "Core/CoreGameData.hpp"

namespace he
{
    he::CoreGameData* he::CoreGameData::_instance = nullptr;

    CoreGameData::CoreGameData()
    {
    }

    CoreGameData::~CoreGameData()
    {
        delete _instance;
    }

    CoreGameData* CoreGameData::GetInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new CoreGameData();
        }
        return _instance;
    }
} // namespace he
