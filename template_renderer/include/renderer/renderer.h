
#include "bootstrap/VKBootstrap.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define VK_TRY(try)                                                                         \
        do                                                                                  \
        {                                                                                   \
                VkResult VK_TRY_result = try;                                               \
                if (VK_TRY_result != VK_SUCCESS)                                            \
                {                                                                           \
                        fprintf(stderr, "VK_TRY(" #try ") failed with: %d", VK_TRY_result); \
                        abort();                                                            \
                }                                                                           \
        } while (0);

typedef struct
{
        VkInstance instance;
        VkPhysicalDevice pdevice;
        VkDevice ldevice;
        VkSurfaceKHR surface;
        uint32_t nswapchain_images;
        VkSwapchainKHR swapchain;
        VkImage *swapchain_images;

        uint32_t memory_type_index, queue_family_index;

        VkCommandPool command_pool;
        VkCommandBuffer command_buffer;

        GLFWwindow *window;
        int window_width, window_height;

        vkb::Instance vkb_instance;
        vkb::PhysicalDevice vkb_pdevice;
        vkb::Device vkb_ldevice;
        vkb::Swapchain vkb_swapchain;
} renderer_t;

void renderer_init(renderer_t *const r, char *name, int width, int height);
void renderer_run(renderer_t *const r);
void renderer_shutdown(renderer_t *const r);
