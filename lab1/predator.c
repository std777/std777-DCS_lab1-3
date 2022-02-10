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
  int x;
  int y;
} Predator_pursuit_position;

/*
 ���ׂ���W�̏����i�[����\����
*/
typedef struct
{
  Predator_pursuit_position pos;     //���݈ʒu
  Predator_pursuit_position backpos; //��O�̈ʒu
  double cost;                       //�R�X�g
  int attri;                         //���
} predator_node;

/*
int�^�Ŏ󂯎�鐢�E�̏���predetor_node�^�֗��Ƃ����ނ��߂̔z��
*/
predator_node predator_maparray0[WORLD_SIZE][WORLD_SIZE];

/*
���ɒT������n�_�̌�������L���[
�L���[�̏����100
temporarynode�͈ꎞ�I�ɒl��ۑ����邽�߂̂���
*/
#define SEARCHQUE_LIMIT 100
predator_node *predator_searchque[SEARCHQUE_LIMIT];
predator_node *predator_temporarynode;
int predator_searchque_head;

/*
�L���[��push����
�v�b�V�������ۂɂ̓R�X�g�̌y�����ɕ��ѕς���悤�ɂ��Ă���
*/
void predator_que_push(predator_node *node)
{
  int i, j;

  if (predator_searchque_head >= SEARCHQUE_LIMIT)
  {
    return;
  }
  predator_searchque[predator_searchque_head] = node;
  predator_searchque_head++;

  if (predator_searchque_head <= 1)
  {
    return;
  }

  for (i = 0; i < predator_searchque_head; i++)
  {
    for (j = 1; j < predator_searchque_head - i; j++)
    {
      if (predator_searchque[j - 1]->cost < predator_searchque[j]->cost)
      {
        predator_temporarynode = predator_searchque[j - 1];
        predator_searchque[j - 1] = predator_searchque[j];
        predator_searchque[j] = predator_temporarynode;
      }
    }
  }
}

/*
�T�����X�g����������o��
*/
predator_node *predator_que_pop(void)
{
  if (predator_searchque_head == 0)
  {
    return NULL;
  }
  predator_searchque_head--;
  return predator_searchque[predator_searchque_head];
}

/*
predator�̌o�H�T�������BA*�A���S���Y����p���Ă���B
*/
int predator_strategem(int maparray[WORLD_SIZE][WORLD_SIZE])
{
  Predator_pursuit_position difpos[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  int i, j, checkx, checky, checkcount, predatorx, preyx, predatory, preyy;
  double cost;
  /*
  �T���̌��݈ʒu��predator_node
  */
  predator_node *nowpos;
  /*
  �L���[�̐擪�ʒu��0��
  */
  predator_searchque_head = 0;

  /*
  int�^�̐��E����preadtor_node�^�ɗ��Ƃ����ނ��߂̏���
  */
  for (i = 0; i < WORLD_SIZE; i++)
  {
    for (j = 0; j < WORLD_SIZE; j++)
    {
      if (maparray[i][j] == VALUE_OF_OBSTACLE)
      {
        predator_maparray0[i][j].attri = VALUE_OF_OBSTACLE;
        predator_maparray0[i][j].pos.x = j;
        predator_maparray0[i][j].pos.y = i;
      }

      if (maparray[i][j] == VALUE_OF_FREE)
      {
        predator_maparray0[i][j].attri = VALUE_OF_FREE;
        predator_maparray0[i][j].pos.x = j;
        predator_maparray0[i][j].pos.y = i;
      }

      if (maparray[i][j] == VALUE_OF_PREDATOR)
      {
        predatorx = j;
        predatory = i;
        predator_maparray0[i][j].attri = VALUE_OF_PREDATOR;
        predator_maparray0[i][j].pos.x = j;
        predator_maparray0[i][j].pos.y = i;
      }

      if (maparray[i][j] == VALUE_OF_PREY)
      {
        preyx = j;
        preyy = i;
        predator_maparray0[i][j].attri = VALUE_OF_PREY;
        predator_maparray0[i][j].pos.x = j;
        predator_maparray0[i][j].pos.y = i;
      }
    }
  }

  /*
  �X�^�[�g�ʒu���L���[��
  */
  predator_que_push(&predator_maparray0[preyy][preyx]);

  /*
  �T����predator�ɍs���܂Ń��[�v����
  */
  do
  {
    /*
    ���ׂ�ʒu���L���[������o��
    */
    nowpos = predator_que_pop();

    /*
    4�������ׂ�
    */
    checkcount = 0;
    for (i = 0; i < 4; i++)
    {
      checkx = nowpos->pos.x + difpos[i].x;
      checky = nowpos->pos.y + difpos[i].y;

      /*
      �`�F�b�N�����ʒu�����[���h�̊O��������ŏ�����
      */
      if ((checky < 0) || (checky >= WORLD_SIZE) || (checkx < 0) || (checkx >= WORLD_SIZE))
      {
        continue;
      }

      /*
      predator�������甲����
      */
      if (maparray[checky][checkx] == VALUE_OF_PREDATOR)
      {
        predator_maparray0[checky][checkx].backpos.x = nowpos->pos.x;
        predator_maparray0[checky][checkx].backpos.y = nowpos->pos.y;
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
      cost = sqrt(abs((predatorx - checkx)) * abs((predatorx - checkx)) + abs((predatory - checky)) * abs((predatory - checky)));

      /*
      �R�X�g��ۑ������̒�����
      */
      maparray[checky][checkx] = VALUE_OF_SEARCHED;
      predator_maparray0[checky][checkx].attri = VALUE_OF_SEARCHED;
      predator_maparray0[checky][checkx].cost = cost;
      predator_maparray0[checky][checkx].backpos.x = nowpos->pos.x;
      predator_maparray0[checky][checkx].backpos.y = nowpos->pos.y;
      predator_que_push(&predator_maparray0[checky][checkx]);
      checkcount++;
    }
    /*
    4�������ׂ����_�łǂ������ׂ��Ȃ������炻���͍��㏜�O����
    */
    if ((!checkcount) && (nowpos->attri == VALUE_OF_SEARCHED))
    {
      nowpos->attri = VALUE_OF_EXCEPT;
    }
    if (nowpos->attri == VALUE_OF_FREE)
    {
      nowpos->attri = VALUE_OF_SEARCHED;
    }
  } while (maparray[checky][checkx] != VALUE_OF_PREDATOR);
  /*
  A*�A���S���Y���ōs�������ڕW�n�_�̑O�ɒ��ׂĂ����ꏊ���玟�ɐi�ނׂ����������肷��
  */
  /*
 �E
 */
  if (predator_maparray0[checky][checkx].backpos.y == checky && predator_maparray0[checky][checkx].backpos.x == checkx + 1)
  {
    return 'r';
  }
  /*
  ��
  */
  else if (predator_maparray0[checky][checkx].backpos.y == checky + 1 && predator_maparray0[checky][checkx].backpos.x == checkx)
  {
    return 'd';
  }
  /*
  ��
  */
  else if (predator_maparray0[checky][checkx].backpos.y == checky && predator_maparray0[checky][checkx].backpos.x == checkx - 1)
  {
    return 'l';
  }
  /*
  ��
  */
  else if (predator_maparray0[checky][checkx].backpos.y == checky - 1 && predator_maparray0[checky][checkx].backpos.x == checkx)
  {
    return 'u';
  }
  return 0;
}

void Predator(int maparray[WORLD_SIZE][WORLD_SIZE], int *action)
{
  *action = predator_strategem(maparray);
}
