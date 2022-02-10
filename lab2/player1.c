/*
 Author:       Daichi Sato
 Student ID:   b1019159
 Class:        K
 Created:      December 19, 2021
 Language:     C
*/

#include <stdio.h>

int player1_count = 1;                  //ラウンドカウント用変数
int player1_nowround;                   //現在のラウンド保存用変数
int player1_myscore = 0;                //自身のスコア保存用
int player1_enemyscore = 0;             //相手のスコア保存用
int player1_enemycoopertecount = 0;     //相手の協調回数カウント用
int player1_prepreviousPlayer2Strategy; //相手の二つ前の手を保存する

void Player1(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer1Strategy)
{
  /*
  スコア計算用
  */
  if (previousPlayer1Strategy == previousPlayer2Strategy == 1)
  {
    player1_myscore += 3;
    player1_enemyscore += 3;
  }
  else if (previousPlayer1Strategy == previousPlayer2Strategy == 0)
  {
    player1_myscore += 1;
    player1_enemyscore += 1;
  }
  else if (previousPlayer1Strategy == 1 && previousPlayer2Strategy == 0)
  {
    player1_enemyscore += 5;
  }
  else if (previousPlayer1Strategy == 0 && previousPlayer2Strategy == 1)
  {
    player1_myscore += 5;
  }
  else
  {
  }

  player1_nowround = player1_count; //ラウンド数を更新
  player1_count += 1;               //次のラウンドに備えてラウンドカウント用変数の更新

  if (player1_nowround == 1) // 一回目の戦略
  {
    *currentPlayer1Strategy = 0; //最初の一回目は絶対に裏切る
  }
  else //2回目以降の戦略
  {
    /*
    スコアを管理して戦略を考えている。
    勝っているときは徹底的に裏切って引き離す
    負けているときは協調するふりをして裏切る
    */
    if (player1_myscore > player1_enemyscore)
    {
      player1_prepreviousPlayer2Strategy = previousPlayer2Strategy;
      *currentPlayer1Strategy = 0;
    }
    else
    {
      if (player1_prepreviousPlayer2Strategy == previousPlayer2Strategy == 1)
      {
        player1_prepreviousPlayer2Strategy = 3;
        *currentPlayer1Strategy = 0;
      }
      player1_prepreviousPlayer2Strategy = previousPlayer2Strategy;
      *currentPlayer1Strategy = 1;
    }
  }
}
