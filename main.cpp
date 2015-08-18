#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include "tile.h"
#include "player.h"
#include "ghosts.h";

// nowhere near complete, but the most I can get done right now

int main(){
	//game map is 224 x 288
	//28 x 36 tiles, 8 pixels square
	int gameWidth = 224;
	int gameHeight = 288;
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "SFML Application");
	//window.setFramerateLimit(60);
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
	playerSprite.setPosition(14 * 8, 20 * 8); //just under ghost house
	Player player(20, 14, playerSprite);

	int pRow = player.row;
	int pCol = player.column;
	char toTileType = tileArray[pRow][pCol - 1].getType();  //default start direction is left
	int lives = 2;
	bool gameOver = false;

	int score = 0;
	int dotScore = 10;
	int puScore = 50; //power up
	int gScore = 200; //ghost


	//score display and other text
	//score display 
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) printf("unable to load font");

	sf::Text scoreDisplay;
	scoreDisplay.setFont(font);
	scoreDisplay.setCharacterSize(11);
	scoreDisplay.setPosition(8, gameHeight - 16);
	scoreDisplay.setColor(sf::Color::White);
	scoreDisplay.setString("Score: " + (std::to_string(score)));

	sf::Sprite life1;
	life1.setTexture(spriteSheet);
	life1.setTextureRect(sf::IntRect(470, 0, 16, 16));
	life1.setOrigin(sf::Vector2f(8, 8));
	life1.setPosition(gameWidth - (8 * 10), gameHeight - 8);

	sf::Sprite life2;
	life2.setTexture(spriteSheet);
	life2.setTextureRect(sf::IntRect(470, 0, 16, 16));
	life2.setOrigin(sf::Vector2f(8, 8));
	life2.setPosition(gameWidth - (8 * 8), gameHeight - 8);

	//ghosts	
	//ghost sprites
	sf::Texture ghostTex;
	ghostTex.loadFromFile("Pac Man Map.png");

	//blinky
	sf::Sprite blinkySpr;
	blinkySpr.setTexture(ghostTex);
	sf::IntRect blink(228, 64, 16, 16);
	blinkySpr.setTextureRect(blink);
	blinkySpr.setOrigin(8, 8);

	Ghosts blinky('s', 'b', blinkySpr, 14, 13);
	blinkySpr.setPosition(13 * 8, 14 * 8);

	//inky
	sf::Sprite inkySpr;
	inkySpr.setTexture(ghostTex);
	sf::IntRect ink(228, 96, 16, 16);
	inkySpr.setTextureRect(ink);
	inkySpr.setOrigin(8, 8);

	Ghosts inky('h', 'i', inkySpr, 14, 14); //movement will start outside house
	inkySpr.setPosition(11.5 * 8, 16.5 * 8);

	//pinky
	sf::Sprite pinkySpr;
	pinkySpr.setTexture(ghostTex);
	sf::IntRect pink(228, 80, 16, 16);
	pinkySpr.setTextureRect(pink);
	pinkySpr.setOrigin(8, 8);

	Ghosts pinky('h', 'p', pinkySpr, 14, 14);
	pinkySpr.setPosition(13.5 * 8, 17 * 8);

	//clyde
	sf::Sprite clydeSpr;
	clydeSpr.setTexture(ghostTex);
	sf::IntRect cly(228, 112, 16, 16);
	clydeSpr.setTextureRect(cly);
	clydeSpr.setOrigin(8, 8);

	Ghosts clyde('h', 'c', clydeSpr, 14, 14);
	clydeSpr.setPosition(15.5 * 8, 16.5 * 8);

	//fright sprite
	//sf::Sprite frightSpr;
	//frightSpr.setTexture(ghostTex);
	sf::IntRect fright(356, 64, 16, 16);
	//frightSpr.setTextureRect(fright);
	//frightSpr.setOrigin(8, 8);

	//timer
	sf::Clock clock;
	//sf::Clock clock2;
	//sf::Time elapsed1;
	int waveCount = 1;
	bool midWave = false;
	int dotCounter = 0;
	bool frightMode = false;

////////--------window loop--------------/////////////
	while (window.isOpen()){

		//ghost, player collision
		if (pRow == blinky.row && pCol == blinky.column){
			if (blinky.getMode() == 'f'){ //collision in fright mode
				score += gScore;
				scoreDisplay.setString("Score: " + (std::to_string(score)));

				blinkySpr.setTextureRect(blink);
				blinkySpr.setPosition(12.5 * 8, 17 * 8);
				blinky.setPos(17, 12);
				blinky.setMode('h');
			}
			else { //lose a life
				lives -= 1;
				player.setPos(20, 14);
				playerSprite.setPosition(14 * 8, 20 * 8); //just under ghost house
				player.setSprite(playerSprite);
			}
		}

		if (player.getDirection() == 'u'){
			toTileType = tileArray[pRow - 1][pCol].getType();
		}
		else if (player.getDirection() == 'd'){
			toTileType = tileArray[pRow + 1][pCol].getType();
		}
		else if (player.getDirection() == 'l'){
			toTileType = tileArray[pRow][pCol - 1].getType();
		}
		else if (player.getDirection() == 'r'){
			toTileType = tileArray[pRow][pCol + 1].getType();
		}

		/////////------event loop-------------//////////////////
		sf::Event event;
		while (window.pollEvent(event)){


			if (event.type == sf::Event::Closed){
				window.close();
			}

			//move player up
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				printf("Row: %d, Column: %d\n MovingTo Row : %d, Column : %d \n", pRow, pCol, pRow - 1, pCol);

				toTileType = tileArray[pRow - 1][pCol].getType();
				if (toTileType != 'w') player.setDirection('u');
			}
			//move player down
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				printf("Row: %d, Column: %d\n MovingTo Row: %d, Column: %d \n", pRow, pCol, pRow + 1, pCol);

				toTileType = tileArray[pRow + 1][pCol].getType();
				if (toTileType != 'w') player.setDirection('d');
			}
			//move player left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				printf("Row: %d, Column: %d\n MovingTo Row: %d, Column: %d \n", pRow, pCol, pRow, pCol - 1);

				toTileType = tileArray[pRow][pCol - 1].getType();
				if (toTileType != 'w') player.setDirection('l');
			}
			//move player right
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				printf("current Row: %d, Column: %d\n MovingTo Row: %d, Column: %d \n", pRow, pCol, pRow, pCol + 1);

				toTileType = tileArray[pRow][pCol + 1].getType();
				if (toTileType != 'w') player.setDirection('r');
			}

			//reset dots
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::R)){
				blinkySpr.setPosition(13 * 8, 14 * 8);
				blinky.setPos(14, 13);

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
			} //end reset dots
		}


///////////////-----end event loop-----/////////////////

		if (toTileType != 'w'){
			player.move(toTileType);
			printf("\ncurrent Row : %d, Column : %d\n ", pRow, pCol);
			playerSprite.setPosition(player.column * 8, player.row * 8);

			if (toTileType == 'd'){ //eat dot, adjust tile
				if (player.getDirection() == 'u'){
					tileArray[pRow - 1][pCol].setType('e');
				}
				else if (player.getDirection() == 'd'){
					tileArray[pRow + 1][pCol].setType('e');
				}
				else if (player.getDirection() == 'l'){
					tileArray[pRow][pCol - 1].setType('e');
				}
				else if (player.getDirection() == 'r'){
					tileArray[pRow][pCol + 1].setType('e');
				}
				score += dotScore;
				scoreDisplay.setString("Score: " + (std::to_string(score)));
			}
			else if (toTileType == 'u'){ //eat powerup, adjust tile
				if (player.getDirection() == 'u'){
					tileArray[pRow - 1][pCol].setType('e');
				}
				else if (player.getDirection() == 'd'){
					tileArray[pRow + 1][pCol].setType('e');
				}
				else if (player.getDirection() == 'l'){
					tileArray[pRow][pCol - 1].setType('e');
				}
				else if (player.getDirection() == 'r'){
					tileArray[pRow][pCol + 1].setType('e');
				}

				score += puScore;
				scoreDisplay.setString("Score: " + (std::to_string(score)));
				frightMode = true;
				blinky.frightenGhost(fright);
				blinkySpr.setTextureRect(fright); //fright blinky
				inky.frightenGhost(fright);
				inkySpr.setTextureRect(fright); //fright inky
				pinky.frightenGhost(fright);
				pinkySpr.setTextureRect(fright); //fright pinky
				clyde.frightenGhost(fright);
				clydeSpr.setTextureRect(fright); //fright clyde
			}
		}

	
		//playerSprite = player.getSprite();

		window.clear();
		window.draw(background);

		//draw dots and powerups
		for (int j = 0; j < rows; j++){
			for (int i = 0; i < cols; i++){
				int xpos = i * 8;
				int ypos = j * 8;
				Tile t = tileArray[j][i]; //j row, i col

				/*
				if (i == 25 && j == 26) {
				//playerSprite.setPosition(i * 8, j * 8);
				//window.draw(playerSprite);
				}
				//*/

				if (t.getType() == 'd' || t.getType() == 'u'){
					sf::Sprite drawTi = t.getSprite();
					drawTi.setPosition(xpos, ypos);
					window.draw(drawTi);

				}
				/*
				else if (t.getType() == 'e'){
				sf::Sprite drawTi = wall; //t.getSprite();
				drawTi.setPosition(xpos, ypos);
				window.draw(drawTi);
				}
				*/
			}
		}


		window.draw(playerSprite);
		pRow = player.row;
		pCol = player.column;
		window.draw(blinkySpr);
		window.draw(inkySpr);
		window.draw(pinkySpr);
		window.draw(clydeSpr);
		window.draw(scoreDisplay);
		if (lives > 1){
			window.draw(life1);
			window.draw(life2);
		}
		else if (lives == 1){
			window.draw(life1);
		}
		else if (lives < 0){
			gameOver = true;
		}

		window.display();
	}
}

