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

	GLFWwindow* ventana = glfwCreateWindow(scr_width, scr_height, "Ejercicio 1", NULL, NULL);
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

	int shaderPrograma = glCreateProgram();
	glAttachShader(shaderPrograma, vertexShader);
	glAttachShader(shaderPrograma, fragmentShader);
	glLinkProgram(shaderPrograma);

	glGetProgramiv(shaderPrograma, GL_LINK_STATUS, &exito);
	if (!exito) {
		glGetShaderInfoLog(shaderPrograma, 512, NULL, infoLog);
		std::cout << "Error en el linkado de programa " << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float mis_vertices[] = {
		0.4f, 0.3f, 0.0,
		0.8f, -0.4f, 0.0,
		0.0f, -0.4f, 0.0,
		//segundo triangulo
		0.0f, -0.4f, 0.0,
		-0.8f, -0.4f, 0.0,
		-0.4f, 0.3f, 0.0,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 4
	};

	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mis_vertices), mis_vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(ventana)) {
		processInput(ventana);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderPrograma);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glfwSwapBuffers(ventana);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}