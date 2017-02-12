//
// Created by Herman Karlsson on 2017-02-11.
//

#ifndef POKEMON_SIMULATION_POKEMON_H
#define POKEMON_SIMULATION_POKEMON_H
#include <random>
#include "util.h"

/*
 * types:
 * 0: normal
 * 1: fire
 * 2: water
 * 3: electric
 * 4: grass
 * 5: ice
 * 6: fighting
 * 7: poison
 * 8: ground
 * 9: flying
 * 10: psychic
 * 11: bug
 * 12: rock
 * 13: ghost
 * 14: dragon
 * 15: dark
 * 16: steel
 * 17: fairy
 */

class pokemon {
private:
	double hp, atk, def, spd, hp_start;
	int type;
	//std::mt19937 rng;

public:
	void generate(std::mt19937 &);

	void fight(pokemon &);

	void atk_change(double);

	void damage(double);

	double weakness(pokemon&);

	double health();

	double hpmax();

	double speed();

	double attack();

	double defence();

	int get_type();

	void heal(int);

};

void pokemon::generate(std::mt19937 &rng) {

	static std::binomial_distribution<double> distribution(239);
	static std::uniform_int_distribution<int> typedist(0,17);

	//this->rng = rng;

	this->hp    = 16+distribution(rng);
	this->atk   = 16+distribution(rng);
	this->def   = 16+distribution(rng);
	this->spd   = 16+distribution(rng);

	this->type  = typedist(rng);

	this->hp_start = this->hp;

}

void pokemon::damage(double dam) {

	this->hp -= dam;

}

void pokemon::fight(pokemon & opp) {

	double atk = this->attack();
	double def = opp.defence();
	double mod = type_diff(this->get_type(),opp.get_type());

	//static std::uniform_real_distribution<double> dist(0.85,1);

	double ran = 1;//dist(this->rng);

	opp.damage(std::max(0.0,(420*atk/def/50+2)*1.25*mod*ran));

	//this->atk_change(1);
	//opp.atk_change(-1);

}

void pokemon::atk_change(double delta) {
		this->atk += delta;
}

double pokemon::weakness(pokemon &opp) {


	double atk = this->attack();
	double def = opp.defence();
	double mod = type_diff(this->get_type(),opp.get_type());

	return std::max(0.0,this->health()-(420*atk/def/50+2)*1.25*mod);


	//return std::max(0.0,this->health()-int((pkmn.attack()-this->defence()/2)*type_diff(pkmn.get_type(),this->get_type())));

}

double pokemon::health() {
	return this->hp;
}

double pokemon::speed() {
	return this->spd;
}

double pokemon::attack() {
	return this->atk;
}

double pokemon::defence() {
	return this->def;
}

double pokemon::hpmax() {
	return this->hp_start;
}

int pokemon::get_type() {
	return this->type;
}

void pokemon::heal(int delta = 10000) {
	this->hp = std::min(this->hp_start,this->hp + delta);
}
#endif //POKEMON_SIMULATION_POKEMON_H
