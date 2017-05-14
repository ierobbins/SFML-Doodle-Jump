#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

struct point
{int x,y;} plat[20];

const int SIZE = 10;

void gen_rand_plat();
void check_bounce(int &x, int &y, float &dy);
void scroll(int &y, int &h, float &dy);

int main(){
    srand(time(0));

    RenderWindow window(VideoMode(400, 533), "Doodle Jump!");
    window.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/platform.png");
    t3.loadFromFile("images/doodle.png");

    Sprite sBackground(t1), sPlat(t2), sPers(t3);
    gen_rand_plat();

    int x = 100, y = 100, h = 200;
    float dy = 0;

    while(window.isOpen()){
        Event e;
        while(window.pollEvent(e)){
            if(e.type == Event::Closed)
                window.close();
        } // END EVENT LOOP

        if(Keyboard::isKeyPressed(Keyboard::Right)) x += 3;
        if(Keyboard::isKeyPressed(Keyboard::Left))  x -= 3;

        dy += 0.2; // dy is vertical acceleration
        y += dy;
        if(y > 500)
            dy = -10;

        check_bounce(x, y, dy);

        if(y < h)
            scroll(y, h, dy);

        sPers.setPosition(x, y);

        window.draw(sBackground);
        window.draw(sPers);

        // Draws the platforms on the screen
        for(int i = 0; i < SIZE; i++){
            sPlat.setPosition(plat[i].x, plat[i].y);
            window.draw(sPlat);
        }
        window.display();
    }

    return 0;
}

void gen_rand_plat(){
    for(int i = 0; i < SIZE; i++){
        plat[i].x = std::rand() % 400;
        plat[i].y = std::rand() % 533;
    }
}

// Bounce is initiated when acceleration is downward and doodle is
// touching a platform.
void check_bounce(int &x, int &y, float &dy){
    for(int i = 0; i < SIZE; i++)
        if((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
        && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))
            dy = -10;
}

void scroll(int &y, int &h, float &dy){
    for(int i = 0; i < SIZE; i++){
        y = h; // doodle's y position set to 200

        plat[i].y = plat[i].y - dy; // all platform y values rerender with dy

        // When a platform goes below the view of the screen, it is redrawn at the
        // top of the screen with a random x coordinate.
        if(plat[i].y > 533){
            plat[i].y = 0;
            plat[i].x = std::rand() %400;
        }
    }
}
