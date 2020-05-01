#pragma once
#include "Helpers.hpp"
#include <random>

class Enemy : public sf::Drawable, public sf::Transformable {
public:
	Enemy();
	bool load(const std::string& tileset_dir);
	void setRandomPos(sf::RenderWindow& window);
	void updatePos(sf::Vector2f player_pos);
	bool isColliding(sf::Vector2f projectile_pos);

	sf::Vector2f get_pos() {
		return pos;
	}

	void setAlive(bool state) {
		alive = state;
	}

	bool isAlive() {
		return alive;
	}
private:
	sf::Vector2f pos;
	sf::Vector2f rand_pos;
	sf::Vector2f vel;

	std::mt19937 random;
	std::uniform_int_distribution<int> dist_x;
	std::uniform_int_distribution<int> dist_y;

	float size = 64.f;

	float velocity = 5.f;

	float x, y, magnitude;

	bool alive = true;

	int rand_xc;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture m_texture;
};

