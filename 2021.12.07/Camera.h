#pragma once
#include <vector>
#include "DxLib.h"
#include "Quaternion.h"
class Transform;
class SceneManager;

class Camera
{

public:

	// カメラの初期座標
	static constexpr VECTOR DEFAULT_CAMERA_POS = { 0.0f, 100.0f, -500.0f };
	// 追従座標
	static constexpr VECTOR RELATIVE_CAMERA_FOLLOW = { 0.0f,25.0f,-80.0f };
	// 追従座標
	static constexpr VECTOR RELATIVE_CAMERA_SPRING = { 0.0f,25.0f,150.0f };
	// カメラ位置と注視点との相対座標
	static constexpr VECTOR RELATIVE_TARGET_POS = { 0.0f,-100.0f,500.0f };

	static constexpr float TIME_SHAKE = 2.0f;
	static constexpr float WIDTH_SHAKE = 7.0f;
	static constexpr float SHAKE_SPEED = 300.0f;


	enum class MODE {
		NONE,
		FREE,			// 自由モード
		FIXED_POINT,	// 定点モード
		FOLLOW,			// 追従モード
		SPRING,
		SHAKE,
	};


	//static constexpr VECTOR RELATIVE_TARGET_POS = { 0.0f, -100.0f, 500.0f };
	
	Camera(SceneManager* manager);
	~Camera();

	void Init(void);
	void SetDefault(void);

	void Update(void);

	void SetBeforeDraw(void);
	void SetBeforeDrawFree(void);
	void SetBeforeDrawFixedPoint(void);
	void SetBeforeDrawFollow(void); 
	void SetBeforeDrawFollowSpring(void);
	void SetBeforeDrawShake(void);

	void Draw(void);
	void DrawDebug(void);
	void DrawUI(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetTargetPos(void);
	VECTOR GetDir(void);

	bool ChangeCameraMode(MODE mode);

	void SetShip(Transform* shiptransform);
private:

	SceneManager* scenemanager_;
	
	MODE mode_;


	// カメラの位置
	VECTOR pos_;

	// カメラ角度
	Quaternion mQuaRot;

	// 注視点
	VECTOR targetpos_;

	// カメラの上方向
	VECTOR cameraup_;

	Transform* shiptransform_;

	// 速度
	VECTOR velocity_;
	
	float stepshake_;
	VECTOR defaultpos_;
	VECTOR shakedir_;
};

