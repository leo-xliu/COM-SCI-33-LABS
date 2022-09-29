#include "histo.h"
#include <semaphore.h>
#include <stdlib.h>

int sem_init(sem_t *s, int p, unsigned int val); /* s = val */

int sem_wait(sem_t *s);  /* P(s) */
int sem_post(sem_t *s);  /* V(s) */



sem_t mutex[64];

/*  ============= 

Add corresponding locks/semaphores and any other global variables here
Sample declarations:
sem_t mutex; //don't forget to initialize in main
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_barrier_t barrier; //don't forget to initialize in main
    pthread_mutex_t locks[BUCKET_SIZE]; //don't forget to initialize in main

=============  */



 /*  ============= 
    add initialization code for locks, or other global variables defined earlier

    the init() function will be called once at the beginning of each trial,
    as shown in the pseudocode below

    for (int i = 0; i < num_trials; i++) {
        init();
        test_results.append(run_tests(all_cases_or_a_particular_case));
    }
    =============  */
    
void init() {

    for (int i = 0; i < 64; i++)
    {
        sem_init(&mutex[i], 0, 1);
    }

}

/************ Test Case 1 ************/



    /*  =============
    this is the thread worker function that will be called for test case 1
    you can assume that there are T1N data points T1B histogram buckets

    This function will be called for each of the NTHREADS (8) worker threads

    The data array pointer (int* data) and the histogram array pointer (int* hist)
    will be the same for each thread. 

    thread_id would be different for each thread: each of the 8 worker 
    threads will get a different thread_id ranging [0, 7] (inclusive on both sides)

    The function given below is effectively only "single-threaded", because only one
    thread (with thread_id 0) does all the work, while all the other threads returns
    immediately. As a result, the performance is not that good.

    You should modify this function to effectively use the pool of the 8 worker 
    threads to compute the histogram faster.
    =============  */

void* compute_histogram_case1(void* input) {

    HistogramArgs* histArgs = (HistogramArgs*)input;
    unsigned int* data = (unsigned int*)(histArgs->data);
    unsigned int* hist = (unsigned int*)(histArgs->hist);
    const int thread_id = histArgs->id;
    
//first optimization: using thread ID, divide up the histogram data so that each thread has its own group of data to work with
    int sec = 12500000; //divides up the data into portions
    int start = sec*thread_id;
    int end = sec + start; //gives the range of data depending on thread_id

    unsigned int temp[8] = {0};

    for (int j = start; j < end; j++) {
        temp[data[j] % 8]++;
    }

    for (int i = 0; i < 8; i++)
    {
        __sync_fetch_and_add( &hist[i], temp[i]);
    }

    return NULL;
}

/*  =============

This commented out function tries to divide up the data into
blocks, one for each thread. However, there is a race! (where?)

Try it out!

void* compute_histogram_case1_RACE_CONDITION(void* input) {
    HistogramArgs* histArgs = (HistogramArgs*)input;
    int* data = (int*)(histArgs->data);
    int* hist = (int*)(histArgs->hist);
    const int thread_id = histArgs->id;

    const int STEP = T1N / NTHREADS;
    const int start = thread_id * STEP;
    const int end = start + STEP;

    for (int i = start; i < end; i++) {
        hist[data[i] % T1B]++;
    }

    return NULL;
}

=============  */

/************ Test Case 2 ************/



    /*  =============
    this function will be called for test case 2
    you can assume that there are T2N data points T2B histogram buckets

    This function will be called for each of the NTHREADS (i.e., 8) worker threads

    The data array pointer (int* data) and the histogram array pointer (int* hist)
    will be the same for each thread. 

    thread_id would be different for each thread: each of the 8 worker 
    threads will get a different thread_id ranging [0, 7] (inclusive on both sides)

    The function given below is effectively only "single-threaded", because only one
    thread (with thread_id 0) does all the work, while all the other threads returns
    immediately. As a result, the performance is not that good.

    You should modify this function to effectively use the pool of the 8 worker 
    threads to compute the histogram faster.
    =============  */


void* compute_histogram_case2(void* input) {

     HistogramArgs* histArgs = (HistogramArgs*)input;
    unsigned int* data = (unsigned int*)(histArgs->data);
    unsigned int* hist = (unsigned int*)(histArgs->hist);
    const int thread_id = histArgs->id;
    
//first optimization: using thread ID, divide up the histogram data so that each thread has its own group of data to work with
    int sec = 3125000; //divides up the data into portions
    int start = sec*thread_id;
    int end = sec + start; //gives the range of data depending on thread_id

    int* temp = (int*)malloc(16000000*sizeof(int));

    for (int j = start; j < end; j++) {
        temp[data[j] % 16000000]++;
    }

    for (int i = 0; i < 16000000; i += 250000)
    {
        sem_wait(&mutex[i/250000]);
        for (int i1 = i; i1 < 250000 + i; i1++)
        {
            hist[i1] += temp[i1];
        }
        sem_post(&mutex[i/250000]);
    }

    return NULL;
}




    // HistogramArgs* histArgs = (HistogramArgs*)input;
    // unsigned int* data = (unsigned int*)(histArgs->data);
    // unsigned* hist = (unsigned*)(histArgs->hist);
    // const int thread_id = histArgs->id;

    // if (thread_id < 4)
    // {
    //     int start = 4000000*thread_id;
    //     int end = 4000000 + start; 
    //     for (int j = 0; j < 12500000; j += 6250000) {
    //         sem_wait(&mutex[thread_id]);
    //         for (int j1 = j; j1 < j + 6250000; j1++)
    //         {
    //         unsigned int ind = data[j1] % 16000000;
    //         if (ind >= end || ind < start)
    //             continue;
    //         hist[ind]++;
    //         }
    //         sem_post(&mutex[thread_id]);
    //     }
    // }
    // else
    // {
    //     int start = 4000000*(7-thread_id);
    //     int end = 4000000 + start; 
    //     for (int j = 12500000; j < 25000000; j += 6250000) {
    //         sem_wait(&mutex[7-thread_id]);
    //         for (int j1 = j; j1 < j + 6250000; j1++)
    //         {
    //         unsigned int ind = data[j1] % 16000000;
    //         if (ind >= end || ind < start)
    //             continue;
    //         hist[ind]++;
    //         }
    //         sem_post(&mutex[7-thread_id]);
    //     }
    // }


    // HistogramArgs* histArgs = (HistogramArgs*)input;
    // unsigned int* data = (unsigned int*)(histArgs->data);
    // unsigned* hist = (unsigned*)(histArgs->hist);
    // const int thread_id = histArgs->id;

    // if (thread_id < 2)
    // {
    //     int start = 8000000*thread_id;
    //     int end = 8000000 + start; 
    //     for (int j = 0; j < 6250000; j++) {
    //         unsigned int ind = data[j] % 16000000;
    //         if (ind >= end || ind < start)
    //             continue;
    //         __sync_fetch_and_add( &hist[ind], 1);
    //     }
    // }
    // else if (thread_id < 4)
    // {
    //     int start = 8000000*(3-thread_id);
    //     int end = 8000000 + start; 
    //     for (int j = 6250000; j < 12500000; j++) {
    //         unsigned int ind = data[j] % 16000000;
    //         if (ind < start || ind >= end)
    //             continue;
    //         __sync_fetch_and_add( &hist[ind], 1);
    //     }
    // }
    //  else if (thread_id < 6)
    // {
    //     int start = 8000000*(5-thread_id);
    //     int end = 8000000 + start; 
    //     for (int j = 12500000; j < 18750000; j++) {
    //         unsigned int ind = data[j] % 16000000;
    //         if (ind >= end || ind < start)
    //             continue;
    //         __sync_fetch_and_add( &hist[ind], 1);
    //     }
    // }
    // else
    // {
    //     int start = 8000000*(7-thread_id);
    //     int end = 8000000 + start; 
    //     for (int j = 18750000; j < 25000000; j++) {
    //         unsigned int ind = data[j] % 16000000;
    //         if (ind < start || ind >= end)
    //             continue;
    //         __sync_fetch_and_add( &hist[ind], 1);
    //     }
    // }
    

    // return NULL;




//     HistogramArgs* histArgs = (HistogramArgs*)input;
//     unsigned int* data = (unsigned int*)(histArgs->data);
//     unsigned int* hist = (unsigned int*)(histArgs->hist);
//     const int thread_id = histArgs->id;
    

// //first optimization: using thread ID, divide up the histogram data so that each thread has its own group of data to work with
//     int sec = 3125000; //divides up the data into portions
//     int start = sec*thread_id;
//     int end = sec + start; //gives the range of data depending on thread_id

//     for (int j = start; j < end; j++) {
//         int val = data[j] % 16000000;
//         __sync_fetch_and_add( &hist[val], 1);
//     }

//     return NULL;




//     HistogramArgs* histArgs = (HistogramArgs*)input;
//     int* data = (int*)(histArgs->data);
//     int* hist = (int*)(histArgs->hist);
//     const int thread_id = histArgs->id;
    
// //first optimization: using thread ID, divide up the histogram data so that each thread has its own group of data to work with
//     const int sec = T2N/NTHREADS; //divides up the data into portions
//     const int start = sec*thread_id;
//     const int end = sec + start; //gives the range of data depending on thread_id

//     for (int j = start; j < end; j++) {
//         __sync_fetch_and_add( &hist[data[j] % T2B], 1);
//     }

//     return NULL;









//     HistogramArgs* histArgs = (HistogramArgs*)input;
//     int* data = (int*)(histArgs->data);
//     int* hist = (int*)(histArgs->hist);
//     const int thread_id = histArgs->id;
    
// //first optimization: using thread ID, divide up the histogram data so that each thread has its own group of data to work with
//     const int sec = T2B/NTHREADS; //divides up the data into portions
//     const int start = sec*thread_id;
//     const int end = sec + start; //gives the range of data depending on thread_id

//     for (int j = 0; j < T2N; j++) {
//         int ind = data[j] % T2B;
//         if ((ind >= start) && (ind < end))
//             hist[ind]++;
//     }

//     return NULL;







