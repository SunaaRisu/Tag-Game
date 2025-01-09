#include <Stitch/stitch.h>
#include <iostream>

#define WIDTH 1080
#define HEIGHT 1080

#define ASSERT(x) if (!(x)) __builtin_trap();
#define GLCall(x) GLClearError();x;ASSERT(GLLogCall(#x, __FILE__, __LINE__));

static void GLClearError() {
  while (glGetError());
}

static bool GLLogCall(const char* function, const char* file, int line) {
  while (GLenum error = glGetError()) {
    std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
    return false;
  }
  return true;
}

int main() {
  Display display(WIDTH, HEIGHT, "Tag-Game");

  float positions[] = {
    -0.5f, -0.5f,
     0.5f, -0.5f, 
     0.5f,  0.5f,
    -0.5f,  0.5f
  };

  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
  };

  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
  glEnableVertexAttribArray(0);

  unsigned int indexBufferObject;
  glGenBuffers(1, &indexBufferObject);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

  Shader basicShader("res/shaders/basic.shader");
  basicShader.Bind();

  int location = basicShader.GetUniformLocation("u_Color");
  ASSERT(location != -1);
  GLCall(glUniform4f(location, 1.0f, 0.0f, 1.0f, 1.0f));
 
  float r = 0.0f;
  float increment = 0.05f;

  while (!display.IsClosed()) {
    display.Clear(0.1f, 0.1f, 0.1f, 1.0f);
    
    GLCall(glUniform4f(location, r, 0.0f, 1.0f, 1.0f));
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

    if (r > 1.0f)
      increment = -0.05f;
    else if (r < 0.0f)
      increment = 0.05f;

    r += increment;

    display.Update();
  }

  return 0;
}
