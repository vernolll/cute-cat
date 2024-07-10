#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

using namespace sf;

extern float offsetX, offsetY;

class PLAYER {

public:

	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;

	PLAYER(Texture& image)
	{
		sprite.setTexture(image);
		rect = FloatRect(320, 240, 60, 60);

		dx = dy = 0.1;
		currentFrame = 0;
	}


	void update(float time)
	{

		rect.left += dx * time;
		Collision(0);

		if (!onGround) dy = dy + 0.0005 * time;
		rect.top += dy * time;
		onGround = false;
		Collision(1);


		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;

		if (dx > 0) sprite.setTextureRect(IntRect(63 * int(currentFrame), 196, 60, 60));
		if (dx < 0) sprite.setTextureRect(IntRect(69 * int(currentFrame), 130, 60, 60));
		//���-�� ������� � ��������� ������
		if (dy > 0 && dx > 0) sprite.setTextureRect(IntRect(60 * int(currentFrame), 60, 60, 60));
		if (dy > 0 && dx < 0) sprite.setTextureRect(IntRect(60 * int(currentFrame), 0, 60, 60));


		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

		dx = 0;
	}


	// collision
	void Collision(int dir)
	{
		for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
			for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
			{
				if ((TileMap[i][j] == 'B') || (TileMap[i][j] == 'E') || (TileMap[i][j] == 'X') || (TileMap[i][j] == 'e'))
				{
					if ((dx > 0) && (dir == 0)) rect.left = j * 32 - rect.width;
					if ((dx < 0) && (dir == 0)) rect.left = j * 32 + 32;
					if ((dy > 0) && (dir == 1)) { rect.top = i * 32 - rect.height;  dy = 0;   onGround = true; }
					if ((dy < 0) && (dir == 1)) { rect.top = i * 32 + 32;   dy = 0; }
				}

				if (TileMap[i][j] == '0')
				{
					TileMap[i][j] = ' ';
				}

			}

	}
};
