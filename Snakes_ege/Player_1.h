#pragma once
#include "Player.h"

class Player_1 :
    public Player
{

public:

	Player_1();

	void on_input(key_msg msg) override;

	void on_update(int delta) override;

	void reset() override;

	void on_move() override;

};

