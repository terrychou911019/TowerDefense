#ifndef TrapDefense_hpp
#define TrapDefense_hpp

#include "Defense.hpp"

class TrapDefense : public Defense {
public:
    TrapDefense(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Draw() const override;
};

#endif /* TrapDefense_hpp */


