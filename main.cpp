#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

using namespace std;

const int HEIGHT = 1000;
const int WIDTH = 1000;
const int SCALE = 10;

int getRealPos(int pos) {
    return pos * SCALE;
}

int getNextPos(int pos, int MAX_SIZE) {
    return (MAX_SIZE + getRealPos(pos) + SCALE) % MAX_SIZE;
}

int getPrevPos(int pos, int MAX_SIZE) {
    return (MAX_SIZE + getRealPos(pos) - SCALE) % MAX_SIZE;
}

int getNextPosWithOverflow(int pos) {
    return getRealPos(pos) + SCALE;
}

int RemoveOverflow(int pos, int MAX_SIZE) {
    return (MAX_SIZE + pos) % MAX_SIZE;
}

void fillPixel(sf::Uint8 *pixels, int posx, int posy, bool color) {
    int realPosX = getRealPos(posx), realPosY = getRealPos(posy);
    int nextPosX = getNextPosWithOverflow(posx), nextPosY = getNextPosWithOverflow(posy);
    for (int i = realPosX; i < nextPosX; i++) {
        for (int j = realPosY; j < nextPosY; j++) {
            for (int layer = 0; layer < 4; layer++) {
                pixels[(RemoveOverflow(i, WIDTH) + RemoveOverflow(j, HEIGHT) * WIDTH) * 4 + layer] = 255 * color;
            }
        }
    }
}


bool isAlive(const sf::Uint8 *pixels, int posx, int posy) {
    return pixels[(posx + posy * WIDTH) * 4] == 255;
}

int getAliveNeighbours(sf::Uint8 *pixels, int posx, int posy) {
    return isAlive(pixels, getPrevPos(posx, WIDTH), getPrevPos(posy, HEIGHT)) +
           isAlive(pixels, getPrevPos(posx, WIDTH), getRealPos(posy)) +
           isAlive(pixels, getPrevPos(posx, WIDTH), getNextPos(posy, HEIGHT)) +
           isAlive(pixels, getRealPos(posx), getPrevPos(posy, HEIGHT)) +
           isAlive(pixels, getRealPos(posx), getNextPos(posy, HEIGHT)) +
           isAlive(pixels, getNextPos(posx, WIDTH), getPrevPos(posy, HEIGHT)) +
           isAlive(pixels, getNextPos(posx, WIDTH), getRealPos(posy)) +
           isAlive(pixels, getNextPos(posx, WIDTH), getNextPos(posy, HEIGHT));
}


sf::Uint8 *iterate(sf::Uint8 *pixels) {
    auto *new_epoch = new sf::Uint8[WIDTH * HEIGHT * 4];
    for (int i = 0; i < WIDTH / SCALE; i++) {
        for (int j = 0; j < HEIGHT / SCALE; j++) {
            int aliveNeighbours = getAliveNeighbours(pixels, i, j);
            if (isAlive(pixels, getRealPos(i), getRealPos(j))) {
                fillPixel(new_epoch, i, j, !(aliveNeighbours < 2 || aliveNeighbours > 3));
            } else {
                fillPixel(new_epoch, i, j, aliveNeighbours == 3);
            }
        }
    }
    delete[] pixels;
    return new_epoch;
}

void redrawWindow(sf::RenderWindow &window, sf::Sprite &sprite, sf::Texture &texture, sf::Uint8 *pixels) {
    texture.update(pixels);
    window.draw(sprite);
    window.display();
}

void startEmulation(sf::RenderWindow &window, sf::Sprite &sprite, sf::Texture &texture, sf::Uint8 *pixels) {
    int speed = 10;
    bool is_paused = true;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Button::Left)
                        fillPixel(pixels, event.mouseButton.x / SCALE, event.mouseButton.y / SCALE, true);
                    else if (event.mouseButton.button == sf::Mouse::Button::Right)
                        fillPixel(pixels, event.mouseButton.x / SCALE, event.mouseButton.y / SCALE, false);
                    redrawWindow(window, sprite, texture, pixels);
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Key::Enter)
                        is_paused = !is_paused;
                    else if (event.key.code == sf::Keyboard::Key::Add)
                        speed = max(speed - 5, 0);
                    else if (event.key.code == sf::Keyboard::Key::Subtract)
                        speed = min(speed + 5, 1000);
                default:
                    break;
            }
        }
        window.clear();
        if (!is_paused) {
            pixels = iterate(pixels);
            redrawWindow(window, sprite, texture, pixels);
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


int main() {
    auto pixels = new sf::Uint8[WIDTH * HEIGHT * 4];
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "A Game of Life");
    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    redrawWindow(window, sprite, texture, pixels);
    startEmulation(window, sprite, texture, pixels);
    return EXIT_SUCCESS;
}