#include <stdio.h>

#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"

#include "renderer/renderer.h"

int main()
{
        renderer_t renderer = {};
        renderer_init(&renderer, "HELLO", 800, 600);

        renderer_run(&renderer);

        return 0;
}
