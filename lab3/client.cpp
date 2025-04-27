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

SharedData* connectSharedSection(const char* name){
    int fd = shm_open(name, O_RDWR, 0666);
    SharedData* data = reinterpret_cast<SharedData*>(
        mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED_VALIDATE, fd, 0)
    );
    return data;
}

int main(void){
    const char* name = "/shm1";
    SharedData* data = connectSharedSection(name);

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dist(1, 100); 

    for (int i = 0; i < 10; i++)
    {
        sem_wait(&data -> fullClient);
        sem_wait(&data -> mtx);

        char recFromServer[ITEM_SIZE];
        strcpy(recFromServer, data -> toClient[data -> outClient]);
        data -> outClient = (data -> outClient + 1) % BUF_SIZE;

        sem_post(&data -> mtx);
        sem_post(&data -> emptyClient);

        cout << "Client recieved: " << recFromServer << endl;

        char answer[ITEM_SIZE];

        int num = dist(gen);
        snprintf(answer, ITEM_SIZE, "Message to server %d", num);

        sem_wait(&data -> emptyServer);
        sem_wait(&data -> mtx);

        strcpy(data -> toServer[data -> inServer], answer);
        data -> inServer = (data -> inServer + 1) % BUF_SIZE;

        sem_post(&data -> mtx);
        sem_post(&data -> fullServer);

        sleep(1);
    }
    
    return 0;
}