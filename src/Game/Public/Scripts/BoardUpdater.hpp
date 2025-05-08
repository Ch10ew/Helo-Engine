#ifndef TTT_BOARD_UPDATER_HPP
#define TTT_BOARD_UPDATER_HPP

#include "Core/Component.hpp"

#include <array>

namespace ttt
{
    class BoardUpdater
    {
    public:
        void Fill1(he::Component* component, he::Component* ignore);
        void Fill2(he::Component* component, he::Component* ignore);
        void Fill3(he::Component* component, he::Component* ignore);
        void Fill4(he::Component* component, he::Component* ignore);
        void Fill5(he::Component* component, he::Component* ignore);
        void Fill6(he::Component* component, he::Component* ignore);
        void Fill7(he::Component* component, he::Component* ignore);
        void Fill8(he::Component* component, he::Component* ignore);
        void Fill9(he::Component* component, he::Component* ignore);

        void FillAI(he::Component* component);
    };
} // namespace ttt

#endif // TTT_BOARD_UPDATER_HPP
