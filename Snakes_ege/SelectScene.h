#pragma once

#include "SceneManager.h"
#include "Map.h"
#include "Position.h"
#include "Tools.h"
#include "Timer.h"
#include "Animation.h"

extern PIMAGE img_P1_snake_head_up;
extern PIMAGE img_P1_snake_head_down;
extern PIMAGE img_P1_snake_body;
extern PIMAGE img_P2_snake_head_up;
extern PIMAGE img_P2_snake_head_down;
extern PIMAGE img_P2_snake_body;

extern PIMAGE img_left_select_button_idle;
extern PIMAGE img_left_select_button_down;
extern PIMAGE img_right_select_button_idle;
extern PIMAGE img_right_select_button_down;

extern PIMAGE img_map_0;
extern PIMAGE img_map_1;
extern PIMAGE img_map_2;

extern PIMAGE img_select_edge;
extern PIMAGE img_black_background;
extern PIMAGE img_menu_scene_background;
extern PIMAGE img_fire_background;

extern bool is_special_mode_on;

extern int FPS;

class SelectScene :
    public Scene
{

public:

	SelectScene();

	void on_enter() override;

	void on_input(key_msg& msg) override;

	void on_update(int delta) override;

	void on_draw() override;

	void on_exit() override;

private:

	void on_draw_special_mode();

	void on_draw_button();

	void on_draw_map();

	void on_draw_player();


private:

	MapType current_map_type = MapType::MAP_0;

	Position img_P1_head_pos = { 100, 100 };
	Position img_P2_head_pos = { 1160, 600 };
	Position img_left_button_pos = { 150, 350 };
	Position img_right_button_pos = { 1077, 350 };
	// Position text_pos;

	bool is_left_button_down = false;
	bool is_right_button_down = false;

	bool is_1P_move_up = false;

	int text_color_rand_r = 255;
	int text_color_rand_g = 255;
	int text_color_rand_b = 255;

	Timer timer_change_text_color;
	const int interval_change_text_color = 250;

	Animation animation_fire_background;

	Camera camera;
	Camera camera_text_1;
	Camera camera_text_2;
	Camera camera_left_button;
	Camera camera_right_button;

};

