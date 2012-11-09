#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "Camera.h"

int draw(sf::Window * window);
int init();
void drawDice(float size);

int window_width = 800;
int window_height = 600;
float rot_angle = 0.01f;

Camera cam;

int main()
{
	sf::Window window(sf::VideoMode(window_width, window_height), "OpenGL Test", sf::Style::Default, sf::ContextSettings(32));

	init();

    bool running = true;
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
            	glViewport(0,0,event.size.width,event.size.height);

            	glMatrixMode(GL_PROJECTION);
            	glLoadIdentity();
            	gluPerspective(45.0f,(GLfloat)event.size.width/(GLfloat)event.size.height,0.1f,500.0f);
            	glMatrixMode(GL_MODELVIEW);
            	glLoadIdentity();

            }
        }

        draw(&window);

        window.display();
    }
    return 0;
}

int init(){
	cam = Camera();
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	float pos[]={0.0,10.0,-100.0,1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	float dif[]={1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,dif);
	float amb[]={0.2,0.2,0.2,1,0};
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb);

	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//glEnable(GL_CULL_FACE);

	glViewport(0,0,window_width,window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)window_width/(GLfloat)window_height,0.1f,500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return 0;
}

int draw(sf::Window* window){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	cam.Control(0.002,0.2,window);
	cam.Update();

	float pos[]={0.0,10.0,-100.0,1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	glPushMatrix();
		glTranslatef(0.0,10.0,-100);
		drawDice(1.0f);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f,0.0f,-1.0f);
		glRotatef(rot_angle,0.5f,0.5f,0.0f);
		drawDice(1.0f);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f,5.0f,-1.0f);
		glRotatef(rot_angle,0.5f,0.5f,0.5f);
		drawDice(1.0f);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(5.0f,5.0f,-1.0f);
		glRotatef(rot_angle,0.5f,0.5f,0.0f);
		drawDice(1.0f);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(5.0f,0.0f,-1.0f);
		glRotatef(rot_angle,1.0f,0.5f,0.0f);
		drawDice(1.0f);
	glPopMatrix();


	float size = 20.0f;
	glPushMatrix();
		glTranslatef(0.0,-25.0,0.0);
		glBegin(GL_QUADS);
			glNormal3f(0.0,1.0,0.0);
			glColor3f(1.0f,1.0f,0.0f);
			glVertex3f(-size, size, size);
			glVertex3f(-size, size, -size);
			glVertex3f(size, size, -size);
			glVertex3f(size, size, size);
		glEnd();
	glPopMatrix();
	rot_angle+=0.01f;
	return 1;
}

void drawDice(float size){
	glBegin(GL_QUADS);
		//Front
		glNormal3f(0.0,0.0,1.0);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-size, -size, size);
		glVertex3f(size, -size, size);
		glVertex3f(size, size, size);
		glVertex3f(-size, size, size);

		//Back
		glNormal3f(0.0,0.0,-1.0);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-size, -size, -size);
		glVertex3f(-size, size, -size);
		glVertex3f(size, size, -size);
		glVertex3f(size, -size, -size);

		//Left
		glNormal3f(-1.0,0.0,0.0);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-size, -size, size);
		glVertex3f(-size, size, size);
		glVertex3f(-size, size, -size);
		glVertex3f(-size, -size, -size);

		//Right
		glNormal3f(1.0,0.0,0.0);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(size, -size, size);
		glVertex3f(size, -size, -size);
		glVertex3f(size, size, -size);
		glVertex3f(size, size, size);

		//Top
		glNormal3f(0.0,1.0,0.0);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-size, size, size);
		glVertex3f(size, size, size);
		glVertex3f(size, size, -size);
		glVertex3f(-size, size, -size);

		//Bottom
		glNormal3f(0.0,-1.0,0.0);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-size, -size, size);
		glVertex3f(-size, -size, -size);
		glVertex3f(size, -size, -size);
		glVertex3f(size, -size, size);
	glEnd();
}
