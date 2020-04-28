#include "Player.hpp"

Player::Player() {
	setOrigin(width / 2, height / 2);
	pos.x = 640.f;
	pos.y = 384.f;
}

bool Player::load(const std::string& tileset_dir) {
	if (!m_texture.loadFromFile(tileset_dir)) {
		return false;
	}

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(4);

	m_vertices[0] = sf::Vector2f(0, 0);
	m_vertices[1] = sf::Vector2f(width, 0.f);
	m_vertices[2] = sf::Vector2f(width, height);
	m_vertices[3] = sf::Vector2f(0, height);

	m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
	m_vertices[1].texCoords = sf::Vector2f(width, 0.f);
	m_vertices[2].texCoords = sf::Vector2f(width, height);
	m_vertices[3].texCoords = sf::Vector2f(0.f, height);

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
	if (pos.x < width / 2) pos.x = width / 2;
	if (pos.x > screen_width - width / 2) pos.x = screen_width - width / 2;
	if (pos.y < height / 2) pos.y = height / 2;
	if (pos.y > screen_height - height / 2) pos.y = screen_height - height / 2;
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
