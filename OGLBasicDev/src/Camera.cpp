/*
 * Camera.cpp
 *
 *  Created on: 08.11.2012
 *      Author: Tadayoshi
 */

#include "Camera.h"

#ifndef M_PI
#define M_PI 3.1415926
#endif

Camera::Camera() {
	camX=0.0, camY=0.0, camZ=5.0;
	camYaw=0.0;
	camPitch=0.0;
}

void Camera::lock() {
	if (camPitch > 90) {
		camPitch = 90;
	}
	if (camPitch< -90) {
		camPitch = -90;
	}
	if (camYaw > 360) {
		camYaw -= 360;
	}
	if (camYaw < 0) {
		camYaw += 360;
	}
}

void Camera::moveXZ(float velocity, float angle) {
	float rad = (camYaw + angle) * M_PI/180;

	camX -= sin(rad)*velocity;
	camZ -= cos(rad)*velocity;
}

void Camera::moveY(float velocity, float angle) {
	float rad = (camPitch + angle) * M_PI/180;

	camY += sin(rad)*velocity;
}

void Camera::Control(float moveVel, float mouseVel, sf::Window * window) {
	int MidX = window->getSize().x/2;
	int MidY = window->getSize().y/2;

	int tmpX, tmpY;
	sf::Vector2i pos = sf::Mouse::getPosition(*window);
	tmpX = pos.x;
	tmpY = pos.y;

	sf::Mouse::setPosition(sf::Vector2i(MidX,MidY),*window);

	camYaw += mouseVel*(MidX-tmpX);
	camPitch += mouseVel*(MidY-tmpY);

	lock();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (camPitch != 90 && camPitch != -90) {
			moveXZ(moveVel,0.0);
			//moveY(moveVel, 0.0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (camPitch != 90 && camPitch != -90) {
			moveXZ(moveVel,180.0);
			//moveY(moveVel, 180.0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveXZ(moveVel,90.0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveXZ(moveVel,270.0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		camY += moveVel;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		camY -= moveVel;
	}
}

void Camera::Update() {
	glRotatef(-camPitch,1.0,0.0,0.0);
	glRotatef(-camYaw,0.0,1.0,0.0);
	glTranslatef(-camX, -camY, -camZ);
}
