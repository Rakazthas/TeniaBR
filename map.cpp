#include "map.h"
#include <QVector2D>
#include <QImage>



map::map()
{

}

map::map(QImage src)
{
    this->source=src;
    int cpt=0;
    QVector2D tab[source.width()*source.height()];
    for(int x=0;x<source.width();x++){
        for(int y=0;y<source.height();y++){
            if(qGray(source.pixel(x,y))==0){
                tab[cpt]=QVector2D(x,y);
                cpt++;
            }
        }
    }
}


