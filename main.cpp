/*
	Copyright 2015 Ludwin Hernández
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    Crear cubo.
*/

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

//variables
double rotate_y=0;
double rotate_x=0;
double rotate_z=0;

GLfloat X = 0.0f;
GLfloat Y = 0.0f;
GLfloat Z = 0.0f;
GLfloat scale = 1.0f;


GLint ancho=800;
GLint alto=600;
int perspectiva = 0;

void reshape(int w, int h)
{
	glViewport(0, 0, w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glLoadIdentity();
	//glFrustum (-1.0, 1.0, -1.0, 1.0, 2.5, 50.0);
	gluPerspective(60.0, GLfloat(w) / GLfloat(h), 1.0, 20.0);
	 
	
	ancho = w;
    alto = h;
}

void display()
{
    //  Borrar pantalla y Z-buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Resetear transformaciones
    glLoadIdentity();
    // Rotar en el eje X,Y y Z
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    glScalef(scale, scale, scale);//Para alejar y acercar 
    
    glTranslatef(0.1,0.1,0); // se aplica gltranslatef para mover la tetera en x y 
    gluLookAt(0,0.5,0,0,0.2,0,0.5,0,0); // aplicnado gluLookAt para una vista de planta sobre la tetera 

    glColor3f(0,1,1); // Aplicamos color a la tetera 
    glutWireTeapot(0.4); // Agregarmos la tetera

    glFlush();
    glutSwapBuffers();

}

void init()
{
    glClearColor(0,0,0,0);
    // Habilitar la prueba de profundidad de Z-buffer
    glEnable(GL_DEPTH_TEST);
    ancho = 800;
    alto = 600;
}

// Función para controlar teclas especiales
void specialKeys( int key, int x, int y )
{

    //  Flecha derecha: aumentar rotación 7 grados
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;

    //  Flecha izquierda: rotación en eje Y negativo 7 grados
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    //  Flecha arriba: rotación en eje X positivo 7 grados
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    //  Flecha abajo: rotación en eje X negativo 7 grados
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    //  Tecla especial F2 : rotación en eje Z positivo 7 grados
    else if (key == GLUT_KEY_F2)
        rotate_z += 5;
    //  Solicitar actualización de visualización
    glutPostRedisplay();

}
// Función para controlar teclas normales del teclado.
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
    {
    case 'Z':
        scale-=0.5;
        break;
    case 'z':
        scale+=0.5;
        break;
     }
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{

    //  Inicializar los parámetros GLUT y de usuario proceso
    glutInit(&argc,argv);

    // Solicitar ventana con color real y doble buffer con Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutInitWindowSize(ancho, alto);
    // Crear ventana
    glutCreateWindow("Tetera rotacion giro y luz");
	init();
    // Funciones de retrollamada
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
	//Aplicando funciones 
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
    // Pasar el control de eventos a GLUT
    glutMainLoop();

    // Regresar 
    return 0;

}
