#include <allegro5/base.h>
#include <random>
#include <string>

#include "DirtyEffect.hpp"
#include "BlueCannonBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Bullet.hpp"
#include "Collider.hpp"
#include "Army.hpp"
#include "GameEngine.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "Sprite.hpp"

class Defense;

//Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* defenseParent);
BlueCannonBullet::BlueCannonBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* parent) :
    Bullet("play/bullet-1.png", 500, 2.5, position, forwardDirection, rotation, parent) {
}

void BlueCannonBullet::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    PlayScene* scene = getPlayScene();

    for (auto& it : scene->ArmyGroup->GetObjects()) {
        Army* army = dynamic_cast<Army*>(it);
        if (!army->Visible)
            continue;
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, army->Position, army->CollisionRadius)) {
            army->Hit(damage);
            if (!army->isslow) {
                army->isslow = true;
                army->SetSpeed((army->GetSpeed()) / 2.0);
            }
            getPlayScene()->BulletGroup->RemoveObject(objectIterator);
            return;
        }
    }
    // Check if out of boundary.
    if (Position.x < 0 || Position.x > PlayScene::GetClientSize().x || Position.y < 0 || Position.y > PlayScene::GetClientSize().y)
        getPlayScene()->BulletGroup->RemoveObject(objectIterator);
}