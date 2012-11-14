/*
 * Camera.h
 *
 *  Created on: 08.11.2012
 *      Author: Tadayoshi
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

class Camera {
public:
	Camera();
	void Update();
	void Control(float,float,sf::Window*);
	bool focus;
private:
	float camX, camY, camZ;
	float camYaw;
	float camPitch;
	void moveXZ(float,float);
	void moveY(float,float);
	void lock();
	bool normalizer;
};

#endif /* CAMERA_H_ */

/*
 * Camera::Camera() {
	camX=0.0, camY=0.0, camZ=5.0;
	camYaw=0.0;
	camPitch=0.0;
}

void Camera::lock() {
	if (camPitch>90) {
		camPitch = 90;
	}
	if (camPitch<-90) {
		camPitch = -90;
	}
	if (camYaw<0.0) {
		camYaw+=360.0;
	}
	if (camYaw>360.0) {
		camYaw-=360;
	}
}

void Camera::moveXZ(float dist,float dir) {
	float rad = (camYaw+dir)*M_PI/180.0;
	camX -= sin(rad)*dist;
	camZ -= cos(rad)*dist;
}

void Camera::moveY(float dist, float dir) {
	float rad = (camPitch+dir)*M_PI/180.0;
	camY += sin(rad)*dist;
}

void Camera::Control(float moveVel, float mouseVel, sf::Window* window) {
	int MidX = window->getSize().x/2;
	int MidY = window->getSize().y/2;
	window->setMouseCursorVisible(false);

	int tmpX, tmpY;
	sf::Vector2i pos = sf::Mouse::getPosition(*window);
	tmpX = pos.x;
	tmpY = pos.y;

	camYaw += mouseVel*(MidX-tmpX);
	camPitch += mouseVel*(MidY-tmpY);

	lock();

	sf::Mouse::setPosition(sf::Vector2i(MidX,MidY),*window);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (camPitch != 90 && camPitch != -90) {
			moveXZ(moveVel,0.0);
			moveY(moveVel, 0.0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (camPitch != 90 && camPitch != -90) {
			moveXZ(moveVel,180.0);
			moveY(moveVel, 180.0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveXZ(moveVel,90.0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveXZ(moveVel,270.0);
	}

	glRotatef(-camPitch,1.0,0.0,0.0);
	glRotatef(-camYaw,0.0,1.0,0.0);
}

void Camera::Update() {
	glTranslatef(-camX, -camY, -camZ);
}
 *
 */
