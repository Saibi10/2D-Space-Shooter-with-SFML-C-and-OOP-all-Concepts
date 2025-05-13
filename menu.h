
#include "game.h"
class Menu
{
private:
    
    Texture logoTex, bgTex, shipTex;
    Sprite logoSprite, bgSprite, shipSprite, shipSprite2;

    Font menuFont;
    Text startGameText;
    Text instructionsText;
    Text scoreText;
    Text quitText;

    Clock clock;

    int n;

    Game g;

public:
    // add menu attributes here
    Menu()
    {

        if (!menuFont.loadFromFile("Fonts/BreeSerif-Regular.ttf"))
        {
            cout << "Failed to load font" << endl;
        }
        // Create start game text
        startGameText.setFont(menuFont);
        startGameText.setString("Start Game");
        startGameText.setCharacterSize(36);
        startGameText.setFillColor(Color::Red);
        startGameText.setPosition(600, 350);

        // Create instructions text
        instructionsText.setFont(menuFont);
        instructionsText.setString("Instructions");
        instructionsText.setCharacterSize(36);
        instructionsText.setFillColor(Color::White);
        instructionsText.setPosition(600, 450);

        // Create Score text
        scoreText.setFont(menuFont);
        scoreText.setString("Scores");
        scoreText.setCharacterSize(36);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(600, 550);

        // Create quit text
        quitText.setFont(menuFont);
        quitText.setString("Quit");
        quitText.setCharacterSize(36);
        quitText.setFillColor(Color::White);
        quitText.setPosition(600, 650);

        n = 1;

        clock.restart();

        logoTex.loadFromFile("img/Logo.png");
        logoSprite.setTexture(logoTex);
        logoSprite.setPosition(350, 50);
        logoSprite.setScale(2.3, 1.5);

        bgTex.loadFromFile("img/Galaxy.png");
        bgSprite.setTexture(bgTex);
        //bgSprite.setScale(3, 3);

        shipTex.loadFromFile("img/player_ship.png");
        shipSprite.setTexture(shipTex);
        shipSprite.setScale(0.5, 0.5);
        shipSprite.setRotation(90);
        shipSprite.setPosition(570, 350);
        //
        shipSprite2.setTexture(shipTex);
        shipSprite2.setScale(0.5, 0.5);
        shipSprite2.setRotation(-90);
        shipSprite2.setPosition(800, 405);
        //
        
    }

    void display_menu()
    {
        RenderWindow window(VideoMode(1400, 1100), title);

        while (window.isOpen())
        {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close();          // close the game
                else if (e.type == Event::KeyPressed)
                {
                    if (clock.getElapsedTime().asMilliseconds() > 100)
                    {
                        clock.restart();
                        if (e.key.code == Keyboard::Up)
                        {
                            if (n != 1)
                            {
                                n--;
                            }
                            // cout << n << endl;
                            updateMenu(n);
                        }
                        else if (e.key.code == Keyboard::Down)
                        {
                            if (n != 4)
                            {
                                n++;
                            }
                            // cout << n << endl;
                            updateMenu(n);
                        }
                        // Starting the Game...
                        else if (e.key.code == Keyboard::Enter)
                        {
                            switch (n)
                            {
                            case 1:
                                window.close();
                                g.start_game();
                                break;
                            case 4:
                                window.close();
                                break;
                            }
                        }
                    }
                }
            }

            window.clear(sf::Color::Black);
            window.draw(bgSprite);
            window.draw(logoSprite);
            window.draw(shipSprite);
            window.draw(shipSprite2);
            window.draw(startGameText);
            window.draw(instructionsText);
            window.draw(scoreText);
            window.draw(quitText);
            window.display();
        }

        // display menu screen here

        // add functionality of all the menu options here

        // if Start game option is chosen
    }

    void updateMenu(int s)
    {
        switch (s)
        {
        case 1:
            startGameText.setFillColor(Color::Red);
            instructionsText.setFillColor(Color::White);
            scoreText.setFillColor(Color::White);
            quitText.setFillColor(Color::White);
            shipSprite.setPosition(570, 350);
            shipSprite2.setPosition(800, 405);
            break;
        case 2:
            startGameText.setFillColor(Color::White);
            instructionsText.setFillColor(Color::Red);
            scoreText.setFillColor(Color::White);
            quitText.setFillColor(Color::White);
            shipSprite.setPosition(578, 450);
            shipSprite2.setPosition(809, 500);
            break;
        case 3:
            startGameText.setFillColor(Color::White);
            instructionsText.setFillColor(Color::White);
            scoreText.setFillColor(Color::Red);
            quitText.setFillColor(Color::White);
            shipSprite.setPosition(578, 550);
            shipSprite2.setPosition(720, 600);
            break;
        case 4:
            startGameText.setFillColor(Color::White);
            instructionsText.setFillColor(Color::White);
            scoreText.setFillColor(Color::White);
            quitText.setFillColor(Color::Red);
            shipSprite.setPosition(578, 650);
            shipSprite2.setPosition(680, 700);
            break;
        default:
            cout << "Wrong Input" << endl;
            break;
        }
    }
};
