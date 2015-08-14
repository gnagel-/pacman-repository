#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Ghosts{
private:
	char mode; //(c)hase, (f)rightened, (s)catter, (h)ouse
	char name; //(b)linky, (i)nky, (p)inky, (c)lyde
	sf::Sprite sprite;
	sf::Clock timer;
	float speed;
	
public:
	double row;
	double column;
	char direction = 'l'; //(u)p, (d)own, (l)eft, (r)ight

	Ghosts();
	Ghosts(char m, char n, sf::Sprite spr, float x, float y);
	char getMode();
	void setMode(char m);
	void changeMode(char newMode);
	void reverse(char dir);
	char getDirection();
	void setDirection(char d);
	char getName();
	void setName(char n);
	sf::Sprite getSprite();
	void setSprite(sf::Sprite spr);
	float getSpeed();
	void setSpeed(float s);
	void Ghosts::frightenGhost(sf::IntRect f);
	double getRow();
	double getCol();
	void setRow(double r);
	void setCol(double c);
	void setPos(double r, double c);
	void resetGhost();
};