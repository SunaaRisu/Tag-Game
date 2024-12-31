#include "../Stitch/Stitch/Core/display.h"

#define WIDTH 1080
#define HEIGHT 1080

int main() {
  Display display(WIDTH, HEIGHT, "Tag-Game");

  while (!display.IsClosed()) {
    display.Clear(0.1f, 0.1f, 0.1f, 1.0f);

    display.Update();
  }

  return 0;
}
