#pragma once
#include "Helpers.hpp"

class Projectile : public sf::Drawable, public sf::Transformable {
public:
	bool load(const std::string& projectile_dir);

	void shoot();
	void setDirection(sf::RenderWindow& window, sf::Vector2f player_pos);

	sf::Vector2f get_pos() {
		return projectile_pos;
	}
	bool isShot() {
		return shot;
	}
private:
	float size = 32.f;
	bool shot = false;

	sf::Vector2i mouse_pos;
	sf::Vector2f projectile_pos;
	sf::Vector2f projectile_velocity;

	float x, y, magnitude;
	float velocity = 20.f;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture m_texture;
};

