/*
 Author:       Daichi Sato
 Student ID:   b1019159
 Class:        K
 Created:      February 6, 2022
 Language:     C
*/

#include <stdio.h>

/* �i�q���E�̑傫�� */
#ifndef WORLD_SIZE
#define WORLD_SIZE 16
#endif

/*
�l���̈ʒu��x���W��y���W�ɕ����č\���̂Ƃ��Ďg�p
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
�l���̎��E��5*5�̔z��ɗ��Ƃ����ޗp�̓񎟌��z����`
*/
int preyview[5][5] = {0};

/*
�l���̎��E�������Ɏ󂯎���Ď��Ɉړ����������Ԃ��֐�
-> �ߐH�҂̍��W�̏d�݂�10�Ƃ��Ă�������d����`�d���Ă����B�������@�ɋ߂��B�ŏI�I�ɂ͎��g�̎���4�}�X�̂�����ԏd�݂�������������߂�l�Ƃ��ĕԂ��B
*/
int Prey_decide_direction(int view[5][5])
{
  int max = 0;
  int num = 10;
  int view_calc[5][5];
  /*
  ���E�̓񎟌��z�����U�v�Z�p�̓񎟌��z��ɃR�s�[����B
  */
  for (int k = 0; k < 5; k++)
  {
    for (int l = 0; l < 5; l++)
    {
      view_calc[k][l] = view[k][l];
    }
  }

  /*
  �ߐH�҂͑S��10�A�܂��v�Z��̓s����Q���Ɛ��E�͈͊O�̍��W��0�Ƃ��Ă����B
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
  �d�݂̓`�d�����B
  10�i�ߐH�ҁj���珇��9.8.7.......�Əd�݂�t�^���Ă����B
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
  ���X�����ŗ^����ꂽ���E�̓񎟌��z����prey�̌��ݒn����㉺���E��4�������ړ��ł�����W�ł͂Ȃ�������d�݂�1000�ɂ���B
  ���̌�ɐi�ޕ��������肷��s����A�i�߂Ȃ����W�͐�ΐi�܂Ȃ��悤�ɏd�݂��������Ă���
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
  �i�ޕ������l���ĕԂ������B
  ��ԏd�݂̒Ⴂ�����ɐi�ނ悤�ɂ���B
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
  ���E�̓񎟌��z����쐻
  �����E�������Ǝ��Ă�̂��m�F�ł����B
  ���E���W�̊O��-10�Ŗ��߂��Ă���͂��Ȃ̂Ɉꕔ�ςȒl�����Ƃ��낪����A�ꏊ�ɂ���Ă͋@�\���Ȃ��B
  ->���|�[�g�ɏڍ׋L��
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
