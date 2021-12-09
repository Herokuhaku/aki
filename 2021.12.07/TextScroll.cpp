#include "TextScroll.h"
#include "Quaternion.h"
#include "SceneManager.h"
#include "Camera.h"
#include "AsoUtility.h"
TextScroll::TextScroll(SceneManager* manager)
{
    scenemanager_ = manager;
    Init();
}

void TextScroll::Init()
{
    code_.try_emplace(CODE::SPACE, 52);
    code_.try_emplace(CODE::DOT, 53);
    code_.try_emplace(CODE::COMMA,54);

    LoadDivGraph("Image/Alphabet.png", NUM_IMAGE, NUM_X_IMAGE, NUM_Y_IMAGE, CHIP_SIZE, CHIP_SIZE, &images_[0], true);
    type_ = TYPE::TITLE;
    std::vector<MsgInfo> infos;
    infos.push_back(MakeMsgInfo("ABCDEFGHIJ",infos.size()));
    infos.push_back(MakeMsgInfo("KLMNOPQRST", infos.size()));
    infos.push_back(MakeMsgInfo("UVWXYZabcd", infos.size()));
    infos.push_back(MakeMsgInfo("efghijklmn", infos.size()));
    infos.push_back(MakeMsgInfo("opqrstuvwx", infos.size()));
    infos.push_back(MakeMsgInfo("yz .,_!?()", infos.size()));

    textmap_.emplace(type_, infos);
    //z = -500;
    z = static_cast<int>(infos.size())*-100;
    y = 0;
}

void TextScroll::Update()
{
    // 文字の移動
    auto infos = textmap_[type_];
    for (auto& info : infos) {
        // 行ごとの位置
        // ★
        z += 0.2f;
    }
}

void TextScroll::Draw()
{    // 文字の移動
    auto infos = textmap_[type_];
    VECTOR pos = {0,y,z };
    Camera* camera = scenemanager_->GetCamera();
    Quaternion rotX = Quaternion::AngleAxis(AsoUtility::Deg2RadF(-90), AsoUtility::AXIS_X);

    VECTOR dir = rotX.GetForward();
    for (auto& info : infos) {
        pos.x = static_cast<int>(infos.size()) / 2 * -40;
        pos = VAdd(pos, dir);
        for (auto& msg : info.messages) {
            // 1文字
            DrawBillboard3D(pos, 0.5f, 0.5f, 20.0f, 0.0f, images_[msg], true);
            pos.x += 25;
        }
        pos.z += 32;
        
    }
    y = 0;
}

void TextScroll::Release(void)
{
    for (int i = 0; i < NUM_IMAGE; i++) {
        DeleteGraph(images_[i]);
    }
}

TextScroll::MsgInfo TextScroll::MakeMsgInfo(std::string msg, int mapCount)
{
    MsgInfo ret;
    // 文字を画像配列の要素番号に変換
    std::vector<int> messages;
    int ascii;
    // 要素番号
    int num;
    int len = msg.size();
    for (int i = 0; i < len; i++) {
        ascii = msg.at(i);

        if (ascii <= 122) {
            ascii >= 97 ? num = ascii - 71 : num = ascii - 65;
        }
        else {
            if (ascii == static_cast<int>(CODE::SPACE)) {
                num = code_[CODE::SPACE];
            }
            else if (ascii == static_cast<int>(CODE::SPACE)) {
                num = code_[CODE::DOT];
            }
            else if (ascii == static_cast<int>(CODE::SPACE)) {
                num = code_[CODE::COMMA];
            }
        }

        messages.emplace_back(num);
    }

    ret.pos = {};
    ret.messages = messages;
    return ret;
}
