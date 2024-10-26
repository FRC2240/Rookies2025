#include <frc/smartdashboard/SmartDashboard.h>
#include "subsystems/Intake.h"

void Intake::Run(bool buttonA) {
    switch (m_state) {
    
    case kIDLE:
        m_roller.Set(0.0);
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
    frc::SmartDashboard::PutNumber("red", color.red);
    frc::SmartDashboard::PutNumber("green", color.green);
    frc::SmartDashboard::PutNumber("blue", color.blue);
}

Intake::Ball_Color Intake::getBallColor() {
    auto color = m_colorSensor.GetColor();
    if ((((color.red > RedRMin) && (color.red < RedRMax)) && 
    ((color.green > RedGMin) && (color.green < RedGMax))) && 
    ((color.blue> RedBMin) && (color.blue < RedBMax))) 
    {
        return kRed;
    }

    else if ((((color.red > BlueRMin) && (color.red < BlueRMax)) && 
    ((color.green > BlueGMin) && (color.green < BlueGMax))) && 
    ((color.blue> BlueBMin) && (color.blue < BlueRMax))) 
    {
        return kBlue;
    }

    return kNone;
}