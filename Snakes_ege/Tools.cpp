#include "Tools.h"

void putimage_alpha(int x, int y, PIMAGE img)
{
	int w = getwidth(img);
	int h = getheight(img);
	AlphaBlend(getHDC(NULL), x, y, w, h, getHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

//从图片文件中加载图像，并将图像缩放成 width x height 大小
void get_zoom_image(PIMAGE img, const char* fileName, int width, int height)
{
	if (img == NULL)
		return;

	PIMAGE temp = newimage();
	getimage(temp, fileName);

	if ((getwidth(img) != width) || (getheight(img) != height))
		resize(img, width, height);

	putimage(img, 0, 0, width, height, temp, 0, 0, getwidth(temp), getheight(temp));

	delimage(temp);
}

void putimage_alpha(const Camera& camera, int x, int y, PIMAGE img)
{
	int w = getwidth(img);
	int h = getheight(img);
	const dPosition& pos_camera = camera.get_position();
	AlphaBlend(getHDC(NULL), (int)(x - pos_camera.x), (int)(y - pos_camera.y), w, h, getHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

void putimage_alphablend(const Camera& camera, PIMAGE imgDest, PCIMAGE imgSrc, int x, int y, unsigned char alpha, alpha_type alphaType)
{
	const dPosition& pos_camera = camera.get_position();
	putimage_alphablend(imgDest, imgSrc, (int)(x - pos_camera.x), (int)(y - pos_camera.y), alpha, alphaType);
}

void putimage_transparent(const Camera& camera, PIMAGE imgDest, PCIMAGE imgSrc, int xDest, int yDest, color_t transparentColor, int xSrc, int ySrc, int widthSrc, int heightSrc)
{
	const dPosition& pos_camera = camera.get_position();
	putimage_transparent(imgDest, imgSrc, (int)(xDest - pos_camera.x), (int)(yDest - pos_camera.y), transparentColor, xSrc, ySrc, widthSrc, heightSrc);
}

void line_alpha(const Camera& camera, int x1, int y1, int x2, int y2)
{
	const dPosition& pos_camera = camera.get_position();
	line((int)(x1 - pos_camera.x), (int)(y1 - pos_camera.y), (int)(x2 - pos_camera.x), (int)(y2 - pos_camera.y));
}

void outtextxy(const Camera& camera, int x, int y, const char* text, PIMAGE pimg)
{
	const dPosition& pos_camera = camera.get_position();
	outtextxy((int)(x - pos_camera.x), (int)(y - pos_camera.y), text, pimg);
}
