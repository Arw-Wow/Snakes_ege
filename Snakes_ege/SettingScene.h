#pragma once

// #include <string>

#include "Scene.h"
#include "SceneManager.h"
#include "Tools.h"
#include "Player.h"


extern PIMAGE img_black_background;
extern PIMAGE img_menu_scene_background;
extern PIMAGE img_select_highlight;

extern bool is_draw_line_on;
extern bool is_draw_background_on;
extern Player::PlayerSpeedMode speed_mode;

class SettingScene :
    public Scene
{

private:

	enum OptionType
	{
		DRAW_LINE,
		DRAW_BACKGROUND,
		PLAYER_SPEED,
		OPTION_NUM,
	};

public:

	SettingScene()
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

		option_draw_line_pos = { 350, 140 };
		option_draw_backround_pos = { 250, option_draw_line_pos.y + getheight(img_select_highlight) };
		option_player_speed_pos = { 300, option_draw_line_pos.y + getheight(img_select_highlight) * 2 };
		option_player_speed_status_pos = { 800, option_player_speed_pos.y };
	}

	void on_enter() override;

	void on_input(key_msg& msg) override
	{
		if (msg.msg & key_msg_down)
		{
			switch (msg.key)
			{
			case VK_RETURN:
				SceneManager::get_instance()->switch_to(SceneType::GAME_SCENE);
				mciSendString("play select_scene_confirm from 0", NULL, 0, NULL);
				break;
			}
		}
		if (msg.msg & key_msg_up)
		{
			switch (msg.key)
			{
			case 65:	case 68:	case VK_LEFT:	case VK_RIGHT:	case VK_SPACE:  // A or D or left or right or space
				switch (current_option_type)
				{
				case SettingScene::DRAW_LINE:
					is_draw_line_on = !is_draw_line_on;
					break;
				case SettingScene::DRAW_BACKGROUND:
					is_draw_background_on = !is_draw_background_on;
					break;
				case SettingScene::PLAYER_SPEED:
					if (msg.key == 65 || msg.key == VK_LEFT)
						speed_mode = speed_mode == Player::PlayerSpeedMode::LOW_SPEED ? Player::PlayerSpeedMode::HIGH_SPEED : (Player::PlayerSpeedMode)((int)speed_mode - 1);
					else
						speed_mode = speed_mode == Player::PlayerSpeedMode::HIGH_SPEED ? Player::PlayerSpeedMode::LOW_SPEED : (Player::PlayerSpeedMode)((int)speed_mode + 1);
					break;
				}
				mciSendString("play select_scene_switch from 0", NULL, 0, NULL);
				break;
			case 87:	case VK_UP:
				current_option_type = current_option_type == OptionType::DRAW_LINE ? OptionType::PLAYER_SPEED : (OptionType)((int)current_option_type - 1);
				// mciSendString("play select_scene_switch from 0", NULL, 0, NULL);
				break;
			case 83:	case VK_DOWN:
				current_option_type = current_option_type == OptionType::PLAYER_SPEED ? OptionType::DRAW_LINE : (OptionType)((int)current_option_type + 1);
				// mciSendString("play select_scene_switch from 0", NULL, 0, NULL);
				break;
			}
		}
	}

	void on_update(int delta) override
	{
		timer_change_text_color.on_update(delta);

		camera_option_1.on_update(delta);
		camera_option_2.on_update(delta);
		camera_option_3.on_update(delta);

		// 更新highlight位置
		switch (current_option_type)
		{
		case SettingScene::DRAW_LINE:
			img_select_highlight_pos = { 0, option_draw_line_pos.y + textheight(option_draw_line_text) / 2 - getheight(img_select_highlight) / 2 };
			break;
		case SettingScene::DRAW_BACKGROUND:
			img_select_highlight_pos = { 0, option_draw_backround_pos.y + textheight(option_draw_backround_text) / 2 - getheight(img_select_highlight) / 2 };
			break;
		case SettingScene::PLAYER_SPEED:
			img_select_highlight_pos = { 0, option_player_speed_pos.y + textheight(option_player_speed_text) / 2 - getheight(img_select_highlight) / 2 };
			break;
		}

	}

	void on_draw() override
	{
		// background
		putimage(0, 10, img_menu_scene_background);

		// 调暗一点
		putimage_alphablend(NULL, img_black_background, 0, 0, 0xd0);

		setbkmode(TRANSPARENT);
		setfont(70, 0, "Comic Sans MS");
		settextcolor(EGERGB(text_color_rand_r, text_color_rand_g, text_color_rand_b));

		// 绘制highlight
		putimage_alphablend(NULL, img_select_highlight, img_select_highlight_pos.x, img_select_highlight_pos.y, 0x50);
		
		// 绘制文字
		outtextxy(camera_option_1, option_draw_line_pos.x, option_draw_line_pos.y, option_draw_line_text);
		option_status_pos = { 800, option_draw_line_pos.y };
		outtextxy(camera_option_1, option_status_pos.x, option_status_pos.y, option_status[is_draw_line_on]);

		outtextxy(camera_option_2, option_draw_backround_pos.x, option_draw_backround_pos.y, option_draw_backround_text);
		option_status_pos = { 800, option_draw_backround_pos.y };
		outtextxy(camera_option_2, option_status_pos.x, option_status_pos.y, option_status[is_draw_background_on]);

		outtextxy(camera_option_3, option_player_speed_pos.x, option_player_speed_pos.y, option_player_speed_text);
		// option_player_speed_status_pos = { 800, option_player_speed_pos.y };
		outtextxy(camera_option_3, option_player_speed_status_pos.x, option_player_speed_status_pos.y, option_player_speed_status[(int)speed_mode]);

	}

	void on_exit() override
	{
		camera_option_1.stop_wandering();
		camera_option_2.stop_wandering();
		camera_option_3.stop_wandering();

		mciSendString("stop menu_scene_bgm", NULL, 0, NULL);
	}

	// bool check_if_draw_line() const
	// {
	//	return is_draw_line_on;
	// }

	// bool check_if_draw_background() const
	// {
	//	return is_draw_background_on;
	// }

private:

	char option_status[2][5] = { "OFF", "ON" };
	char option_player_speed_status[3][8] = { "LOW", "MEDIUM", "HIGH" };

	char option_draw_line_text[256] = "draw line:";
	char option_draw_backround_text[256] = "draw background:";
	char option_player_speed_text[256] = "player speed:";

	Position option_draw_line_pos;
	Position option_draw_backround_pos;
	Position option_player_speed_pos;
	Position img_select_highlight_pos;
	Position option_status_pos;
	Position option_player_speed_status_pos;

	OptionType current_option_type = OptionType::DRAW_LINE;

	int text_color_rand_r = 255;
	int text_color_rand_g = 255;
	int text_color_rand_b = 255;

	Timer timer_change_text_color;
	const int interval_change_text_color = 250;

	Camera camera;
	Camera camera_option_1;
	Camera camera_option_2;
	Camera camera_option_3;

};

