#include "SelectScene.h"

SelectScene::SelectScene()
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

    animation_fire_background.load_img_list("res/img/fire_background/%d.png", 20, 2600, 2800);
    animation_fire_background.set_interval(60);
    animation_fire_background.set_loop(true);
}

void SelectScene::on_enter()
{
    // is_special_mode_on = false;
    FPS = 144;
    camera.wandering(0.15);
    camera_text_1.wandering(0.14);
    camera_text_2.wandering(0.14);
    camera_left_button.wandering(0.14);
    camera_right_button.wandering(0.14);

    timer_change_text_color.restart();

    animation_fire_background.restart();

    current_map_type = MapType::MAP_0;
    bool is_left_button_down = false;
    bool is_right_button_down = false;
    bool is_1P_move_up = false;

    mciSendString("play menu_scene_bgm repeat from 0", NULL, 0, NULL);
}

void SelectScene::on_input(key_msg& msg)
{
    if (msg.msg & key_msg_down)
    {
        switch (msg.key)
        {
        case 65:	case VK_LEFT:	// A or left
            is_left_button_down = true;
            break;
        case 68:	case VK_RIGHT:  // D or right
            is_right_button_down = true;
            break;
        case VK_SPACE:
            if (!is_special_mode_on)
            {
                camera.shake(8, 700);
                camera_text_2.shake(8, 700);
            }
            is_special_mode_on = !is_special_mode_on;
            mciSendString("play select_scene_confirm from 0", NULL, 0, NULL);
            break;
        case VK_RETURN:
            SceneManager::get_instance()->switch_to(SceneType::SETTING_SCENE);
            mciSendString("play select_scene_confirm from 0", NULL, 0, NULL);
            break;
        case VK_ESCAPE:
            SceneManager::get_instance()->switch_to(SceneType::MENU_SCENE);
            mciSendString("play select_scene_confirm from 0", NULL, 0, NULL);
            // mciSendString("stop menu_scene_bgm", NULL, 0, NULL);
            break;
        }
    }
    if (msg.msg & key_msg_up)
    {
        switch (msg.key)
        {
        case 65:	case VK_LEFT:	// A or left
            is_left_button_down = false;
            current_map_type = current_map_type == MapType::MAP_0 ? MapType::MAP_2 : (MapType)((int)current_map_type - 1);
            mciSendString("play select_scene_switch from 0", NULL, 0, NULL);
            break;
        case 68:	case VK_RIGHT:  // D or right
            is_right_button_down = false;
            current_map_type = current_map_type == MapType::MAP_2 ? MapType::MAP_0 : (MapType)((int)current_map_type + 1);
            mciSendString("play select_scene_switch from 0", NULL, 0, NULL);
            break;
        }
    }
}

void SelectScene::on_update(int delta)
{
    camera.on_update(delta);
    camera_text_1.on_update(delta);
    camera_text_2.on_update(delta);
    camera_left_button.on_update(delta);
    camera_right_button.on_update(delta);

    timer_change_text_color.on_update(delta);

    if (is_special_mode_on)
    {
        animation_fire_background.on_update(delta);
    }

    if (img_P1_head_pos.y - 100 > getheight() || img_P1_head_pos.y + 120 < 0)
    {
        is_1P_move_up = !is_1P_move_up;

        // swap the position.x
        int temp_pos_x = img_P1_head_pos.x;
        img_P1_head_pos.x = img_P2_head_pos.x;
        img_P2_head_pos.x = temp_pos_x;
    }

    if (is_1P_move_up)
    {
        img_P1_head_pos.y -= 2;
        img_P2_head_pos.y += 2;
    }
    else
    {
        img_P1_head_pos.y += 2;
        img_P2_head_pos.y -= 2;
    }
}

void SelectScene::on_draw()
{
    // background
    putimage(0, 10, img_menu_scene_background);

    // 调暗一点
    putimage_alphablend(NULL, img_black_background, 0, 0, 0xd0);

    on_draw_special_mode();

    setbkmode(TRANSPARENT);
    setfont(70, 0, "Comic Sans MS");
    settextcolor(EGERGB(text_color_rand_r, text_color_rand_g, text_color_rand_b));
    char str[256] = "-- Choose a Map! --";
    outtextxy(camera_text_1, getwidth() / 2 - textwidth(str) / 2, 20, str);

    on_draw_player();

    on_draw_map();

    on_draw_button();

}

void SelectScene::on_exit()
{
    camera.stop_wandering();
    camera_text_1.stop_wandering();
    camera_text_2.stop_wandering();
    camera_left_button.stop_wandering();
    camera_right_button.stop_wandering();

    switch (current_map_type)
    {
    case MAP_0:
        current_map = map_0;
        break;
    case MAP_1:
        current_map = map_1;
        break;
    case MAP_2:
        current_map = map_2;
        break;
    default:
        break;
    }
}

void SelectScene::on_draw_special_mode()
{
    // special mode
    if (!is_special_mode_on)
    {
        setbkmode(TRANSPARENT);
        setfont(50, 0, "Comic Sans MS");
        settextcolor(EGERGB(text_color_rand_r, text_color_rand_g, text_color_rand_b));
        char str2[256] = "press SPACE: special mode!";
        outtextxy(camera_text_1, getwidth() / 2 - textwidth(str2) / 2, 640, str2);
    }
    else
    {	// 绘制火焰
        // putimage_alphablend(camera, NULL, img_fire_background, 
        //	getwidth() / 2 - getwidth(img_fire_background) / 2, 
        //	getheight() / 2 - getheight(img_fire_background) / 2, 
        //	0x30);
        animation_fire_background.on_draw(//camera,
            getwidth() / 2 - getwidth(animation_fire_background.get_current_frame()) / 2,
            getheight() / 2 - getheight(animation_fire_background.get_current_frame()) / 2 - 200,
            0x30);

        setbkmode(TRANSPARENT);
        setfont(60, 0, "Comic Sans MS");
        settextcolor(EGERGB(text_color_rand_r, text_color_rand_g, text_color_rand_b));
        char str2[256] = "SPECIAL MODE!!!";
        outtextxy(camera_text_2, getwidth() / 2 - textwidth(str2) / 2, 640, str2);
    }
}

void SelectScene::on_draw_button()
{
    // 绘制button
    if (is_left_button_down)
        putimage_alpha(camera_left_button, img_left_button_pos.x, img_left_button_pos.y, img_left_select_button_down);
    else
        putimage_alpha(camera_left_button, img_left_button_pos.x, img_left_button_pos.y, img_left_select_button_idle);

    if (is_right_button_down)
        putimage_alpha(camera_right_button, img_right_button_pos.x, img_right_button_pos.y, img_right_select_button_down);
    else
        putimage_alpha(camera_right_button, img_right_button_pos.x, img_right_button_pos.y, img_right_select_button_idle);
}

void SelectScene::on_draw_map()
{
    // 绘制地图缩略图
    // putimage_alpha(getwidth() / 2 - getwidth(img_select_edge) / 2, getheight() / 2 - getheight(img_select_edge) / 2, img_select_edge);
    putimage_transparent(camera, NULL, img_select_edge, getwidth() / 2 - getwidth(img_select_edge) / 2, getheight() / 2 - getheight(img_select_edge) / 2 + 20, BLACK);
    switch (current_map_type)
    {
    case MAP_0:
        putimage_alpha(camera, getwidth() / 2 - getwidth(img_map_0) / 2, getheight() / 2 - getheight(img_map_0) / 2 + 20, img_map_0);
        break;
    case MAP_1:
        putimage_alpha(camera, getwidth() / 2 - getwidth(img_map_1) / 2, getheight() / 2 - getheight(img_map_1) / 2 + 20, img_map_1);
        break;
    case MAP_2:
        putimage_alpha(camera, getwidth() / 2 - getwidth(img_map_2) / 2, getheight() / 2 - getheight(img_map_2) / 2 + 20, img_map_2);
        break;
    default:
        break;
    }
}

void SelectScene::on_draw_player()
{
    // 绘制player图案
    int offset = is_1P_move_up ? -20 : 20;
    PIMAGE& img_P1_head = is_1P_move_up ? img_P1_snake_head_up : img_P1_snake_head_down;
    PIMAGE& img_P2_head = is_1P_move_up ? img_P2_snake_head_down : img_P2_snake_head_up;
    putimage_alpha(img_P1_head_pos.x, img_P1_head_pos.y, img_P1_head);
    putimage_alpha(img_P1_head_pos.x, img_P1_head_pos.y - offset, img_P1_snake_body);
    putimage_alpha(img_P1_head_pos.x, img_P1_head_pos.y - offset * 2, img_P1_snake_body);
    putimage_alpha(img_P2_head_pos.x, img_P2_head_pos.y, img_P2_head);
    putimage_alpha(img_P2_head_pos.x, img_P2_head_pos.y + offset, img_P2_snake_body);
    putimage_alpha(img_P2_head_pos.x, img_P2_head_pos.y + offset * 2, img_P2_snake_body);
}
