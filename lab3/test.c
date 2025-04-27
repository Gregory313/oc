// // #include <iostream>
// // #include <cstdlib>
// // #include <cstring>
// // #include <unistd.h>
// // #include <fcntl.h>
// // #include <sys/mman.h>
// // #include <semaphore.h>
// // #include <ctime>
// // #include <random>

// // const int BUF_SIZE = 10;
// // const int ITEM_SIZE = 100;

// // struct SharedData {
// //     char toClient[BUF_SIZE][ITEM_SIZE]; // Буфер для клиента
// //     char toServer[BUF_SIZE][ITEM_SIZE];  // Буфер для сервера
// //     int inClient;                         // Индекс записи клиента
// //     int outClient;                        // Индекс чтения клиента
// //     int inServer;                         // Индекс записи сервера
// //     int outServer;                        // Индекс чтения сервера
// //     sem_t emptyClient;                   // Семафор для клиента
// //     sem_t fullClient;                    // Семафор для клиента
// //     sem_t emptyServer;                   // Семафор для сервера
// //     sem_t fullServer;                    // Семафор для сервера
// //     sem_t mtx;                           // Мьютекс
// // };

// // SharedData* connectSharedSection(const char* name) {
// //     int shMem = shm_open(name, O_RDWR, 0666);
// //     SharedData* data = reinterpret_cast<SharedData*>(mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shMem, 0));
// //     return data;
// // }

// // void exchangeData(SharedData* data) {
// //     std::default_random_engine generator(time(0));
// //     std::uniform_int_distribution<int> distribution(1, 100);


// //     std::random_device rd; 
// //     std::mt19937 gen(rd()); 
// //     std::uniform_int_distribution<> dist(1, 100); 

// //     for (int i = 0; i < 10; ++i) {
// //         // Получить сообщение от сервера
// //         sem_wait(&data->fullClient);
// //         sem_wait(&data->mtx);
        
// //         char receivedFromServer[ITEM_SIZE];
// //         strcpy(receivedFromServer, data->toClient[data->outClient]);
// //         data->outClient = (data->outClient + 1) % BUF_SIZE;
        
// //         sem_post(&data->mtx);
// //         sem_post(&data->emptyClient);

// //         std::cout << "Client received: " << receivedFromServer << std::endl;

// //         // Отправка сообщения серверу
// //         char messageToServer[ITEM_SIZE];

// //         int num = dist(gen);//1 + rand() % 100;
// //         snprintf(messageToServer, ITEM_SIZE, "Message to Server %d from Client", num);
        
// //         sem_wait(&data->emptyServer);
// //         sem_wait(&data->mtx);
        
// //         strcpy(data->toServer[data->inServer], messageToServer);
// //         data->inServer = (data->inServer + 1) % BUF_SIZE;
        
// //         sem_post(&data->mtx);
// //         sem_post(&data->fullServer);

// //         sleep(1); // Задержка для демонстрации
// //     }
// // }

// // int main() {
// //     const char* name = "/shared_sme";
// //     SharedData* data = connectSharedSection(name);
// //     exchangeData(data);
// //     return 0;
// // }



















































// #include <iostream>
// #include <cstdlib>
// #include <cstring>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/mman.h>
// #include <semaphore.h>
// #include <ctime>
// #include <random>

// const int BUF_SIZE = 10;
// const int ITEM_SIZE = 100;

// struct SharedData {
//     char toClient[BUF_SIZE][ITEM_SIZE]; // Буфер для клиента
//     char toServer[BUF_SIZE][ITEM_SIZE];  // Буфер для сервера
//     int inClient;                         // Индекс записи клиента
//     int outClient;                        // Индекс чтения клиента
//     int inServer;                         // Индекс записи сервера
//     int outServer;                        // Индекс чтения сервера
//     sem_t emptyClient;                   // Семафор для клиента
//     sem_t fullClient;                    // Семафор для клиента
//     sem_t emptyServer;                   // Семафор для сервера
//     sem_t fullServer;                    // Семафор для сервера
//     sem_t mtx;                           // Мьютекс
// };

// SharedData* createSharedSection(const char* name) {
//     int shMem = shm_open(name, O_CREAT | O_RDWR, 0666);
//     ftruncate(shMem, sizeof(SharedData));
//     SharedData* data = reinterpret_cast<SharedData*>(mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shMem, 0));

//     sem_init(&data->emptyClient, 1, BUF_SIZE);
//     sem_init(&data->fullClient, 1, 0);
//     sem_init(&data->emptyServer, 1, BUF_SIZE);
//     sem_init(&data->fullServer, 1, 0);
//     sem_init(&data->mtx, 1, 1);

//     data->inClient = 0;
//     data->outClient = 0;
//     data->inServer = 0;
//     data->outServer = 0;

//     return data;
// }

// void destroySharedSection(SharedData* data, const char* name) {
//     sem_destroy(&data->emptyClient);
//     sem_destroy(&data->fullClient);
//     sem_destroy(&data->emptyServer);
//     sem_destroy(&data->fullServer);
//     sem_destroy(&data->mtx);
//     munmap(data, sizeof(SharedData));
//     shm_unlink(name);
// }

// void exchangeData(SharedData* data) {
//     std::default_random_engine generator(time(0));
//     std::uniform_int_distribution<int> distribution(1, 100);

//     for (int i = 0; i < 10; ++i) {
//         // Отправка сообщения клиенту
//         char messageToClient[ITEM_SIZE];
//         snprintf(messageToClient, ITEM_SIZE, "Message to Client %d from Server", i);
        
//         sem_wait(&data->emptyClient);
//         sem_wait(&data->mtx);
        
//         strcpy(data->toClient[data->inClient], messageToClient);
//         data->inClient = (data->inClient + 1) % BUF_SIZE;
        
//         sem_post(&data->mtx);
//         sem_post(&data->fullClient);

//         // Ожидание ответа от клиента
//         sem_wait(&data->fullServer);
//         sem_wait(&data->mtx);
        
//         char receivedFromClient[ITEM_SIZE];
//         strcpy(receivedFromClient, data->toServer[data->outServer]);
//         data->outServer = (data->outServer + 1) % BUF_SIZE;
        
//         sem_post(&data->mtx);
//         sem_post(&data->emptyServer);

//         std::cout << "Server received: " << receivedFromClient << std::endl;

//         sleep(1); // Задержка для демонстрации
//     }
// }

// int main() {
//     const char* name = "/shm1";
//     SharedData* data = createSharedSection(name);
//     exchangeData(data);
//     destroySharedSection(data, name);
//     return 0;
// }