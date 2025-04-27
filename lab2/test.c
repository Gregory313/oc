// // #include <stdio.h>
// // #include <stdbool.h>


// // #define MAX_PROCESSES 10
// // struct Process
// // {
// //     char nameProcess;
// //     int hasDependencies;   // need to work with input or demand info from other processes
// //     int numCycleLimitPerUP; // number of cycles to wait until up tempPriority to avoid starvation
// //     int indexInQueue;
// //     int tempPriority;       // priority to up temporary in diff queries
// //     int priority;
// //     int Ta;                 // time arrival  - mom when proc ready to start
// //     int Tw;                 // wait period of proc to be worked
// //     int Ts;                 // till that time proc working
// //     int Tr;                 // Tw + Ts 
// //     int Trem;               // remain time time count procces for proc
// // };

// // struct Queue
// // {
// //     struct Process* processes[MAX_PROCESSES];
// //     int minPriorityProc;    //min priority of proccess in queue 
// //     int count;
// //     int criticalPriority;   // after this prioriry we go to fifo
// //     int numProcCanAddToQ;   // number of processes that can be added to priority query
// //     int priority;
// //     int priorityStep;
// // };

// // struct QueuePair {
// //     struct Queue copiedQueue; // Первая очередь (скопированные процессы)
// //     struct Queue remainingQueue; // Вторая очередь (оставшиеся процессы)
// // };


// // int compareByTrem(const void* a, const void* b) {
// //     struct Process* processA = *(struct Process**)a;
// //     struct Process* processB = *(struct Process**)b;
// //     if (processA->Trem != processB->Trem) {
// //         return processA->Trem - processB->Trem; // Сортировка по возрастанию Trem 
// //     }
// //     return processA->hasDependencies - processB->hasDependencies; // Если Trem равны, сортируем по зависимостям
// // }

// // void removeProcessFromQueue(struct Queue* queue, int index){
// //     for(int i = index; i < queue -> count - 1; i++){
// //         queue -> processes[i] = queue -> processes[i+1];
// //     }
// //     queue -> count--;
// // }


// // int quantum = 5;
// // int highestPriority = 0;

// // void addProcess(struct Queue* queue, char name, int priority, int Ta, int Tw, int Ts) {
    
// //     if (queue->count < MAX_PROCESSES) {

// //         struct Process* newProcess = (struct Process*)malloc(sizeof(struct Process));


// //         newProcess-> nameProcess = name;
// //         newProcess-> priority = priority;
// //         newProcess-> Ta = Ta;
// //         newProcess-> Tw = Tw;
// //         newProcess-> Ts = Ts;
// //         newProcess-> Tr = Ts + Ts;
// //         newProcess-> Trem = Tw + Ts; 
// //         newProcess-> indexInQueue = queue->count;
// //         newProcess-> tempPriority = priority;
// //         newProcess-> numCycleLimitPerUP = 0;
// //         newProcess-> hasDependencies = rand() % 2;

// //         if (quantum > newProcess-> Trem) {
// //             quantum = newProcess-> Trem;
// //         }
// //         if(queue -> minPriorityProc < priority){
// //             queue -> minPriorityProc = priority;
// //         }

// //         queue->processes[queue->count++] = newProcess;
// //     } else {
// //         printf("Queue is full\n");
// //     }
// // }

// // int compareByPriority(const void* a, const void* b) {
// //     struct Process* processA = (struct Process*)a;
// //     struct Process* processB = (struct Process*)b;
// //     return processB->priority - processA->priority; // Сортировка по убыванию приоритета
// // }

// // int compareByDependencies(const void* a, const void* b) {
// //     struct Process* processA = (struct Process*)a;
// //     struct Process* processB = (struct Process*)b;
// //     return processA->hasDependencies - processB->hasDependencies; // Сортировка по возрастанию
// // }

// // int compareProcess(const void* a, const void* b) {
// //     return ((struct Process*)b)->priority - ((struct Process*)a)->priority;
// // }

// // void JSF(struct Queue* queue){

// //     // qsort(queue->processes, queue->count, sizeof(struct Process), compareProcess);

// //     for(int i = 0; i < queue -> count; ){
// //         struct Process* proc = &queue -> processes[i];
// //         printf("CURRENT PROC %c\n", proc->nameProcess);

// //         if(proc -> Trem <= quantum){
// //             proc -> Trem = 0;
// //             printf("Process %c finished for %d time units\n", proc->nameProcess, proc->Trem);
// //             removeProcessFromQueue(queue, i);
// //         } else{
// //             proc -> Trem -= quantum;
// //             printf("Process %c runs remain %d time units\n", proc->nameProcess, proc->Trem);
// //             i++;
// //         }       
// //     }
// // }

// // int countPriorityProcesses(struct Queue* queue, int criticalPriority) {
// //     int count = 0;
// //     for (int i = 0; i < queue->count; i++) {
// //         if (queue->processes[i]-> priority <= criticalPriority) {
// //             count++;
// //         }
// //     }
// //     return count;
// // }



// // struct QueuePair copyQueue(struct Queue* source, int length) {
// //     struct QueuePair result;
// //     result.copiedQueue.count = length;
// //     result.remainingQueue.count = source->count - length;

// //     // Копируем процессы в первую очередь
// //     for (int i = 0; i < length; i++) {
// //         struct Process* newProcess = (struct Process*)malloc(sizeof(struct Process));
// //         if (newProcess == NULL) {
// //             printf("Ошибка выделения памяти для копирования процесса\n");
// //             exit(1);
// //         }
// //         *newProcess = *(source->processes[i]);
// //         result.copiedQueue.processes[i] = newProcess;
// //     }

// //     // Копируем оставшиеся процессы во вторую очередь
// //     for (int i = length; i < source->count; i++) {
// //         struct Process* newProcess = (struct Process*)malloc(sizeof(struct Process));
// //         if (newProcess == NULL) {
// //             printf("Ошибка выделения памяти для копирования процесса\n");
// //             exit(1);
// //         }
// //         *newProcess = *(source->processes[i]);
// //         result.remainingQueue.processes[i - length] = newProcess;
// //     }

// //     // Сортируем первую очередь по приоритету 
// //     qsort(result.copiedQueue.processes, result.copiedQueue.count, sizeof(struct Process*), compareByPriority);

// //     // Сортируем вторую очередь по Trem и зависимостям
// //     qsort(result.remainingQueue.processes, result.remainingQueue.count, sizeof(struct Process*), compareByTrem);

// //     return result; // Возвращаем обе очереди
// // }





// // void freeQueue(struct Queue* queue) {
// //     for (int i = 0; i < queue->count; i++) {
// //         free(queue->processes[i]); // Освобождаем память для каждого процесса
// //     }
// // }


// // void roundRobin(struct Queue* queue, int quantum, int priority) { //priority = 0 += 1; 

// //     int numProcWCritPriority = countPriorityProcesses(queue, priority);
// //     int currAddQ = 0; // nuber of currently added process

// //     struct Queue localQueue = copyQueue(&queue, numProcWCritPriority); 


// //     while (numProcWCritPriority != 0) {
// //         for (int i = 0; i < localQueue.count; ) {
// //             struct Process* proc = &localQueue.processes[i];
// //             printf("CURRENT PROC %c (Priority: %d)\n", proc->nameProcess, proc->priority);

// //             if (proc->tempPriority <= priority) {
// //                 if (proc->Trem <= quantum) {
// //                     printf("Process %c finished for %d time units\n", proc->nameProcess, proc->Trem);
// //                     removeProcessFromQueue(queue, i);
// //                     removeProcessFromQueue(&localQueue, i);
// //                 } else {
// //                     proc->Trem -= quantum;
// //                     printf("Process %c runs remain %d time units\n", proc->nameProcess, proc->Trem);
// //                     i++; 
// //                 }
// //             } else {

// //                 if(localQueue.count < numProcWCritPriority + localQueue.numProcCanAddToQ){
// //                     localQueue.count = numProcWCritPriority + 1;
                    
// //                 }else{

// //                 }

// //                 if(proc -> numCycleLimitPerUP != 0){
                    
// //                 }else{
// //                     proc -> numCycleLimitPerUP  -= 1; 
// //                 }
// //                 printf("Process %c skipped due to high priority\n", proc->nameProcess);
// //                 i++; // Просто переходим к следующему процессу
// //             }
// //         }
        
// //     }
// //     freeQueue(&localQueue);
// // }


// // // void printQueue(struct Queue* queue) {
// // //     for (int i = 0; i < queue->count; i++) {
// // //         printf("Process: %c, Arrival Time: %d, Wait Time: %d, Service Time: %d, Total Time: %d, Remaining Time: %d\n",
// // //                queue->processes[i].nameProcess, queue->processes[i].Ta,
// // //                queue->processes[i].Tw, queue->processes[i].Ts,
// // //                queue->processes[i].Tr, queue->processes[i].Trem);
// // //     }
// // // }


// // int main() {
// //     srand(time(NULL));

// //     struct Queue Q1 = { .count = 0, .priority = 1, .minPriorityProc = 0, .numProcCanAddToQ = 3, .priorityStep = 1}; // Highest priority
// //     struct Queue Q2 = { .count = 0, .priority = 2 }; // Medium priority
// //     struct Queue Q3 = { .count = 0, .priority = 3 }; // Lowest priority

// //     addProcess(&Q1, 'A', 0, 2, 1, 8);
// //     addProcess(&Q1, 'B', 0, 3, 0, 3);
// //     addProcess(&Q1, 'C', 3, 1, 2, 0);
// //     addProcess(&Q1, 'D', 2, 4, 0, 2);


// //     printf("Quantum = %d\n",quantum);

// //     JSF(&Q1);
    


// //     return 0;
// // }



// void addProcesses(struct Queue* queue, char baseName, int priority, int Ta, int Tw, int Ts, int numCycleLimitPerUP, int numProcesses) {
//     if (queue->count + numProcesses > MAX_PROCESSES) {
//         printf("Not enough space in the queue to add %d processes\n", numProcesses);
//         return;
//     }

//     for (int i = 0; i < numProcesses; i++) {
//         struct Process* newProcess = (struct Process*)malloc(sizeof(struct Process));
//         if (newProcess == NULL) {
//             printf("Memory allocation failed\n");
//             return;
//         }

//         newProcess->nameProcess = baseName + i; // Уникальное имя для каждого процесса
//         newProcess->priority = priority;
//         newProcess->Ta = Ta;
//         newProcess->Tw = Tw;
//         newProcess->Ts = Ts;
//         newProcess->Tr = Ts + Tw;
//         newProcess->Trem = Tw + Ts; newProcess->tempPriority = priority;
//         newProcess->numCycleLimitPerUP = numCycleLimitPerUP;
//         newProcess->hasDependencies = rand() % 2;

//         if (queue->minPriorityProc < priority) {
//             queue->minPriorityProc = priority;
//         }

//         queue->processes[queue->count++] = newProcess;
//     }
// }
