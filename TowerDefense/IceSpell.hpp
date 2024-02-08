#ifndef IceSpell_hpp
#define IceSpell_hpp

#include "Army.hpp"
#include "DirtyEffect.hpp"

class IceSpell : public Army {
public:

    IceSpell(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Hit(float damage) override;

    ALLEGRO_TIMER* melt_timer;
    Engine::Sprite* ice_effect[9];
    bool isIce;

};

#endif /* IceSpell_hpp */

