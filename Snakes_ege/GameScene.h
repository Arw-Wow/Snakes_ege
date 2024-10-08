#pragma once

#include <cstring>
#include "SceneManager.h"
#include "Player.h"
#include "Block.h"
#include "Map.h"
#include "Tools.h"
#include "Animation.h"

extern PIMAGE img_P1_snake_head_up;
extern PIMAGE img_P1_snake_head_down;
extern PIMAGE img_P1_snake_head_left;
extern PIMAGE img_P1_snake_head_right;
extern PIMAGE img_P1_snake_body;

extern PIMAGE img_P2_snake_head_up;
extern PIMAGE img_P2_snake_head_down;
extern PIMAGE img_P2_snake_head_left;
extern PIMAGE img_P2_snake_head_right;
extern PIMAGE img_P2_snake_body;

extern PIMAGE img_food;
extern PIMAGE img_stimulant;
extern PIMAGE img_laxative;
extern PIMAGE img_shit;
extern PIMAGE img_pill;
extern PIMAGE img_wall;
extern PIMAGE img_fire;

// extern PIMAGE img_P1_avatar;
// extern PIMAGE img_P2_avatar;
extern PIMAGE img_P1_avatar_edge;
extern PIMAGE img_P2_avatar_edge;
extern PIMAGE img_victory;
extern PIMAGE img_P1_avatar_die;
extern PIMAGE img_P2_avatar_die;

extern PIMAGE img_game_over;
// extern PIMAGE img_game_scene_background;
extern PIMAGE img_black_background;
extern PIMAGE img_game_scene_ui_background;

extern Player* player_1;
extern Player* player_2;

extern BlockType** game_map;

extern bool is_special_mode_on;
extern bool is_draw_line_on;
extern bool is_draw_background_on;
extern Player::PlayerSpeedMode speed_mode;

extern int FPS;

extern Camera camera;


class GameScene :
    public Scene
{

public:

	GameScene();
	
public:

	void on_enter() override;

	void on_input(key_msg& msg) override;
	
	void on_update(int delta) override;

	void on_draw() override;
	
	void on_exit() override;

private:

	void on_draw_map();
	
	void on_draw_background();

	void on_draw_line();

	void clear_map();

	void generate_object(int delta);

	void generate_food();

	void generate_stimulant();

	void generate_laxative();

	void generate_pill();

	void on_update_map();
	
	void on_update_fire(int delta);

	void on_draw_ui();

	void on_draw_game_over();

private:

	bool is_game_over = false;

	bool is_pause = false;
	
	Timer timer_game_over_flash;
	bool is_game_over_visible = true;

	Timer timer_generate_object;
	bool is_can_generate_object = false;
	const int interval_generate_object = 1200;

	Timer timer_fire_spread;	// ¿ØÖÆ»ðÑæÂûÑÓËÙ¶È
	bool is_can_fire_spread = false;
	const int interval_fire_spread = 30;
	Position current_fire_spread_pos;
	int fire_spread_direction_x = 1;
	int fire_spread_direction_y = 0;

	Timer timer_control_fire_spread;	// ¿ØÖÆ»ðÑæÊÇ·ñÂûÑÓ
	bool is_can_fire_spread_uncontrol;
	const int interval_control_fire_spread = 8000;

	Camera camera_fire;

	Position player_1_avatar_pos;
	Position player_2_avatar_pos;
	Position player_1_avatar_edge_pos;
	Position player_2_avatar_edge_pos;
	Position player_1_win_num_text_pos;
	Position player_2_win_num_text_pos;
	Position fire_next_spread_time_text_pos;
	Position fire_spread_text_pos;

	Animation animation_background;
	Animation animation_P1_avatar;
	Animation animation_P2_avatar;

};

