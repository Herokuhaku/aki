#include "Particle.h"
#include "SceneManager.h"

Particle::Particle(SceneManager* manager, int img)
{
	scenemanager_ = manager;
	imglight_ = img;
}

void Particle::Generate(VECTOR pos, float size, VECTOR dir, float speed, float lifetime)
{
	pos_ = pos;
	size_ = size;
	dir_ = dir;
	speed_ = speed;
	lifetime_ = lifetime;
}

void Particle::Update(void)
{
	auto delta = scenemanager_->GetDeltaTime();
	//pos_.x += dir_.x * speed_*delta;
	//pos_.y += dir_.y * speed_*delta;
	//pos_.z += dir_.z * speed_*delta;

	pos_ = VAdd(pos_, dir_);

	if (lifetime_ > 0.0f) {
		lifetime_ -= scenemanager_->GetDeltaTime();
	}
}

void Particle::Draw(void)
{
	DrawBillboard3D(pos_, 0.5f, 0.5f, size_, 0.0f, imglight_, true);
}

void Particle::Release(void)
{
}

void Particle::SetPos(VECTOR pos)
{
	pos_ = pos ;
}

float Particle::GetZLen(void)
{
	return zLen_;
}

void Particle::SetZLen(float len)
{
	zLen_ = len;
}

bool Particle::IsAlive(void)
{
	return lifetime_ > 0.0f;
}
