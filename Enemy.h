#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

class Bumb
{
public:
    Texture bombTex;
    Sprite* bombSprite;
    bool* isShowBomb;
    float attackSpeed;
    Bumb()
    {
        bombTex.loadFromFile("img/bomb.png");
        bombSprite = new Sprite[21];
        for (int i = 0; i < 21; i++)
        {
            bombSprite[i].setTexture(bombTex);
            bombSprite[i].setScale(0.2, 0.2);
            bombSprite[i].setPosition(10100, 1000);
        }

        isShowBomb = new bool[21];
        for (int i = 0; i < 21; i++)
        {
            isShowBomb[i] = false;
        }
    }

    void makeBomb(Sprite s, int n)
    {
        bombSprite[n].setPosition(s.getPosition().x, s.getPosition().y);
        isShowBomb[n] = true;
    }
};


class Bomb
{
public:
    Texture bombTex;
    Sprite* bombSprite;
    bool* isBombShow;
    float attackSpeed;
    Bomb()
    {
        bombTex.loadFromFile("img/bomb.png");
        bombSprite = new Sprite[21];
        for (int i = 0; i < 21; i++)
        {
            bombSprite[i].setTexture(bombTex);
            bombSprite[i].setScale(0.2, 0.2);
            bombSprite[i].setPosition(10100, 1000);
        }

        isBombShow = new bool[21];
        for (int i = 0; i < 21; i++)
        {
            isBombShow[i] = false;
        }

        // attackSpeed = 1.0;
    }

    void sendBomb(int b)
    {
        bombSprite[b].setPosition(10100, 1000);
    }

    void makeBomb(Sprite s, int b)
    {
        float xCords = s.getPosition().x, yCords = s.getPosition().y;
        if (xCords == 0 && yCords == 0)
        {
            return;
        }
        else
        {
            this->bombSprite[b].setPosition(xCords + 50, yCords);
            this->isBombShow[b] = true;
        }
    }

    int randEnemy()
    {
        int num;
        num = rand() % 21;
        return num;
    }
};

class Enemy
{
public:
    Bomb bomb;
    Bumb bumb;
    virtual void destroy(int k) = 0;
    virtual void makeEnemy(int n) = 0;

    virtual Sprite getEnemySprite(int n) = 0;
    virtual Sprite getDestructionSprite(int l) = 0;
    // virtual Sprite getBombSprite(int b);
    // virtual bool getIsShowBomb(int b);

    // virtual void makeBomb(Sprite, int);
};

class Monster : public Enemy
{
public:
    Texture enemyTex1, enemyTex2, destructionTex, attackTex, attackTex2;
    Sprite* destructionSprite;
    Sprite* attackSprite2;
    Sprite enemySprite1, enemySprite2, attackSprite;
    bool movement;
    Monster()
    {
        enemyTex1.loadFromFile("img/monster.png");
        enemySprite1.setTexture(enemyTex1);
        enemyTex2.loadFromFile("img/monster1.png");
        enemySprite2.setTexture(enemyTex2);
        enemySprite1.setScale(0.3, 0.3);
        enemySprite2.setScale(0.7, 0.7);

        destructionTex.loadFromFile("img/explosion.png");
        destructionSprite = new Sprite[4];
        for (int i = 0; i < 4; i++)
        {
            IntRect destructLimit(138 * i, 0, 138, 138); // x, y, width, height

            destructionTex.setRepeated(false);
            destructionTex.setSmooth(true);
            destructionTex.setSrgb(true);
            destructionSprite[i].setTexture(destructionTex);
            destructionSprite[i].setTextureRect(destructLimit);
        }
        movement = true;

        attackTex.loadFromFile("img/laserBeem.png");
        attackSprite.setTexture(attackTex);
        attackSprite.setScale(1, 1.5);
        attackSprite.setOrigin(attackSprite.getLocalBounds().width / 2, 0); // Set origin at the top center of the laser beam
        attackSprite.setPosition(-500, -500);

        attackTex2.loadFromFile("img/bomb.png");
        attackSprite2 = new Sprite[5];
        for (int i = 0; i < 5; i++)
        {
            attackSprite2[i].setTexture(attackTex2);
            attackSprite2[i].setScale(0.2, 0.2);
            attackSprite2[i].setPosition(-1000, -1000);
        }
        attackSprite2[1].setRotation(25);
        attackSprite2[2].setRotation(-25);
        attackSprite2[3].setRotation(65);
        attackSprite2[4].setRotation(-65);
    }

    void move1()
    {
        if (movement)
        {
            // cout << "Move Right\n";
            enemySprite1.move(0.5, 0);
            if (enemySprite1.getPosition().x > 1000)
            {
                movement = false;
            }
        }
        else
        {
            // cout << "Move Left\n";
            enemySprite1.move(-0.5, 0);
            if (enemySprite1.getPosition().x < 100)
            {
                movement = true;
            }
        }
    }
    void move2()
    {
        if (movement)
        {
            // cout << "Move Right\n";
            enemySprite2.move(0.5, 0);
            if (enemySprite2.getPosition().x > 1000)
            {
                movement = false;
            }
        }
        else
        {
            // cout << "Move Left\n";
            enemySprite2.move(-0.5, 0);
            if (enemySprite2.getPosition().x < 100)
            {
                movement = true;
            }
        }
    }

    void makeAttack(int n)
    {
        switch (n)
        {
        case 0:
            attackSprite.setPosition(enemySprite1.getPosition().x + enemySprite1.getGlobalBounds().width / 2,
                enemySprite1.getPosition().y + enemySprite1.getGlobalBounds().height);
            //cout << "0\n";
            break;
        case 1:
            attackSprite.setPosition(-1000, -1000);
            //cout << "1\n";
            break;
        }
    }

    void makeAttack2(int n)
    {
        switch (n)
        {
        case 0:
            attackSprite2[0].setPosition(enemySprite2.getPosition().x + enemySprite2.getGlobalBounds().width / 2,
                enemySprite2.getPosition().y + enemySprite2.getGlobalBounds().height);
            attackSprite2[1].setPosition(enemySprite2.getPosition().x + 10 + enemySprite2.getGlobalBounds().width / 2,
                enemySprite2.getPosition().y + enemySprite2.getGlobalBounds().height);
            attackSprite2[2].setPosition(enemySprite2.getPosition().x  - 10 + enemySprite2.getGlobalBounds().width / 2,
                enemySprite2.getPosition().y + enemySprite2.getGlobalBounds().height);
            attackSprite2[3].setPosition(enemySprite2.getPosition().x + 20 + enemySprite2.getGlobalBounds().width / 2,
                enemySprite2.getPosition().y + enemySprite2.getGlobalBounds().height);
            attackSprite2[4].setPosition(enemySprite2.getPosition().x - 20 + enemySprite2.getGlobalBounds().width / 2,
                enemySprite2.getPosition().y + enemySprite2.getGlobalBounds().height);
            //cout << "0\n";
            break;
        case 1:
            for (int i = 0; i < 3; i++)
            {
                attackSprite2[i].setPosition(-1000, -1000);
            }
            break;
            //cout << "1\n";
        }
    }

    void moveAttack()
    {
        attackSprite2[0].move(0, 1);
        attackSprite2[1].move(1, 1);
        attackSprite2[2].move(-1, 1);
        attackSprite2[3].move(0.8, 1);
        attackSprite2[4].move(-0.8, 1);
    }

    virtual void makeEnemy(int n)
    {
        switch (n)
        {
        case 0:
            enemySprite1.setPosition(500, 40);
            break;
        case 1:
            enemySprite2.setPosition(400, 40);
            break;
        }
    }

    virtual Sprite getEnemySprite(int n)
    {
        if (n == 0)
        {
            return enemySprite1;
        }
        else
        {
            return enemySprite2;
        }
    }

    virtual Sprite getDestructionSprite(int l)
    {
        return destructionSprite[l];
    }

    virtual void destroy(int n)
    {
        switch (n)
        {
        case 0:
            for (int i = 0; i < 4; i++)
            {
                destructionSprite[i].setPosition(enemySprite1.getPosition().x, enemySprite1.getPosition().y);
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++)
            {
                destructionSprite[i].setPosition(enemySprite2.getPosition().x, enemySprite2.getPosition().y);
            }
            break;
        }
    }
};

class Dragon : public Enemy
{
public:
    Texture enemyTex1, destructionTex, attackTex, attackTex2;
    Sprite* destructionSprite;
    Sprite* attackSprite2;
    Sprite enemySprite, attackSprite;
    bool movement;
    Dragon()
    {
        enemyTex1.loadFromFile("img/dragon.png");
        enemySprite.setTexture(enemyTex1);
        enemySprite.setScale(2.5, 2.5);

        destructionTex.loadFromFile("img/explosion.png");
        destructionSprite = new Sprite[4];
        for (int i = 0; i < 4; i++)
        {
            IntRect destructLimit(138 * i, 0, 138, 138); // x, y, width, height

            destructionTex.setRepeated(false);
            destructionTex.setSmooth(true);
            destructionTex.setSrgb(true);
            destructionSprite[i].setTexture(destructionTex);
            destructionSprite[i].setTextureRect(destructLimit);
        }
        movement = true;

        attackTex.loadFromFile("img/laserBeem.png");
        attackSprite.setTexture(attackTex);
        attackSprite.setScale(1, 1.5);
        attackSprite.setOrigin(attackSprite.getLocalBounds().width / 2, 0); // Set origin at the top center of the laser beam
        attackSprite.setPosition(-500, -500);

        attackTex2.loadFromFile("img/bomb.png");
        attackSprite2 = new Sprite[5];
        for (int i = 0; i < 5; i++)
        {
            attackSprite2[i].setTexture(attackTex2);
            attackSprite2[i].setScale(0.2, 0.2);
            attackSprite2[i].setPosition(-1000, -1000);
        }
        attackSprite2[1].setRotation(25);
        attackSprite2[2].setRotation(-25);
        attackSprite2[3].setRotation(65);
        attackSprite2[4].setRotation(-65);
    }

    void makeAttack(int n)
    {
        switch (n)
        {
        case 0:
            attackSprite.setPosition(enemySprite.getPosition().x + enemySprite.getGlobalBounds().width / 2,
                enemySprite.getPosition().y + enemySprite.getGlobalBounds().height);
            //cout << "0\n";
            break;
        case 1:
            attackSprite.setPosition(-1000, -1000);
            //cout << "1\n";
            break;
        }
    }

    void makeAttack2(int n)
    {
        switch (n)
        {
        case 0:
            attackSprite2[0].setPosition(enemySprite.getPosition().x + enemySprite.getGlobalBounds().width / 2,
                enemySprite.getPosition().y + enemySprite.getGlobalBounds().height);
            attackSprite2[1].setPosition(enemySprite.getPosition().x + 10 + enemySprite.getGlobalBounds().width / 2,
                enemySprite.getPosition().y + enemySprite.getGlobalBounds().height);
            attackSprite2[2].setPosition(enemySprite.getPosition().x - 10 + enemySprite.getGlobalBounds().width / 2,
                enemySprite.getPosition().y + enemySprite.getGlobalBounds().height);
            attackSprite2[3].setPosition(enemySprite.getPosition().x + 20 + enemySprite.getGlobalBounds().width / 2,
                enemySprite.getPosition().y + enemySprite.getGlobalBounds().height);
            attackSprite2[4].setPosition(enemySprite.getPosition().x - 20 + enemySprite.getGlobalBounds().width / 2,
                enemySprite.getPosition().y + enemySprite.getGlobalBounds().height);
            //cout << "0\n";
            break;
        case 1:
            for (int i = 0; i < 3; i++)
            {
                attackSprite2[i].setPosition(-1000, -1000);
            }
            break;
            //cout << "1\n";
        }
    }

    void moveAttack()
    {
        attackSprite2[0].move(0, 1);
        attackSprite2[1].move(1, 1);
        attackSprite2[2].move(-1, 1);
        attackSprite2[3].move(0.8, 1);
        attackSprite2[4].move(-0.8, 1);
    }

    void move()
    {
        if (movement)
        {
            // cout << "Move Right\n";
            enemySprite.move(0.5, 0);
            if (enemySprite.getPosition().x > 800)
            {
                movement = false;
            }
        }
        else
        {
            // cout << "Move Left\n";
            enemySprite.move(-0.5, 0);
            if (enemySprite.getPosition().x < 50)
            {
                movement = true;
            }
        }
    }
    
    

    virtual void makeEnemy(int n)
    {
        enemySprite.setPosition(400, 20);
    }

    virtual Sprite getEnemySprite(int n)
    {
        return enemySprite;
    }

    virtual Sprite getDestructionSprite(int l)
    {
        return destructionSprite[l];
    }

    virtual void destroy(int n)
    {

        for (int i = 0; i < 4; i++)
        {
            destructionSprite[i].setPosition(enemySprite.getPosition().x, enemySprite.getPosition().y);
        }
    }
};

class Rebel:public Enemy
{
public:
    Texture enemyTex, attackTex, attackTex2, guidedTex;
    Sprite* attackSprite2;
    Sprite enemySprite, attackSprite, guidedSprite;
    bool movement;

    float guidedCordX, guidedCordY;

    Rebel()
    {
        enemyTex.loadFromFile("img/Rebel.png");
        enemySprite.setTexture(enemyTex);

        movement = true;

        attackTex.loadFromFile("img/laserBeem.png");
        attackSprite.setTexture(attackTex);
        attackSprite.setScale(1, 1.5);
        attackSprite.setOrigin(attackSprite.getLocalBounds().width / 2, 0); // Set origin at the top center of the laser beam

        attackTex2.loadFromFile("img/bomb.png");
        attackSprite2 = new Sprite[5];
        for (int i = 0; i < 5; i++)
        {
            attackSprite2[i].setTexture(attackTex2);
            attackSprite2[i].setScale(0.2, 0.2);
            attackSprite2[i].setPosition(-1000, -1000);
        }
        attackSprite2[1].setRotation(25);
        attackSprite2[2].setRotation(-25);
        attackSprite2[3].setRotation(65);
        attackSprite2[4].setRotation(-65);

        guidedTex.loadFromFile("img/bomb.png");
        guidedSprite.setTexture(guidedTex);
        guidedSprite.setScale(0.8, 0.8);
        guidedSprite.setPosition(-1000, -1000);
    }

    void move()
    {
        if (movement)
        {
            // cout << "Move Right\n";
            enemySprite.move(0.5, 0);
            if (enemySprite.getPosition().x > 800)
            {
                movement = false;
            }
        }
        else
        {
            // cout << "Move Left\n";
            enemySprite.move(-0.5, 0);
            if (enemySprite.getPosition().x < 50)
            {
                movement = true;
            }
        }
    }

    void makeAttack(int n)
    {
        switch (n)
        {
        case 0:
            attackSprite.setPosition(enemySprite.getPosition().x + enemySprite.getGlobalBounds().width / 2 - 90,
                enemySprite.getPosition().y + enemySprite.getGlobalBounds().height - 200);
            //cout << "0\n";
            break;
        case 1:
            attackSprite.setPosition(-1000, -1000);
            //cout << "1\n";
            break;
        }
    }

    void makeAttack2(int n)
    {
        switch (n)
        {
        case 0:
            attackSprite2[0].setPosition(enemySprite.getPosition().x + enemySprite.getGlobalBounds().width / 2 - 90,
                enemySprite.getPosition().y + enemySprite.getGlobalBounds().height - 200);
            attackSprite2[1].setPosition(enemySprite.getPosition().x + 10 + enemySprite.getGlobalBounds().width / 2 - 90,
                enemySprite.getPosition().y + enemySprite.getGlobalBounds().height - 200);
            attackSprite2[2].setPosition(enemySprite.getPosition().x - 10 + enemySprite.getGlobalBounds().width / 2 - 90,
                enemySprite.getPosition().y + enemySprite.getGlobalBounds().height - 200);
            attackSprite2[3].setPosition(enemySprite.getPosition().x + 20 + enemySprite.getGlobalBounds().width / 2 - 90,
                enemySprite.getPosition().y + enemySprite.getGlobalBounds().height - 200);
            attackSprite2[4].setPosition(enemySprite.getPosition().x - 20 + enemySprite.getGlobalBounds().width / 2 - 90,
                enemySprite.getPosition().y + enemySprite.getGlobalBounds().height - 200);
            //cout << "0\n";
            break;
        case 1:
            for (int i = 0; i < 3; i++)
            {
                attackSprite2[i].setPosition(-1000, -1000);
            }
            break;
            //cout << "1\n";
        }
    }

    void moveAttack()
    {
        attackSprite2[0].move(0, 1);
        attackSprite2[1].move(1, 1);
        attackSprite2[2].move(-1, 1);
        attackSprite2[3].move(0.8, 1);
        attackSprite2[4].move(-0.8, 1);
    }

    void makeGuided(Sprite &s)
    {
        float dx = s.getPosition().x - enemySprite.getPosition().x;
        float dy = s.getPosition().y - enemySprite.getPosition().y;
        float length = sqrt(dx * dx + dy * dy);
        guidedCordX = dx / length;
        guidedCordY = dy / length;
    }

    void guidedMove()
    {
        guidedSprite.move(guidedCordX * 1, guidedCordY * 1);
    }

    virtual void destroy(int k)
    {
        return;
    }
    virtual void makeEnemy(int n)
    {
        enemySprite.setPosition(300, -50);
    }

    virtual Sprite getEnemySprite(int n)
    {
        return enemySprite;
    }
    virtual Sprite getDestructionSprite(int l)
    {
        return enemySprite;
    }

};

class Invader : public Enemy
{
    virtual void destroy(int k) = 0;
    virtual void makeEnemy(int n) = 0;
};

class Alpha : public Invader
{
public:
    Texture destructionTex, enemyTex, attackTex;
    Sprite* destructionSprite;
    Sprite* enemySprite;
    Alpha()
    {
        enemyTex.loadFromFile("img/enemy_1.png");
        enemySprite = new Sprite[21];

        for (int i = 0; i < 21; i++)
        {
            enemySprite[i].setTexture(enemyTex);
        }

        destructionTex.loadFromFile("img/explosion.png");
        destructionSprite = new Sprite[4];
        for (int i = 0; i < 4; i++)
        {
            IntRect destructLimit(138 * i, 0, 138, 138); // x, y, width, height

            destructionTex.setRepeated(false);
            destructionTex.setSmooth(true);
            destructionTex.setSrgb(true);
            destructionSprite[i].setTexture(destructionTex);
            destructionSprite[i].setTextureRect(destructLimit);
        }
    }

    virtual Sprite getEnemySprite(int n)
    {
        return enemySprite[n];
    }

    virtual Sprite getDestructionSprite(int l)
    {
        return destructionSprite[l];
    }

    virtual void destroy(int k)
    {
        for (int i = 0; i < 4; i++)
        {
            destructionSprite[i].setPosition(enemySprite[k].getPosition().x, enemySprite[k].getPosition().y);
        }
    }

    virtual void makeEnemy(int n)
    {
        switch (n)
        {
        case 0:
            for (int i = 0; i < 21; i++)
            {
                if (i == 10 || i == 9 || i == 8 || i == 11 || i == 12)
                {
                    continue;
                }
                if (i < 7)
                {
                    enemySprite[i].setPosition(220 + (i * 140), 30);
                }
                else if (i >= 7 && i < 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 7) * 140), 150);
                }
                else if (i >= 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 14) * 140), 270);
                }
            }
            break;
        case 1:
            for (int i = 0; i < 21; i++)
            {
                if (i == 7 || i == 13 || i == 14 || i == 9 || i == 10 || i == 11 || i == 15 || i == 20 || i == 19)
                {
                    continue;
                }
                if (i < 7)
                {
                    enemySprite[i].setPosition(220 + (i * 140), 30);
                }
                else if (i >= 7 && i < 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 7) * 140), 150);
                }
                else if (i >= 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 14) * 140), 270);
                }
            }
            break;
        case 2:
            for (int i = 0; i < 21; i++)
            {
                if (i == 0 || i == 1 || i == 2 || i == 4 || i == 5 || i == 6 || i == 14 || i == 15 || i == 16 || i == 18 || i == 19 || i == 20)
                {
                    continue;
                }
                if (i < 7)
                {
                    enemySprite[i].setPosition(220 + (i * 140), 30);
                }
                else if (i >= 7 && i < 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 7) * 140), 150);
                }
                else if (i >= 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 14) * 140), 270);
                }
            }
            break;
        }
    }
};

class Beta : public Invader
{
public:
    Texture destructionTex, enemyTex, attackTex;
    Sprite* destructionSprite;
    Sprite* enemySprite;
    Beta()
    {
        enemyTex.loadFromFile("img/enemy_2.png");
        enemySprite = new Sprite[21];

        for (int i = 0; i < 21; i++)
        {
            enemySprite[i].setTexture(enemyTex);
        }

        destructionTex.loadFromFile("img/explosion.png");
        destructionSprite = new Sprite[4];
        for (int i = 0; i < 4; i++)
        {
            IntRect destructLimit(138 * i, 0, 138, 138); // x, y, width, height

            destructionTex.setRepeated(false);
            destructionTex.setSmooth(true);
            destructionTex.setSrgb(true);
            destructionSprite[i].setTexture(destructionTex);
            destructionSprite[i].setTextureRect(destructLimit);
        }
    }

    virtual Sprite getEnemySprite(int n)
    {
        return enemySprite[n];
    }

    virtual Sprite getDestructionSprite(int l)
    {
        return destructionSprite[l];
    }

    virtual void destroy(int k)
    {
        for (int i = 0; i < 4; i++)
        {
            destructionSprite[i].setPosition(enemySprite[k].getPosition().x, enemySprite[k].getPosition().y);
        }
    }

    virtual void makeEnemy(int n)
    {
        switch (n)
        {
        case 0:
            for (int i = 0; i < 21; i++)
            {
                if (i == 1 || i == 5 || i == 6 || i == 7 || i == 9 || i == 11 || i == 13 || i == 14 || i == 15 || i == 19 || i == 17 || i == 20)
                {
                    continue;
                }
                if (i == 0)
                {
                    enemySprite[i].setPosition(640, 390);
                    continue;
                }
                if (i < 7)
                {
                    enemySprite[i].setPosition(220 + (i * 140), 30);
                }
                else if (i >= 7 && i < 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 7) * 140), 150);
                }
                else if (i >= 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 14) * 140), 270);
                }
            }
            break;
        case 1:
            for (int i = 0; i < 21; i++)
            {
                if (i == 1 || i == 5 || i == 6 || i == 7 || i == 9 || i == 11 || i == 13 || i == 14 || i == 15 || i == 17 || i == 19 || i == 20 || i == 3)
                {
                    continue;
                }
                if (i == 0)
                {
                    enemySprite[i].setPosition(640, 390);
                    continue;
                }
                if (i < 7)
                {
                    enemySprite[i].setPosition(220 + (i * 140), 30);
                }
                else if (i >= 7 && i < 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 7) * 140), 150);
                }
                else if (i >= 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 14) * 140), 270);
                }
            }
            break;
        case 2:
            for (int i = 0; i < 21; i++)
            {
                if (i == 7 || i == 13 || i == 5 || i == 6 || i == 14 || i == 15 || i == 19 || i == 20)
                {
                    continue;
                }
                if (i == 0)
                {
                    enemySprite[i].setPosition(640, 30);
                    continue;
                }
                if (i == 1)
                {
                    enemySprite[i].setPosition(640, 520);
                    continue;
                }
                if (i < 7)
                {
                    enemySprite[i].setPosition(220 + (i * 140), 150);
                }
                else if (i >= 7 && i < 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 7) * 140), 270);
                }
                else if (i >= 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 14) * 140), 390);
                }
            }
            break;
        }
    }
};
class Gemma : public Invader
{
public:
    Texture destructionTex, enemyTex, attackTex;
    Sprite* destructionSprite;
    Sprite* enemySprite;
    Gemma()
    {
        enemyTex.loadFromFile("img/enemy_3.png");
        enemySprite = new Sprite[21];

        for (int i = 0; i < 21; i++)
        {
            enemySprite[i].setTexture(enemyTex);
        }

        destructionTex.loadFromFile("img/explosion.png");
        destructionSprite = new Sprite[4];
        for (int i = 0; i < 4; i++)
        {
            IntRect destructLimit(138 * i, 0, 138, 138); // x, y, width, height

            destructionTex.setRepeated(false);
            destructionTex.setSmooth(true);
            destructionTex.setSrgb(true);
            destructionSprite[i].setTexture(destructionTex);
            destructionSprite[i].setTextureRect(destructLimit);
        }
    }

    virtual Sprite getEnemySprite(int n)
    {
        return enemySprite[n];
    }

    virtual Sprite getDestructionSprite(int l)
    {
        return destructionSprite[l];
    }

    virtual void destroy(int k)
    {
        for (int i = 0; i < 4; i++)
        {
            destructionSprite[i].setPosition(enemySprite[k].getPosition().x, enemySprite[k].getPosition().y);
        }
    }

    virtual void makeEnemy(int n)
    {
        switch (n)
        {
        case 0:
            for (int i = 0; i < 21; i++)
            {
                if (i < 7)
                {
                    enemySprite[i].setPosition(220 + (i * 140), 30);
                }
                else if (i >= 7 && i < 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 7) * 140), 150);
                }
                else if (i >= 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 14) * 140), 270);
                }
            }
            break;
        case 1:
            for (int i = 0; i < 21; i++)
            {
                if (i == 1 || i == 5 || i == 6 || i == 7 || i == 13 || i == 14 || i == 15 || i == 19 || i == 20 || i == 3)
                {
                    continue;
                }
                if (i == 0)
                {
                    enemySprite[i].setPosition(640, 390);
                    continue;
                }
                if (i < 7)
                {
                    enemySprite[i].setPosition(220 + (i * 140), 30);
                }
                else if (i >= 7 && i < 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 7) * 140), 150);
                }
                else if (i >= 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 14) * 140), 270);
                }
            }
            break;
        case 2:
            for (int i = 0; i < 21; i++)
            {
                if (i == 1 || i == 5 || i == 6 || i == 7 || i == 13 || i == 14 || i == 15 || i == 19 || i == 20)
                {
                    continue;
                }
                if (i == 0)
                {
                    enemySprite[i].setPosition(640, 30);
                    continue;
                }
                if (i == 1)
                {
                    enemySprite[i].setPosition(640, 520);
                    continue;
                }
                if (i < 7)
                {
                    enemySprite[i].setPosition(220 + (i * 140), 30);
                }
                else if (i >= 7 && i < 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 7) * 140), 150);
                }
                else if (i >= 14)
                {
                    enemySprite[i].setPosition(220 + ((i - 14) * 140), 270);
                }
            }
            break;
        }
    }
};
