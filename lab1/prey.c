/*
 Author:       Daichi Sato
 Student ID:   b1019159
 Class:        K
 Created:      November 2, 2021
 Language:     C
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/* �i�q���E�̑傫�� */
#ifndef WORLD_SIZE
#define WORLD_SIZE 8
#endif
/* predator�̐��l�\�� */
#ifndef VALUE_OF_PREDATOR
#define VALUE_OF_PREDATOR 1
#endif
/* prey�̐��l�\�� */
#ifndef VALUE_OF_PREY
#define VALUE_OF_PREY 10
#endif
/* obstacle�̐��l�\�� */
#ifndef VALUE_OF_OBSTACLE
#define VALUE_OF_OBSTACLE -1
#endif
/* free grid�̐��l�\�� */
#ifndef VALUE_OF_FREE
#define VALUE_OF_FREE 0
#endif
/* �T���ς݂̐��l�\�� */
#ifndef VALUE_OF_SEARCHED
#define VALUE_OF_SEARCHED 3
#endif
/* �����g�p���Ȃ����l�\�� */
#ifndef VALUE_OF_EXCEPT
#define VALUE_OF_EXCEPT 6
#endif

/*
 *Predator�����Prey�̈ʒu��\���\����
 */
typedef struct
{
  int x2;
  int y2;
} Prey_pursuit_position;

/*
 ���ׂ���W�̏����i�[����\����
*/
typedef struct
{
  Prey_pursuit_position pos2;     //���݈ʒu
  Prey_pursuit_position backpos2; //��O�̈ʒu
  double cost2;                   //�R�X�g
  int attri2;                     //���
} prey_node;

/*
int�^�Ŏ󂯎�鐢�E�̏���predetor_node�^�֗��Ƃ����ނ��߂̔z��
*/
prey_node prey_maparray0[WORLD_SIZE][WORLD_SIZE];

/*
���ɒT������n�_�̌�������L���[
�L���[�̏����100
temporarynode�͈ꎞ�I�ɒl��ۑ����邽�߂̂���
*/
#define SEARCHQUE_LIMIT 100
prey_node *prey_searchque[SEARCHQUE_LIMIT];
prey_node *prey_temporarynode;
int prey_searchque_head;

/*
�L���[��push����
�v�b�V�������ۂɂ̓R�X�g�̌y�����ɕ��ѕς���悤�ɂ��Ă���
*/
void prey_que_push(prey_node *node)
{
  int i, j;

  if (prey_searchque_head >= SEARCHQUE_LIMIT)
  {
    return;
  }
  prey_searchque[prey_searchque_head] = node;
  prey_searchque_head++;

  if (prey_searchque_head <= 1)
  {
    return;
  }

  for (i = 0; i < prey_searchque_head; i++)
  {
    for (j = 1; j < prey_searchque_head - i; j++)
    {
      if (prey_searchque[j - 1]->cost2 < prey_searchque[j]->cost2)
      {
        prey_temporarynode = prey_searchque[j - 1];
        prey_searchque[j - 1] = prey_searchque[j];
        prey_searchque[j] = prey_temporarynode;
      }
    }
  }
}

/*
�T�����X�g����������o��
*/
prey_node *prey_que_pop(void)
{
  if (prey_searchque_head == 0)
  {
    return NULL;
  }
  prey_searchque_head--;
  return prey_searchque[prey_searchque_head];
}

/*
predator�̌o�H�T�������BA*�A���S���Y����p���Ă���B
*/
int prey_strategem(int maparray[WORLD_SIZE][WORLD_SIZE])
{
  Prey_pursuit_position difpos[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  int i, j, checkx, checky, checkcount, predatorx, preyx, predatory, preyy;
  double cost;
  /*
  �T�����錻�݈ʒu��prey_node
  */
  prey_node *nowpos;
  /*
  �L���[�̐擪�ʒu��0��
  */
  prey_searchque_head = 0;

  /*
  int�^�̐��E����preadtor_node�^�ɗ��Ƃ����ނ��߂̏���
  */
  for (i = 0; i < WORLD_SIZE; i++)
  {
    for (j = 0; j < WORLD_SIZE; j++)
    {
      if (maparray[i][j] == VALUE_OF_OBSTACLE)
      {
        prey_maparray0[i][j].attri2 = VALUE_OF_OBSTACLE;
        prey_maparray0[i][j].pos2.x2 = j;
        prey_maparray0[i][j].pos2.y2 = i;
      }

      if (maparray[i][j] == VALUE_OF_FREE)
      {
        prey_maparray0[i][j].attri2 = VALUE_OF_FREE;
        prey_maparray0[i][j].pos2.x2 = j;
        prey_maparray0[i][j].pos2.y2 = i;
      }

      if (maparray[i][j] == VALUE_OF_PREDATOR)
      {
        predatorx = j;
        predatory = i;
        prey_maparray0[i][j].attri2 = VALUE_OF_PREDATOR;
        prey_maparray0[i][j].pos2.x2 = j;
        prey_maparray0[i][j].pos2.y2 = i;
      }

      if (maparray[i][j] == VALUE_OF_PREY)
      {
        preyx = j;
        preyy = i;
        prey_maparray0[i][j].attri2 = VALUE_OF_PREY;
        prey_maparray0[i][j].pos2.x2 = j;
        prey_maparray0[i][j].pos2.y2 = i;
      }
    }
  }

  /*
  �X�^�[�g�ʒu���L���[��
  */
  prey_que_push(&prey_maparray0[predatory][predatorx]);
  /*
  �T����predator�ɍs���܂Ń��[�v����
  */
  do
  {
    /*
    ���ׂ�ʒu���L���[������o��
    */
    nowpos = prey_que_pop();
    /*
    4�������ׂ�
    */
    checkcount = 0;

    for (i = 0; i < 4; i++)
    {
      checkx = nowpos->pos2.x2 + difpos[i].x2;
      checky = nowpos->pos2.y2 + difpos[i].y2;

      /*
      �`�F�b�N�����ʒu�����[���h�̊O��������ŏ�����
      */
      if ((checky < 0) || (checky >= WORLD_SIZE) || (checkx < 0) || (checkx >= WORLD_SIZE))
      {
        continue;
      }

      /*
      prey�������甲����
      */
      if (maparray[checky][checkx] == VALUE_OF_PREY)
      {
        prey_maparray0[checky][checkx].backpos2.x2 = nowpos->pos2.x2;
        prey_maparray0[checky][checkx].backpos2.y2 = nowpos->pos2.y2;
        break;
      }

      /*
      �ǂƂ������ς݂������疳�����Ď��̌���
      */
      if (maparray[checky][checkx] != VALUE_OF_FREE)
      {
        continue;
      }

      /*
      �R�X�g�𓾂�B����R�X�g�Ȃ̂Œ�������
      */
      cost = sqrt(abs((preyx - checkx)) * abs((preyx - checkx)) + abs((preyy - checky)) * abs((preyy - checky)));

      /*
      �R�X�g��ۑ������̒�����
      */
      maparray[checky][checkx] = VALUE_OF_SEARCHED;
      prey_maparray0[checky][checkx].attri2 = VALUE_OF_SEARCHED;
      prey_maparray0[checky][checkx].cost2 = cost;
      prey_maparray0[checky][checkx].backpos2.x2 = nowpos->pos2.x2;
      prey_maparray0[checky][checkx].backpos2.y2 = nowpos->pos2.y2;
      prey_que_push(&prey_maparray0[checky][checkx]);
      checkcount++;
    }
    /*
    4�������ׂ����_�łǂ������ׂ��Ȃ������炻���͍��㏜�O����
    */
    if ((!checkcount) && (nowpos->attri2 == VALUE_OF_SEARCHED))
    {
      nowpos->attri2 = VALUE_OF_EXCEPT;
    }
    if (nowpos->attri2 == VALUE_OF_FREE)
    {
      nowpos->attri2 = VALUE_OF_SEARCHED;
    }
  } while (maparray[checky][checkx] != VALUE_OF_PREY);

  /*
  A*�A���S���Y���ōs�������ڕW�n�_�̑O�ɒ��ׂĂ����ꏊ���玟�ɐi�ނׂ����������肷��
  */
  /*
 prey�ɍs�������O�̈ʒu��prey�̉E���������ꍇ
 */
  if (prey_maparray0[checky][checkx].backpos2.y2 == checky && prey_maparray0[checky][checkx].backpos2.x2 == checkx + 1)
  {
    /*
    �����p�ɂ�������
    */
    if ((checky == 7 || maparray[checky + 1][checkx] == VALUE_OF_OBSTACLE) && (checkx == 0 || maparray[checky][checkx - 1] == VALUE_OF_OBSTACLE))
    {
      return 'u';
    }
    /*
    ����p�ɂ����牺��
    */
    else if ((checky == 0 || maparray[checky - 1][checkx] == VALUE_OF_OBSTACLE) && (checkx == 0 || maparray[checky][checkx - 1] == VALUE_OF_OBSTACLE))
    {
      return 'd';
    }
    /*
    check�����ʒu�Ƃ��̑O�̈ʒu�Ƃ܂����̑O�̈ʒu����T�����[�g����肵�ē����������Ԃ�
    prey�̉E���T�����Ă����牺��
    */
    else if (((checkx == 0) || (maparray[checky][checkx - 1] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.x2) == (checkx + 1)) && ((prey_maparray0[checky][checkx + 1].backpos2.y2) == (checky - 1)))
    {
      return 'd';
    }
    /*
    check�����ʒu�Ƃ��̑O�̈ʒu�Ƃ܂����̑O�̈ʒu����T�����[�g����肵�ē����������Ԃ�
    prey�̉E����T�����Ă�������
    */
    else if (((checkx == 0) || (maparray[checky][checkx - 1] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.x2) == (checkx + 1)) && ((prey_maparray0[checky][checkx + 1].backpos2.y2) == (checky + 1)))
    {
      return 'u';
    }
    /*
    ����ȊO�͂Ƃ肠�������Ɣ���
    */
    else
    {
      /*
      ���Ǐオ5�}�X�󂢂Ă����ɍs��
      */
      if (checky != 0)
      {
        if ((prey_maparray0[checky - 1][checkx].attri2 == VALUE_OF_FREE && checky - 1 != -1) && (prey_maparray0[checky - 2][checkx].attri2 == VALUE_OF_FREE && checky - 2 != -1) && (prey_maparray0[checky - 3][checkx].attri2 == VALUE_OF_FREE && checky - 3 != -1) && (prey_maparray0[checky - 4][checkx].attri2 == VALUE_OF_FREE && checky - 4 != -1) && (prey_maparray0[checky - 5][checkx].attri2 == VALUE_OF_FREE && checky - 5 != -1))
        {
          return 'u';
        }
      }
      /*
      ���ǉ���5�}�X�󂢂Ă��牺�ɍs��
      */
      if (checky != 7)
      {
        if ((prey_maparray0[checky + 1][checkx].attri2 == VALUE_OF_FREE && checky + 1 != 8) && (prey_maparray0[checky + 2][checkx].attri2 == VALUE_OF_FREE && checky + 2 != 8) && (prey_maparray0[checky + 3][checkx].attri2 == VALUE_OF_FREE && checky + 3 != 8) && (prey_maparray0[checky + 4][checkx].attri2 == VALUE_OF_FREE && checky + 4 != 8) && (prey_maparray0[checky + 5][checkx].attri2 == VALUE_OF_FREE && checky + 5 != 8))
        {
          return 'd';
        }
      }
      return 'l';
    }
  }

  /*
 prey�ɍs�������O�̈ʒu��prey�̉����������ꍇ
 */
  else if (prey_maparray0[checky][checkx].backpos2.y2 == checky + 1 && prey_maparray0[checky][checkx].backpos2.x2 == checkx)
  {
    /*
    �E��p�ɂ����獶��
    */
    if ((checky == 0 || maparray[checky][checkx + 1] == VALUE_OF_OBSTACLE) && (checkx == 7 || maparray[checky + 1][checkx] == VALUE_OF_OBSTACLE))
    {
      return 'l';
    }
    /*
    ����p�ɂ�����E��
    */
    else if ((checky == 0 || maparray[checky][checkx - 1] == VALUE_OF_OBSTACLE) && (checkx == 0 || maparray[checky - 1][checkx] == VALUE_OF_OBSTACLE))
    {
      return 'r';
    }
    /*
    check�����ʒu�Ƃ��̑O�̈ʒu�Ƃ܂����̑O�̈ʒu����T�����[�g����肵�ē����������Ԃ�
    prey�̍�����T�����Ă�����E��
    */
    else if (((checky == 0) || (maparray[checky - 1][checkx] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.y2) == (checky + 1)) && ((prey_maparray0[checky + 1][checkx].backpos2.x2) == (checkx + 1)))
    {
      return 'r';
    }
    /*
    check�����ʒu�Ƃ��̑O�̈ʒu�Ƃ܂����̑O�̈ʒu����T�����[�g����肵�ē����������Ԃ�
    prey�̉E����T�����Ă����獶��
    */
    else if (((checky == 0) || (maparray[checky - 1][checkx] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.y2) == (checky + 1)) && ((prey_maparray0[checky + 1][checkx].backpos2.x2) == (checkx - 1)))
    {
      return 'l';
    }
    /*
    ����ȊO�͂Ƃ肠������Ɣ���
    */
    else
    {
      /*
      ���ǉE��5�}�X�󂢂Ă���E�ɍs��
      */
      if (checkx != 7)
      {
        if ((prey_maparray0[checky][checkx + 1].attri2 == VALUE_OF_FREE && checkx + 1 != 8) && (prey_maparray0[checky][checkx + 2].attri2 == VALUE_OF_FREE && checkx + 2 != 8) && (prey_maparray0[checky][checkx + 3].attri2 == VALUE_OF_FREE && checkx + 3 != 8) && (prey_maparray0[checky][checkx + 4].attri2 == VALUE_OF_FREE && checkx + 4 != 8) && (prey_maparray0[checky][checkx + 5].attri2 == VALUE_OF_FREE && checkx + 5 != 8))
        {
          return 'r';
        }
      }

      /*
      ���Ǎ���5�}�X�󂢂Ă��獶�ɍs��
      */
      if (checkx != 0)
      {
        if ((prey_maparray0[checky][checkx - 1].attri2 == VALUE_OF_FREE && checkx - 1 != -1) && (prey_maparray0[checky][checkx - 2].attri2 == VALUE_OF_FREE && checkx - 2 != -1) && (prey_maparray0[checky][checkx - 3].attri2 == VALUE_OF_FREE && checkx - 3 != -1) && (prey_maparray0[checky][checkx - 4].attri2 == VALUE_OF_FREE && checkx - 4 != -1) && (prey_maparray0[checky][checkx - 5].attri2 == VALUE_OF_FREE && checkx - 5 != -1))
        {
          return 'l';
        }
      }

      return 'u';
    }
  }

  /*
 prey�ɍs�������O�̈ʒu��prey�̍����������ꍇ
 */
  else if (prey_maparray0[checky][checkx].backpos2.y2 == checky && prey_maparray0[checky][checkx].backpos2.x2 == checkx - 1)
  {
    /*
    �E���p�ɂ�������
    */
    if ((checky == 7 || maparray[checky + 1][checkx] == VALUE_OF_OBSTACLE) && (checkx == 7 || maparray[checky][checkx + 1] == VALUE_OF_OBSTACLE))
    {
      return 'u';
    }
    /*
    �E��p�ɂ����牺��
    */
    else if ((checky == 0 || maparray[checky - 1][checkx] == VALUE_OF_OBSTACLE) && (checkx == 7 || maparray[checky][checkx + 1] == VALUE_OF_OBSTACLE))
    {
      return 'd';
    }
    /*
    check�����ʒu�Ƃ��̑O�̈ʒu�Ƃ܂����̑O�̈ʒu����T�����[�g����肵�ē����������Ԃ�
    prey�̍�����T�����Ă�������
    */
    else if (((checkx == 7) || (maparray[checky][checkx + 1] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.x2) == (checkx - 1)) && ((prey_maparray0[checky][checkx - 1].backpos2.y2) == (checky + 1)))
    {
      return 'u';
    }
    /*
    check�����ʒu�Ƃ��̑O�̈ʒu�Ƃ܂����̑O�̈ʒu����T�����[�g����肵�ē����������Ԃ�
    prey�̍����T�����Ă����牺��
    */
    else if (((checkx == 7) || (maparray[checky][checkx + 1] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.x2) == (checkx - 1)) && ((prey_maparray0[checky][checkx - 1].backpos2.y2) == (checky - 1)))
    {
      return 'd';
    }
    /*
    ����ȊO�͂Ƃ肠�����E�Ɣ���
    */
    else
    {
      /*
      ���Ǐオ5�}�X�󂢂Ă����ɍs��
      */
      if (checky != 0)
      {
        if ((prey_maparray0[checky - 1][checkx].attri2 == VALUE_OF_FREE && checky - 1 != -1) && (prey_maparray0[checky - 2][checkx].attri2 == VALUE_OF_FREE && checky - 2 != -1) && (prey_maparray0[checky - 3][checkx].attri2 == VALUE_OF_FREE && checky - 3 != -1) && (prey_maparray0[checky - 4][checkx].attri2 == VALUE_OF_FREE && checky - 4 != -1) && (prey_maparray0[checky - 5][checkx].attri2 == VALUE_OF_FREE && checky - 5 != -1))
        {
          return 'u';
        }
      }
      /*
      ���ǉ���5�}�X�󂢂Ă��牺�ɍs��
      */
      if (checky != 7)
      {
        if ((prey_maparray0[checky + 1][checkx].attri2 == VALUE_OF_FREE && checky + 1 != 8) && (prey_maparray0[checky + 2][checkx].attri2 == VALUE_OF_FREE && checky + 2 != 8) && (prey_maparray0[checky + 3][checkx].attri2 == VALUE_OF_FREE && checky + 3 != 8) && (prey_maparray0[checky + 4][checkx].attri2 == VALUE_OF_FREE && checky + 4 != 8) && (prey_maparray0[checky + 5][checkx].attri2 == VALUE_OF_FREE && checky + 5 != 8))
        {
          return 'd';
        }
      }
      return 'r';
    }
  }

  /*
 prey�ɍs�������O�̈ʒu��prey�̏㑤�������ꍇ
 */
  else if (prey_maparray0[checky][checkx].backpos2.y2 == checky - 1 && prey_maparray0[checky][checkx].backpos2.x2 == checkx)
  {
    /*
    �E���p�ɂ����獶��
    */
    if ((checky == 7 || maparray[checky][checkx + 1] == VALUE_OF_OBSTACLE) && (checkx == 7 || maparray[checky + 1][checkx] == VALUE_OF_OBSTACLE))
    {
      return 'l';
    }
    /*
    �����p�ɂ�����E��
    */
    else if ((checky == 7 || maparray[checky][checkx + 1] == VALUE_OF_OBSTACLE) && (checkx == 0 || maparray[checky - 1][checkx] == VALUE_OF_OBSTACLE))
    {
      return 'r';
    }
    /*
    check�����ʒu�Ƃ��̑O�̈ʒu�Ƃ܂����̑O�̈ʒu����T�����[�g����肵�ē����������Ԃ�
    prey�̍����T�����Ă�����E��
    */
    else if (((checky == 7) || (maparray[checky + 1][checkx] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.y2) == (checky - 1)) && ((prey_maparray0[checky - 1][checkx].backpos2.x2) == (checkx - 1)))
    {
      return 'r';
    }
    /*
    check�����ʒu�Ƃ��̑O�̈ʒu�Ƃ܂����̑O�̈ʒu����T�����[�g����肵�ē����������Ԃ�
    prey�̉E���T�����Ă����獶��
    */
    else if (((checky == 7) || (maparray[checky + 1][checkx] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.y2) == (checky - 1)) && ((prey_maparray0[checky - 1][checkx].backpos2.y2) == (checkx + 1)))
    {
      return 'l';
    }
    /*
    ����ȊO�͂Ƃ肠�������Ɣ���
    */
    else
    {
      /*
      ���ǉE��5�}�X�󂢂Ă���E�ɍs��
      */
      if (checkx != 7)
      {
        if ((maparray[checky][checkx + 1] == VALUE_OF_FREE && checkx + 1 != 8) && (maparray[checky][checkx + 2] == VALUE_OF_FREE && checkx + 2 != 8) && (maparray[checky][checkx + 3] == VALUE_OF_FREE && checkx + 3 != 8) && (maparray[checky][checkx + 4] == VALUE_OF_FREE && checkx + 4 != 8) && (maparray[checky][checkx + 5] == VALUE_OF_FREE && checkx + 5 != 8))
        {
          return 'r';
        }
      }

      /*
      ���Ǎ���5�}�X�󂢂Ă��獶�ɍs��
      */
      if (checkx != 0)
      {
        if ((maparray[checky][checkx - 1] == VALUE_OF_FREE && checkx - 1 != -1) && (maparray[checky][checkx - 2] == VALUE_OF_FREE && checkx - 2 != -1) && (maparray[checky][checkx - 3] == VALUE_OF_FREE && checkx - 3 != -1) && (maparray[checky][checkx - 4] == VALUE_OF_FREE && checkx - 4 != -1) && (maparray[checky][checkx - 5] == VALUE_OF_FREE && checkx - 5 != -1))
        {
          return 'l';
        }
      }
      return 'd';
    }
  }
  return 0;
}

void Prey(int maparray[WORLD_SIZE][WORLD_SIZE], int *action)
{
  *action = prey_strategem(maparray);
}
