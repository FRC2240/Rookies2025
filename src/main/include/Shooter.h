#include <rev/CANSparkMax.h>
#include <units/length.h>
#include <frc/smartdashboard/SmartDashboard.h>

class Shooter {
    public:
        void Shoot(units::meter_t distance);
        void Init() {
            frc::SmartDashboard::PutNumber("P Gain", m_pidCoeff.kP);
            m_pid.SetP(m_pidCoeff.kP);

            m_pidCoeff.kFF = frc::SmartDashboard::PutNumber("Feed Forward", m_pidCoeff.kFF);
            m_pid.SetFF(m_pidCoeff.kFF);
        }

        private:
        rev::CANSparkMax m_left{2, rev::CANSparkMax::MotorType::kBrushless};
        rev::SparkMaxRelativeEncoder m_encoder = m_left.GetEncoder();
        rev::SparkMaxPIDController m_pid = m_left.GetPIDController();

        struct pidCoeff {
            double kP;
            double kI;
            double kD;
            double kIz;
            double kFF;
            double kMinOutput;
            double kMaxOutput;
        };

        void setP(double pGain) { m_pidCoeff.kP = pGain; }

        pidCoeff m_pidCoeff{0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 1.0};
};