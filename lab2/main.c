#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_PROCESSES 100
#define CRITNUMPROC 3


struct Process
{
    char nameProcess;
    int hasDependencies;    // need to work with input or demand info from other processes
    int numCycleLimitPerUP; // number of cycles to wait until up tempPriority to avoid starvation
    int tempPriority;       // priority to up temporary in diff queries
    int priority;
    int Ta;                 // time arrival  - mom when proc ready to start
    int Tw;                 // wait period of proc to be worked
    int Ts;                 // till that time proc working
    int Tr;                 // Tw + Ts 
    int Trem;               // remain time time count procces for proc
};

struct Queue
{
    struct Process* processes[MAX_PROCESSES];
    int minPriorityProc;    //min priority of proccess in queue 
    int count;
    int numProcCanAddToQ;   // number of processes that can be added to priority query
    int priority;
    int priorityStep;
    int quantum;
    int groupSize;

};

void freeQueue(struct Queue* queue) {
    for (int i = 0; i < queue->count; i++) {
        free(queue->processes[i]); 
    }
    queue->count = 0;
}

void removeProcessFromQueue(struct Queue* queue, int index){
    for(int i = index; i < queue -> count - 1; i++){
        queue -> processes[i] = queue -> processes[i+1];
    }
    queue -> count--;
}


int compareByPriorityHasDepTrem(const void* a, const void* b) {
    struct Process* processA = *(struct Process**)a;
    struct Process* processB = *(struct Process**)b;

    if (processA->priority != processB->priority) {
        return processA->priority - processB->priority;
    }

    if (processA->hasDependencies != processB->hasDependencies) {
        return processA->hasDependencies - processB->hasDependencies;
    }

    return processA->Trem - processB->Trem;
}

int compareByTrem(const void* a, const void* b) {
    struct Process* processA = *(struct Process**)a;
    struct Process* processB = *(struct Process**)b;

    return processA->Trem - processB->Trem;
}
void addProcess(struct Queue* queue, char name, int priority, int Ta, int Tw, int Ts, int numCycleLimitPerUP) {
    
    if (queue->count < MAX_PROCESSES) {

        struct Process* newProcess = (struct Process*)malloc(sizeof(struct Process));

        newProcess-> nameProcess = name;
        newProcess-> priority = priority;
        newProcess-> Ta = Ta;
        newProcess-> Tw = Tw;
        newProcess-> Ts = Ts;
        newProcess-> Tr = Ts + Tw;
        newProcess-> Trem = Tw + Ts; 
        newProcess-> tempPriority = priority;
        newProcess-> numCycleLimitPerUP = numCycleLimitPerUP;
        newProcess-> hasDependencies = rand() % 2;

        if(queue -> minPriorityProc > priority){
            queue -> minPriorityProc = priority;
        }

        queue->processes[queue->count++] = newProcess;
    } else {
        printf("Queue is full\n");
    }
}
void addProcesses(struct Queue* queue, char baseName, int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        struct Process* newProcess = (struct Process*)malloc(sizeof(struct Process));

        newProcess->nameProcess = baseName + i; 
        newProcess->priority = rand() % 5 + 1;
        newProcess->Ta = rand() % 50;
        newProcess->Tw = rand() % 50;
        newProcess->Ts = rand() % 50;
        newProcess->Tr = newProcess->Tw + newProcess->Ts;
        newProcess->Trem = newProcess->Tr; 
        newProcess->tempPriority = newProcess->priority;
        newProcess->numCycleLimitPerUP = rand() % 10 + 1;
        newProcess->hasDependencies = rand() % 2;

        if(queue -> minPriorityProc < newProcess->priority){
            queue -> minPriorityProc = newProcess->priority;
        }

        queue->processes[queue->count++] = newProcess;
    }
}

void printProcessesStart(struct Queue* queue) {
    for (int i = 0; i < queue->count; i++) {
        struct Process* p = queue->processes[i];
        printf("Process Name: %c, Priority: %d, Ta: %d, Tw: %d, Ts: %d, Tr: %d, Trem: %d, Temp Priority: %d, Num Cycle Limit: %d, Has Dependencies: %d\n",
               p->nameProcess, p->priority, p->Ta, p->Tw, p->Ts, p->Tr, p->Trem, p->tempPriority, p->numCycleLimitPerUP, p->hasDependencies);
    }
}
void JSF(struct Queue* queue){
    printf("\nJSF START\n");

    qsort(queue -> processes, queue -> count, sizeof(struct Process*), compareByTrem);
    int middleQuatum = (queue -> processes[0] -> Trem + queue -> processes[queue -> count - 1] -> Trem) / 2;
    if(queue -> processes[0] -> Trem >= middleQuatum * 0.1f){
        queue -> quantum = queue -> processes[0] -> Trem;
    }
    else{
        queue -> quantum = middleQuatum * 0.1f;
    }


    printf("Quantum = %d\n", queue -> quantum);
    for(int i = 0; i < queue -> count; ){
        struct Process* proc = queue -> processes[i];
        printf("CURRENT PROC %c\n", proc->nameProcess);

        if(proc -> Trem <= queue -> quantum){
            proc -> Trem = 0;
            printf("Process %c finished for %d time units\n", proc->nameProcess, proc->Trem);
            removeProcessFromQueue(queue, i);
        }else{
            proc -> Trem -= queue -> quantum;
            printf("Process %c runs remain %d time units\n", proc->nameProcess, proc->Trem);
            i++;
        }       
    }
    printf("\nJSF END\n");
}

int countPriorityProcesses(struct Queue* queue, int* criticalPriority) {

    int count;
    do{
        count = 0;
        for (int i = 0; i < queue->count; i++) {
            if (queue->processes[i]-> priority <= *criticalPriority) {
                count++;
            }
        }
        if (count < 3) {
            (*criticalPriority)+=queue -> priorityStep;//++;
            // printf("criticalPriority %d\n", criticalPriority);
            printf("minPriorityProc %d\n",queue -> minPriorityProc);
            if (*criticalPriority > queue -> minPriorityProc) {
                return  0; 
            }
        }
    }while (count < CRITNUMPROC);
    
    return count;
}


void printProcesses(struct Queue* queue) {
    for (int i = 0; i < queue->count; i++) {
        printf("Process %c: Priority = %d, Trem = %d, hasDependencies = %d\n",
               queue->processes[i]->nameProcess,
               queue->processes[i]->priority,
               queue->processes[i]->Trem,
               queue->processes[i]->hasDependencies);
    }
}


void roundRobin(struct Queue* queue, int quantum, int priority) { 

    printf("\nRR START\n");
    int numProcWCritPriority = 0;

    numProcWCritPriority = countPriorityProcesses(queue, &priority);
   
    int tremValues[queue -> count];

    for (int i = 0; i < queue -> count; i++) {
        tremValues[i] = queue->processes[i]->Trem; 
    }

    double median;
    if (queue -> count % 2 == 0) {
        median = (tremValues[queue -> count / 2 - 1] + tremValues[queue -> count / 2]) / 2.0;
    } else {
        median = tremValues[queue -> count / 2];
    }

    queue->quantum = median;
    printf("\nQuantum = %d  numProcWCritPriority %d \n", queue -> quantum, numProcWCritPriority);

    qsort(queue -> processes, queue -> count, sizeof(struct Process*), compareByPriorityHasDepTrem);
    printf("Processes sorted by priority:\n");
    printProcesses(queue);
    
    while (numProcWCritPriority != 0) {
        for (int i = 0; i < queue -> count; ) {
            struct Process* proc = queue -> processes[i];
            printf("numProcWCritPriority %d\n", numProcWCritPriority);
            
            
            if (proc -> tempPriority <= priority) {
                if (proc->Trem <= queue -> quantum) {
                    printf("Process %c finished for %d time units\n", proc->nameProcess, proc->Trem);
                    if (proc -> priority <= priority) numProcWCritPriority--;
                    removeProcessFromQueue(queue, i);
                } else {
                    proc->Trem -= queue -> quantum;
                    printf("Process %c runs remain %d time units\n", proc->nameProcess, proc->Trem);
                    i++; 
                }
            } else {
                if(proc -> tempPriority >= priority){
                    if(proc -> numCycleLimitPerUP > 0) proc -> numCycleLimitPerUP -=1;
                    if (proc -> numCycleLimitPerUP == 0 && queue -> count < numProcWCritPriority + queue -> numProcCanAddToQ){
                        proc -> tempPriority = priority;
                        printf("Process %c in queue\n", proc->nameProcess);
                    
                    }else{
                        printf("Process %c wait %d cycles or queue full\n", proc->nameProcess, proc -> numCycleLimitPerUP);
                    }
                }
                i++; 
            }
        }
        
    }
    printf("\nRR END\n");
}

int main() {
    srand(time(NULL));

    struct Queue Q1 = { .count = 0, .priority = 1, .minPriorityProc = 0, .numProcCanAddToQ = 3, .priorityStep = 1, .quantum = INT_MAX, .groupSize = 3}; // Highest priority

    addProcesses(&Q1, 'A', 15);
    printProcessesStart(&Q1);
    printf("\n");

    int startPrioirity = 1;

    while (Q1.count != 0)
    {
        if(Q1.count > 0) JSF(&Q1);
        if(Q1.count > 0) roundRobin(&Q1, Q1.quantum, startPrioirity);
    }


    printf("END\n");


    freeQueue(&Q1);

    return 0;
}







