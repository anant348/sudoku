#include "mainwindow.h"
#include "sudokusolver.h"
#include "grid.h"
#include <QMessageBox>
#include <QProgressDialog>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
mainWindow::mainWindow(QWidget *parent):QMainWindow(parent){
   createActions();
   createMenus();
   solver = NULL;
   setWindowIcon(QIcon(":/images/icon.png"));
   g =new grid(this);
   setCentralWidget(g);
   solveButton = new QPushButton("SOLVE",this);
   solveButton->setStyleSheet("font-weight:bold;font-size:20px;border-width:20px");
   clearButton = new QPushButton("CLEAR",this);
   clearButton->setStyleSheet("font-weight:bold;font-size:20px");
   solveButton->setGeometry(1100,70,120,40);

   clearButton->setGeometry(1100,120,120,40);
   showMaximized();
   connect(solveButton,SIGNAL(clicked()),this,SLOT(solve()));
   connect(clearButton,SIGNAL(clicked()),this,SLOT(clear()));
}
void mainWindow::clear(){
   for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
         g->getCell(i,j)->setReadOnly(false);
         g->getCell(i,j)->clear();
         g->buf.a[i][j]=0;
         g->getCell(i,j)->setStyleSheet("background-color:white;color:black;");
         g->getCell(i,j)->setReadOnly(true);
      }
   }
}

void mainWindow::solve(){
   solver = new sudokuSolver;
   for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
         QLineEdit *line=g->getCell(i,j);
         if(line->text().isEmpty())
            solver->ans[i][j]=solver->problem[i][j]=0;
         else
            solver->ans[i][j]=solver->problem[i][j]
               =line->text().toInt();

      }
   }
   int x=solver->solve();
   if(x==sudokuSolver::SOLVED){
      int numTasks = 150000;                     //
      QProgressDialog progress;
      progress.setWindowModality(Qt::WindowModal);
      progress.setLabelText("<h2>Solving the problem....");
      progress.setMinimum(0);
      progress.setMaximum(numTasks);
      progress.setMinimumDuration(1);
      for (int i = 0; i < numTasks; i++) {
         progress.setValue(i);
         if (progress.wasCanceled())
         {delete solver;return;}

      }
      progress.setValue(numTasks);      //
      for(int i=0;i<9;i++){
         for(int j=0;j<9;j++){
            QLineEdit *line=g->getCell(i,j);
            line->setReadOnly(false);
            g->buf.a[i][j]=solver->ans[i][j];
            if(line->text().isEmpty())
            {
               line->setText(QString::number(solver->ans[i][j]));
            }
            line->setReadOnly(true);
         }
      }
   }
   else if(x==sudokuSolver::NOTVALID){
      QMessageBox m;
      m.setTextFormat(Qt::RichText);
      m.setText("<h1>Sudoku Is Not Valid.<h1>");
      m.setIcon(QMessageBox::Critical);
      m.exec();
   }
   else{
      QMessageBox m;
      m.setTextFormat(Qt::RichText);
      m.setText("<h1>Sudoku Cannot Be Solved.<h1>");
      m.setIcon(QMessageBox::Critical);
      m.exec();
   }
   delete solver;
}
void mainWindow::createActions(){
   newAction = new QAction("New", this);
   newAction->setIcon(QIcon(":/images/new.png"));
   connect(newAction, SIGNAL(triggered()), this, SLOT(clear()));
   openAction = new QAction("Open", this);
   openAction->setIcon(QIcon(":/images/open.png"));
   connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
   about = new QAction("About", this);
   connect(about, SIGNAL(triggered()), this, SLOT(openAbout()));
}
void mainWindow::createMenus(){
   file = menuBar()->addMenu("File");
   file->addAction(newAction);
   file->addAction(openAction);
   help = menuBar()->addMenu("Help");
   help->addAction(about);
}
void mainWindow::open(){
   QString fileName = QFileDialog::getOpenFileName(this,"Open Sudoku Problem","./examples",
         "Puzzles files (*.txt)");
   if(!fileName.isEmpty()){
      try{
         parseFile(fileName);
         ifstream input(fileName.toLocal8Bit().constData());
         clear();
         for(int i=0;i<9;i++)
            for(int j=0;j<9;j++){
               input>>g->buf.a[i][j];
            }
         displayBuffer();

      }
      catch(...){
         QMessageBox m;
         m.setTextFormat(Qt::RichText);
         m.setText("<h1>File Is Not In The Correct Format.<h1>");
         m.setIcon(QMessageBox::Critical);
         m.exec();
      }
   }
}
bool mainWindow::parseFile(QString& source){
   ifstream input(source.toLocal8Bit().constData());
   int a,count=0;
   while(!input.eof()){
      input >> a;
      count++;
      if(a<0 || a>9 || count>82)
      {
         throw "error";
      }

   }
   return true;
}
void mainWindow::displayBuffer(){

   for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
         QLineEdit *line=g->getCell(i,j);
         line->setReadOnly(false);

         if(g->buf.a[i][j]!=0)
         {
            line->setText(QString::number(g->buf.a[i][j]));
         }
         line->setReadOnly(true);
      }
   }
   sudokuSolver s;
   for(int i=0;i<9;i++)
      for(int j=0;j<9;j++){
         s.ans[i][j]=g->buf.a[i][j];
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
}

void mainWindow::openAbout(){
   QMessageBox m;
   m.setTextFormat(Qt::RichText);
   m.setText("<h2>Sudoku Solver<br></h2><h4>Made By:</h4><br>Naman Jain<br>Simar Batra<br>Jagendra Singh<br>Anant Agrawal");
   m.setIcon(QMessageBox::NoIcon);
   m.exec();
}
