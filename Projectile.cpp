#include "Projectile.hpp"

bool Projectile::load(const std::string& projectile_dir, sf::Vector2f& pos) {
	if (!m_texture.loadFromFile(projectile_dir)) {
		return false;
	}

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(4);

	return true;
}

void Projectile::shoot() {
	projectile_pos.x += projectile_velocity.x;
	projectile_pos.y += projectile_velocity.y;

	m_vertices[0] = sf::Vector2f(0, 0);
	m_vertices[1] = sf::Vector2f(size, 0.f);
	m_vertices[2] = sf::Vector2f(size, size);
	m_vertices[3] = sf::Vector2f(0.f, size);

	m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
	m_vertices[1].texCoords = sf::Vector2f(size, 0.f);
	m_vertices[2].texCoords = sf::Vector2f(size, size);
	m_vertices[3].texCoords = sf::Vector2f(0.f, size);

	setPosition(projectile_pos.x, projectile_pos.y);
}

void Projectile::setDirection(sf::RenderWindow& window, sf::Vector2f& player_pos) {
	shot = true;

	mouse_pos = sf::Mouse::getPosition(window);

	projectile_pos = player_pos;

	x = mouse_pos.x - projectile_pos.x;
	y = mouse_pos.y - projectile_pos.y;

	magnitude = std::sqrt(std::pow(x, 2) + std::pow(y, 2));

	projectile_velocity.x = x * velocity / magnitude;
	projectile_velocity.y = y * velocity / magnitude;

	shoot();
}

void Projectile::updatePos() {
	if (shot) {
		shoot();
	}
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_vertices, states);
}
