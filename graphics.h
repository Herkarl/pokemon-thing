//
// Created by Herman Karlsson on 2017-02-11.
//

#ifndef POKEMON_SIMULATION_GRAPHICS_H
#define POKEMON_SIMULATION_GRAPHICS_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <vector>
#include <string>
#include "state.h"

class graphics {
private:

	sf::RenderWindow statwin;
	sf::RenderWindow window;
	std::vector<std::vector<sf::Uint8 >> colors;
	//sf::Text text;
	int width, height;

public:
	graphics(int,int);

	bool draw(state &);

};

graphics::graphics(int _height, int _width): window(sf::VideoMode((unsigned int) _width, (unsigned int) _height), "Simulation"),
											 statwin(sf::VideoMode(80,303),"Data"){

	std::vector<sf::Uint8> nor = {104,100,80,255};
	std::vector<sf::Uint8> fir = {213,75,15,255};
	std::vector<sf::Uint8> wat = {15,35,213,255};
	std::vector<sf::Uint8> ele = {219,194,30,255};
	std::vector<sf::Uint8> gra = {68,186,72,255};
	std::vector<sf::Uint8> ice = {98,220,216,255};
	std::vector<sf::Uint8> fig = {164,0,0,255};
	std::vector<sf::Uint8> poi = {125,11,166,255};
	std::vector<sf::Uint8> gro = {195,158,57,255};
	std::vector<sf::Uint8> fly = {177,148,229,255};
	std::vector<sf::Uint8> psy = {255,38,176,255};
	std::vector<sf::Uint8> bug = {120,156,58,255};
	std::vector<sf::Uint8> roc = {151,132,36,255};
	std::vector<sf::Uint8> gho = {75,57,81,255};
	std::vector<sf::Uint8> dra = {79,12,235,255};
	std::vector<sf::Uint8> dar = {41,32,5,255};
	std::vector<sf::Uint8> ste = {112,112,112,255};
	std::vector<sf::Uint8> fai = {240,62,246,255};

	colors = {nor,fir,wat,ele,gra,ice,fig,poi,gro,fly,psy,bug,roc,gho,dra,dar,ste,fai};

	this->width = _width;
	this->height = _height;

	this->window.setPosition(sf::Vector2i(120,30));
	this->statwin.setPosition(sf::Vector2i(20,30));

	this->statwin.clear(sf::Color::White);
	this->window.clear(sf::Color::Black);
	
	this->statwin.display();
	this->window.display();
}

bool graphics::draw(state & st) {

	static int frame = 0;

	static std::vector<std::string> types = {"nor","fir","wat","ele","gra","ice","fig","poi","gro","fly","psy","bug","roc","gho","dra","dar","ste","fai"};

	sf::Event event;

	while(this->window.pollEvent(event))
		if(event.type == sf::Event::Closed){
			this->window.close();
			this->statwin.close();
			return 0;			
		}

	while(this->statwin.pollEvent(event))
		if(event.type == sf::Event::Closed){
			this->window.close();
			this->statwin.close();
			return 0;			
		}

	int cnt = 0;
	for(int i = 0; i < 18; ++i) cnt += st.get_count(i) != 0;
	if(cnt == 1) --frame;

	sf::Texture texture;
	texture.create(this->width,this->height);

	sf::Uint8 * pixels = new sf::Uint8[this->width * this->height * 4];

	for(int i = 0; i < this->height; ++i)
		for(int j = 0; j < this->width; ++j)
			for(int k = 0; k < 4; ++k)
				pixels[4 * (i * this->width + j) + k] = this->colors[st.type(i, j)][k];


	texture.update(pixels);

	texture.setSmooth(true);
	
	sf::Sprite sprite;

	sprite.setTexture(texture);

	std::string str = "Frame " + std::to_string(frame)+"\n";

	for(int i = 0; i < 18; ++i)
		str += types[i]+": "+std::to_string(st.get_count(i))+"\n";

	sf::Font font;
	sf::Text text;
	font.loadFromFile("alef/Alef-Regular.ttf");
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::Black);

	this->statwin.clear(sf::Color::White);
	this->window.clear(sf::Color::Black);

	this->statwin.draw(text);
	this->window.draw(sprite);
	
	this->statwin.display();
	this->window.display();

	++frame;

	return 1;
}

#endif //POKEMON_SIMULATION_GRAPHICS_H
