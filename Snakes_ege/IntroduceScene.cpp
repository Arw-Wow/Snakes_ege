#include "IntroduceScene.h"

IntroduceScene::IntroduceScene()
{
    timer_change_text_color.set_one_shot(false);
    timer_change_text_color.set_wait_time(interval_change_text_color);
    timer_change_text_color.set_shot_callback(
        [&]()
        {
            text_color_rand_r = rand() % 256;
            text_color_rand_g = rand() % 256;
            text_color_rand_b = rand() % 256;
        }
    );
}

void IntroduceScene::on_enter()
{
    // player_1_text_pos;
    // player_2_text_pos;
    // other_text_pos;

    text_camera.wandering(0.1);

    timer_change_text_color.restart();
}

void IntroduceScene::on_input(key_msg& msg)
{
    if (msg.msg & key_msg_down)
    {
        switch (msg.key)
        {
        case VK_RETURN:
            SceneManager::get_instance()->switch_to(SceneType::SELECT_SCENE);
            mciSendString("play select_scene_confirm from 0", NULL, 0, NULL);
            break;
        }
    }
}

void IntroduceScene::on_update(int delta)
{
    timer_change_text_color.on_update(delta);
    text_camera.on_update(delta);
}

void IntroduceScene::on_draw()
{
    // background
    putimage(0, 10, img_menu_scene_background);

    // 调暗一点
    putimage_alphablend(NULL, img_black_background, 0, 0, 0xd0);

    setbkmode(TRANSPARENT);
    setfont(70, 0, "Comic Sans MS");
    // 锁定两个颜色参数，使按键介绍始终保持比较亮的颜色
    settextcolor(EGERGB(255, 255, text_color_rand_b));

    char player_1_text[] = "P1：WASD";
    player_1_text_pos = { getwidth() / 4 - textwidth(player_1_text) / 2, getheight() / 3 - textheight(player_1_text) / 2 };
    outtextxy(text_camera, player_1_text_pos.x, player_1_text_pos.y, player_1_text);

    char player_2_text[] = "P2：↑↓←→";
    player_2_text_pos = { getwidth() / 4 * 3 - textwidth(player_2_text) / 2, getheight() / 3 - textheight(player_2_text) / 2 };
    outtextxy(text_camera, player_2_text_pos.x, player_2_text_pos.y, player_2_text);

    char other_text[] = "other：SPACE pause,  ENTER shake";
    other_text_pos = { getwidth() / 2 - textwidth(other_text) / 2, getheight() / 4 * 3 - textheight(other_text) / 2 };
    outtextxy(text_camera, other_text_pos.x, other_text_pos.y, other_text);
}

void IntroduceScene::on_exit()
{
    mciSendString("stop menu_scene_bgm", NULL, 0, NULL);
}
