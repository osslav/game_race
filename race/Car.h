#ifndef CAR_H
#define CAR_H

#include <QRandomGenerator>

const int maxRotationCar = 8;
const int maxSpeedCar = 200;

class Car
{
private:
    int position;
    int rotationTurn;
    int speed;

public:
    Car();
    int getPosition() { return position; };
    int getSpeed() { return speed; };
    void addPosition(int shift) { position += shift; };

    void carTurnLeft();
    void carTurnRight();
    void carGoStraight();

    void gas();
    void withoutGas();
    void brake();

    int drivingDistance;

    void updateCar();

};


#endif // CAR_H
