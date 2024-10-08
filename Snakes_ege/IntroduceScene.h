#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "Tools.h"

extern PIMAGE img_black_background;
extern PIMAGE img_menu_scene_background;

class IntroduceScene :
    public Scene
{

public:

	IntroduceScene();

	void on_enter() override;

	void on_input(key_msg& msg) override;

	void on_update(int delta) override;

	void on_draw() override;

	void on_exit() override;

private:

	Position player_1_text_pos;
	Position player_2_text_pos;
	Position other_text_pos;

	Timer timer_change_text_color;
	const int interval_change_text_color = 250;

	int text_color_rand_r = 255;
	int text_color_rand_g = 255;
	int text_color_rand_b = 255;

	Camera text_camera;

};

