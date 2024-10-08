#pragma once

#include <graphics.h>

#include "Camera.h"
#include "Position.h"

//����͸������ͼƬ
void putimage_alpha(int x, int y, PIMAGE img);

//��ͼƬ�ļ��м���ͼ�񣬲���ͼ�����ų� width x height ��С
void get_zoom_image(PIMAGE img, const char* fileName, int width, int height);

void putimage_alpha(const Camera& camera, int x, int y, PIMAGE img);

void putimage_alphablend(const Camera& camera, PIMAGE imgDest, PCIMAGE imgSrc, int x, int y, unsigned char alpha, alpha_type alphaType = ALPHATYPE_STRAIGHT);

void putimage_transparent(
	const Camera& camera,
	PIMAGE imgDest,            // Ŀ�� IMAGE ����ָ��
	PCIMAGE imgSrc,            // Դ IMAGE ����ָ��
	int xDest,                 // ����λ�õ� x ����
	int yDest,                 // ����λ�õ� y ����
	color_t transparentColor,     // ��Ϊ͸����������ɫ
	int xSrc = 0,              // ���������� IMAGE �����е����Ͻ� x ����
	int ySrc = 0,              // ���������� IMAGE �����е����Ͻ� y ����
	int widthSrc = 0,          // ����������Դ IMAGE �����еĿ��
	int heightSrc = 0          // ����������Դ IMAGE �����еĸ߶�
);

void line_alpha(const Camera& camera, int x1, int y1, int x2, int y2);

void outtextxy(
	const Camera& camera,
	int x,
	int y,
	const char* text,
	PIMAGE pimg = NULL
);

