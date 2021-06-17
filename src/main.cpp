#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

#include "GameOfLife.h"
#include "../config/ConfigFile.h"

#include <iostream>


#define WHITE 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0

// values are read from "game.config"
GLint FPS = 24;
GLint window_width = 512;
GLint window_height = 512;
GLfloat left = 0.0;
GLfloat right = 1.0;
GLfloat bottom = 0.0;
GLfloat top = 1.0;
GLint game_width = 100;
GLint game_height = 100;
int count = 0;
double zoom = 1.0;

GameOfLife *game;

// http://math.hws.edu/graphicsbook/c3/s1.html#:~:text=The%20function%20glVertex2f%20specifies%20the,are%20passed%20to%20the%20function.
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
    GLfloat xSize = (right - left) / ( game_width * 1 );
	GLfloat ySize = (top - bottom) / ( game_height * 1);
	
	glBegin(GL_QUADS);
	for (GLint x = 0; x < game_width; ++x) {
		for (GLint y = 0; y < game_height; ++y) {
            game->getElement(x, y)?glColor3f(BLACK):glColor3f(WHITE); // draw color for quads 
            /**
			// if(y == 1 or y == 99){
			// 	std::cout << " 1: " << x*xSize+left << "," << y*ySize+bottom  << std::endl; 
			// 	std::cout << " 2: " << (x+1)*xSize+left << ", " << y*ySize+bottom <<std::endl; 

			// 	std::cout << " 3: " << (x+1)*xSize+left << ", " << (y+1)*ySize+bottom <<std::endl; 
			// 	std::cout << " 4: " << (x)*xSize+left << ", " << (y+1)*ySize+bottom <<std::endl; 

					
			// 	// y = 1 column 11: 0.93, 0.01
			// 	//2: 0.94, 0.01
			// 	//3: 0.94, 0.02
			// 	//4: 0.93, 0.02
			// 	// y = 99 
			// 	// 1: 0.95,0.99
			// 	//2: 0.96, 0.99
			// 	//3: 0.96, 1
			// 	//4: 0.95, 1
			// }
			*/
			
			glVertex2f(    x*xSize+left,    y*ySize+bottom);
			glVertex2f((x+1)*xSize+left,    y*ySize+bottom);
			glVertex2f((x+1)*xSize+left,(y+1)*ySize+bottom);
			glVertex2f(    x*xSize+left,(y+1)*ySize+bottom);
		}
	}
	glEnd();

	// write line vertical
	glBegin(GL_LINES);
		glColor3ub(180,170,168);
		for (GLint x = 0; x < game_width; ++x) {
			for (GLint y = 0; y < game_height; ++y) {
				glVertex2f(    x*xSize+left,    y*ySize+bottom);
				//glVertex2f((x+1)*xSize+left,    y*ySize+bottom);
				//glVertex2f((x+1)*xSize+left,(y+1)*ySize+bottom);
				glVertex2f(    x*xSize+left,(y+1)*ySize+bottom);
			}
		}
	glEnd();

	// write line horizon
	glBegin(GL_LINES);
		glColor3ub(180,170,168);
		for (GLint x = 0; x < game_width; ++x) {
			for (GLint y = 0; y < game_height; ++y) {
				glVertex2f(    x*xSize+left,    y*ySize+bottom);
				glVertex2f((x+1)*xSize+left,    y*ySize+bottom);
				//glVertex2f((x+1)*xSize+left,(y+1)*ySize+bottom);
				//glVertex2f(    x*xSize+left,(y+1)*ySize+bottom);
			}
		}
	glEnd();
    	
	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	window_width = w;
	window_height = h;

	glViewport(0, 0, window_width, window_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

void update(int value) {
	//count = count + 1;
	//std::cout << " vong lap: " << count <<std::endl; 
	game->iterate();

	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, update, 0);
}

void readConfiguration(char* file) {
	ConfigFile config(file);
	
	config.readInto(FPS, "fps" );
	
	config.readInto(window_width, "window_width");
	config.readInto(window_height, "window_height");
	
	config.readInto(left, "left" );
	config.readInto(right, "right" );
	config.readInto(bottom, "bottom" );
	config.readInto(top, "top" );
	
	config.readInto(game_width, "game_width" );
	config.readInto(game_height, "game_height" );
}

bool checkConfiguration() {
	if (left > right) {
		std::cout << "Ortographic projection values error: 'left' must be less than 'right'" << std::endl;
		return false;
	}
	if (bottom > top) {
		std::cout << "Ortographic projection values error: 'bottom' must be less than 'top'" << std::endl;
		return false;
	}
	if (window_width <= 0 || window_height <= 0 || game_width <= 0 || game_height <= 0) {
		std::cout << "The window's and game's 'width' and 'height' must be greater than 0" << std::endl;
		return false;
	}
	if (game_width >= window_width || game_height >= window_height) {
		std::cout << "Try reducing the game dimensions or increasing the window size for a better visualization" << std::endl;
	}
	
	return true;
}

void mouse(int button, int state, int x, int y)
{
    // Wheel reports as button 3(scroll up) and button 4(scroll down)
    if ((button == 3) || (button == 4)) // It's a wheel event
    {
        // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
        if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
        //printf("Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y);

        if(button == 3)
            zoom += 0.1;
        else
            zoom -= 0.1;

        if(zoom < 0) zoom = 0.1;

        GLfloat aspect = (GLfloat)window_width / (GLfloat)window_height;

        if(window_width >= window_height)
        {
            left = (GLfloat)x / window_width - 2.0 / zoom;
            right = (GLfloat)x / window_width + 2.0 / zoom;
            top = (GLfloat)y / window_height / aspect + 2.0 / zoom;
            bottom = (GLfloat)y / window_height / aspect - 2.0 / zoom;
        }
        else
        {
            left = (GLfloat)x / window_width * aspect - 2.0 / zoom;
            right = (GLfloat)x / window_width * aspect + 2.0 / zoom;
            top = (GLfloat)y / window_height + 2.0 / zoom;
            bottom = (GLfloat)y / window_height - 2.0 / zoom;
        }

    }else{  // normal button event
        //printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
    }
}

int main(int argc, char **argv) {
	game = new GameOfLife(game_width, game_height);
	game->randomInit();

	// game->printGrid();
  	glutInit(&argc, argv);
	
	if (argc > 1) {
		readConfiguration(argv[1]);
	}
	
	if (!checkConfiguration()) {
		return 0;
	}
     
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Game of Life with OpenMP");
	glClearColor(1, 1, 1, 1);

	 glutMouseFunc(mouse);
	 
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	update(0);
	glutMainLoop();
		
  	return 0;
}
