#include "Helpers.hpp"

sf::VertexArray Helpers::getVertices(sf::VertexArray vertices, float size) {
	vertices[0] = sf::Vector2f(0.f, 0.f);
	vertices[1] = sf::Vector2f(size, 0.f);
	vertices[2] = sf::Vector2f(size, size);
	vertices[3] = sf::Vector2f(0.f, size);

	vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
	vertices[1].texCoords = sf::Vector2f(size, 0.f);
	vertices[2].texCoords = sf::Vector2f(size, size);
	vertices[3].texCoords = sf::Vector2f(0.f, size);

	return vertices;
}