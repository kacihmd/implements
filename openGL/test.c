#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void) {
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW.");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
