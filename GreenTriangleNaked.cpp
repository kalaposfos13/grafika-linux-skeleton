//=============================================================================================
// Z�ld h�romsz�g: puc�r, l�bbal hajt�s megold�s
//=============================================================================================
#include "framework.h"

// cs�cspont �rnyal�
const char * vertSource = R"(
	#version 330				
    precision highp float;

	layout(location = 0) in vec2 cP;	// 0. bemeneti regiszter

	void main() {
		gl_Position = vec4(cP.x, cP.y, 0, 1); 	// bemenet m�r normaliz�lt eszk�zkoordin�t�kban
	}
)";

// pixel �rnyal�
const char * fragSource = R"(
	#version 330
    precision highp float;

	uniform vec3 color;			// konstans sz�n
	out vec4 fragmentColor;		// pixel sz�n

	void main() {
		fragmentColor = vec4(color, 1); // RGB -> RGBA
	}
)";

const int winWidth = 600, winHeight = 600;

class GreenTriangleApp : public glApp {
	unsigned int vao;   // geometria
	unsigned int prog;	// cs�cspont �s pixel �rnyal�k
public:
	GreenTriangleApp() : glApp("Green triangle") { }

	// Inicializ�ci�, 
	void onInitialization() {
		glGenVertexArrays(1, &vao);	// egy vao azonos�t� k�r�se
		glBindVertexArray(vao);		// a kapott vao-t aktiv�ljuk
		
		unsigned int vbo;
		glGenBuffers(1, &vbo);		// egy vbo azonos�t� k�r�se
		glBindBuffer(GL_ARRAY_BUFFER, vbo); // a kapott vbo-t aktiv�ljuk

		// Geometria 24 b�jttal (6 float vagy 3x2 koordin�ta)
		float vertices[] = { -0.8f, -0.8f, -0.6f, 1.0f, 0.8f, -0.2f };
		glBufferData(GL_ARRAY_BUFFER, 	// VBO GPU-ra m�sol�sa
			         sizeof(vertices), vertices,	// m�solt b�jtok sz�ma �s c�me
			         GL_STATIC_DRAW);	// nem fogjuk m�dos�tani

		glEnableVertexAttribArray(0);  	// 0. regiszter enged�lyez�se
		glVertexAttribPointer(0,   		// vbo -> 0. regiszter
			                  2, GL_FLOAT, GL_FALSE, // 2 float/nem fix pontos
			                  0, NULL); 	// t�m�ren pakolt

 		// Cs�cspont �rnyal�: azonos�t� gener�l�s, forr�s felt�lt�s, ford�t�s 
		unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertShader, 1, &vertSource, NULL);
		glCompileShader(vertShader);

		// Pixel �rnyal�: azonos�t� gener�l�s, forr�s felt�lt�s, ford�t�s 
		unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragSource, NULL);
		glCompileShader(fragShader);

		// Program = cs�cspont-pixel�rnyal� p�r l�trehoz�sa
		prog = glCreateProgram();
		glAttachShader(prog, vertShader);
		glAttachShader(prog, fragShader);
		glLinkProgram(prog); // a cs�cspont-pixel�rnyal� p�r szerkeszt�se
		glUseProgram(prog);  // ez fusson
	}

	// Ablak �jrarajzol�s
	void onDisplay() {
		glClearColor(0, 0, 0, 0);     // h�tt�r sz�n
		glClear(GL_COLOR_BUFFER_BIT); // rasztert�r t�rl�s
		glViewport(0, 0, winWidth, winHeight);

		int location = glGetUniformLocation(prog, "color");
		glUniform3f(location, 0.0f, 1.0f, 0.0f); // 3 float, z�ld sz�n

		glBindVertexArray(vao);  // Rajzol�si h�v�s
		glDrawArrays(GL_TRIANGLES, 0 /* start index */, 3 /* elem sz�m */);
	}
} app;

