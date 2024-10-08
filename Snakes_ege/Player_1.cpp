#include "Player_1.h"

Player_1::Player_1()
{
    Player::Player();

    snake_list.push_back(Position(2, 2));
    for (int i = 0; i < ORIGINAL_BODY_NUM; i++)	// 初始体节
    {
        snake_list.push_back(get_current_head_position());
    }
    current_head_type = BlockType::P1_HEAD_RIGHT;
    last_head_type = current_head_type;
}

void Player_1::on_input(key_msg msg)
{
    if (msg.msg & key_msg_down)
    {
        switch (msg.key)
        {
        case 87:	// w
            current_head_type = BlockType::P1_HEAD_UP;
            break;
        case 83:	// s
            current_head_type = BlockType::P1_HEAD_DOWN;
            break;
        case 65:	// a
            current_head_type = BlockType::P1_HEAD_LEFT;
            break;
        case 68:	// d
            current_head_type = BlockType::P1_HEAD_RIGHT;
            break;
        }
    }
}

void Player_1::on_update(int delta)
{
    Player::on_update(delta);
}

void Player_1::reset()
{
    Player::reset();

    snake_list.push_back(Position(2, 2));
    for (int i = 0; i < ORIGINAL_BODY_NUM; i++)	// 初始体节
    {
        snake_list.push_back(get_current_head_position());
    }
    current_head_type = BlockType::P1_HEAD_RIGHT;
    last_head_type = current_head_type;
}

void Player_1::on_move()
{
    // 防自杀机制（若在一次update时间内多次改变方向导致最后方向是指向当前相反方向，那么应该无效化这次改变方向的操作，否则会直接“自杀”）
    if (last_head_type == BlockType::P1_HEAD_DOWN && current_head_type == BlockType::P1_HEAD_UP ||
        last_head_type == BlockType::P1_HEAD_UP && current_head_type == BlockType::P1_HEAD_DOWN ||
        last_head_type == BlockType::P1_HEAD_LEFT && current_head_type == BlockType::P1_HEAD_RIGHT ||
        last_head_type == BlockType::P1_HEAD_RIGHT && current_head_type == BlockType::P1_HEAD_LEFT)
        current_head_type = last_head_type;

    Position& current_head_pos = this->get_current_head_position();
    switch (current_head_type)
    {
    case P1_HEAD_UP:
        snake_list.insert(snake_list.begin(), Position(current_head_pos.x, current_head_pos.y - 1));
        break;
    case P1_HEAD_DOWN:
        snake_list.insert(snake_list.begin(), Position(current_head_pos.x, current_head_pos.y + 1));
        break;
    case P1_HEAD_LEFT:
        snake_list.insert(snake_list.begin(), Position(current_head_pos.x - 1, current_head_pos.y));
        break;
    case P1_HEAD_RIGHT:
        snake_list.insert(snake_list.begin(), Position(current_head_pos.x + 1, current_head_pos.y));
        break;
    default:
        break;
    }
    snake_list.pop_back();

    last_head_type = current_head_type;
}
