#ifndef CELL_H
#define CELL_H
#include <QLineEdit>
#include <QFont>
#include "sudokusolver.h"
class grid;
class buffer;
class cell:public QLineEdit{
   QFont *font;
   public:
   int row,column;
   buffer* buf;
   grid *g;
   cell(QWidget *parent=0);
   ~cell();
   inline void setBuffer(buffer* s){buf=s;}
   inline void setGrid(grid *s){g=s;}
   protected:
   void keyPressEvent(QKeyEvent *);
};

#endif // CELL_H

