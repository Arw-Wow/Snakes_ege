#include "Player.h"

Player::Player()
{
    timer_can_move.set_one_shot(false);
    timer_can_move.set_wait_time(current_speed_normal);
    timer_can_move.set_shot_callback(
        [&]() {
            is_can_move = true;
        }
    );

    timer_speed_up.set_one_shot(true);
    timer_speed_up.set_wait_time(speed_up_time);
    timer_speed_up.set_shot_callback(
        [&]() {
            is_speed_up = false;
            timer_can_move.set_wait_time(current_speed_normal);
        }
    );

    timer_shitting.set_one_shot(true);
    timer_shitting.set_wait_time(shitting_time);
    timer_shitting.set_shot_callback(
        [&]() {
            is_shitting = false;
        }
    );

    timer_invincible.set_one_shot(true);
    timer_invincible.set_wait_time(invicible_time);
    timer_invincible.set_shot_callback(
        [&]() {
            is_invincible = false;
        }
    );
}

void Player::on_input(key_msg msg)
{

}

void Player::on_update(int delta)
{
    if (is_dead)
        return;

    if (is_speed_up)
    {
        timer_speed_up.on_update(delta);
    }

    if (is_shitting)
    {
        timer_shitting.on_update(delta);
        on_shitting();
    }

    if (is_invincible)
    {
        timer_invincible.on_update(delta);
    }

    timer_can_move.on_update(delta);

    if (is_can_move)
    {
        is_can_move = false;

        on_move();

        // check if dead or if eat
        Position& player_head_pos = get_current_head_position();
        BlockType player_head_pos_type = game_map[player_head_pos.y][player_head_pos.x];
        if (check_if_out_of_map() || (!is_invincible && is_solid_block(player_head_pos_type)))
            on_dead();
        if (is_object_block(player_head_pos_type))
            eat_object(player_head_pos_type);
    }
}

void Player::on_draw()
{
    if (is_dead)
        return;

    // 加速特效
    if (is_speed_up)
    {
        for (Position& pos : snake_list)
        {
            putimage_alphablend(camera, NULL, img_player_speed_up_effect, (pos.x - 1) * Block_Width, (pos.y - 1) * Block_Height, 0x80);
        }
    }

    // 无敌特效
    if (is_invincible)
    {
        for (Position& pos : snake_list)
        {
            putimage_alphablend(camera, NULL, img_player_invincible_effect, (pos.x - 1) * Block_Width, (pos.y - 1) * Block_Height, 0xa0);
        }
    }
}

void Player::reset()
{
    snake_list.clear();

    is_dead = false;

    switch (current_speed_mode)
    {
    case Player::LOW_SPEED:
        current_speed_normal = low_speed_normal;
        current_speed_fast = low_speed_fast;
        break;
    case Player::MEDIUM_SPEED:
        current_speed_normal = medium_speed_normal;
        current_speed_fast = medium_speed_fast;
        break;
    case Player::HIGH_SPEED:
        current_speed_normal = high_speed_normal;
        current_speed_fast = high_speed_fast;
        break;
    }

    timer_can_move.set_wait_time(current_speed_normal);
    timer_can_move.restart();
    is_can_move = false;

    timer_speed_up.restart();
    is_speed_up = false;

    timer_shitting.restart();
    is_shitting = false;

    timer_invincible.restart();
    is_invincible = false;

}

void Player::on_move()
{

}

void Player::on_shitting()
{
    Position& tail_pos = this->get_current_tail_position();
    game_map[tail_pos.y][tail_pos.x] = BlockType::SHIT;
}

std::vector<Position>& Player::get_snake_list()
{
    return snake_list;
}

BlockType Player::get_current_head_type() const
{
    return current_head_type;
}

Position& Player::get_current_head_position()
{
    return snake_list[0];
}

Position& Player::get_current_tail_position()
{
    return snake_list[snake_list.size() - 1];
}

void Player::eat_object(BlockType type)
{
    switch (type)
    {
    case FOOD:
        eat_food();
        break;
    case STIMULANT:
        eat_stimulant();
        mciSendString("play speed_up_sound from 0", NULL, 0, NULL);
        camera.shake(4.5, 400);
        break;
    case LAXATIVE:
        eat_laxative();
        mciSendString("play shitting_sound from 0", NULL, 0, NULL);
        camera.shake(3, 900);
        break;
    case PILL:
        eat_pill();
        // 给吃药加个音效 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        camera.shake(4, 300);
        break;
    }
    mciSendString("play eat_sound from 0", NULL, 0, NULL);
}

bool Player::check_if_dead() const
{
    return is_dead;
}

void Player::on_dead()
{
    is_dead = true;
    mciSendString("play be_attacked_sound from 0", NULL, 0, NULL);
}

void Player::on_win()
{
    win_num++;
}

int Player::get_win_num() const
{
    return win_num;
}

void Player::set_speed_mode(PlayerSpeedMode speed_mode)
{
    current_speed_mode = speed_mode;
}

bool Player::check_if_invincible() const
{
    return is_invincible;
}

void Player::eat_food()
{
    Position& tail_pos = this->get_current_tail_position();
    snake_list.push_back(tail_pos);
}

void Player::eat_stimulant()
{
    is_speed_up = true;
    timer_can_move.set_wait_time(current_speed_fast);
    timer_speed_up.restart();
}

void Player::eat_laxative()
{
    is_shitting = true;
    timer_shitting.restart();
}

void Player::eat_pill()
{
    is_invincible = true;
    timer_invincible.restart();
}

bool Player::check_if_out_of_map()
{
    Position& head_pos = get_current_head_position();

    return (head_pos.x >= Map_Width - 1 || head_pos.x <= 0 ||
        head_pos.y >= Map_Height - 1 || head_pos.y <= 0);
}
