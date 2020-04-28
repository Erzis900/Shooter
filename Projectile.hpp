#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <chrono>

class Projectile : public sf::Drawable, public sf::Transformable {
public:
	bool load(const std::string& projectile_dir, sf::Vector2f& pos);

	void shoot();
	void setDirection(sf::RenderWindow& window, sf::Vector2f& player_pos);
	void updatePos();

	sf::Vector2f& get_pos() {
		return projectile_pos;
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

