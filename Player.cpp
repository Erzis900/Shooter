#include "Player.hpp"

Player::Player() {
	setOrigin(size / 2, size / 2);
	pos.x = 640.f;
	pos.y = 384.f;
}

bool Player::load(const std::string& tileset_dir) {
	if (!m_texture.loadFromFile(tileset_dir)) {
		return false;
	}

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(4);

	m_vertices = Helpers::getVertices(m_vertices, size);

	move();

	return true;
}

void Player::move() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		pos.y -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		pos.y += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		pos.x += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		pos.x -= speed;
	}

	setPosition(pos.x, pos.y);
}

void Player::checkWallCollision(const unsigned int& screen_width, const unsigned int& screen_height) {
	if (pos.x < size / 2) pos.x = size / 2;
	if (pos.x > screen_width - size / 2) pos.x = screen_width - size / 2;
	if (pos.y < size / 2) pos.y = size / 2;
	if (pos.y > screen_height - size / 2) pos.y = screen_height - size / 2;
}

bool Player::isColliding(sf::Vector2f enemy_pos) {
	return pos.x < enemy_pos.x + size && pos.x + size > enemy_pos.x &&
	pos.y < enemy_pos.y + size && pos.y + size > enemy_pos.y;
}

float Player::getAngle(sf::RenderWindow& window) {
	x = sf::Mouse::getPosition(window).x - pos.x;
	y = sf::Mouse::getPosition(window).y - pos.y;
	angle = std::atan2(y, x) * 180 / M_PI;
	return angle;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_vertices, states);
}
