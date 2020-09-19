#include "core.h"
////////////////
//////PROGRAM
UINT8 check_square_collision(FLOAT square1[2][2],FLOAT square2[2][2])
{
  if ((square2[0][0] > square1[0][0]) &&(square2[1][0] < square1[1][0]) 
      &&(square2[0][1] > square1[0][1]) &&(square2[1][1] < square1[1][1]) )
  {
      return 1;
  }
  else 
  {
      return 0;
  }
}
UINT8 check_grid_collision()
{  
  if (game->snake_xy[0][0] <= game->grid_xy[0][0])
  {          
    return 1;
  }
  if (game->snake_xy[0][1] <= game->grid_xy[0][1])
  {        
    return 1;
  }
  if (game->snake_xy[1][0] >= game->grid_xy[1][0])
  {        
    return 1;
  }
  if (game->snake_xy[1][1] >= game->grid_xy[1][1])
  {            
    return 1;
  }
  else
  {
      return 0;
  }
  
}
UINT8 check_tail_collision()
{
    UINT8 check_food_spawn = 0;
    UINT8 check_food_spawn_head = 0;
    FLOAT check_pos_xy[2][2];      
    if (game->tail_size > 0)
    {
       for (UINT16 k = 0; k < 100; ++k)
       {
           check_pos_xy[0][0]= (game->grid_cell_pos_xy[0][k])+game->food_padding;
           check_pos_xy[0][1]= (game->grid_cell_pos_xy[1][k])+game->food_padding;
           check_pos_xy[1][0]= (check_pos_xy[0][0] + (game->grid_cell_width))-(game->food_padding *2);
           check_pos_xy[1][1]= (check_pos_xy[0][1] + (game->grid_cell_height))-(game->food_padding*2);
           for (UINT16 z = 0; z< game->tail_size; ++z)
           {             
               check_food_spawn = check_square_collision(game->tail_xy[z],check_pos_xy);                   
               check_food_spawn_head = check_square_collision(game->snake_xy,check_pos_xy);               
               if (check_food_spawn == 1 && check_food_spawn_head == 1)
               {                      
                   return 1;
                   break;
               }             
           }              
        } 
                    
    }   
    return 0;    
}
void random_head_spam()
{
    time_t random_time; 
      srand((UINT32)time(&random_time));
      game->snake_xy[0][0] = game->grid_cell_pos_xy[0][rand()%100]+(game->snake_padding);
      game->snake_xy[0][1] = game->grid_cell_pos_xy[1][rand()%100]+(game->snake_padding);
      game->snake_xy[1][0] = (game->snake_xy[0][0]  + game->grid_cell_width)-(game->snake_padding*2);
      game->snake_xy[1][1] = (game->snake_xy[0][1] + game->grid_cell_height)-(game->snake_padding*2);
      
      vertices[30] = (struct Vertex){{ game->snake_xy[0][0],game->snake_xy[0][1],0.0f,0.0f},{ 1.0f,0.6f,1.0f,1.0f}};
      vertices[31] = (struct Vertex){{ game->snake_xy[1][0],game->snake_xy[0][1],0.0f,0.0f},{ 1.0f,0.6f,1.0f,1.0f}};
      vertices[32] = (struct Vertex){{ game->snake_xy[0][0],game->snake_xy[1][1],0.0f,0.0f},{ 1.0f,0.6f,1.0f,1.0f}};
      vertices[33] = (struct Vertex){{ game->snake_xy[0][0],game->snake_xy[1][1],0.0f,0.0f},{ 1.0f,0.6f,1.0f,1.0f}};
      vertices[34] = (struct Vertex){{ game->snake_xy[1][0],game->snake_xy[0][1],0.0f,0.0f},{ 1.0f,0.6f,1.0f,1.0f}};
      vertices[35] = (struct Vertex){{ game->snake_xy[1][0],game->snake_xy[1][1],0.0f,0.0f},{ 1.0f,0.6f,1.0f,1.0f}};
}
void random_food_spam()
{      
   time_t random_time; 
   srand((UINT32)time(&random_time));
   UINT8 check_food_spawn = 0;
   UINT8 check_food_spawn_head = 0;
   UINT8 random_number;  
   UINT8 free_cells_index= 0;   
   FLOAT check_pos_xy[2][2]; 
  
   for (UINT16 b = 0;b<100;++b)
   {
       game->double_check[0][b] = 0;
       game->double_check[1][b] = 0;
   }
   if (game->tail_size > 0)
   {
       for (UINT16 k = 0; k < 100; ++k)
       {
           check_pos_xy[0][0]= (game->grid_cell_pos_xy[0][k])+game->food_padding;
           check_pos_xy[0][1]= (game->grid_cell_pos_xy[1][k])+game->food_padding;
           check_pos_xy[1][0]= (check_pos_xy[0][0] + (game->grid_cell_width))-(game->food_padding *2);
           check_pos_xy[1][1]= (check_pos_xy[0][1] + (game->grid_cell_height))-(game->food_padding*2);
           for (UINT16 z = 0; z< game->tail_size; ++z)
           {               
               check_food_spawn = check_square_collision(game->tail_xy[z],check_pos_xy);                   
               check_food_spawn_head = check_square_collision(game->snake_xy,check_pos_xy);
               if (check_food_spawn == 1 || check_food_spawn_head == 1)
               {            
                   game->double_check[0][k] = 111;
                   break;
               }                 
           }   
           if (check_food_spawn == 0 && check_food_spawn_head == 0 && game->double_check[0][k] != 111)
               {            
                   game->double_check[0][k] = k;
               }    
        }               
    }     
   if (game->tail_size == 0)
   {
       for (UINT16 k = 0; k < 100; ++k)
       {
           check_pos_xy[0][0]= (game->grid_cell_pos_xy[0][k])+game->food_padding;
           check_pos_xy[0][1]= (game->grid_cell_pos_xy[1][k])+game->food_padding;
           check_pos_xy[1][0]= (check_pos_xy[0][0] + (game->grid_cell_width))-(game->food_padding *2);
           check_pos_xy[1][1]= (check_pos_xy[0][1] + (game->grid_cell_height))-(game->food_padding*2);
           check_food_spawn_head = check_square_collision(game->snake_xy,check_pos_xy);
            
        if (check_food_spawn_head == 0)
        {            
            game->double_check[0][k] = k;
        }  
        else if (check_food_spawn_head == 1)
        {            
            game->double_check[0][k] = 111;
        }                
       }          
   }  
     
    for (UINT16 l = 0;l < 100;++l)
    {       
        if (game->double_check[0][l] != 111)
        {
           game->double_check[1][free_cells_index] = game->double_check[0][l];
           free_cells_index += 1;
        }
    }
    random_number = rand()%free_cells_index;
    game->food_xy[0][0] = (game->grid_cell_pos_xy[0][game->double_check[1][random_number]])+game->food_padding;
    game->food_xy[0][1] = (game->grid_cell_pos_xy[1][game->double_check[1][random_number]])+game->food_padding;
        
     
  
}   
void game_over ()
{
    UINT8 check_grid = 0;
    UINT8 check_tail = 0;    
    check_grid = check_grid_collision();
    check_tail = check_tail_collision();
    if (check_grid == 1 || check_tail == 1)
    {         
      game->game_over = 1;
      printf("SCORE = %d\n",game->score);
      printf("SORRY BRO YOU LOST...PRESS SPACE BAR TO TRY AGAIN\n"); 
      game->snake_xy[0][0] = 0;
      game->snake_xy[0][1] = 0;
      game->snake_xy[1][0] = 0;
      game->snake_xy[1][1] = 0;
      
      game->score = 0;
      game->key_right_pressed = 0;   
      game->key_left_pressed = 0;
      game->key_up_pressed = 0; 
      game->key_down_pressed = 0;          
      for(UINT16 i = 0;i < game->tail_size;++i)   
      {   
        game->last_tail_xy[i][0][0] = 0;
        game->last_tail_xy[i][0][1] = 0;  
        game->tail_xy[i][0][0] = 0;
        game->tail_xy[i][0][1] = 0; 
        game->tail_xy[i][1][0] = 0;
        game->tail_xy[i][1][1] = 0;       
        game->tail_index[i] = 36 +(i*6);     
        vertices[game->tail_index[i]]  =(struct Vertex){{ game->tail_xy[i][0][0],game->tail_xy[i][0][1],0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f}};
        vertices[game->tail_index[i]+1]=(struct Vertex){{ game->tail_xy[i][1][0],game->tail_xy[i][0][1],0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f}};
        vertices[game->tail_index[i]+2]=(struct Vertex){{ game->tail_xy[i][0][0],game->tail_xy[i][1][1],0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f}};
        vertices[game->tail_index[i]+3]=(struct Vertex){{ game->tail_xy[i][0][0],game->tail_xy[i][1][1],0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f}};
        vertices[game->tail_index[i]+4]=(struct Vertex){{ game->tail_xy[i][1][0],game->tail_xy[i][0][1],0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f}};
        vertices[game->tail_index[i]+5]=(struct Vertex){{ game->tail_xy[i][1][0],game->tail_xy[i][1][1],0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f}};
      } 
      game->tail_size = 0;    
      random_head_spam();  
    ///////////MEMORY MAPPING    
  
  void* food_data;
  vkMapMemory(core->device,core->stage_memory,core->food_offset,core->food_size,0,&food_data);
  memcpy(food_data,vertices,core->food_size);
  vkUnmapMemory(core->device,core->stage_memory);

  void* snake_data;
  vkMapMemory(core->device,core->stage_memory,core->snake_offset,core->snake_size,0,&snake_data);
  memcpy(snake_data,vertices,core->snake_size);
  vkUnmapMemory(core->device,core->stage_memory); 
 }  
}
void timer_start()
{
    game->move_trigger = 1000 / game->speed;
    core->trigger = 1000;     
    gettimeofday(&core->time_check, NULL); 
    core->start = (INT )core->time_check.tv_sec * 1000 + (INT)core->time_check.tv_usec / 1000; 
}
////GAME PHYSICS
void update_positions()
{
   if (game->game_over == 0)
   {
    if ((core->end-core->start) > game->move_trigger)
    {
                       
        for(UINT16 i = 0;i < game->tail_size;++i)   
        {        
           if (i == 0)
           {
             game->last_tail_xy[i][0][0] =  game->snake_xy[0][0];
             game->last_tail_xy[i][0][1] =  game->snake_xy[0][1];
           }
           if (i != 0) 
           {      
             game->last_tail_xy[i][0][0] = game->tail_xy[game->last_timer_index][0][0];
             game->last_tail_xy[i][0][1] = game->tail_xy[game->last_timer_index][0][1];
           }  
           game->last_timer_index = i;    
        }
        game->move_trigger += 1000/game->speed; 

    }         
   }
   
}
void loop_game()
{    
    
    game->snake_moved = 0; 
    if(game->key_right_pressed == 1)
    {
        if((game->move_trigger != game->check_trigger) &&( game->snake_moved == 0))
        {
         game->snake_xy[0][0] =(game->snake_xy[0][0]+ game->grid_cell_width);
         game->snake_moved = 1; 
                 
        } 
    } 
    if(game->key_left_pressed == 1)
    {
        if((game->move_trigger != game->check_trigger) &&( game->snake_moved == 0))
        {
         game->snake_xy[0][0] =(game->snake_xy[0][0] - game->grid_cell_width);
         game->snake_moved = 1;         
        } 
    }  
    if(game->key_up_pressed == 1)
    {
        if((game->move_trigger != game->check_trigger) &&( game->snake_moved == 0))
        {
         game->snake_xy[0][1] =(game->snake_xy[0][1] - game->grid_cell_height);
         game->snake_moved = 1;         
        } 
    }  
    if(game->key_down_pressed == 1)
    {            
        if((game->move_trigger != game->check_trigger) &&( game->snake_moved == 0))
        {
         game->snake_xy[0][1] =(game->snake_xy[0][1] + game->grid_cell_height);
         game->snake_moved = 1;         
        } 
    }   
    game->check_trigger = game->move_trigger; 
}
void right_key()
{
    
    if (game->key_left_pressed != 1 && game->game_over == 0)
    {
        game->key_right_pressed = 1;    
        game->key_left_pressed = 0;
        game->key_up_pressed = 0; 
        game->key_down_pressed = 0; 
    }   
}
void left_key()
{
     if (game->key_right_pressed != 1&& game->game_over == 0)
     {
        game->key_right_pressed = 0;
        game->key_left_pressed = 1;
        game->key_up_pressed = 0; 
        game->key_down_pressed = 0;
     }
}
void up_key()
{
    if (game->key_down_pressed != 1&& game->game_over == 0)
    {
      game->key_right_pressed = 0;
      game->key_left_pressed = 0;
      game->key_up_pressed = 1; 
      game->key_down_pressed = 0;  
    }   
}
void down_key()
{
     if (game->key_up_pressed != 1&& game->game_over == 0)
     {
         game->key_right_pressed = 0;
         game->key_left_pressed = 0;
         game->key_up_pressed = 0; 
         game->key_down_pressed = 1;
     }
    
    
    
    
}
void space_key()
{
    if(game->game_running == 0)
    {
       game->game_over = 0;  
       timer_start(); 
       game->game_running =1;
    }      
    
}
//////////WINDOW
LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
 {
    switch (msg)
    {        
       // case WM_SIZE:
       //     // Resize the application to the new window size, except when
       //     // it was minimized. Vulkan doesn't support images or swapchains
       //     // with width=0 and height=0.
       //     if (wParam != SIZE_MINIMIZED) {
       //         demo.width = lParam & 0xffff;
       //         demo.height = (lParam & 0xffff0000) >> 16;
       //         demo_resize(&demo);
       //     }
       //     break;
        case WM_KEYDOWN:
            switch (wparam) {
                case VK_ESCAPE:
                    core->quit =1;
                    break;
                case VK_LEFT:
                    left_key();
                    break;
                    game->key_left_pressed = 0;
                case VK_RIGHT:
                    right_key();
                    break;
                    game->key_right_pressed = 0;
                case VK_UP:
                    up_key();
                    break;
                    game->key_up_pressed = 0;
                case VK_DOWN:
                    down_key();
                    break;
                    game->key_down_pressed = 0;
                case VK_SPACE:
                    space_key();
                    break;
            }
            return 0;
        default:
            break;
    }
    return (DefWindowProc(hwnd, msg, wparam, lparam));
}
void init_window()
{
    core->width = WIDTH;
    core->height = HEIGHT;
    WNDCLASSEX win_class;
    // Initialize the window class structure:
    win_class.cbSize = sizeof(WNDCLASSEX);
    win_class.style = CS_HREDRAW | CS_VREDRAW;
    win_class.lpfnWndProc = window_proc;
    win_class.cbClsExtra = 0;
    win_class.cbWndExtra = 0;
    win_class.hInstance = core->hinstance;  // hInstance
    win_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    win_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    win_class.hbrBackground = 0;
    win_class.lpszMenuName = NULL;
    win_class.lpszClassName = "wnd_class";
    win_class.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
    // Register window class:
    if (!RegisterClassEx(&win_class))
    {
        // It didn't work, so try to give a useful error:
        printf("Unexpected error trying to start the application!\n");
        fflush(stdout);
        exit(1);
    }
    // Create window with the registered class:
    RECT wr = {0, 0, core->width, core->height};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
    core->window = CreateWindowEx(0,
                                  "wnd_class",            // class name
                                  0,            // app name
                                  WS_POPUP|WS_VISIBLE|WS_SYSMENU,
                                  100, 100,            // x/y coords
                                  core->width,  // width
                                  core->height,  // height
                                  NULL,                // handle to parent
                                  NULL,                // handle to menu
                                  core->hinstance,    // hInstance
                                  NULL);               // no extra parameters
    if (!core->window) 
    {
        // It didn't work, so try to give a useful error:
        printf("Cannot create a window in which to draw!\n");
        fflush(stdout);
        exit(1);
    }
    // Window client area size must be at least 1 pixel high, to prevent crash.
    //demo->minsize.y = GetSystemMetrics(SM_CYMINTRACK) + 1;
}
////////////DEVICE
////////////////
void init_instance()
{
    VkResult check;
    /////////ALL LAYERS
    UINT32 instance_layers_count = 0;        
    VkBool32 validation_found = 0;    
    ////////VALIDATION LAYERS
    CHAR* instance_validation_layer = "VK_LAYER_KHRONOS_validation";
    UINT32 validation_layers_count = 0; 
    if (instance_validation_layer != NULL) 
    {
        check = vkEnumerateInstanceLayerProperties(&instance_layers_count, NULL);
        
        if (check == 0 && instance_layers_count > 0 )
        {            
            VkLayerProperties *instance_layers = malloc(sizeof(VkLayerProperties) * instance_layers_count);
            check = vkEnumerateInstanceLayerProperties(&instance_layers_count, instance_layers);
            if (check == 0)
            {
                 for (UINT32 i = 0; i < instance_layers_count; ++i) 
                 {
                    if (!strcmp(instance_validation_layer, instance_layers[i].layerName))
                    {
                      validation_found = 1;
                      validation_layers_count = 1;
                      break;
                    }
                 }                  
                 free(instance_layers);
                 if (!validation_found) 
                 {
                 printf ("NO KHRONOS VALIDATION LAYER BRO");
                 exit(-1);
                 }
            }   
                                
        }       
    }   
 ///////////INSTANCE EXTENSIONS
    UINT32 instance_extensions_count = 0;
    VkBool32 surface_extension_found = 0;
    VkBool32 platform_extension_found = 0; 
    CHAR* enabled_instance_extensions[2]; 
    //memset(enabled_instance_extensions, 0, sizeof(enabled_instance_extensions));      
    check = vkEnumerateInstanceExtensionProperties(NULL, &instance_extensions_count, NULL);
    if (check == 0 && instance_extensions_count > 0) 
    {
        VkExtensionProperties *instance_extensions = malloc(sizeof(VkExtensionProperties) * instance_extensions_count);
        check = vkEnumerateInstanceExtensionProperties(NULL, &instance_extensions_count, instance_extensions);
        if (check == 0)
        {
           for (UINT32 i = 0; i < instance_extensions_count; ++i) 
           {
              if (!strcmp(VK_KHR_SURFACE_EXTENSION_NAME, instance_extensions[i].extensionName)) 
              {
                  surface_extension_found = 1;
                  enabled_instance_extensions[0] = VK_KHR_SURFACE_EXTENSION_NAME;
              }
              if (!strcmp(VK_KHR_WIN32_SURFACE_EXTENSION_NAME, instance_extensions[i].extensionName)) 
              {
                 platform_extension_found = 1;
                 enabled_instance_extensions[1] = VK_KHR_WIN32_SURFACE_EXTENSION_NAME;
              }
           }
           free (instance_extensions);
           if (surface_extension_found == 1 && platform_extension_found == 1)
           {
               printf("INSTANCE EXTENSIONS ENABLED\n");

           }
           else
           {
               printf("SORRY BRO NO INSTANCE EXTENSIONS AVAILABLE");
               exit (-1);
           }
           
        }        
    }

    //
    const VkApplicationInfo app_info = 
    {
    
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = NULL,
        .pApplicationName = APP_NAME,
        .applicationVersion = 0,
        .pEngineName = APP_NAME,
        .engineVersion = 0,
        .apiVersion = VK_API_VERSION_1_0,
    };
    VkInstanceCreateInfo instance_info = 
    {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = NULL,
        .pApplicationInfo = &app_info,
        .enabledLayerCount = validation_layers_count,
        .ppEnabledLayerNames = (const CHAR *const *)&instance_validation_layer,
        .enabledExtensionCount = 2,
        .ppEnabledExtensionNames = (const CHAR *const *)enabled_instance_extensions,
    };
    if ((check = vkCreateInstance(&instance_info, NULL, &core->instance))== 0)
    {
        printf("INSTANCE INITIALIZED BRO\n");
    }
    else 
    {
        printf ("FAILED TO INITIALIZED INSTANCE SORRY");
        exit(-1);
    }    
}
void init_device()
{
    VkResult check;
    UINT32 gpu_count;       
    check = vkEnumeratePhysicalDevices(core->instance, &gpu_count, NULL);
    if (check == 0 && gpu_count > 0) 
    {
        VkPhysicalDevice *physical_devices = malloc(sizeof(VkPhysicalDevice) * gpu_count);
        check = vkEnumeratePhysicalDevices(core->instance, &gpu_count, physical_devices);
        VkPhysicalDeviceProperties physical_device_properties;          
        if (check == 0)
        {            
            for (UINT32 i = 0; i < gpu_count; ++i)
            {    
              vkGetPhysicalDeviceProperties(physical_devices[i],&physical_device_properties);
              printf("GPU OF INDEX %d IS : %s\n",i,physical_device_properties.deviceName);
            }
            core->gpu = physical_devices[0];
            vkGetPhysicalDeviceMemoryProperties(core->gpu,&core->gpu_memory_properties);
            vkGetPhysicalDeviceProperties(core->gpu,&core->gpu_properties);
            free(physical_devices);
          
        }     
    }
    ////////DEVICE EXTENSIONS   
    UINT32 device_extensions_count = 0;
    VkBool32 swapchain_extension_found = 0;
    ////////ENABLED EXTENSIONS
    UINT32 device_enabled_extensions_count = 0;
    CHAR* device_enabled_extensions[1];   

    check = vkEnumerateDeviceExtensionProperties(core->gpu, NULL, &device_extensions_count, NULL);
    if (check == 0 && device_extensions_count > 0)
    {
        VkExtensionProperties *device_extensions = malloc(sizeof(VkExtensionProperties) * device_extensions_count);
        check = vkEnumerateDeviceExtensionProperties(core->gpu, NULL, &device_extensions_count, device_extensions);
        if (check == 0)
        {
          for (UINT32 i = 0; i < device_extensions_count; ++i) 
          {
            if (!strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME, device_extensions[i].extensionName)) 
            {
               swapchain_extension_found = 1;
               device_enabled_extensions[0] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
               device_enabled_extensions_count += 1;
               break;
            }                        
          }
          if (swapchain_extension_found != 1)
          {
              printf("NO SWAPCHAIN EXTENSION BRO SORRY");
              exit (-1);
          }

        }
        free(device_extensions);
    }
    /////////////SURFACE
    
    VkWin32SurfaceCreateInfoKHR surface_info=
    {
      .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
      .pNext = NULL,
      .flags = 0,
      .hinstance = core->hinstance,
      .hwnd = core->window,       
    };   

    check = vkCreateWin32SurfaceKHR(core->instance, &surface_info, NULL, &core->surface);
    /////////////QUEUE FAMILIES
    UINT32 queue_families_count = 0; 
    vkGetPhysicalDeviceQueueFamilyProperties(core->gpu, &queue_families_count, NULL);    

    VkQueueFamilyProperties* family_properties = (VkQueueFamilyProperties *)malloc(queue_families_count * sizeof(VkQueueFamilyProperties));
    vkGetPhysicalDeviceQueueFamilyProperties(core->gpu, &queue_families_count, family_properties);      
    VkBool32 *present_support = (VkBool32 *)malloc(queue_families_count * sizeof(VkBool32));
    for (UINT32 i = 0; i < queue_families_count; ++i)
    {
        check = vkGetPhysicalDeviceSurfaceSupportKHR(core->gpu, i, core->surface, &present_support[i]);
    }
    // Search for a graphics and a present queue in the array of queue
    // families, try to find one that supports both
   core->graphics_index = UINT32_MAX;
   core->present_index = UINT32_MAX;
    for (UINT32 i = 0; i < queue_families_count; ++i) 
    {
        if ((family_properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) 
        {
            if (core->graphics_index == UINT32_MAX)
            {
                core->graphics_index = i;
            }
            if (present_support[i] == VK_TRUE) 
            {
                core->graphics_index = i;
                core->present_index = i;
                break;
            }
        }
    }
    if (core->present_index == UINT32_MAX) 
    {
        // If didn't find a queue that supports both graphics and present, then
        // find a separate present queue.
        for (UINT32 i = 0; i < queue_families_count; ++i) 
        {
            if (present_support[i] == VK_TRUE) 
            {
                core->present_index = i;
                printf("GRAPHICS AND PRESENT INDEXES ARE SEPARATED BRO SAD");
                break;
            }
        }
    }

    // Generate error if could not find both a graphics and a present queue
    if (core->graphics_index == UINT32_MAX || core->present_index == UINT32_MAX) 
    {
        printf("SORRY BRO NO QUEUE FAMILIES INDEX FOUND BB");
        exit (-1);
    }
    free(present_support);
   
    FLOAT queue_priorities[1] = {0.0};
    VkDeviceQueueCreateInfo queues[2];
    queues[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queues[0].pNext = NULL;
    queues[0].queueFamilyIndex = core->graphics_index;
    queues[0].queueCount = 1;
    queues[0].pQueuePriorities = queue_priorities;
    queues[0].flags = 0;
//
    VkDeviceCreateInfo device_info = 
    {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = NULL,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = queues,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = NULL,
        .enabledExtensionCount = device_enabled_extensions_count,
        .ppEnabledExtensionNames = (const CHAR *const *)device_enabled_extensions,
        .pEnabledFeatures = NULL,  // If specific features are required, pass them in here
    };
    if (core->graphics_index != core->present_index) 
    {
        queues[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queues[1].pNext = NULL;
        queues[1].queueFamilyIndex = core->present_index;
        queues[1].queueCount = 1;
        queues[1].pQueuePriorities = queue_priorities;
        queues[1].flags = 0;
        device_info.queueCreateInfoCount = 2;
    }
    if((check = vkCreateDevice(core->gpu, &device_info, NULL, &core->device))== 0)
    {
      printf("DEVICE INITIALIZED\n");
    }
    else
    {
      printf("FAILED TO INITIALIZE DEVICE BRO");
      exit (-1);
    }  
    ///DEVICE QUEUES
    if (core->graphics_index != core->present_index)
    {
        vkGetDeviceQueue(core->device,core->graphics_index,0,&core->graphics_queue);
        vkGetDeviceQueue(core->device,core->present_index,0,&core->present_queue);
    }
    else
    {
        vkGetDeviceQueue(core->device,core->graphics_index,0,&core->graphics_queue);
        vkGetDeviceQueue(core->device,core->graphics_index,0,&core->present_queue);
    }
}
/////MEMORY BLOCK
void init_command_pool()
{
  VkCommandPoolCreateInfo command_pool_info =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = 0,
        .pNext = NULL,
        .queueFamilyIndex = core->graphics_index,
    };
    if (vkCreateCommandPool(core->device,&command_pool_info,NULL,&core->command_pool) == 0)
    {
      printf("COMMAND POOL INITIALIZED\n");
    }
    else
    {
        printf("COMMAND POOL FAILURE");
        exit(-1);
    }
}
void init_memory_block()
{    
    /////////STAGE
    UINT32 memory_index = 0;
    for (UINT32 i = 0; i < core->gpu_memory_properties.memoryTypeCount;++i)
    {
      if(core->gpu_memory_properties.memoryTypes[i].propertyFlags & (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
      {
        memory_index = i;
        break;
      }
    }
    VkMemoryAllocateInfo stage_allocation_info =
    {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .pNext = NULL,
        .allocationSize = STAGE_SIZE,
        .memoryTypeIndex = memory_index,        
    };
    vkAllocateMemory(core->device, &stage_allocation_info,NULL, &core->stage_memory);

    //////////BLOCK
    UINT32 memory_index2 = 0;
    for (UINT32 i = 0; i < core->gpu_memory_properties.memoryTypeCount;++i)
    {
      if(core->gpu_memory_properties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
      {
        memory_index2 = i;
        break;
      }
    }
    VkMemoryAllocateInfo block_allocation_info =
    {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .pNext = NULL,
        .allocationSize = BLOCK_SIZE,
        .memoryTypeIndex = memory_index2,        
    };
    vkAllocateMemory(core->device, &block_allocation_info,NULL, &core->block_memory);  

    ////////BUFFERS
    SIZE_T alignment = sizeof(vec4);  
    core->vertex_buffer_size = 1260 * alignment;
    core->container_offset = 0;
    core->food_offset = alignment *48;
    core->snake_offset = alignment *60;
    core->container_size = sizeof(Vertex)*24;
    core->food_size = sizeof(Vertex)*6; 
    core->snake_size = sizeof(Vertex)*600;
    ///////////////STAGE_BUFFER    
    VkBufferCreateInfo stage_buffer_info =
    {
        .sType =VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .flags = 0,
        .pNext = NULL,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .size = core->vertex_buffer_size,
        .usage =VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        .pQueueFamilyIndices = NULL,
        .queueFamilyIndexCount = 0,
    };
    vkCreateBuffer(core->device, &stage_buffer_info, NULL, &core->stage_buffer);
    VkMemoryRequirements stage_memory_requirement;
    vkGetBufferMemoryRequirements(core->device,core->stage_buffer, &stage_memory_requirement);
    vkBindBufferMemory(core->device,core->stage_buffer,core->stage_memory,(VkDeviceSize)0);  


    ////////////VERTEX_BUFFER
    VkBufferCreateInfo vertex_buffer_info =
    {
        .sType =VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .flags = 0,
        .pNext = NULL,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .size = core->vertex_buffer_size,
        .usage =VK_BUFFER_USAGE_TRANSFER_DST_BIT| VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        .pQueueFamilyIndices = NULL,
        .queueFamilyIndexCount = 0,
    };
    vkCreateBuffer(core->device, &vertex_buffer_info, NULL, &core->vertex_buffer);
    VkMemoryRequirements vertex_memory_requirement;
    vkGetBufferMemoryRequirements(core->device,core->vertex_buffer, &vertex_memory_requirement);
    vkBindBufferMemory(core->device,core->vertex_buffer,core->block_memory,(VkDeviceSize)0);    

}
//////////////SWAPCHAIN
void init_swapchain()
{    
    VkSwapchainKHR old_swapchain = core->swapchain;
    VkResult check;
    VkSurfaceCapabilitiesKHR surface_capabilities;
    VkBool32 surface_format_found = 0;
    VkBool32 color_space_found = 0;
    check = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(core->gpu,core->surface,&surface_capabilities);
    ///SURFACE FORMATS
    if (check == 0)
    {
        UINT32 surface_formats_count;
        check = vkGetPhysicalDeviceSurfaceFormatsKHR(core->gpu, core->surface, &surface_formats_count, NULL);
        if (check == 0 && surface_formats_count > 0 )
        {
           VkSurfaceFormatKHR *surface_formats = (VkSurfaceFormatKHR *)malloc(sizeof(VkSurfaceFormatKHR) * surface_formats_count);
           check = vkGetPhysicalDeviceSurfaceFormatsKHR(core->gpu, core->surface, &surface_formats_count, surface_formats);
            if (check == 0)
            {   
                for (UINT32 i = 0; i< surface_formats_count; ++i)
                {
                    if (surface_formats[i].format == VK_FORMAT_B8G8R8A8_SRGB)
                    { 
                        core->surface_format = surface_formats[i].format;
                        surface_format_found = 1;
                    }
                    if (surface_formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                    { 
                        core->color_space = surface_formats[i].colorSpace;
                        color_space_found = 1;
                    }
                    if (color_space_found && surface_format_found)
                    {
                        break;
                    }
                } 
                if (!(surface_format_found) || !(color_space_found))
                {
                    printf("SORRY BRO I DIDN'T FIND THE FORMAT OR COLOR SPACE NEEDED bb");
                    exit(-1);
                }
                if (surface_formats != NULL)
                {
                    free(surface_formats);
                }
              
            }       
        }
        else 
        {
            printf("NO SURFACE FORMATS FOUND BRO SORRY");
            exit(-1);
        }
    
    }
    else 
    {
        printf ("NO SURFACE CAPABILITES BRO SORRY");
        exit(-1);
    }
    
    /////////SWAPCHAIN EXTENT
    VkExtent2D swapchain_extent;
    // width and height are either both 0xFFFFFFFF, or both not 0xFFFFFFFF.
    if (surface_capabilities.currentExtent.width == 0xFFFFFFFF) 
    {        
        swapchain_extent.width = core->width;
        swapchain_extent.height = core->height;
        if (swapchain_extent.width < surface_capabilities.minImageExtent.width) 
        {
            swapchain_extent.width = surface_capabilities.minImageExtent.width;
        } 
        else if (swapchain_extent.width > surface_capabilities.maxImageExtent.width) 
        {
            swapchain_extent.width = surface_capabilities.maxImageExtent.width;
        }
        if (swapchain_extent.height < surface_capabilities.minImageExtent.height) 
        {
            swapchain_extent.height = surface_capabilities.minImageExtent.height;
        }
        else if (swapchain_extent.height > surface_capabilities.maxImageExtent.height) 
        {
            swapchain_extent.height = surface_capabilities.maxImageExtent.height;
        }
    } 
    else 
    {
        // If the surface size is defined, the swap chain size must match
        swapchain_extent = surface_capabilities.currentExtent;
        core->width = surface_capabilities.currentExtent.width;
        core->height = surface_capabilities.currentExtent.height;
    }
    //////////PRESENT_MODES
    core->present_mode = VK_PRESENT_MODE_FIFO_KHR;
    VkBool32 present_mode_found = 0;
    //VK_PRESENT_MODE_FIFO_KHR;    
    // VK_PRESENT_MODE_IMMEDIATE_KHR             
    // VK_PRESENT_MODE_MAILBOX_KHR             
    // VK_PRESENT_MODE_FIFO_RELAXED_KHR
    UINT32 present_modes_count;
    check = vkGetPhysicalDeviceSurfacePresentModesKHR(core->gpu, core->surface, &present_modes_count, NULL);
    if (check == 0)
    {
      VkPresentModeKHR *present_modes = (VkPresentModeKHR *)malloc(present_modes_count * sizeof(VkPresentModeKHR));
      check = vkGetPhysicalDeviceSurfacePresentModesKHR(core->gpu, core->surface, &present_modes_count, present_modes);
      if (check == 0 && present_modes_count > 0)
      {   
          for (UINT32 i = 0; i < present_modes_count; ++i) 
          {
              if (core->present_mode == present_modes[i])
              {
                  printf("PRESENT MODE SPECIFIED FOUND BRO NICE\n");
                  present_mode_found = 1;
                  break;
              }              
          }
          if (!(present_mode_found))
          {
              printf("THE PRESENT MODE SPECIFIED IS NOT COMPATIBLE SORRY BRO");
              exit(-1);
          }
      }     
      if (present_modes != NULL)
      {
          free(present_modes);
      } 
    }
    else
    {
        printf("NO PRESENT MODES FOUND BRO SORRY bb");
        exit (-1);
    }
    
    ////IMAGE COUNT 
  UINT32 desired_swapchain_images = 2;
    if (desired_swapchain_images < surface_capabilities.minImageCount) 
    {
        desired_swapchain_images = surface_capabilities.minImageCount;
    }    
    if ((surface_capabilities.maxImageCount > 0) && (desired_swapchain_images > surface_capabilities.maxImageCount))
    {        
        desired_swapchain_images = surface_capabilities.maxImageCount;
    }
    VkSurfaceTransformFlagsKHR surface_transform;
    if (surface_capabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) 
    {
        surface_transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    } 
    else
    {
        surface_transform = surface_capabilities.currentTransform;
    }
    // Find a supported composite alpha mode - one of these is guaranteed to be set
    VkCompositeAlphaFlagBitsKHR composite_alpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    VkCompositeAlphaFlagBitsKHR composite_alpha_flags[4] =
     {
        VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
        VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
        VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
    };
    for (UINT32 i = 0; i < 4; ++i)
    {
        if (surface_capabilities.supportedCompositeAlpha & composite_alpha_flags[i]) 
        {
            composite_alpha = composite_alpha_flags[i];
            break;
        }
    }

    VkSwapchainCreateInfoKHR swapchain_info = 
    {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = NULL,
        .surface = core->surface,
        .minImageCount = desired_swapchain_images,
        .imageFormat = core->surface_format,
        .imageColorSpace = core->color_space,
        .imageExtent.width =swapchain_extent.width,
        .imageExtent.height = swapchain_extent.height,           
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .preTransform = surface_transform,
        .compositeAlpha = composite_alpha,
        .imageArrayLayers = 1,
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = NULL,
        .presentMode = core->present_mode,
        .oldSwapchain = old_swapchain,
        .clipped = TRUE,
    };   
    if ((check  = vkCreateSwapchainKHR(core->device, &swapchain_info, NULL, &core->swapchain)) == 0)
    {
        printf("SWAPCHAIN INITIALIZED BRO\n");
    }
    else
    {
      printf("FAILED TO INITIALIZE SWAPCHAIN");
      exit(-1);
    }  
    // If we just re-created an existing swapchain, we should destroy the old
    // swapchain at this point.
    // Note: destroying the swapchain also cleans up all its associated
    // presentable images once the platform is done with them.
    if (old_swapchain != VK_NULL_HANDLE) 
    {
        vkDestroySwapchainKHR(core->device, old_swapchain, NULL);
    }

    check  = vkGetSwapchainImagesKHR(core->device, core->swapchain, &core->swapchain_images_count, NULL);
    
    core->swapchain_images = (VkImage *)malloc(core->swapchain_images_count * sizeof(VkImage));
    core->swapchain_views = (VkImageView *)malloc(core->swapchain_images_count * sizeof(VkImageView));
    check = vkGetSwapchainImagesKHR(core->device, core->swapchain, &core->swapchain_images_count, core->swapchain_images);
    for (UINT32 i = 0; i < core->swapchain_images_count; ++i) 
    {
        VkImageViewCreateInfo view_info =
        {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .pNext = NULL,
            .format = core->surface_format,
            .components =
                {
                    .r = VK_COMPONENT_SWIZZLE_R,
                    .g = VK_COMPONENT_SWIZZLE_G,
                    .b = VK_COMPONENT_SWIZZLE_B,
                    .a = VK_COMPONENT_SWIZZLE_A,
                },
            .subresourceRange =
                {
                    .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                    .baseMipLevel = 0, 
                    .levelCount = 1, 
                    .baseArrayLayer = 0, 
                    .layerCount = 1
                },
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .flags = 0,
        };        
        view_info.image = core->swapchain_images[i];
        check = vkCreateImageView(core->device, &view_info, NULL, &core->swapchain_views[i]);        
    }

}
//////RENDER PASS
void init_renderpass()
{
    
    const VkAttachmentDescription attachments[1] = 
    {
        [0] =
            {
                .format = core->surface_format,
                .flags = 0,
                .samples = VK_SAMPLE_COUNT_1_BIT,
                .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
                .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
                .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            }
    };
    const VkAttachmentReference color_reference = 
    {
        .attachment = 0,
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
    };    
    const VkSubpassDescription subpass = 
    {
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .flags = 0,
        .inputAttachmentCount = 0,
        .pInputAttachments = NULL,
        .colorAttachmentCount = 1,
        .pColorAttachments = &color_reference,
        .pResolveAttachments = NULL,
        .pDepthStencilAttachment = NULL,
        .preserveAttachmentCount = 0,
        .pPreserveAttachments = NULL,
    };
    VkSubpassDependency subpass_dependency = 
    {
        .dependencyFlags = 0,
        .srcSubpass = VK_SUBPASS_EXTERNAL,
        .dstSubpass = 0,
        .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = 0,
        .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
    };
    const VkRenderPassCreateInfo render_pass_info =
    {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .pNext = NULL,
        .flags = 0,
        .attachmentCount = 1,
        .pAttachments = attachments,
        .subpassCount = 1,
        .pSubpasses = &subpass,
        .dependencyCount = 1,
        .pDependencies = &subpass_dependency,
    }; 
    vkCreateRenderPass(core->device, &render_pass_info, NULL, &core->render_pass);
    
}
////GAME LOOP
void init_vertex_data()
{ 
    ///REMEMBER -1-1 1-1 -1 1///////-1-1 angolo in alto a sx 1 1 angolo in basso a destra
    //  vec2( 0.0,-0.5),
    //vec2(   0.5, 0.5),
    //vec2  (-0.5, 0.5)

  FLOAT topx0 = -1.0f;
  FLOAT topy0 = -1.0f;
  FLOAT topx1 = 0.95f;
  FLOAT topy1 = -0.95f;  

  FLOAT leftx0 = -1.0f;
  FLOAT lefty0 = -0.95f;
  FLOAT leftx1 = -0.95f;
  FLOAT lefty1 = 1.0f; 

  FLOAT bottomx0 = -0.95f;
  FLOAT bottomy0 =  0.95f;
  FLOAT bottomx1 = 1.0f;
  FLOAT bottomy1 = 1.0f; 

  FLOAT rightx0 =  1.0f;
  FLOAT righty0 = 0.95f;
  FLOAT rightx1 = 0.95f;
  FLOAT righty1 = -1.0f; 
  
  ///////CONTAINER 
  ///////////TOP
  vertices[0] =   (struct Vertex){{ topx0,topy0,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[1] =   (struct Vertex){{ topx1,topy0,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[2] =   (struct Vertex){{ topx0,topy1,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[3] =   (struct Vertex){{ topx0,topy1,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[4] =   (struct Vertex){{ topx1,topy0,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[5] =   (struct Vertex){{ topx1,topy1,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  ///LEFT) 
  vertices[6] =   (struct Vertex){{ leftx0,lefty0,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[7] =   (struct Vertex){{ leftx1,lefty0,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[8] =   (struct Vertex){{ leftx0,lefty1,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[9] =   (struct Vertex){{ leftx0,lefty1,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[10] =  (struct Vertex){{ leftx1,lefty0,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[11] =  (struct Vertex){{ leftx1,lefty1,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  ////BOTTOM)
  vertices[12] =  (struct Vertex){{ bottomx0,bottomy0,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[13] =  (struct Vertex){{ bottomx1,bottomy0,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[14] =  (struct Vertex){{ bottomx0,bottomy1,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[15] =  (struct Vertex){{ bottomx0,bottomy1,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[16] =  (struct Vertex){{ bottomx1,bottomy0,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[17] =  (struct Vertex){{ bottomx1,bottomy1,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  /////RIGHT 
  vertices[18] =  (struct Vertex){{ rightx0,righty0,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[19] =  (struct Vertex){{ rightx1,righty0,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[20] =  (struct Vertex){{ rightx0,righty1,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[21] =  (struct Vertex){{ rightx0,righty1,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[22] =  (struct Vertex){{ rightx1,righty0,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  vertices[23] =  (struct Vertex){{ rightx1,righty1,0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f},};
  ///////////////////GAME INFOS 
  game->grid_xy[0][0]= -0.95f;
  game->grid_xy[0][1]= -0.95f;
  game->grid_xy[1][0]= 0.95f;
  game->grid_xy[1][1]= 0.95f; 
  FLOAT grid_height = 1.90f;
  FLOAT grid_width = 1.90f;
  game->grid_cell_width = grid_width/10;
  game->grid_cell_height = grid_height/10;
  game->food_padding = 0.02f;
  game->snake_padding = 0.01f;  
  game->key_right_pressed = 0;
  game->key_left_pressed = 0;
  game->key_up_pressed = 0;
  game->key_down_pressed = 0;
  game->snake_moved = 0;  
  game->game_over = 0; 
  game->score = 0;
  game->tail_size = 0; 
  game->last_timer_index = 0; 
  UINT8 y_switch = 0;
  UINT8 x_switch = 0;
  for (UINT16 i = 0; i <100; ++i)
  {  
    if (i == 10 || i == 20|| i == 30|| i == 40 || i == 50|| i == 60|| i == 70|| i == 80|| i == 90)
    {
       y_switch += 1;
       x_switch = 0; 
    } 
    if (i != 0 && i != 10&& i != 20&& i != 30&& i != 40&& i != 50&& i != 60&& i != 70&& i != 80&& i != 90)
    {
        x_switch += 1;
    }    
    game->grid_cell_pos_xy[0][i] = game->grid_xy[0][0]  +(game->grid_cell_width * x_switch);
    game->grid_cell_pos_xy[1][i] = game->grid_xy[0][1]  +(game->grid_cell_height* y_switch);
  }
  random_head_spam();
  random_food_spam();
  void* container_data;
  vkMapMemory(core->device,core->stage_memory,core->container_offset,core->container_size,0,&container_data);
  memcpy(container_data,vertices,core->container_size);
  vkUnmapMemory(core->device,core->stage_memory);
}
void update_vertex_data()
{  
  
  if (game->game_over == 0)
  {
    //////FOOD   
  game->food_xy[1][0] = (game->food_xy[0][0] + (game->grid_cell_width))-(game->food_padding *2);
  game->food_xy[1][1] = (game->food_xy[0][1] + (game->grid_cell_height))-(game->food_padding*2);
  
  vertices[24] = (struct Vertex){{ game->food_xy[0][0],game->food_xy[0][1],0.0f,0.0f},{ 1.0f,0.0f,0.0f,0.0f}};
  vertices[25] = (struct Vertex){{ game->food_xy[1][0],game->food_xy[0][1],0.0f,0.0f},{ 1.0f,0.0f,0.0f,0.0f}};
  vertices[26] = (struct Vertex){{ game->food_xy[0][0],game->food_xy[1][1],0.0f,0.0f},{ 1.0f,0.0f,0.0f,0.0f}};
  vertices[27] = (struct Vertex){{ game->food_xy[0][0],game->food_xy[1][1],0.0f,0.0f},{ 1.0f,0.0f,0.0f,0.0f}};
  vertices[28] = (struct Vertex){{ game->food_xy[1][0],game->food_xy[0][1],0.0f,0.0f},{ 1.0f,0.0f,0.0f,0.0f}};
  vertices[29] = (struct Vertex){{ game->food_xy[1][0],game->food_xy[1][1],0.0f,0.0f},{ 1.0f,0.0f,0.0f,0.0f}};  
  ////////////SNAKE   
  game->snake_xy[1][0] = (game->snake_xy[0][0]  + game->grid_cell_width)-(game->snake_padding*2);
  game->snake_xy[1][1] = (game->snake_xy[0][1] + game->grid_cell_height)-(game->snake_padding*2);
  
  vertices[30] = (struct Vertex){{ game->snake_xy[0][0],game->snake_xy[0][1],0.0f,0.0f},{ 1.0f,0.6f,1.0f,1.0f}};
  vertices[31] = (struct Vertex){{ game->snake_xy[1][0],game->snake_xy[0][1],0.0f,0.0f},{ 1.0f,0.6f,1.0f,1.0f}};
  vertices[32] = (struct Vertex){{ game->snake_xy[0][0],game->snake_xy[1][1],0.0f,0.0f},{ 1.0f,0.6f,1.0f,1.0f}};
  vertices[33] = (struct Vertex){{ game->snake_xy[0][0],game->snake_xy[1][1],0.0f,0.0f},{ 1.0f,0.6f,1.0f,1.0f}};
  vertices[34] = (struct Vertex){{ game->snake_xy[1][0],game->snake_xy[0][1],0.0f,0.0f},{ 1.0f,0.6f,1.0f,1.0f}};
  vertices[35] = (struct Vertex){{ game->snake_xy[1][0],game->snake_xy[1][1],0.0f,0.0f},{ 1.0f,0.6f,1.0f,1.0f}}; 
  
  
   UINT8 check_collision = 0;    
   check_collision = check_square_collision(game->snake_xy,game->food_xy);  
   switch (check_collision)
   {
       case 0: 
          break;
       case 1:          
          game->tail_size = game->tail_size +1;
          game->last_tail_xy[game->tail_size-1][0][0] = 0;
          game->last_tail_xy[game->tail_size-1][0][1] = 0;
          break;
   }  
  
  for(UINT16 i = 0;i < game->tail_size;++i)   
  {  
    if ((game->last_tail_xy[i][0][0] !=0) && (game->last_tail_xy[i][0][1]!= 0))   
    {
        game->tail_xy[i][0][0] = game->last_tail_xy[i][0][0] ;
        game->tail_xy[i][0][1] = game->last_tail_xy[i][0][1] ;   
        game->tail_xy[i][1][0] = (game->tail_xy[i][0][0] + game->grid_cell_width)-(game->snake_padding*2);
        game->tail_xy[i][1][1] = (game->tail_xy[i][0][1] + game->grid_cell_height)-(game->snake_padding*2); 
        
        game->tail_index[i] = 36 +(i*6);          
        vertices[game->tail_index[i]]  =(struct Vertex){{ game->tail_xy[i][0][0],game->tail_xy[i][0][1],0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f}};
        vertices[game->tail_index[i]+1]=(struct Vertex){{ game->tail_xy[i][1][0],game->tail_xy[i][0][1],0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f}};
        vertices[game->tail_index[i]+2]=(struct Vertex){{ game->tail_xy[i][0][0],game->tail_xy[i][1][1],0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f}};
        vertices[game->tail_index[i]+3]=(struct Vertex){{ game->tail_xy[i][0][0],game->tail_xy[i][1][1],0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f}};
        vertices[game->tail_index[i]+4]=(struct Vertex){{ game->tail_xy[i][1][0],game->tail_xy[i][0][1],0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f}};
        vertices[game->tail_index[i]+5]=(struct Vertex){{ game->tail_xy[i][1][0],game->tail_xy[i][1][1],0.0f,0.0f},{ 1.0f,1.0f,1.0f,1.0f}};

    } 
  }    
    
       if (check_collision == 1 )
       { 
        game->score += 1;       
        random_food_spam();
       }
  
   
  }     
  
   ///////////MEMORY MAPPING     
  
  void* food_data;
  vkMapMemory(core->device,core->stage_memory,core->food_offset,core->food_size,0,&food_data);
  memcpy(food_data,vertices,core->food_size);
  vkUnmapMemory(core->device,core->stage_memory);

  void* snake_data;
  vkMapMemory(core->device,core->stage_memory,core->snake_offset,core->snake_size,0,&snake_data);
  memcpy(snake_data,vertices,core->snake_size);
  vkUnmapMemory(core->device,core->stage_memory);
  
    
}
///////PIPELINE
void init_pipeline()
{    
    VkShaderModule vertex_shader_module;
    VkShaderModule fragment_shader_module;
    const UINT32 vertex_code[] = 
    {
      #include "C:\Users\xho\Desktop\XHOBO\SHADERS\prova.vertex"
    };    
    const UINT32 fragment_code[] = 
    {
      #include "C:\Users\xho\Desktop\XHOBO\SHADERS\prova.fragment"
    };  
    VkShaderModuleCreateInfo vertex_shader_info =
    {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .flags = 0,
        .pNext = NULL,
        .codeSize = sizeof(vertex_code),        
        .pCode = vertex_code,        
    };    
    vkCreateShaderModule(core->device, &vertex_shader_info, NULL, &vertex_shader_module);
    VkShaderModuleCreateInfo fragment_shader_info =
    {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .flags = 0,
        .pNext = NULL,
        .codeSize = sizeof(fragment_code),        
        .pCode = fragment_code,        
    };    
    vkCreateShaderModule(core->device, &fragment_shader_info, NULL, &fragment_shader_module);
    VkPipelineShaderStageCreateInfo vertex_stage_info =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .flags = 0,
        .pNext = NULL,
        .pName = "main",
        .pSpecializationInfo = NULL,
        .stage = VK_SHADER_STAGE_VERTEX_BIT,
        .module = vertex_shader_module, 
    };
    VkPipelineShaderStageCreateInfo fragment_stage_info =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .flags = 0,
        .pNext = NULL,
        .pName = "main",
        .pSpecializationInfo = NULL,
        .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
        .module = fragment_shader_module, 
    };

    VkPipelineShaderStageCreateInfo shader_stages[] = {vertex_stage_info,fragment_stage_info};
/////////////////
//////////BINDING
//static_vertex =(struct Static_vertex*)malloc(sizeof(struct Static_vertex));
VkVertexInputBindingDescription binding_description[1] =
    {
        [0].binding = 0,
        [0].stride = sizeof(Vertex),
        [0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX,

        //[1].binding = 1,
        //[1].stride = sizeof(Snake),
        //[1].inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
    };  
    VkVertexInputAttributeDescription attribute_description[2] =
    {
        [0].binding = 0,
        [0].location = 0,
        [0].format = VK_FORMAT_R32G32B32A32_SFLOAT,
        [0].offset = offsetof(Vertex,pos),
        [1].binding = 0,
        [1].location = 1,
        [1].format = VK_FORMAT_R32G32B32A32_SFLOAT,
        [1].offset = offsetof(Vertex,color),

        //[2].binding = 1,
        //[2].location = 2,
        //[2].format = VK_FORMAT_R32G32B32A32_SFLOAT,
        //[2].offset = offsetof(Snake,snake_pos),
        //[3].binding = 1,
        //[3].location = 3,
        //[3].format = VK_FORMAT_R32G32B32A32_SFLOAT,
        //[3].offset = offsetof(Snake,snake_color),
    };
    VkPipelineVertexInputStateCreateInfo vertex_input_state =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .flags = 0,
        .pNext = NULL,        
        .vertexBindingDescriptionCount = 1,
        .pVertexBindingDescriptions = binding_description,// Optional
        .vertexAttributeDescriptionCount = 2,
        .pVertexAttributeDescriptions = attribute_description, // Optional
    };
    VkPipelineInputAssemblyStateCreateInfo input_assembly_state =   
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .flags = 0,
        .pNext = NULL,        
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = FALSE,        
    };
    VkViewport viewport =
    {
        .x = 0.0f,
        .y = 0.0f,
        .width = (FLOAT) core->width,
        .height = (FLOAT) core->height,
        .minDepth = 0.0f,
        .maxDepth = 1.0f,
    };
    VkRect2D scissor =
    {
        .offset = {0, 0},
        .extent.height = (UINT32)core->height,
        .extent.width = (UINT32)core->width,
    };
    VkPipelineViewportStateCreateInfo viewport_state =
    {
       .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
       .flags = 0,
       .pNext = NULL,
       .viewportCount = 1,
       .pViewports = &viewport,
       .scissorCount = 1,
       .pScissors = &scissor,
    };
    VkPipelineRasterizationStateCreateInfo rasterizer =
    {
       .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
       .flags = 0,
       .pNext = NULL,       
       .depthClampEnable = FALSE,
       .rasterizerDiscardEnable = FALSE,
       .polygonMode = VK_POLYGON_MODE_FILL,
       .lineWidth = 1.0f,
       .cullMode = VK_CULL_MODE_BACK_BIT,
       .frontFace = VK_FRONT_FACE_CLOCKWISE,
       .depthBiasEnable = FALSE,
       .depthBiasConstantFactor = 0.0f,
       .depthBiasClamp = 0.0f,
       .depthBiasSlopeFactor = 0.0f,

    };
    VkPipelineMultisampleStateCreateInfo multisampling =
    {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
      .flags = 0,
      .pNext = NULL,
      .sampleShadingEnable = FALSE,
      .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
      .minSampleShading = 1.0f, // Optional
      .pSampleMask = NULL, // Optional
      .alphaToCoverageEnable = FALSE, // Optional
      .alphaToOneEnable = FALSE, // Optional
    };
   
VkPipelineColorBlendAttachmentState color_blend_attach =
{
    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
    .blendEnable = FALSE,
    .srcColorBlendFactor = VK_BLEND_FACTOR_ONE, // Optional
    .dstColorBlendFactor = VK_BLEND_FACTOR_ZERO, // Optional
    .colorBlendOp = VK_BLEND_OP_ADD, // Optional
    .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE, // Optional
    .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO, // Optional
    .alphaBlendOp = VK_BLEND_OP_ADD, // Optional
};
VkPipelineColorBlendStateCreateInfo color_blend =
{
   .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
   .logicOpEnable = VK_FALSE,
   .logicOp = VK_LOGIC_OP_COPY,// Optional
   .attachmentCount = 1,
   .pAttachments = &color_blend_attach,
   .blendConstants[0] = 0.0f, // Optional
   .blendConstants[1] = 0.0f, // Optional
   .blendConstants[2] = 0.0f,// Optional
   .blendConstants[3] = 0.0f, // Optional
};
   
VkPipelineLayoutCreateInfo pipeline_layout_info =
{
  .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
  .flags = 0,
  .pNext = NULL,
  .setLayoutCount = 0, // Optional
  .pSetLayouts = NULL, // Optional
  .pushConstantRangeCount = 0, // Optional
  .pPushConstantRanges = NULL, // Optional
};
if ((vkCreatePipelineLayout(core->device, &pipeline_layout_info,NULL, &core->pipeline_layout)) == 0) 
{
    printf("PIPELINE LAYOUT CREATED\n");
}
else 
{
    printf ("FAILED TO CREATE PIPELINE LAYOUT BRO SORRY");
    exit(-1);
}

   const VkGraphicsPipelineCreateInfo pipeline_info = 
   {
     .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
     .flags = 0,
     .pNext = NULL,
     .pVertexInputState = &vertex_input_state,
     .pInputAssemblyState = &input_assembly_state,
     .pRasterizationState = &rasterizer,
     .pColorBlendState = &color_blend,
     .pMultisampleState = &multisampling,
     .pViewportState = &viewport_state,
     .pDepthStencilState = NULL,
     .stageCount = 2,
     .pStages = shader_stages,
     .renderPass = core->render_pass,
     .subpass = 0,
     .pDynamicState = NULL, 
     .layout = core->pipeline_layout,
   }; 
   if ((vkCreateGraphicsPipelines(core->device,VK_NULL_HANDLE,1, &pipeline_info,NULL,&core->pipeline)) == 0) 
   {
       printf("PIPELINE CREATED\n");
   }
   else 
   {
       printf ("FAILED TO CREATE PIPELINE BRO SORRY");
       exit(-1);
   }  
   vkDestroyShaderModule(core->device,fragment_shader_module, NULL);
   vkDestroyShaderModule(core->device,vertex_shader_module, NULL);

}
/////DRAW BUFFERS
void init_draw()
{
    core->frame_buffers = (VkFramebuffer*)malloc(sizeof(VkFramebuffer)*core->swapchain_images_count);
    for (SIZE_T i = 0; i < core->swapchain_images_count;++i)
    {
        VkImageView attachtments[] = {core->swapchain_views[i]};
        VkFramebufferCreateInfo frame_buffer_info =
        {
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .flags = 0,
            .pNext = NULL,
            .renderPass = core->render_pass,
            .attachmentCount = 1,
            .pAttachments = attachtments,
            .width = core->width,
            .height = core->height,
            .layers = 1,            
        };
        if (vkCreateFramebuffer(core->device, &frame_buffer_info,NULL, &core->frame_buffers[i]) ==0) 
        {
        printf("FRAMEBUFFER OF INDEX %I64d CREATED\n",i);
        }
        else 
        {
            printf("FAILED TO CREATE FRAMEBUFFERS");
            exit(-1);
        }
    }    
    core->command_buffers = (VkCommandBuffer*)malloc(sizeof(VkCommandBuffer)*core->swapchain_images_count);
    VkCommandBufferAllocateInfo command_buffers_allocation_info =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .pNext = NULL,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandPool = core->command_pool,
        .commandBufferCount = core->swapchain_images_count,
    };
    if (vkAllocateCommandBuffers(core->device, &command_buffers_allocation_info,core->command_buffers) == 0) 
    {
      printf("COMMAND BUFFERS ALLOCATED\n");
    }
    else
    {
      printf("COMMAND BUFFERS ALLOCATION DENIED");
      exit(-1);
    }
    ///////COMMAND BUFFERS RECORD
    for (SIZE_T i = 0; i < core->swapchain_images_count; ++i)
    {
      VkCommandBufferBeginInfo command_being_info =
      {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = 0,
        .pNext = NULL,
        .pInheritanceInfo = NULL,
      };
      if (vkBeginCommandBuffer(core->command_buffers[i], &command_being_info) == 0) 
      {
          printf("COMMAND BUFFER OF INDEX %I64d RECORDING STARTED\n",i);
      }  
      ///COPY VERTEX   
      VkBufferCopy copy_region =
      {
        .srcOffset = 0, // Optional
        .dstOffset = 0, 
        .size = core->vertex_buffer_size,
      };       
      vkCmdCopyBuffer(core->command_buffers[i],core->stage_buffer, core->vertex_buffer, 1, &copy_region);
      //////////RENDERPASS START
      VkClearValue clear_color = {0.0f,0.0f,0.0f,0.0f};                
      VkRenderPassBeginInfo render_pass_begin_info =
      {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .pNext = NULL,
        .renderPass = core->render_pass,
        .renderArea.offset ={0,0},
        .renderArea.extent.width = (UINT32)core->width,
        .renderArea.extent.height = (UINT32)core->height,
        .clearValueCount = 1,
        .pClearValues = &clear_color,
        .framebuffer = core->frame_buffers[i],
      };
      vkCmdBeginRenderPass(core->command_buffers[i], &render_pass_begin_info, VK_SUBPASS_CONTENTS_INLINE);
      vkCmdBindPipeline(core->command_buffers[i],VK_PIPELINE_BIND_POINT_GRAPHICS,core->pipeline);
      /////////VERTEX     
      VkBuffer buffers[] = {core->vertex_buffer,core->vertex_buffer,core->vertex_buffer};
      VkDeviceSize vertex_offsets[] = {core->container_offset,core->food_offset,core->snake_offset};
      vkCmdBindVertexBuffers(core->command_buffers[i],0,1,buffers,vertex_offsets);      
      vkCmdDraw(core->command_buffers[i],630,1,0,0);       
      vkCmdEndRenderPass(core->command_buffers[i]);       
      if (vkEndCommandBuffer(core->command_buffers[i]) == 0) 
      {
        printf("COMMAND BUFFER OF INDEX %I64d SUCCESsFULLY RECORDED\n",i);
      } 
    }     
}
//////DRAW BARRIERS
void init_syncro()
{
       ///////SEMAPHORES
    VkSemaphoreCreateInfo semaphore_info =
    {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .flags = 0,
        .pNext = NULL,
    };  
    VkFenceCreateInfo fence_info =
    {
      .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
      .flags = VK_FENCE_CREATE_SIGNALED_BIT,
      .pNext = NULL,
    };    
   
    for (SIZE_T i = 0; i < FRAME_LAG;++i)
    {
      if (vkCreateSemaphore(core->device, &semaphore_info,NULL, &core->image_available_semaphores[i]) == 0)
      {
          printf("SEMAPHORE 1 ON\n");
      }
      if (vkCreateSemaphore(core->device, &semaphore_info,NULL, &core->image_finished_semaphores[i]) == 0)
      {
          printf("SEMAPHORE 2 ON\n");
      }
      if (vkCreateFence(core->device, &fence_info,NULL, &core->fences[i]) == 0)
      {
          printf("FENCE ON\n");
      }
      
    }  
    
    core->actual_frame = 0;
    core->swapchain_fences = (VkFence*)malloc(sizeof(VkFence)*core->swapchain_images_count);
    for (SIZE_T i = 0; i < core->swapchain_images_count;++i)
    {
      core->swapchain_fences[i] = VK_NULL_HANDLE;
    }
}
/////////RESIZE
void clean_resize()
{
    for (SIZE_T i = 0;i< core->swapchain_images_count;++i)
    {      
      vkDestroyFramebuffer(core->device,core->frame_buffers[i], NULL);
    }
    vkFreeCommandBuffers(core->device,core->command_pool,(UINT32)core->swapchain_images_count, core->command_buffers);
    vkDestroyPipeline(core->device,core->pipeline,NULL);
    vkDestroyPipelineLayout(core->device,core->pipeline_layout,NULL);
    vkDestroyRenderPass(core->device,core->render_pass,NULL);
    for(SIZE_T i = 0; i < core->swapchain_images_count;++i)
    {
        vkDestroyImageView(core->device,core->swapchain_views[i],NULL);
    }
    //vkDestroySwapchainKHR(core->device,core->swapchain,NULL);
}
void handle_resize()
{
    vkDeviceWaitIdle(core->device);
    clean_resize();
    init_swapchain();
    init_renderpass();
    init_pipeline();
    init_draw();
    core->resize = 0;
    

}
///////////DRAW BRO BRO BRO
void loop_draw()
{      
    VkResult check;
    vkWaitForFences(core->device, 1, &core->fences[core->actual_frame], VK_TRUE, UINT64_MAX);
    UINT32 image_index;
    check = vkAcquireNextImageKHR(core->device,core->swapchain, UINT64_MAX,core->image_available_semaphores[core->actual_frame], 0, &image_index);
    game_over();
    update_vertex_data();
            
    if (check == VK_ERROR_OUT_OF_DATE_KHR) 
    {
    core->resize = 1;
    return;
    }    
    if (core->swapchain_fences[image_index] != VK_NULL_HANDLE) 
    {
        vkWaitForFences(core->device, 1, &core->swapchain_fences[image_index],TRUE, UINT64_MAX);
    }
    core->swapchain_fences[image_index] = core->fences[core->actual_frame];
    ///////SUBMIT
    VkSemaphore wait_semaphores[] = {core->image_available_semaphores[core->actual_frame]};
    VkSemaphore signal_semaphores[] = {core->image_finished_semaphores[core->actual_frame]};
    VkPipelineStageFlags wait_stages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    VkSubmitInfo submit_info = 
    {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext = NULL,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = wait_semaphores,
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = signal_semaphores,
        .pWaitDstStageMask = wait_stages,
        .commandBufferCount = 1,
        .pCommandBuffers = &core->command_buffers[image_index],
    };  
    vkResetFences(core->device, 1, &core->fences[core->actual_frame]);
    vkQueueSubmit(core->graphics_queue, 1, &submit_info, core->fences[core->actual_frame]);
    ////PRESENT
    VkSwapchainKHR swapchains[] = {core->swapchain};
    VkPresentInfoKHR present_info =
    {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .pNext = NULL,
        .pResults = NULL,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = signal_semaphores,
        .swapchainCount = 1,
        .pSwapchains = swapchains,
        .pImageIndices = &image_index,
    };
    check = vkQueuePresentKHR(core->present_queue, &present_info);  
    if (check == VK_ERROR_OUT_OF_DATE_KHR || check == VK_SUBOPTIMAL_KHR) 
    {
    core->resize = 1;
    }  
    core->actual_frame = (core->actual_frame + 1) % FRAME_LAG;
}
//////////OUTPUT FUNCTIONS
void init_vk()
{ 
 init_window();
 init_instance();
 init_device();
 init_command_pool(); 
 init_memory_block(); 
 init_swapchain();
 init_renderpass();
 init_vertex_data(); 
 init_pipeline(); 
 init_draw();
 init_syncro();
}
void loop()
{    
    core->quit = 0;      
    MSG msg;    
    timer_start();
    while (core->quit == 0) 
    {               
       while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))  
       {
          TranslateMessage(&msg);
          DispatchMessage(&msg);           
       }
       if (core->resize == 1)
       {
         handle_resize();
       }
       if(game->game_over == 1)
       {
           game->game_running = 0;
       }
       else
       {
         game->game_running = 1;
       }            
       update_positions();
       loop_game();       
       loop_draw();         
       gettimeofday(&core->time_check, NULL);
       core->end = (INT)core->time_check.tv_sec * 1000 + (INT)core->time_check.tv_usec / 1000; 
       if ((core->end-core->start)> core->trigger) 
       {          
          //printf("%I64d seconds\n", (core->end - core->start)/1000);
          core->trigger += 1000;          
       }       
    }                   
    vkDeviceWaitIdle(core->device);           
         
}
void clean()
{
  clean_resize();
  vkDestroySwapchainKHR(core->device,core->swapchain,NULL);

  vkDestroyBuffer(core->device,core->stage_buffer,NULL);  
  vkDestroyBuffer(core->device,core->vertex_buffer,NULL);
   
  vkFreeMemory(core->device,core->stage_memory,NULL);
  vkFreeMemory(core->device,core->block_memory,NULL); 

  for (SIZE_T i = 0; i< FRAME_LAG;++i)
  {
      vkDestroySemaphore(core->device,core->image_finished_semaphores[i],NULL);
      vkDestroySemaphore(core->device,core->image_available_semaphores[i],NULL);
      vkDestroyFence(core->device, core->fences[i], NULL);      
  }
  free(core->swapchain_fences);  
  vkDestroyCommandPool(core->device,core->command_pool,NULL);
  vkDestroyDevice(core->device,NULL);
  vkDestroySurfaceKHR(core->instance,core->surface,NULL);
  vkDestroyInstance(core->instance,NULL);
  DestroyWindow(core->window);  
}
