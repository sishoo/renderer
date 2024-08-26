#include "bootstrap/VkBootstrap.h"
#include "renderer/renderer.h"

static void renderer_init_instance(renderer_t *const r, char *name)
{
        vkb::InstanceBuilder builder;
        auto res = builder
                .set_app_name("Template Renderer")
                .set_engine_name("No Engine")
                .require_api_version(1, 3, 0)
                .use_default_debug_messenger()
              //.set_debug_callback(debug_callback)
                .request_validation_layers()
                .build();
        VK_TRY(res.vk_result());
        r->vkb_instance = res.value();
        r->instance = r->vkb_instance.instance;
}

static void renderer_init_window(renderer_t *const r, char *const name)
{
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        r->window = glfwCreateWindow(r->window_width, r->window_height, name, NULL, NULL);
        assert(r->window != NULL);
}

static void renderer_init_surface(renderer_t *const r)
{
        VK_TRY(glfwCreateWindowSurface(r->instance, r->window, NULL, &r->surface));
}

static void renderer_init_pdevice(renderer_t *const r)
{
        vkb::PhysicalDeviceSelector selector(r->vkb_instance);
        auto res = selector
                       .set_surface(r->surface)
                       .select_first_device_unconditionally()
                       .select();
        VK_TRY(res.vk_result());
        r->vkb_pdevice = res.value();
        r->pdevice = r->vkb_pdevice.physical_device;
}

static void renderer_init_ldevice(renderer_t *const r)
{
        VkPhysicalDeviceSynchronization2Features sync_features = {};
        sync_features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES;
        sync_features.synchronization2 = VK_TRUE;

        vkb::DeviceBuilder builder{r->vkb_pdevice};
        auto res = builder
                       .add_pNext(&sync_features)
                       .build();
        VK_TRY(res.vk_result());
        r->vkb_ldevice = res.value();
        r->ldevice = r->vkb_ldevice.device;
}

static void renderer_init_queues(renderer_t *const r)
{
        
}

static void renderer_init_swapchain(renderer_t *const r)
{
        vkb::SwapchainBuilder builder{r->vkb_ldevice};
        auto res = builder
                       .add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT)
                       .build();
        VK_TRY(res.vk_result());
        r->vkb_swapchain = res.value();
        r->swapchain = r->vkb_swapchain.swapchain;

        VK_TRY(vkGetSwapchainImagesKHR(r->ldevice, r->swapchain, &r->nswapchain_images, NULL));

        r->swapchain_images = (VkImage *)malloc(sizeof(VkImage) * r->nswapchain_images);

        VK_TRY(vkGetSwapchainImagesKHR(r->ldevice, r->swapchain, &r->nswapchain_images, r->swapchain_images));
}

static void renderer_init_command_pool(renderer_t *const r)
{
        VkCommandPoolCreateInfo command_pool_info = {
                .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
                .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
                .queueFamilyIndex = r->queue_family_index
        };

        VK_TRY(vkCreateCommandPool(r->ldevice, &command_pool_info, NULL, &r->command_pool));
}

static void renderer_allocate_command_buffers(renderer_t *const r)
{
        VkCommandBufferAllocateInfo allocate_info = {
                .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                .commandPool = r->command_pool,
                .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
                .commandBufferCount = 1
        };

        VK_TRY(vkAllocateCommandBuffers(r->ldevice, &allocate_info, &r->command_buffer));
}

void renderer_init(renderer_t *const r, char *name, int width, int height)
{
        r->window_width = width;
        r->window_height = height;
        r->memory_type_index = ;

        renderer_init_instance(r, name);
        renderer_init_window(r, name);
        renderer_init_surface(r);
        renderer_init_pdevice(r);
        renderer_init_ldevice(r);
        renderer_init_queues(r);
        renderer_init_swapchain(r);
        renderer_init_command_pool(r);
        renderer_allocate_command_buffers(r);
}

static void renderer_draw(renderer_t *const r, uint64_t nframe)
{
        uint32_t resource_index = nframe % r->nswapchain_images;

        
}

void renderer_run(renderer_t *const r)
{
        uint64_t nframe = 0;
        while (!glfwWindowShouldClose(r->window))
        {
                renderer_draw(r, nframe);
                ++nframe;
        }
}

void renderer_shutdown(renderer_t *const r)
{
        glfwTerminate();
}


