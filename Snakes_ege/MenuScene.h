#pragma once

#include "SceneManager.h"
#include "Tools.h"
#include "Camera.h"

extern PIMAGE img_menu_scene_background;
extern PIMAGE img_black_background;
extern PIMAGE img_title;

extern int FPS;

extern bool is_running;

class MenuScene :
    public Scene
{

public:

	void on_enter() override;

	void on_input(key_msg& msg) override;

	void on_update(int delta) override;

	void on_draw() override;

	void on_exit() override;

private:

	Camera camera;

};

