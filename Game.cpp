#include "Game.hpp"

Game::Game() {
	window.create(sf::VideoMode(width, height), "SHOOTER");
	window.setFramerateLimit(60);

	if (loadTextures()) {
		loop();
	}
}

bool Game::loadTextures() {
	return map.load("art/tileset.png", sf::Vector2u(64, 64), map_pattern, 20, 12) &&
	player.load("art/player.png") && enemy.load("art/enemy.png") &&
	projectile.load("art/projectile.png");
}

void Game::loop() {
	clock.restart();
	enemies.push_back(enemy);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
			else if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				projectile.setDirection(window, player.get_pos());
				isShot = true;
			}
		}

		player.move();
		player.setRotation(player.getAngle(window));
		player.checkWallCollision(width, height);

		render();
	}
}

void Game::render() {
	window.clear();
	window.draw(map);
	window.draw(player);

	if (isShot) {
		Projectile bullet = projectile;
		projectiles.push_back(bullet);

		isShot = false;
	}

	for (unsigned int i = 0; i < projectiles.size(); i++) {
		if (projectiles.at(i).isShot()) {
			projectiles.at(i).shoot();
		}
		window.draw(projectiles.at(i));
		i_counter = i;
	}

	for (unsigned int j = 0; j < enemies.size(); j++) {
		if (enemies.at(j).isAlive()) {
			enemies.at(j).updatePos(player.get_pos());

			window.draw(enemies.at(j));

			if (enemies.at(j).isColliding(projectiles.at(i_counter).get_pos())) {
				enemies.at(j).setAlive(false);
				isAlive = false;
			}

			elapsed = clock.getElapsedTime();		

			if (!isAlive || static_cast<int>(elapsed.asSeconds()) % 4 == 0 && static_cast<int>(elapsed.asSeconds()) != 0) {
				if (isAlive) {
					clock.restart();
				}

				Enemy new_enemy = enemies.at(j);

				new_enemy.setAlive(true);
				new_enemy.setRandomPos(window);

				enemies.push_back(new_enemy);

				isAlive = true;
			}
		}
	}

	window.display();
}