/*
Programul afiseaza un patrat pe care il translateaza pe axa x la apasarea sagetilor stanga, dreapta
*/
#include "glos.h"
#include "gl.h"
#include "glu.h"
#include "glaux.h"
#include "glut.h"
#define PI 3.1415;

static GLfloat x = 0;
static GLfloat y = 0;
static GLfloat z = 10;
static GLfloat alpha =0;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void CALLBACK MoveLeft()
{
    x -= 10;
}

void CALLBACK MoveRight()
{
    x += 10;
}

void CALLBACK MoveDown() {
    y -= 10;
}

void CALLBACK MoveUp() {
    y += 10;
}

void CALLBACK rot_z_up(AUX_EVENTREC* event) {
    alpha -= 5;
}

void CALLBACK rot_z_down(AUX_EVENTREC* event) {
    alpha += 5;
}

void CALLBACK display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_QUADS);
    {
        

    }

    glEnd();
    
    glFlush();
}



#define ISOTROPIC
#ifdef ISOTROPIC
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) {
        return;
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        glOrtho(0.0, 320.0, 320.0 * (GLfloat)h / (GLfloat)w,0.0 * (GLfloat)h / (GLfloat)w, -100.0, 100.0);
    }
    else {
        glOrtho(0.0 * (GLfloat)w / (GLfloat)h, 320.0 * (GLfloat)w / (GLfloat)h, 0, 320.0, -100.0, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
}
#else
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;			//transformare anizotropica, forma se modifica functie de forma(dimens) viewportului
    glViewport(0, 0, w, h);	//daca w>h stabilim ca baza inaltime, si stab unit logica de dimens in fct de h(h/320, 320 lungime lat patrat)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-160.0, 160.0, -160.0, 160.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}
#endif

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
    auxInitPosition(0, 0, 800, 600);
    auxInitWindow("Square");
    myInit();
    auxKeyFunc(AUX_LEFT, MoveLeft);
    auxKeyFunc(AUX_RIGHT, MoveRight);
    auxKeyFunc(AUX_UP, MoveUp);
    auxKeyFunc(AUX_DOWN, MoveDown);

    auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_z_down);
    auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEDOWN, rot_z_up);


    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}
