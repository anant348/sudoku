#ifndef GRID_H
#define GRID_H
#include "cell.h"
#include <QWidget>
#include <QGridLayout>
#include <QPainter>
#include "buffer.h"
class grid:public QWidget{
   QGridLayout *layout;
   cell* Cell[9][9];

   protected:
   void paintEvent(QPaintEvent *);
   public:
   grid(QWidget *parent=0);
   inline QGridLayout* getLayout()
   {return layout;}
   cell* getCell(int,int);
   buffer buf;
};
#endif // GRID_H

