#pragma once
#include <vector>
#include "DxLib.h"
#include "Quaternion.h"
class Transform;
class SceneManager;

class Camera
{

public:

	// �J�����̏������W
	static constexpr VECTOR DEFAULT_CAMERA_POS = { 0.0f, 100.0f, -500.0f };
	// �Ǐ]���W
	static constexpr VECTOR RELATIVE_CAMERA_FOLLOW = { 0.0f,25.0f,-80.0f };
	// �Ǐ]���W
	static constexpr VECTOR RELATIVE_CAMERA_SPRING = { 0.0f,25.0f,150.0f };
	// �J�����ʒu�ƒ����_�Ƃ̑��΍��W
	static constexpr VECTOR RELATIVE_TARGET_POS = { 0.0f,-100.0f,500.0f };

	static constexpr float TIME_SHAKE = 2.0f;
	static constexpr float WIDTH_SHAKE = 7.0f;
	static constexpr float SHAKE_SPEED = 300.0f;


	enum class MODE {
		NONE,
		FREE,			// ���R���[�h
		FIXED_POINT,	// ��_���[�h
		FOLLOW,			// �Ǐ]���[�h
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


	// �J�����̈ʒu
	VECTOR pos_;

	// �J�����p�x
	Quaternion mQuaRot;

	// �����_
	VECTOR targetpos_;

	// �J�����̏����
	VECTOR cameraup_;

	Transform* shiptransform_;

	// ���x
	VECTOR velocity_;
	
	float stepshake_;
	VECTOR defaultpos_;
	VECTOR shakedir_;
};

