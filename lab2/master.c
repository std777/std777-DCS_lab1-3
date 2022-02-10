/*
 * Master Program for Iterative Prisoner's Dilemma Game (for Solaris)
 * version 1.0
 *
 * Authour: Ei-Ichi Osawa
 * Date: November 1, 2002
 * Copyright (c) 2002, Ei-Ichi Osawa, FUN
 *
 */

#define VERSION_1_0 1

/*
 * Load libralies (stdio.h, stdlib.h, time.h)
 *
 */

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif

#ifndef COOPERATION
#define COOPERATION 1
#endif

#ifndef DECEPTION
#define DECEPTION 0
#endif

/*�Q�[����(�f�B�t�H���g�l) */

#ifndef NUM_OF_GAME
#define NUM_OF_GAME 200
#endif

/*�G���[�����肷��臒l�̐ݒ�  */

#ifndef ERROR
#define ERROR 50
#endif

/*
 * �e�v���C���̗����v�Z *�Ԃ�l: �Ȃ� *
 */

void payoff(int strtgy1, int strtgy2, int *payoff1, int *payoff2)
{

  if (strtgy1 == COOPERATION)
  {
    if (strtgy2 == COOPERATION)
    {
      *payoff1 = 3;
      *payoff2 = 3;
    }
    else if (strtgy2 == DECEPTION)
    {
      *payoff1 = 0;
      *payoff2 = 5;
    }
    else
    {
      *payoff1 = 5;
      *payoff2 = 0;
    }
  }
  else if (strtgy1 == DECEPTION)
  {
    if (strtgy2 == COOPERATION)
    {
      *payoff1 = 5;
      *payoff2 = 0;
    }
    else if (strtgy2 == DECEPTION)
    {
      *payoff1 = 1;
      *payoff2 = 1;
    }
    else
    {
      *payoff1 = 5;
      *payoff2 = 0;
    }
  }
  else
  {
    if ((strtgy2 == COOPERATION) ||
        (strtgy2 == DECEPTION))
    {
      *payoff1 = 0;
      *payoff2 = 5;
    }
    else
    {
      *payoff1 = 0;
      *payoff2 = 0;
    }
  }
  return;
}

/*
Game Master �� main �֐� * �Ԃ�l: ����Ȃ� 0, �ȏ�Ȃ� -1
 */

int main(int argc, char *argv[])
{
  int i, random, error_count1 = 0, error_count2 = 0;
  time_t t;
  int score1 = 0, score2 = 0;             /*�e�v���C���̑����_ */
  int payoff1, payoff2;                   /*�e�v���C���̊e��̃Q�[���̓��_ */
  int gameStepNum;                        /*�Q�[���̌��݂̉� */
  int prevStrtgy1 = -1, prevStrtgy2 = -1; /*�e�v���C���̑O��̐헪 */
  int currentStrtgy1, currentStrtgy2;     /*�e�v���C���̍���̐헪 */

  /* �ȉ��̓I�v�V�����w��ɂ��ύX�����\���̂���ϐ� */
  int gameStepNum_Max = NUM_OF_GAME; /* �Q�[���̍ő�X�e�b�v�� */

  /*�W�����͂���̃p�����[�^���� */
  for (i = 1; i < argc; i++)
  {
    /* "-s" �ΐ�񐔃I�v�V�����̏��� */
    if (strcmp(argv[i], "-s") == 0)
    {
      if (i + 1 < argc)
      {
        gameStepNum_Max = atoi(argv[i + 1]);
        if ((gameStepNum_Max > 0) && (gameStepNum_Max <= 10000))
        {
          i++;
        }
        else
        {
          printf("Invalid input value!! Specify one positive number no more than 10000.\n");
          /* �l���Ó��łȂ��ꍇ*/
          return (1);
        }
      }
      else
      {
        /* �I�v�V�����̎��ɓ��̓p�����[�^���Ȃ��ꍇ */
        printf("Option error!! You must specify number of games.\n");
        return (1);
      }
    }
    else
    {
      printf("Invalid option:  available option is:\n");
      printf("-s: Specify number of games. ex: \"-s 200\"\n");
      return (1);
    }
  }

  /* ���ԂɈˑ����������̃V�[�h�̐ݒ� */
  srand((unsigned)time(&t));

  /* �Q�[���X�^�[�g */

  for (gameStepNum = 1; gameStepNum <= gameStepNum_Max; gameStepNum++)
  {

    currentStrtgy1 = -1;
    currentStrtgy2 = -1;

    /* �e�v���C���̐헪����*/
    Player1(prevStrtgy1, prevStrtgy2, &currentStrtgy1);
    Player2(prevStrtgy1, prevStrtgy2, &currentStrtgy2);

    /*�����̔���*/
    random = rand() % 100;

    /*�v���C��1�ɃG���[���N�����ꍇ�͐헪���t�ɂ��� */

    if (random < ERROR)
    {
      error_count1++;

#ifdef DEBUG
      printf("ERROR on p1. step = %d, random = %d\n", gameStepNum, random);
#endif

      if (currentStrtgy1 == 0)
      {
        currentStrtgy1 = 1;
      }
      else if (currentStrtgy1 == 1)
      {
        currentStrtgy1 = 0;
      }
    }

    /*�����̔���*/
    random = rand() % 100;

    /*�v���C��2�ɃG���[���N�����ꍇ�͐헪���t�ɂ��� */

    if (random < ERROR)
    {

      error_count2++;

#ifdef DEBUG
      printf("ERROR on p2. step = %d, random = %d\n", gameStepNum, random);
#endif

      if (currentStrtgy2 == 0)
      {
        currentStrtgy2 = 1;
      }
      else if (currentStrtgy2 == 1)
      {
        currentStrtgy2 = 0;
      }
    }

#ifdef DEBUG
    printf("p1: %d, p2: %d\n", currentStrtgy1, currentStrtgy2);
#endif

    prevStrtgy1 = currentStrtgy1;
    prevStrtgy2 = currentStrtgy2;

    /*���v���C���̍���̐헪�̗����Ƒ����_�̌v�Z */
    payoff(currentStrtgy1, currentStrtgy2, &payoff1, &payoff2);

    score1 = score1 + payoff1;
    score2 = score2 + payoff2;
  }

  /*�Q�[���̏I�����̑����_�̕\�� */
  printf("Game Over!! Player1 score: %d, Player2 score: %d\n", score1, score2);

  //#ifdef DEBUG

  printf("p1 error: %d, ratio: %f\n", error_count1, ((float)error_count1) / ((float)gameStepNum_Max));
  printf("p2 error: %d, ratio: %f\n", error_count2, ((float)error_count2) / ((float)gameStepNum_Max));

  //#endif
  return (0);
}
