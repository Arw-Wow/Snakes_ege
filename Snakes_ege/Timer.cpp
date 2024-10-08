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
    // ����Ҫдstart����������timer����Ϊtimerֻ����updateʱ�Ż��ۼ�ʱ�䣬��һ�ε���update����start��

    //�����ͣ�Ͳ�����
    if (paused)
        return;

    pass_time += delta;
    if (pass_time >= wait_time)
    {
        // ���callbackδ�����ã��Ͳ����������callback�������ˣ�������ǵ��δ�������ֱ�ӵ�ʱ����������ǵ��δ��������ǻ�δ����������Ҳֱ�ӵ�ʱ������
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
