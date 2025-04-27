#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <ctime>
#include <random>

using namespace std;

const int BUF_SIZE = 10;
const int ITEM_SIZE = 100;

struct SharedData {
    char toClient[BUF_SIZE][ITEM_SIZE]; 
    char toServer[BUF_SIZE][ITEM_SIZE];  
    int inClient;
    int outClient;
    int inServer;
    int outServer;
    sem_t emptyClient;
    sem_t fullClient;
    sem_t emptyServer;
    sem_t fullServer;
    sem_t mtx;
};


SharedData* createSharedSection(const char* name){
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(SharedData));
    SharedData* data = reinterpret_cast<SharedData*>(
        mmap(0,sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED_VALIDATE, fd, 0)
    );

    sem_init(&data->emptyClient, 1, BUF_SIZE);
    sem_init(&data->fullClient, 1, 0);
    sem_init(&data->emptyServer, 1, BUF_SIZE);
    sem_init(&data->fullServer, 1, 0);
    sem_init(&data->mtx, 1, 1);

    data->inClient = 0;
    data->outClient = 0;
    data->inServer = 0;
    data->outServer = 0;

    return data;
}

void destroySharedSection(SharedData* data, const char* name) {
    sem_destroy(&data->emptyClient);
    sem_destroy(&data->fullClient);
    sem_destroy(&data->emptyServer);
    sem_destroy(&data->fullServer);
    sem_destroy(&data->mtx);
    munmap(data, sizeof(SharedData));
    shm_unlink(name);
}



int main() {

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dist(1, 100); 

    const char* name = "/shm1";
    SharedData* data = createSharedSection(name);
    
    for (int i = 0; i < 10; ++i) {
        char messageToClient[ITEM_SIZE];
        int num = dist(gen);
        snprintf(messageToClient, ITEM_SIZE, "Message to client %d ", num);
        
        sem_wait(&data->emptyClient);
        sem_wait(&data->mtx);
        
        strcpy(data->toClient[data->inClient], messageToClient);
        data->inClient = (data->inClient + 1) % BUF_SIZE;
        
        sem_post(&data->mtx);
        sem_post(&data->fullClient);

        sem_wait(&data->fullServer);
        sem_wait(&data->mtx);
        
        char receivedFromClient[ITEM_SIZE];
        strcpy(receivedFromClient, data->toServer[data->outServer]);
        data->outServer = (data->outServer + 1) % BUF_SIZE;
        
        sem_post(&data->mtx);
        sem_post(&data->emptyServer);

        cout << "Server received: " << receivedFromClient << endl;

        sleep(1);
    }

    destroySharedSection(data, name);
    return 0;
}