#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
typedef struct VECTOR
{

    float x, y;

};
typedef struct SDL_Rectf
{

    float x, y;
    float w, h;

};

VECTOR AddVector(VECTOR a, VECTOR b)
{

    VECTOR c;

    c.x = a.x + b.x;
    c.y = a.y + b.y;

    return c;

}

void VectorNormalize(VECTOR* a)
{

    float Length = sqrt((a->x * a->x) + (a->y * a->y));

    a->x /= (Length * 100.0);
    a->y /= (Length * 100.0);

}
bool rectcol(SDL_Rect a, SDL_Rect b)
{
    int x1 = a.x;
    int w1 = a.w;
    int y1 = a.y;
    int h1 = a.h;
    int x2 = b.x;
    int w2 = b.w;
    int y2 = b.y;
    int h2 = b.h;
    if (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2)
    {
        return true;
    }

    return false;
}
bool rectcolf(SDL_Rectf a, SDL_Rectf b)
{
    float x1 = a.x;
    float w1 = a.w;
    float y1 = a.y;
    float h1 = a.h;
    float x2 = b.x;
    float w2 = b.w;
    float y2 = b.y;
    float h2 = b.h;
    if (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2)
    {
        return true;
    }

    return false;
}
bool init(const char* title, int xpos, int ypos, int height, int width, int flas);
void render();
void close();

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* screen = NULL;
SDL_Surface* image = NULL;
SDL_Surface* bulletimg = NULL;
SDL_Texture* texture = NULL;
SDL_Texture* bultexture = NULL;
SDL_Rectf Position;
SDL_Rectf bulletR[20];
SDL_Rectf ebulletR[2000];
SDL_Rectf enemyR[20];
VECTOR eBulV[20];

bool eBulA[2000] = { false };
double eBulVL = 0;
double eBulVX[2000] = { 0 };
double eBulVY[2000] = { 0 };
int i, j;

bool dir[4] = { false , false , false , false };
bool pgun = false;
int speed = 8;
int bulcount = 0;
int pgundelay = 3;

bool eGun[20] = { false };
int eGunDelay[20] = { 0 };
float eBulSpeed = 5;
int eBulCount = 0;
unsigned int a = SDL_GetTicks();
unsigned int b = SDL_GetTicks();
double delta = 0;
bool init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        window = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        image = IMG_Load("image/recttest.png");
        bulletimg = IMG_Load("image/Bullet.png");
        texture = SDL_CreateTextureFromSurface(renderer, image);
        bultexture = SDL_CreateTextureFromSurface(renderer, bulletimg);


       

        Position.x = 320-32;
        Position.y = 240-32;
        Position.w = 64;
        Position.h = 64;
        for(i = 0; i < 20; i++) {
            bulletR[i].x = 20;
            bulletR[i].y = -20;
            bulletR[i].w = 8;
            bulletR[i].h = 8;
            enemyR[i].x = -400;
            enemyR[i].y = 50;
            enemyR[i].w = 64;
            enemyR[i].h = 64;
        }
        for (i = 0; i < 2000; i++) {
            ebulletR[i].x = 20;
            ebulletR[i].y = -20;
            ebulletR[i].w = 8;
            ebulletR[i].h = 8;
        }
        //test
        enemyR[0].x = 300;
    }
    else
    {
        return false; // SDL 초기화 실패
    }
    return true;
}
int main(int argv, char** args)
{
    bool game = false;
    bool running = false;

    game = init("SDL GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (game)
    {
        running = true;
    }
    else
    {
        return 1;
    }

    SDL_Event event;



    while (running)
    {
        a = SDL_GetTicks();
        delta = a - b;

        if (delta > 1000 / 60.0)
        {

            b = a;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        std::cout << "Window Closing...\n";
                        running = false;
                    }
                    if (event.key.keysym.sym == SDLK_a)
                    {
                        dir[3] = true;
                    }
                    if (event.key.keysym.sym == SDLK_d)
                    {
                        dir[1] = true;
                    }
                    if (event.key.keysym.sym == SDLK_w)
                    {
                        dir[0] = true;
                    }
                    if (event.key.keysym.sym == SDLK_s)
                    {
                        dir[2] = true;
                    }
                    if (event.key.keysym.sym == SDLK_j)
                    {
                        pgun = true;
                    }
                    break;
                case SDL_KEYUP:
                    if (event.key.keysym.sym == SDLK_a)
                    {
                        dir[3] = false;
                    }
                    if (event.key.keysym.sym == SDLK_d)
                    {
                        dir[1] = false;
                    }
                    if (event.key.keysym.sym == SDLK_w)
                    {
                        dir[0] = false;
                    }
                    if (event.key.keysym.sym == SDLK_s)
                    {
                        dir[2] = false;
                    }
                    if (event.key.keysym.sym == SDLK_j)
                    {
                        pgun = false;
                    }
                    break;

                }
            }
            //이동
            if (dir[0] == true)
                Position.y -= speed;
            if (dir[2] == true)
                Position.y += speed;
            if (dir[1] == true)
                Position.x += speed;
            if (dir[3] == true)
                Position.x -= speed;
            //공격
            for (i = 0; i < 20; i++)
                bulletR[i].y -= 8;
            if (pgun == true && pgundelay == 0) {
                bulletR[bulcount].x = Position.x;
                bulletR[bulcount].y = Position.y;
                bulcount++;
                pgundelay = 10;
                if (bulcount == 20)
                    bulcount = 0;
            }
            if (pgundelay > 0)
                pgundelay--;
            //적 공격
            for (i = 0; i < 20; i++) {
                if (enemyR[i].x >= 0 && enemyR[i].x <= WINDOW_WIDTH && enemyR[i].y >= 0 && enemyR[i].y <= WINDOW_HEIGHT) {
                    eGun[i] = true;
          
                }
                else
                    eGun[i] = false;
                if (eGun[i] == true) {
                    if (eGunDelay[i] == 0) {
                        ebulletR[eBulCount].x = enemyR[i].x;
                        ebulletR[eBulCount].y = enemyR[i].y;
                        eBulV[i].x = enemyR[i].x - Position.x;
                        eBulV[i].y = enemyR[i].y - Position.y;
                        eBulVL = sqrt((eBulV[i].x * eBulV[i].x) + (eBulV[i].y * eBulV[i].y));
                        eBulVX[eBulCount] = eBulV[i].x / eBulVL;
                        eBulVY[eBulCount] = eBulV[i].y / eBulVL;
                        eGunDelay[i] += 30;
                        
                        eBulA[eBulCount] = true;
                        eBulCount++;
                        if (eBulCount == 2000)
                            eBulCount = 0;
                    }
                    else
                        eGunDelay[i]--;
                }
            }
            







            for (i = 0; i < 20; i++) {
                for (j = 0; j < 20; j++)
                    if (rectcolf(bulletR[i], enemyR[j])) {//내 총알과 적의 충돌 판정
                        bulletR[i].x = -10;

                    }
                
            }
            for (i = 0; i < 2000; i++) {
                if(eBulA[i] == true)
                ebulletR[i].x -= eBulVX[i]* eBulSpeed;
                ebulletR[i].y -= eBulVY[i]* eBulSpeed;
                if (ebulletR[i].x < 0 && ebulletR[i].x > WINDOW_WIDTH && ebulletR[i].y < 0 && ebulletR[i].y > WINDOW_HEIGHT)
                    eBulA[i] = false;
            }
            render();//그래픽 렌더링
        }
        
    }
    close();

    return 0;
}


void render()
{
    SDL_Rect temp;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //Black Color
    SDL_RenderClear(renderer);
    for (i = 0; i < 20; i++) {
        temp.x = round(enemyR[i].x);
        temp.y = round(enemyR[i].y);
        temp.w = round(enemyR[i].w);
        temp.h = round(enemyR[i].h);
        SDL_RenderCopy(renderer, bultexture, NULL, &temp);
        temp.x = round(bulletR[i].x);
        temp.y = round(bulletR[i].y);
        temp.w = round(bulletR[i].w);
        temp.h = round(bulletR[i].h);
        SDL_RenderCopy(renderer, bultexture, NULL, &temp);
    }
    for (i = 0; i < 2000; i++){
        temp.x = round(ebulletR[i].x);
        temp.y = round(ebulletR[i].y);
        temp.w = round(ebulletR[i].w);
        temp.h = round(ebulletR[i].h);
        SDL_RenderCopy(renderer, texture, NULL, &temp);
    }
    temp.x = round(Position.x);
    temp.y = round(Position.y);
    temp.w = round(Position.w);
    temp.h = round(Position.h);
    SDL_RenderCopy(renderer, texture, NULL, &temp);
    SDL_RenderPresent(renderer);
}

void close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}