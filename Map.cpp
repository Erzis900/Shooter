#include "Map.hpp"

bool Map::load(const std::string& tileset_dir, sf::Vector2u tile_size, const int* map_pattern, unsigned int width, unsigned int height) {
	if (!m_texture.loadFromFile(tileset_dir)) {
		return false;
	}

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            tile_number = map_pattern[i + j * width];

            row_size = m_texture.getSize().x / tile_size.x;

            texture_x = tile_number % row_size;
            texture_y = tile_number / row_size;

            quad = &m_vertices[(i + j * width) * 4];

            quad[0].position = sf::Vector2f(static_cast<float>(i * tile_size.x), static_cast<float>(j * tile_size.y));
            quad[1].position = sf::Vector2f(static_cast<float>((i + 1) * tile_size.x), static_cast<float>(j * tile_size.y));
            quad[2].position = sf::Vector2f(static_cast<float>((i + 1) * tile_size.x), static_cast<float>((j + 1) * tile_size.y));
            quad[3].position = sf::Vector2f(static_cast<float>(i * tile_size.x), static_cast<float>((j + 1) * tile_size.y));
            
            quad[0].texCoords = sf::Vector2f(static_cast<float>(texture_x * tile_size.x), static_cast<float>(texture_y * tile_size.y));
            quad[1].texCoords = sf::Vector2f(static_cast<float>((texture_x + 1) * tile_size.x), static_cast<float>(texture_y * tile_size.y));
            quad[2].texCoords = sf::Vector2f(static_cast<float>((texture_x + 1) * tile_size.x), static_cast<float>((texture_y + 1) * tile_size.y));
            quad[3].texCoords = sf::Vector2f(static_cast<float>(texture_x * tile_size.x), static_cast<float>((texture_y + 1) * tile_size.y));
        }
    }
       
	return true;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_vertices, states);
}
