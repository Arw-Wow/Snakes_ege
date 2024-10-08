#include <graphics.h>
#include <iostream>

#include "Scene.h"
#include "MenuScene.h"
#include "IntroduceScene.h"
#include "SelectScene.h"
#include "SettingScene.h"
#include "GameScene.h"
#include "SceneManager.h"

#include "Player.h"
#include "Player_1.h"
#include "Player_2.h"

#include "Tools.h"

#include "resource.h"



PIMAGE img_P1_snake_head_up;
PIMAGE img_P1_snake_head_down;
PIMAGE img_P1_snake_head_left;
PIMAGE img_P1_snake_head_right;
PIMAGE img_P1_snake_body;

PIMAGE img_P2_snake_head_up;
PIMAGE img_P2_snake_head_down;
PIMAGE img_P2_snake_head_left;
PIMAGE img_P2_snake_head_right;
PIMAGE img_P2_snake_body;

PIMAGE img_food;
PIMAGE img_stimulant;
PIMAGE img_laxative;
PIMAGE img_shit;
PIMAGE img_pill;
PIMAGE img_wall;
PIMAGE img_fire;

PIMAGE img_left_select_button_idle;
PIMAGE img_left_select_button_down;
PIMAGE img_right_select_button_idle;
PIMAGE img_right_select_button_down;

PIMAGE img_map_0;
PIMAGE img_map_1;
PIMAGE img_map_2;

// PIMAGE img_P1_avatar;
// PIMAGE img_P2_avatar;
PIMAGE img_P1_avatar_edge;
PIMAGE img_P2_avatar_edge;
PIMAGE img_victory;
PIMAGE img_P1_avatar_die;
PIMAGE img_P2_avatar_die;

PIMAGE img_game_over;
// PIMAGE img_game_scene_background;
PIMAGE img_black_background;
PIMAGE img_menu_scene_background;
PIMAGE img_title;
PIMAGE img_select_edge;
PIMAGE img_select_highlight;
PIMAGE img_game_scene_ui_background;
PIMAGE img_player_speed_up_effect;
PIMAGE img_player_invincible_effect;
// PIMAGE img_fire_background;

#pragma comment(lib, "winmm.lib")

static void load_res()
{
	img_P1_snake_head_up = newimage();
	get_zoom_image(img_P1_snake_head_up, "res/img/P1_snake_head_up.png", 20, 20);
	img_P1_snake_head_down = newimage();
	get_zoom_image(img_P1_snake_head_down, "res/img/P1_snake_head_down.png", 20, 20);
	img_P1_snake_head_left = newimage();
	get_zoom_image(img_P1_snake_head_left, "res/img/P1_snake_head_left.png", 20, 20);
	img_P1_snake_head_right = newimage();
	get_zoom_image(img_P1_snake_head_right, "res/img/P1_snake_head_right.png", 20, 20);
	img_P1_snake_body = newimage();
	get_zoom_image(img_P1_snake_body, "res/img/P1_snake_body.png", 20, 20);

	img_P2_snake_head_up = newimage();
	get_zoom_image(img_P2_snake_head_up, "res/img/P2_snake_head_up.png", 20, 20);
	img_P2_snake_head_down = newimage();
	get_zoom_image(img_P2_snake_head_down, "res/img/P2_snake_head_down.png", 20, 20);
	img_P2_snake_head_left = newimage();
	get_zoom_image(img_P2_snake_head_left, "res/img/P2_snake_head_left.png", 20, 20);
	img_P2_snake_head_right = newimage();
	get_zoom_image(img_P2_snake_head_right, "res/img/P2_snake_head_right.png", 20, 20);
	img_P2_snake_body = newimage();
	get_zoom_image(img_P2_snake_body, "res/img/P2_snake_body.png", 20, 20);

	img_food = newimage();
	get_zoom_image(img_food, "res/img/food.png", 20, 20);
	img_stimulant = newimage();
	get_zoom_image(img_stimulant, "res/img/stimulant.png", 20, 20);
	img_laxative = newimage();
	get_zoom_image(img_laxative, "res/img/laxative.png", 20, 20);
	img_shit = newimage();
	get_zoom_image(img_shit, "res/img/shit.png", 20, 20);
	img_pill = newimage();
	get_zoom_image(img_pill, "res/img/pill.png", 20, 20);
	img_wall = newimage();
	get_zoom_image(img_wall, "res/img/wall.png", 20, 20);
	img_fire = newimage();
	get_zoom_image(img_fire, "res/img/fire.png", 20, 20);

	img_left_select_button_idle = newimage();
	getimage(img_left_select_button_idle, "res/img/left_select_button_idle.png");
	img_left_select_button_down = newimage();
	getimage(img_left_select_button_down, "res/img/left_select_button_down.png");
	img_right_select_button_idle = newimage();
	getimage(img_right_select_button_idle, "res/img/right_select_button_idle.png");
	img_right_select_button_down = newimage();
	getimage(img_right_select_button_down, "res/img/right_select_button_down.png");

	img_map_0 = newimage();
	get_zoom_image(img_map_0, "res/img/map_0.png", 560, 420);
	img_map_1 = newimage();
	get_zoom_image(img_map_1, "res/img/map_1.png", 560, 420);
	img_map_2 = newimage();
	get_zoom_image(img_map_2, "res/img/map_2.png", 560, 420);

	// img_P1_avatar = newimage();
	// get_zoom_image(img_P1_avatar, "res/img/P1_avatar.png", 80, 80);
	// img_P2_avatar = newimage();
	// get_zoom_image(img_P2_avatar, "res/img/P2_avatar.png", 80, 80);
	img_P1_avatar_edge = newimage();
	get_zoom_image(img_P1_avatar_edge, "res/img/P1_avatar_edge.png", 110, 110);
	img_P2_avatar_edge = newimage();
	get_zoom_image(img_P2_avatar_edge, "res/img/P2_avatar_edge.png", 110, 110);
	img_victory = newimage();
	get_zoom_image(img_victory, "res/img/victory.png", 80, 80);
	img_P1_avatar_die = newimage();
	get_zoom_image(img_P1_avatar_die, "res/img/P1_avatar_die.png", 80, 80);
	img_P2_avatar_die = newimage();
	get_zoom_image(img_P2_avatar_die, "res/img/P2_avatar_die.png", 80, 80);

	img_game_over = newimage();
	getimage(img_game_over, "res/img/game_over.png");
	// img_game_scene_background = newimage();
	// getimage(img_game_scene_background, "res/img/game_scene_background.jpg");
	img_black_background = newimage();
	getimage(img_black_background, "res/img/black_background.jpg");
	img_menu_scene_background = newimage();
	getimage(img_menu_scene_background, "res/img/menu_scene_background.png");
	img_title = newimage();
	getimage(img_title, "res/img/title.png");
	img_select_edge = newimage();
	get_zoom_image(img_select_edge, "res/img/select_edge.png", 720, 950);
	img_select_highlight = newimage();
	get_zoom_image(img_select_highlight, "res/img/select_highlight.png", 1300, 170);
	img_game_scene_ui_background = newimage();
	getimage(img_game_scene_ui_background, "res/img/game_scene_ui_background.png");
	img_player_speed_up_effect = newimage();
	get_zoom_image(img_player_speed_up_effect, "res/img/player_speed_up_effect.png", 20, 20);
	img_player_invincible_effect = newimage();
	get_zoom_image(img_player_invincible_effect, "res/img/player_invincible_effect.png", 20, 20);
	// img_fire_background = newimage();
	// get_zoom_image(img_fire_background, "res/img/fire.png", 700, 550);

	mciSendString("open res/msc/be_attacked_sound.mp3 alias be_attacked_sound", NULL, 0, NULL);
	mciSendString("open res/msc/eat_sound.mp3 alias eat_sound", NULL, 0, NULL);
	mciSendString("open res/msc/game_scene_bgm.mp3 alias game_scene_bgm", NULL, 0, NULL);
	mciSendString("open res/msc/menu_scene_bgm.mp3 alias menu_scene_bgm", NULL, 0, NULL);
	mciSendString("open res/msc/speed_up_sound.mp3 alias speed_up_sound", NULL, 0, NULL);
	mciSendString("open res/msc/select_scene_switch.wav alias select_scene_switch", NULL, 0, NULL);
	mciSendString("open res/msc/select_scene_confirm.wav alias select_scene_confirm", NULL, 0, NULL);
	mciSendString("open res/msc/generate_object_sound.mp3 alias generate_object_sound", NULL, 0, NULL);
	mciSendString("open res/msc/shitting_sound.mp3 alias shitting_sound", NULL, 0, NULL);
}

void delete_res()
{
	delimage(img_P1_snake_head_up);
	delimage(img_P1_snake_head_down);
	delimage(img_P1_snake_head_left);
	delimage(img_P1_snake_head_right);
	delimage(img_P1_snake_body);

	delimage(img_P2_snake_head_up);
	delimage(img_P2_snake_head_down);
	delimage(img_P2_snake_head_left);
	delimage(img_P2_snake_head_right);
	delimage(img_P2_snake_body);

	delimage(img_food);
	delimage(img_stimulant);
	delimage(img_laxative);
	delimage(img_shit);
	delimage(img_pill);
	delimage(img_wall);
	delimage(img_fire);

	delimage(img_left_select_button_idle);
	delimage(img_left_select_button_down);
	delimage(img_right_select_button_idle);
	delimage(img_right_select_button_down);

	delimage(img_map_0);
	delimage(img_map_1);
	delimage(img_map_2);

	delimage(img_P1_avatar_edge);
	delimage(img_P2_avatar_edge);
	delimage(img_victory);
	delimage(img_P1_avatar_die);
	delimage(img_P2_avatar_die);

	delimage(img_game_over);
	delimage(img_black_background);
	delimage(img_menu_scene_background);
	delimage(img_title);
	delimage(img_select_edge);
	delimage(img_select_highlight);
	delimage(img_game_scene_ui_background);
	delimage(img_player_speed_up_effect);
	// delimage(img_fire_background);
}

int FPS = 144;

bool is_special_mode_on = false;
bool is_draw_line_on = false;
bool is_draw_background_on = true;
Player::PlayerSpeedMode speed_mode = Player::PlayerSpeedMode::MEDIUM_SPEED;

Scene* menu_scene;
Scene* introduce_scene;
Scene* select_scene;
Scene* setting_scene;
Scene* game_scene;

BlockType** game_map;

Player* player_1;
Player* player_2;

Camera camera;

bool is_running = true;



int main()
{
	srand(time(NULL));

	//创建窗口，设置手动渲染模式
	initgraph(1280, 720, INIT_RENDERMANUAL);
	// setbkcolor(BLACK);

	//设置窗口标题和图标
	setcaption("贪吃蛇大作战");
	seticon(IDI_ICON1);

	load_res();

	menu_scene = new MenuScene();
	introduce_scene = new IntroduceScene();
	select_scene = new SelectScene();
	setting_scene = new SettingScene();
	game_scene = new GameScene();

	player_1 = new Player_1();
	player_2 = new Player_2();
	
	SceneManager::get_instance()->switch_to(SceneType::MENU_SCENE);

	//帧循环，通过delay_fps()触发缓冲区交换
	for (; is_run() && is_running; delay_fps(FPS)) 
	{
		//清屏d
		ege::cleardevice();

		//输入
		while (kbmsg()) {
			key_msg msg = getkey();
			SceneManager::get_instance()->on_input(msg);
		}

		//计算上次update到这次update的delta时间
		static ULONGLONG last_tick_time = GetTickCount64();
		ULONGLONG current_tick_time = GetTickCount64();
		SceneManager::get_instance()->on_update(current_tick_time - last_tick_time);
		last_tick_time = current_tick_time;

		//绘图，中途可使用getch()暂停，或者调用delay_ms(0)触发缓冲区交换
		SceneManager::get_instance()->on_draw();
	}

	// delete
	delete_res();

	delete menu_scene;
	delete introduce_scene;
	delete select_scene;
	delete setting_scene;
	delete game_scene;
	delete player_1;
	delete player_2;

	closegraph();
}