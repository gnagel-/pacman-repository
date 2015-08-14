#include <SFML/Graphics.hpp>

class Tile{
private:
	double xpos;
	double ypos;
	char type = 'w'; //(w)all, (d)ot, (p)layer, power(u)p, (h)ouse, (e)mpty
	sf::Sprite sprite;
	bool isEdible = false;
	
public:
	Tile();
	Tile(double x, double y, char contains, sf::Sprite spr);
	void setTile(char item, sf::Sprite spr);
	void resetMap(int xval, int yval); //work on this
	void eatenTile();
	bool isLegal();
	sf::Sprite getSprite();
	void setSprite(sf::Sprite spr);
	char getType();
	void setType(char item);
	char checkTile(int tileX, int TileY);
	char checkTile(char t);
};