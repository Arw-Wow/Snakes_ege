#include "GameScene.h"


GameScene::GameScene()
{
	timer_generate_object.set_one_shot(false);
	timer_generate_object.set_wait_time(interval_generate_object);
	timer_generate_object.set_shot_callback(
		[&]() {
			is_can_generate_object = true;
		}
	);

	timer_game_over_flash.set_one_shot(false);
	timer_game_over_flash.set_wait_time(600);
	timer_game_over_flash.set_shot_callback(
		[&]() {
			is_game_over_visible = !is_game_over_visible;
		}
	);

	timer_fire_spread.set_one_shot(false);
	timer_fire_spread.set_wait_time(interval_fire_spread);
	timer_fire_spread.set_shot_callback(
		[&]() {
			is_can_fire_spread = true;
		}
	);

	timer_control_fire_spread.set_one_shot(false);
	timer_control_fire_spread.set_wait_time(interval_control_fire_spread);
	timer_control_fire_spread.set_shot_callback(
		[&]() {
			is_can_fire_spread_uncontrol = !is_can_fire_spread_uncontrol;
			if (is_can_fire_spread_uncontrol)
				camera_fire.shake(1.8, interval_control_fire_spread);
		}
	);

	animation_background.load_img_list("res/img/background/%d.png", 27);
	// animation_background.load_img_list("res/img/background/%d.png", 110);
	animation_background.set_interval(40);
	animation_background.set_loop(true);

	animation_P1_avatar.load_img_list("res/img/P1_avatar/%d.png", 4);
	animation_P1_avatar.set_interval(200);
	animation_P1_avatar.set_loop(true);

	animation_P2_avatar.load_img_list("res/img/P2_avatar/%d.png", 4);
	animation_P2_avatar.set_interval(200);
	animation_P2_avatar.set_loop(true);

	current_fire_spread_pos = { 1, 1 };
	player_1_avatar_pos = { 1080, 80 };
	player_2_avatar_pos = { 1080, 440 };
	player_1_avatar_edge_pos = { 1065, 70 };
	player_2_avatar_edge_pos = { 1065, 430 };
	player_1_win_num_text_pos = { 1000, 200 };
	player_2_win_num_text_pos = { 1000, 560 };
	fire_next_spread_time_text_pos = { 970, 340 };
	fire_spread_text_pos = { 1000, 330 };

}

void GameScene::on_enter()
{
	// 设置帧数
	FPS = 144;

	player_1->set_speed_mode(speed_mode);
	player_2->set_speed_mode(speed_mode);
	player_1->reset();
	player_2->reset();

	camera.restart();
	camera_fire.restart();

	timer_game_over_flash.restart();
	timer_generate_object.restart();
	timer_fire_spread.restart();
	timer_control_fire_spread.restart();
	is_game_over_visible = true;
	is_can_generate_object = false;
	is_game_over = false;
	is_pause = false;
	is_can_fire_spread = false;
	is_can_fire_spread_uncontrol = false;

	current_fire_spread_pos = { 1, 1 };
	fire_spread_direction_x = 1;
	fire_spread_direction_y = 0;

	animation_background.restart();
	animation_P1_avatar.restart();

	if (game_map)
	{
		for (int i = 0; i < Map_Height; i++)
			delete[] game_map[i];
		delete[] game_map;
	}

	game_map = new BlockType * [Map_Height];
	for (int i = 0; i < Map_Height; i++)
		game_map[i] = new BlockType[Map_Width];

	for (int i = 0; i < Map_Height; i++)
		std::memcpy(game_map[i], current_map[i], sizeof(BlockType) * Map_Width);

	mciSendString("play game_scene_bgm repeat from 0", NULL, 0, NULL);
}

void GameScene::on_input(key_msg& msg)
{
	if (msg.msg & key_msg_down)
	{
		switch (msg.key)
		{
		case VK_SPACE:	// 空格
			is_pause = !is_pause;
			break;
		case VK_RETURN:
			if (is_game_over)
			{
				SceneManager::get_instance()->switch_to(SceneType::SELECT_SCENE);
				mciSendString("play select_scene_confirm from 0", NULL, 0, NULL);
				break;
			}
			camera.shake(4, 500);
			break;
		case VK_ESCAPE:
			SceneManager::get_instance()->switch_to(SceneType::SELECT_SCENE);
			mciSendString("play select_scene_confirm from 0", NULL, 0, NULL);
			break;
		default:
			break;
		}
	}
	if (is_pause)	// 如果暂停了就不获取输入
		return;
	player_1->on_input(msg);
	player_2->on_input(msg);
}

void GameScene::on_update(int delta)
{
    if (is_pause && !is_game_over)
        return;

    animation_background.on_update(delta);
    animation_P1_avatar.on_update(delta);
    animation_P2_avatar.on_update(delta);

    if (is_game_over)
    {
        timer_game_over_flash.on_update(delta);
        return;
    }

    // update camera
    camera.on_update(delta);
    camera_fire.on_update(delta);

    // update 物品生成
    generate_object(delta);

    player_1->on_update(delta);
    player_2->on_update(delta);

    if (player_1->check_if_dead())
    {
        is_game_over = true;
        player_2->on_win();
        return;
    }
    if (player_2->check_if_dead())
    {
        is_game_over = true;
        player_1->on_win();
        return;
    }

    // update 地图更新
    on_update_map();

    if (is_special_mode_on)
    {
        on_update_fire(delta);
    }

}

void GameScene::on_draw()
{
	if (is_draw_background_on)
	{
		this->on_draw_background();
	}

	if (is_draw_line_on)
	{
		this->on_draw_line();
	}

	this->on_draw_map();

	player_1->on_draw();
	player_2->on_draw();

	this->on_draw_ui();

	if (is_game_over && is_game_over_visible)
	{
		this->on_draw_game_over();
	}

	// 以下在游戏结束之后不再绘制
	if (is_game_over)
		return;

	// 注意，游戏结束之后不能再暂停
	if (is_pause)
	{
		// 整体变暗
		putimage_alphablend(camera, NULL, img_black_background, 0, 0, 0x50);

		setbkmode(TRANSPARENT);	// 设置字体背景透明
		setfont(60, 0, "微软雅黑");
		settextcolor(WHITE);
		outtextxy((Map_Width - 2) * 20 / 2 - textwidth("游戏暂停") / 2, (Map_Height - 2) * 20 / 2 - textheight("游戏暂停") / 2, "游戏暂停");
	}
}

void GameScene::on_exit()
{
	mciSendString("stop game_scene_bgm", NULL, 0, NULL);
}

void GameScene::on_draw_map()
{
	// 不画出最边缘的墙
	for (int i = 1; i < Map_Height - 1; i++)
	{
		for (int j = 1; j < Map_Width - 1; j++)
		{
			switch (game_map[i][j])
			{
			case P1_HEAD_UP:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_P1_snake_head_up);
				break;
			case P1_HEAD_DOWN:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_P1_snake_head_down);
				break;
			case P1_HEAD_LEFT:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_P1_snake_head_left);
				break;
			case P1_HEAD_RIGHT:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_P1_snake_head_right);
				break;
			case P1_BODY:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_P1_snake_body);
				break;
			case P2_HEAD_UP:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_P2_snake_head_up);
				break;
			case P2_HEAD_DOWN:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_P2_snake_head_down);
				break;
			case P2_HEAD_LEFT:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_P2_snake_head_left);
				break;
			case P2_HEAD_RIGHT:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_P2_snake_head_right);
				break;
			case P2_BODY:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_P2_snake_body);
				break;
			case FOOD:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_food);
				break;
			case STIMULANT:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_stimulant);
				break;
			case LAXATIVE:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_laxative);
				break;
			case SHIT:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_shit);
				break;
			case PILL:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_pill);
				break;
			case WALL:
				putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_wall);
				break;
			case FIRE:
				if (is_can_fire_spread_uncontrol)
					putimage_alphablend(camera_fire, NULL, img_fire, (j - 1) * Block_Width, (i - 1) * Block_Height, 0xb0);
				// putimage_alpha(camera, (j - 1) * Block_Width, (i - 1) * Block_Height, img_fire);
				else
					putimage_alphablend(camera, NULL, img_fire, (j - 1) * Block_Width, (i - 1) * Block_Height, 0xb0);
			case EMPTY:	default:
				break;
			}
		}
	}
}

void GameScene::on_draw_background()
{
	// putimage_alphablend(camera, NULL, img_game_scene_background, 
	//	(Map_Width - 2) * 20 / 2 - getwidth(img_game_scene_background) / 2,
	//	(Map_Height - 2) * 20 / 2 - getheight(img_game_scene_background) / 2,
	//	0x80); 

	animation_background.on_draw(camera,
		(Map_Width - 2) * 20 / 2 - getwidth(animation_background.get_current_frame()) / 2,
		(Map_Height - 2) * 20 / 2 - getheight(animation_background.get_current_frame()) / 2);

	putimage_alphablend(camera, NULL, img_black_background, 0, 0, 0x50);

}

void GameScene::on_draw_line()
{
	// return ;

	setlinecolor(EGERGB(27, 39, 69));

	// 横线
	for (int i = 0; i < Map_Height - 1; i++)
	{
		line_alpha(camera, 0, i * Block_Height, getwidth(), i * Block_Height);
	}

	// 竖线
	for (int j = 0; j < Map_Width - 1; j++)
	{
		line_alpha(camera, j * Block_Width, 0, j * Block_Width, getheight());
	}
}

void GameScene::clear_map()
{
	for (int i = 1; i < Map_Height - 1; i++)
	{
		for (int j = 1; j < Map_Width - 1; j++)
		{
			if (is_player_block(game_map[i][j]))
				game_map[i][j] = BlockType::EMPTY;
		}
	}
}

void GameScene::generate_object(int delta)
{
	timer_generate_object.on_update(delta);
	if (is_can_generate_object)
	{
		int object = rand() % 12;
		switch (object)
		{
		case 0:	case 1:	case 2: case 3: case 4:
			generate_food();
			break;
		case 5: case 6: case 7:
			generate_stimulant();
			break;
		case 8: case 9:
			generate_laxative();
			break;
		case 10: case 11:
			generate_pill();
			break;
		}
		is_can_generate_object = false;
		mciSendString("play generate_object_sound from 0", NULL, 0, NULL);
	}
}

void GameScene::generate_food()
{
	int x = rand() % Map_Width;
	int y = rand() % Map_Height;

	while (game_map[y][x] != BlockType::EMPTY)
	{
		x = rand() % Map_Width;
		y = rand() % Map_Height;
	}

	game_map[y][x] = BlockType::FOOD;
}

void GameScene::generate_stimulant()
{
	int x = rand() % Map_Width;
	int y = rand() % Map_Height;

	while (game_map[y][x] != BlockType::EMPTY)
	{
		x = rand() % Map_Width;
		y = rand() % Map_Height;
	}

	game_map[y][x] = BlockType::STIMULANT;
}

void GameScene::generate_laxative()
{
	int x = rand() % Map_Width;
	int y = rand() % Map_Height;

	while (game_map[y][x] != BlockType::EMPTY)
	{
		x = rand() % Map_Width;
		y = rand() % Map_Height;
	}

	game_map[y][x] = BlockType::LAXATIVE;
}

void GameScene::generate_pill()
{
	int x = rand() % Map_Width;
	int y = rand() % Map_Height;

	while (game_map[y][x] != BlockType::EMPTY)
	{
		x = rand() % Map_Width;
		y = rand() % Map_Height;
	}

	game_map[y][x] = BlockType::PILL;

}

void GameScene::on_update_map()
{
	// update player
	clear_map();

	std::vector<Position>& snake_list_1 = player_1->get_snake_list();
	std::vector<Position>& snake_list_2 = player_2->get_snake_list();

	if (!snake_list_1.empty())
	{
		if (!player_1->check_if_invincible() && is_player_block(game_map[snake_list_1[0].y][snake_list_1[0].x]))
		{
			player_1->on_dead();
			is_game_over = true;
			return;
		}
		game_map[snake_list_1[0].y][snake_list_1[0].x] = player_1->get_current_head_type();
		for (int i = 1; i < snake_list_1.size(); i++)
			game_map[snake_list_1[i].y][snake_list_1[i].x] = BlockType::P1_BODY;
	}

	if (!snake_list_2.empty())
	{
		// 增加一个判断，以免头碰头时不出现死亡
		if (!player_2->check_if_invincible() && is_player_block(game_map[snake_list_2[0].y][snake_list_2[0].x]))
		{
			player_2->on_dead();
			is_game_over = true;
			return;
		}
		game_map[snake_list_2[0].y][snake_list_2[0].x] = player_2->get_current_head_type();
		for (int i = 1; i < snake_list_2.size(); i++)
			game_map[snake_list_2[i].y][snake_list_2[i].x] = BlockType::P2_BODY;
	}

	// update food and stimulant


}

void GameScene::on_update_fire(int delta)
{
	timer_control_fire_spread.on_update(delta);

	if (!is_can_fire_spread_uncontrol)
		return;

	timer_fire_spread.on_update(delta);

	if (is_can_fire_spread)
	{
		game_map[current_fire_spread_pos.y][current_fire_spread_pos.x] = BlockType::FIRE;
		Position next_fire_spread_pos = { current_fire_spread_pos.x + fire_spread_direction_x, current_fire_spread_pos.y + fire_spread_direction_y };
		if (next_fire_spread_pos.x >= Map_Width - 1 || next_fire_spread_pos.x <= 0 || next_fire_spread_pos.y >= Map_Height - 1 || next_fire_spread_pos.y <= 0 ||
			game_map[next_fire_spread_pos.y][next_fire_spread_pos.x] == BlockType::FIRE)
		{
			// change fire spread direction
			if (fire_spread_direction_x == 1 && fire_spread_direction_y == 0)	// right --> down
			{
				fire_spread_direction_x = 0;
				fire_spread_direction_y = 1;
			}
			else if (fire_spread_direction_x == 0 && fire_spread_direction_y == 1)	// down --> left
			{
				fire_spread_direction_x = -1;
				fire_spread_direction_y = 0;
			}
			else if (fire_spread_direction_x == -1 && fire_spread_direction_y == 0)	// left --> up
			{
				fire_spread_direction_x = 0;
				fire_spread_direction_y = -1;
			}
			else if (fire_spread_direction_x == 0 && fire_spread_direction_y == -1)	// up --> right
			{
				fire_spread_direction_x = 1;
				fire_spread_direction_y = 0;
			}
		}

		next_fire_spread_pos = { current_fire_spread_pos.x + fire_spread_direction_x, current_fire_spread_pos.y + fire_spread_direction_y };
		current_fire_spread_pos = next_fire_spread_pos;
		is_can_fire_spread = false;
	}

}

void GameScene::on_draw_ui()
{
	putimage_alpha(camera, 960, 0, img_black_background);	//先将背景涂黑
	putimage_alphablend(camera, NULL, img_game_scene_ui_background, 960, 0, 0x33);

	setbkmode(TRANSPARENT);
	setfont(70, 0, "Comic Sans MS");

	settextcolor(YELLOW);
	char text_player_1_win_num[256] = { 0 };
	sprintf_s(text_player_1_win_num, sizeof(text_player_1_win_num), "P1 win: %d", player_1->get_win_num());
	outtextxy(camera, player_1_win_num_text_pos.x, player_1_win_num_text_pos.y, text_player_1_win_num);

	settextcolor(BLUE);
	char text_player_2_win_num[256] = { 0 };
	sprintf_s(text_player_2_win_num, sizeof(text_player_2_win_num), "P2 win: %d", player_2->get_win_num());
	outtextxy(camera, player_2_win_num_text_pos.x, player_2_win_num_text_pos.y, text_player_2_win_num);

	if (is_special_mode_on)
	{
		settextcolor(RED);
		char fire_spread_time_text[256] = { 0 };

		if (is_can_fire_spread_uncontrol)
		{
			setfont(50, 0, "Comic Sans MS");
			sprintf_s(fire_spread_time_text, sizeof(fire_spread_time_text), "Fire Spread!");
			outtextxy(camera, fire_spread_text_pos.x, fire_spread_text_pos.y, fire_spread_time_text);
		}
		else
		{
			setfont(30, 0, "Comic Sans MS");
			sprintf_s(fire_spread_time_text, sizeof(fire_spread_time_text), "Fire Next Spread Time: %d s", (interval_control_fire_spread - timer_control_fire_spread.get_pass_time()) / 1000);
			outtextxy(camera, fire_next_spread_time_text_pos.x, fire_next_spread_time_text_pos.y, fire_spread_time_text);
		}
	}

	if (is_game_over)
	{
		if (player_1->check_if_dead())
		{
			animation_P2_avatar.on_draw(camera, player_2_avatar_pos.x, player_2_avatar_pos.y);
			if (is_game_over_visible)	// 让奖杯和死亡头像跟 game over 一起闪起来
			{
				putimage_alpha(camera, player_1_avatar_pos.x, player_1_avatar_pos.y, img_P1_avatar_die);
				putimage_alpha(camera, player_2_avatar_pos.x + 100, player_2_avatar_pos.y, img_victory);
			}
		}
		if (player_2->check_if_dead())
		{
			animation_P1_avatar.on_draw(camera, player_1_avatar_pos.x, player_1_avatar_pos.y);
			if (is_game_over_visible)	// 让奖杯和死亡头像跟 game over 一起闪起来
			{
				putimage_alpha(camera, player_2_avatar_pos.x, player_2_avatar_pos.y, img_P2_avatar_die);
				putimage_alpha(camera, player_1_avatar_pos.x + 100, player_1_avatar_pos.y, img_victory);
			}
		}
	}
	else
	{
		animation_P1_avatar.on_draw(camera, player_1_avatar_pos.x, player_1_avatar_pos.y);
		animation_P2_avatar.on_draw(camera, player_2_avatar_pos.x, player_2_avatar_pos.y);
	}
	putimage_alphablend(camera, NULL, img_P1_avatar_edge, player_1_avatar_edge_pos.x, player_1_avatar_edge_pos.y, 0xff);
	putimage_alphablend(camera, NULL, img_P2_avatar_edge, player_2_avatar_edge_pos.x, player_2_avatar_edge_pos.y, 0xff);
}

void GameScene::on_draw_game_over()
{
	if (player_1->check_if_dead())
	{
		putimage_transparent(camera, NULL, img_game_over,
			(Map_Width - 2) * 20 / 2 - getwidth(img_game_over) / 2,
			(Map_Height - 2) * 20 / 2 - getheight(img_game_over) / 2,
			WHITE);
	}
	else if (player_2->check_if_dead())
	{
		putimage_transparent(camera, NULL, img_game_over,
			(Map_Width - 2) * 20 / 2 - getwidth(img_game_over) / 2,
			(Map_Height - 2) * 20 / 2 - getheight(img_game_over) / 2,
			WHITE);
	}
}

