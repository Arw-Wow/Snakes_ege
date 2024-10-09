#include "SceneManager.h"

SceneManager* SceneManager::get_instance()
{
    static SceneManager* instance = new SceneManager();
    return instance;
}

SceneManager::SceneManager()
{

}

// 用枚举降低耦合度，不用将头文件到处include

void SceneManager::switch_to(SceneType type)
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

void SceneManager::on_input(key_msg& msg)
{
	current_scene->on_input(msg);
}

void SceneManager::on_update(int delta)
{
	current_scene->on_update(delta);
}

void SceneManager::on_draw()
{
	current_scene->on_draw();
}
