#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "Camera.h"

int draw(float delta);
int init();
void drawDice(float size);
void update(float delta, sf::Window *window);

int window_width = 800;
int window_height = 600;
float rot_angle = 0.01f;
float static normalizer = 100;

Camera cam;

int main()
{
	float delta = 0;

	sf::Window window(sf::VideoMode(window_width, window_height), "OpenGL Test", sf::Style::Default, sf::ContextSettings(32));
	//window.setFramerateLimit(120);
	//window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	init();
	sf::Mouse::setPosition(sf::Vector2i(window_width/2,window_height/2),window);
	sf::Clock clock;

	sf::Text fpstxt;

    bool running = true;
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
        	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
				running = false;
			}

        	if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::LAlt || event.key.code == sf::Keyboard::RAlt)) {
				cam.focus = false;
			}

        	if (event.MouseButtonPressed) {
        		cam.focus = true;
			}

        	if (event.type == sf::Event::LostFocus) {
				cam.focus = false;
			}else if (event.type == sf::Event::GainedFocus) {
				cam.focus = true;
				sf::Mouse::setPosition(sf::Vector2i(window_width/2,window_height/2),window);
			}

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
        delta = clock.restart().asSeconds();

        update(delta, &window);
        draw(delta);
        window.display();

        float fps = 1.f / delta;
        std::cout << "DELTA: "<< delta << "     FPS:" << fps <<  "        focus: " << cam.focus << std::endl;
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

	float dif[]={1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,dif);
	float amb[]={0.2,0.2,0.2,1,0};
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb);

	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_CULL_FACE);

	glViewport(0,0,window_width,window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)window_width/(GLfloat)window_height,0.1f,500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return 0;
}

void update(float delta, sf::Window* window){
	float velocity = (0.8*delta)*normalizer;
	float velocity2 = (0.2*delta)*normalizer;
	if (cam.focus) {
		cam.Control(velocity,velocity2,window);
	}
}

int draw(float delta){
	int count = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	int dist = 10;

	cam.Update();

	float pos[]={0.0,10.0,-10.0,1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	//Light source
	glPushMatrix();
		glTranslatef(pos[0],pos[1],pos[2]);
		drawDice(1.0f);
	glPopMatrix();

	for (int x = 0; x < 20; ++x) {
		glPushMatrix();
			glTranslatef(+x*dist,0.0f,-5.0f);
			glRotatef(rot_angle,1.0f,0.5f,0.0f);
			drawDice(1.0f);
			count ++;
		glPopMatrix();
		for (int y = 0; y < 10; ++y) {
			glPushMatrix();
				glTranslatef(x*dist,+y*dist,-5.0f);
				glRotatef(rot_angle,1.0f,0.5f,0.0f);
				drawDice(0.5f);
				count ++;
			glPopMatrix();

			for (int z = 0;z < 30; z++) {
				glPushMatrix();
					glTranslatef(x*dist,+y*dist,+z*dist);
					glRotatef(rot_angle,1.0f,0.5f,0.0f);
					drawDice(1.0f);
				glPopMatrix();
				count++;
			}
		}
	}

	for (int x = 0; x < 20; ++x) {
		glPushMatrix();
			glTranslatef(-x*dist,0.0f,-5.0f);
			glRotatef(rot_angle,1.0f,0.5f,0.0f);
			drawDice(1.0f);
			count++;
		glPopMatrix();
		for (int y = 0; y < 10; ++y) {
			glPushMatrix();
				glTranslatef(-x*dist,+y*dist,-5.0f);
				glRotatef(rot_angle,1.0f,0.5f,0.0f);
				drawDice(0.5f);
				count++;
			glPopMatrix();

			for (int z = 0;z < 30; z++) {
				glPushMatrix();
					glTranslatef(-x*dist,+y*dist,+z*dist);
					glRotatef(rot_angle,1.0f,0.5f,0.0f);
					drawDice(1.0f);
					count++;
				glPopMatrix();
			}
		}
	}

	float size = 100.0f;
	glPushMatrix();
		glTranslatef(0.0,-110.0,0.0);
		glBegin(GL_QUADS);
			glNormal3f(0.0,1.0,0.0);
			glColor3f(1.0f,1.0f,0.0f);
			glVertex3f(-size, size, size);
			glVertex3f(-size, size, -size);
			glVertex3f(size, size, -size);
			glVertex3f(size, size, size);
		glEnd();
	glPopMatrix();
	rot_angle+=100.0f*delta;

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
