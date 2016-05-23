#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H
class sudokuSolver{
   public:
      int problem[9][9],ans[9][9];
      enum status{
         NOTVALID,
         SOLVED,
         UNSOLVED,
      };
      bool fillColumn(int,int);
      bool checkRow(int,int);
      bool checkBlock(int,int);
      bool checkColumn(int,int);
      bool validateProblem();
      status solve();
};
#endif
