#include "Player_2.h"

Player_2::Player_2()
{
    Player::Player();

    snake_list.push_back(Position(Map_Width - 3, Map_Height - 3));
    for (int i = 0; i < ORIGINAL_BODY_NUM; i++)	// 初始体节
    {
        snake_list.push_back(get_current_head_position());
    }
    current_head_type = BlockType::P2_HEAD_LEFT;
    last_head_type = current_head_type;
}

void Player_2::on_input(key_msg msg)
{
    if (msg.msg & key_msg_down)
    {
        switch (msg.key)
        {
        case VK_UP:		// up
            if (current_head_type == BlockType::P2_HEAD_DOWN)	break;
            current_head_type = BlockType::P2_HEAD_UP;
            break;
        case VK_DOWN:	// down
            if (current_head_type == BlockType::P2_HEAD_UP)		break;
            current_head_type = BlockType::P2_HEAD_DOWN;
            break;
        case VK_LEFT:	// left
            if (current_head_type == BlockType::P2_HEAD_RIGHT)	break;
            current_head_type = BlockType::P2_HEAD_LEFT;
            break;
        case VK_RIGHT:	// right
            if (current_head_type == BlockType::P2_HEAD_LEFT)	break;
            current_head_type = BlockType::P2_HEAD_RIGHT;
            break;
        }
    }
}

void Player_2::on_update(int delta)
{
    Player::on_update(delta);
}

void Player_2::reset()
{
    Player::reset();

    snake_list.push_back(Position(Map_Width - 3, Map_Height - 3));
    for (int i = 0; i < ORIGINAL_BODY_NUM; i++)	// 初始体节
    {
        snake_list.push_back(get_current_head_position());
    }
    current_head_type = BlockType::P2_HEAD_LEFT;
    last_head_type = current_head_type;
}
