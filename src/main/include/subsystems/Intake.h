#include "rev/ColorSensorV3.h"
#include "rev/CANSparkMax.h"
class Intake {
    
    public:
        void Test();
        void Run(bool buttonA);

        enum Ball_Color {
            kRed,
            kBlue,
            kNone
        };

        enum State {
            kIDLE,
            kACTIVE,
            kINTAKE,
            kEJECT
        } m_state;

        Ball_Color getBallColor();
    
    private:
        rev::ColorSensorV3 m_colorSensor{frc::I2C::Port::kOnboard};

        rev::CANSparkMax m_roller{2, rev::CANSparkMax::MotorType::kBrushless};

        rev::CANSparkMax m_hinge{3, rev::CANSparkMax::MotorType::kBrushless};
        rev::SparkMaxPIDController m_pid = m_hinge.GetPIDController();

        //Declares all values used to determine if the ball is red
        const double RedRMin = 0.53;
        const double RedRMax = 0.59;
        const double RedGMin = 0.30;
        const double RedGMax = 0.36;
        const double RedBMin = 0.09;
        const double RedBMax = 0.15;

        //Declares all values used to determine if the ball is blue
        const double BlueRMin = 0.09;
        const double BlueRMax = 0.15;
        const double BlueGMin = 0.33;
        const double BlueGMax = 0.39;
        const double BlueBMin = 0.50;
        const double BlueBMax = 0.56;

};