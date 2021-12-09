#pragma once
#include <DxLib.h>
#include <vector>
#include <map>
#include <string>
class SceneManager;
class TextScroll
{
public:
	static constexpr int NUM_X_IMAGE = 10;
	static constexpr int NUM_Y_IMAGE = 6;

	static constexpr int NUM_IMAGE = NUM_X_IMAGE* NUM_Y_IMAGE;
	static constexpr int CHIP_SIZE= 32;
	
	struct MsgInfo {
		VECTOR pos;
		std::vector<int> messages;

	};
	enum class TYPE {
		TITLE,
	};
	enum class CODE {
		SMALL,
		BIG,
		SPACE = 32,
		DOT = 46,
		COMMA = 44,
	};
	TextScroll(SceneManager* manager);
	void Init();
	void Update();
	void Draw();
	void Release(void);
private:
	SceneManager* scenemanager_;
	// �摜
	int images_[NUM_IMAGE];
	// �Đ�����e�L�X�g�X�N���[��
	TYPE type_;
	// �e�L�X�g�Ǘ�
	std::map<TYPE, std::vector<MsgInfo>> textmap_;
	// string�̕�������摜�̗v�f�ԍ��ɕϊ�
	MsgInfo MakeMsgInfo(std::string msg, int mapCount);

	std::map<CODE, int> code_;
	float z;
	float y;
};

