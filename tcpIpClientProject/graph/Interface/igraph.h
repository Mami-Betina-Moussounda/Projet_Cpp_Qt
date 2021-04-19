#ifndef IGRAPH_H
#define IGRAPH_H

#include <QWidget>
#include <QString>

class IGraph
{


public:
    IGraph()
    {

    }

    virtual ~ IGraph()
    {}

   virtual  void getTempData(double &temperature, long long &temperatureTime)=0;

   virtual void clearLists()=0;
   virtual void showGraph()=0;

};

#endif // IGRAPH_H
