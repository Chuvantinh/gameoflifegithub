/** \mainpage OpenMP main page
 * @brief A main class only for game of life with openMP
 * @return void
 */

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
// #include "../config/ConfigFile.h"
#include <fstream>
#include <algorithm>

#include <iostream>

//! A define variable.
/*!
    Define colors of the game
	white for backroun
	black for the display of element.
*/
#define WHITE 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0

//! Default will be declared here but after reading 
//! values are read from "config/game.txt"
GLint FPS = 24;
GLint window_width = 900;
GLint window_height = 600;
GLfloat left = 0.0;
GLfloat right = 1.0;
GLfloat bottom = 0.0;
GLfloat top = 1.0;
GLint game_width = 100;
GLint game_height = 100;
int count = 0;
double zoom = 1.0;
int OMP_NUM_THREADS;//! NUMBER OF THREADS FOR OPENMP

GameOfLife *game; //! Object of game and can use for all methode

//! http://math.hws.edu/graphicsbook/c3/s1.html#:~:text=The%20function%20glVertex2f%20specifies%20the,are%20passed%20to%20the%20function.
//! A callback function
/**
 * glutDisplayFunc sets the display callback for the current window.
 * glutDisplayFunc sets the display callback for the current window. 
 * When GLUT determines that the normal plane for the window needs to be redisplayed, 
 * the display callback for the window is called. Before the callback, 
 * the current window is set to the window needing to be redisplayed and 
 * (if no overlay display callback is registered) the layer in use is set to the normal plane. 
 * The display callback is called with no parameters.
 * The entire normal plane region should be redisplayed in response to the callback (this includes ancillary buffers if your program depends on their state).
 * @param int width
 * @param int height
 * @return void
 */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
    GLfloat xSize = (right - left) / ( game_width * 1 );
	GLfloat ySize = (top - bottom) / ( game_height * 1);
	
	glBegin(GL_QUADS);
	for (GLint x = 0; x < game_width; ++x) {
		for (GLint y = 0; y < game_height; ++y) {
            game->getElement(x, y)?glColor3f(BLACK):glColor3f(WHITE); // draw color for quads 
            /*
			 * Just print element to see 
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


/**
 * glutReshapeFunc sets the reshape callback for the current window.
 * @param : int width
 * @paramterte int height
 * @return void
*/
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

/**
 * glutTimerFunc callbackfunction and afer time
 * glutPostRedisplay marks the current window as needing to be redisplayed.
 * @param int value 
 * @return void
*/
void update(int value) {
	count = count + 1;
	std::cout << " intertor : " << count <<std::endl; 
	game->iterate();

	glutPostRedisplay();
	glutTimerFunc(2000, update, 0);
}

/**
 * Event crt and scroll up or ow to see more detail of the element on the grid
 * @param : int button, int state, int x, int y 
 * @return void
*/
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

/**
	* get config file from txt file
	* instruction from: https://www.walletfox.com/course/parseconfigfile.php
	* stoi() convert string to int
*/
void getConfigFile(){
		 // std::ifstream is RAII, i.e. no need to call close
    std::ifstream cFile ("config/game.txt");
    if (cFile.is_open())
    {
        std::string line;
        while(getline(cFile, line)){
            line.erase(std::remove_if(line.begin(), line.end(), isspace),
                                 line.end());
            if(line[0] == '#' || line.empty())
                continue;
            auto delimiterPos = line.find("=");
            auto name = line.substr(0, delimiterPos);
            auto value = line.substr(delimiterPos + 1);
            // std::cout << name << "=" << value << '\n';
			if(name=="fps"){FPS = stoi(value);}
			if(name=="windowWidth"){window_width = stoi(value);}
			if(name=="windowHeight"){window_height = stoi(value);}

			if(name=="left"){left = stoi(value);}
			if(name == "right"){right = stoi(value);}
			if(name == "bottom"){bottom = stoi(value);}
			if(name == "top"){top = stoi(value);}

			if(name == "gameWidth"){game_width = stoi(value);}
			if(name == "gameHeight"){ game_height = stoi(value);}
			if(name == "OMP_NUM_THREADS"){ OMP_NUM_THREADS = stoi(value);}
        }
        
    }
    else {
        std::cerr << "Couldn't open config file for reading.\n";
    }
}

/**
 * A main function only for openMP
 * work follow: getconfig
 * init object
 * show gird 
 * update grid
 * glutmainloop to wait funcion
 * finish
*/
int main(int argc, char **argv) {
	getConfigFile();
	game = new GameOfLife(game_width, game_height);
	game->randomInit();

	// game->printGrid();
  	glutInit(&argc, argv);
     
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Game of Life with OpenMP");
	glClearColor(1, 1, 1, 1);

	glutMouseFunc(mouse);
	 
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	game->iterate();

	glutPostRedisplay();
	glutPostRedisplay();
	// glutTimerFunc(2000, update, 0);

	// update(0); // ko can cap nhat gui
	glutMainLoop();
		
  	return 0;
}
