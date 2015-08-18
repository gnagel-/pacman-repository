#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "player.h";

Player::Player(int r, int c, sf::Sprite spr){
	row = r;
	column = c;
	sprite = spr;
	score = 0;
	speed = 0.1;
	speedAdjust = 0;
	//timePass = 0;
	//animation = 225;
	//bool isDead;
}

void Player::move(){
	if (direction == 'l' && row == 17 && column == 27) wrapHorizontal();
	else if (direction == 'r' && row == 17 && column == 1) wrapHorizontal();
	//up
	else if (direction == 'u'){
		sprite.move(0, -8);
		row -= 1;
	}
	//down
	else if (direction == 'd'){
		sprite.move(0, 8);
		row += 1;
	}
	//left
	else if (direction == 'l'){
		sprite.move(-8, 0);
		column -= 1;
	}
	//right
	else if (direction == 'r'){
		sprite.move(8, 0);
		column += 1;
	}
}
void Player::move(char toType){

	speedAdjust += speed; //reconcile sprite movement/position with map position

	if (direction == 'l' && row == 17 && column <= 1){
		wrapHorizontal();
	}
	else if (direction == 'r' && row == 17 && column >= 26){
		wrapHorizontal();
	}
	else if (toType != 'w'){

		//up
		if (direction == 'u'){
			//sprite.move(0, -8);
			//row -= 1;
			sprite.move(0, -speed);
			if (speedAdjust >= speedInc){
				row -= 1;
				speedAdjust = 0;
			}
		}
		//down
		else if (direction == 'd'){
			//sprite.move(0, 8);
			//row += 1;
			sprite.move(0, speed);
			if (speedAdjust >= speedInc){
				row += 1;
				speedAdjust = 0;
			}
		}
		//left
		else if (direction == 'l'){
			//sprite.move(-8, 0);
			//column -= 1;
			sprite.move(-speed, 0);
			if (speedAdjust >= speedInc){
				column -= 1;
				speedAdjust = 0;
			}
		}
		//right
		else if (direction == 'r'){
			//sprite.move(8, 0);
			//column += 1;
			sprite.move(speed, 0);
			if (speedAdjust >= speedInc){
				column += 1;
				speedAdjust = 0;
			}
		}
	}
}


void Player::wrapHorizontal(){
	if (direction == 'l'){
		sprite.setPosition(27*8, row*8);
		column = 27;
	}
	else if (direction == 'r'){
		sprite.setPosition(8, row * 8);
		column = 1;
	}
		speedAdjust = 0;
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

void Player::setPos(int r, int c){
	row=r;
	column=c;
}

