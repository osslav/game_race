#include "Car.h"

Car::Car()
{
    speed = 0;
    position = rotationTurn = 0;
    drivingDistance = 0;
};

void Car::carTurnLeft()
{
    if (rotationTurn > -maxRotationCar) rotationTurn--;
};


void Car::carTurnRight()
{
    if (rotationTurn < maxRotationCar) rotationTurn++;
};

void Car::gas()
{
    if (speed < maxSpeedCar) speed += 1;//200 - (100 / speed);
}

void Car::withoutGas()
{
    if ((speed > 0) && (rand() % 50)) speed--;
}
void Car::brake()
{
    speed -= 5;
    if (speed < 0) speed = 0;
}


void Car::carGoStraight()
{
    if (rotationTurn > 0) rotationTurn--;
    if (rotationTurn < 0) rotationTurn++;
};


void Car::updateCar()
{
    drivingDistance += speed;
    position += rotationTurn;
};
