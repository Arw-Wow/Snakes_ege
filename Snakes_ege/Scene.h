#pragma once

#include <graphics.h>

class Scene
{

protected:

	Scene();

public:

	virtual void on_enter();
	
	virtual void on_input(key_msg& msg);

	virtual void on_update(int delta);

	virtual void on_draw();

	virtual void on_exit();

protected:

};

