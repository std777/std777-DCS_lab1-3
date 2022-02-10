/*
 * 2 Players Pursuit Game �����ץ����
 * version 1.2 SP2
 *
 * by E. Osawa and E. Yoshikawa, Sept 2002.
 * 
 * last revision by E. Osawa Oct. 2002
 *
 * (�ѹ�����)
 * 2002.10.1            �㳲ʪ,��ͳ�ʻ�,�Ῡ��,��ʪ��ɽ�������Ƴ��
 *
 * 2000.12.26(1.2.1)    �������ɲ�
 *                      thread����󥻥����segmentation fault�β��
 * 2000.12.25(1.2)      watch dog timer���ɲá�
 *                      Prey��Predator�μ¹Ի��֤�1�ä��ƻ뤹�롥
 * 2000.12.20(1.1 SP2): ���ץ����˴ؤ��륨�顼�����򶯲���
 *                      ����ͤ���ꤹ���̵�¥롼�פ˴٤븽�ݤ䡢
 *                      ���ץ����Τߤ����ꤵ��Ƥ⥨�顼��Ф��ʤ����ݡ�
 *                      ̤����Υ��ץ������Ф��ƥ��顼��Ф��ʤ����ݤʤɤ�
 *                      ����
 *
 * 2000.12.20(1.1 SP1): Prey��Predator�η׻���ͭ���֤ˤ�äơ�ɽ���ι�����
 *                      ����Ĥ����ݤ����
 *                      �ǥե���Ȥγʻ������ե������"battlefield.txt"����
 *                      "battlefield.dat"���ѹ�
 * 
 * 2000.12.20(1.1)    : ɽ���κݤˤ���륦������(�Υǥե����)��0.5�ä�Ĵ��
 *                      �����ॹ�ƥå׿�(�Υǥե����)��30���ѹ�
 *                      �����ॹ�ƥå׿���"-s 30",�������Ȥ��礭����
 *                      "-t 500000",�ޤ�������ǡ�������Ǽ����Ƥ���
 *                      "-w battlefield2.txt"�Τ褦�ˡ��¹ԥե�������Ф���
 *                      ���ץ����Ȥ���runtime���ɤ߹����褦���ѹ�
 *                      Predator��Prey�ξ��Ԥ˴ؤ����å�����ɽ�����ɲ�
 * 
 * 2000.12.19(1.0 SP2): ��¤��̾��position��pursuit_position���ѹ�
 *                      Prey�����Predator���Ϥ��ʻ������������,
 *                      ���Τ�Τλ����Ϥ������ԡ��λ����Ϥ����ѹ�
 *                      (Predator��Prey���ʻ�������񤭴����뤳�Ȥ��ɤ�����)
 *                      Prey����3��Τ�����2�����ư����פȤ������ͤβ���
 *                      �ѹ�����ư�����Ψ66��פȤ�����ΨŪ�ʵ�ư����
 *                     ��2��ư����1��٤�פȤ�������Ū�ʵ�ư��
 *
 * 2000.12.15(1.0 SP1): ���ͤ˹��פ��Ƥ��ʤ��������
 *                      (����νĤȲ�����ž���Ƥ����Τ���)
 */


#define VERSION_1_2 1

/*
 * ɬ�פʥ饤�֥��Υ���
 * (stdio.h�����stdlib.h)
 */
#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

#ifdef VERSION_1_2
#ifndef PTHREAD_H
#include <pthread.h>
#endif /* PTHREAD_H */
#endif /* VERSION_1_2 */

/* predator�ο���ɽ�� */
#ifndef VALUE_OF_PREDATOR
#define VALUE_OF_PREDATOR 1
#endif

/* prey�ο���ɽ�� */
#ifndef VALUE_OF_PREY
#define VALUE_OF_PREY 10
#endif

/* obstacle�ο���ɽ�� */
#ifndef VALUE_OF_OBSTACLE
#define VALUE_OF_OBSTACLE -1
#endif

/* free grid�ο���ɽ�� */
#ifndef VALUE_OF_FREE
#define VALUE_OF_FREE 0
#endif

/* �ʻ��������礭�� */
#ifndef WORLD_SIZE
#define WORLD_SIZE 8
#endif
 
/* �����֤����ƥå׿�(�ǥե������) */
#ifndef GAME_NUM
#define GAME_NUM 30
#endif

/* VALID(�����Ǥ���) */
#ifndef VALID
#define VALID 1
#endif

/* INVALID(�����Ǥʤ�) */
#ifndef INVALID
#define INVALID 0
#endif

/* �ʻ������ե�����̾�κ���ʸ���� */
#ifndef WORLD_FILE_NAME_LENGTH
#define WORLD_FILE_NAME_LENGTH 256
#endif

/* ɽ���Υ�������(�ǥե������) */
#ifdef VERSION_1_2
#ifndef DISPLAY_WAIT
#define DISPLAY_WAIT 0
#endif
#else /* VERSION_1_2 */
#ifndef DISPLAY_WAIT
#define DISPLAY_WAIT 500000
#endif
#endif /* VERSION_1_2 */

/*
 *Predator�����Prey�ΰ��֤�ɽ����¤��
 */
typedef struct{
  int x;
  int y;
} pursuit_position;


#ifdef VERSION_1_2

/* 
 * watch dog timer�Ѥι���
 */
typedef struct{
  pthread_mutex_t mutex; /* ��¾������ */
  int count;             /* watch dog timer */
  int state;             /* watch dog state */
}watchdog_t;

static watchdog_t wdtimer =
{
  PTHREAD_MUTEX_INITIALIZER,
  0,
  0
};

#define WATCHDOG_COUNT_INIT  1
#define WATCHDOG_INTERVAL 1000000 /* usec */

#define WATCHDOG_RUN           1 /* WD status */
#define WATCHDOG_STOP          0 /* WD status */

pthread_t wd_tid;     /* Watch dog ����åɤ�thread ID */
pthread_t player_tid; /* Prey/Predator ����åɤ�thread ID */

#endif /* VERSION_1_2 */


/*
 * ������֥ǡ����ե�������ɤ߹���
 * int battleFieldArray[WORLD_SIZE][WORLD_SIZE]
 *      : �ʻ�������ɽ��WORLD_SIZE*WORLD_SIZE��������2��������
 * char *fileName: �ʻ������ե�����̾����Ǽ���줿ʸ����
 * �֤���:���ｪλ�ʤ�0,�۾ｪλ�ʤ�1
 */
int ReadInitConf(int battleFieldArray[WORLD_SIZE][WORLD_SIZE], char *fileName){
  FILE *fp;
  int i, j;

  fp = fopen(fileName, "r");
  if (fp == NULL){
    /* �ե����륪���ץ󥨥顼 */
    return(1);
  }
  else{
    for (i = 0; i < WORLD_SIZE; i++){
      for (j = 0; j < WORLD_SIZE; j++){

	if (EOF == fscanf(fp,"%d", &battleFieldArray[i][j])){
	  /* �ե������Ĺ�������ꤷ�Ƥ�������û�����顼 */
	  return(1);
	}

      }
    }

    fclose(fp);
    return(0);
  }
}

/*
 * �ʻ�������ɽ������ؿ�
 * int battleFieldArray[WORLD_SIZE][WORLD_SIZE]
 *      : �ʻ�������ɽ��WORLD_SIZE*WORLD_SIZE��������2��������
 * int clockNum: ���ߤΥ���å���
 * �֤���:���ｪλ�ʤ�0,�۾ｪλ�ʤ�1
 */
int PrintWorld(int battleFieldArray[WORLD_SIZE][WORLD_SIZE], int clockNum){
  int i, j;

  printf("clock %d\n", clockNum);
  for (i = 0; i < WORLD_SIZE; i++){
    for (j = 0; j < WORLD_SIZE; j++){

      switch(battleFieldArray[i][j]){
      case VALUE_OF_OBSTACLE: /* �㳲ʪ */
	printf ("#");
	break;
      case VALUE_OF_FREE: /* ��ͳ�ʻ� */
	printf(".");
	break;
      case VALUE_OF_PREDATOR: /* Predator */
	printf("@");
	break;
      case VALUE_OF_PREY: /* Prey */
	printf("*");
	break;
      default: /* �����ˤ�������ã���ʤ��Ϥ� */
	fprintf(stderr, "%d\n",battleFieldArray[i][j]);
	fprintf(stderr, "Execution Error!! \n");
	return(1);
	break;
      }
    }
    printf("\n");
  }
  printf("\n");
  return(0);
}

/*
 * Predator�ΰ��ֺ�ɸ���������
 * int battleFieldArray[WORLD_SIZE][WORLD_SIZE]
 *      : �ʻ�������ɽ��WORLD_SIZE*WORLD_SIZE��������2��������
 * �֤���:Predator�ΰ��ֺ�ɸ��ɽ��pursuit_position��¤��
 */
pursuit_position getPredatorPosition
(int battleFieldArray[WORLD_SIZE][WORLD_SIZE]){
  
  int i,j;
  pursuit_position returnPosition;

  /*
   * battleFieldArray�Τʤ��ǡ��ͤ�VALUE_OF_PREDATOR�ˤʤäƤ���Ȥ����
   * õ���ơ����κ�ɸ��returnPosition����������return����
   */
  for (i=0; i<WORLD_SIZE; i++){
    for (j=0; j<WORLD_SIZE; j++){
      if (battleFieldArray[i][j] == VALUE_OF_PREDATOR){
	returnPosition.x=j;
	returnPosition.y=i;
	return returnPosition;
      }
    }
  }

  /*
   * �����ޤǽ��������Ȥ������Ȥϰ۾���֤ʤΤǡ�position�Ȥ���
   * (-1,-1)���֤�
   */
  returnPosition.x=-1;
  returnPosition.y=-1;
  return returnPosition;
}

/*
 * Prey�ΰ��ֺ�ɸ���������
 * int battleFieldArray[WORLD_SIZE][WORLD_SIZE]
 *      : �ʻ�������ɽ��WORLD_SIZE*WORLD_SIZE��������2��������
 * �֤���:Prey�ΰ��ֺ�ɸ��ɽ��pursuit_position��¤��
 */
pursuit_position getPreyPosition
(int battleFieldArray[WORLD_SIZE][WORLD_SIZE]){
  
  int i,j;
  pursuit_position returnPosition;
  /*
   * battleFieldArray�Τʤ��ǡ��ͤ�VALUE_OF_PREY�ˤʤäƤ���Ȥ����
   * õ���ơ����κ�ɸ��returnPosition����������return����
   */
  for (i=0; i<WORLD_SIZE; i++){
    for (j=0; j<WORLD_SIZE; j++){
      if (battleFieldArray[i][j] == VALUE_OF_PREY){
	returnPosition.x=j;
	returnPosition.y=i;
	return returnPosition;
      }
    }
  }

  /*
   * �����ޤǽ��������Ȥ������Ȥϰ۾���֤ʤΤǡ�position�Ȥ���
   * (-1,-1)���֤�
   */
  returnPosition.x=-1;
  returnPosition.y=-1;
  return returnPosition;

}

/*
 * ���ꤵ�줿action�˽��äơ���ɸ�򹹿�����
 * pursuit_position currentPosition: 
 * Predator�ޤ���Prey�ΰ��ֺ�ɸ��ɽ��pursuit_position��¤��
 * int action: ���ι�ư��ɽ��ʸ��(��int����ɽ�������)
 * 'u','d','l','r','s'�Τɤ줫
 * �֤���:�������줿���ֺ�ɸ��ɽ��position��¤��
 */
pursuit_position movePP(pursuit_position currentPosition, int action){
  switch(action){
  case 'u': /* ��˰�ư */
    currentPosition.y=currentPosition.y-1;
    break;
  case 'd': /* ���˰�ư */
    currentPosition.y=currentPosition.y+1;
    break;
  case 'l': /* ���˰�ư */
    currentPosition.x=currentPosition.x-1;
    break;
  case 'r': /* ���˰�ư */
    currentPosition.x=currentPosition.x+1;
    break;
  case 's': /* ���ξ��α�ޤ� */
    break;
  default:  /* ���곰��ʸ������ꤷ������'s'�������Ȥߤʤ� */
    break;
  }

  return (currentPosition);

}

/*
 * ��ư������ɸ����������Ƥ����
 * pursuit_position currentPosition: 
 * Predator�ޤ���Prey�ΰ��ֺ�ɸ��ɽ��pursuit_position��¤��
 * int battleFieldArray[WORLD_SIZE][WORLD_SIZE]
 *      : �ʻ�������ɽ��WORLD_SIZE*WORLD_SIZE��������2��������
 * �֤���: �����ʤ��VALID(=1),�����Ǥʤ����INVALID(=0)
 */
int evalPosition(pursuit_position currentPosition, 
		 int battleFieldArray[WORLD_SIZE][WORLD_SIZE]){
  
  /* 
   * ������Ĵ�٤Ƥ���Τ�,
   *   1. ���ꤵ�줿���֤���WORLD_SIZE*WORLD_SIZE�γʻ���������Ϥ߽Ф���
   *      ���ʤ����ɤ���
   *   2. ���ꤵ�줿���֤˾㳲ʪ��¸�ߤ��Ƥ��ʤ����ɤ���
   */
  if (currentPosition.x >=0 && currentPosition.x < WORLD_SIZE
      && currentPosition.y >= 0 && currentPosition.y < WORLD_SIZE
      && battleFieldArray[currentPosition.y][currentPosition.x] != -1){
    return VALID;
  }
  else{
    return INVALID;
  }

}

/*
 * �ʻ������򹹿�����
 * int battleFieldArray[WORLD_SIZE][WORLD_SIZE]
 *      : �ʻ�������ɽ��WORLD_SIZE*WORLD_SIZE��������2��������
 * int predatorAction: Predator�ι�ư��ɽ��ʸ��(��int��ɽ�������)
 * ('u','d','l','r','s'�Τɤ줫)
 * int preyAction: prey�ι�ư��ɽ��ʸ��(��int��ɽ�������)
 * ('u','d','l','r','s'�Τɤ줫)
 * �֤���: �ʻ����������η��Prey����ͤ�����1�������Ǥʤ����0
 */
int RenewWorld(int battleFieldArray[WORLD_SIZE][WORLD_SIZE],
	       int predatorAction, int preyAction){

  /* Predator��Prey�ΰ��ֺ�ɸ��ɽ��position��¤�� */
  pursuit_position predatorPosition, preyPosition;
  pursuit_position newPredatorPosition, newPreyPosition;

  /* Predator��Prey�θ��߰��֤����� */
  predatorPosition = getPredatorPosition(battleFieldArray);
  preyPosition = getPreyPosition(battleFieldArray);

  /* ��ư���Predator��Prey�κ�ɸ������ */
  newPredatorPosition = movePP(predatorPosition, predatorAction);
  newPreyPosition = movePP(preyPosition, preyAction);

  /* battleFieldArray�����öPredator��Prey���� */
  battleFieldArray[predatorPosition.y][predatorPosition.x] = 0;  
  battleFieldArray[preyPosition.y][preyPosition.x] = 0;

  /* �⤷��ư��κ�ɸ�ͤ������ʤ�� */
  if (evalPosition(newPredatorPosition,battleFieldArray) == VALID){
    /* ��������ɸ��predatorPosition�˥��ԡ� */
    predatorPosition.x = newPredatorPosition.x;
    predatorPosition.y = newPredatorPosition.y;    
  }

  /* �⤷��ư��κ�ɸ�ͤ������ʤ�� */
  if (evalPosition(newPreyPosition,battleFieldArray) == VALID){
    /* ��������ɸ��preyPosition�˥��ԡ� */    
    preyPosition.x = newPreyPosition.x;
    preyPosition.y = newPreyPosition.y;
  }

  /*
   * Prey(=VALUE_OF_PREY)��Predator(=VALUE_OF_PREDATOR)������֤��� 
   * ���ν��֤ʤΤϡ�Predator��Prey�˾�񤭤����ΤϤ�����������
   */
  battleFieldArray[preyPosition.y][preyPosition.x] = VALUE_OF_PREY;
  battleFieldArray[predatorPosition.y][predatorPosition.x] = VALUE_OF_PREDATOR;

  /* ��λȽ�� */
  if (predatorPosition.x == preyPosition.x 
      && predatorPosition.y == preyPosition.y){
    return(1);
  }
  else{
    return(0);
  }

}

/*
 * �ʻ������Υ��ԡ���Ԥ�
 * int copy[WORLD_SIZE][WORLD_SIZE]: ���ԡ���
 * int original[WORLD_SIZE][WORLD_SIZE]: ���ԡ���
 * �֤���: 0
 */
int copyWorld(int copy[WORLD_SIZE][WORLD_SIZE], 
	      int original[WORLD_SIZE][WORLD_SIZE]){
  int i,j;

  for (i=0; i<WORLD_SIZE; i++){
    for (j=0; j<WORLD_SIZE; j++){
      copy[i][j] = original[i][j];
    }
  }
  return(1);
}

#ifdef VERSION_1_2 
static int copy_array[WORLD_SIZE][WORLD_SIZE];     /* �ʻ�����(���ԡ�) */

/*
 * Watch dog timer��¤�Τν������(��������)
 */
static void setWatchdogTimer(){
  int status;

  /* ��¾����Ϥޤ� */
  status=pthread_mutex_lock(&(wdtimer.mutex));
  if(status != 0){
    fprintf(stderr,"mutex lock fail!!\n");
    abort();
  }
  
  /* ���� */
  wdtimer.count = WATCHDOG_COUNT_INIT;
  wdtimer.state = WATCHDOG_RUN; /* ���֤δƻ볫�� */

  /* ��¾���潪��� */
  status=pthread_mutex_unlock(&(wdtimer.mutex));
  if(status != 0){
    fprintf(stderr,"mutex unlock fail!!\n");
    abort();
  }
}

/*
 * Watch dog timer�β��
 * 1�ä�Wait�Ѥˤ����
 */
static void resetWatchdogTimer(){
  int status;

  /* ��¾����Ϥޤ� */
  status=pthread_mutex_lock(&(wdtimer.mutex));
  if(status != 0){
    fprintf(stderr,"mutex lock fail!!\n");
    abort();
  }
  
  /* ���� */
  wdtimer.state = WATCHDOG_STOP; /* ���֤δƻ뽪λ */
  
  /* ��¾���潪��� */
  status=pthread_mutex_unlock(&(wdtimer.mutex));
  if(status != 0){
    fprintf(stderr,"mutex unlock fail!!\n");
    abort();
  }
}

/*
 * Watchdog timer����åɤ����Ρʴؿ�)
 * void *arg:Prey/Predator����åɤ�thread ID�ؤΥݥ���
 */
static void *threadWatchdogTimer(void *arg){
  int status;
  pthread_t *tid = (pthread_t *) arg;
  int wdexit=0;

  setWatchdogTimer(); /* watchdog_t��¤�Τν���� */

  /* ��¾����Ϥޤ� */
  while(1){
    status=pthread_mutex_lock(&(wdtimer.mutex));
    if(status != 0){
      fprintf(stderr,"mutex lock fail!!\n");
      abort();
    }
  
    /* ���� */
    if(wdtimer.count == 0){
      if(wdtimer.state == WATCHDOG_RUN){
	/* ������˽����ʤ�Prey/Predator����åɤ򥭥�󥻥뤹�� */
	status = pthread_cancel(*tid); 
      }
      /* �����ϰ�������ȥ�����
      if(status != 0){
	fprintf(stderr,"pthread_cancel fail!!\n");
	abort();
      }
      */
      wdexit = 1; /* watchdog thread��λ���뤿��Υե饰 */
    }
    else {
      /* watch dog timer�Υ����󥿤�1���� */
      if(wdtimer.count>0){
	wdtimer.count--;
      }
      else{
	wdexit = 1; /* watchdog thread��λ���뤿��Υե饰 */
      }
    }

    /* ��¾���潪��� */
    status=pthread_mutex_unlock(&(wdtimer.mutex));
    if(status != 0){
      fprintf(stderr,"mutex unlock fail!!\n");
      abort();
    }
    if(wdexit)
      {	
	/* watchdog thread��λ���� */
	pthread_exit(0);
      }
    usleep(WATCHDOG_INTERVAL);
  }
}

/*
 * Prey ����åɤ����Ρʴؿ�)
 * void *arg:�ʻҶ��֤ؤΥݥ��󥿡�int *)
 */
static void *threadPrey(void *arg)
{
  static int Action;
  int *ca = arg;
  int cancel_type;
  int status;

  /* ��Ʊ������󥻥���ǽ�ˤ��� */
  status = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,
				 &cancel_type);
  if(status != 0){
    fprintf(stderr,"pthread_setcanceltype fail!!\n");
    abort();
  }

  Prey(ca, &Action);  
  resetWatchdogTimer();  /* watchdog timer��λ���� */
  pthread_exit(&Action); /* thread��λ��������ͤȤ��Ƽ���ư����֤� */
}

/*
 * Predator ����åɤ����Ρʴؿ�)
 * void *arg:�ʻҶ��֤ؤΥݥ��󥿡�int *)
 */
static void *threadPredator(void *arg)
{
  static int Action;
  int *ca = arg;
  int cancel_type;
  int status;
  int i,j;

  /* ��Ʊ������󥻥���ǽ�ˤ��� */
  status = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,
				 &cancel_type);
  if(status != 0){
    fprintf(stderr,"pthread_setcanceltype fail!!\n");
    abort();
  }

  /*  usleep(1100*1000);*/
  /* for(;;) */
  Predator(ca, &Action);
  resetWatchdogTimer();  /* watchdog timer��λ���� */
  pthread_exit(&Action); /* thread��λ��������ͤȤ��Ƽ���ư����֤� */
}

#endif /* VERSION_1_2 */
/*
 * Pursuit Game��main�ؿ�
 * �֤���: ���ｪλ�ʤ�0,�۾ｪλ�ʤ�1
 */

int main(int argc, char *argv[]){
  int i;
  int array[WORLD_SIZE][WORLD_SIZE];          /* �ʻ�����(���ꥸ�ʥ�) */
#ifndef VERSION_1_2
  int copy_array[WORLD_SIZE][WORLD_SIZE];     /* �ʻ�����(���ԡ�) */
#endif /* VERSION_1_2 */
  int gameStepNum;                            /* ������Υ��ƥå׿� */
  int predatorAction, preyAction;             /* Predator��Prey��ư����ɽ�� */

#ifdef VERSION_1_2
  int status;                                 /* pthread_*�ؿ���������� */
  void *tret;                                 /* Prey/Predator����åɽ�λ����������� */
#endif /* VERSION_1_2 */

  /* �ʲ��ϥ��ץ�������ˤ���ѹ�������ǽ���Τ����ѿ� */
  int gameStepNum_Max;                        /* ������κ��祹�ƥå׿� */
  int displayWait;                            /* ɽ�������ֳ�(�ޥ�������) */
  char worldFileName[WORLD_FILE_NAME_LENGTH]; /* �ʻ������ե�����̾ */

  /* �ѿ��Υǥե�����ͤ����ꤹ�� */
  gameStepNum_Max = GAME_NUM;
  displayWait = DISPLAY_WAIT;
  strcpy(worldFileName, "battlefield.dat");

  /* ɸ�����Ϥ���Υѥ�᡼������ */
  for (i=1; i<argc; i++){
    /* "-s"(���ƥå׿�����)���ץ����ν��� */
    if (strcmp(argv[i], "-s")==0){              /* "-s"�����ä��� */
      if (i+1 < argc){                          /* ���μ������Ϥ����뤫? */
	if (atoi(argv[i+1]) > 0){               /* ���Ϥ��줿�ͤ�����? */
	  gameStepNum_Max = atoi(argv[i+1]);    /* ����OK�ΤȤ��ν��� */
	  i++;
	}
	else{
	  printf("Invalid input value!! Specify one positive number.\n");
	  /* �ͤ������Ǥʤ���� */
	  return(1);
	}
      }
      else{
	/* ���ץ����μ������Ϥ��ʤ���� */
	printf("Option error!! You must specify number of game step.\n");
	return(1);
      }
    }
    /* "-t"(ɽ���ֳֻ���)���ץ����ν��� */
    else if(strcmp(argv[i], "-t")==0){         /* "-t"�����ä��� */
      if (i+1 < argc){                         /* ���μ������Ϥ����뤫? */
	if (atoi(argv[i+1]) >= 0){              /* ���Ϥ��줿�ͤ�������? */
	  displayWait = atoi(argv[i+1]);       /* ����OK�ΤȤ��ν��� */
	  i++;
	}
	else{
	  printf("Invalid input value!! Specify one positive number.\n");
	  /* �ͤ������Ǥʤ���� */
	  return(1);
	}
      }
      else{
	/* ���ץ����μ������Ϥ��ʤ���� */
	printf("Option error!! you must specify interval time of redraw.\n");
	return(1);
      }
    }
    /* "-w"(�ʻ������ե�����̾����)���ץ����ν��� */
    else if(strcmp(argv[i], "-w")==0){          /* "-w"�����ä��� */
      if (i+1 < argc){                          /* ���μ������Ϥ����뤫? */
	/* ����OK�ΤȤ��ν��� */
	strncpy(worldFileName, argv[i+1], WORLD_FILE_NAME_LENGTH);
	i++;
      }
      else{
	/* ���ץ����μ������Ϥ��ʤ���� */
	printf("Option error!! You must specify world file name.\n");
	return(1);
      }
    }
    else {
      printf("Invalid option: available options are:\n");
      printf("-s: Specify number of game step. ex: \"-s 10\"\n");
      printf("-t: Specify interval  time of redraw. ex: \"-t 100000\"\n");
      printf("-w: Specify world file name. ex: \"-w battlefield2.dat\"\n");
      return(1);
    }
  }

  /* BattleField���ɤ߹��� */
  if (ReadInitConf(array,worldFileName) == 1){
    fprintf(stderr,"File read failed!!\n");
    return(1);
  }

  /* ɽ���Υ��ꥢ */
  system("clear");

  /* ������֤�ɽ�� */
  PrintWorld(array,0);

#ifdef VERSION_1_2
  /* ����¹Ԥ��륹��åɿ��򥻥åȤ��� */
  pthread_setconcurrency(3);
#endif /* VERSION_1_2 */

  /* �����ॹ������ */
  for (gameStepNum=1; gameStepNum<= gameStepNum_Max; gameStepNum++){

#ifdef VERSION_1_2 /* ���ִƻ�С������ */
    /* Predator�ι�ư */
    copyWorld(copy_array,array);

    /* Predator thread���� */
    status = pthread_create(&player_tid, NULL, threadPredator, (void *)copy_array);
    if(status != 0){
      fprintf(stderr,"pthread_create fail!!: %s\n", strerror(status));
      abort();
    }

    /* watch dog timer thread���� */
    status = pthread_create(&wd_tid, NULL, threadWatchdogTimer, (void *)&player_tid);
    if(status != 0){
      fprintf(stderr,"pthread_create fail!!: %s\n", strerror(status));
      abort();
    }

    /* Predator thread�ν�λ���Ԥġ���λ����ͤ�tret */
    status = pthread_join(player_tid, &tret);
    if(status != 0){
      fprintf(stderr,"pthread_join fail!!: %s\n", strerror(status));
      abort();
    }

    /* Predator thread������󥻥뤵�줿����ǧ */
    if(tret == (void *)PTHREAD_CANCELED){
      predatorAction = 's';
    }
    else{
      predatorAction = *((int *)tret);
    }

    /* watch dog thread�ν�λ���Ԥġ���λ����ͤ�tret */
    status = pthread_join(wd_tid, &tret);
    if(status != 0){
      fprintf(stderr,"pthread_join fail!!: %s\n", strerror(status));
      abort();
    }

    /* Prey�ι�ư(2��ư����1��٤�) */
    if (gameStepNum % 3 != 0){ 
      copyWorld(copy_array,array);

      /* Prey thread���� */
      status = pthread_create(&player_tid, NULL, threadPrey, (void *)copy_array);
      if(status != 0){
	fprintf(stderr,"pthread_create fail!!: %s\n", strerror(status));
	abort();
      }

      /* watch dog timer thread���� */
      status = pthread_create(&wd_tid, NULL, threadWatchdogTimer, (void *)&player_tid);
      if(status != 0){
	fprintf(stderr,"pthread_create fail!!: %s\n", strerror(status));
	abort();
      }

      /* Prey thread�ν�λ���Ԥġ���λ����ͤ�tret */
      status = pthread_join(player_tid, &tret);
      if(status != 0){
	fprintf(stderr,"pthread_join fail!!: %s\n", strerror(status));
	abort();
      }

      /* Prey thread������󥻥뤵�줿����ǧ */
      if(tret == (void *)PTHREAD_CANCELED){
	preyAction = 's';
      }
      else{
	preyAction = *((int *)tret);
      }

      /* watch dog thread�ν�λ���Ԥġ���λ����ͤ�tret */
      status = pthread_join(wd_tid, &tret);
      if(status != 0){
	fprintf(stderr,"pthread_join fail!!: %s\n", strerror(status));
	abort();
	
      }
    }
    else{
      preyAction = 's';
      usleep(WATCHDOG_COUNT_INIT*WATCHDOG_INTERVAL);
    }
#else /* VERSION_1_2 */
    /* Predator�ι�ư */
    copyWorld(copy_array,array);
    Predator(copy_array, &predatorAction);

    /* Prey�ι�ư(2��ư����1��٤�) */
    if (gameStepNum % 3 != 0){
      copyWorld(copy_array,array);
      Prey(copy_array,&preyAction);      
    }
    else{
      preyAction = 's';
    }
#endif /* VERSION_1_2 */

    /* ɽ���Υ������� */
    usleep(displayWait);

    /*
     * ���줾��ι�ư�˹�碌�Ƴʻ������򹹿�
     * RenewWorld�ε����ͤ�0�ʤ�з�³
     */
    if (RenewWorld(array,predatorAction, preyAction) == 0){
      system("clear");
      PrintWorld(array, gameStepNum);
    }
    /* �����Ǥʤ����(1�ʤ��)��λ */
    else{
      system("clear");
      PrintWorld(array, gameStepNum);      
      printf("Game Over!! Winner Predator (%d clock)!!\n",gameStepNum);
      return(0);
    }

  } 

  /* Prey���Ǹ�ޤ�ƨ���ڤä��Ȥ��Υ�å��������� */
  printf("Game Over!! Winner Prey!!\n");
  return(0);
}

