#pragma once

#include "Timer.h"
#include "dPosition.h"

extern int FPS;

// �����ڸ������ж�Ҫʹ�õĶ�����Ҫ������װ����Խ����Խ�ã������໥���������ڵ��ȹ���
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

	//����cameraλ�õ���0��0��������Щ��Ϸ�����õ������Ϊ���ĵ�λ�ã����Ƚ����ָ����Ϊȫ�ֱ�������extern���ָ�룬������ʹ�ã�
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

	dPosition position;	// camera�����Ǵ����������Ͻ�

	Timer timer_shake;				//�����������ʱ��
	bool is_shaking = false;		//������Ƿ񶶶�
	double shaking_strength = 0;	//�������������
	int shake_time = 0;

	// Timer timer_wander;				//������λμ�ʱ��
	bool is_wandering = false;		//������Ƿ��λ�
	double wandering_strength = 0;		//������λη���
	WanderType current_wander_type;	//��ǰ�λη�ʽ
	bool is_current_wander_end = true;		//��ǰ�λ��Ƿ����
	int count = 0;
	const double wander_speed = 4.0;

};

