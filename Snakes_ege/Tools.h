#pragma once

#include <graphics.h>

#include "Camera.h"
#include "Position.h"

//绘制透明背景图片
void putimage_alpha(int x, int y, PIMAGE img);

//从图片文件中加载图像，并将图像缩放成 width x height 大小
void get_zoom_image(PIMAGE img, const char* fileName, int width, int height);

void putimage_alpha(const Camera& camera, int x, int y, PIMAGE img);

void putimage_alphablend(const Camera& camera, PIMAGE imgDest, PCIMAGE imgSrc, int x, int y, unsigned char alpha, alpha_type alphaType = ALPHATYPE_STRAIGHT);

void putimage_transparent(
	const Camera& camera,
	PIMAGE imgDest,            // 目标 IMAGE 对象指针
	PCIMAGE imgSrc,            // 源 IMAGE 对象指针
	int xDest,                 // 绘制位置的 x 坐标
	int yDest,                 // 绘制位置的 y 坐标
	color_t transparentColor,     // 变为透明的像素颜色
	int xSrc = 0,              // 绘制内容在 IMAGE 对象中的左上角 x 坐标
	int ySrc = 0,              // 绘制内容在 IMAGE 对象中的左上角 y 坐标
	int widthSrc = 0,          // 绘制内容在源 IMAGE 对象中的宽度
	int heightSrc = 0          // 绘制内容在源 IMAGE 对象中的高度
);

void line_alpha(const Camera& camera, int x1, int y1, int x2, int y2);

void outtextxy(
	const Camera& camera,
	int x,
	int y,
	const char* text,
	PIMAGE pimg = NULL
);

