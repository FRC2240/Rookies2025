#include "rev/ColorSensorV3.h"
#include <rev/CANSparkMax.h>

class Intake {
    public:

        enum BALL_COLOR
    {
        kRED,
        kBLUE,
        kNONE
    };

    enum STATE
    {
        kIDLE,
        kACTIVE,
        kINTAKE,
        kEJECT
    } m_state;

        void Test();
        BALL_COLOR getBallColor();

        void run(bool buttonA);

    private:
    const double TOLERANCE          = 0.04;

    const double REDBALL_RED        = 0.56;
    const double REDBALL_GREEN      = 0.33;
    const double REDBALL_BLUE       = 0.12;

    const double BLUEBALL_RED       = 0.12;
    const double BLUEBALL_GREEN     = 0.36;
    const double BLUEBALL_BLUE      = 0.53;

    const double REDBALL_RED_MIN    = REDBALL_RED - TOLERANCE;
    const double REDBALL_RED_MAX    = REDBALL_RED + TOLERANCE;
    const double REDBALL_GREEN_MIN  = REDBALL_GREEN - TOLERANCE;
    const double REDBALL_GREEN_MAX  = REDBALL_GREEN + TOLERANCE;
    const double REDBALL_BLUE_MIN   = REDBALL_BLUE - TOLERANCE;
    const double REDBALL_BLUE_MAX   = REDBALL_BLUE + TOLERANCE;

    const double BLUEBALL_RED_MIN   = BLUEBALL_RED - TOLERANCE;
    const double BLUEBALL_RED_MAX    = BLUEBALL_RED + TOLERANCE;
    const double BLUEBALL_GREEN_MIN = BLUEBALL_GREEN - TOLERANCE;
    const double BLUEBALL_GREEN_MAX = BLUEBALL_GREEN + TOLERANCE;
    const double BLUEBALL_BLUE_MIN  = BLUEBALL_BLUE - TOLERANCE;
    const double BLUEBALL_BLUE_MAX  = BLUEBALL_BLUE + TOLERANCE;

    rev::ColorSensorV3 m_colorSensor{frc::I2C::Port::kOnboard};

    rev::CANSparkMax m_roller{1, rev::CANSparkMax::MotorType::kBrushless};
};