// In this quiz you'll implement the global kinematic model.
// The dynamic model is based on bicycle kinematic model.
#include <math.h>
#include <iostream>
#include "Eigen-3.3/Eigen/Core"

using Eigen::VectorXd;

//
// Helper functions
//
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

const double Lf = 2;

// Return the next state.
VectorXd globalKinematic(const VectorXd &state, 
                         const VectorXd &actuators, double dt);

int main() {
  // [x, y, psi, v]
  VectorXd state(4);
  // [delta, v]
  VectorXd actuators(2);

  state << 0, 0, deg2rad(45), 1;
  actuators << deg2rad(5), 1;

  // should be [0.212132, 0.212132, 0.798488, 1.3]
  auto next_state = globalKinematic(state, actuators, 0.3);

  std::cout << next_state << std::endl;
}

VectorXd globalKinematic(const VectorXd &state, 
                         const VectorXd &actuators, double dt) {
  // Create a new vector for the next state.
  VectorXd next_state(state.size());
  double x = state(0);
  double y = state(1);
  double psi = state(2);
  double v = state(3);
  double delta = actuators(0);
  double a = actuators(1);

  next_state(0) = x + v * cos(psi) * dt;
  next_state(1) = y + v * sin(psi) * dt;
  next_state(2) = psi + v / Lf * delta * dt;
  next_state(3) = v + a * dt;
  return next_state;
}