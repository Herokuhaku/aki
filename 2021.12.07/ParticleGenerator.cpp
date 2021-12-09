#include "ParticleGenerator.h"
#include <algorithm>
#include "Quaternion.h"
#include "AsoUtility.h"
#include "Particle.h"
#include "SceneManager.h"
#include "Camera.h"
ParticleGenerator::ParticleGenerator(SceneManager* manager, VECTOR pos, float radius)
{
	scenemanager_ = manager;
	pos_ = pos;
	radius_ = radius;
	Init();
}

void ParticleGenerator::Init()
{
	imglight_ = LoadGraph("Image/Light.png");
	CreateMeshCircle();
	CreateMeshSquare();

	// テスト用
	Generate(nullptr);
	//for (int i = 0; i < PARTICLE; i++) {
	//	particles_.push_back(Generate(nullptr));
	//}
}

void ParticleGenerator::Update(void)
{
	if(particles_.size() < PARTICLE && rand() % 35 == 0) {
		particles_.push_back(Generate(nullptr));
	}

	for (auto& p : particles_) {
		p->Update();
		// 生存時間が切れたら再生成
		if (!p->IsAlive()) {
			p = Generate(p);
			p->GetPos();
		}
	}
	DebugProcess();
}

void ParticleGenerator::Draw(void)
{
	Camera* camera = scenemanager_->GetCamera();
	VECTOR c2t = camera->GetDir();
	VECTOR c2p;
	for(auto& p : particles_){
		// カメラから見たパーティクルの向き(ベクトル)
		c2p = VSub(p->GetPos(), camera->GetPos());
		p->SetZLen(VDot(c2t,c2p));
	}

	sort(particles_.begin(), particles_.end(), [](Particle* x, Particle* y) {
		return x->GetZLen() > y->GetZLen(); });

	//DrawBillboard3D(pos_,0.5f,0.5f,100.0f,0.0f,imglight_,true);
	//DrawMeshSquare();
	DrawMeshCircle();
	//SetDrawBlendMode(DX_GRAPH_BLEND_ADD, 128);

	for (auto& p : particles_) {
		p->Draw();
	}
}

void ParticleGenerator::DebugProcess(void)
{
	Quaternion tmpQ;
	bool isHitKey = false;
	// 右回転
	if (CheckHitKey(KEY_INPUT_L)) {
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(AsoUtility::Deg2RadF(1.0f), AsoUtility::AXIS_Y);
	}
	// 左回転
	if (CheckHitKey(KEY_INPUT_J)) {
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(AsoUtility::Deg2RadF(-1.0f), AsoUtility::AXIS_Y);
	}

	// 上回転
	if (CheckHitKey(KEY_INPUT_I)) {
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(AsoUtility::Deg2RadF(-1.0f), AsoUtility::AXIS_X);
	}

	// 下回転
	if (CheckHitKey(KEY_INPUT_K)) {
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(AsoUtility::Deg2RadF(1.0f), AsoUtility::AXIS_X);
	}
	if (isHitKey) {
		quarot_ = quarot_.Mult(tmpQ);
		CreateMeshCircle();
	}
}

void ParticleGenerator::DrawMeshSquare(void)
{
	DrawPolygon3D(verticesSquare_, 2, DX_NONE_GRAPH, true);
	for (auto& v : verticesSquare_) {
		DrawSphere3D(v.pos, 2, 3, 0xff0000, 0xff0000, true);
	}
}

void ParticleGenerator::DrawMeshCircle(void)
{
	//DrawSphere3D(verticesCircle_[0].pos, 5, 5, 0x00ffff, 0x00ffff, true);
	DrawPolygonIndexed3D(verticesCircle_,NUM_POLYGON+1,indexs_,NUM_POLYGON, DX_NONE_GRAPH, true);
	for (auto& v : verticesCircle_) {
		DrawSphere3D(v.pos, 2, 3, 0xffff00, 0xffff00, true);
	}
}

void ParticleGenerator::Release(void)
{
	DeleteGraph(imglight_);

	for (auto& p : particles_) {
		p->Release();
	}
}

void ParticleGenerator::SetPos(VECTOR pos)
{
	pos_ = pos;
}

void ParticleGenerator::SetRot(Quaternion rot)
{
	quarot_ = rot;
}

Particle* ParticleGenerator::Generate(Particle* particle)
{
	if (particle == nullptr) {
		particle = new Particle(scenemanager_,imglight_);
	}
	// 発生位置
	//------------------------------------------------------------------
	VECTOR pos = {};
	Quaternion rotY = Quaternion::AngleAxis(
	AsoUtility::Deg2RadF(GetRand(360.0f)),AsoUtility::AXIS_Y
	);
	float min = radius_ * 4 / 3;
	pos = rotY.PosAxis({0.0f,0.0f,min + (float)GetRand(radius_ - min)});
	pos = VAdd(pos, pos_);
	//------------------------------------------------------------------
	VECTOR dir = {};

	float randDeg = 30 + GetRand(40 - 30);
	randDeg *= -1.0f;
	Quaternion rotX = Quaternion::AngleAxis(AsoUtility::Deg2RadF(randDeg), AsoUtility::AXIS_X);
	Quaternion rot = rotY.Mult(rotX);
	rot = quarot_.Mult(rot);
	dir = rot.GetForward();
	// 大きさ
	float size = GetRand(GEN_MAX_SIZE - GEN_MIN_SIZE) + GEN_MIN_SIZE;
	// 大きさ
	float speed = GetRand(GEN_MAX_SPEED - GEN_MIN_SPEED) + GEN_MIN_SPEED;
	// 大きさ
	float life = GetRand(GEN_MAX_LIFE - GEN_MIN_LIFE) + GEN_MIN_LIFE;
	particle->Generate(pos,size,dir,speed,life);
	return particle;
}

void ParticleGenerator::CreateMeshSquare(void)
{
	// 白
	COLOR_U8 c = GetColorU8(255, 255, 255, 255);
	for (int i = 0; i < 6; i++) {
		verticesSquare_[i].dif = c;

	}
	float h = 100.0f;
	verticesSquare_[0].pos = { 0,0,0 };
	verticesSquare_[1].pos = { 0,0,h };
	verticesSquare_[2].pos = { h,0,h };

	verticesSquare_[3].pos = { 0,0,0 };
	verticesSquare_[4].pos = { h,0,h };
	verticesSquare_[5].pos = { h,0,0 };
}

void ParticleGenerator::CreateMeshCircle(void)
{	// 白
	COLOR_U8 c = GetColorU8(255, 255, 255, 255);
	COLOR_U8 g = GetColorU8(0, 200,0, 255);
	verticesCircle_[0].dif = g;
	for (int i = 1; i < NUM_POLYGON+1; i++) {
		verticesCircle_[i].dif = c;
	}
	VECTOR cpos = pos_;
	// 円の中心頂点
	int cntvertex = 0;
	verticesCircle_[cntvertex++].pos = cpos;

	VECTOR pos;
	Quaternion rot;
	float cntang = 0;
	// 円周のループ
	for (int i = 1; i < NUM_POLYGON+1;i++) {
		rot = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(cntang), AsoUtility::AXIS_Y);
		rot = quarot_.Mult(rot);
		pos = rot.PosAxis({ 0.0f,0.0f,radius_ });
		//pos = VAdd(pos_, pos);

		verticesCircle_[i].pos = VAdd(cpos,pos);

		cntang += SPLIT_ANGLE_DEG;
	}
	int cntidx = 0;
	int cnttry = 1;
	for (int i = 0; i < NUM_POLYGON; i++) {
		indexs_[cntidx++] = 0;
		indexs_[cntidx++] = cnttry;
		indexs_[cntidx++] = ++cnttry;
	}
	indexs_[--cntidx] = 0;
	indexs_[cntidx] = cnttry;
	indexs_[cntidx] = 1;
}
