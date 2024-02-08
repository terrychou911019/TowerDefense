#ifndef BlueCannonDefense_hpp
#define BlueCannonDefense_hpp

#include "Defense.hpp"

class BlueCannonDefense : public Defense {
public:
    BlueCannonDefense(float x, float y);
    void CreateBullet(Engine::Point pt) override;
};

#endif /* BlueCannonDefense_hpp */

