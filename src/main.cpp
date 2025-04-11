#include "IndexBuffer.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <Stitch/stitch.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "vendor/imGui/imgui.h"
#include "vendor/imGui/imgui_impl_glfw.h"
#include "vendor/imGui/imgui_impl_opengl3.h"

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

  GLCall(glEnable(GL_BLEND));
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  VertexArray va;
  VertexBuffer vb(positions, 4 * 4 * sizeof(float));

  VertexBufferLayout layout;
  layout.Push<float>(2);
  layout.Push<float>(2);
  va.AddBuffer(vb, layout);

  IndexBuffer ib(indices, 6);

  glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(WIDTH), 0.0f, static_cast<float>(HEIGHT), -1.0f, 1.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

  Shader testShader("res/shaders/basic.shader");
  testShader.Bind();
  testShader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

  Shader basicShader("res/shaders/texture.shader");
  basicShader.Bind();
  basicShader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

  Texture texture("res/textures/raccoon.png");
  texture.Bind();
  basicShader.SetUniform1i("u_Texture", 0);

  va.Unbind();
  vb.Unbind();
  ib.Unbind();
  basicShader.Unbind();
  testShader.Unbind();

  Renderer renderer;

  ImGui::CreateContext(); // IMGUI STUFF
  ImGui_ImplGlfw_InitForOpenGL(display.m_window, true); // IMGUI STUFF
  ImGui_ImplOpenGL3_Init("#version 130"); // IMGUI STUFF
  ImGui::StyleColorsDark(); // IMGUI STUFF

  glm::vec3 translationA(200.0f, 200.0f, 0);
  glm::vec3 translationB(400.0f, 200.0f, 0);

  float r = 0.0f;
  float increment = 0.05f;

  while (!display.IsClosed()) {
    renderer.Clear();

    ImGui_ImplOpenGL3_NewFrame(); // IMGUI STUFF
    ImGui_ImplGlfw_NewFrame(); // IMGUI STUFF
    ImGui::NewFrame(); // IMGUI STUFF
    

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

    ImGui::Render(); // IMGUI STUFF
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // IMGUI STUFF

    display.Update();
  }

  ImGui_ImplOpenGL3_Shutdown(); // IMGUI STUFF
  ImGui_ImplGlfw_Shutdown(); // IMGUI STUFF
  ImGui::DestroyContext(); // IMGUI STUFF
}
