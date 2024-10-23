#include <frc/smartdashboard/SmartDashboard.h>
#include "Intake.h"
#include <iostream>


void Intake::Init() {
    double sensorColors[3] = {0,0,0};
    frc::SmartDashboard::PutString("Intake State", "Idle");
    frc::SmartDashboard::PutNumberArray("Color: Sensor Color", sensorColors);
    frc::SmartDashboard::PutNumber("P Gain", m_pidCoeff.kP);
    frc::SmartDashboard::PutNumber("Hinge Pos", 0);
    m_pid.SetP(m_pidCoeff.kP);
}

void Intake::Periodic(bool buttonA) {
    frc::SmartDashboard::PutNumber("Hinge Pos", m_encoder.GetPosition());
    m_pidCoeff.kP = frc::SmartDashboard::GetNumber("P Gain", m_pidCoeff.kP);
    m_pid.SetP(m_pidCoeff.kP);


    std::optional<frc::DriverStation::Alliance> alliance = frc::DriverStation::GetAlliance();

    if (alliance == frc::DriverStation::Alliance::kRed) {
        correctColor = kRED;
    }
    if (alliance == frc::DriverStation::Alliance::kBlue) {
        correctColor = kBLUE;
    }

    BALL_COLOR currentColor = getBallColor();
    switch (m_state) {
    case kIDLE:
        frc::SmartDashboard::PutString("Intake State", "Idle");
        // Code for IDLE state
        if (buttonA) {
            m_state = kACTIVE;
        }
        m_roller.Set(0.0);
        m_pid.SetReference(0.0, rev::CANSparkMax::ControlType::kPosition);
        
        break;
    case kACTIVE:
        frc::SmartDashboard::PutString("Intake State", "Active");

        // Code for ACTIVE state
        if (buttonA) {
            m_state = kIDLE;
        }
        if (currentColor == correctColor) {
            m_state = kINTAKE;
            // Starts timer
            m_timer.Reset();
            m_timer.Start();
            break;
        } else if (currentColor == !correctColor && currentColor != kNONE) {
            m_state = kEJECT;
            // Starts timer
            m_timer.Reset();
            m_timer.Start();
            break;
        }
        m_roller.Set(0.25);    
        m_pid.SetReference(80.5, rev::CANSparkMax::ControlType::kPosition);
        break;
    case kINTAKE:
        frc::SmartDashboard::PutString("Intake State", "Intake");
        
        if (m_timer.Get() > 1_s) {
            m_hinge.Set(0);
            m_state = kIDLE;
        }
        break;
    case kEJECT:
        frc::SmartDashboard::PutString("Intake State", "Eject");
        // Code for EJECT state
        m_roller.Set(-0.25);

        if (m_timer.Get() > 1_s) {
            m_roller.Set(0);
            m_state = kACTIVE;
        }
        break;
    }
}

void Intake::Test() {

    auto color = m_colorSensor.GetColor();
    frc::Color{
    frc::SmartDashboard::GetNumber("red", 0),
    frc::SmartDashboard::GetNumber("green", 0),
    frc::SmartDashboard::GetNumber("blue", 0),};


    //frc::SmartDashboard::PutNumber("red", color.red);
    //frc::SmartDashboard::PutNumber("green", color.green);
    //frc::SmartDashboard::PutNumber("blue", color.blue);

}

Intake::BALL_COLOR Intake::getBallColor() {
    auto color = m_colorSensor.GetColor();
    /*
    frc::Color color = {
        frc::SmartDashboard::GetNumber("red", 0),
        frc::SmartDashboard::GetNumber("green", 0),
        frc::SmartDashboard::GetNumber("blue", 0)
    };
    */
    
    double sensorColors[3] = {color.red, color.green, color.blue};
    frc::SmartDashboard::PutNumberArray("Sensor Color", sensorColors);

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
