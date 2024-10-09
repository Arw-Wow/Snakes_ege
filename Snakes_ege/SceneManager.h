#pragma once

#include "Scene.h"
#include "SceneType.h"

extern Scene* menu_scene;
extern Scene* introduce_scene;
extern Scene* select_scene;
extern Scene* setting_scene;
extern Scene* game_scene;

class SceneManager
{

public:

	static SceneManager* get_instance();

private:

	SceneManager();

public:

	// void set_current_scene(Scene* scene)
	// {
	//	if (current_scene)
	//		current_scene->on_exit();

	//	current_scene = scene;

	//	current_scene->on_enter();
	// }

	// 用枚举降低耦合度，不用将头文件到处include
	void switch_to(SceneType type);

	void on_input(key_msg& msg);

	void on_update(int delta);

	void on_draw();

private:

	Scene* current_scene = nullptr;

};

