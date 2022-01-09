#ifndef MAP_H
#define MAP_H

#include <QVector2D>
#include <QImage>

class map
{
public:
    QVector2D vertices;
    QImage source;

    map();
    map(QImage src);

};

#endif // MAP_H
