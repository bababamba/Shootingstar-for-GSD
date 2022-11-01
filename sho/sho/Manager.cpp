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
#include "zigzag.h"
#include "middle1.h"
#include "Stage_Reader.h"
#include "player.h"
#include "BulletVectorCalculator.h"
using namespace std;

//이거 다 쓰면 너무 길어서 일단 BVC로 줄여 놨는데 걍 바꿔도 됨
typedef BulletVectorCalculator BVC;

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

//게임의 기반을 준비하는 부분
Manager::Manager(const char* title, int xpos, int ypos, int height, int width, int flags) {
    if( SDL_Init(SDL_INIT_EVERYTHING) >= 0 ) {
        //SDL 준비
        window = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        //SDL 텍스처 생성, enemy 텍스처는 각각의 enemy_type에서 생성하므로 제외할 것
        texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("image/recttest.png"));
        bultexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("image/Bullet.png"));
        ebultexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("image/enemy_bullet.png"));
        item_texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("image/item.png"));
        //플레이어 생성
        player* temp_p = new player();
        Plr = temp_p;
        Plr->init();
        //총알 생성
        for( int i = 0; i < 100; i++ ) {
            available_bullets.push(new SDL_Rectf);
            available_bullets.top()->init(-100, -100, 8, 8);
        }
        //적 생성
        //★화면에 최대로 등장하는 적 개수만큼 enemy가 생성되어 있어야 한다, 추후 적 개수가 확정되면 이 주석을 지울 것
        for( int i = 0; i < 10; i++ ) {
            available_enemy.push(new enemy());
        }
        //enemy_type 생성
        srct_basic = new basic(renderer);
        srct_zigzag = new zigzag(renderer);
        srct_middle1 = new middle1(renderer);
        //item 생성
        for( int i = 0; i < 3; i++ ) {
            available_items.push(new SDL_Rectf());
            available_items.top()->init(-100, -100, 64, 64, 0, 1);
        }
        //스테이지 생성 관련
        stage_load();
        //초기화
        init();
    } else {
        cout << "SDL initiation fail" << endl;
    }
}
//Manager::~Manager() { }

Manager* Manager::get_m() { 
    if( !m ) {
        m = new Manager("SDL GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    }
    return m;
}

void Manager::init() { 
    int size;
    //플레이어 초기화
    Plr->init();
    //총알 초기화
    size = enemy_bullets.size();
    for( int i = 0; i < size; i++ ) {
        enemy_bullets[i]->init(-100, -100, 8, 8);
        available_bullets.push(enemy_bullets[i]);
        enemy_bullets.erase(enemy_bullets.begin() + i);
    }
    size = player_bullets.size();
    for( int i = 0; i < size; i++ ) {
        player_bullets[i]->init(-100, -100, 8, 8);
        available_bullets.push(player_bullets[i]);
        enemy_bullets.erase(player_bullets.begin() + i);
    }
    //적 초기화
    size = cur_enemy.size();
    for( int i = 0; i < size; i++ ) {
        cur_enemy[i]->set_type(nullptr);
        cur_enemy[i]->e_sdl.init(-100, -100, 0, 0);
        available_enemy.push(cur_enemy[i]);
        cur_enemy.erase(cur_enemy.begin() + i);
    }
    //item 초기화
    size = cur_items.size();
    for( int i = 0; i < size; i++ ) {
        cur_items[i]->init(-100, -100, 64, 64, 0, 1);
        available_items.push(cur_items[i]);
        cur_items.erase(cur_items.begin() + i);
    }
    //스테이지 생성 관련
    cur_enemy_num = 0;
    is_enemy_generating = true;
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

void Manager::render() {
    int size;
    SDL_Rect temp;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //Black Color
    SDL_RenderClear(renderer);
    //적 출력
    
    size = cur_enemy.size();
    for( int i = 0; i < size; i++ ) {
        temp.x = round(cur_enemy[i]->e_sdl.x);
        temp.y = round(cur_enemy[i]->e_sdl.y);
        temp.w = round(cur_enemy[i]->e_sdl.w);
        temp.h = round(cur_enemy[i]->e_sdl.h);
        SDL_RenderCopy(renderer, cur_enemy[i]->get_type()->get_texture(), NULL, &temp);
    }
    //적 총알 출력
    size = enemy_bullets.size();
    for( int i = 0; i < size; i++ ) {
        temp.x = round(enemy_bullets[i]->x);
        temp.y = round(enemy_bullets[i]->y);
        temp.w = round(enemy_bullets[i]->w);
        temp.h = round(enemy_bullets[i]->h);
        SDL_RenderCopy(renderer, ebultexture, NULL, &temp);
    }
    //플레이어 총알 출력
    size = player_bullets.size();
    for( int i = 0; i < size; i++ ) {
        temp.x = round(player_bullets[i]->x);
        temp.y = round(player_bullets[i]->y);
        temp.w = round(player_bullets[i]->w);
        temp.h = round(player_bullets[i]->h);
        SDL_RenderCopy(renderer, bultexture, NULL, &temp);
    }
    //아이템 출력
    size = cur_items.size();
    for( int i = 0; i < size; i++ ) { 
        temp.x = round(cur_items[i]->x);
        temp.y = round(cur_items[i]->y);
        temp.w = round(cur_items[i]->w);
        temp.h = round(cur_items[i]->h);
        SDL_RenderCopy(renderer, item_texture, NULL, &temp);
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

void Manager::bullet_set(const float x, const float y, const float slope_x, const float slope_y,const int speed, bool is_players) { 
    if( available_bullets.size() == 0 ) { 
        cout << "bullet number limitation" << endl;
        return;
    }
    SDL_Rectf* temp = available_bullets.top();
    temp->x = x;
    temp->y = y;
    temp->set_slope(slope_x, slope_y);
    temp->set_speed(speed);

    //★발사 주체의 rect를 아예 받아와서 width, height까지 계산하여 정중앙에서 총알을 생성토록 변경할 것
    if( is_players )
        player_bullets.push_back(temp);
    else
        enemy_bullets.push_back(temp);	//★추후 enemy_bullet 이동이 구현되면 그쪽 벡터로 이관
    available_bullets.pop();
}

void Manager::enemy_set(float x, float y, float slope_x, float slope_y, int enemy_code, bool item) { 
    //available 스택들은 주소값을 저장하도록 되어 있기 떄문에 지역 변수 거치면 오류난다, 메서드가 종료되면 지역 변수가 할당 해제되면서 그 주소값이 버려지니까
    if( available_enemy.size() == 0 ) {
        cout << "enemy number limitation" << endl;
        return;
    }
    cur_enemy.push_back(available_enemy.top());
    cur_enemy.back()->e_sdl.x = x;
    cur_enemy.back()->e_sdl.y = y;
    cur_enemy.back()->e_sdl.set_slope(slope_x, slope_y);
    cur_enemy.back()->set_has_item(item);
    switch(enemy_code) { 
        case 1:
            cur_enemy.back()->set_type(srct_basic);
            break;
        case 2:
            cur_enemy.back()->set_type(srct_zigzag);
            break;
        case 3:
            cur_enemy.back()->set_type(srct_middle1);
            break;
    }
    available_enemy.pop();
}

void Manager::item_set(float x, float y) { 
    if( available_items.size() == 0 ) {
        cout << "item number limitation" << endl;
        return;
    }
    cur_items.push_back(available_items.top());
    cur_items.back()->init(x, y, 32, 32, 0, 1);
    available_items.pop();
}

void Manager::stage_load() { 
    //함수 1개 실행이지만 일단 함수에 넣어놨다, 추후 2개 이상의 스테이지를 사용할 경우 이 함수를 확장할 것
    file_parse("stage.txt", &cur_stage);
    assert(cur_stage["stage"].IsArray());
    last_enemy_num = cur_stage["stage"].Size();
    //assert(cur_stage["test1"].IsString());
    //printf( cur_stage["test1"].GetString());
}

//main 메서드를 특정 클래스 내부에 위치하게 하지 말 것
int Manager::amain(int argv, char** args) {   
    int size=0; int size2=0;
    //★게임이 재시작될 때 게임시간 또한 초기화되어야 하지만 SDL의 GetTick은 window를 새로고침하지 않는 이상 초기화할 수 없다, 따라서 run_time에 delta_time을 더한 것을 게임시간으로 사용해 이를 해결한다
    float run_time = 0;
    bool game = true;
    bool running = true;
    bool collision_chk;

    SDL_Event event;
    while (running) {
        current_time = SDL_GetTicks();
        if (current_time-prev_time > 1000 / 60.0) {
            deltaTime = (current_time - prev_time) / 100;
            //★run_time += deltaTime;    
            prev_time = current_time;
            
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
                        if( event.key.keysym.sym == SDLK_r ) {
                            //게임 재시작
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
            if( (dir[0] == true) & (Plr->p_sdl.y > 0) )
                Plr->p_sdl.y -= speed;
            if( (dir[2] == true) & (Plr->p_sdl.y < WINDOW_HEIGHT - Plr->p_sdl.h) )
                Plr->p_sdl.y += speed;
            if( (dir[1] == true) & (Plr->p_sdl.x < WINDOW_WIDTH - Plr->p_sdl.w) )
                Plr->p_sdl.x += speed;
            if( (dir[3] == true) & (Plr->p_sdl.x > 0) )
                Plr->p_sdl.x -= speed;
            //플레이어 공격
            Plr->attack_delay_decrease();
            if( pgun ) { 
                Plr->attack();
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
            //플레이어 총알 이동, 적이 맞았는지 확인
            size = player_bullets.size();
            size2 = cur_enemy.size();
            for( int i = 0; i < size; i++ ) {
                collision_chk = false;
                player_bullets[i]->linear_move();
                for( int j = 0; j < size2; j++ ) {
                    if( rectcolf(*player_bullets[i], cur_enemy[j]->e_sdl) ) {
                        collision_chk = true;
                        if( cur_enemy[j]->hit() ) { 
                            available_enemy.push(cur_enemy[j]);
                            cur_enemy.erase(cur_enemy.begin() + j);
                            j--; size2--;
                        }
                        break;
                    }
                }
                if( player_bullets[i]->is_out() | collision_chk ) {
                    available_bullets.push(player_bullets[i] );
                    player_bullets.erase(player_bullets.begin() + i);
                    i--; size--;
                }
            }
            //적 총알 이동, 플레이어가 맞았는지 확인
            size = enemy_bullets.size();
            for( int i = 0; i < size; i++ ) {
                enemy_bullets[i]->linear_move();
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
            //아이템 이동, 플레이어가 획득했는지 확인
            size = cur_items.size();
            for( int i = 0; i < size; i++ ) {
                cur_items[i]->linear_move(1);
                if( cur_items[i]->is_out() | rectcolf( *cur_items[i], Plr->p_sdl ) ) {
                    if( rectcolf(*cur_items[i], Plr->p_sdl) ) { 
                        Plr->increse_attack_level(1);
                    }
                    available_items.push(cur_items[i]);
                    cur_items.erase(cur_items.begin() + i);
                    i--; size--;
                }
            }
            //json Document에 따른 적 생성
            if( is_enemy_generating ){
                if( current_time > cur_stage["stage"][cur_enemy_num][0].GetInt() ) {
                    enemy_set(
                        cur_stage["stage"][cur_enemy_num][1].GetInt(),
                        cur_stage["stage"][cur_enemy_num][2].GetInt(),
                        cur_stage["stage"][cur_enemy_num][3].GetInt(),
                        cur_stage["stage"][cur_enemy_num][4].GetInt(),
                        cur_stage["stage"][cur_enemy_num][5].GetInt(),
                        cur_stage["stage"][cur_enemy_num][6].GetBool()
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

//! @context  도착 지점을 인수로 받는 방향탄 생성 함수
//! @parameter start_x 탄이 발사되는 지점의 x좌표
//! @parameter start_y 탄이 발사되는 지점의 y좌표
//! @parameter end_x 탄이 도착하는 지점의 x좌표
//! @parameter end_y 탄이 도착하는 지점의 y좌표
//! @parameter is_players 탄이 플레이어의 것인지 판별하는 bool 대수
void Manager::directbullet_set_coordinate(const float start_x, const float start_y, const float end_x, const float end_y, const int speed, bool is_players)
{
    //임시 방향 벡터를 생성
    float vx = 0.0f, vy = 0.0f;

    //방향 벡터를 연산
    BVC::InitAimingBullet(end_x, end_y, start_x, start_y, vx, vy);
    
    //bullet_set 호출
    bullet_set(start_x, start_y, vx, vy, speed, is_players);
}

//! @context 발사 각도를 인수로 받는 방향탄 생성 함수. 
//! @parameter start_x 탄이 발사되는 지점의 x좌표
//! @parameter start_y 탄이 발사되는 지점의 y좌표
//! @parameter theta 탄이 발사되는 각도(degree). 양의 x축을 기준으로 시계방향으로 잰다.
//! @parameter is_players 탄이 플레이어의 것인지 판별하는 bool 대수
void Manager::directbullet_set_degree(const float start_x, const float start_y, float theta, const int speed, bool is_players)
{
    //임시 방향 벡터를 생성
    float vx = 0.0f, vy = 0.0f;

    //방향 벡터를 연산
    BVC::InitDirectedBullet(start_x, start_y, vx, vy, theta);

    //bullet_set 호출
    bullet_set(start_x, start_y, vx, vy, speed, is_players);
}

//! @context 원형탄 생성 함수. 
//! @parameter start_x 탄이 발사되는 지점의 x좌표
//! @parameter start_y 탄이 발사되는 지점의 y좌표
//! @parameter n 생성할 원형탄의 개수
//! @parameter odd 홀수 패턴일 때 참.
//! @parameter is_players 탄이 플레이어의 것인지 판별하는 bool 대수
void Manager::circlebullet_set(const float start_x, const float start_y, int n, bool odd, const int speed, bool is_players)
{
    //임시 방향 벡터를 생성
    float* vx = new float[n] {};
    float* vy = new float[n] {};

    //방향 벡터를 연산
    BVC::InitCircleBullets(n, odd, vx, vy);

    //탄환 설정
    for (int i = 0; i < n; i++)
        bullet_set(start_x, start_y, vx[i], vy[i], speed, is_players);

    delete[] vx;
    delete[] vy;
}

//! @context 중심 탄의 방향을 각도로 받는 확산탄 생성 함수. 
//! @parameter start_x 탄이 발사되는 지점의 x좌표
//! @parameter start_y 탄이 발사되는 지점의 y좌표
//! @parameter central_angle 발사할 확산탄의 중심이 되는 탄의 각도(degree). 양의 x축을 기준으로 시계방향으로 잰다.
//! @parameter theta 확산탄 사이의 각도(degree)
//! @parameter n 생성할 탄의 개수
//! @parameter is_players 탄이 플레이어의 것인지 판별하는 bool 대수
void Manager::nwaybullet_set_degree(const float start_x, const float start_y, const float central_angle, const float theta, int n, const int speed, bool is_players)
{
    //임시 기준 방향 벡터를 생성
    float cvx = 0.0f, cvy = 0.0f;
    
    //임시 방향 벡터를 생성
    float* vx = new float[n] {};
    float* vy = new float[n] {};

    //기준 방향 벡터 초기화
    BVC::InitDirectedBullet(start_x, start_y, cvx, cvy, central_angle);

    //기준 방향 벡터를 사용하여 방향 벡터 초기화
    BVC::InitNWayBullets(cvx, cvy, theta, n, vx, vy);

    //탄환 설정
    for (int i = 0; i < n; i++)
        bullet_set(start_x, start_y, vx[i], vy[i], speed, is_players);

    delete[] vx;
    delete[] vy;
}

//! @context 중심 탄의 도착 지점을 인수로 받는 확산탄 생성 함수. 
//! @parameter start_x 탄이 발사되는 지점의 x좌표
//! @parameter start_y 탄이 발사되는 지점의 y좌표
//! @parameter central_angle 발사할 확산탄의 중심이 되는 탄의 각도(degree). 양의 x축을 기준으로 시계방향으로 잰다.
//! @parameter theta 확산탄 사이의 각도(degree)
//! @parameter n 생성할 탄의 개수
//! @parameter is_players 탄이 플레이어의 것인지 판별하는 bool 대수
void Manager::nwaybullet_set_coordinate(const float start_x, const float start_y, const float end_x, const float end_y, float theta, int n, const int speed, bool is_players)
{
    //임시 기준 방향 벡터를 생성
    float cvx = 0.0f, cvy = 0.0f;
    //임시 방향 벡터를 생성
    float* vx = new float[n] {};
    float* vy = new float[n] {};

    //기준 방향 벡터 초기화
    BVC::InitAimingBullet(end_x, end_y, start_x, start_y, cvx, cvy);
    //기준 방향 벡터를 사용하여 방향 벡터 초기화
    BVC::InitNWayBullets(cvx, cvy, theta, n, vx, vy);

    //탄환 설정
    for (int i = 0; i < n; i++)
        bullet_set(start_x, start_y, vx[i], vy[i], speed, is_players);

    delete[] vx;
    delete[] vy;
}

//! @context 중심 탄의 방향 벡터를 받는 확산탄 생성 함수. 
//! @parameter start_x 탄이 발사되는 지점의 x좌표
//! @parameter start_y 탄이 발사되는 지점의 y좌표
//! @parameter central_angle 발사할 확산탄의 중심이 되는 탄의 각도(degree). 양의 x축을 기준으로 시계방향으로 잰다.
//! @parameter theta 확산탄 사이의 각도(degree)
//! @parameter n 생성할 탄의 개수
//! @parameter is_players 탄이 플레이어의 것인지 판별하는 bool 대수
void Manager::nwaybullet_set_slope(const float start_x, const float start_y, const float slope_x, const float slope_y, float theta, int n, const int speed, bool is_players)
{
    //임시 기준 방향 벡터를 생성
    float cvx = 0.0f, cvy = 0.0f;

    //임시 방향 벡터를 생성
    float* vx = new float[n] {};
    float* vy = new float[n] {};

    //인수로 받은 방향 벡터를 사용하여 중앙각 구하기
    float central_angle = BVC::SlopeToDegree(slope_x, slope_y);;

    //기준 방향 벡터 초기화
    BVC::InitDirectedBullet(start_x, start_y, cvx, cvy, central_angle);
    //기준 방향 벡터를 사용하여 방향 벡터 초기화
    BVC::InitNWayBullets(cvx, cvy, theta, n, vx, vy);

    //탄환 설정
    for (int i = 0; i < n; i++)
    {
        bullet_set(start_x, start_y, vx[i], vy[i], speed, is_players);
    }
    delete[] vx;
    delete[] vy;
}
