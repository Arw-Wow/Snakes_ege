#include "Block.h"

bool is_player_block(BlockType type)
{
	return (type == P1_HEAD_UP || type == P1_HEAD_DOWN || type == P1_HEAD_LEFT || type == P1_HEAD_RIGHT || type == P1_BODY ||
			type == P2_HEAD_UP || type == P2_HEAD_DOWN || type == P2_HEAD_LEFT || type == P2_HEAD_RIGHT || type == P2_BODY);
}

bool is_object_block(BlockType type)
{
	return (type == FOOD || type == STIMULANT || type == LAXATIVE || type == PILL);
}

bool is_solid_block(BlockType type)
{
	return (type == WALL || type == SHIT || type == FIRE || is_player_block(type));
}
