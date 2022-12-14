#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include "Bullet.h"
#include "enemy.h"
#include "Manager.h"
#include "SDL_Rectf.h"
#include "basic_enemy.h"
#include "zigzag.h"
#include "charger.h"
#include "middle1.h"
#include "BEEG.h"
#include "fixed_enemy.h"
#include "boss1.h"
#include "boss1_base.h"
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
        back_texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("image/background1.png"));
        title_texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("image/sho_title.png"));
        tutorial_texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("image/sho_tutorial.png"));
        gameover_texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("image/sho_gameover.png"));
        clear_texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("image/sho_clear.png"));
        //플레이어 생성
        player* temp_p = new player();
        Plr = temp_p;
        Plr->init();
        Plr->SetTexture(texture);
        //총알 생성
        for( int i = 0; i < 500; i++ ) {
            available_bullets.push(new Bullet);
            available_bullets.top()->init(-100, -100, 8, 8);
        }
        //적 생성
        //★화면에 최대로 등장하는 적 개수만큼 enemy가 생성되어 있어야 한다, 추후 적 개수가 확정되면 이 주석을 지울 것
        for( int i = 0; i < 15; i++ ) {
            available_enemy.push(new enemy());
        }
        //enemy_type 생성
        srct_basic = new basic(renderer);
        srct_zigzag = new zigzag(renderer);
        srct_charger = new charger(renderer);
        srct_middle1 = new middle1(renderer);
        srct_BEEG = new BEEG(renderer);
        srct_fixed = new Fixed(renderer);
        boss1instance = new Boss1(renderer);
        boss1instance->set_type(new boss1_base(renderer));
        //item 생성
        for( int i = 0; i < 3; i++ ) {
            available_items.push(new SDL_Rectf());
            available_items.top()->init(-100, -100, 64, 64, 0, 1);
            available_items.top()->set_speed(235);
        }
        //배경 생성
        for( int i = 2; i < 7; i++ ) { 
            background.push_back(new SDL_Rectf());
            background.back()->init(120 * (i-1), (i * i % 10) * 90, 8, 8, 0, 1);
            background.back()->set_speed((i * 77) % 60);
        }
        //텍스트 생성
            // 0=title
        text.push_back(new SDL_Rectf());
        text.back()->init(0, 1000, 720, 180, 0, 1);
        text.back()->set_speed(60);
            // 1=tutorial
        text.push_back(new SDL_Rectf());
        text.back()->init(0, 1000, 720, 180, 0, 1);
        text.back()->set_speed(60);
            // 2=gameover
        text.push_back(new SDL_Rectf());
        text.back()->init(0, 1000, 720, 240, 0, 0);
        text.back()->set_speed(0);
            // 3=clear
        text.push_back(new SDL_Rectf());
        text.back()->init(0, 1000, 720, 190, 0, 0);
        text.back()->set_speed(0);        
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
        //enemy_bullets[i]->SetTexture(ebultexture);
        available_bullets.push(enemy_bullets[i]);
        enemy_bullets.erase(enemy_bullets.begin() + i);
        i--; size--;
    }
    size = player_bullets.size();
    for( int i = 0; i < size; i++ ) {
        player_bullets[i]->init(-100, -100, 8, 8);
        //player_bullets[i]->SetTexture(bultexture);
        available_bullets.push(player_bullets[i]);
        player_bullets.erase(player_bullets.begin() + i);
        i--; size--;
    }
    //적 초기화
    size = cur_enemy.size();
    for( int i = 0; i < size; i++ ) {
        cur_enemy[i]->set_type(nullptr);
        cur_enemy[i]->e_sdl.init(-100, -100, 0, 0);
        available_enemy.push(cur_enemy[i]);
        cur_enemy.erase(cur_enemy.begin() + i);
        i--; size--;
    }
    //item 초기화
    size = cur_items.size();
    for( int i = 0; i < size; i++ ) {
        cur_items[i]->init(-100, -100, 64, 64, 0, 1);
        available_items.push(cur_items[i]);
        cur_items.erase(cur_items.begin() + i);
        i--; size--;
    }
    //텍스트 초기화
    text[0]->y = 240;
    text[1]->y = 0;
    text[2]->y = 1000;
    text[3]->y = 1000;
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
    //배경 출력, 먼저 출력된 물체가 뒤쪽에 렌더링된다
    size = background.size();
    for( int i = 0; i < size; i++ ) { 
        temp.x = round(background[i]->x);
        temp.y = round(background[i]->y);
        temp.w = round(background[i]->w);
        temp.h = round(background[i]->h);
        SDL_RenderCopy(renderer, back_texture, NULL, &temp);
    }
    //텍스트 출력
    size = text.size();
    SDL_Texture* temp_texture = nullptr;
    for( int i = 0; i < size; i++ ) { 
        temp.x = round(text[i]->x);
        temp.y = round(text[i]->y);
        temp.w = round(text[i]->w);
        temp.h = round(text[i]->h);
        switch( i ) {
            case 0:
                temp_texture = title_texture; break;
            case 1:
                temp_texture = tutorial_texture; break;
            case 2:
                temp_texture = gameover_texture; break;
            case 3:
                temp_texture = clear_texture; break;
        }
        SDL_RenderCopy(renderer, temp_texture, NULL, &temp);
    }
    //적 출력
    size = cur_enemy.size();
    for( int i = 0; i < size; i++ ) {
        cur_enemy[i]->render();
    }
    //보스 출력
    if (boss1battle)
        boss1instance->render();
    //적 총알 출력
    size = enemy_bullets.size();
    for( int i = 0; i < size; i++ ) {
        enemy_bullets[i]->render();
    }
    //플레이어 총알 출력
    size = player_bullets.size();
    for( int i = 0; i < size; i++ ) {
        player_bullets[i]->render();
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
    Plr->render();
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
    Bullet* temp = available_bullets.top();
    temp->b_sdl.x = x;
    temp->b_sdl.y = y;
    temp->b_sdl.set_slope(slope_x, slope_y);
    temp->b_sdl.set_speed(speed);

    if (is_players)
    {
        temp->SetTexture(bultexture);
        player_bullets.push_back(temp);
    }
    else {
        temp->SetTexture(ebultexture);
        enemy_bullets.push_back(temp);
    }
    available_bullets.pop();
}

void Manager::enemy_set(float x, float y, float slope_x, float slope_y, int enemy_code, bool item) { 
    //available 스택들은 주소값을 저장하도록 되어 있기 떄문에 지역 변수 거치면 오류난다, 메서드가 종료되면 지역 변수가 할당 해제되면서 그 주소값이 버려지니까
    if( available_enemy.size() == 0 ) {
        cout << "enemy number limitation" << endl;
        return;
    }
    cur_enemy.push_back(available_enemy.top());
    switch( enemy_code ) {
        case 1:
            cur_enemy.back()->set_type(srct_basic);
            break;
        case 2:
            cur_enemy.back()->set_type(srct_zigzag);
            break;
        case 3:
            cur_enemy.back()->set_type(srct_charger);
            break;
        case 4:
            cur_enemy.back()->set_type(srct_middle1);
            break;
        case 6:
            cur_enemy.back()->set_type(srct_BEEG);
            break;
        case 7:
            cur_enemy.back()->set_type(srct_fixed);
            break;
    }    
    cur_enemy.back()->e_sdl.x = x - cur_enemy.back()->get_type()->get_wh()[0] / 2;
    cur_enemy.back()->e_sdl.y = y - cur_enemy.back()->get_type()->get_wh()[1] / 2;
    cur_enemy.back()->e_sdl.set_slope(slope_x, slope_y);
    cur_enemy.back()->set_has_item(item);
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

void Manager::show_text(int ind) { 
    for( int i = 0; i < 4; i++ ) { 
        if( i == ind )
            text[i]->y = 480;
        else
            text[i]->y = 1000;
    }
}

player& Manager::getPlayer() {
    return *Plr;
}

void Manager::stage_load() { 
    //함수 1개 실행이지만 일단 함수에 넣어놨다, 추후 2개 이상의 스테이지를 사용할 경우 이 함수를 확장할 것
    file_parse("stage.txt", &cur_stage);
    assert(cur_stage["stage"].IsArray());
    last_enemy_num = cur_stage["stage"].Size();
    /*
    assert(cur_stage["test"].IsArray());
    last_enemy_num = cur_stage["test"].Size();
    */
}

//main 메서드를 특정 클래스 내부에 위치하게 하지 말 것
int Manager::amain(int argv, char** args) {   
    int size=0; int size2=0;
    float run_time = 0;
    bool game = true;
    bool running = true;
    bool collision_chk;

    SDL_Event event;
    while (running) {
        current_time = SDL_GetTicks();
        if (current_time-prev_time > 1000 / 60.0) {
            deltaTime = (current_time - prev_time) / 1000.0;
            run_time += deltaTime;    
            prev_time = current_time;
            //배경 이동
            size = background.size();
            for( SDL_Rectf* s : background ) { 
                s->linear_move();
                if( s->is_out() ) { 
                    s->y = -10;
                    s->speed = (s->speed + 14) % 40;
                }
            }
            //텍스트 이동, 0번 타이틀/1번 튜토리얼만 화면 내에 있는 동안 이동한다
            if( text[0]->y < 960 )
                text[0]->linear_move();
            if( text[1]->y < 960 )
                text[1]->linear_move();
            //플레이어 입력
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
                            init();
                            run_time = 0;
                            game = true;
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
            if( game ) {
                size = cur_enemy.size();
                for( int i = 0; i < size; i++ ) { 
                    if( game & rectcolf(cur_enemy[i]->e_sdl, Plr->p_sdl) ) {
                        Plr->die();
                        game = false;
                    }
                }
                float PLAYER_TEMP_X = 0, PLAYER_TEMP_Y = 0;
                if( (dir[0] == true) & (Plr->p_sdl.y > 0) )
                    PLAYER_TEMP_Y -= 1;
                if( (dir[2] == true) & (Plr->p_sdl.y < WINDOW_HEIGHT - Plr->p_sdl.h) )
                    PLAYER_TEMP_Y += 1;
                if( (dir[1] == true) & (Plr->p_sdl.x < WINDOW_WIDTH - Plr->p_sdl.w) )
                    PLAYER_TEMP_X += 1;
                if( (dir[3] == true) & (Plr->p_sdl.x > 0) )
                    PLAYER_TEMP_X -= 1;
                
                if ((PLAYER_TEMP_X != 0) && (PLAYER_TEMP_Y != 0))
                {
                    PLAYER_TEMP_X /= sqrt(2);
                    PLAYER_TEMP_Y /= sqrt(2);
                }

                Plr->p_sdl.x += speed * deltaTime * PLAYER_TEMP_X;
                Plr->p_sdl.y += speed * deltaTime * PLAYER_TEMP_Y;
            }
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
                    cur_enemy[i]->die();
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
                player_bullets[i]->move();
                for( int j = 0; j < size2; j++ ) {
                    if( rectcolf(player_bullets[i]->getCollisonRectf(), cur_enemy[j]->getCollisonRectf()) ) {
                        collision_chk = true;
                        if( cur_enemy[j]->hit() ) { 
                            available_enemy.push(cur_enemy[j]);
                            cur_enemy.erase(cur_enemy.begin() + j);
                            j--; size2--;
                        }
                        break;
                    }
                }
                if( player_bullets[i]->b_sdl.is_out() | collision_chk ) {
                    available_bullets.push(player_bullets[i] );
                    player_bullets.erase(player_bullets.begin() + i);
                    i--; size--;
                }
            }
            //첫스테이지 보스전 처리
            if (boss1battle) {
                //is_enemy_generating = false;
                //보스 이동, 발사 처리
                boss1instance->move();
                if( !boss1instance->permit_fire && boss1instance->e_sdl.y > 99 ) boss1instance->permit_fire = true;
                boss1instance->fire();
                collision_chk = false;
                size = player_bullets.size();

                for (int i = 0; i < size; i++) {
                    if (boss1instance->CollisionTest(player_bullets[i]->getCollisonRectf())) {
                        available_bullets.push(player_bullets[i]);
                        player_bullets.erase(player_bullets.begin() + i);
                        i--; size--;
                        collision_chk = true;
                    }
                }

                //클리어 처리
                if (collision_chk && boss1instance->hit())
                {
                    //보스 처치 시(=클리어 시) 처리를 여기서 하면 됨
                }
            }

            //적 총알 이동, 플레이어가 맞았는지 확인
            size = enemy_bullets.size();
            for( int i = 0; i < size; i++ ) {
                enemy_bullets[i]->move();
                if( enemy_bullets[i]->b_sdl.is_out() | rectcolf(Plr->getCollisonRectf() , enemy_bullets[i]->getCollisonRectf()) ) {
                    if( game & rectcolf(Plr->getCollisonRectf(),enemy_bullets[i]->getCollisonRectf()) ) {
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
                cur_items[i]->linear_move();
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
                if( run_time > cur_stage["stage"][cur_enemy_num][0].GetFloat() ) {
                    enemy_set(
                        cur_stage["stage"][cur_enemy_num][1].GetInt(),
                        cur_stage["stage"][cur_enemy_num][2].GetInt(),
                        cur_stage["stage"][cur_enemy_num][3].GetInt(),
                        cur_stage["stage"][cur_enemy_num][4].GetInt(),
                        cur_stage["stage"][cur_enemy_num][5].GetInt(),
                        cur_stage["stage"][cur_enemy_num][6].GetBool()
                    );
                    /*
                    enemy_set(
                        cur_stage["test"][cur_enemy_num][1].GetInt(),
                        cur_stage["test"][cur_enemy_num][2].GetInt(),
                        cur_stage["test"][cur_enemy_num][3].GetInt(),
                        cur_stage["test"][cur_enemy_num][4].GetInt(),
                        cur_stage["test"][cur_enemy_num][5].GetInt(),
                        cur_stage["test"][cur_enemy_num][6].GetBool()
                    );
                    */
                    cur_enemy_num++;
                    if( cur_enemy_num >= last_enemy_num ) {
                        boss1battle = true;
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
