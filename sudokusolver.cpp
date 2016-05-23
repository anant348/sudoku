#include "sudokusolver.h"

bool sudokuSolver::checkRow(int row,int column){
   for(int i=0;i<9;i++){
    if(i==column) continue;
    if(ans[row][i]==ans[row][column]) return false;
   }
   return true;
}
bool sudokuSolver::checkColumn(int row,int column){
   for(int i=0;i<9;i++){
    if(i==row) continue;
    if(ans[i][column]==ans[row][column]) return false;
   }
   return true;
}
bool sudokuSolver::checkBlock(int row,int column){
    int i,imax,j,jmax,temp;
    temp=row/3;
    switch(temp){
      case 0:i=0;imax=2;break;
      case 1:i=3;imax=5;break;
      case 2:i=6;imax=8;break;
    }
    temp=column/3;
    switch(temp){
      case 0:j=0;jmax=2;break;
      case 1:j=3;jmax=5;break;
      case 2:j=6;jmax=8;break;
    }
    for(int i1=i;i1<=imax;i1++)
      for(int j1=j;j1<=jmax;j1++){
        if(i1==row && j1==column) continue;
        if(ans[i1][j1]==ans[row][column]) return false;
      }
    return true;
}

bool sudokuSolver::fillColumn(int row,int column){
  if(row==9){
    return true;
  }
  else if(column==9){
    if(fillColumn(row+1,0))return true;
    else return false; 
  }

  else if(problem[row][column]==0){
    for(int i=1;i<=9;i++){
      ans[row][column]=i;
      for(int k=row;k<9;k++){
        if(k==row){
            for(int l=column+1;l<9;l++)
            ans[k][l]=problem[k][l];
        }
        else{
          for(int l=0;l<9;l++)
            ans[k][l]=problem[k][l];
        }
      }
     if(checkColumn(row,column) && checkRow(row,column) && checkBlock(row,column)) 
      if(fillColumn(row,column+1))return true;
    }
    return false;
  }
    else {if(fillColumn(row,column+1))return true;else return false;}
  }

bool sudokuSolver::validateProblem(){
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      if(problem[i][j]==0)continue;
      else{
        if(!(checkBlock(i,j)&&checkRow(i,j)&&checkColumn(i,j)))return false;
      }
    }
  }
  return true;
}
sudokuSolver::status sudokuSolver::solve(){
  if(validateProblem()){
    if(fillColumn(0,0))return SOLVED;
    else return UNSOLVED;
  }
  else{
    return NOTVALID;
  }
}
