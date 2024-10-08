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

	static SceneManager* get_instance()
	{
		static SceneManager* instance = new SceneManager();
		return instance;
	}

private:

	SceneManager() 
	{
	}

public:

	// void set_current_scene(Scene* scene)
	// {
	//	if (current_scene)
	//		current_scene->on_exit();

	//	current_scene = scene;

	//	current_scene->on_enter();
	// }

	// 用枚举降低耦合度，不用将头文件到处include
	void switch_to(SceneType type)
	{
		if (current_scene)
			current_scene->on_exit();

		switch (type)
		{
		case MENU_SCENE:
			current_scene = menu_scene;
			break;
		case INTRODUCE_SCENE:
			current_scene = introduce_scene;
			break;
		case SELECT_SCENE:
			current_scene = select_scene;
			break;
		case SETTING_SCENE:
			current_scene = setting_scene;
			break;
		case GAME_SCENE:
			current_scene = game_scene;
			break;
		}

		current_scene->on_enter();
	}

	void on_input(key_msg& msg)
	{
		current_scene->on_input(msg);
	}

	void on_update(int delta)
	{
		current_scene->on_update(delta);
	}

	void on_draw()
	{
		current_scene->on_draw();
	}


private:

	Scene* current_scene = nullptr;

};

