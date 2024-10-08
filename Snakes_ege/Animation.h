#pragma once

#include <graphics.h>
#include <vector>
#include "Timer.h"
#include "Tools.h"

class Animation
{

public:

	Animation();

	void load_img_list(const char* img_address, int img_num, int w = 0, int h = 0);

	void set_loop(bool in);

	void set_interval(int interval);

	bool check_if_finished() const;

	PIMAGE& get_current_frame();

	void restart();

	void on_update(int delta);

	void on_draw(int x, int y);

	void on_draw(int x, int y, unsigned char alpha);

	void on_draw(const Camera& camera, int x, int y);

	void on_draw(const Camera& camera, int x, int y, unsigned char alpha);

private:

	std::vector<PIMAGE> img_list;
	int current_img_index = 0;

	bool is_loop = true;
	bool is_finished = false;

	Timer timer_display_next_image;
	bool is_can_display_next_image = false;

	int interval = 200;

};

