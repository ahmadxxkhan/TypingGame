#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>
#include <cstdlib>

using namespace std;
using namespace sf;

string displayString(RenderWindow& window, const string& str, Font& font) {
    Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(30);
    text.setFillColor(Color::White);
    text.setPosition(20, 20);

    window.draw(text);
    return str;
}

void showStartPage(RenderWindow& window, Font& font, bool& gameStarted) {
    Text title;
    title.setFont(font);
    title.setString("Speed Typing Adventure");
    title.setCharacterSize(50);
    title.setFillColor(Color::White);
    title.setPosition(250, 100);

    Text instructions;
    instructions.setFont(font);
    instructions.setString(
        "Instructions:\n\n"
        "- Type the shown text accurately\n"
        "- Complete each level within the time limit\n"
        "- Progress through 5 levels to win\n\n"
        "Press ENTER to start"
    );
    instructions.setCharacterSize(30);
    instructions.setFillColor(Color::Cyan);
    instructions.setPosition(250, 250);

    while (window.isOpen() && !gameStarted) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
                gameStarted = true;
        }

        window.clear(Color(50, 50, 50));
        window.draw(title);
        window.draw(instructions);
        window.display();
    }
}

void showEndPage(RenderWindow& window, Font& font, bool won) {
    Text gameOverText;
    gameOverText.setFont(font);

    if (won) {
        gameOverText.setString("Congratulations!\nYou've Won!");
        gameOverText.setFillColor(Color::Green);
    }
    else {
        gameOverText.setString("Game Over!\nBetter luck next time!");
        gameOverText.setFillColor(Color::Red);
    }

    gameOverText.setCharacterSize(50);
    gameOverText.setPosition(250, 200);

    Text exitText;
    exitText.setFont(font);
    exitText.setString("Press ESC to exit");
    exitText.setCharacterSize(30);
    exitText.setFillColor(Color::White);
    exitText.setPosition(350, 400);

    bool exitGame = false;
    while (window.isOpen() && !exitGame) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed ||
                (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
                window.close();
                exitGame = true;
            }
        }

        window.clear(Color(50, 50, 50));
        window.draw(gameOverText);
        window.draw(exitText);
        window.display();
    }
}

void typingGame(RenderWindow& window, string& str, Font& font, int level) {
    vector<RectangleShape> rectangles(26);
    vector<Text> letters(26);

    vector<Vector2f> positions = {
        {50, 100}, {110, 100}, {170, 100}, {230, 100}, {290, 100}, {350, 100}, {410, 100}, {470, 100}, {530, 100}, {590, 100},
        {650, 100}, {710, 100}, {770, 100}, {80, 160}, {140, 160}, {200, 160}, {260, 160}, {320, 160}, {380, 160}, {440, 160},
        {500, 160}, {560, 160}, {620, 160}, {680, 160}, {740, 160}, {800, 160}
    };

    for (int i = 0; i < 26; ++i) {
        rectangles[i].setSize(Vector2f(50, 50));
        rectangles[i].setFillColor(Color::White);
        rectangles[i].setOutlineColor(Color::Black);
        rectangles[i].setOutlineThickness(2);
        rectangles[i].setPosition(positions[i]);

        letters[i].setFont(font);
        letters[i].setString(static_cast<char>('a' + i));
        letters[i].setCharacterSize(20);
        letters[i].setFillColor(Color::Black);
        letters[i].setPosition(rectangles[i].getPosition().x + 15, rectangles[i].getPosition().y + 10);
    }


    Texture texture;
    if (!texture.loadFromFile("player1.png")) {
        cout << "player wasn't loaded" << endl;
    }

    Sprite playersprite;
    playersprite.setTexture(texture);
    playersprite.setPosition(20, window.getSize().y - 80);

    RectangleShape endpoint(Vector2f(30, 30));
    endpoint.setPosition(875, 530);
    endpoint.setFillColor(Color::Green);

    size_t typedIndex = 0;
    float speedFactor = static_cast<float>(str.length()) / 200.0f;
    float playerSpeed = 5.0f / speedFactor;

    Clock clock;
    float timeLimit = 25.0f;
    float remainingTime = timeLimit;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

    if (event.type == Event::TextEntered && typedIndex < str.length()) {
      char enteredChar = static_cast<char>(event.text.unicode);

  if (str[typedIndex] == ' ' && enteredChar == ' ') {
     typedIndex++;
     continue;
    }

 if (enteredChar == str[typedIndex]) {
                    int rectIndex = enteredChar - 'a';
                    if (rectIndex >= 0 && rectIndex < 26) {
                        rectangles[rectIndex].setFillColor(Color::Green);
                        typedIndex++;

       float playerNewX = playersprite.getPosition().x + playerSpeed;
           if (playerNewX + playersprite.getLocalBounds().width <= window.getSize().x) {
        playersprite.setPosition(playerNewX, playersprite.getPosition().y);
        }

      rectangles[rectIndex].setFillColor(Color::White);
                    }
                }
            }
        }

        if (playersprite.getGlobalBounds().intersects(endpoint.getGlobalBounds())) {
            cout << "Level " << level << " completed!" << endl;
            return;
        }

        remainingTime -= clock.restart().asSeconds();
        if (remainingTime <= 0.0f) {
            cout << "Game Lost - Time's up!" << endl;
            window.close();
            return;
        }

        window.clear(Color(50, 50, 50));

        Text levelText;
        levelText.setFont(font);
        levelText.setString("Level: " + to_string(level));
        levelText.setCharacterSize(30);
        levelText.setFillColor(Color::Cyan);
        levelText.setPosition(20, 60);
        window.draw(levelText);

        displayString(window, str, font);

        Text typedText;
        typedText.setFont(font);
        typedText.setString(str.substr(0, typedIndex));
        typedText.setCharacterSize(30);
        typedText.setFillColor(Color::Green);
        typedText.setPosition(20, 20);
        window.draw(typedText);

        Text timerText;
        timerText.setFont(font);
        timerText.setString("Time: " + to_string(static_cast<int>(remainingTime)) + "s");
        timerText.setCharacterSize(30);
        timerText.setFillColor(Color::Red);
        timerText.setPosition(750, 320);
        window.draw(timerText);

        for (int i = 0; i < 26; ++i) {
            window.draw(rectangles[i]);
            window.draw(letters[i]);
        }

        window.draw(playersprite);
        window.draw(endpoint);
        window.display();
    }
}

int main() {
    RenderWindow window(VideoMode(900, 600), "Speed Typing Adventure");
    window.setFramerateLimit(60);

    Font font;
    if (!font.loadFromFile("pokemon.ttf")) {
        cout << "Error loading font!" << endl;
        return -1;
    }

    bool gameStarted = false;
    bool gameOver = false;
    bool wonGame = false;

    showStartPage(window, font, gameStarted);

    if (gameStarted) {
        vector<string> levelTexts = {
            "the quick brown fox jumps over the lazy dog",
            "practice makes perfect keep trying",
            "success comes from consistent effort",
            "believe in yourself and your abilities",
            "determination leads to achievement",
            "will you be the person who will own this institue",
            "now you should keep your mouth close"
           };

        int level = 1;

        while (window.isOpen() && !gameOver) {
            if (level > 7) {
                wonGame = true;
                gameOver = true;
                continue;
            }

            window.clear(Color(50, 50, 50));
       Text levelText;
            levelText.setFont(font);
     levelText.setString("Level " + to_string(level) + "\nPress ENTER to continue");
        levelText.setCharacterSize(40);
           levelText.setFillColor(Color::White);
       levelText.setPosition(300, 250);
     window.draw(levelText);
 window.display();


            bool levelStarted = false;
            while (!levelStarted && window.isOpen()) {
      Event event;
     while (window.pollEvent(event)) {
    if (event.type == Event::Closed) {
           window.close();
        return 0;
      }
  if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return) {
                        levelStarted = true;
               }
                }
            }

            string currentText = levelTexts[level - 1];
            typingGame(window, currentText, font, level);

            if (!window.isOpen()) {
                gameOver = true;
                wonGame = false;
                break;
            }

            level++;
        }


        if (window.isOpen()) {
            showEndPage(window, font, wonGame);
        }
    }

    return 0;
} 