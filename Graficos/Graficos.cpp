// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include <iostream>
using namespace std;

//Declaración de Ventana
GLFWwindow *window;

GLfloat red, green, blue;
GLfloat ty = 0.0f;
GLfloat tx = 0.0f;

double tiempoAnterior = 0.0f;
double velocidad = 0.1f;
double angulo = 0.2f;

void actualizar()
{
	//Aqui esta bien para actualizar los valores
	//De la version del programa!
	double tiempoActual = glfwGetTime();
	double tiempoTrancurrido = tiempoActual - tiempoAnterior;

	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS)
	{
		if (ty < 1)
			ty += velocidad * tiempoTrancurrido;
	}

	int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajo == GLFW_PRESS)
	{
		if (ty > -1)
			ty -= velocidad * tiempoTrancurrido;
	}

	tiempoAnterior = tiempoActual;

}

void dibujar()
{
	glPushMatrix();

	glTranslatef(tx, ty, 0.0f);
	glScalef(0.08f, 0.08f, 0.08f);

	glBegin(GL_TRIANGLES); //Inicia la rutina con un modo de dibujo
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd(); // Finaliza la rutina
	glPopMatrix();
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (ty < 0.9)
		{
			ty += 0.05f;
		}
	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (ty > -0.9)
		{
			ty -= 0.05f;
		}
	}

	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (tx < 0.9)
		{
			tx += 0.05f;
		}
	}

	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		if (tx > -0.9)
		{
			tx -= 0.05f;
		}
	}
}

int main()
{
	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 768;

	//Inicialización de GLFW
	if (!glfwInit())
	{
		//Si no se inicia bien termina la ejecución
		exit(EXIT_FAILURE);
	}

	//Inicialización de la ventana
	window = glfwCreateWindow(ancho, alto, "Gráficos", NULL, NULL);

	//Verificación de creación de ventana
	if (!window)
	{
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecución
		exit(EXIT_FAILURE);
	}


	//Establecer "windows" como contexto
	glfwMakeContextCurrent(window);

	//Se trae las funciones de OpenGL Moderno
	glewExperimental = true;

	//Inicializar GLEW
	GLenum glewError = glewInit();

	//Verificar si GLEW se inicializo bien
	if (glewError != GLEW_OK)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL:" << version << endl;

	red = green = blue = 0.0f;

	//glfwSetKeyCallback(window, key_callback);

	tiempoAnterior = glfwGetTime();

	//Ciclo de Dibujo
	while (!glfwWindowShouldClose(window))
	{
		//Establecer el area de render (viewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia
		glClearColor(red, green, blue, 1);

		

		
		//Limpiar pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de Dibujo
		actualizar();
		dibujar();

		//Intercambio de Buffers
		glfwSwapBuffers(window);
		//Buscar nueva señal de entrada
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

