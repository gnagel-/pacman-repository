#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player{
private:
	//double xpos;
	//double ypos;
	//sf::Vector2f mapLocation;
	sf::Sprite sprite;
	int score;
	char direction = 'l'; //(u)p, (d)own, (l)eft, (r)ight,  by default start facing left
	
public:
	double xpos;
	double ypos;

	Player();
	Player(double x, double y, sf::Sprite spr);
	void move();
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
};