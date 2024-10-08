#pragma once

enum BlockType
{
	P1_HEAD_UP,
	P1_HEAD_DOWN,
	P1_HEAD_LEFT,
	P1_HEAD_RIGHT,
	P1_BODY,

	P2_HEAD_UP,
	P2_HEAD_DOWN,
	P2_HEAD_LEFT,
	P2_HEAD_RIGHT,
	P2_BODY,

	FOOD,
	STIMULANT,
	LAXATIVE,
	PILL,
	
	SHIT,
	WALL,
	FIRE,

	EMPTY,
};

constexpr int Block_Width = 20;
constexpr int Block_Height = 20;

bool is_player_block(BlockType type);

bool is_object_block(BlockType type);

bool is_solid_block(BlockType type);
