#include <Stitch/stitch.h>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderCherno.h"

#define WIDTH 1080
#define HEIGHT 1080

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

  VertexArray va;
  VertexBuffer vb(positions, 4 * 2 * sizeof(float));

  VertexBufferLayout layout;
  layout.Push<float>(2);
  va.AddBuffer(vb, layout);

  IndexBuffer ib(indices, 6);

  ShaderCherno basicShader("res/shaders/basic.shader");
  basicShader.Bind();
  basicShader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

  va.Unbind();
  vb.Unbind();
  ib.Unbind();
  basicShader.Unbind();
 
  float r = 0.0f;
  float increment = 0.05f;

  while (!display.IsClosed()) {
    display.Clear(0.1f, 0.1f, 0.1f, 1.0f);
    
    basicShader.Bind();
    basicShader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

    va.Bind();
    ib.Bind(); 

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

    if (r > 1.0f)
      increment = -0.05f;
    else if (r < 0.0f)
      increment = 0.05f;

    r += increment;

    display.Update();
  }
}
