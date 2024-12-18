// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "frc/smartdashboard/SmartDashboard.h"

void Robot::RobotInit() {
  frc::SmartDashboard::PutNumber("red", 0);
  frc::SmartDashboard::PutNumber("green", 0);
  frc::SmartDashboard::PutNumber("blue", 0.5);

  //m_intake.Init();
  m_shooter.Init();
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  //m_intake.Periodic(m_stick.GetAButtonPressed());
  auto distance = m_vision.getDistanceToTarget();
  m_shooter.Shoot(distance);
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {
  //m_intake.Test();
}

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
