#pragma once

#include <functional>

class Timer
{
public:

	Timer() = default;

	~Timer() = default;

	void restart();

	void set_wait_time(int val);

	void set_one_shot(bool in);

	void set_shot_callback(std::function < void() > callback);

	void pause();

	void resume();

	void on_update(int delta);

	int get_pass_time() const;

private:

	int pass_time = 0;	//�ѹ�ʱ��
	int wait_time = 0;	//�ȴ�ʱ��
	bool paused = false;	//�Ƿ���ͣ
	bool shotted = false;	//�Ƿ񱻴�����
	bool one_shot = false;	//�Ƿ�Ϊ���δ���
	
	std::function < void() > shot_callback;	// �ص���������ʱ������ʱ����callback

};

