#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include "RoboticArm.h"


RoboticArm *RoboArm;


void _cleanup(int signum)
{
   std::cout << "\nINFO: Caught signal " << signum << std::endl;

   /* Delete all of the robotic-arm objects */
    delete RoboArm;

    exit(signum);
}


int main(void)
{
    /* Two joints robotic arm for the demo */
    RoboArm = new RoboticArm(1);
    
    /* Register a signal handler to exit gracefully */
    signal(SIGINT, _cleanup);
    
    RoboArm->Init();
    /* Input a curve or shape to the roboarm to draw it */
    for(;;) {
        RoboArm->DemoCircle();
        RoboArm->UpdatePosition();
        usleep(5000000);
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}

