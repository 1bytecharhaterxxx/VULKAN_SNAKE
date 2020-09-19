#include "core.h"

int WINAPI WinMain(HINSTANCE Hinstance, HINSTANCE hprevinstance, LPSTR pcmdline, int ncmdshow) 
{ 
    core = (struct Core*)malloc(sizeof(struct Core));
    game = (struct Game*)malloc(sizeof(struct Game));
    core->hinstance = Hinstance; 
    core->swapchain = VK_NULL_HANDLE;  
    game->speed = 6;    
    init_vk();
    loop();
    vkDeviceWaitIdle(core->device); 
    clean();       
    free(game);
    free(core);    
    return 0;
}