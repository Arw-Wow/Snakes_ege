#pragma once
#include "Player.h"

class Player_2 :
    public Player
{

public:
	
	Player_2();

	void on_input(key_msg msg) override;

	void on_update(int delta) override;

	void reset() override;

	void on_move() override
	{
		// 防自杀机制（若在一次update时间内多次改变方向导致最后方向是指向当前相反方向，那么应该无效化这次改变方向的操作，否则会直接“自杀”）
		if (last_head_type == BlockType::P2_HEAD_DOWN && current_head_type == BlockType::P2_HEAD_UP ||
			last_head_type == BlockType::P2_HEAD_UP && current_head_type == BlockType::P2_HEAD_DOWN ||
			last_head_type == BlockType::P2_HEAD_LEFT && current_head_type == BlockType::P2_HEAD_RIGHT ||
			last_head_type == BlockType::P2_HEAD_RIGHT && current_head_type == BlockType::P2_HEAD_LEFT)
			current_head_type = last_head_type;

		Position& current_head_pos = this->get_current_head_position();
		switch (current_head_type)
		{
		case P2_HEAD_UP:
			snake_list.insert(snake_list.begin(), Position(current_head_pos.x, current_head_pos.y - 1));
			break;
		case P2_HEAD_DOWN:
			snake_list.insert(snake_list.begin(), Position(current_head_pos.x, current_head_pos.y + 1));
			break;
		case P2_HEAD_LEFT:
			snake_list.insert(snake_list.begin(), Position(current_head_pos.x - 1, current_head_pos.y));
			break;
		case P2_HEAD_RIGHT:
			snake_list.insert(snake_list.begin(), Position(current_head_pos.x + 1, current_head_pos.y));
			break;
		default:
			break;
		}
		snake_list.pop_back();

		last_head_type = current_head_type;
	}
};

