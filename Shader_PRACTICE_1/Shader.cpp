#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		//abrir archivos
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;

		//leemos el buffer del archibo en los streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//cerramos los archivos
		vShaderFile.close();
		fShaderFile.close();

		//convertimos los stream en strings
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR!: los archivos de FILE SHADER no fueron leidos" << std::endl;
	}

	const char* vShaderCodigo = vertexCode.c_str();
	const char* fShaderCodigo = fragmentCode.c_str();

	//Compilamos y linkamos los shaders
	unsigned int vertex, fragment;
	int exito;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCodigo, NULL);
	glCompileShader(vertex);
	//errorssss
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &exito);
	if (!exito) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Error COMPILACION VERTEX\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCodigo, NULL);
	glCompileShader(fragment);
	//errorsss
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &exito);
	if (!exito) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Error COMPILACION FRAGMENT\n" << infoLog << std::endl;
	}

	//SHADER PROGRAM
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	//errorsssss
	glGetProgramiv(ID, GL_COMPILE_STATUS, &exito);
	if (!exito) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Error PROGRAMSHADER COMPILACION\n" << infoLog << std::endl;
	}
	//BORRAMOS
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{//especifica el valor de una variable uniforme para el programa actual
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
