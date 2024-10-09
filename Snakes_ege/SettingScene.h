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

	SettingScene();

	void on_enter() override;

	void on_input(key_msg& msg) override;

	void on_update(int delta) override;

	void on_draw() override;

	void on_exit() override;

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

