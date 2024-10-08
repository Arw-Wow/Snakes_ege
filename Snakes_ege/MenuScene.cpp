#include "MenuScene.h"

void MenuScene::on_enter()
{
    FPS = 144;

    camera.wandering(0.1);

    mciSendString("play menu_scene_bgm repeat from 0", NULL, 0, NULL);
}

void MenuScene::on_input(key_msg& msg)
{
    if (msg.msg & key_msg_down)
    {
        switch (msg.key)
        {
        case VK_ESCAPE:
            mciSendString("play select_scene_confirm from 0", NULL, 0, NULL);
            is_running = false;
            break;
        default:	// ������ESC���������������Ϸ
            SceneManager::get_instance()->switch_to(SceneType::INTRODUCE_SCENE);
            mciSendString("play select_scene_confirm from 0", NULL, 0, NULL);
            break;
        }
    }
}

void MenuScene::on_update(int delta)
{
    camera.on_update(delta);
}

void MenuScene::on_draw()
{
    // background
    putimage(0, 10, img_menu_scene_background);

    // ����һ��
    putimage_alphablend(NULL, img_black_background, 0, 0, 0xb0);

    // title
    // putimage(getwidth() / 2 - getwidth(img_title) / 2, 200, img_title);
    // putimage_alpha(getwidth() / 2 - getwidth(img_title) / 2, 200, img_title);
    putimage_transparent(camera, NULL, img_title, getwidth() / 2 - getwidth(img_title) / 2, 200, BLACK);

    // text
    LOGFONTW f;
    getfont(&f);
    f.lfHeight = 30;
    settextcolor(EGERGB(224, 224, 224));
    strcpy((char*)f.lfFaceName, "����");
    setbkmode(TRANSPARENT);
    f.lfItalic = true;
    setfont(&f);                          // ����������ʽ
    char str[256] = "-- ���������ʼ��Ϸ --";
    outtextxy(getwidth() / 2 - textwidth(str) / 2, getheight() - 80 - textheight(str) / 2, str);
}

void MenuScene::on_exit()
{
    camera.stop_wandering();
}
