#include "Core/CoreGameData.hpp"

namespace he
{
    CoreGameData::CoreGameData()
    {
    }

    CoreGameData::~CoreGameData()
    {
    }

    CoreGameData& CoreGameData::GetInstance()
    {
        static CoreGameData _instance;
        return _instance;
    }
} // namespace he
