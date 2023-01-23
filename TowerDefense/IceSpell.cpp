#include <allegro5/base.h>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Collider.hpp"
#include "Army.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "IceSpell.hpp"
#include "Defense.hpp"

//Army(std::string img, float x, float y, float radius, float coolDown, float speed, float hp, int id, float shootRadius);
IceSpell::IceSpell(float x, float y) :
    Army("play/snowflake.png", x, y, 20, 0, 0, 15, 3, 0) {
    // Move center downward, since we the army head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
    melt_timer = al_create_timer(1.0);
}

void IceSpell::Update(float deltaTime) {
    // PlayScene
    PlayScene* scene = getPlayScene();

    if (isPreview) return;

     if (!isIce) {
        isIce = true;
        al_start_timer(melt_timer);
        getPlayScene()->EffectGroup->AddNewObject(ice_effect[0] = new Engine::Sprite("play/snowflake.png", Position.x - PlayScene::BlockSize, Position.y - PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(ice_effect[1] = new Engine::Sprite("play/snowflake.png", Position.x, Position.y - PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(ice_effect[2] = new Engine::Sprite("play/snowflake.png", Position.x + PlayScene::BlockSize, Position.y - PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(ice_effect[3] = new Engine::Sprite("play/snowflake.png", Position.x - PlayScene::BlockSize, Position.y));
        getPlayScene()->EffectGroup->AddNewObject(ice_effect[4] = new Engine::Sprite("play/snowflake.png", Position.x, Position.y));
        getPlayScene()->EffectGroup->AddNewObject(ice_effect[5] = new Engine::Sprite("play/snowflake.png", Position.x + PlayScene::BlockSize, Position.y));
        getPlayScene()->EffectGroup->AddNewObject(ice_effect[6] = new Engine::Sprite("play/snowflake.png", Position.x - PlayScene::BlockSize, Position.y + PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(ice_effect[7] = new Engine::Sprite("play/snowflake.png", Position.x, Position.y + PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(ice_effect[8] = new Engine::Sprite("play/snowflake.png", Position.x + PlayScene::BlockSize, Position.y + PlayScene::BlockSize));
        AudioHelper::PlayAudio("ice.wav");
    }

    Defense* tgt = nullptr;
    for (auto& it : scene->DefenseGroup->GetObjects()) {
        int dis = ManHattanDistance(it->Position);
        if (dis * dis <= 5) {  // ???
            tgt = dynamic_cast<Defense*>(it);
            if (tgt->id == 2 || tgt->id == 3)
                tgt->Enabled = false;
        }
    }

    if (al_get_timer_count(melt_timer) >= 2.0) {
        al_stop_timer(melt_timer);
        al_set_timer_count(melt_timer, 0);
        Hit(INFINITY);
        if (tgt->id == 2 || tgt->id == 3) 
            tgt->Enabled = true;
    }
}


// Since the bomb army cannot shoot, the function doesn't need to do anything.
void IceSpell::CreateBullet(Engine::Point pt) {}

// TODO 2 (5/8): You can imitate the hit function in Army class. Notice that the bomb army won't have explosion effect.
void IceSpell::Hit(float damage) {
    HP -= damage;
    if (HP <= 0) {
        //OnExplode();
        // Remove all Defense's reference to target.
        for (auto& it : lockedDefenses)
            it->Target = nullptr;
        for (int i = 0; i < 9; i++) {
            getPlayScene()->EffectGroup->RemoveObject(ice_effect[i]->GetObjectIterator());
        }
        getPlayScene()->ArmyGroup->RemoveObject(objectIterator);
        //AudioHelper::PlayAudio("explosion.wav");
    }
}