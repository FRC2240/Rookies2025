#include <frc/smartdashboard/SmartDashboard.h>
#include "Intake.h"


void Intake::run(bool buttonA)
{
    switch (m_state) {
    case kIDLE:
        // Code for IDLE state
        if (buttonA) {
            m_state = kACTIVE;
        }
        m_roller.Set(0.0);
        
        break;
    case kACTIVE:
        // Code for ACTIVE state
        if (buttonA) {
            m_state = kIDLE;
        }
        m_roller.Set(0.25);
        break;
    case kINTAKE:
        // Code for INTAKE state

        break;
    case kEJECT:
        // Code for EJECT state

        break;
    }

}

void Intake::Test() {

    auto color = m_colorSensor.GetColor();
    frc::SmartDashboard::PutNumber("red", color.red);
    frc::SmartDashboard::PutNumber("green", color.green);
    frc::SmartDashboard::PutNumber("blue", color.blue);

}

Intake::BALL_COLOR Intake::getBallColor() {
    auto color = m_colorSensor.GetColor();

    if (((color.red > REDBALL_RED_MIN) && (color.red < REDBALL_RED_MAX)) &&
        ((color.green > REDBALL_GREEN_MIN) && (color.green < REDBALL_GREEN_MAX)) &&
        ((color.blue > REDBALL_BLUE_MIN) && (color.blue < REDBALL_BLUE_MAX))
        ) {
            return kRED;
        }

   if (((color.red > BLUEBALL_RED_MIN) && (color.red < BLUEBALL_RED_MAX)) &&
        ((color.green > BLUEBALL_GREEN_MIN) && (color.green < BLUEBALL_GREEN_MAX)) &&
        ((color.blue > BLUEBALL_BLUE_MIN) && (color.blue < BLUEBALL_BLUE_MAX))
        ) {
            return kBLUE;
        }   

    return kNONE;
}
