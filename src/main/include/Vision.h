//if 6.5-7 ft to target
//spin 1250 +- 1% rpm
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <vector>
#include <units/length.h>

class Vision {

    public:
        units::meter_t getDistanceToTarget();

    private:
    std::shared_ptr<nt::NetworkTable> m_left_table = 
        nt::NetworkTableInstance::GetDefault().GetTable("limelight-dev");
    std::vector<double> m_zero_vector = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

};