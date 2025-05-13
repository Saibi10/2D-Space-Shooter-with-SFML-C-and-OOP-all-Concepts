
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace std;
#include "player.h"
#include "Enemy.h"
//#include "AddOn.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
    Sprite background; // Game background sprite
    Texture bg_texture;

    Sprite barSprite;
    Texture barTex;

    //Scores
    int score;

    Player* p; // player
    Alpha alpha;
    Beta beta;
    Gemma gemma;
    // Bomb bomb;
    Monster monster;
    Dragon dragon;
    Rebel rebel;
    Enemy* enemy;
   
    int enemyPhase;
    int enemyLevel;
    bool isPhaseClear;

    // SpaceShip

    bool isAlive;
    int lives;

    // In Game Text...

    Font inGameFont;
    Text level1Text, level2Text, level3Text;
    Text phase1Text, phase2Text, phase3Text;
    Text bossText, dragonText;
    Text liveText, liveNumText, scoreText, scoreNumText;
    Text gameClock;

    string liveNum = to_string(lives), scoreNum = to_string(score);

    // Attackings///

    int randAttack;
    int randThrow, enemyBombNum;

    // Bosses
    bool isBoss, bossShow, bossMake;
    int bossType;

    //Dragon
    bool isDragon, isShowDragon, dragonMake;
    int dragonNum;

    //Add On

    Live live;
    Power power;
    Fire fire;
    Danger danger;
    
    bool isP2, isP3;
    int powerCount;

    Clock pEaten, fEaten;

    Clock pauseClock;

    int addOnNum, addOnCount;
    bool isAddOn;

    Game()
    {
        p = new Player("img/player_ship.png");
        bg_texture.loadFromFile("img/background.jpg");
        background.setTexture(bg_texture);
        background.setScale(2, 2.5);

        barTex.loadFromFile("img/Line.png");
        barSprite.setTexture(barTex);
        barSprite.setScale(3.3, 2);
        barSprite.setPosition(-50, 900);

        enemyPhase = 0;
        enemyLevel = 0;
        isPhaseClear = false;

        isAlive = true;
        lives = 3;

        // Dragon
        isDragon = false;
        isShowDragon = false;
        dragonMake = false;

        //Score
        score = 0;

        pauseClock.restart();
        
    }
    void start_game()
    {
        srand(time(0));
        RenderWindow window(VideoMode(1400, 1100), title);
        Clock clock, enemyClock, destructClock, inGameClock, shipClock, bossClock, dragonClock;
        bool isEnemyOn = false;
        enemyClock.restart();
        destructClock.restart();
        inGameClock.restart();
        shipClock.restart();
        bossClock.restart();
        dragonClock.restart();

        float timer = 0;

        // Draw Variables
        int spr[21] = { -1 };
        int clearings = 0;
        int totalEnemies;

        // Draw Explosion Variables
        int bombEnemy;
        bool isDestruct = false;

        // Text Variables...
        inGameFont.loadFromFile("Fonts/BreeSerif-Regular.ttf");

        // Level 1
        level1Text.setFont(inGameFont);
        level1Text.setString("Level 1");
        level1Text.setCharacterSize(72);
        level1Text.setFillColor(Color::White);
        level1Text.setPosition(600, 350);

        // Level 2
        level2Text.setFont(inGameFont);
        level2Text.setString("Level 2");
        level2Text.setCharacterSize(72);
        level2Text.setFillColor(Color::White);
        level2Text.setPosition(600, 350);

        // Level 3
        level3Text.setFont(inGameFont);
        level3Text.setString("Level 3");
        level3Text.setCharacterSize(72);
        level3Text.setFillColor(Color::White);
        level3Text.setPosition(600, 350);

        // Phases...

        // phase 1
        phase1Text.setFont(inGameFont);
        phase1Text.setString("Phase 1");
        phase1Text.setCharacterSize(48);
        phase1Text.setFillColor(Color::White);
        phase1Text.setPosition(620, 450);

        // phase 2
        phase2Text.setFont(inGameFont);
        phase2Text.setString("Phase 2");
        phase2Text.setCharacterSize(48);
        phase2Text.setFillColor(Color::White);
        phase2Text.setPosition(620, 450);

        // phase 3
        phase3Text.setFont(inGameFont);
        phase3Text.setString("Phase 3");
        phase3Text.setCharacterSize(48);
        phase3Text.setFillColor(Color::White);
        phase3Text.setPosition(620, 450);

        // BOSS
        bossText.setFont(inGameFont);
        bossText.setString("<<<BOSS COMING>>>");
        bossText.setCharacterSize(72);
        bossText.setFillColor(Color::White);
        bossText.setPosition(350, 400);

        // Dragon
        dragonText.setFont(inGameFont);
        dragonText.setString("Oh...Its a Dragon");
        dragonText.setCharacterSize(72);
        dragonText.setFillColor(Color::White);
        dragonText.setPosition(450, 400);

        // Lives
        liveText.setFont(inGameFont);
        liveText.setString("LIVES: ");
        liveText.setCharacterSize(40);
        liveText.setFillColor(Color::White);
        liveText.setPosition(15, 1020);

        
        // Scores
        scoreText.setFont(inGameFont);
        scoreText.setString("SCORE: ");
        scoreText.setCharacterSize(40);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(1150, 1020);

        

        // Bosses
        isBoss = false, bossShow = false, bossMake = true;
        bossType = 0;

        //Add On
        isP2 = isP3 = false;
        powerCount = 1;

        while (window.isOpen())
        {
            srand(time(0));
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            // cout<<time<<endl;
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close();          // close the game
            }

            if (Keyboard::isKeyPressed(Keyboard::Left)) // If left key is pressed
            {
                if (isAlive)
                {
                    p->move("l"); // Player will move to left
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
            {
                if (isAlive)
                {
                    p->move("r"); // player will move to right
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)) // If up key is pressed
            {
                if (isAlive)
                {
                    p->move("u"); // playet will move upwards
                }
            }
            // ---------------------------------------- //
            if ((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Up))) // If right key is pressed
            {
                if (isAlive)
                {
                    p->move("ru"); // player will move to right
                }
            }
            if ((Keyboard::isKeyPressed(Keyboard::Left)) && (Keyboard::isKeyPressed(Keyboard::Up))) // If right key is pressed
            {
                if (isAlive)
                {
                    p->move("lu"); // player will move to right
                }
            }
            // ---------------------------------------- //
            if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
            {
                if (isAlive)
                {
                    p->move("d"); // player will move downwards
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::X)) // If down key is pressed
            {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) // If down key is pressed
            {
                pause(window);
            }

            ////////////////////////////////////////////////
            /////  Call your functions here            ////
            
            
            if ((!isDragon) && (!isBoss))
            {
                //dragonNum = rand() % 50;
                dragonNum = 0;
                //cout << "Making rand DragonNum\n";
                if (dragonNum == 5)
                {
                    isDragon = true;
                    isShowDragon = false;
                }

                dragonClock.restart();
            }

            if (isDragon)
            {
                if (dragonClock.getElapsedTime().asMilliseconds() > 5000)
                {
                    isShowDragon = true;
                    //cout << "DragonShow true\n";
                }
            }

            // Continuously Firing...
            //isP2 = true;
            if (isAlive)
            {
                shipClock.restart();
                if ((!power.isEaten) && (!isP2) && (!isP3))
                {
                    p->fire(0);
                }
                if((!power.isEaten) && (isP2) && (!isP3))
                {
                    //cout << "2\n";
                    p->fire(2);
                }
                else if ((!power.isEaten) && (isP3) && (!isP2))
                {
                    p->fire(3);
                }
                
                if (power.isEaten)
                {
                    p->fire(7);
                }
                
            }
            if (!isBoss)
            {
                bossClock.restart();
            }

            // Ship Destruction
            if (!isAlive)
            {
                if (shipClock.getElapsedTime().asMilliseconds() > 3000)
                {
                    isAlive = true;
                    p->respawnShip();
                }
            }

            if (enemyClock.getElapsedTime().asMilliseconds() > 5000)
            {
                isEnemyOn = true;
            }

            if (!isDragon)
            {
                switch (enemyLevel)
                {
                case 0:
                    enemy = &alpha;
                    break;
                case 1:
                    enemy = &beta;
                    break;
                case 2:
                    enemy = &gemma;
                    break;
                }

                // Bombing

                /*switch (enemyLevel)
                {
                case 0:
                    randThrow = rand() % 3;
                    enemyBombNum = rand() & 21;
                    enemy->bumb.attackSpeed = 1.0;
                    break;
                case 1:
                    randThrow = rand() % 2;
                    enemyBombNum = rand() & 21;
                    enemy->bumb.attackSpeed = 1.5;
                    break;
                case 2:
                    randThrow = rand() % 1;
                    enemyBombNum = rand() & 21;
                    enemy->bumb.attackSpeed = 2.0;
                    break;
                }*/


                switch (enemyLevel)
                {
                case 0:
                    randAttack = rand() % 3;
                    bombEnemy = enemy->bomb.randEnemy();
                    enemy->bomb.attackSpeed = 1.0;
                    break;
                case 1:
                    randAttack = rand() % 2;
                    bombEnemy = enemy->bomb.randEnemy();
                    enemy->bomb.attackSpeed = 1.5;
                    break;
                case 2:
                    randAttack = rand() % 1;
                    bombEnemy = enemy->bomb.randEnemy();
                    enemy->bomb.attackSpeed = 2.0;
                    break;
                }

                //Phases and Levels
                if (isEnemyOn)
                {
                    if (!isPhaseClear)
                    {
                        enemy->makeEnemy(enemyPhase);
                        // Enemy Attacks
                        for (int y = 0; y < 21; y++)
                        {
                            if (enemy->bomb.isBombShow[y] == true)
                            {
                                enemy->bomb.bombSprite[y].move(0, enemy->bomb.attackSpeed);
                            }
                            else
                            {
                                enemy->bomb.sendBomb(y);
                            }
                        }
                    }
                    else
                    {
                        //score += 10;
                        enemyPhase++;
                        powerCount++;
                        
                        /*if (powerCount == 2)
                        {
                            isP2 = true;
                            isP3 = false;
                        }*/
                        if (powerCount >= 3)
                        {
                            isP2 = false;
                            isP3 = true;
                        }
                        if (powerCount <= 1)
                        {
                            isP2 = false;
                            isP3 = false;
                            powerCount = 1;
                        }
                        // cout << "Phase" << enemyPhase << endl << "Level" << enemyLevel << endl;
                        if (enemyPhase > 2)
                        {
                            enemyPhase = 0;
                            //enemyLevel++;
                            isBoss = true;
                            bossClock.restart();
                        }
                         if (enemyLevel > 2)
                         {
                             enemyLevel = 0;
                         }
                        for (int i = 0; i < 21; i++)
                        {
                            spr[i] = -1;
                        }
                        isPhaseClear = false;
                        isEnemyOn = false;
                        enemyClock.restart();
                        clearings = 0;
                    }
                }

                //Bosses
                if (bossClock.getElapsedTime().asMilliseconds() < 15000)
                {
                    if (bossClock.getElapsedTime().asMilliseconds() > 4900)
                    {
                        // cout << "In Monster\n";
                        if (isBoss)
                        {
                            switch (bossType)
                            {
                            case 0:
                                enemy = &monster;
                                if (bossMake)
                                {
                                    enemy->makeEnemy(0);
                                    bossMake = false;
                                    // cout << "MakeBoss" << endl;
                                }
                                if ((bossClock.getElapsedTime().asMilliseconds() > 7000) && (bossClock.getElapsedTime().asMilliseconds() < 9000))
                                {
                                    //cout << "0" << endl;
                                    monster.makeAttack(0);
                                }
                                else if ((bossClock.getElapsedTime().asMilliseconds() > 9000) && (bossClock.getElapsedTime().asMilliseconds() < 11000))
                                {
                                    //cout << "1" << endl;
                                    monster.makeAttack(1);
                                }
                                else if ((bossClock.getElapsedTime().asMilliseconds() > 11000) && (bossClock.getElapsedTime().asMilliseconds() < 14000))
                                {
                                    //cout << "0" << endl;
                                    monster.makeAttack(0);
                                }
                                else
                                {
                                    //cout << "1" << endl;
                                    monster.makeAttack(1);
                                }
                                monster.move1();
                                // cout << enemy->getEnemySprite(0).getPosition().x << endl;
                                enemyClock.restart();
                                break;
                            case 1:
                                enemy = &monster;
                                if (bossMake)
                                {
                                    enemy->makeEnemy(1);
                                    bossMake = false;
                                    // cout << "MakeBoss" << endl;
                                }
                                if ((bossClock.getElapsedTime().asMilliseconds() > 6000) && (bossClock.getElapsedTime().asMilliseconds() < 6200))
                                {
                                    monster.makeAttack2(0);
                                }
                                else if ((bossClock.getElapsedTime().asMilliseconds() > 10000) && (bossClock.getElapsedTime().asMilliseconds() < 10200))
                                {
                                    monster.makeAttack2(0);
                                }
                                else if ((bossClock.getElapsedTime().asMilliseconds() > 13000) && (bossClock.getElapsedTime().asMilliseconds() < 13200))
                                {
                                    monster.makeAttack2(0);
                                }

                                monster.moveAttack();
                                monster.move2();
                                // cout << enemy->getEnemySprite(0).getPosition().x << endl;
                                enemyClock.restart();
                                break;
                            case 2:
                                enemy = &dragon;
                                if (bossMake)
                                {
                                    enemy->makeEnemy(1);
                                    bossMake = false;
                                    // cout << "MakeBoss" << endl;
                                }
                                if ((bossClock.getElapsedTime().asMilliseconds() > 6000) && (bossClock.getElapsedTime().asMilliseconds() < 6200))
                                {
                                    dragon.makeAttack2(0);
                                }
                                else if ((bossClock.getElapsedTime().asMilliseconds() > 10000) && (bossClock.getElapsedTime().asMilliseconds() < 10200))
                                {
                                    dragon.makeAttack2(0);
                                }
                                else if ((bossClock.getElapsedTime().asMilliseconds() > 13000) && (bossClock.getElapsedTime().asMilliseconds() < 13200))
                                {
                                    dragon.makeAttack2(0);
                                }
                                dragon.moveAttack();

                                if ((bossClock.getElapsedTime().asMilliseconds() > 7000) && (bossClock.getElapsedTime().asMilliseconds() < 9000))
                                {
                                    //cout << "0" << endl;
                                    dragon.makeAttack(0);
                                }
                                else if ((bossClock.getElapsedTime().asMilliseconds() > 9000) && (bossClock.getElapsedTime().asMilliseconds() < 11000))
                                {
                                    //cout << "1" << endl;
                                    dragon.makeAttack(1);
                                }
                                else if ((bossClock.getElapsedTime().asMilliseconds() > 11000) && (bossClock.getElapsedTime().asMilliseconds() < 14000))
                                {
                                    //cout << "0" << endl;
                                    dragon.makeAttack(0);
                                }
                                else
                                {
                                    //cout << "1" << endl;
                                    dragon.makeAttack(1);
                                }
                                //dragon.moveAttack();
                                dragon.move();
                                // cout << enemy->getEnemySprite(0).getPosition().x << endl;
                                enemyClock.restart();
                                break;
                            }
                        }
                    }
                }
                else
                {
                    score += 30;
                    isBoss = false;
                    bossMake = true;
                    //cout << "Boss" << bossType << endl;
                    bossType++;
                    enemyLevel++;
                    if (enemyLevel > 2)
                    {
                        enemyLevel = 0;
                    }
                    if (bossType > 2)
                    {
                        //enemyLevel = 0;
                        bossType = 0;
                    }
                }
            }
            else
            {
                //cout << "IsDragon\n";

                if (dragonClock.getElapsedTime().asMilliseconds() < 20000)
                {
                    if (isShowDragon)
                    {
                        if (!dragonMake)
                        {
                            enemy = &rebel;
                            enemy->makeEnemy(0);
                            dragonMake = true;
                        }
                        if ((dragonClock.getElapsedTime().asMilliseconds() > 6000) && (dragonClock.getElapsedTime().asMilliseconds() < 6200))
                        {
                            rebel.makeAttack2(0);
                        }
                        else if ((dragonClock.getElapsedTime().asMilliseconds() > 10000) && (dragonClock.getElapsedTime().asMilliseconds() < 10200))
                        {
                            rebel.makeAttack2(0);
                        }
                        else if ((dragonClock.getElapsedTime().asMilliseconds() > 13000) && (dragonClock.getElapsedTime().asMilliseconds() < 13200))
                        {
                            rebel.makeAttack2(0);
                        }
                        rebel.moveAttack();

                        if ((dragonClock.getElapsedTime().asMilliseconds() > 7000) && (dragonClock.getElapsedTime().asMilliseconds() < 9000))
                        {
                            //cout << "0" << endl;
                            rebel.makeAttack(0);
                        }
                        else if ((dragonClock.getElapsedTime().asMilliseconds() > 9000) && (dragonClock.getElapsedTime().asMilliseconds() < 11000))
                        {
                            //cout << "1" << endl;
                            rebel.makeAttack(1);
                        }
                        else if ((dragonClock.getElapsedTime().asMilliseconds() > 11000) && (dragonClock.getElapsedTime().asMilliseconds() < 14000))
                        {
                            //cout << "0" << endl;
                            rebel.makeAttack(0);
                        }
                        else
                        {
                            //cout << "1" << endl;
                            rebel.makeAttack(1);
                        }

                        if ((dragonClock.getElapsedTime().asMilliseconds() > 6000) && (dragonClock.getElapsedTime().asMilliseconds() < 8000))
                        {
                            rebel.makeGuided(p->playerSprite);
                        }
                        else if ((dragonClock.getElapsedTime().asMilliseconds() > 10000) && (dragonClock.getElapsedTime().asMilliseconds() < 12000))
                        {
                            rebel.makeGuided(p->playerSprite);
                        }
                        else if ((dragonClock.getElapsedTime().asMilliseconds() > 15000) && (dragonClock.getElapsedTime().asMilliseconds() < 17000))
                        {
                            rebel.makeGuided(p->playerSprite);
                        }
                        rebel.guidedMove();


                        rebel.move();
                        enemyClock.restart();
                        bossClock.restart();
                    }
                    
                }
                else
                {
                    score += 50;
                    isDragon = false;
                    isShowDragon = false;
                    //enemyClock.restart();
                    //continue;
                }
            }


            

            //Add On
            addOnCount = rand() % 4;

            addOnNum = rand() % 4;
            switch (addOnNum)
            {
            case 0:
                p->addOn = &power;
                break;
            case 1:
                p->addOn = &fire;
                break;
            case 2:
                p->addOn = &live;
                break;
            case 3:
                p->addOn = &danger;
                break;
            }

            p->move1 = &power;
            p->move2 = &fire;
            p->move3 = &live;
            p->move4 = &danger;

            p->move1->moveItem();
            p->move2->moveItem();
            p->move3->moveItem();
            p->move4->moveItem();

            if (p->playerSprite.getGlobalBounds().intersects(power.itemSprite.getGlobalBounds()))
            {
                power.isEaten = true;
                pEaten.restart();
            }
            if (p->playerSprite.getGlobalBounds().intersects(fire.itemSprite.getGlobalBounds()))
            {
                fire.isEaten = true;
                fEaten.restart();
            }
            if (p->playerSprite.getGlobalBounds().intersects(danger.itemSprite.getGlobalBounds()) && isAlive)
            {
                danger.isEaten = true;
                fEaten.restart();
                isAlive = false;
                lives--;
            }
            if ((p->playerSprite.getGlobalBounds().intersects(live.itemSprite.getGlobalBounds())) && (!live.isEaten))
            {
                live.isEaten = true;
                lives++;
                if (lives >= 5)
                {
                    lives = 5;
                }
            }

            if (power.isEaten)
            {
                if (pEaten.getElapsedTime().asMilliseconds() > 5000)
                {
                    power.isEaten = false;
                }
            }
            if (fire.isEaten)
            {
                if (fEaten.getElapsedTime().asMilliseconds() > 5000)
                {
                    fire.isEaten = false;
                }
            }
            
            liveText.setString("LIVES: " + to_string(lives));
            scoreText.setString("SCORE: " + to_string(score));


            

            //cout << score << endl;

            //////////////////////////////////////////////

            window.clear(Color::Black); // clears the screen
            window.draw(background);    // setting background

            if (!isDragon)
            {
                if (isEnemyOn)
                {

                    if (enemyLevel == 0)
                    {
                        switch (enemyPhase)
                        {
                        case 0:
                            totalEnemies = 16;
                            for (int t = 0; t < 21; t++)
                            {
                                if (spr[t] != t)
                                {
                                    for (int i = 0; i < 21; i++)
                                    {
                                        if (i == 10 || i == 9 || i == 8 || i == 11 || i == 12)
                                        {
                                            continue;
                                        }
                                        if (bulletTouch(i))
                                        {
                                            if (spr[i] != i)
                                            {
                                                if (addOnCount == 1)
                                                {
                                                    p->addOn->makeItem(enemy->getEnemySprite(i));
                                                }
                                                if (!fire.isEaten)
                                                {
                                                    p->respawnFire(0);
                                                }
                                                clearings++;
                                                score += 10;
                                                enemy->bomb.isBombShow[i] = false;
                                                // cout << clearings << endl;
                                                for (int o = 0; o < 4; o++)
                                                {
                                                    enemy->destroy(i);
                                                    window.draw(enemy->getDestructionSprite(o));
                                                }
                                                spr[i] = i;
                                                continue;
                                            }
                                        }
                                        if (spr[i] != i)
                                        {
                                            sf::FloatRect enemyBounds = enemy->getEnemySprite(i).getLocalBounds();
                                            sf::FloatRect playerBounds = p->playerSprite.getLocalBounds();

                                            // Get the position components of the sprites
                                            float enemyX = enemy->getEnemySprite(i).getPosition().x;
                                            float enemyY = enemy->getEnemySprite(i).getPosition().y;
                                            float playerX = p->playerSprite.getPosition().x;
                                            float playerY = p->playerSprite.getPosition().y;

                                            // Adjust the bounds with the positions
                                            enemyBounds.left += enemyX;
                                            enemyBounds.top += enemyY;
                                            playerBounds.left += playerX;
                                            playerBounds.top += playerY;

                                            if (enemyBounds.intersects(playerBounds) && isAlive)
                                            {
                                                isAlive = false;
                                                lives--;
                                                cout << "Enemy\n";
                                            }
                                            
                                            window.draw(enemy->getEnemySprite(i));
                                            if ((randAttack == 0) && (spr[i] != i))
                                            {
                                                enemy->bomb.makeBomb(enemy->getEnemySprite(bombEnemy), bombEnemy);
                                            }
                                            
                                        }
                                        
                                        
                                    }
                                }
                                if (clearings == totalEnemies)
                                {
                                    isPhaseClear = true;
                                    // cout << "All Clear" << endl;
                                }
                            }
                            for (int y = 0; y < 21; y++)
                            {
                                if (enemy->bomb.isBombShow[y] == true)
                                {
                                    if (y == 10 || y == 9 || y == 8 || y == 11 || y == 12 || !isAlive)
                                    {
                                        //enemy->bomb.sendBomb(y);
                                        continue;
                                    }
                                    if (spr[y] != y)
                                    {
                                        window.draw(enemy->bomb.bombSprite[y]);
                                    }
                                    
                                }
                                else
                                {
                                    enemy->bomb.sendBomb(y);
                                }
                            }
                            break;
                        case 1:
                            totalEnemies = 12;
                            for (int t = 0; t < 21; t++)
                            {
                                if (spr[t] != t)
                                {
                                    for (int i = 0; i < 21; i++)
                                    {
                                        if (i == 7 || i == 13 || i == 14 || i == 9 || i == 10 || i == 11 || i == 15 || i == 20 || i == 19)
                                        {
                                            continue;
                                        }
                                        if (bulletTouch(i))
                                        {
                                            if (spr[i] != i)
                                            {
                                                if (addOnCount == 1)
                                                {
                                                    p->addOn->makeItem(enemy->getEnemySprite(i));
                                                }
                                                if (!fire.isEaten)
                                                {
                                                    p->respawnFire(0);
                                                }
                                                clearings++;
                                                score+=10;
                                                enemy->bomb.isBombShow[i] = false;
                                                for (int o = 0; o < 4; o++)
                                                {
                                                    enemy->destroy(i);
                                                    window.draw(enemy->getDestructionSprite(o));
                                                }
                                                spr[i] = i;
                                                continue;
                                            }
                                        }
                                        if (spr[i] != i)
                                        {
                                            sf::FloatRect enemyBounds = enemy->getEnemySprite(i).getLocalBounds();
                                            sf::FloatRect playerBounds = p->playerSprite.getLocalBounds();

                                            // Get the position components of the sprites
                                            float enemyX = enemy->getEnemySprite(i).getPosition().x;
                                            float enemyY = enemy->getEnemySprite(i).getPosition().y;
                                            float playerX = p->playerSprite.getPosition().x;
                                            float playerY = p->playerSprite.getPosition().y;

                                            // Adjust the bounds with the positions
                                            enemyBounds.left += enemyX;
                                            enemyBounds.top += enemyY;
                                            playerBounds.left += playerX;
                                            playerBounds.top += playerY;

                                            if (enemyBounds.intersects(playerBounds) && isAlive)
                                            {
                                                isAlive = false;
                                                lives--;
                                                cout << "Enemy\n";
                                            }
                                            window.draw(enemy->getEnemySprite(i));
                                        }
                                        if ((randAttack == 0) && (spr[i] != i))
                                        {
                                            enemy->bomb.makeBomb(enemy->getEnemySprite(bombEnemy), bombEnemy);
                                        }

                                    }
                                }
                                if (clearings == totalEnemies)
                                {
                                    isPhaseClear = true;
                                    // cout << "All Clear" << endl;
                                }
                            }
                            for (int y = 0; y < 21; y++)
                            {
                                if (enemy->bomb.isBombShow[y] == true)
                                {
                                    if (y == 7 || y == 13 || y == 14 || y == 9 || y == 10 || y == 11 || y == 15 || y == 20 || y == 19)
                                    {
                                        //enemy->bomb.sendBomb(y);
                                        continue;
                                    }
                                    if (!isAlive)
                                    {
                                        continue;
                                    }
                                    if (spr[y] != y)
                                    {
                                        window.draw(enemy->bomb.bombSprite[y]);
                                    }

                                }
                                else
                                {
                                    enemy->bomb.sendBomb(y);
                                }
                            }
                            break;
                        case 2:
                            totalEnemies = 9;
                            for (int t = 0; t < 21; t++)
                            {
                                if (spr[t] != t)
                                {
                                    for (int i = 0; i < 21; i++)
                                    {
                                        if (i == 0 || i == 1 || i == 2 || i == 4 || i == 5 || i == 6 || i == 14 || i == 15 || i == 16 || i == 18 || i == 19 || i == 20)
                                        {
                                            continue;
                                        }
                                        if (bulletTouch(i))
                                        {
                                            if (spr[i] != i)
                                            {
                                                if (addOnCount == 1)
                                                {
                                                    p->addOn->makeItem(enemy->getEnemySprite(i));
                                                }
                                                if (!fire.isEaten)
                                                {
                                                    p->respawnFire(0);
                                                }
                                                clearings++;
                                                score+=10;
                                                enemy->bomb.isBombShow[i] = false;
                                                for (int o = 0; o < 4; o++)
                                                {
                                                    enemy->destroy(i);
                                                    window.draw(enemy->getDestructionSprite(o));
                                                }
                                                spr[i] = i;
                                                continue;
                                            }
                                        }
                                        if (spr[i] != i)
                                        {
                                            sf::FloatRect enemyBounds = enemy->getEnemySprite(i).getLocalBounds();
                                            sf::FloatRect playerBounds = p->playerSprite.getLocalBounds();

                                            // Get the position components of the sprites
                                            float enemyX = enemy->getEnemySprite(i).getPosition().x;
                                            float enemyY = enemy->getEnemySprite(i).getPosition().y;
                                            float playerX = p->playerSprite.getPosition().x;
                                            float playerY = p->playerSprite.getPosition().y;

                                            // Adjust the bounds with the positions
                                            enemyBounds.left += enemyX;
                                            enemyBounds.top += enemyY;
                                            playerBounds.left += playerX;
                                            playerBounds.top += playerY;

                                            if (enemyBounds.intersects(playerBounds) && isAlive)
                                            {
                                                isAlive = false;
                                                lives--;
                                                cout << "Enemy\n";
                                            }
                                            window.draw(enemy->getEnemySprite(i));
                                        }
                                        if ((randAttack == 0) && (spr[i] != i))
                                        {
                                            enemy->bomb.makeBomb(enemy->getEnemySprite(bombEnemy), bombEnemy);
                                        }

                                    }
                                }
                                if (clearings == totalEnemies)
                                {
                                    isPhaseClear = true;
                                    // cout << "All Clear" << endl;
                                }
                            }
                            for (int i = 0; i < 21; i++)
                            {
                                if (enemy->bomb.isBombShow[i] == true)
                                {
                                    if (i == 0 || i == 1 || i == 2 || i == 4 || i == 5 || i == 6 || i == 14 || i == 15 || i == 16 || i == 18 || i == 19 || i == 20)
                                    {
                                        //enemy->bomb.sendBomb(i);
                                        continue;
                                    }
                                    if (!isAlive)
                                    {
                                        continue;
                                    }
                                    if (spr[i] != i)
                                    {
                                        window.draw(enemy->bomb.bombSprite[i]);
                                    }

                                }
                                else
                                {
                                    enemy->bomb.sendBomb(i);
                                }
                            }
                            break;
                        }
                    }
                    else if (enemyLevel == 1)
                    {
                        switch (enemyPhase)
                        {
                        case 0:
                            totalEnemies = 8;
                            for (int t = 0; t < 21; t++)
                            {
                                if (spr[t] != t)
                                {
                                    for (int i = 0; i < 21; i++)
                                    {
                                        if (i == 1 || i == 5 || i == 6 || i == 7 || i == 9 || i == 11 || i == 13 || i == 14 || i == 15 || i == 19 || i == 17 || i == 20)
                                        {
                                            continue;
                                        }
                                        if (bulletTouch(i))
                                        {
                                            if (spr[i] != i)
                                            {
                                                if (addOnCount == 1)
                                                {
                                                    p->addOn->makeItem(enemy->getEnemySprite(i));
                                                }
                                                if (!fire.isEaten)
                                                {
                                                    p->respawnFire(0);
                                                }
                                                clearings++;
                                                score += 20;
                                                enemy->bomb.isBombShow[i] = false;
                                                // cout << clearings << endl;
                                                for (int o = 0; o < 4; o++)
                                                {
                                                    enemy->destroy(i);
                                                    window.draw(enemy->getDestructionSprite(o));
                                                }
                                                spr[i] = i;
                                                continue;
                                            }
                                        }
                                        if (spr[i] != i)
                                        {
                                            sf::FloatRect enemyBounds = enemy->getEnemySprite(i).getLocalBounds();
                                            sf::FloatRect playerBounds = p->playerSprite.getLocalBounds();

                                            // Get the position components of the sprites
                                            float enemyX = enemy->getEnemySprite(i).getPosition().x;
                                            float enemyY = enemy->getEnemySprite(i).getPosition().y;
                                            float playerX = p->playerSprite.getPosition().x;
                                            float playerY = p->playerSprite.getPosition().y;

                                            // Adjust the bounds with the positions
                                            enemyBounds.left += enemyX;
                                            enemyBounds.top += enemyY;
                                            playerBounds.left += playerX;
                                            playerBounds.top += playerY;

                                            if (enemyBounds.intersects(playerBounds) && isAlive)
                                            {
                                                isAlive = false;
                                                lives--;
                                                cout << "Enemy\n";
                                            }
                                            window.draw(enemy->getEnemySprite(i));
                                        }
                                        if ((randAttack == 0) && (spr[i] != i))
                                        {
                                            enemy->bomb.makeBomb(enemy->getEnemySprite(bombEnemy), bombEnemy);
                                        }

                                    }
                                }
                                if (clearings == totalEnemies)
                                {
                                    isPhaseClear = true;
                                    // cout << "All Clear" << endl;
                                }
                            }
                            for (int i = 0; i < 21; i++)
                            {
                                if (enemy->bomb.isBombShow[i] == true)
                                {
                                    if (i == 1 || i == 5 || i == 6 || i == 7 || i == 9 || i == 11 || i == 13 || i == 14 || i == 15 || i == 19 || i == 17 || i == 20)
                                    {
                                        //enemy->bomb.sendBomb(i);
                                        continue;
                                    }
                                    if (!isAlive)
                                    {
                                        continue;
                                    }
                                    if (spr[i] != i)
                                    {
                                        window.draw(enemy->bomb.bombSprite[i]);
                                    }

                                }
                                else
                                {
                                    enemy->bomb.sendBomb(i);
                                }
                            }
                            break;
                        case 1:
                            totalEnemies = 8;
                            for (int t = 0; t < 21; t++)
                            {
                                if (spr[t] != t)
                                {
                                    for (int i = 0; i < 21; i++)
                                    {
                                        if (i == 1 || i == 5 || i == 6 || i == 7 || i == 9 || i == 11 || i == 13 || i == 14 || i == 15 || i == 17 || i == 19 || i == 20 || i == 3)
                                        {
                                            continue;
                                        }
                                        if (bulletTouch(i))
                                        {
                                            if (spr[i] != i)
                                            {
                                                if (addOnCount == 1)
                                                {
                                                    p->addOn->makeItem(enemy->getEnemySprite(i));
                                                }
                                                if (!fire.isEaten)
                                                {
                                                    p->respawnFire(0);
                                                }
                                                clearings++;
                                                score +=20;
                                                enemy->bomb.isBombShow[i] = false;
                                                for (int o = 0; o < 4; o++)
                                                {
                                                    enemy->destroy(i);
                                                    window.draw(enemy->getDestructionSprite(o));
                                                }
                                                spr[i] = i;
                                                continue;
                                            }
                                        }
                                        if (spr[i] != i)
                                        {
                                            sf::FloatRect enemyBounds = enemy->getEnemySprite(i).getLocalBounds();
                                            sf::FloatRect playerBounds = p->playerSprite.getLocalBounds();

                                            // Get the position components of the sprites
                                            float enemyX = enemy->getEnemySprite(i).getPosition().x;
                                            float enemyY = enemy->getEnemySprite(i).getPosition().y;
                                            float playerX = p->playerSprite.getPosition().x;
                                            float playerY = p->playerSprite.getPosition().y;

                                            // Adjust the bounds with the positions
                                            enemyBounds.left += enemyX;
                                            enemyBounds.top += enemyY;
                                            playerBounds.left += playerX;
                                            playerBounds.top += playerY;

                                            if (enemyBounds.intersects(playerBounds) && isAlive)
                                            {
                                                isAlive = false;
                                                lives--;
                                                cout << "Enemy\n";
                                            }
                                            window.draw(enemy->getEnemySprite(i));
                                        }
                                        if ((randAttack == 0) && (spr[i] != i))
                                        {
                                            enemy->bomb.makeBomb(enemy->getEnemySprite(bombEnemy), bombEnemy);
                                        }

                                    }
                                }
                                if (clearings == totalEnemies)
                                {
                                    isPhaseClear = true;
                                    // cout << "All Clear" << endl;
                                }
                            }
                            for (int i = 0; i < 21; i++)
                            {
                                if (enemy->bomb.isBombShow[i] == true)
                                {
                                    if (i == 1 || i == 5 || i == 6 || i == 7 || i == 9 || i == 11 || i == 13 || i == 14 || i == 15 || i == 17 || i == 19 || i == 20 || i == 3)
                                    {
                                        //enemy->bomb.sendBomb(i);
                                        continue;
                                    }
                                    if (!isAlive)
                                    {
                                        continue;
                                    }
                                    if (spr[i] != i)
                                    {
                                        window.draw(enemy->bomb.bombSprite[i]);
                                    }

                                }
                                else
                                {
                                    enemy->bomb.sendBomb(i);
                                }
                            }
                            break;
                        case 2:
                            totalEnemies = 13;
                            for (int t = 0; t < 21; t++)
                            {
                                if (spr[t] != t)
                                {
                                    for (int i = 0; i < 21; i++)
                                    {
                                        if (i == 7 || i == 13 || i == 5 || i == 6 || i == 14 || i == 15 || i == 19 || i == 20)
                                        {
                                            continue;
                                        }
                                        if (bulletTouch(i))
                                        {
                                            if (spr[i] != i)
                                            {
                                                if (addOnCount == 1)
                                                {
                                                    p->addOn->makeItem(enemy->getEnemySprite(i));
                                                }
                                                if (!fire.isEaten)
                                                {
                                                    p->respawnFire(0);
                                                }
                                                clearings++;
                                                score +=20;
                                                enemy->bomb.isBombShow[i] = false;
                                                for (int o = 0; o < 4; o++)
                                                {
                                                    enemy->destroy(i);
                                                    window.draw(enemy->getDestructionSprite(o));
                                                }
                                                spr[i] = i;
                                                continue;
                                            }
                                        }
                                        if (spr[i] != i)
                                        {
                                            sf::FloatRect enemyBounds = enemy->getEnemySprite(i).getLocalBounds();
                                            sf::FloatRect playerBounds = p->playerSprite.getLocalBounds();

                                            // Get the position components of the sprites
                                            float enemyX = enemy->getEnemySprite(i).getPosition().x;
                                            float enemyY = enemy->getEnemySprite(i).getPosition().y;
                                            float playerX = p->playerSprite.getPosition().x;
                                            float playerY = p->playerSprite.getPosition().y;

                                            // Adjust the bounds with the positions
                                            enemyBounds.left += enemyX;
                                            enemyBounds.top += enemyY;
                                            playerBounds.left += playerX;
                                            playerBounds.top += playerY;

                                            if (enemyBounds.intersects(playerBounds) && isAlive)
                                            {
                                                isAlive = false;
                                                lives--;
                                                cout << "Enemy\n";
                                            }
                                            window.draw(enemy->getEnemySprite(i));
                                        }
                                        if ((randAttack == 0) && (spr[i] != i))
                                        {
                                            enemy->bomb.makeBomb(enemy->getEnemySprite(bombEnemy), bombEnemy);
                                        }

                                    }
                                }
                                if (clearings == totalEnemies)
                                {
                                    isPhaseClear = true;
                                    // cout << "All Clear" << endl;
                                }
                            }
                            for (int i = 0; i < 21; i++)
                            {
                                if (enemy->bomb.isBombShow[i] == true)
                                {
                                    if (i == 7 || i == 13 || i == 5 || i == 6 || i == 14 || i == 15 || i == 19 || i == 20)
                                    {
                                        //enemy->bomb.sendBomb(i);
                                        continue;
                                    }
                                    if (!isAlive)
                                    {
                                        continue;
                                    }
                                    if (spr[i] != i)
                                    {
                                        window.draw(enemy->bomb.bombSprite[i]);
                                    }

                                }
                                else
                                {
                                    enemy->bomb.sendBomb(i);
                                }
                            }
                            break;
                        }
                    }
                    else if (enemyLevel == 2)
                    {
                        switch (enemyPhase)
                        {
                        case 0:
                            totalEnemies = 21;
                            for (int t = 0; t < 21; t++)
                            {
                                if (spr[t] != t)
                                {
                                    for (int i = 0; i < 21; i++)
                                    {
                                        if (bulletTouch(i))
                                        {
                                            if (spr[i] != i)
                                            {
                                                if (addOnCount == 1)
                                                {
                                                    p->addOn->makeItem(enemy->getEnemySprite(i));
                                                }
                                                if (!fire.isEaten)
                                                {
                                                    p->respawnFire(0);
                                                }
                                                clearings++;
                                                score += 30;
                                                enemy->bomb.isBombShow[i] = false;
                                                // cout << clearings << endl;
                                                for (int o = 0; o < 4; o++)
                                                {
                                                    enemy->destroy(i);
                                                    window.draw(enemy->getDestructionSprite(o));
                                                }
                                                spr[i] = i;
                                                continue;
                                            }
                                        }
                                        if (spr[i] != i)
                                        {
                                            sf::FloatRect enemyBounds = enemy->getEnemySprite(i).getLocalBounds();
                                            sf::FloatRect playerBounds = p->playerSprite.getLocalBounds();

                                            // Get the position components of the sprites
                                            float enemyX = enemy->getEnemySprite(i).getPosition().x;
                                            float enemyY = enemy->getEnemySprite(i).getPosition().y;
                                            float playerX = p->playerSprite.getPosition().x;
                                            float playerY = p->playerSprite.getPosition().y;

                                            // Adjust the bounds with the positions
                                            enemyBounds.left += enemyX;
                                            enemyBounds.top += enemyY;
                                            playerBounds.left += playerX;
                                            playerBounds.top += playerY;

                                            if (enemyBounds.intersects(playerBounds) && isAlive)
                                            {
                                                isAlive = false;
                                                lives--;
                                                cout << "Enemy\n";
                                            }
                                            window.draw(enemy->getEnemySprite(i));
                                        }
                                        if ((randAttack == 0) && (spr[i] != i))
                                        {
                                            enemy->bomb.makeBomb(enemy->getEnemySprite(bombEnemy), bombEnemy);
                                        }

                                    }
                                }
                                if (clearings == totalEnemies)
                                {
                                    isPhaseClear = true;
                                    // cout << "All Clear" << endl;
                                }
                            }
                            for (int i = 0; i < 21; i++)
                            {
                                if (enemy->bomb.isBombShow[i] == true)
                                {
                                    if (!isAlive)
                                    {
                                        continue;
                                    }
                                    if (spr[i] != i)
                                    {
                                        window.draw(enemy->bomb.bombSprite[i]);
                                    }

                                }
                                else
                                {
                                    enemy->bomb.sendBomb(i);
                                }
                            }
                            break;
                        case 1:
                            totalEnemies = 11;
                            for (int t = 0; t < 21; t++)
                            {
                                if (spr[t] != t)
                                {
                                    for (int i = 0; i < 21; i++)
                                    {
                                        if (i == 1 || i == 5 || i == 6 || i == 7 || i == 13 || i == 14 || i == 15 || i == 19 || i == 20 || i == 3)
                                        {
                                            continue;
                                        }
                                        if (bulletTouch(i))
                                        {
                                            if (spr[i] != i)
                                            {
                                                if (addOnCount == 1)
                                                {
                                                    p->addOn->makeItem(enemy->getEnemySprite(i));
                                                }
                                                if (!fire.isEaten)
                                                {
                                                    p->respawnFire(0);
                                                }
                                                clearings++;
                                                score += 30;
                                                enemy->bomb.isBombShow[i] = false;
                                                for (int o = 0; o < 4; o++)
                                                {
                                                    enemy->destroy(i);
                                                    window.draw(enemy->getDestructionSprite(o));
                                                }
                                                spr[i] = i;
                                                continue;
                                            }
                                        }
                                        if (spr[i] != i)
                                        {
                                            sf::FloatRect enemyBounds = enemy->getEnemySprite(i).getLocalBounds();
                                            sf::FloatRect playerBounds = p->playerSprite.getLocalBounds();

                                            // Get the position components of the sprites
                                            float enemyX = enemy->getEnemySprite(i).getPosition().x;
                                            float enemyY = enemy->getEnemySprite(i).getPosition().y;
                                            float playerX = p->playerSprite.getPosition().x;
                                            float playerY = p->playerSprite.getPosition().y;

                                            // Adjust the bounds with the positions
                                            enemyBounds.left += enemyX;
                                            enemyBounds.top += enemyY;
                                            playerBounds.left += playerX;
                                            playerBounds.top += playerY;

                                            if (enemyBounds.intersects(playerBounds) && isAlive)
                                            {
                                                isAlive = false;
                                                lives--;
                                                cout << "Enemy\n";
                                            }
                                            window.draw(enemy->getEnemySprite(i));
                                        }
                                        if ((randAttack == 0) && (spr[i] != i))
                                        {
                                            enemy->bomb.makeBomb(enemy->getEnemySprite(bombEnemy), bombEnemy);
                                        }

                                    }
                                }
                                if (clearings == totalEnemies)
                                {
                                    isPhaseClear = true;
                                    // cout << "All Clear" << endl;
                                }
                            }
                            for (int i = 0; i < 21; i++)
                            {
                                if (enemy->bomb.isBombShow[i] == true)
                                {
                                    if (i == 1 || i == 5 || i == 6 || i == 7 || i == 13 || i == 14 || i == 15 || i == 19 || i == 20 || i == 3)
                                    {
                                        //enemy->bomb.sendBomb(i);
                                        continue;
                                    }
                                    if (!isAlive)
                                    {
                                        continue;
                                    }
                                    if (spr[i] != i)
                                    {
                                        window.draw(enemy->bomb.bombSprite[i]);
                                    }

                                }
                                else
                                {
                                    enemy->bomb.sendBomb(i);
                                }
                            }
                            break;
                        case 2:
                            totalEnemies = 12;
                            for (int t = 0; t < 21; t++)
                            {
                                if (spr[t] != t)
                                {
                                    for (int i = 0; i < 21; i++)
                                    {
                                        if (i == 1 || i == 5 || i == 6 || i == 7 || i == 13 || i == 14 || i == 15 || i == 19 || i == 20)
                                        {
                                            continue;
                                        }
                                        if (bulletTouch(i))
                                        {
                                            if (spr[i] != i)
                                            {
                                                if (addOnCount == 1)
                                                {
                                                    p->addOn->makeItem(enemy->getEnemySprite(i));
                                                }
                                                if (!fire.isEaten)
                                                {
                                                    p->respawnFire(0);
                                                }
                                                clearings++;
                                                score += 30;
                                                enemy->bomb.isBombShow[i] = false;
                                                for (int o = 0; o < 4; o++)
                                                {
                                                    enemy->destroy(i);
                                                    window.draw(enemy->getDestructionSprite(o));
                                                }
                                                spr[i] = i;
                                                continue;
                                            }
                                        }
                                        if (spr[i] != i)
                                        {
                                            sf::FloatRect enemyBounds = enemy->getEnemySprite(i).getLocalBounds();
                                            sf::FloatRect playerBounds = p->playerSprite.getLocalBounds();

                                            // Get the position components of the sprites
                                            float enemyX = enemy->getEnemySprite(i).getPosition().x;
                                            float enemyY = enemy->getEnemySprite(i).getPosition().y;
                                            float playerX = p->playerSprite.getPosition().x;
                                            float playerY = p->playerSprite.getPosition().y;

                                            // Adjust the bounds with the positions
                                            enemyBounds.left += enemyX;
                                            enemyBounds.top += enemyY;
                                            playerBounds.left += playerX;
                                            playerBounds.top += playerY;

                                            if (enemyBounds.intersects(playerBounds) && isAlive)
                                            {
                                                isAlive = false;
                                                lives--;
                                                cout << "Enemy\n";
                                            }
                                            window.draw(enemy->getEnemySprite(i));
                                        }
                                        if ((randAttack == 0) && (spr[i] != i))
                                        {
                                            enemy->bomb.makeBomb(enemy->getEnemySprite(bombEnemy), bombEnemy);
                                        }
                                        
                                    }
                                }
                                if (clearings == totalEnemies)
                                {
                                    isPhaseClear = true;
                                    // cout << "All Clear" << endl;
                                }
                            }
                            for (int i = 0; i < 21; i++)
                            {
                                if (enemy->bomb.isBombShow[i] == true)
                                {
                                    if (i == 1 || i == 5 || i == 6 || i == 7 || i == 13 || i == 14 || i == 15 || i == 19 || i == 20)
                                    {
                                        //enemy->bomb.sendBomb(i);
                                        continue;
                                    }
                                    if (!isAlive)
                                    {
                                        continue;
                                    }
                                    if (spr[i] != i)
                                    {
                                        window.draw(enemy->bomb.bombSprite[i]);
                                    }
                                    
                                }
                                else
                                {
                                    enemy->bomb.sendBomb(i);
                                }
                            }
                            break;
                        }
                    }
                }

                // Level Number...
                if (!isBoss)
                {
                    if (!isEnemyOn)
                    {
                        switch (enemyLevel)
                        {
                        case 0:
                            window.draw(level1Text);
                            break;
                        case 1:
                            window.draw(level2Text);
                            break;
                        case 2:
                            window.draw(level3Text);
                            break;
                        }
                        switch (enemyPhase)
                        {
                        case 0:
                            window.draw(phase1Text);
                            break;
                        case 1:
                            window.draw(phase2Text);
                            break;
                        case 2:
                            window.draw(phase3Text);
                            break;
                        }
                    }
                }
                else
                {
                    if (bossClock.getElapsedTime().asMilliseconds() < 5000)
                    {
                        window.draw(bossText);
                    }
                    else
                    {
                        window.draw(enemy->getEnemySprite(bossType));
                        if (bossType == 0)
                        {
                            window.draw(monster.attackSprite);
                        }
                        else if (bossType == 1)
                        {
                            for (int t = 0; t < 5; t++)
                            {
                                window.draw(monster.attackSprite2[t]);
                            }
                        }
                        else if (bossType == 2)
                        {
                            window.draw(dragon.attackSprite);
                            for (int t = 0; t < 5; t++)
                            {
                                window.draw(dragon.attackSprite2[t]);
                            }
                        }
                    }
                }
            }
            else
            {
                if (!isShowDragon)
                {
                    window.draw(dragonText);
                }
                else
                {
                    enemy = &rebel;
                    window.draw(enemy->getEnemySprite(0));
                    window.draw(rebel.attackSprite);
                    window.draw(rebel.guidedSprite);
                    for (int t = 0; t < 5; t++)
                    {
                        window.draw(rebel.attackSprite2[t]);
                    }
                }
            }

            //Add Ons
            if (!power.isEaten)
            {
                window.draw(power.itemSprite);
            }
            if (!fire.isEaten)
            {
                window.draw(fire.itemSprite);
            }
            if (!live.isEaten)
            {
                window.draw(live.itemSprite);
            }
            if (!danger.isEaten)
            {
                window.draw(danger.itemSprite);
            }
            
            // Ship Destruction...
            for (int i = 0; i < 21; i++)
            {
                if (((enemy->bomb.bombSprite[i].getGlobalBounds().intersects(p->playerSprite.getGlobalBounds()) && isAlive == true)) && isAlive && power.isEaten == false)
                {
                    if (enemy->bomb.isBombShow[i] == true && spr[i] != i)
                    {
                        //cout << enemy->bomb.bombSprite[i].getPosition().x << "\t" << enemy->bomb.bombSprite[i].getPosition().y << endl;
                        isAlive = false;
                        lives--;
                        //cout << "Bomb\n";
                    }
                }
            }

            if ((monster.attackSprite.getGlobalBounds().intersects(p->playerSprite.getGlobalBounds())) && isAlive && power.isEaten == false)
            {
                isAlive = false;
                lives--;
                //cout << "MonsterBeem\n";
            }

            for (int i = 0; i < 5; i++)
            {
                if (monster.attackSprite2[i].getGlobalBounds().intersects(p->playerSprite.getGlobalBounds()) && isAlive && power.isEaten == false)
                {
                    isAlive = false;
                    lives--;
                    //cout << "MonsterBomb\n";
                }
            }

            if ((dragon.attackSprite.getGlobalBounds().intersects(p->playerSprite.getGlobalBounds())) && isAlive && power.isEaten == false)
            {
                isAlive = false;
                lives--;
                //cout << "DragonBeem\n";
            }

            for (int i = 0; i < 5; i++)
            {
                if (dragon.attackSprite2[i].getGlobalBounds().intersects(p->playerSprite.getGlobalBounds()) && isAlive && power.isEaten == false)
                {
                    isAlive = false;
                    lives--;
                    //cout << "DragonBomb\n";
                }
            }

            if ((rebel.attackSprite.getGlobalBounds().intersects(p->playerSprite.getGlobalBounds())) && isAlive && power.isEaten == false)
            {
                isAlive = false;
                lives--;
                //cout << "DragonBeem\n";
            }

            for (int i = 0; i < 5; i++)
            {
                if (rebel.attackSprite2[i].getGlobalBounds().intersects(p->playerSprite.getGlobalBounds()) && isAlive && power.isEaten == false)
                {
                    isAlive = false;
                    lives--;
                    //cout << "DragonBomb\n";
                }
            }

            // Sprite Touching...

            
            if (!isDragon && isBoss)
            {
                if (monster.enemySprite1.getGlobalBounds().intersects(p->playerSprite.getGlobalBounds()) && isAlive)
                {
                    isAlive = false;
                    lives--;
                    cout << "Monster1\n";
                }

                if (monster.enemySprite2.getGlobalBounds().intersects(p->playerSprite.getGlobalBounds()) && isAlive)
                {
                    isAlive = false;
                    lives--;
                    cout << "Monster2\n";
                }

                if (dragon.enemySprite.getGlobalBounds().intersects(p->playerSprite.getGlobalBounds()) && isAlive)
                {
                    isAlive = false;
                    lives--;
                    cout << "Dragon\n";
                }
            }

            if (isDragon)
            {
                if (rebel.enemySprite.getGlobalBounds().intersects(p->playerSprite.getGlobalBounds()) && isAlive)
                {
                    isAlive = false;
                    lives--;
                    cout << "Rebel\n";
                }
            }




            if (isAlive)
            {
                window.draw(p->playerSprite);  // setting player on screen
                if ((!power.isEaten) && (!isP2) && (!isP3))
                {
                    window.draw(p->fireSprite[0]); // Bullet Sprite
                }
                else if ((!power.isEaten) && (isP2) && (!isP3))
                {
                    for (int f = 1; f < 3; f++)
                    {
                        window.draw(p->fireSprite[f]);
                    }
                }
                else if ((!power.isEaten) && (!isP2) && (isP3))
                {
                    for (int f = 10; f < 13; f++)
                    {
                        window.draw(p->fireSprite[f]);
                    }
                }
                else
                {
                    for (int f = 3; f < 10; f++)
                    {
                        window.draw(p->fireSprite[f]);
                    }
                }
            }
            if (!isAlive)
            {
                p->destroy();
                for (int i = 0; i < 4; i++)
                {
                    window.draw(p->shipDesSprite1[i]);
                }
                window.draw(p->shipDesSprite2);
                window.draw(p->shipDesSprite3);
                window.draw(p->shipDesSprite4);
                // shipClock.restart();
            }
             /*if (lives == 0)
             {
                 window.close();
             }*/
            window.draw(liveText);
            window.draw(scoreText);
            window.draw(barSprite);
            /*window.draw(liveNumText);
            window.draw(scoreNumText);*/
            window.display(); // Displying all the sprites
        }
    }
    bool bulletTouch(int j)
    {
        for (int i = 0; i < 13; i++)
        {
            if (!power.isEaten)
            {
                if (i < 10 && i > 2)
                {
                    continue;
                }
            }
            if (p->fireSprite[i].getGlobalBounds().intersects(enemy->getEnemySprite(j).getGlobalBounds()))
            {
                return true;
			}
        }
        return false;
        //return false;
    }
    /*void sendBombs()
    {
        for (int i = 0; i < 21; i++)
        {
            if (enemy->bomb.bombSprite[i].getPosition().y < 0)
            {
                enemy->bomb.isBombShow[i] = false;
            }
        }
    }*/

    void pause(RenderWindow& window)
    {
        // Font for the texts
        sf::Font font;

        font.loadFromFile("Fonts/BreeSerif-Regular.ttf");

        // Game Paused text
        sf::Text gamePausedText;
        gamePausedText.setFont(font);
        gamePausedText.setString("Game Paused");
        gamePausedText.setCharacterSize(60);
        gamePausedText.setFillColor(sf::Color::White);
        gamePausedText.setStyle(sf::Text::Bold);
        gamePausedText.setPosition(1400 / 2 - gamePausedText.getGlobalBounds().width / 2, 200);

        // Resume game text
        sf::Text resumeText;
        resumeText.setFont(font);
        resumeText.setString("1: Resume Game");
        resumeText.setCharacterSize(40);
        resumeText.setFillColor(sf::Color::White);
        resumeText.setPosition(1400 / 2 - resumeText.getGlobalBounds().width / 2, 400);

        // Options text
        sf::Text optionsText;
        optionsText.setFont(font);
        optionsText.setString("2: Restart Game");
        optionsText.setCharacterSize(40);
        optionsText.setFillColor(sf::Color::White);
        optionsText.setPosition(1400 / 2 - optionsText.getGlobalBounds().width / 2, 500);

        // Quit text
        sf::Text quitText;
        quitText.setFont(font);
        quitText.setString("3: Quit");
        quitText.setCharacterSize(40);
        quitText.setFillColor(sf::Color::White);
        quitText.setPosition(1400 / 2 - quitText.getGlobalBounds().width / 2, 600);

        sf::RectangleShape background;
        background.setSize(sf::Vector2f(1400, 1100));
        background.setFillColor(sf::Color(0, 0, 0, 128)); // Adjust the alpha value (128) for transparency

        // Draw the texts
        window.draw(background);
        window.draw(gamePausedText);
        window.draw(resumeText);
        window.draw(optionsText);
        window.draw(quitText);

        window.display();
        
        while(1)
        {
            sleep(microseconds(0.1));
            
            if (Keyboard::isKeyPressed(Keyboard::Num1)) // If down key is pressed
            {
                break;
            }
            if (Keyboard::isKeyPressed(Keyboard::Num2)) // If down key is pressed
            {
                window.close();
                Game g;
                g.start_game();
            }
            if (Keyboard::isKeyPressed(Keyboard::Num3)) // If down key is pressed
            {
                window.close();
                break;
            }
        }
    }


};

