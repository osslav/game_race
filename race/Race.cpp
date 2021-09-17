#include "Race.h"

Race::Race()
{
    //setSize(1280, 720);
    setMinimumSize(800, 480);
    setMaximumSize(1280, 720);
    setStyleSheet("background-color:black;");

    pressedUp = pressedDown = pressedLeft = pressedRight = false;
    score = 0;

    road = new Road(64, 128);
    car = new Car();

    markingLinesOnFirstRoadLine = false;

    carStraight.load("car_straight.png");
    carTurnLeft.load("car_left.png");
    carTurnRight.load("car_right.png");
    background.load("background_synthwave.png");
    //speedometer.load("speedometer_8bit.png");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(newFrame()));
    timer->start(50);   //20 fps
}


void Race::newFrame()
{
    if (pressedLeft && !pressedRight) car->carTurnLeft();
    if (pressedRight && !pressedLeft) car->carTurnRight();
    if (pressedRight == pressedLeft) car->carGoStraight();

    if (pressedDown) car->brake();
    else
        if (pressedUp) car->gas();
        else car->withoutGas();

    car->updateCar();

    while (car->drivingDistance >= 200)
    {
        car->addPosition(-road->head->shift);
        road->updateRoad(1);
        score++;
        markingLinesOnFirstRoadLine = !markingLinesOnFirstRoadLine;
        car->drivingDistance -= 200;
    }

    update();
}


void Race::drawMarkingLines(QPainter* painter, QPolygon* polyRoad)
{
    painter->setPen(QPen(QBrush("#FFF"), 1));
    painter->setBrush(QBrush(QColor("#FFF")));

    QPolygon currentSegment(4);

    for (int i = (markingLinesOnFirstRoadLine ? 0 : 1); (i + 1) < road->countLine; i += 2)
    {

        currentSegment.setPoint(0,
                                (polyRoad->point(road->countLine * 2 - i - 1).x() - polyRoad->point(i).x()) * 63 / 128 + polyRoad->point(i).x(),
                                polyRoad->point(i).y());

        currentSegment.setPoint(1,
                                (polyRoad->point(road->countLine * 2 - i - 1).x() - polyRoad->point(i).x()) * 65 / 128 + polyRoad->point(i).x(),
                                polyRoad->point(i).y());

       currentSegment.setPoint(2,
                                (polyRoad->point(road->countLine * 2 - i - 2).x() - polyRoad->point(i + 1).x()) * 65 / 128 + polyRoad->point(i + 1).x(),
                                polyRoad->point(i + 1).y());

       currentSegment.setPoint(3,
                               (polyRoad->point(road->countLine * 2 - i - 2).x() - polyRoad->point(i + 1).x()) * 63 / 128 + polyRoad->point(i + 1).x(),
                               polyRoad->point(i + 1).y());

        painter->drawPolygon(currentSegment);
    }

}


void Race::drawSpeedometer(QPainter* painter)
{
    painter->setPen(QPen(QBrush("#FFC"), 1));
    painter->setBrush(QBrush(QColor("#FFC")));
/*
    QPainterPath path;


    path.moveTo(this->width() * 8 / 10, this->height() - 5);
    path.quadTo(this->width() * 8 / 10, this->height() * 9 / 10, this->width() - 5, this->height() * 9 / 10);
    path.lineTo(this->width() - 5, this->height() * 91 / 100);
    path.quadTo(this->width() * 85 / 100, this->height() * 9 / 10, this->width() * 85 / 100, this->height() - 5);
    path.lineTo(this->width() * 8 / 10, this->height() - 5);

    path.addRect(this->width() * 8 / 10, this->height() * 9 / 10, this->width() * 1 / 10, this->height() * 1 / 10);


    painter->drawPath(path);

    int counter = 0;
    while(counter < 200)
    {
        painter->drawLine(this->width(), this->height(), sqrt(20 - (counter - this->width())^2 ), this->height() - counter);

        counter++;
    }*/

    painter->drawRect(this->width() * 8 / 10, this->height() * 19/20, this->width() * car->getSpeed() / (5 * maxSpeedCar), this->height() / 20);
}

void Race::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.setPen(QPen(QBrush("#888"), 1));
    painter.setBrush(QBrush(QColor("#888")));

    QPolygon* polyRoad = road->createRoadPolygon(this->width(), this->height(), car->getPosition(), car->drivingDistance, maxSpeedCar);
    painter.drawPolygon(*polyRoad);

    drawMarkingLines(&painter, polyRoad);

    //int carSize = this->height() / 5;
    QRect carRect((this->width() / 16) * 6, this->height() - (this->width() / 4),  this->width() / 4,  this->width() / 4);
    if (pressedLeft && !pressedRight) painter.drawImage(carRect, carTurnLeft);
    if (pressedRight && !pressedLeft) painter.drawImage(carRect, carTurnRight);
    if (pressedRight == pressedLeft) painter.drawImage(carRect, carStraight);

    QRect bacgroundRect(0, 0,  this->width() ,  this->height() / 2);
    painter.drawImage(bacgroundRect, background);

    drawSpeedometer(&painter);

    QFont font = painter.font();
    font.setPixelSize(this->width() / 40);
    painter.setFont(font);

    painter.drawText(0, this->width() / 40, QString::number(score));
}

void Race::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();

    if (key == Qt::Key_Left) pressedLeft = true;

    if (key == Qt::Key_Right) pressedRight = true;

    if (key == Qt::Key_Up) pressedUp = true;

    if (key == Qt::Key_Down) pressedDown = true;

    QWidget::keyPressEvent(e);
};

void Race::keyReleaseEvent(QKeyEvent *e)
{
    int key = e->key();

    if (key == Qt::Key_Left) pressedLeft = false;

    if (key == Qt::Key_Right) pressedRight = false;

    if (key == Qt::Key_Up) pressedUp = false;

    if (key == Qt::Key_Down) pressedDown = false;

    QWidget::keyReleaseEvent(e);
};


Race::~Race()
{
    delete road;
    delete timer;
    delete car;
};
