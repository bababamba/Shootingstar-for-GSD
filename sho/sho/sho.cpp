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

class Enemy {
public:
    SDL_Rectf Rect;
    bool GunActive = false;
    int GunDelay;
    int HP = 100;
    VECTOR GunVector = { 0 };

};
class EnemyBullet {
public:
    SDL_Rectf Rect;
    bool Active = false;
    float Speed = 5;
    double VectorLength = 0;
    VECTOR Vecter = { 0 };


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

Enemy enemy[20];
SDL_Rectf ebulletR[2000];
EnemyBullet enemyBullet[2000];
SDL_Rectf enemyR[20];
VECTOR eBulV[20];

bool eBulA[2000] = { false };
double vectorLength = 0;
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

//초기화ㅏㅏㅏㅏㅏ
bool init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        window = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        //이미지
        image = IMG_Load("image/recttest.png");
        bulletimg = IMG_Load("image/Bullet.png");
        texture = SDL_CreateTextureFromSurface(renderer, image);
        bultexture = SDL_CreateTextureFromSurface(renderer, bulletimg);

        //초기값 부여, 생성
        Position.x = 320-32;
        Position.y = 240-32;
        Position.w = 64;
        Position.h = 64;
        for(i = 0; i < 20; i++) {
            bulletR[i].x = 20;
            bulletR[i].y = -20;
            bulletR[i].w = 8;
            bulletR[i].h = 8;
            enemy[i].Rect.x = -400;
            enemy[i].Rect.y = 50;
            enemy[i].Rect.w = 64;
            enemy[i].Rect.h = 64;
        }
        for (i = 0; i < 2000; i++) {
            enemyBullet[i].Rect.x = 20;
            enemyBullet[i].Rect.y = -20;
            enemyBullet[i].Rect.w = 8;
            enemyBullet[i].Rect.h = 8;
        }
        //test
        enemy[0].Rect.x = 300;
        enemy[1].Rect.x = 100;
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

    game = init("ShootingStar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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


    //메인 루프
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
                if (enemy[i].Rect.x >= 0 && enemy[i].Rect.x <= WINDOW_WIDTH && enemy[i].Rect.y >= 0 && enemy[i].Rect.y <= WINDOW_HEIGHT) {
                    enemy[i].GunActive = true;
          
                }
                else
                    enemy[i].GunActive = false;
                if (enemy[i].GunActive == true) {
                    if (enemy[i].GunDelay == 0) {
                        enemyBullet[eBulCount].Rect.x = enemy[i].Rect.x;
                        enemyBullet[eBulCount].Rect.y = enemy[i].Rect.y;
                        enemy[i].GunVector.x = enemy[i].Rect.x - Position.x;
                        enemy[i].GunVector.y = enemy[i].Rect.y - Position.y;
                        vectorLength = sqrt((enemy[i].GunVector.x * enemy[i].GunVector.x) + (enemy[i].GunVector.y * enemy[i].GunVector.y));
                        enemyBullet[eBulCount].Vecter.x = enemy[i].GunVector.x / vectorLength;
                        enemyBullet[eBulCount].Vecter.y = enemy[i].GunVector.y / vectorLength;
                        enemy[i].GunDelay += 30;
                        
                        enemyBullet[eBulCount].Active = true;
                        eBulCount++;
                        if (eBulCount == 2000)
                            eBulCount = 0;
                    }
                    else
                        enemy[i].GunDelay--;
                }
            }
            







            for (i = 0; i < 20; i++) {
                for (j = 0; j < 20; j++)
                    if (rectcolf(bulletR[i], enemy[j].Rect)) {//내 총알과 적의 충돌 판정
                        bulletR[i].x = -10;

                    }
                
            }
            for (i = 0; i < 2000; i++) {
                if(enemyBullet[i].Active == true)
                enemyBullet[i].Rect.x -= enemyBullet[i].Vecter.x * enemyBullet[i].Speed;
                enemyBullet[i].Rect.y -= enemyBullet[i].Vecter.y * enemyBullet[i].Speed;
                if (enemyBullet[i].Rect.x < -50 && enemyBullet[i].Rect.x > WINDOW_WIDTH + 50 && enemyBullet[i].Rect.y < -50 && enemyBullet[i].Rect.y > WINDOW_HEIGHT + 50)
                    enemyBullet[i].Active = false;
            }
            render();//그래픽 렌더링
        }
        
    }
    close();

    return 0;
}

//그래픽
void render()
{
    SDL_Rect temp;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //Black Color
    SDL_RenderClear(renderer);
    for (i = 0; i < 20; i++) {
        temp.x = round(enemy[i].Rect.x);
        temp.y = round(enemy[i].Rect.y);
        temp.w = round(enemy[i].Rect.w);
        temp.h = round(enemy[i].Rect.h);
        SDL_RenderCopy(renderer, bultexture, NULL, &temp);
        temp.x = round(bulletR[i].x);
        temp.y = round(bulletR[i].y);
        temp.w = round(bulletR[i].w);
        temp.h = round(bulletR[i].h);
        SDL_RenderCopy(renderer, bultexture, NULL, &temp);
    }
    for (i = 0; i < 2000; i++){
        temp.x = round(enemyBullet[i].Rect.x);
        temp.y = round(enemyBullet[i].Rect.y);
        temp.w = round(enemyBullet[i].Rect.w);
        temp.h = round(enemyBullet[i].Rect.h);
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