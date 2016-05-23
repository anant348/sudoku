#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "grid.h"
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
class sudokuSolver;
class mainWindow:public QMainWindow{
   Q_OBJECT
      QPushButton *solveButton;
   QPushButton *clearButton;
   sudokuSolver *solver;
   QMenu *file;
   QMenu *help;
   QAction *openAction;
   QAction *about;
   QAction *newAction;
   public:
   mainWindow(QWidget *parent=0);
   grid *g;
   void displayBuffer();
   private slots:
      void solve();
   void clear();
   void open();
   void openAbout();
   private:
   void createActions();
   void createMenus();
   bool parseFile(QString&);
};

#endif // MAINWINDOW_H

