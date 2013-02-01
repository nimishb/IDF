#include "SingleCameraController.hh"

using namespace idf;

SingleCameraController::SingleCameraController(
  const Input& panInput, const Input& tiltInput, const Input& spinInput, const Input& zoomInput) :
    pan(panInput), tilt(tiltInput), spin(spinInput), zoom(zoomInput) {}

void SingleCameraController::addDeadband(const Deadband& deadband) {
    pan.addDeadband(deadband);
    tilt.addDeadband(deadband);
    spin.addDeadband(deadband);
    zoom.addDeadband(deadband);
}

void SingleCameraController::clearDeadbands() {
    pan.clearDeadbands();
    tilt.clearDeadbands();
    spin.clearDeadbands();
    zoom.clearDeadbands();
}

double SingleCameraController::getCommandedPan() const {
    return pan.getNormalizedValue();
}

double SingleCameraController::getCommandedTilt() const {
    return tilt.getNormalizedValue();
}

double SingleCameraController::getCommandedSpin() const {
    return spin.getNormalizedValue();
}

double SingleCameraController::getCommandedZoom() const {
    return zoom.getNormalizedValue();
}

SingleCameraController* SingleCameraController::createInstance(const WingMan& wingMan) {
    CompositeInput* zoom = new CompositeInput();
    zoom->addInput(wingMan.hatNorth);
    zoom->addInput(wingMan.hatSouth, -1);

    SingleCameraController *controller =
      new SingleCameraController(wingMan.twist, wingMan.forwardBackwardPivot,
      wingMan.leftRightPivot, *zoom);

    controller->pan.setInverted(true);
    controller->tilt.setInverted(true);

    return controller;
}

SingleCameraController* SingleCameraController::createInstance(const SpaceExplorer& spaceExplorer) {
    SingleCameraController *controller =
      new SingleCameraController(
      spaceExplorer.twist,
      spaceExplorer.forwardBackwardPivot,
      spaceExplorer.leftRightPivot,
      spaceExplorer.forwardBackwardTranslation);

    controller->pan.setInverted(true);
    controller->tilt.setInverted(true);
    controller->spin.setInverted(true);
    controller->zoom.setInverted(true);

    return controller;
}

SingleCameraController* SingleCameraController::createInstance(const SpaceNavigator& spaceNavigator) {
    SingleCameraController *controller =
      new SingleCameraController(
      spaceNavigator.twist,
      spaceNavigator.forwardBackwardPivot,
      spaceNavigator.leftRightPivot,
      spaceNavigator.forwardBackwardTranslation);

    controller->pan.setInverted(true);
    controller->tilt.setInverted(true);
    controller->spin.setInverted(true);
    controller->zoom.setInverted(true);

    return controller;
}

SingleCameraController* SingleCameraController::createInstance(const Gravis& gravis) {
    CompositeInput* pan = new CompositeInput();
    pan->addInput(gravis.directionalPadLeft);
    pan->addInput(gravis.directionalPadRight, -1);

    CompositeInput* tilt = new CompositeInput();
    tilt->addInput(gravis.directionalPadUp);
    tilt->addInput(gravis.directionalPadDown, -1);

    CompositeInput* spin = new CompositeInput();
    spin->addInput(gravis.leftBumper1);
    spin->addInput(gravis.rightBumper1, -1);

    CompositeInput* zoom = new CompositeInput();
    zoom->addInput(gravis.westButton);
    zoom->addInput(gravis.southButton, -1);

    return new SingleCameraController(*pan, *tilt, *spin, *zoom);
}

SingleCameraController* SingleCameraController::createInstance(const DualShock3& dualShock3) {
    CompositeInput* pan = new CompositeInput();
    pan->addInput(dualShock3.directionalPadLeft);
    pan->addInput(dualShock3.directionalPadRight, -1);

    CompositeInput* tilt = new CompositeInput();
    tilt->addInput(dualShock3.directionalPadUp, -1);
    tilt->addInput(dualShock3.directionalPadDown);

    CompositeInput* spin = new CompositeInput();
    spin->addInput(dualShock3.leftBumper, -1);
    spin->addInput(dualShock3.rightBumper);

    CompositeInput* zoom = new CompositeInput();
    zoom->addInput(dualShock3.circleButton);
    zoom->addInput(dualShock3.squareButton, -1);

    SingleCameraController* controller = new SingleCameraController(*pan, *tilt, *spin, *zoom);

    return controller;
}

SingleCameraController* SingleCameraController::createInstance(const VirtualLayout& virtualLayout) {
    return new SingleCameraController(
      virtualLayout.leftRightRotation,
      virtualLayout.upDownRotation,
      virtualLayout.clockwiseCounterclockwiseRotation,
      virtualLayout.inOutTranslation);
}

SingleCameraController* SingleCameraController::createInstance(const ThrustMaster& thrustMaster) {
    SingleCameraController *controller =
      new SingleCameraController(
      thrustMaster.twist,
      thrustMaster.forwardBackwardPivot,
      thrustMaster.leftRightPivot,
      thrustMaster.forwardBackwardTranslation);

    controller->tilt.setInverted(true);
    controller->pan.setInverted(true);

    return controller;
}

SingleCameraController* SingleCameraController::createInstance(const IndustrialProducts& industrialProducts) {
    SingleCameraController *controller =
      new SingleCameraController(
      industrialProducts.twist,
      industrialProducts.forwardBackwardPivot,
      industrialProducts.leftRightPivot,
      industrialProducts.hatUpDownPivot);

    controller->pan.setInverted(true);

    return controller;
}

SingleCameraController* SingleCameraController::createInstance(const IndustrialProducts2& industrialProducts2) {
    CompositeInput* zoom = new CompositeInput();
    zoom->addInput(industrialProducts2.hatNorth);
    zoom->addInput(industrialProducts2.hatSouth, -1);

    SingleCameraController *controller =
      new SingleCameraController(
      industrialProducts2.twist,
      industrialProducts2.forwardBackwardPivot,
      industrialProducts2.leftRightPivot,
      *zoom);

    controller->pan.setInverted(true);
    controller->tilt.setInverted(true);

    return controller;
}
