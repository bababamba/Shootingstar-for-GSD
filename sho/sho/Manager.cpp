#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include "enemy.h"
#include "Manager.h"
#include "SDL_Rectf.h"
#include "basic_enemy.h"
using namespace std;

/*VECTOR AddVector(VECTOR a, VECTOR b) {
    VECTOR c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}*/
/*void VectorNormalize(VECTOR* a) {
    float Length = sqrt((a->x * a->x) + (a->y * a->y));
    a->x /= (Length * 100.0);
    a->y /= (Length * 100.0);
}*/
/*bool Manager::rectcol(const SDL_Rectf a, const SDL_Rectf b) {
    int x1 = a.x;
    int w1 = a.w;
    int y1 = a.y;
    int h1 = a.h;
    int x2 = b.x;
    int w2 = b.w;
    int y2 = b.y;
    int h2 = b.h;
    if (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2) {
        return true;
    }
    return false;
}*/

Manager* Manager::m = NULL;

Manager::Manager() { }
//Manager::~Manager() { }

Manager* Manager::get_m() { 
    if( !m ) {
        m = new Manager();
    }
    return m;
}

bool Manager::rectcolf(SDL_Rectf a, SDL_Rectf b)
{
    float x1 = a.x;
    float w1 = a.w;
    float y1 = a.y;
    float h1 = a.h;
    float x2 = b.x;
    float w2 = b.w;
    float y2 = b.y;
    float h2 = b.h;
    if (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2) {
        return true;
    }
    return false;
}

bool Manager::init(const char* title, int xpos, int ypos, int height, int width, int flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        window = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);

        texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("image/recttest.png"));
        bultexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("image/Bullet.png"));

        //플레이어 위치
        Position.x = WINDOW_WIDTH / 2 - 32;
        Position.y = WINDOW_HEIGHT / 2 - 32;
        Position.w = 64;
        Position.h = 64;
        //총알 초기화
        SDL_Rectf temp;
        for(int i = 0; i < 100; i++) {
            temp.init(-10, -10, 8, 8);
            available_bullets.push(temp);
        }
        //적 초기화
        //★화면에 최대로 등장하는 적 개수만큼 enemy가 생성되어 있어야 한다, 추후 적 개수가 확정되면 이 주석을 지울 것
        for( int i = 0; i < 10; i++ ) {
            available_enemy.push(new enemy());
        }

        //★테스트용 적
        //!!!주의사항, Manager에서 enemy를 저장해두는 collections는 전부 주소값을 저장하도록 되어 있기 떄문에 temp 변수같은 거 거치면 오류난다, 해당 메서드가 종료되면 지역 변수 temp가 할당 해제되면서 그 주소값이 버려지니까
        cur_enemy.push_back(available_enemy.top());
        cur_enemy[0]->set_type(srct_basic);
        cur_enemy[0]->e_sdl.x = 100;
        cur_enemy[0]->e_sdl.y = 100;
        cur_enemy[0]->e_sdl.set_slope(4, 1);
    } else {
        return false;   //SDL 초기화 실패
    }
    return true;
}
void Manager::render() {
    int size;
    SDL_Rect temp;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //Black Color
    SDL_RenderClear(renderer);
    //적 출력
    //★만약 중간 보스, 최종 보스의 크기가 다른 적들과 다르다면 전용 렌더링 과정을 추가해야 한다
    size = cur_enemy.size();
    for( int i = 0; i < size; i++ ) {
        temp.x = round(cur_enemy[i]->e_sdl.x);
        temp.y = round(cur_enemy[i]->e_sdl.y);
        temp.w = round(cur_enemy[i]->e_sdl.w);
        temp.h = round(cur_enemy[i]->e_sdl.h);
        SDL_RenderCopy(renderer, texture, NULL, &temp);
    }
    //적 총알 출력
    size = enemy_bullets.size();
    for( int i = 0; i < size; i++ ) {
        temp.x = round(enemy_bullets[i].x);
        temp.y = round(enemy_bullets[i].y);
        temp.w = round(enemy_bullets[i].w);
        temp.h = round(enemy_bullets[i].h);
        SDL_RenderCopy(renderer, bultexture, NULL, &temp);
    }
    //플레이어 총알 출력
    size = player_bullets.size();
    for( int i = 0; i < size; i++ ) {
        temp.x = round(player_bullets[i].x);
        temp.y = round(player_bullets[i].y);
        temp.w = round(player_bullets[i].w);
        temp.h = round(player_bullets[i].h);
        SDL_RenderCopy(renderer, texture, NULL, &temp);
    }
    //플레이어 출력
    temp.x = round(Position.x);
    temp.y = round(Position.y);
    temp.w = round(Position.w);
    temp.h = round(Position.h);
    SDL_RenderCopy(renderer, texture, NULL, &temp);
    SDL_RenderPresent(renderer);
}

void Manager::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void bullet_set(float x, float y, float slope_x, float slope_y, bool is_players) { 

}

//★main 메서드를 특정 클래스 내부에 위치하게 하지 말 것
int Manager::amain(int argv, char** args) {
    //Manager에서 모든 enemy_type 객체를 1개씩만 가지고 있으며, 이것의 주소값을 enemy.set_type에 넘겨줘서 적을 분화시킨다
    basic temp = basic();
    srct_basic = &temp;

    int size=0; int size2=0;
    bool game = false;
    bool running = false;

    game = init("SDL GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (game) {
        running = true;
    } else {
        cout << "init and game run failed\n";
        return 1;
    }

    SDL_Event event;
    while (running) {
        a = SDL_GetTicks();
        if (a-b > 1000 / 60.0) {
            b = a;
            while( SDL_PollEvent(&event) ) {
                switch( event.type ) {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_KEYDOWN:
                        if( event.key.keysym.sym == SDLK_ESCAPE ) {
                            std::cout << "Window Closing...\n";
                            running = false;
                        }
                        if( event.key.keysym.sym == SDLK_a ) {
                            dir[3] = true;
                        }
                        if( event.key.keysym.sym == SDLK_d ) {
                            dir[1] = true;
                        }
                        if( event.key.keysym.sym == SDLK_w ) {
                            dir[0] = true;
                        }
                        if( event.key.keysym.sym == SDLK_s ) {
                            dir[2] = true;
                        }
                        if( event.key.keysym.sym == SDLK_j ) {
                            pgun = true;
                        }
                        break;
                    case SDL_KEYUP:
                        if( event.key.keysym.sym == SDLK_a ) {
                            dir[3] = false;
                        }
                        if( event.key.keysym.sym == SDLK_d ) {
                            dir[1] = false;
                        }
                        if( event.key.keysym.sym == SDLK_w ) {
                            dir[0] = false;
                        }
                        if( event.key.keysym.sym == SDLK_s ) {
                            dir[2] = false;
                        }
                        if( event.key.keysym.sym == SDLK_j ) {
                            pgun = false;
                        }
                        break;
                }
            }
            //플레이어 이동
            if( dir[0] == true )
                Position.y -= speed;
            if( dir[2] == true )
                Position.y += speed;
            if( dir[1] == true )
                Position.x += speed;
            if( dir[3] == true )
                Position.x -= speed;
            //플레이어 공격
            //★플레이어 클래스가 제작된 이후 그곳으로 이동, 이곳의 if문은 그 메서드를 호출만 할 것
            if( pgun == true && pgundelay == 0 ) {
                SDL_Rectf temp = available_bullets.top();
                temp.x = Position.x;
                temp.y = Position.y;
                temp.set_slope(0, -1);
                player_bullets.push_back(temp);
                pgundelay = 10;
            }
            if( pgundelay > 0 ) {
                pgundelay--;
            }
            //적 이동 및 공격
            //★적 클래스가 구현된 이후 enemy 목록을 돌면서 그 클래스의 공격 메서드 호출
            for( enemy* e : cur_enemy ) { 
                e->move();
                e->fire();
            }
            //플레이어 총알 이동
            size = player_bullets.size();
            for( int i = 0; i < size; i++ ) {
                player_bullets[i].linear_move(8);
                if( player_bullets[i].is_out() ) {
                    player_bullets[i].x = -10;
                    available_bullets.push(player_bullets[i]);
                    player_bullets.erase(player_bullets.begin() + i);
                    size--;
                }
            }
            /*
            //플레이어 총알과 적 충돌 판정
            size2 = cur_enemy.size();
            for( int i = 0; i < size; i++ ) {
                for( int j = 0; j < size2; j++ ) {
                    if( rectcolf(player_bullets[i], cur_enemy[j].e_sdl) ) {
                        player_bullets[i].x = -10;
                        available_bullets.push(player_bullets[i]);
                        player_bullets.erase(player_bullets.begin() + i);
                        //★cur_enemy[j]의 피격 처리
                    }
                }
            }
            //적 총알 이동
            size = enemy_bullets.size();
            for( int i = 0; i < size; i++ ) {
                enemy_bullets[i].linear_move(8);
                if( enemy_bullets[i].is_out() ) {
                    enemy_bullets[i].x = -10;
                    available_bullets.push(enemy_bullets[i]);
                    enemy_bullets.erase(enemy_bullets.begin() + i);
                }
            }
            //적 총알과 플레이어의 충돌 판정
            for( int i = 0; i < size; i++ ) {
                if( rectcolf(enemy_bullets[i], Position) ) {
                    enemy_bullets[i].x = -10;
                    available_bullets.push(enemy_bullets[i]);
                    enemy_bullets.erase(enemy_bullets.begin() + i);
                    //★플레이어 폭파 처리
                }
            }*/
            render();//그래픽 렌더링

        }
    }
    close();
    return 0;
}