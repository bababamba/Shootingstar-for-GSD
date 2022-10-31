﻿#include "SDL.h"
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
#include "Stage_Reader.h"
#include "player.h"
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
        //플레이어 생성
        player* temp_p = new player();
        m->Plr = temp_p;
        //Manager에서 모든 enemy_type 객체를 1개씩만 가지고 있으며, 이것의 주소값을 enemy.set_type에 넘겨줘서 적을 분화시킨다
        basic temp1 = basic();
        m->srct_basic = &temp1;
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

        //플레이어 초기화
        Plr->init();
        //총알 초기화
        for(int i = 0; i < 100; i++) {
            available_bullets.push(new SDL_Rectf);
            available_bullets.top()->init(-100, -100, 8, 8);
        }
        //적 초기화
        //★화면에 최대로 등장하는 적 개수만큼 enemy가 생성되어 있어야 한다, 추후 적 개수가 확정되면 이 주석을 지울 것
        for( int i = 0; i < 10; i++ ) {
            available_enemy.push(new enemy());
        }
        //item 초기화
        for( int i = 0; i < 3; i++ ) { 
            available_items.push(new SDL_Rectf());
            available_items.top()->init(-100, -100, 64, 64, 0, 1);
        }
        cur_enemy_num = 0;
        is_enemy_generating = true;

    } else {
        cout << "SDL initiation fail" << endl;
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
        temp.x = round(enemy_bullets[i]->x);
        temp.y = round(enemy_bullets[i]->y);
        temp.w = round(enemy_bullets[i]->w);
        temp.h = round(enemy_bullets[i]->h);
        SDL_RenderCopy(renderer, bultexture, NULL, &temp);
    }
    //플레이어 총알 출력
    size = player_bullets.size();
    for( int i = 0; i < size; i++ ) {
        temp.x = round(player_bullets[i]->x);
        temp.y = round(player_bullets[i]->y);
        temp.w = round(player_bullets[i]->w);
        temp.h = round(player_bullets[i]->h);
        SDL_RenderCopy(renderer, texture, NULL, &temp);
    }
    //플레이어 출력
    temp.x = round(Plr->p_sdl.x);
    temp.y = round(Plr->p_sdl.y);
    temp.w = round(Plr->p_sdl.w);
    temp.h = round(Plr->p_sdl.h);
    SDL_RenderCopy(renderer, texture, NULL, &temp);
    SDL_RenderPresent(renderer);
}

void Manager::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Manager::bullet_set(const float x, const float y, const float slope_x, const float slope_y, bool is_players) { 
    SDL_Rectf* temp = available_bullets.top();
    temp->x = x;
    temp->y = y;
    //★발사 주체의 rect를 아예 받아와서 width, height까지 계산하여 정중앙에서 총알을 생성토록 변경할 것
    temp->set_slope(slope_x, slope_y);
    if( is_players )
        player_bullets.push_back(temp);
    else
        enemy_bullets.push_back(temp);	//★추후 enemy_bullet 이동이 구현되면 그쪽 벡터로 이관
    available_bullets.pop();
}

void Manager::enemy_set(float x, float y, float slope_x, float slope_y, int enemy_code) { 
    //available_enemy는 주소값을 저장하도록 되어 있기 떄문에 temp 변수같은 거 거치면 오류난다, 해당 메서드가 종료되면 지역 변수 temp가 할당 해제되면서 그 주소값이 버려지니까
    cur_enemy.push_back(available_enemy.top());
    cur_enemy.back()->e_sdl.x = x;
    cur_enemy.back()->e_sdl.y = y;
    cur_enemy.back()->e_sdl.set_slope(slope_x, slope_y);
    switch(enemy_code) { 
        case 1:
            cur_enemy.back()->set_type(srct_basic);
            break;
    }
    available_enemy.pop();
}

void Manager::item_set(float x, float y) { 
    SDL_Rectf* temp = available_items.top();
    temp->x = x;
    temp->y = y;
    
}

void Manager::stage_load() { 
    //함수 1개 실행이지만 일단 함수에 넣어놨다, 추후 2개 이상의 스테이지를 사용할 경우 이 함수를 확장할 것
    file_parse("stage.txt", &cur_stage);
    assert(cur_stage["stage"].IsArray());
    last_enemy_num = cur_stage["stage"].Size();
    //assert(cur_stage["test1"].IsString());
    //printf( cur_stage["test1"].GetString());
}

//★main 메서드를 특정 클래스 내부에 위치하게 하지 말 것
int Manager::amain(int argv, char** args) {
    //★
    stage_load();
    
    int size=0; int size2=0;
    bool game = false;
    bool running = false;

    game = init("SDL GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if (game) {
        //cout << "init and game run success\n";
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
                Plr->p_sdl.y -= speed;
            if( dir[2] == true )
                Plr->p_sdl.y += speed;
            if( dir[1] == true )
                Plr->p_sdl.x += speed;
            if( dir[3] == true )
                Plr->p_sdl.x -= speed;
            //플레이어 공격
            //★플레이어 클래스가 제작된 이후 그곳으로 이동, 이곳의 if문은 그 메서드를 호출만 할 것
            if( pgun == true && pgundelay == 0 ) {
                SDL_Rectf* temp = available_bullets.top();
                temp->x = Plr->p_sdl.x;
                temp->y = Plr->p_sdl.y;
                temp->set_slope(0, -1);
                player_bullets.push_back(temp);
                available_bullets.pop();
                pgundelay = 10;
            }
            if( pgundelay > 0 ) {
                pgundelay--;
            }
            //적 이동 및 공격
            size = cur_enemy.size();
            for( int i = 0; i < size; i++ ) {
                cur_enemy[i]->move();
                cur_enemy[i]->fire();
                if( cur_enemy[i]->e_sdl.is_out() ) {
                    cur_enemy[i]->set_type(nullptr);
                    available_enemy.push(cur_enemy[i]);
                    cur_enemy.erase(cur_enemy.begin() + i);
                    i--; size--;
                }
            }
            //플레이어 총알 이동
            size = player_bullets.size();
            for( int i = 0; i < size; i++ ) {
                player_bullets[i]->linear_move(8);
                if( player_bullets[i]->is_out() ) {
                    available_bullets.push(player_bullets[i]);
                    player_bullets.erase(player_bullets.begin() + i);
                    i--; size--;
                }
            }
            //적 총알 이동, 플레이어가 맞았는지 확인
            size = enemy_bullets.size();
            for( int i = 0; i < size; i++ ) {
                enemy_bullets[i]->linear_move(8);
                if( enemy_bullets[i]->is_out() | rectcolf(*enemy_bullets[i], Plr->p_sdl) ) {
                    if( rectcolf(*enemy_bullets[i], Plr->p_sdl) ) {
                        cout << "player is hit by enemy_bullet" << endl;
                        Plr->die();
                        game = false;
                    }
                    available_bullets.push(enemy_bullets[i]);
                    enemy_bullets.erase(enemy_bullets.begin() + i);                    
                    i--; size--;
                }
            }            
            //아이템 이동
            size = cur_items.size();
            for( int i = 0; i < size; i++ ) {
                cur_items[i]->linear_move(1);
                if( cur_items[i]->is_out() ) {
                    available_items.push(cur_items[i]);
                    cur_items.erase(cur_items.begin() + i);
                    i--; size--;
                }
            }
            /*
            //플레이어 총알과 적 충돌 판정
            //★총알 이동 부분에 통합시키기
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
            //적 총알과 플레이어의 충돌 판정
            for( int i = 0; i < size; i++ ) {
                
            }*/
            //json Document에 따른 적 생성
            if( is_enemy_generating ){
                if( a > cur_stage["stage"][cur_enemy_num][0].GetInt() ) {
                    enemy_set(
                        cur_stage["stage"][cur_enemy_num][1].GetInt(),
                        cur_stage["stage"][cur_enemy_num][2].GetInt(),
                        cur_stage["stage"][cur_enemy_num][3].GetInt(),
                        cur_stage["stage"][cur_enemy_num][4].GetInt(),
                        cur_stage["stage"][cur_enemy_num][5].GetInt()
                    );
                    cur_enemy_num++;
                    if( cur_enemy_num >= last_enemy_num ) {
                        is_enemy_generating = false;
                    }
                }
            }

            render();//그래픽 렌더링
        }
    }    
    close();
    return 0;
}