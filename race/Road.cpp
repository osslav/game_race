#include "Road.h"

Road::Road(int countLine_, int wigthRoad_)
{
    countLine = countLine_;
    wigthRoad = wigthRoad_;
    if (countLine == 0)
    {
        head = tail = nullptr;
        return;
    }

    head = tail = new RoadLine(wigthRoad, 0);
    countLine--;
    updateFragment();

    while(countLine_ > 0)
    {
        RoadLine* oldTail = tail;
        tail = new RoadLine(wigthRoad, tail->shift, nullptr, oldTail);
        if (tail->shift < shift) tail->shift++;
        if (tail->shift > shift) tail->shift--;

        oldTail->next = tail;

        countLine_--;
        lenth--;
        if (!lenth) updateFragment();
    }
}

void Road::updateFragment()
{
    shift = (rand() % 14) - 6;
    if (!shift) lenth = (rand() % 20) + 20;
    else lenth = (rand() % 10) + 10;
};

void Road::updateRoad(int drivingDistance)
{
    while (drivingDistance > 0)
    {
        RoadLine* oldHead = head;
        head = head->next;
        head->prev = nullptr;

        oldHead->next = nullptr;
        oldHead->prev = tail;
        tail->next = oldHead;

        tail = oldHead;
        tail->shift = tail->prev->shift;
        if (tail->shift < shift) tail->shift++;
        if (tail->shift > shift) tail->shift--;

        lenth--;
        if (!lenth) updateFragment();

        drivingDistance--;
    }
}

QPoint pointProjection(int x, int y, int z_num, int z_denom, int screenX, int screenY, int screenZ)
{
    return QPoint(x*screenZ*z_denom/z_num + screenX, y*screenZ*z_denom/z_num + screenY);
}

QPolygon* Road::createRoadPolygon(int wigthWindow, int heightWindow, int positionCar_x, int positionCar_z_num, int positionCar_z_denom)
{
    QPolygon* polygonRoad = new QPolygon(countLine * 2);

    RoadLine* currentLine = head;
    int shift = -positionCar_x;
    for(int i = 0; i < countLine; i++)
    {

        QPoint left = pointProjection(-(currentLine->wigth / 2) + shift, 40, positionCar_z_denom*(i + 1) - positionCar_z_num, positionCar_z_denom, wigthWindow / 2, heightWindow / 2, wigthWindow / 128);
        polygonRoad->setPoint(i, left);

        QPoint right = pointProjection((currentLine->wigth / 2) + shift, 40, positionCar_z_denom*(i + 1) - positionCar_z_num, positionCar_z_denom, wigthWindow / 2, heightWindow / 2, wigthWindow / 128);
        polygonRoad->setPoint(countLine * 2 - i - 1, right);

        currentLine = currentLine->next;

        if (currentLine) shift = shift + currentLine->shift;
    }

    return polygonRoad;
};

Road::~Road()
{
   if (countLine)
   {
       RoadLine* currentLine = head->next;
       while(currentLine)
       {
           delete head;
           head = currentLine;
           currentLine = currentLine->next;
       }
   }
}
