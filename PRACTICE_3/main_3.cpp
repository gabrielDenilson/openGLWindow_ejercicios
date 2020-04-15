#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int ancho, int alto);
void processInput(GLFWwindow* window);

const unsigned int scr_width = 800;
const unsigned int scr_height = 600;

const char* vertexShaderCodigo = "#version 330 core \n"
"layout (location = 0) in vec3 aPos; \n"
"void main()\n"
"{\n"
"	gl_Position = vec4( aPos.x, aPos.y, aPos.z, 1.0); \n"
"} \0";

const char* fragmentShaderCodigo = "#version 330 core\n"
"out vec4 FragColor; \n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char* fragmentShaderAmarilloCodigo = "#version 330 core\n"
"out vec4 FragColor; \n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
"}\0";

void framebuffer_size_callback(GLFWwindow* window, int ancho, int alto) {
	glViewport(0, 0, ancho, alto);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* ventana = glfwCreateWindow(scr_width, scr_height, "Ejercicio 3", NULL, NULL);
	if (ventana == NULL) {
		std::cout << "Fallor la creacion de la ventana" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(ventana);
	glfwSetFramebufferSizeCallback(ventana, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Fallo al inicializar GLAD" << std::endl;
	}

	int exito;
	char infoLog[512];

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCodigo, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &exito);
	if (!exito) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error en el vertexShader " << infoLog << std::endl;
	}

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCodigo, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &exito);
	if (!exito) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Error en el fragmentShader " << infoLog << std::endl;
	}

	int fragmentAmarilloShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentAmarilloShader, 1, &fragmentShaderAmarilloCodigo, NULL);
	glCompileShader(fragmentAmarilloShader);

	glGetShaderiv(fragmentAmarilloShader, GL_COMPILE_STATUS, &exito);
	if (!exito) {
		glGetShaderInfoLog(fragmentAmarilloShader, 512, NULL, infoLog);
		std::cout << "Error en el fragmentShader " << infoLog << std::endl;
	}

	int shaderPrograma = glCreateProgram();
	glAttachShader(shaderPrograma, vertexShader);
	glAttachShader(shaderPrograma, fragmentShader);
	glLinkProgram(shaderPrograma);

	int shaderPrograma2 = glCreateProgram();
	glAttachShader(shaderPrograma2, vertexShader);
	glAttachShader(shaderPrograma2, fragmentAmarilloShader);
	glLinkProgram(shaderPrograma2);

	glGetProgramiv(shaderPrograma, GL_LINK_STATUS, &exito);
	if (!exito) {
		glGetShaderInfoLog(shaderPrograma, 512, NULL, infoLog);
		std::cout << "Error en el linkado de programa " << infoLog << std::endl;
	}

	glGetProgramiv(shaderPrograma2, GL_LINK_STATUS, &exito);
	if (!exito) {
		glGetShaderInfoLog(shaderPrograma2, 512, NULL, infoLog);
		std::cout << "Error en el linkado de programa " << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentAmarilloShader);

	//first triangle
	float mis_vertices[] = {
		0.4f, 0.3f, 0.0,
		0.8f, -0.4f, 0.0,
		0.0f, -0.4f, 0.0,
	};
	//second triangle
	float mis_vertices2[] = {
		0.0f, -0.4f, 0.0,
		-0.8f, -0.4f, 0.0,
		-0.4f, 0.3f, 0.0,
	};

	unsigned int VBO[2], VAO[2];

	glGenBuffers(2, VBO); //no need be referenced
	glGenVertexArrays(2, VAO);
	//firs triangle setup
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mis_vertices), mis_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mis_vertices2), mis_vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(ventana)) {
		processInput(ventana);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderPrograma);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(shaderPrograma2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(ventana);
		glfwPollEvents();
	}
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	//glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}