#include "LevelAnim.h"
#include "GameManager.h"

LevelAnim::LevelAnim(TileSet* tileset, float delay, bool repeat) {
	ts = tileset;
	this->repeat = repeat;
	anim = new Animation(tileset, delay, repeat);
}

LevelAnim::~LevelAnim() {
	delete anim;
}

void LevelAnim::OnCollision(Object* obj) {}

void LevelAnim::Update() {
	if (anim->Inactive() && !repeat) {
		GameManager::currLevel->scene->Delete(this, STATIC);
	}
	else {
		anim->NextFrame();
	}

}

inline void LevelAnim::Draw() { anim->Draw(x, y, Layer::FRONT); }