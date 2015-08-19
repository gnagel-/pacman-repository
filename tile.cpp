
#include "tile.h";
#include <SFML/Graphics.hpp>

//create a tile
Tile::Tile(double x, double y, char contains, sf::Sprite spr){
	xpos = x;
	ypos = y;
	type = contains;
	sprite = spr;
}
Tile::Tile(){
	;
}

//set content type and sprite
void Tile::setTile(char item, sf::Sprite spr){
	type = item;
	sprite = spr;
}
void Tile::setType(char item){
	type = item;
}


//remove dot, increment score
void Tile::eatenTile(){
	;
}

//get sprite
sf::Sprite Tile::getSprite(){
	return sprite;
}
//set sprite
void Tile::setSprite(sf::Sprite spr){
	sprite = spr;
}

//get type
char Tile::getType(){
	return type;
}

/*
char Tile::checkTile(int tileX, int TileY){
	;
}
char checkTile(char t){
	;
}
*/


//set up map
void Tile::resetMap(int xval, int yval){
	//game map is 224 x 288
	//28 x 36 tiles, 8 pixels square
	int rows = 28;
	int cols = 36;
	//Tile tileArray[28][36];

	//start with topmost row of dots, move down row by row
	//row 1
	if (xval == 4){
		if ((yval > 0 && yval < 13) || (yval>14 && yval < 27)){
			type = 'd';
		}
	}
	//row 2
	else if (xval == 5){
		if ((yval == 1) || (yval == 6) || (yval == 12) || (yval == 15) || (yval == 21) || (yval == 26)){
			type = 'd';
		}
	}
	//row 3
	else if (xval == 6){
		if ((yval == 6) || (yval == 12) || (yval == 15) || (yval == 21)){
			type = 'd';
		}
		if ((yval == 1) || (yval == 26)){
			type = 'u';
		}
	}
	//row 4
	else if (xval == 7){
		if ((yval == 1) || (yval == 6) || (yval == 12) || (yval == 15) || (yval == 21) || (yval == 26)){
			type = 'd';
		}
	}
	//row 5
	else if (xval == 8){
		if ((yval > 0) && (yval < 27)){
			type = 'd';
		}
	}
	//row 6
	else if (xval == 9){
		if ((yval == 1) || (yval == 6) || (yval == 9) || (yval == 18) || (yval == 21) || (yval == 26)){

			type = 'd';
		}
	}
	//row 7
	else if (xval == 10){
		if ((yval == 1) || (yval == 6) || (yval == 9) || (yval == 18) || (yval == 21) || (yval == 26)){
			type = 'd';
		}
		
	}
	//row 8
	else if (xval == 11){
		if ((yval != 0) && (yval != 7) && (yval != 8) && (yval != 13) && (yval != 14) && (yval != 19) && (yval != 20) && (yval != 27)){
			type = 'd';
		}
		if (yval == 12 || yval == 15){
			type = 'e';
		}
	}
	//row 9
	else if (xval == 12){
		if ((yval == 6) || (yval == 21)){
			type = 'd';
		}
		if (yval == 12 || yval == 15){
			type = 'e';
		}
	}
	//rows 10 - 19
	else if ((xval == 13) || (xval == 14) || (xval == 15) || (xval == 16) || (xval == 17) || (xval == 18)
		|| (xval == 19) || (xval == 20) || (xval == 21) || (xval == 22)){
		if ((yval == 6) || (yval == 21)){
			type = 'd';
		}
		if (xval == 13 && (yval == 12 || yval == 15)){ //row 10
			type = 'e';
		}
		if (xval == 14 && (yval >8 && yval < 19)){ //row 11
			type = 'e';
		}
		if ((xval == 15 || xval == 16) && (yval == 9 || yval == 18)){ //rows 12, 13
			type = 'e';
		}
		if ((xval == 17) && (yval<10 || yval >17)){
			/*(yval < 6 || yval == 7 || yval == 8 || yval == 9 || yval == 18 || yval ==19 
			|| yval==20 || yval>21)){ //row 14*/
			type = 'e';
			if ((xval == 17) && (yval == 6 || yval == 21)){
				type = 'd';
			}
		}
		if ((xval == 18 || xval == 19) && (yval == 9 || yval == 18)){ //rows 14, 15
			type = 'e';
		}
		if ((xval == 20) && (yval > 8 && yval < 19)){ //row 16
			type = 'e';
		}
		if ((xval == 21 || xval == 22) && (yval == 9 || yval == 18)){ //rows 17, 18
			type = 'e';
		}
	}
	//row 20
	else if (xval == 23){
		if ((yval != 0) && (yval != 13) && (yval != 14) && (yval != 27)){
			type = 'd';
		}
	}
	//row 21
	else if (xval == 24){
		if ((yval == 1) || (yval == 6) || (yval == 12) || (yval == 15) || (yval == 21) || (yval == 26)){
			type = 'd';
		}
	}
	//row 22
	else if (xval == 25){
		if ((yval == 1) || (yval == 6) || (yval == 12) || (yval == 15) || (yval == 21) || (yval == 26)){
			type = 'd';
		}
	}
	//row 23
	else if (xval == 26){
		if ((yval != 0) && (yval != 1) && (yval != 4) && (yval != 5) && (yval != 13)
			&& (yval != 14) && (yval != 22) && (yval != 23) && (yval != 26) && (yval != 27)){
			type = 'd';
		}
		if ((yval == 1) || (yval == 26)){
			type = 'u';
		}
		if (yval == 13 || yval == 14){
			type = 'e';
		}
	}
	//rows 24, 25
	else if (xval == 27 || xval == 28){
		if ((yval == 3) || (yval == 6) || (yval == 9) || (yval == 18) || (yval == 21) || (yval == 24)){
			type = 'd';
		}
	}
	//row 26
	else if (xval == 29){
		if ((yval != 0) && (yval != 7) && (yval != 8) && (yval != 13) && (yval != 14)
			&& (yval != 19) && (yval != 20) && (yval != 27)){
			type = 'd';
		}
	}
	//rows 27, 28
	else if (xval == 30 || xval == 31){
		if ((yval == 1) || (yval == 12) || (yval == 15) || (yval == 26)){
			type = 'd';
		}
	}
	//row 29
	else if (xval == 32){
		if ((yval != 0) && (yval != 27)){
			type = 'd';
		}
	}
	//rest
	else{
		type = 'w';
	}
}