/*
 Author:       Daichi Sato
 Student ID:   b1019159
 Class:        K
 Created:      February 2, 2022
 Language:     C
*/

#include <stdio.h>

/* �i�q���E�̑傫�� */
#ifndef WORLD_SIZE
#define WORLD_SIZE 16
#endif

/*���Ղ̎��*/
#ifndef UP
#define UP 11
#endif

#ifndef RIGHT
#define RIGHT 12
#endif

#ifndef LEFT
#define LEFT 13
#endif

#ifndef DOWN
#define DOWN 14
#endif

#ifndef STAY
#define STAY 15
#endif

/*
�ߐH�҂̈ʒu��x���W��y���W�ɕ����č\���̂Ƃ��Ďg�p
*/
typedef struct
{
  int x;
  int y;
} Predator_position;

typedef struct
{
  Predator_position pos;
} eachpredator;

eachpredator predator1;
eachpredator predator2;
eachpredator predator3;
eachpredator predator4;

/*
�ߐH�҂��ꂼ��̑��Ղ��i�[���Ă����z��B
11����A12���E�A13�����A14���������A15��stay�̑��Ղɂ��Ă������B
*/
int predator1footprint[WORLD_SIZE][WORLD_SIZE] = {0};
int predator2footprint[WORLD_SIZE][WORLD_SIZE] = {0};
int predator3footprint[WORLD_SIZE][WORLD_SIZE] = {0};
int predator4footprint[WORLD_SIZE][WORLD_SIZE] = {0};

/*
�ߐH�҂��ꂼ��̎��E��5*5�̔z��ɗ��Ƃ����ޗp�̓񎟌��z����`
*/
int predator1view[5][5] = {0};
int predator2view[5][5] = {0};
int predator3view[5][5] = {0};
int predator4view[5][5] = {0};

int enemyfindflag = 0; // �ߐH�҂��l�������������ǂ����̃t���O�B�ǂꂩ�̕ߐH�҂��l������������1�ɂ���B
int finder = 0;        //�l�������߂Č������ߐH�҂̔ԍ����o���Ă����ׂ̕ϐ��B�l���𔭌���A��3�̕ߐH�҂͂����̕ϐ��ƈ�v���鑫�Ղ����ǂ邱�ƂŊl���ɋ߂Â����Ƃ����Z�i�B

int situation1 = 0; // Predator1�̍��̏�ԁBprey���A�F��������0�A������������1�A���̕ߐH�҂�������2
int situation2 = 0; // Predator2�̍��̏�ԁB
int situation3 = 0; // Predator3�̍��̏�ԁB
int situation4 = 0; // Predator4�̍��̏�ԁB

/*
�ߐH�҂̎��E�������Ɏ󂯎���Ď��Ɉړ����������Ԃ��֐�
���������i�G���[�ɂȂ�Ȃ��悤�Ɏ�芸�����E�ɐݒ�j
*/
int Predator_decide_direction(int view[5][5])
{
  return 's';
}

void Predator1(int fieldarray1[WORLD_SIZE][WORLD_SIZE], int *action1)
{

  /*
  ���������ȊO�̒N������ߐH�҂𔭌����Ă����ꍇ�̏���
  */
  if (enemyfindflag != 0)
  {
    situation1 = 2;
  }

  switch (situation1)
  {
  case 1: //�����������ς݂̏�
    for (int i = 0; i <= WORLD_SIZE; i++)
    {
      for (int j = 0; j <= WORLD_SIZE; j++)
      {
        if (fieldarray1[i][j] == 1)
        {
          predator1.pos.x = i;
          predator1.pos.y = j;
        }
      }
    }
    /*
    ���E�̓񎟌��z����쐻
    �����E�������Ǝ��Ă�̂��m�F�ł����B
    */
    predator1view[2][2] = 1;
    predator1view[0][0] = fieldarray1[predator1.pos.x - 2][predator1.pos.y - 2];
    predator1view[0][1] = fieldarray1[predator1.pos.x - 2][predator1.pos.y - 1];
    predator1view[0][2] = fieldarray1[predator1.pos.x - 2][predator1.pos.y];
    predator1view[0][3] = fieldarray1[predator1.pos.x - 2][predator1.pos.y + 1];
    predator1view[0][4] = fieldarray1[predator1.pos.x - 2][predator1.pos.y + 2];
    predator1view[1][0] = fieldarray1[predator1.pos.x - 1][predator1.pos.y - 2];
    predator1view[1][1] = fieldarray1[predator1.pos.x - 1][predator1.pos.y - 1];
    predator1view[1][2] = fieldarray1[predator1.pos.x - 1][predator1.pos.y];
    predator1view[1][3] = fieldarray1[predator1.pos.x - 1][predator1.pos.y + 1];
    predator1view[1][4] = fieldarray1[predator1.pos.x - 1][predator1.pos.y + 2];
    predator1view[2][0] = fieldarray1[predator1.pos.x][predator1.pos.y - 2];
    predator1view[2][1] = fieldarray1[predator1.pos.x][predator1.pos.y - 1];
    predator1view[2][3] = fieldarray1[predator1.pos.x][predator1.pos.y + 1];
    predator1view[2][4] = fieldarray1[predator1.pos.x][predator1.pos.y + 2];
    predator1view[3][0] = fieldarray1[predator1.pos.x + 1][predator1.pos.y - 2];
    predator1view[3][1] = fieldarray1[predator1.pos.x + 1][predator1.pos.y - 1];
    predator1view[3][2] = fieldarray1[predator1.pos.x + 1][predator1.pos.y];
    predator1view[3][3] = fieldarray1[predator1.pos.x + 1][predator1.pos.y + 1];
    predator1view[3][4] = fieldarray1[predator1.pos.x + 1][predator1.pos.y + 2];
    predator1view[4][0] = fieldarray1[predator1.pos.x + 2][predator1.pos.y - 2];
    predator1view[4][1] = fieldarray1[predator1.pos.x + 2][predator1.pos.y - 1];
    predator1view[4][2] = fieldarray1[predator1.pos.x + 2][predator1.pos.y];
    predator1view[4][3] = fieldarray1[predator1.pos.x + 2][predator1.pos.y + 1];
    predator1view[4][4] = fieldarray1[predator1.pos.x + 2][predator1.pos.y + 2];

    /*
    ���E���֐��ɓn���Ď��ɐi�ޕ��������肷��B
    */
    *action1 = Predator_decide_direction(predator1view);

    /*
�@�@���Ղ��c������
�@�@*/
    if (*action1 == 'u')
    {
      predator1footprint[predator1.pos.x][predator1.pos.y] = UP;
    }
    else if (*action1 == 'r')
    {
      predator1footprint[predator1.pos.x][predator1.pos.y] = RIGHT;
    }
    else if (*action1 == 'l')
    {
      predator1footprint[predator1.pos.x][predator1.pos.y] = LEFT;
    }
    else if (*action1 == 'd')
    {
      predator1footprint[predator1.pos.x][predator1.pos.y] = DOWN;
    }
    else
    {
      predator1footprint[predator1.pos.x][predator1.pos.y] = STAY;
    }

    break;

  case 2: //�N�����������Ă��
    for (int i = 0; i <= WORLD_SIZE; i++)
    {
      for (int j = 0; j <= WORLD_SIZE; j++)
      {
        if (fieldarray1[i][j] == 1)
        {
          predator1.pos.x = i;
          predator1.pos.y = j;
        }
      }
    }

    /*
    ���E�̓񎟌��z����쐻
    �����E�������Ǝ��Ă�̂��m�F�ł����B
    */
    predator1view[2][2] = 1;
    predator1view[0][0] = fieldarray1[predator1.pos.x - 2][predator1.pos.y - 2];
    predator1view[0][1] = fieldarray1[predator1.pos.x - 2][predator1.pos.y - 1];
    predator1view[0][2] = fieldarray1[predator1.pos.x - 2][predator1.pos.y];
    predator1view[0][3] = fieldarray1[predator1.pos.x - 2][predator1.pos.y + 1];
    predator1view[0][4] = fieldarray1[predator1.pos.x - 2][predator1.pos.y + 2];
    predator1view[1][0] = fieldarray1[predator1.pos.x - 1][predator1.pos.y - 2];
    predator1view[1][1] = fieldarray1[predator1.pos.x - 1][predator1.pos.y - 1];
    predator1view[1][2] = fieldarray1[predator1.pos.x - 1][predator1.pos.y];
    predator1view[1][3] = fieldarray1[predator1.pos.x - 1][predator1.pos.y + 1];
    predator1view[1][4] = fieldarray1[predator1.pos.x - 1][predator1.pos.y + 2];
    predator1view[2][0] = fieldarray1[predator1.pos.x][predator1.pos.y - 2];
    predator1view[2][1] = fieldarray1[predator1.pos.x][predator1.pos.y - 1];
    predator1view[2][3] = fieldarray1[predator1.pos.x][predator1.pos.y + 1];
    predator1view[2][4] = fieldarray1[predator1.pos.x][predator1.pos.y + 2];
    predator1view[3][0] = fieldarray1[predator1.pos.x + 1][predator1.pos.y - 2];
    predator1view[3][1] = fieldarray1[predator1.pos.x + 1][predator1.pos.y - 1];
    predator1view[3][2] = fieldarray1[predator1.pos.x + 1][predator1.pos.y];
    predator1view[3][3] = fieldarray1[predator1.pos.x + 1][predator1.pos.y + 1];
    predator1view[3][4] = fieldarray1[predator1.pos.x + 1][predator1.pos.y + 2];
    predator1view[4][0] = fieldarray1[predator1.pos.x + 2][predator1.pos.y - 2];
    predator1view[4][1] = fieldarray1[predator1.pos.x + 2][predator1.pos.y - 1];
    predator1view[4][2] = fieldarray1[predator1.pos.x + 2][predator1.pos.y];
    predator1view[4][3] = fieldarray1[predator1.pos.x + 2][predator1.pos.y + 1];
    predator1view[4][4] = fieldarray1[predator1.pos.x + 2][predator1.pos.y + 2];

    /*
    �ŏ��Ɋl�����������ߐH�҂�2�̎��A3�̎��A4�̎��B
    */
    if (finder == 2)
    {
      if (predator2footprint[predator1.pos.x][predator1.pos.y] == 0)
      {
        *action1 = Predator_decide_direction(predator1view);
      }
      else
      {
        if (predator2footprint[predator1.pos.x][predator1.pos.y] == UP)
        {
          *action1 = 'u';
        }
        else if (predator2footprint[predator1.pos.x][predator1.pos.y] == RIGHT)
        {
          *action1 = 'r';
        }
        else if (predator2footprint[predator1.pos.x][predator1.pos.y] == LEFT)
        {
          *action1 = 'l';
        }
        else if (predator2footprint[predator1.pos.x][predator1.pos.y] == DOWN)
        {
          *action1 = 'd';
        }
        else
        {
          *action1 = 's';
        }
      }
    }
    else if (finder == 3)
    {
      if (predator3footprint[predator1.pos.x][predator1.pos.y] == 0)
      {
        *action1 = Predator_decide_direction(predator1view);
      }
      else
      {
        if (predator3footprint[predator1.pos.x][predator1.pos.y] == UP)
        {
          *action1 = 'u';
        }
        else if (predator3footprint[predator1.pos.x][predator1.pos.y] == RIGHT)
        {
          *action1 = 'r';
        }
        else if (predator3footprint[predator1.pos.x][predator1.pos.y] == LEFT)
        {
          *action1 = 'l';
        }
        else if (predator3footprint[predator1.pos.x][predator1.pos.y] == DOWN)
        {
          *action1 = 'd';
        }
        else
        {
          *action1 = 's';
        }
      }
    }
    else if (finder == 4)
    {
      if (predator4footprint[predator1.pos.x][predator1.pos.y] == 0)
      {
        *action1 = Predator_decide_direction(predator1view);
      }
      else
      {
        if (predator4footprint[predator1.pos.x][predator1.pos.y] == UP)
        {
          *action1 = 'u';
        }
        else if (predator4footprint[predator1.pos.x][predator1.pos.y] == RIGHT)
        {
          *action1 = 'r';
        }
        else if (predator4footprint[predator1.pos.x][predator1.pos.y] == LEFT)
        {
          *action1 = 'l';
        }
        else if (predator4footprint[predator1.pos.x][predator1.pos.y] == DOWN)
        {
          *action1 = 'd';
        }
        else
        {
          *action1 = 's';
        }
      }
    }

    break;

  default: //(0)�F�������̏�
    for (int i = 0; i <= WORLD_SIZE; i++)
    {
      for (int j = 0; j <= WORLD_SIZE; j++)
      {
        if (fieldarray1[i][j] == 1)
        {
          predator1.pos.x = i;
          predator1.pos.y = j;
        }
      }
    }
    /*
    ���E�̓񎟌��z����쐻
    �����E�������Ǝ��Ă�̂��m�F�ł����B
    */
    predator1view[2][2] = 1;
    predator1view[0][0] = fieldarray1[predator1.pos.x - 2][predator1.pos.y - 2];
    predator1view[0][1] = fieldarray1[predator1.pos.x - 2][predator1.pos.y - 1];
    predator1view[0][2] = fieldarray1[predator1.pos.x - 2][predator1.pos.y];
    predator1view[0][3] = fieldarray1[predator1.pos.x - 2][predator1.pos.y + 1];
    predator1view[0][4] = fieldarray1[predator1.pos.x - 2][predator1.pos.y + 2];
    predator1view[1][0] = fieldarray1[predator1.pos.x - 1][predator1.pos.y - 2];
    predator1view[1][1] = fieldarray1[predator1.pos.x - 1][predator1.pos.y - 1];
    predator1view[1][2] = fieldarray1[predator1.pos.x - 1][predator1.pos.y];
    predator1view[1][3] = fieldarray1[predator1.pos.x - 1][predator1.pos.y + 1];
    predator1view[1][4] = fieldarray1[predator1.pos.x - 1][predator1.pos.y + 2];
    predator1view[2][0] = fieldarray1[predator1.pos.x][predator1.pos.y - 2];
    predator1view[2][1] = fieldarray1[predator1.pos.x][predator1.pos.y - 1];
    predator1view[2][3] = fieldarray1[predator1.pos.x][predator1.pos.y + 1];
    predator1view[2][4] = fieldarray1[predator1.pos.x][predator1.pos.y + 2];
    predator1view[3][0] = fieldarray1[predator1.pos.x + 1][predator1.pos.y - 2];
    predator1view[3][1] = fieldarray1[predator1.pos.x + 1][predator1.pos.y - 1];
    predator1view[3][2] = fieldarray1[predator1.pos.x + 1][predator1.pos.y];
    predator1view[3][3] = fieldarray1[predator1.pos.x + 1][predator1.pos.y + 1];
    predator1view[3][4] = fieldarray1[predator1.pos.x + 1][predator1.pos.y + 2];
    predator1view[4][0] = fieldarray1[predator1.pos.x + 2][predator1.pos.y - 2];
    predator1view[4][1] = fieldarray1[predator1.pos.x + 2][predator1.pos.y - 1];
    predator1view[4][2] = fieldarray1[predator1.pos.x + 2][predator1.pos.y];
    predator1view[4][3] = fieldarray1[predator1.pos.x + 2][predator1.pos.y + 1];
    predator1view[4][4] = fieldarray1[predator1.pos.x + 2][predator1.pos.y + 2];

    /*
    for (int i = 0; i < 5; i++)
    {
      printf("%d %d %d %d %d\n", predator1view[i][0], predator1view[i][1], predator1view[i][2], predator1view[i][3], predator1view[i][4]);
    }
    */

    /*
    ���E�̒��Ɋl����������t���O�𔭌���Ԃɂ��Ď��̍s������ǂ��l�߂邽�߂�case�Ɉڍs���邽�߂̏���
    */
    for (int i = 0; i < 5; i++)
    {
      for (int k = 0; k < 5; k++)
      {
        if (predator1view[i][k] == 10)
        {
          enemyfindflag = 1;
          finder = 1; // 1����������
          situation1 = 1;
        }
      }
    }

    /*
    ���E���֐��ɓn���Ď��ɐi�ޕ��������肷��B
    */
    *action1 = Predator_decide_direction(predator1view);

    /*
�@�@���Ղ��c������
�@�@*/
    if (*action1 == 'u')
    {
      predator1footprint[predator1.pos.x][predator1.pos.y] = UP;
    }
    else if (*action1 == 'r')
    {
      predator1footprint[predator1.pos.x][predator1.pos.y] = RIGHT;
    }
    else if (*action1 == 'l')
    {
      predator1footprint[predator1.pos.x][predator1.pos.y] = LEFT;
    }
    else if (*action1 == 'd')
    {
      predator1footprint[predator1.pos.x][predator1.pos.y] = DOWN;
    }
    else
    {
      predator1footprint[predator1.pos.x][predator1.pos.y] = STAY;
    }

    break;
  }
}

void Predator2(int fieldarray2[WORLD_SIZE][WORLD_SIZE], int *action2)
{
  /*
  ���������ȊO�̒N������ߐH�҂𔭌����Ă����ꍇ�̏���
  */
  if (enemyfindflag != 0)
  {
    situation2 = 2;
  }

  switch (situation2)
  {
  case 1: //�����������ς݂̏�
    for (int i = 0; i <= WORLD_SIZE; i++)
    {
      for (int j = 0; j <= WORLD_SIZE; j++)
      {
        if (fieldarray2[i][j] == 1)
        {
          predator2.pos.x = i;
          predator2.pos.y = j;
        }
      }
    }
    /*
    ���E�̓񎟌��z����쐻
    �����E�������Ǝ��Ă�̂��m�F�ł����B
    */
    predator2view[2][2] = 2;
    predator2view[0][0] = fieldarray2[predator2.pos.x - 2][predator2.pos.y - 2];
    predator2view[0][1] = fieldarray2[predator2.pos.x - 2][predator2.pos.y - 1];
    predator2view[0][2] = fieldarray2[predator2.pos.x - 2][predator2.pos.y];
    predator2view[0][3] = fieldarray2[predator2.pos.x - 2][predator2.pos.y + 1];
    predator2view[0][4] = fieldarray2[predator2.pos.x - 2][predator2.pos.y + 2];
    predator2view[1][0] = fieldarray2[predator2.pos.x - 1][predator2.pos.y - 2];
    predator2view[1][1] = fieldarray2[predator2.pos.x - 1][predator2.pos.y - 1];
    predator2view[1][2] = fieldarray2[predator2.pos.x - 1][predator2.pos.y];
    predator2view[1][3] = fieldarray2[predator2.pos.x - 1][predator2.pos.y + 1];
    predator2view[1][4] = fieldarray2[predator2.pos.x - 1][predator2.pos.y + 2];
    predator2view[2][0] = fieldarray2[predator2.pos.x][predator2.pos.y - 2];
    predator2view[2][1] = fieldarray2[predator2.pos.x][predator2.pos.y - 1];
    predator2view[2][3] = fieldarray2[predator2.pos.x][predator2.pos.y + 1];
    predator2view[2][4] = fieldarray2[predator2.pos.x][predator2.pos.y + 2];
    predator2view[3][0] = fieldarray2[predator2.pos.x + 1][predator2.pos.y - 2];
    predator2view[3][1] = fieldarray2[predator2.pos.x + 1][predator2.pos.y - 1];
    predator2view[3][2] = fieldarray2[predator2.pos.x + 1][predator2.pos.y];
    predator2view[3][3] = fieldarray2[predator2.pos.x + 1][predator2.pos.y + 1];
    predator2view[3][4] = fieldarray2[predator2.pos.x + 1][predator2.pos.y + 2];
    predator2view[4][0] = fieldarray2[predator2.pos.x + 2][predator2.pos.y - 2];
    predator2view[4][1] = fieldarray2[predator2.pos.x + 2][predator2.pos.y - 1];
    predator2view[4][2] = fieldarray2[predator2.pos.x + 2][predator2.pos.y];
    predator2view[4][3] = fieldarray2[predator2.pos.x + 2][predator2.pos.y + 1];
    predator2view[4][4] = fieldarray2[predator2.pos.x + 2][predator2.pos.y + 2];

    /*
    ���E���֐��ɓn���Ď��ɐi�ޕ��������肷��B
    */
    *action2 = Predator_decide_direction(predator2view);

    /*
�@�@���Ղ��c������
�@�@*/
    if (*action2 == 'u')
    {
      predator2footprint[predator2.pos.x][predator2.pos.y] = UP;
    }
    else if (*action2 == 'r')
    {
      predator2footprint[predator2.pos.x][predator2.pos.y] = RIGHT;
    }
    else if (*action2 == 'l')
    {
      predator2footprint[predator2.pos.x][predator2.pos.y] = LEFT;
    }
    else if (*action2 == 'd')
    {
      predator2footprint[predator2.pos.x][predator2.pos.y] = DOWN;
    }
    else
    {
      predator2footprint[predator2.pos.x][predator2.pos.y] = STAY;
    }

    break;

  case 2: //�N�����������Ă��
    for (int i = 0; i <= WORLD_SIZE; i++)
    {
      for (int j = 0; j <= WORLD_SIZE; j++)
      {
        if (fieldarray2[i][j] == 1)
        {
          predator2.pos.x = i;
          predator2.pos.y = j;
        }
      }
    }

    /*
    ���E�̓񎟌��z����쐻
    �����E�������Ǝ��Ă�̂��m�F�ł����B
    */
    predator2view[2][2] = 2;
    predator2view[0][0] = fieldarray2[predator2.pos.x - 2][predator2.pos.y - 2];
    predator2view[0][1] = fieldarray2[predator2.pos.x - 2][predator2.pos.y - 1];
    predator2view[0][2] = fieldarray2[predator2.pos.x - 2][predator2.pos.y];
    predator2view[0][3] = fieldarray2[predator2.pos.x - 2][predator2.pos.y + 1];
    predator2view[0][4] = fieldarray2[predator2.pos.x - 2][predator2.pos.y + 2];
    predator2view[1][0] = fieldarray2[predator2.pos.x - 1][predator2.pos.y - 2];
    predator2view[1][1] = fieldarray2[predator2.pos.x - 1][predator2.pos.y - 1];
    predator2view[1][2] = fieldarray2[predator2.pos.x - 1][predator2.pos.y];
    predator2view[1][3] = fieldarray2[predator2.pos.x - 1][predator2.pos.y + 1];
    predator2view[1][4] = fieldarray2[predator2.pos.x - 1][predator2.pos.y + 2];
    predator2view[2][0] = fieldarray2[predator2.pos.x][predator2.pos.y - 2];
    predator2view[2][1] = fieldarray2[predator2.pos.x][predator2.pos.y - 1];
    predator2view[2][3] = fieldarray2[predator2.pos.x][predator2.pos.y + 1];
    predator2view[2][4] = fieldarray2[predator2.pos.x][predator2.pos.y + 2];
    predator2view[3][0] = fieldarray2[predator2.pos.x + 1][predator2.pos.y - 2];
    predator2view[3][1] = fieldarray2[predator2.pos.x + 1][predator2.pos.y - 1];
    predator2view[3][2] = fieldarray2[predator2.pos.x + 1][predator2.pos.y];
    predator2view[3][3] = fieldarray2[predator2.pos.x + 1][predator2.pos.y + 1];
    predator2view[3][4] = fieldarray2[predator2.pos.x + 1][predator2.pos.y + 2];
    predator2view[4][0] = fieldarray2[predator2.pos.x + 2][predator2.pos.y - 2];
    predator2view[4][1] = fieldarray2[predator2.pos.x + 2][predator2.pos.y - 1];
    predator2view[4][2] = fieldarray2[predator2.pos.x + 2][predator2.pos.y];
    predator2view[4][3] = fieldarray2[predator2.pos.x + 2][predator2.pos.y + 1];
    predator2view[4][4] = fieldarray2[predator2.pos.x + 2][predator2.pos.y + 2];

    /*
    �ŏ��Ɋl�����������ߐH�҂�1�̎��A3�̎��A4�̎��B
    */
    if (finder == 1)
    {
      if (predator1footprint[predator2.pos.x][predator2.pos.y] == 0)
      {
        *action2 = Predator_decide_direction(predator2view);
      }
      else
      {
        if (predator1footprint[predator2.pos.x][predator2.pos.y] == UP)
        {
          *action2 = 'u';
        }
        else if (predator1footprint[predator2.pos.x][predator2.pos.y] == RIGHT)
        {
          *action2 = 'r';
        }
        else if (predator1footprint[predator2.pos.x][predator2.pos.y] == LEFT)
        {
          *action2 = 'l';
        }
        else if (predator1footprint[predator2.pos.x][predator2.pos.y] == DOWN)
        {
          *action2 = 'd';
        }
        else
        {
          *action2 = 's';
        }
      }
    }
    else if (finder == 3)
    {
      if (predator3footprint[predator2.pos.x][predator2.pos.y] == 0)
      {
        *action2 = Predator_decide_direction(predator2view);
      }
      else
      {
        if (predator3footprint[predator2.pos.x][predator2.pos.y] == UP)
        {
          *action2 = 'u';
        }
        else if (predator3footprint[predator2.pos.x][predator2.pos.y] == RIGHT)
        {
          *action2 = 'r';
        }
        else if (predator3footprint[predator2.pos.x][predator2.pos.y] == LEFT)
        {
          *action2 = 'l';
        }
        else if (predator3footprint[predator2.pos.x][predator2.pos.y] == DOWN)
        {
          *action2 = 'd';
        }
        else
        {
          *action2 = 's';
        }
      }
    }
    else if (finder == 4)
    {
      if (predator4footprint[predator2.pos.x][predator2.pos.y] == 0)
      {
        *action2 = Predator_decide_direction(predator2view);
      }
      else
      {
        if (predator4footprint[predator2.pos.x][predator2.pos.y] == UP)
        {
          *action2 = 'u';
        }
        else if (predator4footprint[predator2.pos.x][predator2.pos.y] == RIGHT)
        {
          *action2 = 'r';
        }
        else if (predator4footprint[predator2.pos.x][predator2.pos.y] == LEFT)
        {
          *action2 = 'l';
        }
        else if (predator4footprint[predator2.pos.x][predator2.pos.y] == DOWN)
        {
          *action2 = 'd';
        }
        else
        {
          *action2 = 's';
        }
      }
    }

    break;

  default: //(0)�F�������̏�
    for (int i = 0; i <= WORLD_SIZE; i++)
    {
      for (int j = 0; j <= WORLD_SIZE; j++)
      {
        if (fieldarray2[i][j] == 1)
        {
          predator2.pos.x = i;
          predator2.pos.y = j;
        }
      }
    }
    /*
    ���E�̓񎟌��z����쐻
    �����E�������Ǝ��Ă�̂��m�F�ł����B
    */
    predator2view[2][2] = 2;
    predator2view[0][0] = fieldarray2[predator2.pos.x - 2][predator2.pos.y - 2];
    predator2view[0][1] = fieldarray2[predator2.pos.x - 2][predator2.pos.y - 1];
    predator2view[0][2] = fieldarray2[predator2.pos.x - 2][predator2.pos.y];
    predator2view[0][3] = fieldarray2[predator2.pos.x - 2][predator2.pos.y + 1];
    predator2view[0][4] = fieldarray2[predator2.pos.x - 2][predator2.pos.y + 2];
    predator2view[1][0] = fieldarray2[predator2.pos.x - 1][predator2.pos.y - 2];
    predator2view[1][1] = fieldarray2[predator2.pos.x - 1][predator2.pos.y - 1];
    predator2view[1][2] = fieldarray2[predator2.pos.x - 1][predator2.pos.y];
    predator2view[1][3] = fieldarray2[predator2.pos.x - 1][predator2.pos.y + 1];
    predator2view[1][4] = fieldarray2[predator2.pos.x - 1][predator2.pos.y + 2];
    predator2view[2][0] = fieldarray2[predator2.pos.x][predator2.pos.y - 2];
    predator2view[2][1] = fieldarray2[predator2.pos.x][predator2.pos.y - 1];
    predator2view[2][3] = fieldarray2[predator2.pos.x][predator2.pos.y + 1];
    predator2view[2][4] = fieldarray2[predator2.pos.x][predator2.pos.y + 2];
    predator2view[3][0] = fieldarray2[predator2.pos.x + 1][predator2.pos.y - 2];
    predator2view[3][1] = fieldarray2[predator2.pos.x + 1][predator2.pos.y - 1];
    predator2view[3][2] = fieldarray2[predator2.pos.x + 1][predator2.pos.y];
    predator2view[3][3] = fieldarray2[predator2.pos.x + 1][predator2.pos.y + 1];
    predator2view[3][4] = fieldarray2[predator2.pos.x + 1][predator2.pos.y + 2];
    predator2view[4][0] = fieldarray2[predator2.pos.x + 2][predator2.pos.y - 2];
    predator2view[4][1] = fieldarray2[predator2.pos.x + 2][predator2.pos.y - 1];
    predator2view[4][2] = fieldarray2[predator2.pos.x + 2][predator2.pos.y];
    predator2view[4][3] = fieldarray2[predator2.pos.x + 2][predator2.pos.y + 1];
    predator2view[4][4] = fieldarray2[predator2.pos.x + 2][predator2.pos.y + 2];

    /*
    ���E�̒��Ɋl����������t���O�𔭌���Ԃɂ��Ď��̍s������ǂ��l�߂邽�߂�case�Ɉڍs���邽�߂̏���
    */
    for (int i = 0; i < 5; i++)
    {
      for (int k = 0; k < 5; k++)
      {
        if (predator2view[i][k] == 10)
        {
          enemyfindflag = 1;
          finder = 2; // 2����������
          situation2 = 1;
        }
      }
    }

    /*
    ���E���֐��ɓn���Ď��ɐi�ޕ��������肷��B
    */
    *action2 = Predator_decide_direction(predator2view);

    /*
�@�@���Ղ��c������
�@�@*/
    if (*action2 == 'u')
    {
      predator2footprint[predator2.pos.x][predator2.pos.y] = UP;
    }
    else if (*action2 == 'r')
    {
      predator2footprint[predator2.pos.x][predator2.pos.y] = RIGHT;
    }
    else if (*action2 == 'l')
    {
      predator2footprint[predator2.pos.x][predator2.pos.y] = LEFT;
    }
    else if (*action2 == 'd')
    {
      predator2footprint[predator2.pos.x][predator2.pos.y] = DOWN;
    }
    else
    {
      predator2footprint[predator2.pos.x][predator2.pos.y] = STAY;
    }

    break;
  }
}

void Predator3(int fieldarray3[WORLD_SIZE][WORLD_SIZE], int *action3)
{
  /*
  ���������ȊO�̒N������ߐH�҂𔭌����Ă����ꍇ�̏���
  */
  if (enemyfindflag != 0)
  {
    situation3 = 2;
  }

  switch (situation3)
  {
  case 1: //�����������ς݂̏�
    for (int i = 0; i <= WORLD_SIZE; i++)
    {
      for (int j = 0; j <= WORLD_SIZE; j++)
      {
        if (fieldarray3[i][j] == 1)
        {
          predator3.pos.x = i;
          predator3.pos.y = j;
        }
      }
    }
    /*
    ���E�̓񎟌��z����쐻
    �����E�������Ǝ��Ă�̂��m�F�ł����B
    */
    predator3view[2][2] = 3;
    predator3view[0][0] = fieldarray3[predator3.pos.x - 2][predator3.pos.y - 2];
    predator3view[0][1] = fieldarray3[predator3.pos.x - 2][predator3.pos.y - 1];
    predator3view[0][2] = fieldarray3[predator3.pos.x - 2][predator3.pos.y];
    predator3view[0][3] = fieldarray3[predator3.pos.x - 2][predator3.pos.y + 1];
    predator3view[0][4] = fieldarray3[predator3.pos.x - 2][predator3.pos.y + 2];
    predator3view[1][0] = fieldarray3[predator3.pos.x - 1][predator3.pos.y - 2];
    predator3view[1][1] = fieldarray3[predator3.pos.x - 1][predator3.pos.y - 1];
    predator3view[1][2] = fieldarray3[predator3.pos.x - 1][predator3.pos.y];
    predator3view[1][3] = fieldarray3[predator3.pos.x - 1][predator3.pos.y + 1];
    predator3view[1][4] = fieldarray3[predator3.pos.x - 1][predator3.pos.y + 2];
    predator3view[2][0] = fieldarray3[predator3.pos.x][predator3.pos.y - 2];
    predator3view[2][1] = fieldarray3[predator3.pos.x][predator3.pos.y - 1];
    predator3view[2][3] = fieldarray3[predator3.pos.x][predator3.pos.y + 1];
    predator3view[2][4] = fieldarray3[predator3.pos.x][predator3.pos.y + 2];
    predator3view[3][0] = fieldarray3[predator3.pos.x + 1][predator3.pos.y - 2];
    predator3view[3][1] = fieldarray3[predator3.pos.x + 1][predator3.pos.y - 1];
    predator3view[3][2] = fieldarray3[predator3.pos.x + 1][predator3.pos.y];
    predator3view[3][3] = fieldarray3[predator3.pos.x + 1][predator3.pos.y + 1];
    predator3view[3][4] = fieldarray3[predator3.pos.x + 1][predator3.pos.y + 2];
    predator3view[4][0] = fieldarray3[predator3.pos.x + 2][predator3.pos.y - 2];
    predator3view[4][1] = fieldarray3[predator3.pos.x + 2][predator3.pos.y - 1];
    predator3view[4][2] = fieldarray3[predator3.pos.x + 2][predator3.pos.y];
    predator3view[4][3] = fieldarray3[predator3.pos.x + 2][predator3.pos.y + 1];
    predator3view[4][4] = fieldarray3[predator3.pos.x + 2][predator3.pos.y + 2];

    /*
    ���E���֐��ɓn���Ď��ɐi�ޕ��������肷��B
    */
    *action3 = Predator_decide_direction(predator3view);

    /*
�@�@���Ղ��c������
�@�@*/
    if (*action3 == 'u')
    {
      predator3footprint[predator3.pos.x][predator3.pos.y] = UP;
    }
    else if (*action3 == 'r')
    {
      predator3footprint[predator3.pos.x][predator3.pos.y] = RIGHT;
    }
    else if (*action3 == 'l')
    {
      predator3footprint[predator3.pos.x][predator3.pos.y] = LEFT;
    }
    else if (*action3 == 'd')
    {
      predator3footprint[predator3.pos.x][predator3.pos.y] = DOWN;
    }
    else
    {
      predator3footprint[predator3.pos.x][predator3.pos.y] = STAY;
    }

    break;

  case 2: //�N�����������Ă��
    for (int i = 0; i <= WORLD_SIZE; i++)
    {
      for (int j = 0; j <= WORLD_SIZE; j++)
      {
        if (fieldarray3[i][j] == 1)
        {
          predator3.pos.x = i;
          predator3.pos.y = j;
        }
      }
    }

    /*
    ���E�̓񎟌��z����쐻
    �����E�������Ǝ��Ă�̂��m�F�ł����B
    */
    predator3view[2][2] = 3;
    predator3view[0][0] = fieldarray3[predator3.pos.x - 2][predator3.pos.y - 2];
    predator3view[0][1] = fieldarray3[predator3.pos.x - 2][predator3.pos.y - 1];
    predator3view[0][2] = fieldarray3[predator3.pos.x - 2][predator3.pos.y];
    predator3view[0][3] = fieldarray3[predator3.pos.x - 2][predator3.pos.y + 1];
    predator3view[0][4] = fieldarray3[predator3.pos.x - 2][predator3.pos.y + 2];
    predator3view[1][0] = fieldarray3[predator3.pos.x - 1][predator3.pos.y - 2];
    predator3view[1][1] = fieldarray3[predator3.pos.x - 1][predator3.pos.y - 1];
    predator3view[1][2] = fieldarray3[predator3.pos.x - 1][predator3.pos.y];
    predator3view[1][3] = fieldarray3[predator3.pos.x - 1][predator3.pos.y + 1];
    predator3view[1][4] = fieldarray3[predator3.pos.x - 1][predator3.pos.y + 2];
    predator3view[2][0] = fieldarray3[predator3.pos.x][predator3.pos.y - 2];
    predator3view[2][1] = fieldarray3[predator3.pos.x][predator3.pos.y - 1];
    predator3view[2][3] = fieldarray3[predator3.pos.x][predator3.pos.y + 1];
    predator3view[2][4] = fieldarray3[predator3.pos.x][predator3.pos.y + 2];
    predator3view[3][0] = fieldarray3[predator3.pos.x + 1][predator3.pos.y - 2];
    predator3view[3][1] = fieldarray3[predator3.pos.x + 1][predator3.pos.y - 1];
    predator3view[3][2] = fieldarray3[predator3.pos.x + 1][predator3.pos.y];
    predator3view[3][3] = fieldarray3[predator3.pos.x + 1][predator3.pos.y + 1];
    predator3view[3][4] = fieldarray3[predator3.pos.x + 1][predator3.pos.y + 2];
    predator3view[4][0] = fieldarray3[predator3.pos.x + 2][predator3.pos.y - 2];
    predator3view[4][1] = fieldarray3[predator3.pos.x + 2][predator3.pos.y - 1];
    predator3view[4][2] = fieldarray3[predator3.pos.x + 2][predator3.pos.y];
    predator3view[4][3] = fieldarray3[predator3.pos.x + 2][predator3.pos.y + 1];
    predator3view[4][4] = fieldarray3[predator3.pos.x + 2][predator3.pos.y + 2];

    /*
    �ŏ��Ɋl�����������ߐH�҂�1�̎��A2�̎��A4�̎��B
    */
    if (finder == 1)
    {
      if (predator1footprint[predator3.pos.x][predator3.pos.y] == 0)
      {
        *action3 = Predator_decide_direction(predator3view);
      }
      else
      {
        if (predator1footprint[predator3.pos.x][predator3.pos.y] == UP)
        {
          *action3 = 'u';
        }
        else if (predator1footprint[predator3.pos.x][predator3.pos.y] == RIGHT)
        {
          *action3 = 'r';
        }
        else if (predator1footprint[predator3.pos.x][predator3.pos.y] == LEFT)
        {
          *action3 = 'l';
        }
        else if (predator1footprint[predator3.pos.x][predator3.pos.y] == DOWN)
        {
          *action3 = 'd';
        }
        else
        {
          *action3 = 's';
        }
      }
    }
    else if (finder == 2)
    {
      if (predator2footprint[predator3.pos.x][predator3.pos.y] == 0)
      {
        *action3 = Predator_decide_direction(predator3view);
      }
      else
      {
        if (predator2footprint[predator3.pos.x][predator3.pos.y] == UP)
        {
          *action3 = 'u';
        }
        else if (predator2footprint[predator3.pos.x][predator3.pos.y] == RIGHT)
        {
          *action3 = 'r';
        }
        else if (predator2footprint[predator3.pos.x][predator3.pos.y] == LEFT)
        {
          *action3 = 'l';
        }
        else if (predator2footprint[predator3.pos.x][predator3.pos.y] == DOWN)
        {
          *action3 = 'd';
        }
        else
        {
          *action3 = 's';
        }
      }
    }
    else if (finder == 4)
    {
      if (predator4footprint[predator3.pos.x][predator3.pos.y] == 0)
      {
        *action3 = Predator_decide_direction(predator3view);
      }
      else
      {
        if (predator4footprint[predator3.pos.x][predator3.pos.y] == UP)
        {
          *action3 = 'u';
        }
        else if (predator4footprint[predator3.pos.x][predator3.pos.y] == RIGHT)
        {
          *action3 = 'r';
        }
        else if (predator4footprint[predator3.pos.x][predator3.pos.y] == LEFT)
        {
          *action3 = 'l';
        }
        else if (predator4footprint[predator3.pos.x][predator3.pos.y] == DOWN)
        {
          *action3 = 'd';
        }
        else
        {
          *action3 = 's';
        }
      }
    }

    break;

  default: //(0)�F�������̏�
    for (int i = 0; i <= WORLD_SIZE; i++)
    {
      for (int j = 0; j <= WORLD_SIZE; j++)
      {
        if (fieldarray3[i][j] == 1)
        {
          predator3.pos.x = i;
          predator3.pos.y = j;
        }
      }
    }
    /*
    ���E�̓񎟌��z����쐻
    �����E�������Ǝ��Ă�̂��m�F�ł����B
    */
    predator3view[2][2] = 3;
    predator3view[0][0] = fieldarray3[predator3.pos.x - 2][predator3.pos.y - 2];
    predator3view[0][1] = fieldarray3[predator3.pos.x - 2][predator3.pos.y - 1];
    predator3view[0][2] = fieldarray3[predator3.pos.x - 2][predator3.pos.y];
    predator3view[0][3] = fieldarray3[predator3.pos.x - 2][predator3.pos.y + 1];
    predator3view[0][4] = fieldarray3[predator3.pos.x - 2][predator3.pos.y + 2];
    predator3view[1][0] = fieldarray3[predator3.pos.x - 1][predator3.pos.y - 2];
    predator3view[1][1] = fieldarray3[predator3.pos.x - 1][predator3.pos.y - 1];
    predator3view[1][2] = fieldarray3[predator3.pos.x - 1][predator3.pos.y];
    predator3view[1][3] = fieldarray3[predator3.pos.x - 1][predator3.pos.y + 1];
    predator3view[1][4] = fieldarray3[predator3.pos.x - 1][predator3.pos.y + 2];
    predator3view[2][0] = fieldarray3[predator3.pos.x][predator3.pos.y - 2];
    predator3view[2][1] = fieldarray3[predator3.pos.x][predator3.pos.y - 1];
    predator3view[2][3] = fieldarray3[predator3.pos.x][predator3.pos.y + 1];
    predator3view[2][4] = fieldarray3[predator3.pos.x][predator3.pos.y + 2];
    predator3view[3][0] = fieldarray3[predator3.pos.x + 1][predator3.pos.y - 2];
    predator3view[3][1] = fieldarray3[predator3.pos.x + 1][predator3.pos.y - 1];
    predator3view[3][2] = fieldarray3[predator3.pos.x + 1][predator3.pos.y];
    predator3view[3][3] = fieldarray3[predator3.pos.x + 1][predator3.pos.y + 1];
    predator3view[3][4] = fieldarray3[predator3.pos.x + 1][predator3.pos.y + 2];
    predator3view[4][0] = fieldarray3[predator3.pos.x + 2][predator3.pos.y - 2];
    predator3view[4][1] = fieldarray3[predator3.pos.x + 2][predator3.pos.y - 1];
    predator3view[4][2] = fieldarray3[predator3.pos.x + 2][predator3.pos.y];
    predator3view[4][3] = fieldarray3[predator3.pos.x + 2][predator3.pos.y + 1];
    predator3view[4][4] = fieldarray3[predator3.pos.x + 2][predator3.pos.y + 2];

    /*
    ���E�̒��Ɋl����������t���O�𔭌���Ԃɂ��Ď��̍s������ǂ��l�߂邽�߂�case�Ɉڍs���邽�߂̏���
    */
    for (int i = 0; i < 5; i++)
    {
      for (int k = 0; k < 5; k++)
      {
        if (predator3view[i][k] == 10)
        {
          enemyfindflag = 1;
          finder = 3; // 3����������
          situation3 = 1;
        }
      }
    }

    /*
    ���E���֐��ɓn���Ď��ɐi�ޕ��������肷��B
    */
    *action3 = Predator_decide_direction(predator3view);

    /*
�@�@���Ղ��c������
�@�@*/
    if (*action3 == 'u')
    {
      predator3footprint[predator3.pos.x][predator3.pos.y] = UP;
    }
    else if (*action3 == 'r')
    {
      predator3footprint[predator3.pos.x][predator3.pos.y] = RIGHT;
    }
    else if (*action3 == 'l')
    {
      predator3footprint[predator3.pos.x][predator3.pos.y] = LEFT;
    }
    else if (*action3 == 'd')
    {
      predator3footprint[predator3.pos.x][predator3.pos.y] = DOWN;
    }
    else
    {
      predator3footprint[predator3.pos.x][predator3.pos.y] = STAY;
    }

    break;
  }
}

void Predator4(int fieldarray4[WORLD_SIZE][WORLD_SIZE], int *action4)
{
  /*
  ���������ȊO�̒N������ߐH�҂𔭌����Ă����ꍇ�̏���
  */
  if (enemyfindflag != 0)
  {
    situation4 = 2;
  }

  switch (situation4)
  {
  case 1: //�����������ς݂̏�
    for (int i = 0; i <= WORLD_SIZE; i++)
    {
      for (int j = 0; j <= WORLD_SIZE; j++)
      {
        if (fieldarray4[i][j] == 1)
        {
          predator4.pos.x = i;
          predator4.pos.y = j;
        }
      }
    }
    /*
    ���E�̓񎟌��z����쐻
    �����E�������Ǝ��Ă�̂��m�F�ł����B
    */
    predator4view[2][2] = 4;
    predator4view[0][0] = fieldarray4[predator4.pos.x - 2][predator4.pos.y - 2];
    predator4view[0][1] = fieldarray4[predator4.pos.x - 2][predator4.pos.y - 1];
    predator4view[0][2] = fieldarray4[predator4.pos.x - 2][predator4.pos.y];
    predator4view[0][3] = fieldarray4[predator4.pos.x - 2][predator4.pos.y + 1];
    predator4view[0][4] = fieldarray4[predator4.pos.x - 2][predator4.pos.y + 2];
    predator4view[1][0] = fieldarray4[predator4.pos.x - 1][predator4.pos.y - 2];
    predator4view[1][1] = fieldarray4[predator4.pos.x - 1][predator4.pos.y - 1];
    predator4view[1][2] = fieldarray4[predator4.pos.x - 1][predator4.pos.y];
    predator4view[1][3] = fieldarray4[predator4.pos.x - 1][predator4.pos.y + 1];
    predator4view[1][4] = fieldarray4[predator4.pos.x - 1][predator4.pos.y + 2];
    predator4view[2][0] = fieldarray4[predator4.pos.x][predator4.pos.y - 2];
    predator4view[2][1] = fieldarray4[predator4.pos.x][predator4.pos.y - 1];
    predator4view[2][3] = fieldarray4[predator4.pos.x][predator4.pos.y + 1];
    predator4view[2][4] = fieldarray4[predator4.pos.x][predator4.pos.y + 2];
    predator4view[3][0] = fieldarray4[predator4.pos.x + 1][predator4.pos.y - 2];
    predator4view[3][1] = fieldarray4[predator4.pos.x + 1][predator4.pos.y - 1];
    predator4view[3][2] = fieldarray4[predator4.pos.x + 1][predator4.pos.y];
    predator4view[3][3] = fieldarray4[predator4.pos.x + 1][predator4.pos.y + 1];
    predator4view[3][4] = fieldarray4[predator4.pos.x + 1][predator4.pos.y + 2];
    predator4view[4][0] = fieldarray4[predator4.pos.x + 2][predator4.pos.y - 2];
    predator4view[4][1] = fieldarray4[predator4.pos.x + 2][predator4.pos.y - 1];
    predator4view[4][2] = fieldarray4[predator4.pos.x + 2][predator4.pos.y];
    predator4view[4][3] = fieldarray4[predator4.pos.x + 2][predator4.pos.y + 1];
    predator4view[4][4] = fieldarray4[predator4.pos.x + 2][predator4.pos.y + 2];

    /*
    ���E���֐��ɓn���Ď��ɐi�ޕ��������肷��B
    */
    *action4 = Predator_decide_direction(predator4view);

    /*
�@�@���Ղ��c������
�@�@*/
    if (*action4 == 'u')
    {
      predator4footprint[predator4.pos.x][predator4.pos.y] = UP;
    }
    else if (*action4 == 'r')
    {
      predator4footprint[predator4.pos.x][predator4.pos.y] = RIGHT;
    }
    else if (*action4 == 'l')
    {
      predator4footprint[predator4.pos.x][predator4.pos.y] = LEFT;
    }
    else if (*action4 == 'd')
    {
      predator4footprint[predator4.pos.x][predator4.pos.y] = DOWN;
    }
    else
    {
      predator4footprint[predator4.pos.x][predator4.pos.y] = STAY;
    }

    break;

  case 2: //�N�����������Ă��
    for (int i = 0; i <= WORLD_SIZE; i++)
    {
      for (int j = 0; j <= WORLD_SIZE; j++)
      {
        if (fieldarray4[i][j] == 1)
        {
          predator4.pos.x = i;
          predator4.pos.y = j;
        }
      }
    }

    /*
    ���E�̓񎟌��z����쐻
    �����E�������Ǝ��Ă�̂��m�F�ł����B
    */
    predator4view[2][2] = 4;
    predator4view[0][0] = fieldarray4[predator4.pos.x - 2][predator4.pos.y - 2];
    predator4view[0][1] = fieldarray4[predator4.pos.x - 2][predator4.pos.y - 1];
    predator4view[0][2] = fieldarray4[predator4.pos.x - 2][predator4.pos.y];
    predator4view[0][3] = fieldarray4[predator4.pos.x - 2][predator4.pos.y + 1];
    predator4view[0][4] = fieldarray4[predator4.pos.x - 2][predator4.pos.y + 2];
    predator4view[1][0] = fieldarray4[predator4.pos.x - 1][predator4.pos.y - 2];
    predator4view[1][1] = fieldarray4[predator4.pos.x - 1][predator4.pos.y - 1];
    predator4view[1][2] = fieldarray4[predator4.pos.x - 1][predator4.pos.y];
    predator4view[1][3] = fieldarray4[predator4.pos.x - 1][predator4.pos.y + 1];
    predator4view[1][4] = fieldarray4[predator4.pos.x - 1][predator4.pos.y + 2];
    predator4view[2][0] = fieldarray4[predator4.pos.x][predator4.pos.y - 2];
    predator4view[2][1] = fieldarray4[predator4.pos.x][predator4.pos.y - 1];
    predator4view[2][3] = fieldarray4[predator4.pos.x][predator4.pos.y + 1];
    predator4view[2][4] = fieldarray4[predator4.pos.x][predator4.pos.y + 2];
    predator4view[3][0] = fieldarray4[predator4.pos.x + 1][predator4.pos.y - 2];
    predator4view[3][1] = fieldarray4[predator4.pos.x + 1][predator4.pos.y - 1];
    predator4view[3][2] = fieldarray4[predator4.pos.x + 1][predator4.pos.y];
    predator4view[3][3] = fieldarray4[predator4.pos.x + 1][predator4.pos.y + 1];
    predator4view[3][4] = fieldarray4[predator4.pos.x + 1][predator4.pos.y + 2];
    predator4view[4][0] = fieldarray4[predator4.pos.x + 2][predator4.pos.y - 2];
    predator4view[4][1] = fieldarray4[predator4.pos.x + 2][predator4.pos.y - 1];
    predator4view[4][2] = fieldarray4[predator4.pos.x + 2][predator4.pos.y];
    predator4view[4][3] = fieldarray4[predator4.pos.x + 2][predator4.pos.y + 1];
    predator4view[4][4] = fieldarray4[predator4.pos.x + 2][predator4.pos.y + 2];

    /*
    �ŏ��Ɋl�����������ߐH�҂�1�̎��A2�̎��A3�̎��B
    */
    if (finder == 1)
    {
      if (predator1footprint[predator4.pos.x][predator4.pos.y] == 0)
      {
        *action4 = Predator_decide_direction(predator4view);
      }
      else
      {
        if (predator1footprint[predator4.pos.x][predator4.pos.y] == UP)
        {
          *action4 = 'u';
        }
        else if (predator1footprint[predator4.pos.x][predator4.pos.y] == RIGHT)
        {
          *action4 = 'r';
        }
        else if (predator1footprint[predator4.pos.x][predator4.pos.y] == LEFT)
        {
          *action4 = 'l';
        }
        else if (predator1footprint[predator4.pos.x][predator4.pos.y] == DOWN)
        {
          *action4 = 'd';
        }
        else
        {
          *action4 = 's';
        }
      }
    }
    else if (finder == 2)
    {
      if (predator2footprint[predator4.pos.x][predator4.pos.y] == 0)
      {
        *action4 = Predator_decide_direction(predator4view);
      }
      else
      {
        if (predator2footprint[predator4.pos.x][predator4.pos.y] == UP)
        {
          *action4 = 'u';
        }
        else if (predator2footprint[predator4.pos.x][predator4.pos.y] == RIGHT)
        {
          *action4 = 'r';
        }
        else if (predator2footprint[predator4.pos.x][predator4.pos.y] == LEFT)
        {
          *action4 = 'l';
        }
        else if (predator2footprint[predator4.pos.x][predator4.pos.y] == DOWN)
        {
          *action4 = 'd';
        }
        else
        {
          *action4 = 's';
        }
      }
    }
    else if (finder == 3)
    {
      if (predator3footprint[predator4.pos.x][predator4.pos.y] == 0)
      {
        *action4 = Predator_decide_direction(predator4view);
      }
      else
      {
        if (predator3footprint[predator4.pos.x][predator4.pos.y] == UP)
        {
          *action4 = 'u';
        }
        else if (predator3footprint[predator4.pos.x][predator4.pos.y] == RIGHT)
        {
          *action4 = 'r';
        }
        else if (predator3footprint[predator4.pos.x][predator4.pos.y] == LEFT)
        {
          *action4 = 'l';
        }
        else if (predator3footprint[predator4.pos.x][predator4.pos.y] == DOWN)
        {
          *action4 = 'd';
        }
        else
        {
          *action4 = 's';
        }
      }
    }

    break;

  default: //(0)�F�������̏�
    for (int i = 0; i <= WORLD_SIZE; i++)
    {
      for (int j = 0; j <= WORLD_SIZE; j++)
      {
        if (fieldarray4[i][j] == 1)
        {
          predator4.pos.x = i;
          predator4.pos.y = j;
        }
      }
    }
    /*
    ���E�̓񎟌��z����쐻
    �����E�������Ǝ��Ă�̂��m�F�ł����B
    */
    predator4view[2][2] = 4;
    predator4view[0][0] = fieldarray4[predator4.pos.x - 2][predator4.pos.y - 2];
    predator4view[0][1] = fieldarray4[predator4.pos.x - 2][predator4.pos.y - 1];
    predator4view[0][2] = fieldarray4[predator4.pos.x - 2][predator4.pos.y];
    predator4view[0][3] = fieldarray4[predator4.pos.x - 2][predator4.pos.y + 1];
    predator4view[0][4] = fieldarray4[predator4.pos.x - 2][predator4.pos.y + 2];
    predator4view[1][0] = fieldarray4[predator4.pos.x - 1][predator4.pos.y - 2];
    predator4view[1][1] = fieldarray4[predator4.pos.x - 1][predator4.pos.y - 1];
    predator4view[1][2] = fieldarray4[predator4.pos.x - 1][predator4.pos.y];
    predator4view[1][3] = fieldarray4[predator4.pos.x - 1][predator4.pos.y + 1];
    predator4view[1][4] = fieldarray4[predator4.pos.x - 1][predator4.pos.y + 2];
    predator4view[2][0] = fieldarray4[predator4.pos.x][predator4.pos.y - 2];
    predator4view[2][1] = fieldarray4[predator4.pos.x][predator4.pos.y - 1];
    predator4view[2][3] = fieldarray4[predator4.pos.x][predator4.pos.y + 1];
    predator4view[2][4] = fieldarray4[predator4.pos.x][predator4.pos.y + 2];
    predator4view[3][0] = fieldarray4[predator4.pos.x + 1][predator4.pos.y - 2];
    predator4view[3][1] = fieldarray4[predator4.pos.x + 1][predator4.pos.y - 1];
    predator4view[3][2] = fieldarray4[predator4.pos.x + 1][predator4.pos.y];
    predator4view[3][3] = fieldarray4[predator4.pos.x + 1][predator4.pos.y + 1];
    predator4view[3][4] = fieldarray4[predator4.pos.x + 1][predator4.pos.y + 2];
    predator4view[4][0] = fieldarray4[predator4.pos.x + 2][predator4.pos.y - 2];
    predator4view[4][1] = fieldarray4[predator4.pos.x + 2][predator4.pos.y - 1];
    predator4view[4][2] = fieldarray4[predator4.pos.x + 2][predator4.pos.y];
    predator4view[4][3] = fieldarray4[predator4.pos.x + 2][predator4.pos.y + 1];
    predator4view[4][4] = fieldarray4[predator4.pos.x + 2][predator4.pos.y + 2];

    /*
    ���E�̒��Ɋl����������t���O�𔭌���Ԃɂ��Ď��̍s������ǂ��l�߂邽�߂�case�Ɉڍs���邽�߂̏���
    */
    for (int i = 0; i < 5; i++)
    {
      for (int k = 0; k < 5; k++)
      {
        if (predator4view[i][k] == 10)
        {
          enemyfindflag = 1;
          finder = 4; // 4����������
          situation4 = 1;
        }
      }
    }

    /*
    ���E���֐��ɓn���Ď��ɐi�ޕ��������肷��B
    */
    *action4 = Predator_decide_direction(predator4view);

    /*
�@�@���Ղ��c������
�@�@*/
    if (*action4 == 'u')
    {
      predator4footprint[predator4.pos.x][predator4.pos.y] = UP;
    }
    else if (*action4 == 'r')
    {
      predator4footprint[predator4.pos.x][predator4.pos.y] = RIGHT;
    }
    else if (*action4 == 'l')
    {
      predator4footprint[predator4.pos.x][predator4.pos.y] = LEFT;
    }
    else if (*action4 == 'd')
    {
      predator4footprint[predator4.pos.x][predator4.pos.y] = DOWN;
    }
    else
    {
      predator4footprint[predator4.pos.x][predator4.pos.y] = STAY;
    }

    break;
  }
}

void Predator(int fieldarray1[WORLD_SIZE][WORLD_SIZE], int fieldarray2[WORLD_SIZE][WORLD_SIZE], int fieldarray3[WORLD_SIZE][WORLD_SIZE], int fieldarray4[WORLD_SIZE][WORLD_SIZE], int *action1, int *action2, int *action3, int *action4)
{
  Predator1(fieldarray1, action1);
  Predator2(fieldarray2, action2);
  Predator3(fieldarray3, action3);
  Predator4(fieldarray4, action4);
}
