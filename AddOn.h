#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

class AddOn
{
public:
	virtual Sprite getItemSprite() = 0;
	virtual void moveItem() = 0;
	virtual void makeItem(Sprite s) = 0;
};

class Power :public AddOn
{
public:
	Texture itemTex;
	Sprite itemSprite;
	bool isOn, isEaten;
	Clock itemClock;
	Power()
	{
		itemTex.loadFromFile("img/PowerUp.png");
		itemSprite.setTexture(itemTex);
		itemSprite.setPosition(-1000, -1000);
		itemSprite.setScale(2, 2);
		isOn = isEaten = false;
		itemClock.restart();
	}

	Sprite getItemSprite()
	{
		return itemSprite;
	}

	void moveItem()
	{
		itemSprite.move(0, 0.3);
	}

	void isDone()
	{
		if (itemClock.getElapsedTime().asMilliseconds() > 5000)
		{
			isOn = false;
		}
		else
		{
			isOn = true;
		}
	}

	void makeItem(Sprite s)
	{
		isDone();
		if (!isOn)
		{
			itemSprite.setPosition(s.getPosition().x, s.getPosition().y);
			isOn = true;
			itemClock.restart();
		}
	}
};

class Fire :public AddOn
{
public:
	Texture itemTex;
	Sprite itemSprite;
	bool isOn, isEaten;
	Clock itemClock;
	Fire()
	{
		itemTex.loadFromFile("img/Fire.png");
		itemSprite.setTexture(itemTex);
		itemSprite.setPosition(-1000, -1000);
		itemSprite.setScale(1.5, 1.5);
		isOn = isEaten = false;
		itemClock.restart();
	}

	Sprite getItemSprite()
	{
		return itemSprite;
	}

	void moveItem()
	{
		itemSprite.move(0, 0.3);
	}

	void isDone()
	{
		if (itemClock.getElapsedTime().asMilliseconds() > 5000)
		{
			isOn = false;
		}
		else
		{
			isOn = true;
		}
	}

	void makeItem(Sprite s)
	{
		isDone();
		if (!isOn)
		{
			itemSprite.setPosition(s.getPosition().x, s.getPosition().y);
			isOn = true;
			itemClock.restart();
		}
	}
};

class Live :public AddOn
{
public:
	Texture itemTex;
	Sprite itemSprite;
	bool isOn, isEaten;
	Clock itemClock;
	Live()
	{
		itemTex.loadFromFile("img/Heart.png");
		itemSprite.setTexture(itemTex);
		itemSprite.setPosition(-1000, -1000);
		itemSprite.setScale(0.2, 0.2);
		isOn = isEaten = false;
		itemClock.restart();
	}

	Sprite getItemSprite()
	{
		return itemSprite;
	}

	void moveItem()
	{
		itemSprite.move(0, 0.3);
	}

	void isDone()
	{
		if (itemClock.getElapsedTime().asMilliseconds() > 5000)
		{
			isOn = false;
		}
		else
		{
			isOn = true;
		}
	}

	void makeItem(Sprite s)
	{
		isDone();
		if (!isOn)
		{
			itemSprite.setPosition(s.getPosition().x, s.getPosition().y);
			isOn = true;
			itemClock.restart();
		}
	}
};

class Danger :public AddOn
{
public:
	Texture itemTex;
	Sprite itemSprite;
	bool isOn, isEaten;
	Clock itemClock;
	Danger()
	{
		itemTex.loadFromFile("img/Danger.png");
		itemSprite.setTexture(itemTex);
		itemSprite.setPosition(-1000, -1000);
		itemSprite.setScale(0.2, 0.2);
		isOn = isEaten = false;
		itemClock.restart();
	}

	Sprite getItemSprite()
	{
		return itemSprite;
	}

	void moveItem()
	{
		itemSprite.move(0, 0.3);
	}

	void isDone()
	{
		if (itemClock.getElapsedTime().asMilliseconds() > 5000)
		{
			isOn = false;
		}
		else
		{
			isOn = true;
		}
	}

	void makeItem(Sprite s)
	{
		isDone();
		if (!isOn)
		{
			itemSprite.setPosition(s.getPosition().x, s.getPosition().y);
			isOn = true;
			itemClock.restart();
		}
	}
};