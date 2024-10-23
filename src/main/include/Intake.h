#include "rev/ColorSensorV3.h"
#include <rev/CANSparkMax.h>
#include <frc/Timer.h>
#include "units/time.h"
#include "frc/DriverStation.h"


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
    BALL_COLOR correctColor = kNONE;
    
    void Init();
    void Periodic(bool buttonA);

  private:

    const double TOLERANCE = 0.04;

    const double REDBALL_RED       = 0.56;
    const double REDBALL_GREEN     = 0.33;
    const double REDBALL_BLUE      = 0.12;
    const double REDBALL_RED_MIN   = REDBALL_RED - TOLERANCE;
    const double REDBALL_RED_MAX   = REDBALL_RED + TOLERANCE;
    const double REDBALL_GREEN_MIN = REDBALL_GREEN - TOLERANCE;
    const double REDBALL_GREEN_MAX = REDBALL_GREEN + TOLERANCE;
    const double REDBALL_BLUE_MIN  = REDBALL_BLUE - TOLERANCE;
    const double REDBALL_BLUE_MAX  = REDBALL_BLUE + TOLERANCE;

    const double BLUEBALL_RED       = 0.12;
    const double BLUEBALL_GREEN     = 0.36;
    const double BLUEBALL_BLUE      = 0.53;
    const double BLUEBALL_RED_MIN   = BLUEBALL_RED - TOLERANCE;
    const double BLUEBALL_RED_MAX   = BLUEBALL_RED + TOLERANCE;
    const double BLUEBALL_GREEN_MIN = BLUEBALL_GREEN - TOLERANCE;
    const double BLUEBALL_GREEN_MAX = BLUEBALL_GREEN + TOLERANCE;
    const double BLUEBALL_BLUE_MIN  = BLUEBALL_BLUE - TOLERANCE;
    const double BLUEBALL_BLUE_MAX  = BLUEBALL_BLUE + TOLERANCE;

    frc::Timer m_timer;

    rev::ColorSensorV3 m_colorSensor{frc::I2C::Port::kOnboard};

    rev::CANSparkMax m_roller{2, rev::CANSparkMax::MotorType::kBrushless};
    rev::CANSparkMax m_hinge{3, rev::CANSparkMax::MotorType::kBrushless};
    rev::SparkMaxRelativeEncoder m_encoder = m_hinge.GetEncoder();
    rev::SparkMaxPIDController m_pid = m_hinge.GetPIDController();

    std::optional<frc::DriverStation::Alliance> alliance = frc::DriverStation::GetAlliance();

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

    pidCoeff m_pidCoeff{0.1, 0.0, 0.0, 0.0, 0.0, -1.0, 1.0};
    
};

