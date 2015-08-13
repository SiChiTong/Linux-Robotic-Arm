#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>
#include <pthread.h>
#include "RoboticArm.h"


RoboticArm *RoboArm;
Point coordinates;


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
    RoboArm = new RoboticArm();
    
    /* Register a signal handler to exit gracefully */
    signal(SIGINT, _cleanup);

#ifdef RT_PRIORITY
    /* Higher priority for interrupt procesisng */
    /* https://rt.wiki.kernel.org/index.php/HOWTO:_Build_an_RT-application */
    struct sched_param sp = { .sched_priority = 99 };
    if( sched_setscheduler(0, SCHED_FIFO, &sp) != 0 ) {
        std::cout << "WARNING: Failed to increase process priority!" << std::endl;
    }
#endif

    RoboArm->Init();
    usleep(2E06);
    
    /* Input a curve or shape to the roboarm to draw it */
    for(;;) {
        RoboArm->GetPosition(coordinates);
        
        /* Show the cartesian coordinates */
        std::cout << "( x: "  << coordinates.x
                  <<  " | y: "  << coordinates.y
                  <<  " | z: " << coordinates.z
                  << " )" << std::endl;

        /* Debug information displayed */
        RoboArm->DebugMessages();

        /* Command the robot to a new position */
        //Point new_coordinates;
        //new_coordinates.x = 0.02;
        //new_coordinates.y = 0.03;
        RoboArm->SetPosition(coordinates);

        usleep(3E06);
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}

