/*
 Author:       Daichi Sato
 Student ID:   b1019159
 Class:        K
 Created:      February 6, 2022
 Language:     C
*/

#include <stdio.h>

/* 格子世界の大きさ */
#ifndef WORLD_SIZE
#define WORLD_SIZE 16
#endif

/*
獲物の位置をx座標とy座標に分けて構造体として使用
*/
typedef struct
{
  int x;
  int y;
} Prey_position;

typedef struct
{
  Prey_position pos;
} Preypositionstruct;

Preypositionstruct prey;

/*
獲物の視界を5*5の配列に落とし込む用の二次元配列を定義
*/
int preyview[5][5] = {0};

/*
獲物の視界を引数に受け取って次に移動する方向を返す関数
-> 捕食者の座標の重みを10としてそこから重さを伝播していく。等高線法に近い。最終的には自身の周囲4マスのうち一番重みが小さい方向を戻り値として返す。
*/
int Prey_decide_direction(int view[5][5])
{
  int max = 0;
  int num = 10;
  int view_calc[5][5];
  /*
  視界の二次元配列を一旦計算用の二次元配列にコピーする。
  */
  for (int k = 0; k < 5; k++)
  {
    for (int l = 0; l < 5; l++)
    {
      view_calc[k][l] = view[k][l];
    }
  }

  /*
  捕食者は全て10、また計算上の都合障害物と世界範囲外の座標を0としておく。
  */
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (view_calc[i][j] == 1)
      {
        view_calc[i][j] = 10;
      }
      if (view_calc[i][j] == 2)
      {
        view_calc[i][j] = 10;
      }
      if (view_calc[i][j] == 3)
      {
        view_calc[i][j] = 10;
      }
      if (view_calc[i][j] == 4)
      {
        view_calc[i][j] = 10;
      }
      if (view_calc[i][j] == -1)
      {
        view_calc[i][j] = 0;
      }
      if (view_calc[i][j] == -10)
      {
        view_calc[i][j] = 0;
      }
    }
  }

  /*
  重みの伝播処理。
  10（捕食者）から順に9.8.7.......と重みを付与していく。
  */
  for (int n = 0; n < 10; n++)
  {
    for (int k = 0; k < 5; k++)
    {
      for (int l = 0; l < 5; l++)
      {
        if (view_calc[k][l] == num)
        {
          if ((k - 1 >= 0) && view_calc[k - 1][l] < num)
          {
            view_calc[k - 1][l] = num - 1;
          }
          if ((l - 1 >= 0) && view_calc[k][l - 1] < num)
          {
            view_calc[k][l - 1] = num - 1;
          }
          if ((k + 1 <= 4) && view_calc[k + 1][l] < num)
          {
            view_calc[k + 1][l] = num - 1;
          }
          if ((l + 1 <= 4) && view_calc[k][l + 1] < num)
          {
            view_calc[k][l + 1] = num - 1;
          }
        }
      }
    }
    num -= 1;
  }

  /*
  元々引数で与えられた視界の二次元配列上でpreyの現在地から上下左右の4方向が移動できる座標ではなかったら重みを1000にする。
  この後に進む方向を決定する都合上、進めない座標は絶対進まないように重みを高くしておく
  */
  if (view[2][1] != 0)
  {
    view_calc[2][1] = 1000;
  }
  if (view[1][2] != 0)
  {
    view_calc[1][2] = 1000;
  }
  if (view[3][2] != 0)
  {
    view_calc[3][2] = 1000;
  }
  if (view[2][3] != 0)
  {
    view_calc[2][3] = 1000;
  }

  /*
  進む方向を考えて返す処理。
  一番重みの低い方向に進むようにする。
  */
  if ((view_calc[2][1] <= view_calc[1][2]) && (view_calc[2][1] <= view_calc[3][2]) && (view_calc[2][1] <= view_calc[2][3]))
  {
    return 'u';
  }
  else if ((view_calc[1][2] <= view_calc[2][1]) && (view_calc[1][2] <= view_calc[3][2]) && (view_calc[1][2] <= view_calc[2][3]))
  {
    return 'l';
  }
  else if ((view_calc[3][2] <= view_calc[1][2]) && (view_calc[3][2] <= view_calc[2][1]) && (view_calc[3][2] <= view_calc[2][3]))
  {
    return 'r';
  }
  else if ((view_calc[2][3] <= view_calc[1][2]) && (view_calc[2][3] <= view_calc[2][1]) && (view_calc[2][3] <= view_calc[3][2]))
  {
    return 'd';
  }
  else
  {
    return 's';
  }
}

void Prey(int fieldarray[WORLD_SIZE][WORLD_SIZE], int *preyaction)
{
  for (int i = 0; i <= WORLD_SIZE; i++)
  {
    for (int j = 0; j <= WORLD_SIZE; j++)
    {
      if (fieldarray[i][j] == 10)
      {
        prey.pos.x = i;
        prey.pos.y = j;
      }
    }
  }

  /*
  視界の二次元配列を作製
  →視界がちゃんと取れてるのを確認できた。
  世界座標の外は-10で埋められているはずなのに一部変な値を取るところがあり、場所によっては機能しない。
  ->レポートに詳細記載
  */
  preyview[2][2] = 10;
  preyview[0][0] = fieldarray[prey.pos.x - 2][prey.pos.y - 2];
  preyview[0][1] = fieldarray[prey.pos.x - 2][prey.pos.y - 1];
  preyview[0][2] = fieldarray[prey.pos.x - 2][prey.pos.y];
  preyview[0][3] = fieldarray[prey.pos.x - 2][prey.pos.y + 1];
  preyview[0][4] = fieldarray[prey.pos.x - 2][prey.pos.y + 2];
  preyview[1][0] = fieldarray[prey.pos.x - 1][prey.pos.y - 2];
  preyview[1][1] = fieldarray[prey.pos.x - 1][prey.pos.y - 1];
  preyview[1][2] = fieldarray[prey.pos.x - 1][prey.pos.y];
  preyview[1][3] = fieldarray[prey.pos.x - 1][prey.pos.y + 1];
  preyview[1][4] = fieldarray[prey.pos.x - 1][prey.pos.y + 2];
  preyview[2][0] = fieldarray[prey.pos.x][prey.pos.y - 2];
  preyview[2][1] = fieldarray[prey.pos.x][prey.pos.y - 1];
  preyview[2][3] = fieldarray[prey.pos.x][prey.pos.y + 1];
  preyview[2][4] = fieldarray[prey.pos.x][prey.pos.y + 2];
  preyview[3][0] = fieldarray[prey.pos.x + 1][prey.pos.y - 2];
  preyview[3][1] = fieldarray[prey.pos.x + 1][prey.pos.y - 1];
  preyview[3][2] = fieldarray[prey.pos.x + 1][prey.pos.y];
  preyview[3][3] = fieldarray[prey.pos.x + 1][prey.pos.y + 1];
  preyview[3][4] = fieldarray[prey.pos.x + 1][prey.pos.y + 2];
  preyview[4][0] = fieldarray[prey.pos.x + 2][prey.pos.y - 2];
  preyview[4][1] = fieldarray[prey.pos.x + 2][prey.pos.y - 1];
  preyview[4][2] = fieldarray[prey.pos.x + 2][prey.pos.y];
  preyview[4][3] = fieldarray[prey.pos.x + 2][prey.pos.y + 1];
  preyview[4][4] = fieldarray[prey.pos.x + 2][prey.pos.y + 2];

  *preyaction = Prey_decide_direction(preyview);
}
