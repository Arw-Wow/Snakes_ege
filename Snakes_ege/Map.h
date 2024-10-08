#pragma once

#include <graphics.h>
#include "Block.h"

enum MapType
{
	MAP_0,
	MAP_1,
	MAP_2,
};

constexpr int Map_Width = 50;
constexpr int Map_Height = 38;

extern BlockType (*current_map)[Map_Width];

extern BlockType map_0[Map_Height][Map_Width];

extern BlockType map_1[Map_Height][Map_Width];

extern BlockType map_2[Map_Height][Map_Width];
