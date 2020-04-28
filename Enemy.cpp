#include "Enemy.hpp"

Enemy::Enemy() : dist_x(0, 19), dist_y(0, 11) {}

bool Enemy::load(const std::string& tileset_dir) {
	if (!m_texture.loadFromFile(tileset_dir)) {
		return false;
	}

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(4);

	m_vertices[0] = sf::Vector2f(0, 0);
	m_vertices[1] = sf::Vector2f(size, 0.f);
	m_vertices[2] = sf::Vector2f(size, size);
	m_vertices[3] = sf::Vector2f(0, size);

	m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
	m_vertices[1].texCoords = sf::Vector2f(size, 0.f);
	m_vertices[2].texCoords = sf::Vector2f(size, size);
	m_vertices[3].texCoords = sf::Vector2f(0.f, size);

	return true;
}

void Enemy::setRandomPos(sf::RenderWindow& window) {
	random.seed(std::random_device()());

	rand_xc = dist_x(random);

	if (rand_xc > 0 && rand_xc < window.getSize().x / size - 1) {
		if (rand_xc % 2 == 0) {
			rand_pos.y = 0.f;
		}
		else {
			rand_pos.y = (window.getSize().y / size - 1) * size;
		}
	}
	else {
		rand_pos.y = dist_y(random) * size;
	}

	rand_pos.x = rand_xc * size;

	pos = rand_pos;
}

void Enemy::updatePos(sf::Vector2f& player_pos) {
	x = player_pos.x - pos.x;
	y = player_pos.y - pos.y;

	magnitude = std::sqrt(std::pow(x, 2) + std::pow(y, 2));

	vel.x = x * velocity / magnitude;
	vel.y = y * velocity / magnitude;

	pos.x += vel.x;
	pos.y += vel.y;

	m_vertices[0] = sf::Vector2f(0, 0);
	m_vertices[1] = sf::Vector2f(size, 0.f);
	m_vertices[2] = sf::Vector2f(size, size);
	m_vertices[3] = sf::Vector2f(0.f, size);

	m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
	m_vertices[1].texCoords = sf::Vector2f(size, 0.f);
	m_vertices[2].texCoords = sf::Vector2f(size, size);
	m_vertices[3].texCoords = sf::Vector2f(0.f, size);

	setPosition(pos.x, pos.y);
}

bool Enemy::isColliding(sf::Vector2f& projectile_pos) {
	if (pos.x < projectile_pos.x + size && pos.x + size > projectile_pos.x &&
		pos.y < projectile_pos.y + size && pos.y + size > projectile_pos.y && projectile_pos.x != 0.f) {

		return true;
	}
	return false;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_vertices, states);
}