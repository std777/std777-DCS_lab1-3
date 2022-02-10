/*
 Author:       Daichi Sato
 Student ID:   b1019159
 Class:        K
 Created:      December 19, 2021
 Language:     C
*/

#include <stdio.h>

int player2_count = 1;            //ラウンドカウント用変数
int player2_nowround;             //現在のラウンド保存用変数
int player2_decidedstrategem;     //player2が出すと決めた手を保存する変数
int player2_cooperationcount = 0; //協調を出すフラグ

void Player2(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer2Strategy)
{
  player2_nowround = player2_count; //ラウンド数を更新
  player2_count += 1;               //ラウンド数管理用変数の更新

  /*
  1ラウンド目は裏切る
  */
  if (player2_nowround == 1)
  {
    player2_decidedstrategem = 0; //直前自分が決めた手を保存
    *currentPlayer2Strategy = 0;
  }
  /*
  1ラウンド目意外の処理
  */
  else
  {
    /*
    戦略の内容
    直前で自分にエラーが起きてかつ結果として「裏切り」を出してしまってしまっていた時はその後は協調を出す。
    そのほかはTFT
    */
    if (player2_cooperationcount != 0)
    {
      player2_decidedstrategem = 1;
      player2_cooperationcount -= 1;
      *currentPlayer2Strategy = 1;
    }
    if ((player2_decidedstrategem != previousPlayer2Strategy) && (previousPlayer2Strategy == 0))
    {
      player2_cooperationcount = 1;
      player2_decidedstrategem = 1;
      *currentPlayer2Strategy = 1;
    }
    else
    {
      player2_decidedstrategem = previousPlayer1Strategy;
      *currentPlayer2Strategy = previousPlayer1Strategy;
    }
  }
}
