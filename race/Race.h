#ifndef RACE_H
#define RACE_H


#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include "Road.h"
#include "Car.h"

class Race : public QWidget {
    Q_OBJECT

  public:
    Race();
    ~Race();

    void drawMarkingLines(QPainter* painter, QPolygon* polyRoad);
    void drawSpeedometer(QPainter* painter);

private slots:
    void paintEvent(QPaintEvent *event);    
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);


    void newFrame();

private:
    Road* road;
    Car* car;

    int score;

    QImage carStraight;
    QImage carTurnLeft;
    QImage carTurnRight;

    QImage background;

    //QImage speedometer;

    bool pressedUp;
    bool pressedDown;
    bool pressedLeft;
    bool pressedRight;

    bool markingLinesOnFirstRoadLine;

    QTimer *timer;
};


#endif
