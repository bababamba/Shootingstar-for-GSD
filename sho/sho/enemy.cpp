#include "enemy.h"

void enemy::fire() { 
	for( int i = 0; i < 4; i++ ) {
		if( fire_delay[i]-- < -10 )
			break;
	}
	e_type->how_to_fire(this);
}

void enemy::move() { 
	e_type->move(this);
}

void enemy::hit() { 
	hp--;
	if( hp < 1 ) { 
		die();
	}
}

void enemy::die() { 
	if( has_item ) { 
		//�ھ����� ����
	}
	//��ȭ�� ������ ġ���, Manager�� bullet �������� �� ����, e_type ���� nullptr�� �ٲ���� �Ѵ�
}

void enemy::set_type(enemy_type* para_type) {
	if( para_type == nullptr ) { 
		e_type = nullptr;
		return;
	}
	for( int i : fire_delay ) {
		i = 5;
	}
	e_type = para_type;
	e_type->init(&e_sdl, &hp);
}