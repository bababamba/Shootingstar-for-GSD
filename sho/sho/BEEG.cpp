#pragma once
#include "SDL_Rectf.h"
#include "enemy_type.h"
#include "Manager.h"
#include "BEEG.h"
#include "enemy.h"
#include "player.h"

BEEG::BEEG(SDL_Renderer* M_renderer) {
	wh[0] = 256;
	wh[1] = 256;
	max_hp = 80;
	speed = 235;
	e_texture = SDL_CreateTextureFromSurface(M_renderer, IMG_Load("image/enemy_basic.png"));
}

void BEEG::move(enemy* enem) {
	if(enem->get_SA_var1() == -1)
	enem->set_SA_var1(2);
	if (enem->e_sdl.x + enem->e_sdl.w >= WINDOW_WIDTH - 104 && enem->get_SA_var1() == 2 ) {
		enem->set_SA_var1(4);
		enem->set_SA_bool(true);
		enem->e_sdl.set_slope(0, 1);
	}
	if (enem->e_sdl.x <= 104 && enem->get_SA_var1() == 3) {
		enem->set_SA_var1(1);
		enem->set_SA_bool(true);
		enem->e_sdl.set_slope(0, -1);
	}
	if (enem->e_sdl.x + enem->e_sdl.w >= WINDOW_WIDTH - 104 && enem->e_sdl.y >= 360 && enem->get_SA_var1() == 4) {
		enem->set_SA_var1(3);
		enem->set_SA_bool(true);
		enem->e_sdl.set_slope(-1, 0);
	}
	if (enem->e_sdl.x <= 104 && enem-> e_sdl.y <= 104 && enem->get_SA_var1() == 1) {
		enem->set_SA_var1(2);
		enem->set_SA_bool(true);
		enem->e_sdl.set_slope(1, 0);
	}
	cout << enem->get_SA_var1() << endl;
	
	
	

}
void BEEG::how_to_fire(enemy* enem) {
	if (enem->get_SA_bool() == true) {
		if (enem->get_SA_var1() == 3) {
			if (enem->get_fire_delay()[0] <= 0) {
				Manager::get_m()->circlebullet_set(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					16, false, 400, false);
				enem->get_fire_delay()[0] = 110;

			}
			if (enem->get_fire_delay()[0] == 100) {
				Manager::get_m()->circlebullet_set(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					15, true, 400, false);
			}
			if (enem->get_fire_delay()[0] == 90) {
				Manager::get_m()->directbullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					200, false
				);
			}
			if (enem->get_fire_delay()[0] == 80) {
				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					15, 5, 400, false);
			}
			if (enem->get_fire_delay()[0] == 70) {
				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					15, 5, 400, false);
			}
			if (enem->get_fire_delay()[0] == 40) {
				Manager::get_m()->directbullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					500, false
				);

			}if (enem->get_fire_delay()[0] == 38) {
				Manager::get_m()->directbullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					450, false
				);

			}
			if (enem->get_fire_delay()[0] == 36) {
				Manager::get_m()->directbullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					400, false
				);

			}
			if (enem->get_fire_delay()[0] == 34) {
				Manager::get_m()->directbullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					350, false
				);

			}
			if (enem->get_fire_delay()[0] == 32) {
				Manager::get_m()->directbullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					300, false
				);

			}if (enem->get_fire_delay()[0] == 30) {
				Manager::get_m()->directbullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					250, false
				);

			}
			if (enem->get_fire_delay()[0] == 28) {
				Manager::get_m()->directbullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					200, false
				);

			}
			if (enem->get_fire_delay()[0] == 1) {
				enem->set_SA_bool(false);
				enem->e_sdl.linear_move(200);

			}
		}
		if (enem->get_SA_var1() == 4) {
			if (enem->get_fire_delay()[0] <= 0) {

				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					15, 5, 250, false);
				enem->get_fire_delay()[0] = 110;
			}
			if (enem->get_fire_delay()[0] == 108) {
				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					15, 5, 300, false);

			}
			if (enem->get_fire_delay()[0] == 106) {
				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					15, 5, 350, false);

			}
			if (enem->get_fire_delay()[0] == 104) {
				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					15, 5, 400, false);
			}
			if (enem->get_fire_delay()[0] == 102) {
				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					15, 5, 450, false);
			}
			if (enem->get_fire_delay()[0] == 100) {
				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					15, 5, 500, false);
			}
			if (enem->get_fire_delay()[0] == 50) {
				Manager::get_m()->directbullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					700, false
				);

			}
			if (enem->get_fire_delay()[0] == 40) {
				Manager::get_m()->directbullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					600, false
				);

			}if (enem->get_fire_delay()[0] == 30) {
				Manager::get_m()->directbullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					500, false
				);

			}
			if (enem->get_fire_delay()[0] == 20) {
				Manager::get_m()->directbullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					400, false
				);

			}
			if (enem->get_fire_delay()[0] == 1) {
				enem->set_SA_bool(false);
				enem->e_sdl.linear_move(200);

			}
		}
		if (enem->get_SA_var1() == 1) {
			if (enem->get_fire_delay()[0] <= 0) {

				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					30, 5, 300, false);
				enem->get_fire_delay()[0] = 110;
			}
			if (enem->get_fire_delay()[0] == 100) {
				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					30, 5, 300, false);

			}
			if (enem->get_fire_delay()[0] == 70) {
				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					30, 5, 400, false);

			}
			if (enem->get_fire_delay()[0] == 60) {
				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					30, 5, 400, false);
			}
			if (enem->get_fire_delay()[0] == 30) {
				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					15, 5, 500, false);
			}
			if (enem->get_fire_delay()[0] == 20) {
				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					30, 5, 500, false);
			}
			if (enem->get_fire_delay()[0] == 10) {
				Manager::get_m()->nwaybullet_set_coordinate(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					Manager::get_m()->get_Plr()->p_sdl.x+28, Manager::get_m()->get_Plr()->p_sdl.y+28,
					15, 5, 500, false);

			}
			
			if (enem->get_fire_delay()[0] == 1) {
				enem->set_SA_bool(false);
				enem->e_sdl.linear_move(200);

			}
		}
		if (enem->get_SA_var1() == 2) {
			if (enem->get_fire_delay()[0] <= 0) {
				Manager::get_m()->circlebullet_set(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					16, false, 300, false);
				enem->get_fire_delay()[0] = 110;

			}
			if (enem->get_fire_delay()[0] == 100) {
				Manager::get_m()->circlebullet_set(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					15, true, 300, false);
			}
			if (enem->get_fire_delay()[0] == 90) {
				Manager::get_m()->circlebullet_set(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					16, false, 300, false);
			}
			if (enem->get_fire_delay()[0] == 70) {
				Manager::get_m()->circlebullet_set(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					15, true, 300, false);
			}
			if (enem->get_fire_delay()[0] == 60) {
				Manager::get_m()->circlebullet_set(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					16, false, 300, false);
			}
			if (enem->get_fire_delay()[0] == 50) {
				Manager::get_m()->circlebullet_set(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					15, true, 300, false);

			}if (enem->get_fire_delay()[0] == 30) {
				Manager::get_m()->circlebullet_set(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					20, false, 500, false);

			}
			if (enem->get_fire_delay()[0] == 20) {
				Manager::get_m()->circlebullet_set(
					enem->e_sdl.x+124, enem->e_sdl.y+124,
					21, true, 500, false);

			}
			
			if (enem->get_fire_delay()[0] == 1) {
				enem->set_SA_bool(false);
				enem->e_sdl.linear_move(200);

			}
		}
	}
	if (enem->get_fire_delay()[0] <= 0) {

		enem->e_sdl.linear_move(200);
	}

}