#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include "tile.h"
#include "player.h"

int main(){
	//game map is 224 x 288
	//28 x 36 tiles, 8 pixels square
	int gameWidth = 224;
	int gameHeight = 288;
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "SFML Application");
	int rows = 36;
	int cols = 28;
	Tile tileArray[36][28];

	//background stuff
	//main sprite sheet, textures from this
	sf::Texture spriteSheet;
	spriteSheet.loadFromFile("ARC_Pacman_everything.png");

	//dot sprite
	sf::Sprite dot;
	dot.setTexture(spriteSheet);
	dot.setTextureRect(sf::IntRect(8, 8, 8, 8));
	dot.setOrigin(4, 4);

	//powerup sprite
	sf::Sprite powerup;
	powerup.setTexture(spriteSheet);
	powerup.setTextureRect(sf::IntRect(8, 8 * 3, 8, 8));
	powerup.setOrigin(4, 4);

	//wall sprite for testing
	sf::Sprite wall;
	wall.setTexture(spriteSheet);
	wall.setTextureRect(sf::IntRect(8, 8, 8, 8));
	wall.setColor(sf::Color(0, 255, 0)); // green
	wall.setOrigin(4, 4);

	//set up the map, tiles wall by default
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			tileArray[i][j].resetMap(i, j);
			if (tileArray[i][j].getType() == 'd'){
				tileArray[i][j].setSprite(dot);
			}
			if (tileArray[i][j].getType() == 'u'){
				tileArray[i][j].setSprite(powerup);
			}
			if (tileArray[i][j].getType() == 'e'){
				tileArray[i][j].setSprite(wall);
			}

		}
	}


	//cosmetic background
	sf::Sprite background;
	sf::Texture mazeBackground;
	if (!mazeBackground.loadFromFile("Pac Man Map.png", sf::IntRect(0, 0, 224, 288))) //map section of spritesheet
	{
		printf("unable to load background texture");
	}
	background.setTexture(mazeBackground);
	//background.setPosition(0, (8 * 3)); //leave space for score and lives	
	background.setPosition(-4, 8 * 2.5);

	//player
	sf::Sprite playerSprite;
	playerSprite.setTexture(spriteSheet);
	playerSprite.setTextureRect(sf::IntRect(470, 0, 16, 16));
	playerSprite.setOrigin(sf::Vector2f(8, 8));
	playerSprite.setPosition(3 * 8, 29 * 8); //(gameWidth/2,gameHeight/2+20); //just under ghost house
	//Player player(gameWidth / 2, gameHeight / 2 + 20, playerSprite);
	Player player(29, 3, playerSprite);


//score display and other text
	//score display setup
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) printf("unable to load font");

	// Initialize the pause message
	sf::Text scoreDisplay;
	scoreDisplay.setFont(font);
	scoreDisplay.setCharacterSize(11);
	scoreDisplay.setPosition(8, gameHeight - 16);
	scoreDisplay.setColor(sf::Color::White);
	int score = 0;
	scoreDisplay.setString("Score: "+ (std::to_string(score)) );


	////////--------window loop--------------/////////////
	while (window.isOpen()){

		int pRow = player.xpos;
		int pCol = player.ypos;
		//char currTileType = tileArray[px][py].getType();
		char toTileType;
		bool changePlayerDir = false;
		char currDir = 'l';
		player.move('l');


		sf::Event event;
		while (window.pollEvent(event)){

			if (event.type == sf::Event::Closed){
				window.close();
			}


			//move player up
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				toTileType = tileArray[pRow - 1][pCol].getType();
				if (toTileType != 'w'){
					player.setDirection('u');
					currDir = 'u';
					player.move();
					playerSprite = player.getSprite();
				}
				//adjust score & tile if applicable
				if (toTileType == 'd'){
					tileArray[pRow-1][pCol].setType('e');
					score += 1;
					scoreDisplay.setString("Score: " + (std::to_string(score)));
				}
			}
			//move player down
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				toTileType = tileArray[pRow + 1][pCol].getType();
				if (toTileType != 'w'){
					player.setDirection('d');
					currDir = 'd';
					player.move();
					playerSprite = player.getSprite();
				}
				//adjust score & tile if applicable
				if (toTileType == 'd'){
					tileArray[pRow+1][pCol].setType('e');
					score += 1;
					scoreDisplay.setString("Score: " + (std::to_string(score)));
				}
			}
			//move player left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				toTileType = tileArray[pRow][pCol - 1].getType();
				if (toTileType != 'w'){
					player.setDirection('l');
					currDir = 'l';
					if (pRow == 17 && pCol == 1) player.wrapHorizontal();
					else {
						player.move();
					}
					playerSprite = player.getSprite();
				}
				//adjust score & tile if applicable
				if (toTileType == 'd'){
					tileArray[pRow][pCol-1].setType('e');
					score += 1;
					scoreDisplay.setString("Score: " + (std::to_string(score)));
				}
			}
			//move player right
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				toTileType = tileArray[pRow][pCol + 1].getType();
				if (pRow == 17 && pCol == 27) {
					player.setDirection('r');
					currDir = 'r';
					player.wrapHorizontal();
				}
				else{
					if (toTileType != 'w'){
						player.setDirection('r');
						currDir = 'r';
						player.move();
					}
				}
				playerSprite = player.getSprite();
				//adjust score & tile if applicable
				if (toTileType == 'd'){
					tileArray[pRow][pCol+1].setType('e');
					score += 1;
					scoreDisplay.setString("Score: " + (std::to_string(score)));
				}
			}


			window.clear();
			window.draw(background);

			//draw dots and powerups
			for (int j = 0; j < rows; j++){
				for (int i = 0; i < cols; i++){
					int xpos = i * 8;
					int ypos = j * 8;
					Tile t = tileArray[j][i]; //j row, i col

					/*
					if (i == 3 && j == 29) {
						playerSprite.setPosition(i * 8, j * 8);
						window.draw(playerSprite);
						}
						*/

					if (t.getType() == 'e'){
						sf::Sprite drawTi = wall; //t.getSprite();
						drawTi.setPosition(xpos, ypos);
						window.draw(drawTi);
					}

					if (t.getType() == 'd' || t.getType() == 'u'){
						sf::Sprite drawTi = t.getSprite();
						drawTi.setPosition(xpos, ypos);
						window.draw(drawTi);
					}
				}
			}

			window.draw(playerSprite);
			window.draw(scoreDisplay);

			window.display();
		}

	}
}
