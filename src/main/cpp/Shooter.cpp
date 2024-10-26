#include "Shooter.h"

void Shooter::Shoot(units::meter_t distance) {
    frc::SmartDashboard::PutNumber("Velocity", m_encoder.GetVelocity());
    m_pidCoeff.kP = frc::SmartDashboard::GetNumber("P Gain", m_pidCoeff.kP);
    m_pid.SetP(m_pidCoeff.kP);

    m_pidCoeff.kFF = frc::SmartDashboard::GetNumber("Feed Forward", m_pidCoeff.kFF);
    m_pid.SetFF(m_pidCoeff.kFF);

    if ((distance >= 6.5_ft) && (distance <= 7.0_ft)) {
        m_pid.SetReference(1250.0, rev::CANSparkMax::ControlType::kVelocity);
    }

    else {
        m_pid.SetReference(0.0, rev::CANSparkMax::ControlType::kVelocity);
    }
}
