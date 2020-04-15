#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

// ################ VERTEX INPUT ####################
    // asignamos los valores del vertice
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    unsigned int VBO; //para los datos
    unsigned int VAO; // puede ser bound(ligado) como un VBO

    glGenBuffers(1, &VBO); // para generar su ID en el buffer

    glGenVertexArrays(1, &VAO); //es todo lo que se hace para usar el VAO

    glBindVertexArray(VAO);

    //OGL allow bind to several while the type (GL_ARRAY_BUFFER) are diferent
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Enlazamos el buffer

    //Copia nuestro vertex definido en la memoria del buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //ahora tenemos almacenado el vertexData en la memoria grafica
// ################ VERTEX INPUT END ####################

// ################ VERTEX SHADER ####################
    //Compiling shader
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    //Creamos un shaderObject
    unsigned int vertexShader;
    //le decimos el type of shader que queremos crear en el argumento
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Adjuntmos el codigoShader al objectShader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //!!!!!!!!!!!!! verificacion de error de compilacion
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR: compilation shader failed\n" << infoLog << std::endl;
    }
//!!!!!!!!!!!!!!!!!!!!
// ################ VERTEX SHADER ####################

// ################ FRAGMENT SHADER ####################
    //Codigo del fragment shader
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";
    //Creamos un shaderObject
    unsigned int fragmentShader;
    //le decimos el type of shader que queremos crear en el argumento
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Adjuntmos el codigoShader al objectShader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //!!!!!!!!!!!!! verificacion de error de compilacion
    int success_fragment;
    char infoLog_fragment[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success_fragment);
    if (!success_fragment) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog_fragment);
        std::cout << "ERROR: compilation fragment shader failed\n" << infoLog_fragment << std::endl;
    }
    //!!!!!!!!!!!!!!!!!!!!!!!
    //*********** shader program *******************
        // Final linked version of multiple shaders combined
    unsigned int shaderProgram;
    //Crea un programObject y nos devuelve su ID
    shaderProgram = glCreateProgram();
    // Adjuntamos los shaders compilados al programa
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Los enlazamos
    glLinkProgram(shaderProgram);
//!!!!!!!!!!!!!! error check
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success_fragment)
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog_fragment);
        std::cout << "ERROR: compilation shader program failed\n" << infoLog_fragment << std::endl;
    }
//!!!!!!!!!!!!!!
    //No olvidar que todo shader and rendering se hace antes de esto
    //Activamos el programObject y solo trabajaremos con el

                //glUseProgram(shaderProgram);

    //Eliminamos los shader objects una vez vinculados al programObject
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //*********** shader program *******************

            //glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Ungind el VAO para que otros VAO's no modifiquen este VAO
            //glBindVertexArray(0);
// ################ FRAGMENT SHADER ####################

// ################ LINKING VERTEX ATTRIBUTES ####################
    //Decimos a OGL cual dato va a que vertexAttribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //Enable the vertex atribute
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
// ################ LINKING VERTEX ATTRIBUTES ####################

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Dibujando el triangulo
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}