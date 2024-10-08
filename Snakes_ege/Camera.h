#pragma once

#include "Timer.h"
#include "dPosition.h"

extern int FPS;

// 这种在各个类中都要使用的东西就要单独封装，且越独立越好，避免相互包含，便于调度管理
class Camera
{

private:

	enum WanderType
	{
		SQUARE,
		// CIRCLE,
		TRIANGLE,
		REVERSE_SQUARE,
		DOWN_TRIANGLE,
		SLASH,
		WANDER_TYPE_NUM,
	};

public:

	Camera();

	~Camera() = default;
	
	const dPosition& get_position() const;

	//重置camera位置到（0，0）处（有些游戏是重置到以玩家为中心的位置，就先将玩家指针设为全局变量，再extern玩家指针，在这里使用）
	void reset();

	void restart();

	void on_update(int delta);

	void shake(double strength, int shake_time);

	void wandering(double strength);

	void stop_wandering();

	bool check_if_shaking()	const;

	// int get_shake_time() const
	// {
	//	return this->shake_time;
	// }

private:

	void wander_square();
	
	void wander_reverse_square();

	void wander_triangle();

	void wander_down_triangle();

	void wander_slash();

private:

	dPosition position;	// camera坐标是窗口坐标左上角

	Timer timer_shake;				//摄像机抖动计时器
	bool is_shaking = false;		//摄像机是否抖动
	double shaking_strength = 0;	//摄像机抖动幅度
	int shake_time = 0;

	// Timer timer_wander;				//摄像机游晃计时器
	bool is_wandering = false;		//摄像机是否游晃
	double wandering_strength = 0;		//摄像机游晃幅度
	WanderType current_wander_type;	//当前游晃方式
	bool is_current_wander_end = true;		//当前游晃是否结束
	int count = 0;
	const double wander_speed = 4.0;

};

