#include <SFML/Graphics.hpp>
#include <vector>

namespace Tileset 
{
    enum TILES {
        WALL, GROUND, DOOR
    };
}

class Map {
public:
    Map(int rows, int cols);
    std::unique_ptr<std::vector<sf::Sprite>> getMap();
private:
    int n_rows;
    int n_cols;
    sf::Texture tileset;
    std::vector<sf::Sprite> positions;
}



