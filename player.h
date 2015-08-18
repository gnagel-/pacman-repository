#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player{
private:
	sf::Sprite sprite;
	int score;
	char direction = 'l'; //(u)p, (d)own, (l)eft, (r)ight,  by default start facing left
	float speed;
	float speedAdjust;
	float speedInc = 8;
	//int timePass;
	//int animation;
	//bool isDead;
	
public:
	int row;
	int column;

	Player();
	Player(int r, int c, sf::Sprite spr);
	void move();
	void move(char toType);
	void death();
	void gameOver();
	sf::Sprite getSprite();
	void setSprite(sf::Sprite spr);
	int getScore();
	void setScore(int s);
	char getDirection();
	void setDirection(char dir);
	void eatTile();
	void wrapHorizontal();
	void setPos(int row, int column);

	void update();
};