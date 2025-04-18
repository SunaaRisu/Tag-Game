#include <GL/glew.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __builtin_trap();
#define GLCall(x) GLClearError();x;ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError() {
  while (glGetError());
}

bool GLLogCall(const char *function, const char *file, int line) {
  while (GLenum error = glGetError()) {
    std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
    return false;
  }
  return true;
}
