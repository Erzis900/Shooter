#pragma once
#include <SFML/Graphics.hpp>

class Map : public sf::Drawable, public sf::Transformable {
public:
	bool load(const std::string& tileset_dir, sf::Vector2u tile_size, const int* map_pattern, unsigned int width, unsigned int height);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture m_texture;

	int tile_number;
	int row_size;
	int texture_x, texture_y;
	sf::Vertex* quad;
};

