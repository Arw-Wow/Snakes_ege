#pragma once

#include <graphics.h>
#include <vector>
#include "Block.h"
#include "Position.h"
#include "Map.h"
#include "Timer.h"
#include "Tools.h"

extern PIMAGE img_player_speed_up_effect;
extern PIMAGE img_player_invincible_effect;

extern BlockType** game_map;

extern Camera camera;


constexpr int ORIGINAL_BODY_NUM = 2;


class Player
{

public:

	enum PlayerSpeedMode
	{
		LOW_SPEED,
		MEDIUM_SPEED,
		HIGH_SPEED,
		MODE_NUM,
	};

	// enum HeadDirection
	// {
	//	HEAD_UP,
	//	HEAD_DOWN,
	//	HEAD_LEFT,
	//	HEAD_RIGHT,
	// };

public:

	Player();

	virtual void on_input(key_msg msg);

	virtual void on_update(int delta);

	virtual void on_draw();

	virtual void reset();

	virtual void on_move();

	void on_shitting();

	std::vector<Position>& get_snake_list();

	BlockType get_current_head_type() const;

	Position& get_current_head_position();

	Position& get_current_tail_position();

	void eat_object(BlockType type);

	bool check_if_dead() const;

	void on_dead();

	void on_win();

	int get_win_num() const;

	void set_speed_mode(PlayerSpeedMode speed_mode);

	bool check_if_invincible() const;

	// void set_speed_up(bool in)
	// {
	//	is_speed_up = in;
	// }

	// bool check_if_speed_up() const
	// {
	//	return is_speed_up;
	// }

protected:

	void eat_food();

	void eat_stimulant();

	void eat_laxative();

	void eat_pill();

	bool check_if_out_of_map();

	// void reset_moving()
	// {
	//	is_moving_up = false;
	//	is_moving_down = false;
	//	is_moving_left = false;
	//	is_moving_right = false;
	// }

protected:

	std::vector<Position> snake_list;	// 0是头，后面是尾

	BlockType current_head_type;
	BlockType last_head_type;

	bool is_dead = false;

	int win_num = 0;

	Timer timer_can_move;
	bool is_can_move = false;

	Timer timer_speed_up;
	bool is_speed_up = false;
	const int speed_up_time = 2400;

	Timer timer_shitting;
	bool is_shitting = false;
	const int shitting_time = 800;

	Timer timer_invincible;
	bool is_invincible = false;
	const int invicible_time = 3000;

	//2400倍数可同步
	const int low_speed_normal = 120;	// 越小越快
	const int low_speed_fast = 75;		// 加速，移动间隔缩小为原来的5/8

	const int medium_speed_normal = 80;
	const int medium_speed_fast = 50;

	const int high_speed_normal = 56;
	const int high_speed_fast = 35;

	int current_speed_normal = medium_speed_normal;
	int current_speed_fast = medium_speed_fast;

	PlayerSpeedMode current_speed_mode = MEDIUM_SPEED;

};

