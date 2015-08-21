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
	window.setFramerateLimit(60);
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
	int bRow = blinky.getRow();
	int bCol = blinky.getColumn();
	blinky.scatterMode();

	//inky
	sf::Sprite inkySpr;
	inkySpr.setTexture(ghostTex);
	sf::IntRect ink(228, 96, 16, 16);
	inkySpr.setTextureRect(ink);
	inkySpr.setOrigin(8, 8);

	Ghosts inky('h', 'i', inkySpr, 14, 14); //movement will start outside house
	inkySpr.setPosition(11.5 * 8, 16.5 * 8);
	int iRow = inky.getRow();
	int iCol = inky.getColumn();

	//pinky
	sf::Sprite pinkySpr;
	pinkySpr.setTexture(ghostTex);
	sf::IntRect pink(228, 80, 16, 16);
	pinkySpr.setTextureRect(pink);
	pinkySpr.setOrigin(8, 8);

	Ghosts pinky('h', 'p', pinkySpr, 14, 14);
	pinkySpr.setPosition(13.5 * 8, 17 * 8);
	int piRow = pinky.getRow();
	int piCol = pinky.getColumn();

	//clyde
	sf::Sprite clydeSpr;
	clydeSpr.setTexture(ghostTex);
	sf::IntRect cly(228, 112, 16, 16);
	clydeSpr.setTextureRect(cly);
	clydeSpr.setOrigin(8, 8);

	Ghosts clyde('h', 'c', clydeSpr, 14, 14);
	clydeSpr.setPosition(15.5 * 8, 16.5 * 8);
	int cRow = clyde.getRow();
	int cCol = clyde.getColumn();

	//fright sprite
	//sf::Sprite frightSpr;
	//frightSpr.setTexture(ghostTex);
	sf::IntRect fright(356, 64, 16, 16);
	//frightSpr.setTextureRect(fright);
	//frightSpr.setOrigin(8, 8);

	//scatter chase timer
	sf::Clock clock;
	sf::Time elapsed1;
	float waveCount = 1;
	bool midWave = false;

	int dotCounter = 0;

	//fright timer
	sf::Clock frightTimer;

	char toTileb = 'e';
	char bToTileUp;
	char bToTileDown;
	char bToTileLeft;
	char bToTileRight;
	char bestDirection = 'l';


	blinky.scatterMode(); //start in scatter mode
	clock.restart();
	////////--------window loop--------------/////////////
	while (window.isOpen()){
		//wave 1: scatter 7, chase 20
		if (clock.getElapsedTime() >= sf::seconds(4) && waveCount == 1){ //7 seconds up, switch to  chase
			//printf("wave 1 - fright\n");
			//blinkySpr.setTextureRect(fright);
			//blinky.setTarget(pRow, pCol); //chase
			blinky.chaseMode(pRow, pCol, player.getDirection());
			pinky.chaseMode(pRow, pCol, player.getDirection());
			inky.chaseModeInky(pRow, pCol, bRow, bCol, player.getDirection(), blinky.getDirection());
			clyde.chaseModeClyde(pRow, pCol, player.getDirection());
			clock.restart();
			waveCount += 0.5;
		}
		else if (clock.getElapsedTime() >= sf::seconds(4) && waveCount == 1.5){ //20 seconds up, switch to scatter
			//printf("wave 2 - normal\n");
			//blinkySpr.setTextureRect(blink);
			blinky.scatterMode();
			pinky.scatterMode();
			inky.scatterMode();
			clyde.scatterMode();
			clock.restart();
			waveCount += 0.5;
		}
		//wave 2: scatter 7, chase 20
		else if (clock.getElapsedTime() >= sf::seconds(4) && waveCount == 2){
			//printf("wave 2 - normal\n");
			//blinkySpr.setTextureRect(fright);
			blinky.chaseMode(pRow, pCol, player.getDirection());
			pinky.chaseMode(pRow, pCol, player.getDirection());
			inky.chaseModeInky(pRow, pCol, bRow, bCol, player.getDirection(), blinky.getDirection());
			clyde.chaseModeClyde(pRow, pCol, player.getDirection());
			clock.restart();
			waveCount += 0.5;
		}
		else if (clock.getElapsedTime() >= sf::seconds(4) && waveCount == 2.5){
			//printf("wave 2 - normal\n");
			//blinkySpr.setTextureRect(blink);
			blinky.scatterMode();
			pinky.scatterMode();
			inky.scatterMode();
			clyde.scatterMode();
			clock.restart();
			waveCount += 0.5;
		}
		// wave 3: scatter 5, chase 20
		else if (clock.getElapsedTime() >= sf::seconds(4) && waveCount == 3){
			//printf("wave 2 - normal\n");
			//blinkySpr.setTextureRect(fright);
			blinky.chaseMode(pRow, pCol, player.getDirection());
			pinky.chaseMode(pRow, pCol, player.getDirection());
			inky.chaseModeInky(pRow, pCol, bRow, bCol, player.getDirection(), blinky.getDirection());
			clyde.chaseModeClyde(pRow, pCol, player.getDirection());
			clock.restart();
			waveCount += 0.5;
		}
		else if (clock.getElapsedTime() >= sf::seconds(4) && waveCount == 3.5){
			//printf("wave 3 - fright\n");
			//blinkySpr.setTextureRect(blink);
			blinky.scatterMode();
			pinky.scatterMode();
			inky.scatterMode();
			clyde.scatterMode();
			clock.restart();
			waveCount += 0.5;
		}
		// wave 4: scatter 5, chase permanent
		else if (clock.getElapsedTime() >= sf::seconds(4) && waveCount == 4){
			//printf("wave 2 - normal\n");
			//blinkySpr.setTextureRect(fright);
			blinky.chaseMode(pRow, pCol, player.getDirection());
			pinky.chaseMode(pRow, pCol, player.getDirection());
			inky.chaseModeInky(pRow, pCol, bRow, bCol, player.getDirection(), blinky.getDirection());
			clyde.chaseModeClyde(pRow, pCol, player.getDirection());
			clock.restart();
			waveCount += 0.5;
		}


		//ghost, player collision
		if (pRow == blinky.getRow() && pCol == blinky.getColumn()){
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

				clock.restart(); //reset scatterChase timer
				waveCount = 1;
			}
		}

		//player
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

//for some reason array not cooperating, so tons of text for  ghost movement
		//blinky movement
		float lastDistance = -1;
		float distance;
		char nextDirection = blinky.getDirection();
		//look right
		if ((tileArray[bRow][bCol + 1].getType() != 'w') && blinky.getDirection() != 'l'){
			nextDirection = 'r';
			//lastDistance = blinky.distanceCheck(bRow, bCol+1);
			lastDistance = (sqrt((bCol + 1 - blinky.getTargetColumn()) * (bCol + 1 - blinky.getTargetColumn())
				+ (blinky.getTargetRow() - bRow) * (blinky.getTargetRow() - bRow)));

		}
		//look down
		if ((tileArray[bRow + 1][bCol].getType() != 'w') && blinky.getDirection() != 'u'){
			//distance = blinky.distanceCheck(bRow+1, bCol);
			distance = (sqrt((bCol - pCol) * (bCol - pCol)
				+ (bRow + 1 - blinky.getTargetRow()) * (bRow + 1 - blinky.getTargetRow())));

			if (distance <= lastDistance || lastDistance == -1){
				nextDirection = 'd';
				lastDistance = distance;
			}
		}//look left
		if (tileArray[bRow][bCol - 1].getType() != 'w' && blinky.getDirection() != 'r'){
			//distance = blinky.distanceCheck(bRow, bCol-1);
			distance = (sqrt((bCol - 1 - blinky.getTargetColumn()) * (bCol - 1 - blinky.getTargetColumn())
				+ (bRow - blinky.getTargetRow()) * (bRow - blinky.getTargetRow())));

			if (distance <= lastDistance || lastDistance == -1){
				nextDirection = 'l';
				lastDistance = distance;
			}
		}//look up
		if (tileArray[bRow - 1][bCol].getType() != 'w' && blinky.getDirection() != 'd'){
			//distance = blinky.distanceCheck(bRow-1, bCol);
			distance = (sqrt((bCol - blinky.getTargetColumn()) * (bCol - blinky.getTargetColumn())
				+ (bRow - 1 - blinky.getTargetRow()) * (bRow - 1 - blinky.getTargetRow())));

			if (distance <= lastDistance || lastDistance == -1){
				nextDirection = 'u';
			}
		}

		if (blinky.getMode() == 'c'){ //make sure chase target is up to date
			blinky.chaseMode(pRow, pCol, player.getDirection());
			//printf("target row: %d, target col:  %d\n", blinky.getTargetRow(), blinky.getTargetColumn());
		}
		if (blinky.getSpeedAdjust() >= blinky.getSpeedInc() - blinky.getSpeed()){
			blinky.setDirection(nextDirection);
		}
		blinky.move();
		//printf("adjust: %f, inc:  %f\n", blinky.getSpeedAdjust(), blinky.getSpeedInc());
		//printf("target row: %d, target col:  %d\n", blinky.getTargetRow(), blinky.getTargetColumn());
		bRow = blinky.getRow();
		bCol = blinky.getColumn();
		blinkySpr.setPosition(bCol * 8, bRow * 8);

//
		//inky movement
		lastDistance = -1;
		distance;
		nextDirection = inky.getDirection();
		//look right
		if ((tileArray[iRow][iCol + 1].getType() != 'w') && inky.getDirection() != 'l'){
			nextDirection = 'r';
			lastDistance = (sqrt((iCol + 1 - inky.getTargetColumn()) * (iCol + 1 - inky.getTargetColumn())
				+ (inky.getTargetRow() - iRow) * (inky.getTargetRow() - iRow)));
		}
		//look down
		if ((tileArray[iRow + 1][iCol].getType() != 'w') && inky.getDirection() != 'u'){
			distance = (sqrt((iCol - pCol) * (iCol - pCol)
				+ (iRow + 1 - inky.getTargetRow()) * (iRow + 1 - inky.getTargetRow())));
			if (distance <= lastDistance || lastDistance == -1){
				nextDirection = 'd';
				lastDistance = distance;
			}
		}//look left
		if (tileArray[iRow][iCol - 1].getType() != 'w' && inky.getDirection() != 'r'){
			distance = (sqrt((iCol - 1 - inky.getTargetColumn()) * (iCol - 1 - inky.getTargetColumn())
				+ (iRow - inky.getTargetRow()) * (iRow - inky.getTargetRow())));
			if (distance <= lastDistance || lastDistance == -1){
				nextDirection = 'l';
				lastDistance = distance;
			}
		}//look up
		if (tileArray[iRow - 1][iCol].getType() != 'w' && inky.getDirection() != 'd'){
			distance = (sqrt((iCol - inky.getTargetColumn()) * (iCol - inky.getTargetColumn())
				+ (iRow - 1 - inky.getTargetRow()) * (iRow - 1 - inky.getTargetRow())));
			if (distance <= lastDistance || lastDistance == -1){
				nextDirection = 'u';
			}
		}

		if (inky.getMode() == 'c'){ //make sure chase target is up to date
			inky.chaseModeInky(pRow, pCol,bRow,bCol, player.getDirection(), blinky.getDirection());
		}
		if (inky.getSpeedAdjust() >= inky.getSpeedInc() - inky.getSpeed()){
			inky.setDirection(nextDirection);
		}
		inky.move();
		iRow = inky.getRow();
		iCol = inky.getColumn();
		inkySpr.setPosition(iCol * 8, iRow * 8);
//
		//pinky movement
		lastDistance = -1;
		distance;
		nextDirection = inky.getDirection();
		//look right
		if ((tileArray[piRow][piCol + 1].getType() != 'w') && pinky.getDirection() != 'l'){
			nextDirection = 'r';
			lastDistance = (sqrt((piCol + 1 - pinky.getTargetColumn()) * (piCol + 1 - pinky.getTargetColumn())
				+ (pinky.getTargetRow() - piRow) * (pinky.getTargetRow() - piRow)));
		}
		//look down
		if ((tileArray[piRow + 1][piCol].getType() != 'w') && pinky.getDirection() != 'u'){
			distance = (sqrt((piCol - pCol) * (piCol - pCol)
				+ (piRow + 1 - pinky.getTargetRow()) * (piRow + 1 - pinky.getTargetRow())));
			if (distance <= lastDistance || lastDistance == -1){
				nextDirection = 'd';
				lastDistance = distance;
			}
		}//look left
		if (tileArray[piRow][piCol - 1].getType() != 'w' && pinky.getDirection() != 'r'){
			distance = (sqrt((piCol - 1 - pinky.getTargetColumn()) * (piCol - 1 - pinky.getTargetColumn())
				+ (piRow - pinky.getTargetRow()) * (piRow - pinky.getTargetRow())));
			if (distance <= lastDistance || lastDistance == -1){
				nextDirection = 'l';
				lastDistance = distance;
			}
		}//look up
		if (tileArray[piRow - 1][piCol].getType() != 'w' && pinky.getDirection() != 'd'){
			distance = (sqrt((piCol - pinky.getTargetColumn()) * (piCol - pinky.getTargetColumn())
				+ (piRow - 1 - pinky.getTargetRow()) * (piRow - 1 - pinky.getTargetRow())));
			if (distance <= lastDistance || lastDistance == -1){
				nextDirection = 'u';
			}
		}

		if (pinky.getMode() == 'c'){ //make sure chase target is up to date
			pinky.chaseMode(pRow, pCol, player.getDirection());
		}
		if (pinky.getSpeedAdjust() >= pinky.getSpeedInc() - pinky.getSpeed()){
			pinky.setDirection(nextDirection);
		}
		pinky.move();
		piRow = pinky.getRow();
		piCol = pinky.getColumn();
		pinkySpr.setPosition(piCol * 8, piRow * 8);
//
		//clyde movement
		lastDistance = -1;
		distance;
		nextDirection = clyde.getDirection();
		//look right
		if ((tileArray[cRow][cCol + 1].getType() != 'w') && clyde.getDirection() != 'l'){
			nextDirection = 'r';
			lastDistance = (sqrt((cCol + 1 - clyde.getTargetColumn()) * (cCol + 1 - clyde.getTargetColumn())
				+ (clyde.getTargetRow() - cRow) * (clyde.getTargetRow() - cRow)));
		}
		//look down
		if ((tileArray[cRow + 1][cCol].getType() != 'w') && clyde.getDirection() != 'u'){
			distance = (sqrt((cCol - pCol) * (cCol - pCol)
				+ (cRow + 1 - clyde.getTargetRow()) * (cRow + 1 - clyde.getTargetRow())));
			if (distance <= lastDistance || lastDistance == -1){
				nextDirection = 'd';
				lastDistance = distance;
			}
		}//look left
		if (tileArray[cRow][cCol - 1].getType() != 'w' && clyde.getDirection() != 'r'){
			distance = (sqrt((cCol - 1 - clyde.getTargetColumn()) * (cCol - 1 - clyde.getTargetColumn())
				+ (cRow - clyde.getTargetRow()) * (cRow - clyde.getTargetRow())));
			if (distance <= lastDistance || lastDistance == -1){
				nextDirection = 'l';
				lastDistance = distance;
			}
		}//look up
		if (tileArray[cRow - 1][cCol].getType() != 'w' && clyde.getDirection() != 'd'){
			distance = (sqrt((cCol - clyde.getTargetColumn()) * (cCol - clyde.getTargetColumn())
				+ (cRow - 1 - clyde.getTargetRow()) * (cRow - 1 - clyde.getTargetRow())));
			if (distance <= lastDistance || lastDistance == -1){
				nextDirection = 'u';
			}
		}

		if (clyde.getMode() == 'c'){ //make sure chase target is up to date
			clyde.chaseModeClyde(pRow, pCol, player.getDirection());
		}
		if (clyde.getSpeedAdjust() >= clyde.getSpeedInc() - clyde.getSpeed()){
			clyde.setDirection(nextDirection);
		}
		clyde.move();
		cRow = clyde.getRow();
		cCol = clyde.getColumn();
		clydeSpr.setPosition(cCol * 8, cRow * 8);



		/////////------event loop-------------//////////////////
		sf::Event event;
		while (window.pollEvent(event)){


			if (event.type == sf::Event::Closed){
				window.close();
			}

			//move player up
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				//printf("Row: %d, Column: %d\n MovingTo Row : %d, Column : %d \n", pRow, pCol, pRow - 1, pCol);

				toTileType = tileArray[pRow - 1][pCol].getType();
				if (toTileType != 'w') player.setDirection('u');
			}
			//move player down
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				//printf("Row: %d, Column: %d\n MovingTo Row: %d, Column: %d \n", pRow, pCol, pRow + 1, pCol);

				toTileType = tileArray[pRow + 1][pCol].getType();
				if (toTileType != 'w') player.setDirection('d');
			}
			//move player left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				//printf("Row: %d, Column: %d\n MovingTo Row: %d, Column: %d \n", pRow, pCol, pRow, pCol - 1);

				toTileType = tileArray[pRow][pCol - 1].getType();
				if (toTileType != 'w') player.setDirection('l');
			}
			//move player right
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				//printf("current Row: %d, Column: %d\n MovingTo Row: %d, Column: %d \n", pRow, pCol, pRow, pCol + 1);

				toTileType = tileArray[pRow][pCol + 1].getType();
				if (toTileType != 'w') player.setDirection('r');
			}

			//reset dots, ghost positions
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::R)){
				blinky.resetGhost();
				blinkySpr.setTextureRect(blink);
				blinkySpr.setPosition(13 * 8, 14 * 8);

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
			//printf("\ncurrent Row : %d, Column : %d\n ", pRow, pCol);
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

				//fright mode
				//frightMode = true;
				blinky.frightenGhost(fright);
				blinkySpr.setTextureRect(fright); //fright blinky
				inky.frightenGhost(fright);
				inkySpr.setTextureRect(fright); //fright inky
				pinky.frightenGhost(fright);
				pinkySpr.setTextureRect(fright); //fright pinky
				clyde.frightenGhost(fright);
				clydeSpr.setTextureRect(fright); //fright clyde

				//pause scatterChase timer
				elapsed1 = clock.getElapsedTime();
				frightTimer.restart();
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
		bRow = blinky.getRow();
		bCol = blinky.getColumn();

		iRow = inky.getRow();
		iCol = inky.getColumn();
		window.draw(inkySpr);

		piRow = pinky.getRow();
		piCol = pinky.getColumn();
		window.draw(pinkySpr);

		cRow = clyde.getRow();
		cCol = clyde.getColumn();
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

		//all dots & power ups eaten -> score = 2580
		window.display();
	}
}

