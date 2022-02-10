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

/* 格子世界の大きさ */
#ifndef WORLD_SIZE
#define WORLD_SIZE 8
#endif
/* predatorの数値表現 */
#ifndef VALUE_OF_PREDATOR
#define VALUE_OF_PREDATOR 1
#endif
/* preyの数値表現 */
#ifndef VALUE_OF_PREY
#define VALUE_OF_PREY 10
#endif
/* obstacleの数値表現 */
#ifndef VALUE_OF_OBSTACLE
#define VALUE_OF_OBSTACLE -1
#endif
/* free gridの数値表現 */
#ifndef VALUE_OF_FREE
#define VALUE_OF_FREE 0
#endif
/* 探索済みの数値表現 */
#ifndef VALUE_OF_SEARCHED
#define VALUE_OF_SEARCHED 3
#endif
/* もう使用しない数値表現 */
#ifndef VALUE_OF_EXCEPT
#define VALUE_OF_EXCEPT 6
#endif

/*
 *PredatorおよびPreyの位置を表す構造体
 */
typedef struct
{
  int x;
  int y;
} Predator_pursuit_position;

/*
 調べる座標の情報を格納する構造体
*/
typedef struct
{
  Predator_pursuit_position pos;     //現在位置
  Predator_pursuit_position backpos; //一個前の位置
  double cost;                       //コスト
  int attri;                         //状態
} predator_node;

/*
int型で受け取る世界の情報をpredetor_node型へ落とし込むための配列
*/
predator_node predator_maparray0[WORLD_SIZE][WORLD_SIZE];

/*
次に探索する地点の候補を入れるキュー
キューの上限は100
temporarynodeは一時的に値を保存するためのもの
*/
#define SEARCHQUE_LIMIT 100
predator_node *predator_searchque[SEARCHQUE_LIMIT];
predator_node *predator_temporarynode;
int predator_searchque_head;

/*
キューにpushする
プッシュした際にはコストの軽い順に並び変えるようにしている
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
探索リストから候補を取り出す
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
predatorの経路探索処理。A*アルゴリズムを用いている。
*/
int predator_strategem(int maparray[WORLD_SIZE][WORLD_SIZE])
{
  Predator_pursuit_position difpos[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  int i, j, checkx, checky, checkcount, predatorx, preyx, predatory, preyy;
  double cost;
  /*
  探索の現在位置のpredator_node
  */
  predator_node *nowpos;
  /*
  キューの先頭位置を0へ
  */
  predator_searchque_head = 0;

  /*
  int型の世界情報をpreadtor_node型に落とし込むための処理
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
  スタート位置をキューへ
  */
  predator_que_push(&predator_maparray0[preyy][preyx]);

  /*
  探索がpredatorに行くまでループする
  */
  do
  {
    /*
    調べる位置をキューから取り出す
    */
    nowpos = predator_que_pop();

    /*
    4方向調べる
    */
    checkcount = 0;
    for (i = 0; i < 4; i++)
    {
      checkx = nowpos->pos.x + difpos[i].x;
      checky = nowpos->pos.y + difpos[i].y;

      /*
      チェックした位置がワールドの外だったら最初から
      */
      if ((checky < 0) || (checky >= WORLD_SIZE) || (checkx < 0) || (checkx >= WORLD_SIZE))
      {
        continue;
      }

      /*
      predatorだったら抜ける
      */
      if (maparray[checky][checkx] == VALUE_OF_PREDATOR)
      {
        predator_maparray0[checky][checkx].backpos.x = nowpos->pos.x;
        predator_maparray0[checky][checkx].backpos.y = nowpos->pos.y;
        break;
      }

      /*
      壁とか調査済みだったら無視して次の候補へ
      */
      if (maparray[checky][checkx] != VALUE_OF_FREE)
      {
        continue;
      }

      /*
      コストを得る。推定コストなので直線距離
      */
      cost = sqrt(abs((predatorx - checkx)) * abs((predatorx - checkx)) + abs((predatory - checky)) * abs((predatory - checky)));

      /*
      コストを保存し次の調査へ
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
    4方向調べた時点でどこも調べられなかったらそこは今後除外する
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
  A*アルゴリズムで行きついた目標地点の前に調べていた場所から次に進むべき方向を決定する
  */
  /*
 右
 */
  if (predator_maparray0[checky][checkx].backpos.y == checky && predator_maparray0[checky][checkx].backpos.x == checkx + 1)
  {
    return 'r';
  }
  /*
  下
  */
  else if (predator_maparray0[checky][checkx].backpos.y == checky + 1 && predator_maparray0[checky][checkx].backpos.x == checkx)
  {
    return 'd';
  }
  /*
  左
  */
  else if (predator_maparray0[checky][checkx].backpos.y == checky && predator_maparray0[checky][checkx].backpos.x == checkx - 1)
  {
    return 'l';
  }
  /*
  上
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
