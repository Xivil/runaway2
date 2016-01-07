#pragma once
#include "VECTOR.h"
#include "Model.h"
#include "Task.h"
#include "MATRIX.h"

class Object : public Task, public Model{
public:
	km::Vector3 *position;
	km::Vector3 *unit;
	km::Vector3 *vector;
	km::Vector3 *direction;
	km::Vector3 *rotate;	//	Šp“x‚¾‚¯‚Ç–Ê“|‚È‚Ì‚ÅVector3‚ð‘ã—p
public:
	Object();
	Object(const char* name);
	Object(const Object &obj);
	virtual ~Object();
	Object& operator = (const Object &obj);

	km::Vector3 get_position();
	km::Vector3 get_unit();
	km::Vector3 get_vector();
	km::Vector3 get_direction();
	km::Vector3 get_rotate();
	void set_position(km::Vector3 vec);
	void set_unit(km::Vector3 vec);
	void set_vector(km::Vector3 vec);
	void set_direction(km::Vector3 vec);
	void set_rotate(km::Vector3 vec);

	//void Init() override;
	//void Final() override;
	void Update() override;
	void Draw() override;
};

class Character : public Object{
protected:
	int life;
	unsigned int flag;
public:
	enum flag_state{
		gravity = 1,
	};
	Character();
	Character(const char* name);
	Character(const Character &obj);
	virtual ~Character();

	inline int Character::get_life(){
		return life;
	}

	inline unsigned int Character::get_flag(){
		return flag;
	}

	void set_life(const int life);
	void enable_gravity();
	void disable_gravity();
	
	//void Init() override;
	//void Final() override;
	void Update() override;
	void Draw() override;
	
};

class Player : public Character{
public:
	Player(const char* name);
};

class Enemy : public Character{
public:

};