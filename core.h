///////INCLUDES
#include <windows.h>
#include <shellapi.h>
#include <stdbool.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>


/////////defines
#define TRUE 1
#define FALSE 0
#define FRAME_LAG 2
#define APP_NAME "VULKAN SNAKE"
#define STAGE_SIZE (VkDeviceSize)32768
#define BLOCK_SIZE (VkDeviceSize)32768
#define INT    int64_t
#define INT32  int32_t
#define UINT8  uint8_t
#define UINT16 uint16_t
#define UINT32 uint32_t
#define UINT64 uint64_t
#define SIZE_T size_t
#define FLOAT  float
#define CHAR   char
#define WIDTH  (UINT16)620
#define HEIGHT (UINT16)620
typedef float vec4[4];

struct Core
{
    //////WINDOW       
    HWND window;
    HINSTANCE hinstance;
    UINT16 width;
    UINT16 height;
    ////////DEVICE
    VkInstance instance;  
    VkPhysicalDevice gpu;  
    VkSurfaceKHR surface;
    VkDevice device;
    VkPhysicalDeviceMemoryProperties gpu_memory_properties;  
    VkPhysicalDeviceProperties gpu_properties;  
    ////////QUEUE FAMILIES INDEX
    UINT32 graphics_index;
    UINT32 present_index;
    VkQueue graphics_queue;
    VkQueue present_queue;
    ////////SWAPCHAIN
    VkSwapchainKHR swapchain;
    VkFormat surface_format;
    VkColorSpaceKHR color_space;
    VkPresentModeKHR present_mode;
    UINT32 swapchain_images_count;
    VkImage* swapchain_images;
    VkImageView* swapchain_views;
    ////////RENDERPASS
    VkRenderPass render_pass;
    ///////////PIPELINE
    VkPipelineLayout pipeline_layout;
    VkPipeline pipeline;
    ////////DRAW_BUFFERS
    VkCommandPool command_pool;
    VkFramebuffer* frame_buffers;
    VkCommandBuffer* command_buffers;
    //////DRAW BARRIERS
    VkSemaphore image_available_semaphores[FRAME_LAG];
    VkSemaphore image_finished_semaphores[FRAME_LAG];
    VkFence fences[FRAME_LAG];
    VkFence* swapchain_fences;
    SIZE_T actual_frame;
    //////CHECKS
    UINT8 quit;
    UINT8 resize; 
    //////MEMORY BLOCK      
    VkDeviceMemory block_memory;    
    VkDeviceMemory stage_memory;  
    VkBuffer vertex_buffer; 
    VkBuffer stage_buffer;     
    VkDeviceSize container_offset;
    VkDeviceSize food_offset;
    VkDeviceSize snake_offset;  
    SIZE_T vertex_buffer_size;   
    SIZE_T container_size;
    SIZE_T food_size;
    SIZE_T snake_size;
    /////TIMER
    struct timeval time_check;
    INT start;
    INT end;
    INT trigger;    
};
struct Core* core;
////GIANT VERTEX
struct Vertex
{
    vec4 pos;
    vec4 color;
};
typedef struct Vertex Vertex;
struct Vertex vertices[630]; 
////////GAME MECHANICS
struct Game
{
    //////////GRID
    FLOAT grid_xy [2][2];   
    FLOAT grid_cell_width;
    FLOAT grid_cell_height;
    FLOAT grid_cell_pos_xy [2][100];    
    UINT8 double_check [2][100];    
    /////////FOOD
    FLOAT food_padding;
    FLOAT food_xy [2][2];    
    ////////SNAKE
    FLOAT snake_padding;
    FLOAT snake_xy [2][2];            
    /////////KEYBOARD
    UINT8 key_right_pressed;
    UINT8 key_left_pressed;
    UINT8 key_up_pressed;
    UINT8 key_down_pressed;    
    ////////TAIL           
    UINT16 tail_index[100];
    FLOAT tail_xy [100][2][2];
    FLOAT last_tail_xy[100][2][2];    
    UINT8 tail_size;      
    ///////////GAME 
    UINT8 game_over;  
    UINT8 score; 
    UINT8 snake_moved;
    UINT8 last_timer_index;  
    INT move_trigger;
    INT check_trigger;   
    UINT8 speed;
    UINT8 game_running;
};
struct Game* game;

void init_vk();
void loop();
void clean();
void timer();