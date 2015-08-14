#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ghosts.h";

Ghosts::Ghosts(){
	;
}
Ghosts::Ghosts(char m, char n, sf::Sprite spr, float x, float y){
	mode = m;
	name = n;
	sprite = spr;
	speed = 0.019;
	column = x;
	row = y;

}

//mode get and set
char Ghosts::getMode(){
	return mode;
}
void Ghosts::setMode(char m){
	mode = m;
}

//reverse direction
void Ghosts::reverse(char dir){
	if (direction == 'l'){
		dir = 'r';
	}
	if (direction == 'r'){
		dir = 'l';
	}
	if (direction == 'u'){
		dir = 'd';
	}
	if (direction == 'd'){
		dir = 'u';
	}
}

//direction get and set
char Ghosts::getDirection(){
	return direction;
}
void Ghosts::setDirection(char d){
	direction = d;
}

//name get and set
char Ghosts::getName(){
	return name;
}
void Ghosts::setName(char n){
	name = n;
}

//sprite get and set
sf::Sprite Ghosts::getSprite(){
	return sprite;
}
void Ghosts::setSprite(sf::Sprite spr){
	sprite = spr;
}

//speed get and set
float Ghosts::getSpeed(){
	return speed;
}
void Ghosts::setSpeed(float s){
	speed = s;
}

void Ghosts::frightenGhost(sf::IntRect f){ 
	mode = 'f';
	reverse(direction);
	//sprite.setTextureRect(f);  //not working
}


//get and set row, column
double Ghosts::getRow(){
	return row;
}
double Ghosts::getCol(){
	return column;
}
void Ghosts::setRow(double r){
	row = r;
}
void Ghosts::setCol(double c){
	column = c;
}
void Ghosts::setPos(double r, double c){
	row = r;
	column = c;
}

/*
void Ghosts::resetGhost(){ //not working
	if (name == 'b') {
		sprite.setPosition(20 * 8, 20 * 8);
	}
	else if (name == 'i'){
		sprite.setPosition(11.5 * 8, 16.5 * 8);
	}
	else if (name == 'p'){
		sprite.setPosition(13.5 * 8, 17 * 8);
	}
	else if (name == 'c'){
		sprite.setPosition(15.5 * 8, 16.5 * 8);
	}
		row = 14;
		column = 14;
		mode = 'h';
}
*/
