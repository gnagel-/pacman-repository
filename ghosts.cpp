#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

#include "ghosts.h";

Ghosts::Ghosts(){
	;
}
Ghosts::Ghosts(char m, char n, sf::Sprite spr, float r, float c){
	mode = m; //(c)hase, (f)rightened, (s)catter, (h)ouse
	name = n;
	sprite = spr;
	direction = 'l';
	speed = 0.4;//0.019;
	speedAdjust = 0;
	speedInc = 8;
	column = c;
	row = r;

	if (name == 'b'){
		this->setHomeTile(0, 32);
	}
	else if (name == 'i'){
		this->setHomeTile(27, 35);
	}
	else if (name == 'p'){
		this->setHomeTile(0, 2);
	}
	else if (name == 'c'){
		this->setHomeTile(27, 0);
	}

}

void Ghosts::scatterMode(){
	this->setTarget(homeTileRow, homeTileColumn);

}


void Ghosts::move(){
	speedAdjust += speed;

	//up
	if (direction == 'u'){
		sprite.move(0, -speed);
		if (speedAdjust >= speedInc){
			row -= 1;
			speedAdjust = 0;
		}
	}
	//down
	else if (direction == 'd'){
		sprite.move(0, speed);
		if (speedAdjust >= speedInc){
			row += 1;
			speedAdjust = 0;
		}
	}
	//left
	else if (direction == 'l'){
		sprite.move(-speed, 0);
		if (speedAdjust >= speedInc){
			column -= 1;
			speedAdjust = 0;
		}
	}
	//right
	else if (direction == 'r'){
		sprite.move(speed, 0);
		if (speedAdjust >= speedInc){
			column += 1;
			speedAdjust = 0;
		}
	}
}

char Ghosts::chooseDirection(char toTileType){
	char bestDistance = 'l';
	int dist = 0;

	//tile above
	if (toTileType != 'w'){
		dist = distanceCheck(row - 1, column);
		if (dist < bestDistance){
			bestDistance = 'u';
		}
		//tile to left
		dist = distanceCheck(row, column - 1);
		if (dist < bestDistance){
			bestDistance = 'l';
		}
		//tile below
		dist = distanceCheck(row + 1, column);
		if (dist < bestDistance){
			bestDistance = 'd';
		}
		//tile to right
		dist = distanceCheck(row, column + 1);
		if (dist < bestDistance){
			bestDistance = 'r';
		}
	}

	return bestDistance;
	
}

float Ghosts::distanceCheck(int r, int c){
	//distance = sqrt( (x2-x1)^2 - (y2-y1)^2 )
	int x = std::pow(this->getTargetColumn() - c, 2);
	int y = std::pow(this->getTargetRow() - r, 2);
	return std::sqrt(x - y);
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

//row, column get and set 
double Ghosts::getRow(){
	return row;
}
double Ghosts::getColumn(){
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

//home tile get and set
void Ghosts::setHomeTile(int r, int c){
	homeTileRow = r;
	homeTileColumn = c;
}
int Ghosts::getHomeRow(){
	return homeTileRow;
}
int Ghosts::getHomeColumn(){
	return homeTileColumn;
}

//target tile get and set
void Ghosts::setTarget(int r, int c){
	targetTileRow = r;
	targetTileColumn = c;
}
int Ghosts::getTargetRow(){
	return targetTileRow;
}
int Ghosts::getTargetColumn(){
	return targetTileColumn;
}

//mode get and set
char Ghosts::getMode(){
	return mode;
}
void Ghosts::setMode(char m){
	mode = m;
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
float Ghosts::getSpeedAdjust(){
	return this->speedAdjust;
}
float Ghosts::getSpeedInc(){
	return this->speedInc;
}


void Ghosts::frightenGhost(sf::IntRect f){ 
	mode = 'f';
	reverse(direction);
	//sprite.setTextureRect(f);  //not working
}





void Ghosts::resetGhost(){ //not working
	mode = 's';

	if (name == 'b') {
		//sprite.setPosition(13 * 8, 14 * 8); //not working
		this->setPos(14, 13);
	}
	else if (name == 'i'){
		//sprite.setPosition(11.5 * 8, 16.5 * 8);
		this->setPos(17, 12);
	}
	else if (name == 'p'){
		//sprite.setPosition(13.5 * 8, 17 * 8);
		this->setPos(17, 12);
	}
	else if (name == 'c'){
		//sprite.setPosition(15.5 * 8, 16.5 * 8);
		this->setPos(17, 12);
	}

}
