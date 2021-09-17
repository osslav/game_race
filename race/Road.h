#ifndef ROAD_H
#define ROAD_H

#include <QPolygon>

struct RoadLine
{

    int wigth, shift;
    RoadLine* next;
    RoadLine* prev;

    RoadLine(int wigth_, int shift_, RoadLine* next_ = nullptr, RoadLine* prev_ = nullptr) { wigth = wigth_; shift = shift_; next = next_; prev = prev_; };

};


class Road
{
private:
    //current fragment
    int shift;
    int lenth;
    void updateFragment();

public:
    int countLine, wigthRoad;
    RoadLine* head;
    RoadLine* tail;

    Road(int countLine_ = 32, int wigthRoad_ = 32);
    void updateRoad(int drivingDistance);

    QPolygon* createRoadPolygon(int wigthWindow, int heightWindow, int positionCar_x, int positionCar_z_num, int positionCar_z_denom);

    ~Road();
};


#endif
