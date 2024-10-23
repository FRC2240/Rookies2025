#include <frc/smartdashboard/SmartDashboard.h>
#include "Intake.h"

void Intake::run(bool buttonA)
{
    switch (m_state) {
    case kIDLE:

        if (buttonA) {
            m_state = kACTIVE;
        }

        break;
    case kACTIVE:
        m_roller.Set(0.25);
        if (buttonA) {
            m_state = kIDLE;
        }
        break;
    case kINTAKE:

        break;
    case kEJECT:

        break;
    }
}




void Intake::Test() {

    auto color = m_colorSensor.GetColor();
    frc::Color{   
    //frc::SmartDashboard::GetNumber("red", 0),
    //frc::SmartDashboard::GetNumber("green", 0),
    //frc::SmartDashboard::GetNumber("blue", 0)};

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