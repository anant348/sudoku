#include "grid.h"
#include "cell.h"
#include "buffer.h"
grid::grid(QWidget *parent):QWidget(parent){
   layout = new QGridLayout;
   for(int i=0;i<9;i++)
      for(int j=0;j<9;j++){
         Cell[i][j]=new cell;
         Cell[i][j]->row=i;
         Cell[i][j]->column=j;
         Cell[i][j]->setBuffer(&buf);
         Cell[i][j]->setGrid(this);
         layout->addWidget(Cell[i][j],i,j);
      }
   setLayout(layout);
   layout->setVerticalSpacing(0);
   layout->setContentsMargins(300,0,300,0);
}
void grid::paintEvent(QPaintEvent *){
   QPainter p(this);
   QPen k;
   k.setWidth(2);
   p.setPen(k);
   p.drawLine(540,10,539,730);
   p.drawLine(782,10,782,730);
   p.drawLine(300,245,1020,245);
   p.drawLine(300,488,1020,488);
}
cell* grid::getCell(int i,int j){
   return Cell[i][j];
}
