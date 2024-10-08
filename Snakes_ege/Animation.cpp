#include "Animation.h"

Animation::Animation()
{
    timer_display_next_image.set_one_shot(false);
    timer_display_next_image.set_shot_callback(
        [&]() {
            is_can_display_next_image = true;
        }
    );
}

void Animation::load_img_list(const char* img_address, int img_num, int w, int h)
{
    for (PIMAGE& img : img_list)
        delimage(img);
    img_list.clear();
    img_list.resize(img_num);

    for (PIMAGE& img : img_list)
        img = newimage();

    char file_name[256] = { 0 };
    for (int i = 0; i < img_num; i++)
    {
        sprintf_s(file_name, sizeof(file_name), img_address, i);
        if (w == 0 && h == 0)
            getimage(img_list[i], file_name);
        else
            get_zoom_image(img_list[i], file_name, w, h);
    }
}

void Animation::set_loop(bool in)
{
    is_loop = in;
}

void Animation::set_interval(int interval)
{
    this->interval = interval;
    timer_display_next_image.set_wait_time(interval);
}

bool Animation::check_if_finished() const
{
    return is_finished;
}

PIMAGE& Animation::get_current_frame()
{
    return img_list[current_img_index];
}

void Animation::restart()
{
    current_img_index = 0;
}

void Animation::on_update(int delta)
{
    timer_display_next_image.on_update(delta);

    if (is_can_display_next_image && !is_finished)
    {
        if (current_img_index >= img_list.size() - 1)
        {
            if (is_loop)
            {
                current_img_index = 0;
            }
            else
            {
                current_img_index = img_list.size() - 1;
                is_finished = true;
            }
        }
        else
        {
            current_img_index++;
        }

        is_can_display_next_image = false;
    }
}

void Animation::on_draw(int x, int y)
{
    putimage_alpha(x, y, (img_list[current_img_index]));
}

void Animation::on_draw(int x, int y, unsigned char alpha)
{
    putimage_alphablend(NULL, img_list[current_img_index], x, y, alpha);
}

void Animation::on_draw(const Camera& camera, int x, int y)
{
    putimage_alpha(camera, x, y, (img_list[current_img_index]));
}

void Animation::on_draw(const Camera& camera, int x, int y, unsigned char alpha)
{
    putimage_alphablend(camera, NULL, img_list[current_img_index], x, y, alpha);
}
