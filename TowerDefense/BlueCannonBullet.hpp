#ifndef BlueCannonBullet_hpp
#define BlueCannonBullet_hpp

#include "Bullet.hpp"

class Army;
class Defense;
namespace Engine {
    struct Point;
}  // namespace Engine

class BlueCannonBullet : public Bullet {
public:
    explicit BlueCannonBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* parent);
    void Update(float deltaTime) override;
};

#endif /* BlueCannonBullet_hpp */
