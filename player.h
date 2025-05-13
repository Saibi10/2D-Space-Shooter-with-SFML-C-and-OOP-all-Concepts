#include <SFML/Graphics.hpp>
#include <string.h>
#include "AddOn.h"

using namespace sf;

class Player
{
public:
	Texture playerTex, playerTex45, playerTexn45, fireTex, fireTex2, fireTex3;
	Sprite playerSprite;
	Sprite* fireSprite = new Sprite[13];
	float speed = 0.8;
	int x, y;
	float firePosX, firePosY;

	//Add On
	AddOn* addOn;
	AddOn* move1;
	AddOn* move2;
	AddOn* move3;
	AddOn* move4;

	// Destruction Variables
	Texture destructionTex1, destructionTex2, destructionTex3, destructionTex4;
	Sprite* shipDesSprite1, shipDesSprite2, shipDesSprite3, shipDesSprite4;

	Player(std::string png_path)
	{
		playerTex.loadFromFile("img/player_ship.png");
		playerTex45.loadFromFile("img/player_ship45.png");
		playerTexn45.loadFromFile("img/player_ship-45.png");
		fireTex.loadFromFile("img/PNG/Lasers/laserBlue01.png");
		fireTex2.loadFromFile("img/PNG/Lasers/laserRed13.png");
		fireTex3.loadFromFile("img/PNG/Lasers/laserGreen07.png");
		playerSprite.setTexture(playerTex);
		x = 650;
		y = 900;
		playerSprite.setPosition(x, y);
		playerSprite.setScale(1, 1);

		// Setting Destruction Sprites...
		shipDesSprite1 = new Sprite[4];
		destructionTex1.loadFromFile("img/explosion.png");
		shipDesSprite1 = new Sprite[4];
		for (int i = 0; i < 4; i++)
		{
			IntRect destructLimit(138 * i, 0, 138, 138); // x, y, width, height

			destructionTex1.setRepeated(false);
			destructionTex1.setSmooth(true);
			destructionTex1.setSrgb(true);
			shipDesSprite1[i].setTexture(destructionTex1);
			shipDesSprite1[i].setTextureRect(destructLimit);
		}

		destructionTex2.loadFromFile("img/PNG/Effects/star3.png");
		shipDesSprite2.setTexture(destructionTex2);
		destructionTex3.loadFromFile("img/PNG/Effects/star2.png");
		shipDesSprite3.setTexture(destructionTex3);
		destructionTex4.loadFromFile("img/PNG/Effects/star1.png");
		shipDesSprite4.setTexture(destructionTex4);

		for (int i = 0; i < 13; i++)
		{
			firePosX = playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2 - fireSprite[i].getGlobalBounds().width / 2;
			firePosY = playerSprite.getPosition().y - fireSprite[i].getGlobalBounds().height;
			if (i == 0)
			{
				fireSprite[i].setTexture(fireTex);
				fireSprite[i].setPosition(firePosX, firePosY);
			}
			else if (i < 3)
			{
				fireSprite[i].setTexture(fireTex);
				fireSprite[i].setPosition(firePosX, firePosY);
				if (i == 2)
				{
					fireSprite[i].setPosition(firePosX + 10, firePosY);
				}
				else
				{
					fireSprite[i].setPosition(firePosX - 10, firePosY);
				}
			}
			else if (i < 10)
			{
				fireSprite[i].setTexture(fireTex2);
				fireSprite[i].setPosition(firePosX, firePosY);
			}
			else if (i < 13)
			{
				fireSprite[i].setTexture(fireTex3);
				fireSprite[i].setPosition(firePosX, firePosY);
			}
			fireSprite[i].setPosition(+5000, 5000);
		}
		fireSprite[10].setRotation(-20);
		fireSprite[12].setRotation(20);
		//
		fireSprite[3].setRotation(-40);
		fireSprite[4].setRotation(-20);
		fireSprite[5].setRotation(-10);
		//fireSprite[6].setRotation();
		fireSprite[7].setRotation(10);
		fireSprite[8].setRotation(20);
		fireSprite[9].setRotation(40);
	}

	void destroy()
	{
		for (int i = 0; i < 4; i++)
		{
			shipDesSprite1[i].setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y);
		}
		shipDesSprite2.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y);
		shipDesSprite2.setScale(3, 3);
		shipDesSprite3.setPosition(playerSprite.getPosition().x + 50, playerSprite.getPosition().y + 10);
		shipDesSprite3.setScale(3, 3);
		shipDesSprite4.setPosition(playerSprite.getPosition().x + 20, playerSprite.getPosition().y + 50);
		shipDesSprite4.setScale(3, 3);
	}

	void respawnFire(int k)
	{
		for (int n = 0; n < 20; n++)
		{
			float firePosX2 = playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2 - fireSprite[n].getGlobalBounds().width / 2;
			float firePosY2 = playerSprite.getPosition().y - fireSprite[n].getGlobalBounds().height;
			fireSprite[n].setPosition(firePosX2, firePosY2);
		}
	}
	void fire(int k)
	{
		int n = 0;
		switch (k)
		{
		case 0:
			fireSprite[n].move(0, -2);

			if (fireSprite[n].getPosition().y < 0)
			{
				float firePosX2 = playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2 - fireSprite[n].getGlobalBounds().width / 2;
				float firePosY2 = playerSprite.getPosition().y - fireSprite[n].getGlobalBounds().height;
				fireSprite[n].setPosition(firePosX2, firePosY2);
			}
			break;
		case 7:
			fireSprite[3].move(-0.9, -1.1);
			fireSprite[4].move(-0.7, -1.3);
			fireSprite[5].move(-0.3, -1.7);
			fireSprite[6].move(0, -1.9);
			fireSprite[7].move(0.3, -1.7);
			fireSprite[8].move(0.7, -1.3);
			fireSprite[9].move(0.9, -1.1);
			if (fireSprite[3].getPosition().y < 0)
			{
				for (int i = 3; i < 10; i++)
				{
					
						float firePosX2 = playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2 - fireSprite[n].getGlobalBounds().width / 2;
						float firePosY2 = playerSprite.getPosition().y - fireSprite[i].getGlobalBounds().height;
						fireSprite[i].setPosition(firePosX2, firePosY2);
					
				}
			}
			break;
		case 3:
			fireSprite[10].move(-0.3, -1.7);
			fireSprite[11].move(0, -1.9);
			fireSprite[12].move(0.3, -1.7);
			if (fireSprite[10].getPosition().y < 0)
			{
				for (int i = 10; i < 13; i++)
				{
						float firePosX2 = playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2 - fireSprite[n].getGlobalBounds().width / 2;
						float firePosY2 = playerSprite.getPosition().y - fireSprite[i].getGlobalBounds().height;
						fireSprite[i].setPosition(firePosX2, firePosY2);
				}
			}
			break;
		case 2:
			fireSprite[1].move(0, -2);
			fireSprite[2].move(0, -2);
			if (fireSprite[1].getPosition().y < 0)
			{
				for (int i = 1; i < 3; i++)
				{
					float firePosX2 = playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2 - fireSprite[n].getGlobalBounds().width / 2;
					float firePosY2 = playerSprite.getPosition().y - fireSprite[i].getGlobalBounds().height;
					if (i == 1)
					{
						fireSprite[i].setPosition(firePosX2 - 10, firePosY2);
					}
					else
					{
						fireSprite[i].setPosition(firePosX2 + 10, firePosY2);
					}
				}
			}
			break;
		}
	}

	void respawnShip()
	{
		playerSprite.setPosition(650, 900);
	}

	void move(std::string s)
	{
		float delta_x = 0, delta_y = 0;
		if (s == "l")
		{
			// move the player left
			delta_x = -1;
		}
		else if (s == "r")
		{
			// move the player right
			delta_x = 1;
		}
		if (s == "u")
		{
			delta_y = -1;
		}
		else if (s == "d")
		{
			if (playerSprite.getPosition().y < 900)
			{
				delta_y = 1;
			}
		}

		if (s == "ru")
		{
			playerSprite.setTexture(playerTex45);
		}
		else if (s == "lu")
		{
			playerSprite.setTexture(playerTexn45);
		}
		else
		{
			playerSprite.setTexture(playerTex);
		}

		delta_x *= speed;
		delta_y *= speed;
		// cout << playerSprite.getPosition().x << "\t" << playerSprite.getPosition().y << endl;
		if (playerSprite.getPosition().x >= 1300)
		{
			float yCords = playerSprite.getPosition().y;
			playerSprite.setPosition(0, yCords);
		}
		else if (playerSprite.getPosition().x <= 0)
		{
			float yCords = playerSprite.getPosition().y;
			playerSprite.setPosition(1300, yCords);
		}
		playerSprite.move(delta_x, delta_y);
	}
};
