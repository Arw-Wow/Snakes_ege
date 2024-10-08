#include "Camera.h"

Camera::Camera()
{
    //д�ڹ��캯������Ϊ�˴�����ͬʱ���ú�һЩ������������Ҫ���û���������
    timer_shake.set_one_shot(true);
    timer_shake.set_shot_callback(
        [&]() {
            //��ʱֹͣ���������������λ��
            is_shaking = false;
            this->reset();
        }
    );
}

const dPosition& Camera::get_position() const
{
    return position;
}

//����cameraλ�õ���0��0��������Щ��Ϸ�����õ������Ϊ���ĵ�λ�ã����Ƚ����ָ����Ϊȫ�ֱ�������extern���ָ�룬������ʹ�ã�

void Camera::reset()
{
    position.x = 0;
    position.y = 0;
}

void Camera::restart()
{
    reset();

    timer_shake.restart();
    is_shaking = false;
    shaking_strength = 0;

    is_wandering = false;
    wandering_strength = 0;
    is_current_wander_end = true;
    count = 0;
    // wander_speed = 4.0;

}

void Camera::on_update(int delta)
{
    timer_shake.on_update(delta);

    if (is_shaking)
    {	// -1 ~ 1 �����С�� ���� ҡ��ǿ��
        position.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
        position.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
    }

    if (is_wandering)
    {
        if (is_current_wander_end)
        {
            current_wander_type = (WanderType)(rand() % (int)WANDER_TYPE_NUM);
            is_current_wander_end = false;
        }

        switch (current_wander_type)
        {
        case Camera::SQUARE:
            wander_square();
            break;
            // case Camera::CIRCLE:
            //	wander_circle();
            //	break;
        case Camera::REVERSE_SQUARE:
            wander_reverse_square();
            break;
        case Camera::TRIANGLE:
            wander_triangle();
            break;
        case Camera::DOWN_TRIANGLE:
            wander_down_triangle();
            break;
        case Camera::SLASH:
            wander_slash();
            break;
        default:
            break;
        }
    }
}

void Camera::shake(double strength, int shake_time)
{
    is_shaking = true;
    shaking_strength = strength;
    this->shake_time = shake_time;
    timer_shake.set_wait_time(shake_time);
    timer_shake.restart();
}

void Camera::wandering(double strength)
{
    is_wandering = true;
    wandering_strength = strength;
    this->reset();
}

void Camera::stop_wandering()
{
    is_wandering = false;
    is_current_wander_end = false;
    count = 0;
    this->reset();
}

bool Camera::check_if_shaking() const
{
    return is_shaking;
}

void Camera::wander_square()
{
    if (count == 0)
    {
        position.x += wandering_strength;
        if (position.x >= (FPS / wander_speed) * wandering_strength)
            count++;
    }
    else if (count == 1)
    {
        position.y += wandering_strength;
        if (position.y >= (FPS / wander_speed) * wandering_strength)
            count++;
    }
    else if (count == 2)
    {
        position.x -= wandering_strength;
        if (position.x <= 0)
            count++;
    }
    else if (count == 3)
    {
        position.y -= wandering_strength;
        if (position.y <= 0)
        {
            count = 0;
            is_current_wander_end = true;
        }
    }
}

void Camera::wander_reverse_square()
{
    if (count == 0)
    {
        position.x -= wandering_strength;
        if (position.x <= -(FPS / wander_speed) * wandering_strength)
            count++;
    }
    else if (count == 1)
    {
        position.y -= wandering_strength;
        if (position.y <= -(FPS / wander_speed) * wandering_strength)
            count++;
    }
    else if (count == 2)
    {
        position.x += wandering_strength;
        if (position.x >= 0)
            count++;
    }
    else if (count == 3)
    {
        position.y += wandering_strength;
        if (position.y >= 0)
        {
            count = 0;
            is_current_wander_end = true;
        }
    }
}

void Camera::wander_triangle()
{
    if (count == 0)
    {
        position.x += wandering_strength;
        position.y += wandering_strength;
        if (position.x >= (FPS / wander_speed) * wandering_strength)
            count++;
    }
    else if (count == 1)
    {
        position.x -= wandering_strength * 2;
        if (position.x <= -(FPS / wander_speed) * wandering_strength)
            count++;
    }
    else if (count == 2)
    {
        position.x += wandering_strength;
        position.y -= wandering_strength;
        if (position.x >= 0)
        {
            count = 0;
            is_current_wander_end = true;
        }
    }
}

void Camera::wander_down_triangle()
{
    if (count == 0)
    {
        position.x -= wandering_strength;
        position.y -= wandering_strength;
        if (position.x <= -(FPS / wander_speed) * wandering_strength)
            count++;
    }
    else if (count == 1)
    {
        position.x += wandering_strength * 2;
        if (position.x >= (FPS / wander_speed) * wandering_strength)
            count++;
    }
    else if (count == 2)
    {
        position.x -= wandering_strength;
        position.y += wandering_strength;
        if (position.x <= 0)
        {
            count = 0;
            is_current_wander_end = true;
        }
    }
}

void Camera::wander_slash()
{
    if (count == 0)
    {
        position.x -= wandering_strength;
        position.y -= wandering_strength;
        if (position.x <= (FPS / wander_speed) * wandering_strength)
            count++;
    }
    else if (count == 1)
    {
        position.x += wandering_strength;
        position.y += wandering_strength;
        if (position.x >= 0)
        {
            count = 0;
            is_current_wander_end = true;
        }
    }
}

