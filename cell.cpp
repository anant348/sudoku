#include "cell.h"
#include <QRegExpValidator>
#include <QKeyEvent>
#include "buffer.h"
#include "grid.h"
cell::cell(QWidget *parent):QLineEdit(parent){
   row=-1;column=-1;
   setMinimumHeight(75);
   setMaximumHeight(75);
   setMaximumWidth(75);
   setMinimumWidth(75);
   setContentsMargins(0,0,0,0);
   setAlignment(Qt::AlignHCenter);
   QRegExp regExp("[1-9]{1,1}");
   setValidator(new QRegExpValidator(regExp,this));
   setReadOnly(true);
   font = new QFont;
   font->setStretch(100);
   font->setPointSize(40);
   setFont(*font);
}
void cell::keyPressEvent(QKeyEvent* e)
{

   setReadOnly(false);
   if(e->key()==Qt::Key_Backspace){
      clear();
      buf->a[row][column]=0;
   }
   
      else if(e->key()==Qt::Key_Right){
        if(column!=8)
          g->getCell(row,column+1)->setFocus();
      }
      
      else if(e->key()==Qt::Key_Left){
        if(column!=0)
          g->getCell(row,column-1)->setFocus();
      }

      else if(e->key()==Qt::Key_Up){
        if(row!=0)
          g->getCell(row-1,column)->setFocus();
      }

      else if(e->key()==Qt::Key_Down){
        if(row!=8)
          g->getCell(row+1,column)->setFocus();
      }
      else{
      int k = e->text().toInt();
      if(k>=1 && k<=9){
         setText(e->text());
         buf->a[row][column]=k;
      }
    }
   sudokuSolver s;
   for(int i=0;i<9;i++)
      for(int j=0;j<9;j++){
         s.ans[i][j]=buf->a[i][j];
      }
   for(int i=0;i<9;i++)
      for(int j=0;j<9;j++){
         if(g->getCell(i,j)->text().isEmpty())
            g->getCell(i,j)->setStyleSheet("background-color:white;");
         else if(s.checkRow(i,j)&&s.checkColumn(i,j)&&s.checkBlock(i,j))
            g->getCell(i,j)->setStyleSheet("background-color:gray;color:black");
         else
            g->getCell(i,j)->setStyleSheet("background-color:gray;color:red");  
      }
   setReadOnly(true);
}
cell::~cell(){
   delete font;
}
