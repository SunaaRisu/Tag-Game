#include "Texture.h"

#include <Stitch/stitch.h>
#include <Stitch/gui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WIDTH 1080 //960  // 1080
#define HEIGHT 1080 //540 // 1080

int main() {
  Display display(WIDTH, HEIGHT, "Tag-Game");

  float positions[] = {
      -50.0f, -50.0f, 0.0f, 0.0f, // 0
       50.0f, -50.0f, 1.0f, 0.0f, // 1
       50.0f,  50.0f, 1.0f, 1.0f, // 2
      -50.0f,  50.0f, 0.0f, 1.0   // 3
  };

  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  
  VertexBufferLayout layout;
  layout.Push<float>(2);
  layout.Push<float>(2);

  VertexArray va(positions, 4 * 4 * sizeof(float), layout);

  IndexBuffer ib(indices, 6);

  glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(WIDTH), 0.0f, static_cast<float>(HEIGHT), -1.0f, 1.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

  Shader basicShader("res/shaders/texture.shader");
  basicShader.Bind();
  basicShader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

  Texture texture("res/textures/raccoon.png");
  texture.Bind();
  basicShader.SetUniform1i("u_Texture", 0);

  va.Unbind();
  ib.Unbind();
  basicShader.Unbind();

  Renderer renderer;

  Gui gui(display.GetWindow(), GUI_STYLE::CLASSIC);

  glm::vec3 translationA(200.0f, 200.0f, 0);
  glm::vec3 translationB(400.0f, 200.0f, 0);

  float r = 0.0f;
  float increment = 0.05f;

  while (!display.IsClosed()) {
    renderer.Clear();

    gui.Clear(); 

    {
      glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
      glm::mat4 mvp = proj * view * model;

      basicShader.Bind();
      basicShader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
      basicShader.SetUniformMat4f("u_MVP", mvp);
     
      renderer.Draw(va, ib, basicShader);
    }


    {
      glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
      glm::mat4 mvp = proj * view * model;

      basicShader.Bind();
      basicShader.SetUniform4f("u_Color", 0.3f, r, 0.3f, 1.0f);
      basicShader.SetUniformMat4f("u_MVP", mvp);
      
      renderer.Draw(va, ib, basicShader);
    }

    if (r > 1.0f)
      increment = -0.05f;
    else if (r < 0.0f)
      increment = 0.05f;

    r += increment;

    {// IMGUI STUFF
        ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, static_cast<float>(WIDTH)); // IMGUI STUFF
        ImGui::SliderFloat3("translation B", &translationB.x, 0.0f, static_cast<float>(WIDTH)); // IMGUI STUFF
    }

    gui.Draw();
    display.Update();
  }
}
