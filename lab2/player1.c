/*
 Author:       Daichi Sato
 Student ID:   b1019159
 Class:        K
 Created:      December 19, 2021
 Language:     C
*/

#include <stdio.h>

int player1_count = 1;                  //���E���h�J�E���g�p�ϐ�
int player1_nowround;                   //���݂̃��E���h�ۑ��p�ϐ�
int player1_myscore = 0;                //���g�̃X�R�A�ۑ��p
int player1_enemyscore = 0;             //����̃X�R�A�ۑ��p
int player1_enemycoopertecount = 0;     //����̋����񐔃J�E���g�p
int player1_prepreviousPlayer2Strategy; //����̓�O�̎��ۑ�����

void Player1(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer1Strategy)
{
  /*
  �X�R�A�v�Z�p
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

  player1_nowround = player1_count; //���E���h�����X�V
  player1_count += 1;               //���̃��E���h�ɔ����ă��E���h�J�E���g�p�ϐ��̍X�V

  if (player1_nowround == 1) // ���ڂ̐헪
  {
    *currentPlayer1Strategy = 0; //�ŏ��̈��ڂ͐�΂ɗ��؂�
  }
  else //2��ڈȍ~�̐헪
  {
    /*
    �X�R�A���Ǘ����Đ헪���l���Ă���B
    �����Ă���Ƃ��͓O��I�ɗ��؂��Ĉ�������
    �����Ă���Ƃ��͋�������ӂ�����ė��؂�
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
