#include <allegro5/base.h>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <string>

#include "TrapDefense.hpp"
#include "AudioHelper.hpp"
#include "BlueCannonBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Army.hpp"
#include "Collider.hpp"
#include "GameEngine.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "Sprite.hpp"

//Defense(std::string imgDefense, float x, float y, float radius, float coolDown, int hp, int id, float shootRadius);
TrapDefense::TrapDefense(float x, float y) :
    Defense("play/bomb.png", x, y, 20, 0.5, 50, 4, 100) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
    //Visible = false;
}

void TrapDefense::CreateBullet(Engine::Point pt) {
    
}

void TrapDefense::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    PlayScene* scene = getPlayScene();
    if (!Enabled)
        return;

    //if (scene->DebugMode == true) Visible = true;
    //else Visible = false;

    if (scene->DebugMode == true) Draw();
    

    for (auto& it : scene->ArmyGroup->GetObjects()) {
        Army* army = dynamic_cast<Army*>(it);
        if (!army->Visible)
            continue;
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, army->Position, army->CollisionRadius)) {
            if (army->id != 3) {
                army->Hit(INFINITY);
                Army* tgt = nullptr;
                for (auto& it : scene->ArmyGroup->GetObjects()) {
                    if (InShootingRange(it->Position)) {
                        tgt = dynamic_cast<Army*>(it);
                        tgt->Hit(INFINITY);
                    }
                }
                Hit(INFINITY);
                //getPlayScene()->BulletGroup->RemoveObject(objectIterator);
                return;
            }
        }
    }
}

void TrapDefense::Draw() const {
    
    if (PlayScene::DebugMode) {
        // Draw target radius.
        if (shootRadius < 425)
            Sprite::Draw();
            al_draw_circle(Position.x, Position.y, shootRadius, al_map_rgb(0, 255, 0), 2);
        //else
        //    al_draw_circle(Position.x, Position.y, shootRadius, al_map_rgb(0, 0, 255), 2);
    }
}