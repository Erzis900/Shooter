#pragma once
#define M_PI 3.14159265358979323846
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable, public sf::Transformable {
public:
	Player();
	bool load(const std::string& tileset_dir);

	void move();
	void checkWallCollision(const unsigned int& screen_width, const unsigned int& screen_height);
	float getAngle(sf::RenderWindow& window);

	sf::Vector2f& get_pos() {
		return pos;
	}
private:
	sf::Vector2f pos;

	float width = 128.f;
	float height = 128.f;

	float speed = 5.f;

	float x, y, angle;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture m_texture;
};

