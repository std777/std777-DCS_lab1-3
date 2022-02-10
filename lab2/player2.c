/*
 Author:       Daichi Sato
 Student ID:   b1019159
 Class:        K
 Created:      December 19, 2021
 Language:     C
*/

#include <stdio.h>

int player2_count = 1;            //���E���h�J�E���g�p�ϐ�
int player2_nowround;             //���݂̃��E���h�ۑ��p�ϐ�
int player2_decidedstrategem;     //player2���o���ƌ��߂����ۑ�����ϐ�
int player2_cooperationcount = 0; //�������o���t���O

void Player2(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer2Strategy)
{
  player2_nowround = player2_count; //���E���h�����X�V
  player2_count += 1;               //���E���h���Ǘ��p�ϐ��̍X�V

  /*
  1���E���h�ڂ͗��؂�
  */
  if (player2_nowround == 1)
  {
    player2_decidedstrategem = 0; //���O���������߂����ۑ�
    *currentPlayer2Strategy = 0;
  }
  /*
  1���E���h�ڈӊO�̏���
  */
  else
  {
    /*
    �헪�̓��e
    ���O�Ŏ����ɃG���[���N���Ă����ʂƂ��āu���؂�v���o���Ă��܂��Ă��܂��Ă������͂��̌�͋������o���B
    ���̂ق���TFT
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
