#pragma once
#include <iostream>
#include <stdint.h>
#include "Linux-DC-Motor/Motor.h"
#include "Linux-Quadrature-Encoder/QuadratureEncoder.h"

class RoboticArm
{
    public:
        explicit RoboticArm(const uint16_t &joints_nr);
        virtual ~RoboticArm(void);

        void UpdatePosition(void);

    private:
        uint16_t _joints_nr;

#ifndef VISUAL_ENCODER
        std::vector<QuadratureEncoder*> angular_joints;
#else
        std::vector<VisualEncoder*> angular_joints;
#endif
        /* Movement DC motors */
        std::vector<Motor*> angular_rotors;

};
