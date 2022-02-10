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
  int x2;
  int y2;
} Prey_pursuit_position;

/*
 調べる座標の情報を格納する構造体
*/
typedef struct
{
  Prey_pursuit_position pos2;     //現在位置
  Prey_pursuit_position backpos2; //一個前の位置
  double cost2;                   //コスト
  int attri2;                     //状態
} prey_node;

/*
int型で受け取る世界の情報をpredetor_node型へ落とし込むための配列
*/
prey_node prey_maparray0[WORLD_SIZE][WORLD_SIZE];

/*
次に探索する地点の候補を入れるキュー
キューの上限は100
temporarynodeは一時的に値を保存するためのもの
*/
#define SEARCHQUE_LIMIT 100
prey_node *prey_searchque[SEARCHQUE_LIMIT];
prey_node *prey_temporarynode;
int prey_searchque_head;

/*
キューにpushする
プッシュした際にはコストの軽い順に並び変えるようにしている
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
探索リストから候補を取り出す
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
predatorの経路探索処理。A*アルゴリズムを用いている。
*/
int prey_strategem(int maparray[WORLD_SIZE][WORLD_SIZE])
{
  Prey_pursuit_position difpos[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  int i, j, checkx, checky, checkcount, predatorx, preyx, predatory, preyy;
  double cost;
  /*
  探索する現在位置のprey_node
  */
  prey_node *nowpos;
  /*
  キューの先頭位置を0へ
  */
  prey_searchque_head = 0;

  /*
  int型の世界情報をpreadtor_node型に落とし込むための処理
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
  スタート位置をキューへ
  */
  prey_que_push(&prey_maparray0[predatory][predatorx]);
  /*
  探索がpredatorに行くまでループする
  */
  do
  {
    /*
    調べる位置をキューから取り出す
    */
    nowpos = prey_que_pop();
    /*
    4方向調べる
    */
    checkcount = 0;

    for (i = 0; i < 4; i++)
    {
      checkx = nowpos->pos2.x2 + difpos[i].x2;
      checky = nowpos->pos2.y2 + difpos[i].y2;

      /*
      チェックした位置がワールドの外だったら最初から
      */
      if ((checky < 0) || (checky >= WORLD_SIZE) || (checkx < 0) || (checkx >= WORLD_SIZE))
      {
        continue;
      }

      /*
      preyだったら抜ける
      */
      if (maparray[checky][checkx] == VALUE_OF_PREY)
      {
        prey_maparray0[checky][checkx].backpos2.x2 = nowpos->pos2.x2;
        prey_maparray0[checky][checkx].backpos2.y2 = nowpos->pos2.y2;
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
      cost = sqrt(abs((preyx - checkx)) * abs((preyx - checkx)) + abs((preyy - checky)) * abs((preyy - checky)));

      /*
      コストを保存し次の調査へ
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
    4方向調べた時点でどこも調べられなかったらそこは今後除外する
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
  A*アルゴリズムで行きついた目標地点の前に調べていた場所から次に進むべき方向を決定する
  */
  /*
 preyに行きつく直前の位置がpreyの右側だった場合
 */
  if (prey_maparray0[checky][checkx].backpos2.y2 == checky && prey_maparray0[checky][checkx].backpos2.x2 == checkx + 1)
  {
    /*
    左下角にいたら上へ
    */
    if ((checky == 7 || maparray[checky + 1][checkx] == VALUE_OF_OBSTACLE) && (checkx == 0 || maparray[checky][checkx - 1] == VALUE_OF_OBSTACLE))
    {
      return 'u';
    }
    /*
    左上角にいたら下へ
    */
    else if ((checky == 0 || maparray[checky - 1][checkx] == VALUE_OF_OBSTACLE) && (checkx == 0 || maparray[checky][checkx - 1] == VALUE_OF_OBSTACLE))
    {
      return 'd';
    }
    /*
    checkした位置とその前の位置とまたその前の位置から探索ルートを特定して逃げる方向を返す
    preyの右上を探索していたら下へ
    */
    else if (((checkx == 0) || (maparray[checky][checkx - 1] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.x2) == (checkx + 1)) && ((prey_maparray0[checky][checkx + 1].backpos2.y2) == (checky - 1)))
    {
      return 'd';
    }
    /*
    checkした位置とその前の位置とまたその前の位置から探索ルートを特定して逃げる方向を返す
    preyの右下を探索していたら上へ
    */
    else if (((checkx == 0) || (maparray[checky][checkx - 1] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.x2) == (checkx + 1)) && ((prey_maparray0[checky][checkx + 1].backpos2.y2) == (checky + 1)))
    {
      return 'u';
    }
    /*
    それ以外はとりあえず左と判定
    */
    else
    {
      /*
      けど上が5マス空いてたら上に行く
      */
      if (checky != 0)
      {
        if ((prey_maparray0[checky - 1][checkx].attri2 == VALUE_OF_FREE && checky - 1 != -1) && (prey_maparray0[checky - 2][checkx].attri2 == VALUE_OF_FREE && checky - 2 != -1) && (prey_maparray0[checky - 3][checkx].attri2 == VALUE_OF_FREE && checky - 3 != -1) && (prey_maparray0[checky - 4][checkx].attri2 == VALUE_OF_FREE && checky - 4 != -1) && (prey_maparray0[checky - 5][checkx].attri2 == VALUE_OF_FREE && checky - 5 != -1))
        {
          return 'u';
        }
      }
      /*
      けど下が5マス空いてたら下に行く
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
 preyに行きつく直前の位置がpreyの下側だった場合
 */
  else if (prey_maparray0[checky][checkx].backpos2.y2 == checky + 1 && prey_maparray0[checky][checkx].backpos2.x2 == checkx)
  {
    /*
    右上角にいたら左へ
    */
    if ((checky == 0 || maparray[checky][checkx + 1] == VALUE_OF_OBSTACLE) && (checkx == 7 || maparray[checky + 1][checkx] == VALUE_OF_OBSTACLE))
    {
      return 'l';
    }
    /*
    左上角にいたら右へ
    */
    else if ((checky == 0 || maparray[checky][checkx - 1] == VALUE_OF_OBSTACLE) && (checkx == 0 || maparray[checky - 1][checkx] == VALUE_OF_OBSTACLE))
    {
      return 'r';
    }
    /*
    checkした位置とその前の位置とまたその前の位置から探索ルートを特定して逃げる方向を返す
    preyの左下を探索していたら右へ
    */
    else if (((checky == 0) || (maparray[checky - 1][checkx] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.y2) == (checky + 1)) && ((prey_maparray0[checky + 1][checkx].backpos2.x2) == (checkx + 1)))
    {
      return 'r';
    }
    /*
    checkした位置とその前の位置とまたその前の位置から探索ルートを特定して逃げる方向を返す
    preyの右下を探索していたら左へ
    */
    else if (((checky == 0) || (maparray[checky - 1][checkx] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.y2) == (checky + 1)) && ((prey_maparray0[checky + 1][checkx].backpos2.x2) == (checkx - 1)))
    {
      return 'l';
    }
    /*
    それ以外はとりあえず上と判定
    */
    else
    {
      /*
      けど右が5マス空いてたら右に行く
      */
      if (checkx != 7)
      {
        if ((prey_maparray0[checky][checkx + 1].attri2 == VALUE_OF_FREE && checkx + 1 != 8) && (prey_maparray0[checky][checkx + 2].attri2 == VALUE_OF_FREE && checkx + 2 != 8) && (prey_maparray0[checky][checkx + 3].attri2 == VALUE_OF_FREE && checkx + 3 != 8) && (prey_maparray0[checky][checkx + 4].attri2 == VALUE_OF_FREE && checkx + 4 != 8) && (prey_maparray0[checky][checkx + 5].attri2 == VALUE_OF_FREE && checkx + 5 != 8))
        {
          return 'r';
        }
      }

      /*
      けど左が5マス空いてたら左に行く
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
 preyに行きつく直前の位置がpreyの左側だった場合
 */
  else if (prey_maparray0[checky][checkx].backpos2.y2 == checky && prey_maparray0[checky][checkx].backpos2.x2 == checkx - 1)
  {
    /*
    右下角にいたら上へ
    */
    if ((checky == 7 || maparray[checky + 1][checkx] == VALUE_OF_OBSTACLE) && (checkx == 7 || maparray[checky][checkx + 1] == VALUE_OF_OBSTACLE))
    {
      return 'u';
    }
    /*
    右上角にいたら下へ
    */
    else if ((checky == 0 || maparray[checky - 1][checkx] == VALUE_OF_OBSTACLE) && (checkx == 7 || maparray[checky][checkx + 1] == VALUE_OF_OBSTACLE))
    {
      return 'd';
    }
    /*
    checkした位置とその前の位置とまたその前の位置から探索ルートを特定して逃げる方向を返す
    preyの左下を探索していたら上へ
    */
    else if (((checkx == 7) || (maparray[checky][checkx + 1] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.x2) == (checkx - 1)) && ((prey_maparray0[checky][checkx - 1].backpos2.y2) == (checky + 1)))
    {
      return 'u';
    }
    /*
    checkした位置とその前の位置とまたその前の位置から探索ルートを特定して逃げる方向を返す
    preyの左上を探索していたら下へ
    */
    else if (((checkx == 7) || (maparray[checky][checkx + 1] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.x2) == (checkx - 1)) && ((prey_maparray0[checky][checkx - 1].backpos2.y2) == (checky - 1)))
    {
      return 'd';
    }
    /*
    それ以外はとりあえず右と判定
    */
    else
    {
      /*
      けど上が5マス空いてたら上に行く
      */
      if (checky != 0)
      {
        if ((prey_maparray0[checky - 1][checkx].attri2 == VALUE_OF_FREE && checky - 1 != -1) && (prey_maparray0[checky - 2][checkx].attri2 == VALUE_OF_FREE && checky - 2 != -1) && (prey_maparray0[checky - 3][checkx].attri2 == VALUE_OF_FREE && checky - 3 != -1) && (prey_maparray0[checky - 4][checkx].attri2 == VALUE_OF_FREE && checky - 4 != -1) && (prey_maparray0[checky - 5][checkx].attri2 == VALUE_OF_FREE && checky - 5 != -1))
        {
          return 'u';
        }
      }
      /*
      けど下が5マス空いてたら下に行く
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
 preyに行きつく直前の位置がpreyの上側だった場合
 */
  else if (prey_maparray0[checky][checkx].backpos2.y2 == checky - 1 && prey_maparray0[checky][checkx].backpos2.x2 == checkx)
  {
    /*
    右下角にいたら左へ
    */
    if ((checky == 7 || maparray[checky][checkx + 1] == VALUE_OF_OBSTACLE) && (checkx == 7 || maparray[checky + 1][checkx] == VALUE_OF_OBSTACLE))
    {
      return 'l';
    }
    /*
    左下角にいたら右へ
    */
    else if ((checky == 7 || maparray[checky][checkx + 1] == VALUE_OF_OBSTACLE) && (checkx == 0 || maparray[checky - 1][checkx] == VALUE_OF_OBSTACLE))
    {
      return 'r';
    }
    /*
    checkした位置とその前の位置とまたその前の位置から探索ルートを特定して逃げる方向を返す
    preyの左上を探索していたら右へ
    */
    else if (((checky == 7) || (maparray[checky + 1][checkx] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.y2) == (checky - 1)) && ((prey_maparray0[checky - 1][checkx].backpos2.x2) == (checkx - 1)))
    {
      return 'r';
    }
    /*
    checkした位置とその前の位置とまたその前の位置から探索ルートを特定して逃げる方向を返す
    preyの右上を探索していたら左へ
    */
    else if (((checky == 7) || (maparray[checky + 1][checkx] == VALUE_OF_OBSTACLE)) && ((prey_maparray0[checky][checkx].backpos2.y2) == (checky - 1)) && ((prey_maparray0[checky - 1][checkx].backpos2.y2) == (checkx + 1)))
    {
      return 'l';
    }
    /*
    それ以外はとりあえず下と判定
    */
    else
    {
      /*
      けど右が5マス空いてたら右に行く
      */
      if (checkx != 7)
      {
        if ((maparray[checky][checkx + 1] == VALUE_OF_FREE && checkx + 1 != 8) && (maparray[checky][checkx + 2] == VALUE_OF_FREE && checkx + 2 != 8) && (maparray[checky][checkx + 3] == VALUE_OF_FREE && checkx + 3 != 8) && (maparray[checky][checkx + 4] == VALUE_OF_FREE && checkx + 4 != 8) && (maparray[checky][checkx + 5] == VALUE_OF_FREE && checkx + 5 != 8))
        {
          return 'r';
        }
      }

      /*
      けど左が5マス空いてたら左に行く
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
