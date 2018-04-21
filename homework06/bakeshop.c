/*
* bakeshop.c simulates a bakery with one bread maker.
*
* Author -- rlc32 Russell Clousing
* April 7, 2018
* CS232 homework06
*
*/

// includes needed.
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// semaphores needed
sem_t bakerSem;
sem_t custSem;
sem_t storeSem;

// global counters needed
int bakedLoaves = 0;
int availableLoaves = 0;
int loavesGivenOut =0;
int checkedoutCust = 0;
long threadReadyCheckout;

//debug variable
int debug = 0;

/*
* bakeBreadFunction is the function for bakingThread
* steps
*   announce the bake shop is open for business
*   while bakedLoaves < 10
*       try and grabe bakerSem
*       bake a loaf of bread
*       increase bakedLoaves and availableLoaves by 1
*       announce that a loaf was baked successfully
*       release bakerSem
*       Delay 1 second
*Once all 10 loaves have been baked, announce done baking for the day.
*/
void* bakeBreadFunction(){
    //announce open
    fprintf(stderr, "\n----------Store is open and FRESH bread is baking----------\n\n");
    //while loop
    while(bakedLoaves < 10){
        //attmept to grab bakerSem
        sem_wait(&bakerSem);
        //bake loaf and increase counters
        availableLoaves += 1;
        bakedLoaves += 1;
        //announce baked loaf
        fprintf(stderr, "Loaf %d is FRESH out of the oven and ready to be sold.\n\n", bakedLoaves);
        //release bakerSem
        sem_post(&bakerSem);
        //delay one second
        usleep(1000000);
    }
    fprintf(stderr, "---------All bread for today has been baked----------\n\n");
}
/*
* cashFunction is the function for cash thread.
* steps needed:
*   while checkedoutCust < 10
*     if loavesGivenOut > checkedoutCust
*       grab the customer semaphore
*       announce customer is ready
*       grab baker semaphore
*       delay 1 second
*       announce customer paid
*       announce recipt printed
*       announce cust received receipt
*       increase checkedoutCust by 1
*       release both semaphores
*   announce all checked out
*/
void* CashFunction(){
    while(checkedoutCust < 10){
        if(loavesGivenOut > checkedoutCust){
            //try and grab customer semaphore
            sem_wait(&custSem);
            //announce ready to checkout
            fprintf(stderr, "Customer %ld is waiting to check out.\n\n", threadReadyCheckout);
            //try and grab bakerSem
            sem_wait(&bakerSem);
            //delay 1 second
            usleep(1000000);
            //announce cust paid
            fprintf(stderr, "Customer %ld paid for the loaf.\n\n", threadReadyCheckout);
            //announce print of receipt
            fprintf(stderr, "Baker printed a recipt for customer %ld.\n\n", threadReadyCheckout);
            usleep(1000000);
            //add to checkedoutCust
            checkedoutCust +=1;
            //release semaphores
            sem_post(&bakerSem);
            sem_post(&custSem);
        }
    }
    //announce all checked out
    fprintf(stderr, "--------All customers have checked out and gotten reciepts--------\n\n");
}

/*
* custInShop is the function for all customers that are in the shop
* Steps:
*   Cust tries and enter store
*   grab storeSem
*   once inside wait for bread
*   grab custSem
*   update loaves available coutner and loaves given coutner
*   update thread id to ready to checkout
*   delay 1 second
*   grab customer semaphores
*   leave Store
*   release custSem
*   release storeSem
*
*/
void* custInShop(void *id_num){
    //convert id_num back to long int.
    long id;
    id = (long)id_num;
    //announce waiting to enter
    fprintf(stderr, "Customer %ld is waiting to enter the store.\n\n",id);
    //try and grab store semaphore
    sem_wait(&storeSem);
    //announce entry to storeSem
    fprintf(stderr, "Customer %ld has entered the store.\n\n", id);
    //try and grab customer semaphore
    sem_wait(&custSem);
    //wait for available loaf of bread by waiting 1 second
    while(availableLoaves == 0){
        usleep(1000000);
    }
    //announce customer has loaf of bread
    fprintf(stderr, "Customer %ld has a loaf of bread.\n\n", id);
    sem_post(&custSem);
    availableLoaves -=1;
    //update coutners
    loavesGivenOut +=1;
    //update threadReadyCheckout id.
    threadReadyCheckout = id;

    if(debug){
        //debuging for threadReadyCheckout not updateing correctly
        fprintf(stderr,"*****threadReadyCheckout is now %ld*****\n\n", id);

    }
    //delay 1 second
    usleep(1000000);
    //grab custSem
    sem_wait(&custSem);
    //announce leaving store
    fprintf(stderr, "Customer %ld has left the store.\n\n", id);
    //release semaphores
    sem_post(&custSem);
    sem_post(&storeSem);

}

int main() {
    //initialize the semaphores
    sem_init(&bakerSem, 0, 1);
    sem_init(&custSem, 0, 1);
    sem_init(&storeSem, 0, 5);

    //create threads for each of the bakers jobs
    pthread_t bakingThread;
    pthread_t cashThread;

    //create array of 10 threads. each one represents one customer
    pthread_t threads[10];

    //declare integer thread return values for error use
    int bakerReturnForError;
    int custReturnForError;
    int cashReturnForError;
    //create thread for baking bread and check for errors on creation.
    bakerReturnForError = pthread_create(&bakingThread, NULL, bakeBreadFunction, NULL);
    if(bakerReturnForError){
        fprintf(stderr, "ERROR; return code from bakingThread pthread_create() is %d\n\n", bakerReturnForError);
            exit(-1);
    }
    //create thread for using cash register and check for errors on creation
    cashReturnForError = pthread_create(&cashThread, NULL, CashFunction, NULL);
    if(cashReturnForError){
        fprintf(stderr, "ERROR; return code from cashThread pthread_create() is %d\n\n", cashReturnForError);
            exit(-1);
    }
    //create each customer thread from the threads in threads[]. check on creation for errors.
    for(long i=0; i<10; i++){
        //setting last thread to have high priority.
        /*
        if(i==9){
            pthread_setschedprio(threads[9],99);
        }
        */
        custReturnForError = pthread_create(&threads[i], NULL, custInShop, (void *)i);
        if(custReturnForError){
            fprintf(stderr, "ERROR; return code from custThread pthread_create() is %d\n\n",custReturnForError);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
