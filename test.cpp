#include "movement.h"
#include <unistd.h>

int main()
{
    usleep(4000000);
    Movement obj;
    float movementSpeed = 0.3;
    for (int i = 0; i <= 100;i++){
    	obj.left();
    }
    obj.deactivate();
    return 0;
}
