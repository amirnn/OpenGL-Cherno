#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <Eigen/Eigen>
#include <Eigen/Geometry>

namespace
{
    using namespace std::string_literals;
    using namespace Eigen;

    std::string const vertex_shader_text =
        "#version 460 core\n"s +
        "uniform mat4 MVP;\n"s +
        "layout(location = 0) in vec3 vCol;\n"s +
        "layout(location = 1) in vec2 vPos;\n"s +
        "out vec3 color;\n"s +
        "void main()\n"s +
        "{\n"s +
        "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"s +
        "    color = vCol;\n"s +
        "}\n"s;

    std::string const fragment_shader_text =
        "#version 460 core\n"s +
        "in vec3 color;\n"s +
        "out vec4 fragment;\n"s +
        "void main()\n"s +
        "{\n"s +
        "    fragment = vec4(color, 1.0);\n"s +
        "}\n"s;


    Matrix4f mat4f_rotate_z(Matrix4f const M, float angle)
    {
        float s = sinf(angle);
        float c = cosf(angle);
        auto const R = Matrix4f
        {
            {   c,   s, 0.f, 0.f},
            {  -s,   c, 0.f, 0.f},
            { 0.f, 0.f, 1.f, 0.f},
            { 0.f, 0.f, 0.f, 1.f}
        };
        return M * R;
    }

    void mat4f_ortho(Matrix4f& M, float const l, float const r, float const b, float const t, float const n, float const f)
    {
        M(0, 0) = 2.f/(r-l);
        M(0, 1) = M(0, 2) = M(0, 3) = 0.f;
        M(1, 1) = 2.f/(t-b);
        M(1, 0) = M(1, 2) = M(1, 3) = 0.f;
        M(2, 2) = -2.f/(f-n);
        M(2, 0) = M(2, 1) = M(2 , 3) = 0.f;
        M(3, 0) = -(r+l)/(r-l);
        M(3, 1) = -(t+b)/(t-b);
        M(3, 2) = -(f+n)/(f-n);
        M(3, 3) = 1.f;
    }

}


GLuint gWidth = 1024;
GLuint gHeight = 768;
GLFWwindow* gWindow = nullptr;
GLuint gProgram = 0;
bool gShouldQuit = false;

GLuint g_vertex_array = 0;
GLint g_mvp_location = 0;
GLint g_vpos_location = 0;
GLint g_vcol_location = 0;

static void error_callback(int const error, char const* description)
{
    std::stringstream ss;
    ss << "Error: " << error << description << std::endl;
    std::cerr << ss.str();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void InitializeProgram()
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    gWindow = glfwCreateWindow(gWidth, gHeight, "OpenGL Triangle", NULL, NULL);

    if (!gWindow)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(gWindow, key_callback);

    glfwMakeContextCurrent(gWindow);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);
}

void CleanUp()
{
    glDeleteProgram(gProgram);
    glfwDestroyWindow(gWindow);
    glfwTerminate();
}

void VertexSpecification()
{
    using namespace Eigen;

    struct Vertex
    {
        Vector2f pos;
        Vector3f col;
    };

    static const Vertex vertices[3] =
    {
        {{-0.6f, -0.4f}, {1.f, 0.f, 0.f}},
        {{0.6f, -0.4f}, {0.f, 1.f, 0.f}},
        {{0.f, 0.6f}, {0.f, 0.f, 1.f}}
    };

    // Genereate a Vertex Buffer Object
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // provide the buffer data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    g_mvp_location = glGetUniformLocation(gProgram, "MVP");
    g_vpos_location = glGetAttribLocation(gProgram, "vPos");
    g_vcol_location = glGetAttribLocation(gProgram, "vCol");

    glGenVertexArrays(1, &g_vertex_array);
    glBindVertexArray(g_vertex_array);
    glEnableVertexAttribArray(g_vpos_location);
    glVertexAttribPointer(g_vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, pos)));
    glEnableVertexAttribArray(g_vcol_location);
    glVertexAttribPointer(g_vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, col)));
}

GLuint CreateGraphiscProgram(std::string const& vertexShaderSource, std::string const& fragmentShaderSource)
{
    GLuint const vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    GLchar const* vertexSourcePtr = vertexShaderSource.c_str();
    glShaderSource(vertex_shader, 1, &vertexSourcePtr, NULL);
    glCompileShader(vertex_shader);

    GLuint const fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    GLchar const* fragmentSourcePtr = fragmentShaderSource.c_str();
    glShaderSource(fragment_shader, 1, &fragmentSourcePtr, NULL);
    glCompileShader(fragment_shader);

    GLuint const program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    // Detach shaders
    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);

    // Delete the shaders
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

void CreateGraphicsPipeline()
{
    gProgram = CreateGraphiscProgram(vertex_shader_text, fragment_shader_text);
}

void GetEvents()
{
    gShouldQuit = glfwWindowShouldClose(gWindow);
    glfwPollEvents();
}



void PreDraw()
{
    // Do calculations

    int width, height;
    glfwGetFramebufferSize(gWindow, &width, &height);
    const float ratio = width / (float) height;

    Matrix4f m{}, p{}, mvp{};
    m = Matrix4f::Identity();
    auto rotated = mat4f_rotate_z(m, (float) glfwGetTime());
    mat4f_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mvp = p * rotated;

    // Use the desired pipeline
    glUseProgram(gProgram);
    glUniformMatrix4fv(g_mvp_location, 1, GL_FALSE, (GLfloat const*) &mvp);

    // Bind the vertex array
    glBindVertexArray(g_vertex_array);
}

void Draw()
{
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(gWindow);
}

void MainLoop()
{
    while (not gShouldQuit)
    {
        PreDraw();

        Draw();

        GetEvents();
    }
}

int main()
{
    // 1. Setup the Graphics Program
    InitializeProgram();

    // 2. Setup our Geometry
    VertexSpecification();

    // 3. Create our graphics pipeline
    CreateGraphicsPipeline();

    // 4. Call the main application loop
    MainLoop();

    // 5. Call the cleanup function when our program terminates
    CleanUp();

    return EXIT_SUCCESS;
}
