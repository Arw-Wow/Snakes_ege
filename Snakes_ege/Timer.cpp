#include "Timer.h"

void Timer::restart()
{
    pass_time = 0;
    shotted = false;
}

void Timer::set_wait_time(int val)
{
    wait_time = val;
}

void Timer::set_one_shot(bool in)
{
    one_shot = in;
}

void Timer::set_shot_callback(std::function<void()> callback)
{
    this->shot_callback = callback;
}

void Timer::pause()
{
    paused = true;
}

void Timer::resume()
{
    paused = false;
}

void Timer::on_update(int delta)
{
    // 不需要写start函数来启动timer，因为timer只有在update时才会累加时间，第一次调用update就是start了

    //如果暂停就不更新
    if (paused)
        return;

    pass_time += delta;
    if (pass_time >= wait_time)
    {
        // 如果callback未被设置，就不触发。如果callback被设置了：如果不是单次触发，就直接到时触发；如果是单次触发，但是还未被触发过，也直接到时触发。
        if ((!one_shot || (one_shot && !shotted)) && shot_callback)
            shot_callback();

        shotted = true;

        if (!one_shot)
            pass_time -= wait_time;
        else
            pass_time = 0;
    }


}

int Timer::get_pass_time() const
{
    return pass_time;
}
