#include "SettingScene.h"

void SettingScene::on_enter()
{
    camera_option_1.wandering(0.2);
    camera_option_2.wandering(0.2);
    camera_option_3.wandering(0.2);

    current_option_type = OptionType::DRAW_LINE;

    timer_change_text_color.restart();
}
