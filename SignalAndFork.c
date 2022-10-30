#include <stdio.h>
#include <stdlib.h> // for exit()
#include <sys/types.h>
#include <time.h>
#include <unistd.h> // for fork()
#include <signal.h>
#include <stdio.h>

//------------const--------------
const int NUMBER_OF_CHILD = 2,
		  SIZE_OF_ARRAY = 50000,
		  RANGE_OF_NUMBERS = 100,
		  FRIST_CHILD = 0;

//----------prototype------------
void check_if_status_failed(const pid_t *status);
void do_father();
void do_child(const int *i,int * array);
void fill_array(int *array);
void swap(int* num1, int* num2);
void bubble_sort(int *array);
void insertion_sort(int arr[]);
void catch_sigusr1(int sig_num) ;
void catch_sigusr2(int sig_num) ;

//------------main---------------
int main() {

	 signal(SIGUSR1, catch_sigusr1);
	 signal(SIGUSR2, catch_sigusr2);
	 srand(time(NULL));
	 pid_t status ;
	 int i , array[SIZE_OF_ARRAY];

	 fill_array(array);
	 for(i = 0 ; i < NUMBER_OF_CHILD ;i++){
		 status = fork();
		 check_if_status_failed(&status);

	 if(status > 0)
		 do_father();

	 else do_child(&i,array);
	 }

	 return(EXIT_SUCCESS) ;
}
//The function gets array and insert random numbers to array
//-------fill_array----------
void fill_array(int *array){

	int i;

	for(i = 0 ; i < SIZE_OF_ARRAY ;i++)
		array[i] = rand() % RANGE_OF_NUMBERS;

}
//---------do_child-------------
void do_child(const int *i,int *array){

	if(*i == FRIST_CHILD)
		bubble_sort(array);

	else insertion_sort(array);

}
//The function gets array and execute insertion sort
//--------insertion_sort----------
void insertion_sort(int arr[])
{
    int i, key, j;

    for (i = 1; i < SIZE_OF_ARRAY; i++){
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    kill(getppid(), SIGUSR2);//signal to father
}
//----------swap------------
void swap(int* num1, int* num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}
//The function gets array and execute bubble sort
//-------bubble_sort---------
void bubble_sort(int *arr)
{
    int i, j;
    for (i = 0; i < SIZE_OF_ARRAY - 1; i++)
        for (j = 0; j < SIZE_OF_ARRAY - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);

    kill(getppid(), SIGUSR1);
}
//The function make to father wite for suns
//---------do_father--------
void do_father(){

	pause();//wait for signal
	pause();

}
//--------check_if_status_failed--------
void check_if_status_failed(const pid_t * status){

	if(status < 0) {
		perror("cannot fork") ;
		exit(EXIT_FAILURE) ;
	}
}
//------------catch_sigusr1----------
void catch_sigusr1(int sig_num){
	printf("The process number one finished\n");
}
//------------catch_sigusr2----------
void catch_sigusr2(int sig_num){
	printf("The process number two finished\n");
}
