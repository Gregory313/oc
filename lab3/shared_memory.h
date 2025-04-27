#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define BUF_SIZE 10
#define ITEM_SIZE 100

struct Message {
    char text[ITEM_SIZE];
    bool available;
};

struct SharedData {
    Message messages[BUF_SIZE];
    sem_t empty;
    sem_t full;
    sem_t mtx;
    int in;
    int out;
};

SharedData* createSharedSection(const char* name) {
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(SharedData));
    SharedData* data = (SharedData*)mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    data->in = 0;
    data->out = 0;

    sem_init(&data->empty, 1, BUF_SIZE);
    sem_init(&data->full, 1, 0);
    sem_init(&data->mtx, 1, 1);

    for (int i = 0; i < BUF_SIZE; ++i) {
        data->messages[i].available = false;
    }

    return data;
}

SharedData* connectToSharedSection(const char* name) {
    int fd = shm_open(name, O_RDWR, 0666);
    SharedData* data = (SharedData*)mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    return data;
}

#endif 