 //Game.Desktop.OpenGL.cpp : Defines the entry point for the console application.slac
#include "pch.h"
#include "SList.h"
#include <fstream>
#include <iostream>
#include "soil.h"
#include "LevelManager.h"

using namespace std;
using namespace FieaGameEngine;

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	UNREFERENCED_PARAMETER(window);
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}
//
//
//int WINAPI WinMain(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine,
//	int nCmdShow)
//{
//
//	//Show that the shared library has been linked properly and that we can access it.
//	SList<int> list;
//	UNREFERENCED_PARAMETER(list);
//	UNREFERENCED_PARAMETER(hInstance);
//	UNREFERENCED_PARAMETER(hPrevInstance);
//	UNREFERENCED_PARAMETER(lpCmdLine);
//	UNREFERENCED_PARAMETER(nCmdShow);
//
//	//intialize glfw
//	glfwInit();
//	
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	//create a window object 
//	GLFWwindow* window = glfwCreateWindow(800, 800, "Window using OpenGL", NULL, NULL);
//	if (window == nullptr)
//	{
//		cout << "error creating the window" << endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);								//Set the context to be the created window
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))	//initialize glad
//	{
//		cout << "failed to intialize glad" << endl;
//		return -1;
//	}
//
//
//	//set the viewport dimensions
//	glViewport(0, 0, 800, 800);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending
//	glEnable(GL_BLEND);											// Enable Blending
//	glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
//	glEnable(GL_CULL_FACE);										// Remove Back Face
//
//	//register a callback function to resize the viewport whenever the window is resized
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	GLuint b = SOIL_load_OGL_texture("../../../../../Assets/Tiles/FlagTile2.PNG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
//		SOIL_FLAG_MIPMAPS);
//
//	GLuint c = SOIL_load_OGL_texture("../Assets/Tiles/Baba_character.PNG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
//		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
//
//
//	wchar_t buffer[MAX_PATH];
//	LPWSTR test = buffer;
//
//	GetModuleFileName(NULL, test, MAX_PATH);
//
//	test;
//	c;
//
//	glClearColor(0.0f, 0.3f, 0.5f, 1.0f);
//
//	while (!glfwWindowShouldClose(window))
//	{
//		glClear(GL_COLOR_BUFFER_BIT);
//		glLoadIdentity();
//		processInput(window);
//
//		//
//		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, b);
//		glBegin(GL_QUADS);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//		glTexCoord2f(0, 0);
//		glVertex3f(100, 100, 0.0);
//		glTexCoord2f(1, 0);
//		glVertex3f(200, 100, 0.0);
//		glTexCoord2f(1, 1);
//		glVertex3f(200, 200, 0.0);
//		glTexCoord2f(0, 1);
//		glVertex3f(100, 200, 0.0);
//		glEnd();
//		//
//
//		//glFlush();
//		glfwSwapBuffers(window);
//
//		
//		glfwPollEvents();
//	}
//	glfwTerminate();
//	return 0;
//}


/*
INVALID           0
IS_WORD           1
BABA_WORD         2
ROCK_WORD         3
FLAG_WORD         4
SKULL_WORD        5 
WALL_WORD         6
PUSH_WORD         7
STOP_WORD         8
DIE_WORD          9
WIN_WORD          10
YOU_WORD          11
BABA              12
ROCK              13 
FLAG              14
SKULL             15
WALL              16
BUSH              17
MAX
*/
				//0  1  2  3  4  5  6  7  8  9 10  11 12 13 14 15 16 17 18 19
int types[400] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//0
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//1
				  0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//2
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//3
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//4
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//5
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//6
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//7
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//8
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//9
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//10
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//11
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//12
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//13
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//14
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//15
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//16
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//17
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//18
				  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	//19

int main()
{
	ofstream file("Level5.json");
	file << "{" << "\n";
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (types[i * 20 + j] != 0)
			{
				std::string name = "\"Object";
				name.append(std::to_string((i * 20) + j));
				name.append("\" : {");
				file << name << "\n";

				file << "\"Type\" : \"Entity\"," << "\n";
				file << "\"ClassName\" : \"GameObject\"," <<"\n";
				file << "\"Value\" : {" << "\n";
				file << "\"Position\" : {" << "\n";
				file << "\"Type\" : \"Integer\"," <<"\n";
				file << "\"Value\" : [" << i << "," << j << "]" << "\n";
				file << "}," << "\n";
				file << "\"ObjectType\" : {" << "\n";
				file << "\"Type\" : \"Integer\"," << "\n";
				file << "\"Value\" : " << types[i * 20 + j] << "\n";
				file << "}" << "\n";
				file << "}" << "\n";
				file << "}," << "\n";
			}
		}
	}
	file << "}";
	return 0;
}