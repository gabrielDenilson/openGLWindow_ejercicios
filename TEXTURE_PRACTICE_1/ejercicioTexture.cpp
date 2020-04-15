#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"

#include "stb_image.h"

void frameBuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);

const unsigned int scr_widht = 800;
const unsigned int scr_height = 600;

float tono = 0.2f;

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* my_ventana = glfwCreateWindow(scr_widht, scr_height, "MI TEXTURA", NULL, NULL);
	if (my_ventana == NULL) {
		std::cout << "CrearVentana ERROR " << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(my_ventana);
	glfwSetFramebufferSizeCallback(my_ventana, frameBuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "No se cargo glad correctamente" << std::endl;
		return -1;
	}

	Shader misShaders("C:/Users/GabrielSinn/OneDrive/Documentos/Visual Studio 2019/learnOpenGL/openWindow/TEXTURE_PRACTICE_1/vertexTex_ejercicio.vert",
		"C:/Users/GabrielSinn/OneDrive/Documentos/Visual Studio 2019/learnOpenGL/openWindow/TEXTURE_PRACTICE_1/fragmentTex_ejercicio.frag");
	
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.7f,  0.7f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.7f, -0.7f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.7f, -0.7f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.7f,  0.7f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// LOS BINDS
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// LOS ATTRIBS
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// LOS UNBINDINGs
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	unsigned int textura1, textura2;

	//Establecemos la primera textura
	glGenTextures(1, &textura1);
	glBindTexture(GL_TEXTURE_2D, textura1);

	//Configuramos la textura WRAPPING/FILTERING
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//WRAPPING
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//WRAPPING
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//FILTERING (MIPMAP)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//FILTERING

	int width, height, nrCanales;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* dataImage = stbi_load("C:/Users/GabrielSinn/OneDrive/Documentos/Visual Studio 2019/learnOpenGL/openWindow/TEXTURES_LEARN/spaceHoleStar.jpg",
		&width, &height, &nrCanales, 0);

	if (dataImage) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataImage);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Error al cargar la imagen" << std::endl;
		return -1;
	}
	stbi_image_free(dataImage);

	//Establecemos la  segunda textura
	glGenTextures(1, &textura2);
	glBindTexture(GL_TEXTURE_2D, textura2);

	//Configuramos la textura WRAPPING/FILTERING
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//WRAPPING
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//WRAPPING
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//FILTERING (MIPMAP)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//FILTERING

	dataImage = stbi_load("C:/Users/GabrielSinn/OneDrive/Documentos/Visual Studio 2019/learnOpenGL/openWindow/TEXTURES_LEARN/carSagan.jpg",
		&width, &height, &nrCanales, 0);
	if (dataImage) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataImage);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Error al cargar la imagen" << std::endl;
		return -1;
	}
	stbi_image_free(dataImage);

	misShaders.use();
	glUniform1i(glGetUniformLocation(misShaders.ID, "mi_textura_0"), 0);
	misShaders.setInt("mi_textura_1", 1);

	while (!glfwWindowShouldClose(my_ventana))
	{
		processInput(my_ventana);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textura1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textura2);

		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;

		glUniform1f(glGetUniformLocation(misShaders.ID, "miMix"), greenValue);

		misShaders.use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(my_ventana);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void frameBuffer_size_callback(GLFWwindow* ventana, int width, int height) {
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* ventana) {
	//Tecla escape cierra la ventana
	if (glfwGetKey(ventana, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(ventana, true);
	}
	//Tecla arriba sube el tono 
	if (glfwGetKey(ventana, GLFW_KEY_UP) == GLFW_PRESS) {
		tono = tono + 0.005f;
		std::cout << "arriba" << std::endl;
		if (tono >= 1.0f)
		{
			tono = 1.0f;
		}
	}
	//Tecla abajo baja el tono
	if (glfwGetKey(ventana, GLFW_KEY_DOWN) == GLFW_PRESS) {
		tono = tono - 0.005f;
		std::cout << "abajo" << std::endl;
		if (tono < 0.0f)
		{
			tono = 0.0f;
		}
	}
}