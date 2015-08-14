#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "player.h";

Player::Player(double x, double y, sf::Sprite spr){
		xpos = x;
		ypos = y;
		sprite = spr;
		score = 0;
}

void Player::move(){
	//up
	if (direction == 'u'){
		sprite.move(0, -8);
		xpos -= 1;
	}
	//down
	else if (direction == 'd'){
		sprite.move(0, 8);
		xpos += 1;
	}
	//left
	else if (direction == 'l'){
		sprite.move(-8, 0);
		ypos -= 1;
	}
	//right
	else if (direction == 'r'){
		sprite.move(8, 0);
		ypos += 1;
	}
}

void Player::wrapHorizontal(){
	if (direction == 'l'){
		sprite.setPosition(27*8, xpos*8);
		ypos = 27;
	}
	if (direction == 'r'){
		sprite.setPosition(8, xpos * 8);
		ypos = 1;
	}
}

//sprite get and set
sf::Sprite Player::getSprite(){
	return sprite;
}
void Player::setSprite(sf::Sprite spr){
	sprite = spr;
}

//score get and set
int Player::getScore(){
	return score;
}
void Player::setScore(int s){
	score = s;
}

//direction get and set
char Player::getDirection(){
	return direction;
}
void Player::setDirection(char dir){
	direction = dir;
}

//get location in tileArray
/*
sf::Vector2f Player::getLocation(){
	return mapLocation;
}
*/

void eatTile(){
	;
}

void Player::setPos(int row, int column){
	xpos = row;
	ypos = column;
}
