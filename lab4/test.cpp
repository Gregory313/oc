// // // // #include <stdio.h>
// // // // #include <string>
// // // // #include <vector>
// // // // #include <limits.h>  
// // // // #include <iostream>
// // // // #include <fstream>
// // // // #include <pthread.h>

// // // // #define PROC_NUM 8

// // // // using namespace std;

// // // // struct Process{
// // // //     vector<int> frames;
// // // //     string name;
// // // //     unsigned int pageSize;
// // // //     unsigned int faults;
// // // // };

// // // // struct Frame{
// // // //     string proccess; //имя процесса
// // // //     int num; // номер процесса к которому принадлежит фрейм
// // // // };

// // // // struct Mem{
// // // //     vector<Frame> *frames;
// // // //     vector<int> *counts;
// // // // };

// // // // struct Command{
// // // //     int rw;
// // // //     Frame *frame;
// // // //     int slot;
// // // //     Mem mem;
// // // // };

// // // // struct DiskArgs
// // // // {
// // // //     Command *cmd;
// // // // };

// // // // struct HandlerArg
// // // // {
// // // //     Mem *memory;
// // // //     Frame *frame;
// // // //     Command *disk_command;
// // // // };

// // // // struct RepPage{
// // // //     Mem *mem;
// // // //     Command *cmd;
// // // // };

// // // // vector<string> getInfo(string line){
// // // //     vector<string> list;
// // // //     if(line.size() == 0) return list;

// // // //     int end = line.find(" ");
// // // //     if(end != string::npos){
// // // //         list.push_back(line.substr(0, end));
// // // //         vector<string> s_list = getInfo(line.substr(end + 1, line.size()));
// // // //         if(s_list.size() != 0){
// // // //             list.insert(list.end(), s_list.begin(), s_list.end());
// // // //         }
// // // //     }else{
// // // //         end = line.size();
// // // //         list.push_back(line.substr(0, end));
// // // //     }
// // // //     return list;
// // // // }

// // // // Process getProc(string name, vector<Process> &processes){
// // // //     for (int i = 0; i < processes.size(); i++)
// // // //     {
// // // //         if(name == processes[i].name){
// // // //             return processes[i];
// // // //         }
// // // //     }
// // // // }

// // // // void accessMemory(Frame *frame, Mem *mem, int slot, int rw){
// // // //     if(rw == 0){
// // // //         mem -> frames -> operator[](slot) = *frame;
// // // //     }else{
// // // //         mem -> frames -> operator[](slot).num = -1;
// // // //         mem -> frames -> operator[](slot).proccess = "";
// // // //     }
// // // // }

// // // // int maxCountSlot(Mem *mem){
// // // //     int max = 0;
// // // //     int slot = 0;
// // // //     for (int i = 0; i < mem -> counts ->size(); i++)
// // // //     {
// // // //         if(mem -> counts -> operator[](i) > max){
// // // //             max = mem -> counts -> operator[](i);
// // // //             slot = i;
// // // //         }
// // // //     }
// // // //     return slot;    
// // // // }

// // // // int freeSlots(Mem *mem){
// // // //     int count = 0;
// // // //     for (int i = 0; i < mem -> frames ->size(); i++)
// // // //     {
// // // //         if(mem -> frames -> operator[](i).proccess.length() == 0){
// // // //             count++;
// // // //         }
// // // //     }
// // // //     return count;
// // // // }


// // // // void replacePage(Mem *mem, Command *cmd, Frame *frame){
// // // //     int freeSlotsNum = freeSlots(mem);
// // // //     while(freeSlotsNum > 4)
// // // //     {
// // // //         freeSlotsNum = freeSlots(mem);
// // // //     }

// // // //     cmd -> frame = frame;
// // // //     cmd -> rw = 1;
// // // //     cmd -> slot = maxCountSlot(mem);
// // // //     cmd -> mem = *mem;
// // // // }

// // // // unsigned int numInBits(unsigned int n){
// // // //     unsigned int count = 0;
// // // //     while(n){
// // // //         count ++;
// // // //         n >>= 1;
// // // //     }
// // // //     return count;
// // // // }

// // // // unsigned int countBits(unsigned int n) 
// // // // { 
// // // //    unsigned int count = 0; 
// // // //    while (n) 
// // // //    { 
// // // //         count++; 
// // // //         n /= 2; 
// // // //     } 
// // // //     return count; 
// // // // } 


// // // // void updateProcesses(Process process, std::vector<Process> &processes)
// // // // {
// // // //     for(int i= 0; i < processes.size(); i++)
// // // //     {
// // // //         if(process.name == processes[i].name)
// // // //         {
// // // //             processes[i] = process;
// // // //             return;
// // // //         }
// // // //     }
// // // // }


// // // // int pageInMemory(std::string name, int page, const Mem *memory)
// // // // {
// // // //     cout << " DD " << name << " page " << page << endl;
// // // //     for(int i= 0; i < memory->frames->size(); i++)
// // // //     {

// // // //         if(name == memory->frames->operator[](i).proccess && page == memory->frames->operator[](i).num )
// // // //         {
// // // //             cout << " !!! " << endl;
// // // //             return 1;
// // // //         }
// // // //     }
// // // //     cout << " ??? " << endl;
// // // //     return -1;
// // // // }

// // // // void memorySweepFIFO(Mem *memory)
// // // // {
// // // //     for(int i= 0; i < memory->counts->size(); i++)
// // // //     {
// // // //         memory->counts->operator[](i)++;
// // // //     }
// // // // }

// // // // int main(void){
// // // //     ifstream file("input.txt");
// // // //     string line;
// // // //     vector<vector<string>> simData;

// // // //     while (getline(file, line))
// // // //     {
// // // //         vector<string> list = getInfo(line);
// // // //         simData.push_back(list);
// // // //     }

// // // //     for (const auto& list : simData) {
// // // //         for (const auto& word : list) {
// // // //             std::cout << word << " || "; 
// // // //         }
// // // //         std::cout << std::endl; 
// // // //     }
    
// // // //     int memSize = stoi(simData[0][0]);
// // // //     cout << memSize << " frames in mem\n";
// // // //     vector<Frame> *frames = new vector<Frame>(memSize);
// // // //     vector<int> *counts = new vector<int>(memSize);

// // // //     for (int i = 0; i < memSize; i++){
// // // //         Frame frame;
// // // //         frame.proccess = "";
// // // //         frame.num = -1;
// // // //         frames -> operator[](i) = frame;
// // // //         counts -> operator[](i) = 0;
// // // //     }

// // // //     Mem *mem = new Mem;
// // // //     mem -> frames = frames;
// // // //     mem -> counts = counts;     
    
// // // //     int procNum = PROC_NUM;
// // // //     cout << procNum << " proc nums\n";

// // // //     vector<Process> procs;

// // // //     for(int i = 0; i < procNum; i++){
// // // //         Process proc;
// // // //         proc.faults = 0;
// // // //         proc.name = simData[6 + i + 1][0]; 
// // // //         cout << proc.name << " proc name\n";
// // // //         proc.pageSize = stoi(simData[6+1+i][1]);
// // // //         procs.push_back(proc);
// // // //     }

// // // //     DiskArgs *dkArgs = new DiskArgs;
// // // //     Command *cmd = new Command;
// // // //     dkArgs -> cmd = cmd;

// // // //     HandlerArg *hndlr = new HandlerArg;
// // // //     Frame *missing_frame = new Frame;
// // // //     hndlr->memory = mem;
// // // //     hndlr->frame = missing_frame;
// // // //     hndlr->disk_command = dkArgs->cmd;


// // // //     RepPage *rPage = new RepPage;
// // // //     rPage -> mem = mem;
// // // //     rPage -> cmd = dkArgs -> cmd;

// // // //     int pageSize = stoi(simData[1][0]);
// // // //     cout << "page size: " << pageSize << '\n';
// // // //     for( int i = 6+procNum+1; i < simData.size(); i++)
// // // //     {
// // // //         Process process = getProc(simData[i][0], procs);
// // // //         if (std::stoi(simData[i][1], 0, 16 )==-1) 
// // // //         {
// // // //             continue;
// // // //             std::cout << "process died \n";
// // // //         }
// // // //         int page = 7;//std::stoi(simData[i][1], 0, 16 ) >> (countBits(pageSize)-1);
// // // //         printf("dddd %d \n",  page);
// // // //         cout << " DDD " << simData[i][1] << endl;
// // // //         if(-1==pageInMemory(process.name, page, mem))
// // // //         {
// // // //             missing_frame->num = page;
// // // //             missing_frame->proccess = process.name;process.faults++;
// // // //             updateProcesses(process, procs);
// // // //             memorySweepFIFO(mem);

// // // //         }else{
// // // //             printf("<<<<<<<<<<<<<<<<<<<< \n");
// // // //         }
// // // //     }
    

// // // //     int total = 0;
// // // //     for(auto process: procs)
// // // //     {
// // // //         std::cout << "faults from process " << process.name << " :" << process.faults << " \n";
// // // //         total += process.faults;
// // // //     }
// // // //     std::cout << "total faults: " << total << " \n";

// // // //     return 0;
// // // // }























// // // // // #include <stdio.h>
// // // // // #include <string>
// // // // // #include <vector>
// // // // // #include <limits.h>  
// // // // // #include <iostream>
// // // // // #include <fstream>
// // // // // #include <pthread.h>


// // // // // #define PROC_NUM 8

// // // // // using namespace std;


// // // // // struct Page{
// // // // //     unsigned int num;
// // // // //     string process;
// // // // //     int frame; 
// // // // // };

// // // // // struct Process{
// // // // //     vector<int> pages;
// // // // //     string name;
// // // // //     unsigned int pageSize;
// // // // //     unsigned int faults;
// // // // // };


// // // // // struct Memory{
// // // // //     vector<Page> *pages;
// // // // //     vector<int> *num;
// // // // // };

// // // // // struct Command{
// // // // //     int rw;
// // // // //     Page *page;
// // // // //     int slots;
// // // // // };

// // // // // struct QueueCommands{
// // // // //     Command *cmd;
// // // // // };

// // // // // struct ReplacePage{
// // // // //     Memory *memory;
// // // // //     Command *cmd;
// // // // // };

// // // // // struct Handler
// // // // // {
// // // // //     Memory *memory;
// // // // //     Page *page;
// // // // //     Command *cmd;
// // // // // };


// // // // // vector<string> getInfo(string line){
// // // // //     vector<string> list;
// // // // //     if(line.size() == 0) return list;

// // // // //     int end = line.find(" ");
// // // // //     if(end != string::npos){
// // // // //         list.push_back(line.substr(0, end));
// // // // //         vector<string> s_list = getInfo(line.substr(end + 1, line.size()));
// // // // //         if(s_list.size() != 0){
// // // // //             list.insert(list.end(), s_list.begin(), s_list.end());
// // // // //         }
// // // // //     }else{
// // // // //         end = line.size();
// // // // //         list.push_back(line.substr(0, end));
// // // // //     }
// // // // //     return list;
// // // // // }

// // // // // Process getProc(string name, vector<Process> &procs){
// // // // //     for (int i = 0; i < procs.size(); i++)
// // // // //     {
// // // // //         if(name == procs[i].name){
// // // // //             return procs[i];
// // // // //         }
// // // // //     }
    
// // // // // }

// // // // // void initPages(vector<Page> *pages, int i){
// // // // //     Page page;
// // // // //     page.process = "";
// // // // //     page.num = -1;
// // // // //     page.frame = 0;
// // // // //     pages -> operator[](i) = page;
// // // // // }


// // // // // int pageInMemory(const Memory *mem, int page, string name){
// // // // //     for (int i = 0; i < mem -> pages -> size(); i++)
// // // // //     {
// // // // //         if(name == mem -> pages -> operator[](i).process && page == page == mem->pages->operator[](i).num){
// // // // //             return 1;
// // // // //         }
// // // // //     }
// // // // //     return -1;
// // // // // }

// // // // // unsigned int countBits(unsigned int n) { 
// // // // //    unsigned int count = 0; 
// // // // //    while (n) 
// // // // //    { 
// // // // //         count++; 
// // // // //         n /= 2; 
// // // // //     } 
// // // // //     return count; 
// // // // // } 

// // // // // void updateProcesses(Process process, vector<Process> &procs){
// // // // //     for(int i= 0; i < procs.size(); i++)
// // // // //     {
// // // // //         if(process.name == procs[i].name)
// // // // //         {
// // // // //             procs[i] = process;
// // // // //             return;
// // // // //         }
// // // // //     }
// // // // // }

// // // // // void memorySweepFIFO(Memory *memory){
// // // // //     for(int i= 0; i < memory->num->size(); i++)
// // // // //     {
// // // // //         memory->num->operator[](i)++;
// // // // //     }
// // // // // }




// // // // // void splitAddress(const std::string &hexAddress, unsigned long &pageNumber, unsigned long &offset) {
// // // // //     std::string pageHex = hexAddress.substr(0, 4); 
// // // // //     std::string offsetHex = hexAddress.substr(4, 16); 

// // // // //     pageNumber = std::stoul(pageHex, nullptr, 16);
// // // // //     offset = std::stoul(offsetHex, nullptr, 16); 
// // // // // }




// // // // // void translateVirtToPhisycs(int page, vector<Page> &pages, string process, unsigned long offset, unsigned long addr){
// // // // //     if (offset >= 4096) {
// // // // //         cerr << "Ошибка: Смещение выходит за пределы страницы." << endl;
// // // // //         addr -1;
// // // // //     }

// // // // //     for (size_t i = 0; i < pages.size(); i++) {
// // // // //         if (pages[i].num == page && pages[i].process == process) { 
// // // // //             addr = pages[i].frame + offset; 
// // // // //         }
// // // // //     }

// // // // // }

// // // // // int main(void){

// // // // //     ifstream file("input.txt");
// // // // //     string line;
// // // // //     vector<vector<string>> simData;

// // // // //     while (getline(file, line))
// // // // //     {
// // // // //         vector<string> list = getInfo(line);
// // // // //         simData.push_back(list);
// // // // //     }

// // // // //     int memSize = 8;
    
// // // // //     vector<Page> *pages = new vector<Page>(memSize);
// // // // //     vector<int> *counts = new vector<int>(memSize);

// // // // //     for (int i = 0; i < memSize; i++){
// // // // //         initPages(pages, i);
// // // // //         counts -> operator[](i) = 0;
// // // // //     }

// // // // //     Memory *mem = new Memory;
// // // // //     mem -> pages = pages;
// // // // //     mem -> num = counts;

// // // // //     int procLimit = 5;

// // // // //     vector<Process> procs;

// // // // //     for (int i = 0; i < procLimit; i++)
// // // // //     {
// // // // //         Process proc;
// // // // //         proc.faults = 0;
// // // // //         proc.name = simData[6 + i + 1][0];

// // // // //         cout << proc.name << " proc name\n";

// // // // //         proc.pageSize = stoi(simData[6+1+i][1]);
// // // // //         procs.push_back(proc);
// // // // //     }
    
// // // // //     QueueCommands *qCmd = new QueueCommands;
// // // // //     Command *cmd = new Command;

// // // // //     qCmd -> cmd = cmd;

// // // // //     Handler *mHndlr = new Handler;
// // // // //     Page *mPage = new Page;

// // // // //     mHndlr -> memory = mem;
// // // // //     mHndlr -> page = mPage;
// // // // //     mHndlr -> cmd = qCmd -> cmd;

// // // // //     ReplacePage *rPage = new ReplacePage;
// // // // //     rPage -> memory = mem;
// // // // //     rPage -> cmd = qCmd -> cmd;

// // // // //     int pageSize = stoi(simData[1][0]);

// // // // //     unsigned long pageNumber = 0;
// // // // //     unsigned long offset = 0;
// // // // //     unsigned long addr = 0;
// // // // //     string hexAddress;
    
// // // // //     for (int i = 6+ procLimit +1; i < simData.size(); i++)
// // // // //     {
// // // // //         Process proc = getProc(simData[i][1], procs);
// // // // //         int page = std::stoi(simData[i][1], 0, 16) / (countBits(pageSize) - 1);
// // // // //         cout << " SSSSS " << page << endl;
// // // // //         hexAddress = "00001234567890AB";

// // // // //         splitAddress(hexAddress, pageNumber, offset);

// // // // //         if(pageInMemory(mem, pageNumber, proc.name) == 1){
// // // // //             translateVirtToPhisycs(pageNumber, *pages, proc.name, offset, addr);
// // // // //             cout << " Virt address " << hexAddress << " from page " << pageNumber <<" Physic address" << addr << endl;
// // // // //         }else{
// // // // //             mPage -> num = pageNumber;
// // // // //             mPage -> process = proc.name;
// // // // //             proc.faults++;
// // // // //             updateProcesses(proc, procs);
// // // // //             memorySweepFIFO(mem);
// // // // //         }
        
// // // // //     }
    

// // // // //     int total = 0;
// // // // //     for(auto process: procs)
// // // // //     {
// // // // //         std::cout << "faults from process " << process.name << " :" << process.faults << " \n";
// // // // //         total += process.faults;
// // // // //     }
// // // // //     std::cout << "total faults: " << total << " \n";

// // // // //     return 0;
// // // // // }









































// // // #include <stdio.h>
// // // #include <string>
// // // #include <vector>
// // // #include <limits.h>  // for INT_MAX
// // // #include <iostream>
// // // #include <fstream>

// // // std::vector<std::string> getStringParts(std::string line)
// // // {
// // //     std::vector<std::string> list;
// // //     if (line.size() == 0) return list;
// // //     int end = line.find(' ');
// // //     if (end != std::string::npos)
// // //     {
// // //         list.push_back(line.substr(0, end));
// // //         std::vector<std::string> sub_list = getStringParts(line.substr(end + 1, line.size()));
// // //         if (sub_list.size() != 0)
// // //             list.insert(list.end(), sub_list.begin(), sub_list.end());
// // //     }
// // //     else
// // //     {
// // //         end = line.size();
// // //         list.push_back(line.substr(0, end));
// // //     }
// // //     return list;
// // // }

// // // struct Frame
// // // {
// // //     std::string process;
// // //     int number;
// // // };

// // // struct Memory
// // // {
// // //     std::vector<Frame> *frames;
// // //     std::vector<int> *counts;
// // // };

// // // struct Process
// // // {
// // //     std::vector<int> frames;
// // //     std::string name;
// // //     unsigned int page_size;
// // //     unsigned int faults;
// // // };

// // // Process getProcess(std::string name, std::vector<Process> &processes)
// // // {
// // //     for (int i = 0; i < processes.size(); i++)
// // //     {
// // //         if (name == processes[i].name)
// // //         {
// // //             return processes[i];
// // //         }
// // //     }
// // // }

// // // unsigned int countBits(unsigned int n)
// // // {
// // //     unsigned int count = 0;
// // //     while (n)
// // //     {
// // //         count++;
// // //         n >>= 1;
// // //     }
// // //     return count;
// // // }

// // // void modifyMemory(Frame *frame, Memory *memory, int slot, int rw)
// // // {
// // //     if (rw == 0)
// // //     {
// // //         memory->frames->operator[](slot) = *frame;
// // //     }
// // //     else
// // //     {
// // //         memory->frames->operator[](slot).number = -1;
// // //         memory->frames->operator[](slot).process = "";
// // //     }
// // // }

// // // int getFreeFrame(const Memory *memory)
// // // {
// // //     for (int i = 0; i < memory->frames->size(); i++)
// // //     {
// // //         if (memory->frames->operator[](i).process.length() == 0)
// // //         {
// // //             return i;
// // //         }
// // //     }
// // //     return -1;
// // // }

// // // int maxCountSlot(Memory *memory)
// // // {
// // //     int max = 0;
// // //     int slot = 0;
// // //     for (int i = 0; i < memory->counts->size(); i++)
// // //     {
// // //         if (memory->counts->operator[](i) > max)
// // //         {
// // //             max = memory->counts->operator[](i);
// // //             slot = i;
// // //         }
// // //     }
// // //     return slot;
// // // }

// // // int freeSlots(Memory *memory)
// // // {
// // //     int count = 0;
// // //     for (int i = 0; i < memory->frames->size(); i++)
// // //     {
// // //         if (memory->frames->operator[](i).process.length() == 0)
// // //         {
// // //             count++;
// // //         }
// // //     }
// // //     return count;
// // // }

// // // void memorySweepFIFO(Memory *memory)
// // // {
// // //     for (int i = 0; i < memory->counts->size(); i++)
// // //     {
// // //         memory->counts->operator[](i)++;
// // //     }
// // // }

// // // int pageInMemory(std::string name, int page, const Memory *memory)
// // // {
// // //     for (int i = 0; i < memory->frames->size(); i++)
// // //     {
// // //         if (name == memory->frames->operator[](i).process && page == memory->frames->operator[](i).number)
// // //         {
// // //             return 1;
// // //         }
// // //     }
// // //     return -1;
// // // }

// // // void updateProcesses(Process process, std::vector<Process> &processes)
// // // {
// // //     for (int i = 0; i < processes.size(); i++)
// // //     {
// // //         if (process.name == processes[i].name)
// // //         {
// // //             processes[i] = process;
// // //             return;
// // //         }
// // //     }
// // // }

// // // int main()
// // // {
// // //     std::ifstream file("input.txt");
// // //     std::string line;
// // //     std::vector<std::vector<std::string>> sim_data;

// // //     while (std::getline(file, line))
// // //     {
// // //         std::vector<std::string> list = getStringParts(line);
// // //         sim_data.push_back(list);
// // //     }

// // //     // Create the simulator
// // //     // Initialize memory
// // //     int memory_size = std::stoi(sim_data[0][0]);
// // //     std::vector<Frame> *frames = new std::vector<Frame>(memory_size);
// // //     std::vector<int> *counts = new std::vector<int>(memory_size);
// // //     std::cout << "Total frames in memory: " << memory_size << '\n';

// // //     for (int i = 0; i < memory_size; i++)
// // //     {
// // //         Frame frame;
// // //         frame.process = "";
// // //         frame.number = -1;
// // //         frames->operator[](i) = frame;
// // //         counts->operator[](i) = 0;
// // //     }

// // //     Memory *memory = new Memory;
// // //     memory->frames = frames;
// // //     memory->counts = counts;

// // //     // Create the processes
// // //     int process_number = std::stoi(sim_data[6][0]);
// // //     std::cout << "Number of processes: " << process_number << '\n';
// // //     std::vector<Process> processes;

// // //     for (int i = 0; i < process_number; i++)
// // //     {
// // //         Process process;
// // //         process.faults = 0;
// // //         process.page_size = std::stoi(sim_data[6 + 1 + i][1]);
// // //         process.name = sim_data[6 + 1 + i][0];
// // //         processes.push_back(process);
// // //     }

// // //     // Run simulation
// // //     int page_size = std::stoi(sim_data[1][0]);
// // //     std::cout << "Page size: " << page_size << '\n';

// // //     for (int i = 6 + process_number + 1; i < sim_data.size(); i++)
// // //     {
// // //         Process process = getProcess(sim_data[i][0], processes);
// // //         if (std::stoi(sim_data[i][1], 0, 16) == -1)
// // //         {
// // //             continue;
// // //         }

// // //         int page = std::stoi(sim_data[i][1], 0, 16) >> (countBits(page_size) - 1);
// // //         if (-1 == pageInMemory(process.name, page, memory))
// // //         {
// // //             Frame missing_frame;
// // //             missing_frame.number = page;
// // //             missing_frame.process = process.name;

// // //             int free_frame = getFreeFrame(memory);
// // //             if (free_frame == -1)
// // //             {
// // //                 free_frame = maxCountSlot(memory);
// // //                 modifyMemory(&missing_frame, memory, free_frame, 1); // Write to disk
// // //             }
// // //             else
// // //             {
// // //                 modifyMemory(&missing_frame, memory, free_frame, 0); // Read from disk
// // //             }

// // //             process.faults++;
// // //             updateProcesses(process, processes);
// // //             memorySweepFIFO(memory);
// // //             printf("1111111111111111111111111111111111111111111\n");
// // //         }else{
// // //             printf("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS\n");
// // //         }
// // //     } // end of simulation loop

// // //     int total = 0;
// // //     for (auto process : processes)
// // //     {
// // //         std::cout << "Faults from process " << process.name << " :" << process.faults << " \n";
// // //         total += process.faults;
// // //     }
// // //     std::cout << "Total faults: " << total << " \n";

// // //     delete frames;
// // //     delete counts;
// // //     delete memory;

// // //     return 0;
// // // }


























// // #include <stdio.h>
// // #include <string>
// // #include <vector>
// // #include <limits.h>  // for INT_MAX
// // #include <iostream>
// // #include <fstream>

// // using namespace std;

// // std::vector<std::string> getStringParts(std::string line)
// // {
// //     std::vector<std::string> list;
// //     if (line.size() == 0) return list;
// //     int end = line.find(' ');
// //     if (end != std::string::npos)
// //     {
// //         list.push_back(line.substr(0, end));
// //         std::vector<std::string> sub_list = getStringParts(line.substr(end + 1, line.size()));
// //         if (sub_list.size() != 0)
// //             list.insert(list.end(), sub_list.begin(), sub_list.end());
// //     }
// //     else
// //     {
// //         end = line.size();
// //         list.push_back(line.substr(0, end));
// //     }
// //     return list;
// // }

// // struct Frame
// // {
// //     std::string process;
// //     int number;
// // };

// // struct Memory
// // {
// //     std::vector<Frame> *frames;
// //     std::vector<int> *counts;
// // };

// // struct Process
// // {
// //     std::vector<int> frames;
// //     std::string name;
// //     unsigned int page_size;
// //     unsigned int faults;
// // };

// // Process getProcess(std::string name, std::vector<Process> &processes)
// // {
// //     for (int i = 0; i < processes.size(); i++)
// //     {
// //         if (name == processes[i].name)
// //         {
// //             return processes[i];
// //         }
// //     }
// // }

// // unsigned int countBits(unsigned int n)
// // {
// //     unsigned int count = 0;
// //     while (n)
// //     {
// //         count++;
// //         n >>= 1;
// //     }
// //     return count;
// // }

// // void modifyMemory(Frame *frame, Memory *memory, int slot, int rw)
// // {
// //     if (rw == 0)
// //     {
// //         memory->frames->operator[](slot) = *frame;
// //     }
// //     else
// //     {
// //         memory->frames->operator[](slot).number = -1;
// //         memory->frames->operator[](slot).process = "";
// //     }
// // }

// // int getFreeFrame(const Memory *memory)
// // {
// //     for (int i = 0; i < memory->frames->size(); i++)
// //     {
// //         if (memory->frames->operator[](i).process.length() == 0)
// //         {
// //             return i;
// //         }
// //     }
// //     return -1;
// // }

// // int maxCountSlot(Memory *memory)
// // {
// //     int max = 0;
// //     int slot = 0;
// //     for (int i = 0; i < memory->counts->size(); i++)
// //     {
// //         if (memory->counts->operator[](i) > max)
// //         {
// //             max = memory->counts->operator[](i);
// //             slot = i;
// //         }
// //     }
// //     return slot;
// // }

// // int freeSlots(Memory *memory)
// // {
// //     int count = 0;
// //     for (int i = 0; i < memory->frames->size(); i++)
// //     {
// //         if (memory->frames->operator[](i).process.length() == 0)
// //         {
// //             count++;
// //         }
// //     }
// //     return count;
// // }

// // void memorySweepFIFO(Memory *memory)
// // {
// //     for (int i = 0; i < memory->counts->size(); i++)
// //     {
// //         memory->counts->operator[](i)++;
// //     }
// // }

// // int pageInMemory(std::string name, int page, const Memory *memory)
// // {
// //     for (int i = 0; i < memory->frames->size(); i++)
// //     {
// //         if (name == memory->frames->operator[](i).process && page == memory->frames->operator[](i).number)
// //         {
// //             return i; // Return the index of the frame
// //         }
// //     }
// //     return -1;
// // }

// // void updateProcesses(Process process, std::vector<Process> &processes)
// // {
// //     for (int i = 0; i < processes.size(); i++)
// //     {
// //         if (process.name == processes[i].name)
// //         {
// //             processes[i] = process;
// //             return;
// //         }
// //     }
// // }




// // unsigned long translateToPhysicalAddress(int page, unsigned long offset, Memory *memory) {
// //     // Проверка на выход за пределы страницы
// //     if (offset >= 4096) {
// //         cerr << "Ошибка: Смещение выходит за пределы страницы." << endl;
// //         return -1; // Возвращаем недопустимый адрес
// //     }

// //     for (size_t i = 0; i < memory->frames->size(); i++) {
// //         if (memory->frames->operator[](i).number == page) {
// //             // Предполагается, что memory->frames->operator[](i).frame содержит базовый адрес фрейма
// //             unsigned long baseAddress = memory->frames->operator[](i).number; 
// //             return baseAddress + offset; // Рассчитываем физический адрес, добавляя смещение к базовому адресу
// //         }
// //     }

// //     cerr << "Ошибка: Страница не найдена для номера страницы " << page << "." << endl;
// //     return -1; // Возвращаем недопустимый адрес, если страница не найдена
// // }




// // int main()
// // {
// //     std::ifstream file("input.txt");
// //     std::string line;
// //     std::vector<std::vector<std::string>> sim_data;

// //     while (std::getline(file, line))
// //     {
// //         std::vector<std::string> list = getStringParts(line);
// //         sim_data.push_back(list);
// //     }

// //     // Create the simulator
// //     // Initialize memory
// //     int memory_size = std::stoi(sim_data[0][0]);
// //     std::vector<Frame> *frames = new std::vector<Frame>(memory_size);
// //     std::vector<int> *counts = new std::vector<int>(memory_size);
// //     std::cout << "Total frames in memory: " << memory_size << '\n';

// //     for (int i = 0; i < memory_size; i++)
// //     {
// //         Frame frame;
// //         frame.process = "";
// //         frame.number = -1;
// //         frames->operator[](i) = frame;
// //         counts->operator[](i) = 0;
// //     }

// //     Memory *memory = new Memory;
// //     memory->frames = frames;
// //     memory->counts = counts;

// //     // Create the processes
// //     int process_number = std::stoi(sim_data[6][0]);
// //     std::cout << "Number of processes: " << process_number << '\n';
// //     std::vector<Process> processes;

// //     for (int i = 0; i < process_number; i++)
// //     {
// //         Process process;
// //         process.faults = 0;
// //         process.page_size = std::stoi(sim_data[6 + 1 + i][1]);
// //         process.name = sim_data[6 + 1 + i][0];
// //         processes.push_back(process);
// //     }

// //     // Run simulation
// //     int page_size = std::stoi(sim_data[1][0]);
// //     std::cout << "Page size: " << page_size << '\n';

// //     for (int i = 6 + process_number + 1; i < sim_data.size(); i++)
// //     {
// //         Process process = getProcess(sim_data[i][0], processes);
// //         if (std::stoi(sim_data[i][1], 0, 16) == -1)
// //         {
// //             continue;
// //         }

// //         unsigned long address = std::stoul(sim_data[i][1], nullptr, 16);
// //         int page = address >> (countBits(page_size) - 1); // Get the page number
// //         unsigned long offset = address & (page_size - 1); // Get the offset

// //         int frame_index = pageInMemory(process.name, page, memory);
// //         if (frame_index == -1)
// //         {
// //             // Page fault handling
// //             Frame missing_frame;
// //             missing_frame.number = page;
// //             missing_frame.process = process.name;

// //             int free_frame = getFreeFrame(memory);
// //             if (free_frame == -1)
// //             {
// //                 free_frame = maxCountSlot(memory);
// //                 modifyMemory(&missing_frame, memory, free_frame, 1); // Write to disk
// //             }
// //             else
// //             {
// //                 modifyMemory(&missing_frame, memory, free_frame, 0); // Read from disk
// //             }

// //             process.faults++;
// //             updateProcesses(process, processes);
// //             memorySweepFIFO(memory);
// //         }
// //         else
// //         {
// //             // Page is in memory, convert virtual address to physical address
// //             unsigned long physical_address = translateToPhysicalAddress(page, offset, memory);
// //             std::cout << "Virtual address: " << std::hex << address << " translates to Physical address: " << physical_address << std::dec << '\n';
// //         }
// //     } // end of simulation loop

// //     int total = 0;
// //     for (auto process : processes)
// //     {
// //         std::cout << "Faults from process " << process.name << " :" << process.faults << " \n";
// //         total += process.faults;
// //     }
// //     std::cout << "Total faults: " << total << " \n";

// //     delete frames;
// //     delete counts;
// //     delete memory;

// //     return 0;
// // }





































// #include <stdio.h>
// #include <string>
// #include <vector>
// #include <limits.h>  // for INT_MAX
// #include <iostream>
// #include <fstream>

// using namespace std;

// std::vector<std::string> getStringParts(std::string line)
// {
//     std::vector<std::string> list;
//     if (line.size() == 0) return list;
//     int end = line.find(' ');
//     if (end != std::string::npos)
//     {
//         list.push_back(line.substr(0, end));
//         std::vector<std::string> sub_list = getStringParts(line.substr(end + 1, line.size()));
//         if (sub_list.size() != 0)
//             list.insert(list.end(), sub_list.begin(), sub_list.end());
//     }
//     else
//     {
//         end = line.size();
//         list.push_back(line.substr(0, end));
//     }
//     return list;
// }

// struct Page
// {
//     std::string process; // Имя процесса
//     int number;          // Номер страницы
//     int frame;           // Номер фрейма, в котором хранится страница
// };

// struct Memory
// {
//     std::vector<Page> *pages;  // Вектор страниц
//     std::vector<int> *counts;   // Счетчики использования страниц
// };

// struct Process
// {
//     std::vector<int> pages;    // Список фреймов
//     std::string name;           // Имя процесса
//     unsigned int page_size;     // Размер страницы
//     unsigned int faults;        // Количество страничных ошибок
// };

// Process getProcess(std::string name, std::vector<Process> &processes)
// {
//     for (int i = 0; i < processes.size(); i++)
//     {
//         if (name == processes[i].name)
//         {
//             return processes[i];
//         }
//     }
// }

// unsigned int countBits(unsigned int n)
// {
//     unsigned int count = 0;
//     while (n)
//     {
//         count++;
//         n >>= 1;
//     }
//     return count;
// }

// void modifyMemory(Page *page, Memory *memory, int slot, int rw)
// {
//     if (rw == 0) // Чтение
//     {
//         memory->pages->operator[](slot) = *page;
//     }
//     else // Запись
//     {
//         memory->pages->operator[](slot).number = -1;
//         memory->pages->operator[](slot).process = "";
//         memory->pages->operator[](slot).frame = -1; // Сбрасываем номер фрейма
//     }
// }

// int getFreeFrame(const Memory *memory)
// {
//     for (int i = 0; i < memory->pages->size(); i++)
//     {
//         if (memory->pages->operator[](i).process.length() == 0)
//         {
//             return i;
//         }
//     }
//     return -1;
// }

// int maxCountSlot(Memory *memory)
// {
//     int max = 0;
//     int slot = 0;
//     for (int i = 0; i < memory->counts->size(); i++)
//     {
//         if (memory->counts->operator[](i) > max)
//         {
//             max = memory->counts->operator[](i);
//             slot = i;
//         }
//     }
//     return slot;
// }

// int freeSlots(Memory *memory)
// {
//     int count = 0;
//     for (int i = 0; i < memory->pages->size(); i++)
//     {
//         if (memory->pages->operator[](i).process.length() == 0)
//         {
//             count++;
//         }
//     }
//     return count;
// }

// void memorySweepFIFO(Memory *memory)
// {
//     for (int i = 0; i < memory->counts->size(); i++)
//     {
//         memory->counts->operator[](i)++;
//     }
// }

// int pageInMemory(std::string name, int page, const Memory *memory)
// {
//     for (int i = 0; i < memory->pages->size(); i++)
//     {
//         if (name == memory->pages->operator[](i).process && page == memory->pages->operator[](i).number)
//         {
//             return i; // Возвращаем индекс страницы
//         }
//     }
//     return -1;
// }

// void updateProcesses(Process process, std::vector<Process> &processes)
// {
//     for (int i = 0; i < processes.size(); i++)
//     {
//         if (process.name == processes[i].name)
//         {
//             processes[i] = process;
//             return;
//         }
//     }
// }

// unsigned long translateToPhysicalAddress(int page, unsigned long offset, Memory *memory) {
//     for (size_t i = 0; i < memory->pages->size(); i++) {
//         if (memory->pages->operator[](i).number == page) {
//             int frame = memory->pages->operator[](i).frame; // Получаем номер фрейма
//             // Предполагается, что фреймы имеют фиксированный размер, например, 4096 байт
//             unsigned long baseAddress = frame * 4096; // Рассчитываем базовый адрес фрейма
//             return baseAddress + offset; // Рассчитываем физический адрес, добавляя смещение к базовому адресу
//         }
//     }

//     cerr << "Ошибка: Страница не найдена для номера страницы " << page << "." << endl;
//     return -1; // Возвращаем недопустимый адрес, если страница не найдена
// }

// int main()
// {
//     std::ifstream file("input.txt");
//     std::string line;
//     std::vector<std::vector<std::string>> sim_data;

//     while (std::getline(file, line))
//     {
//         std::vector<std::string> list = getStringParts(line);
//         sim_data.push_back(list);
//     }

//     // Создаем симулятор и инициализируем память
//     int memory_size = std::stoi(sim_data[0][0]);
//     std::vector<Page> *pages = new std::vector<Page>(memory_size);
//     std::vector<int> *counts = new std::vector<int>(memory_size);
//     std::cout << "Total pages in memory: " << memory_size << '\n';

//     for (int i = 0; i < memory_size; i++)
//     {
//         Page page;
//         page.process = "";
//         page.number = -1;
//         page.frame = -1; // Инициализируем номер фрейма
//         pages->operator[](i) = page;
//         counts->operator[](i) = 0;
//     }

//     Memory *memory = new Memory;
//     memory->pages = pages;
//     memory->counts = counts;

//     // Создаем процессы
//     int process_number = std::stoi(sim_data[6][0]);
//     std::cout << "Number of processes: " << process_number << '\n';
//     std::vector<Process> processes;

//     for (int i = 0; i < process_number; i++)
//     {
//         Process process;
//         process.faults = 0;
//         process.page_size = std::stoi(sim_data[6 + 1 + i][1]);
//         process.name = sim_data[6 + 1 + i][0];
//         processes.push_back(process);
//     }

//     // Запускаем симуляцию
//     int page_size = std::stoi(sim_data[1][0]);
//     std::cout << "Page size: " << page_size << '\n';

//     for (int i = 6 + process_number + 1; i < sim_data.size(); i++)
//     {
//         Process process = getProcess(sim_data[i][0], processes);
//         if (std::stoi(sim_data[i][1], 0, 16) == -1)
//         {
//             continue;
//         }

//         unsigned long address = std::stoul(sim_data[i][1], nullptr, 16);
//         int page = address >> (countBits(page_size) - 1); // Получаем номер страницы
//         unsigned long offset = address & (page_size - 1); // Получаем смещение

//         int frame_index = pageInMemory(process.name, page, memory);
//         if (frame_index == -1)
//         {
//             // Обработка страничной ошибки
//             Page missing_page;
//             missing_page.number = page;
//             missing_page.process = process.name;

//             int free_frame = getFreeFrame(memory);
//             if (free_frame == -1)
//             {
//                 free_frame = maxCountSlot(memory);
//                 modifyMemory(&missing_page, memory, free_frame, 1); // Запись на диск
//             }
//             else
//             {
//                 missing_page.frame = free_frame; // Указываем номер фрейма
//                 modifyMemory(&missing_page, memory, free_frame, 0); // Чтение с диска
//             }

//             process.faults++;
//             updateProcesses(process, processes);
//             memorySweepFIFO(memory);
//         }
//         else
//         {
//             // Страница в памяти, конвертируем виртуальный адрес в физический адрес
//             unsigned long physical_address = translateToPhysicalAddress(page, offset, memory);
//             std::cout << "Virtual address: " << std::hex << address << " translates to Physical address: " << physical_address << std::dec << '\n';
//         }
//     } // конец цикла симуляции

//     int total = 0;
//     for (auto process : processes)
//     {
//         std::cout << "Faults from process " << process.name << " :" << process.faults << " \n";
//         total += process.faults;
//     }
//     std::cout << "Total faults: " << total << " \n";

//     delete pages;
//     delete counts;
//     delete memory;

//     return 0;
// }




















#include <stdio.h>
#include <string>
#include <vector>
#include <limits.h> 
#include <iostream>
#include <fstream>

using namespace std;

vector<string> getTxtInfo(string line){
    vector<string> list;
    if(line.size() == 0) return list;

    int end = line.find(' ');
    if(end != string::npos){
        list.push_back(line.substr(0, end));
        vector<string> subList = getTxtInfo(line.substr(end + 1, line.size()));

        if(subList.size() != 0){
            list.insert(list.end(), subList.begin(), subList.end());
        }
    }else{
        end = line.size();
        list.push_back(line.substr(0, end));
    }
    return list;
}


struct Page{
    string process;
    int num;
    int frame;
};

struct Memory{
    vector<Page> *pages;
    vector<int> *counts;
};

struct Process{
    vector<int> pages;
    string name;
    unsigned int pageSize; 
    unsigned int faults;
};

Process getProcess(string name, vector<Process> &procs){
    for (int i = 0; i < procs.size(); i++)
    {
        if(name == procs[i].name){
           return procs[i];
        }
    }   
}

void accessMemory(Page *page, Memory *mem, int slot, int rw){
    if(rw == 0){
        mem -> pages -> operator[](slot) = *page;
    }else{
        mem -> pages -> operator[](slot).num = -1;
        mem -> pages -> operator[](slot).process = "";
        mem -> pages -> operator[](slot).frame = -1;
    }
}

int getFreeFrame(const Memory *mem){
    for (int i = 0; i < mem -> pages -> size(); i++)
    {
        if(mem -> pages -> operator[](i).process.length() == 0){
            return i;
        }
    }
    return -1;
}

int maxCountSlot(Memory *mem){
    int max = INT_MIN;  
    int slot = -1;
    for (int i = 0; i < mem->counts->size(); i++)
    {
        if (mem->counts->operator[](i) > max) {
            max = mem->counts->operator[](i);
            slot = i;
        }
    }
    return slot;
}


int freeSlots(Memory *mem){
    int count = 0;
    for (int i = 0; i < mem->pages->size(); i++)
    {
        if (mem->pages->operator[](i).process.length() == 0)
        {
            count++;
        }
    }
    return count;
}

void memorySweepFIFO(Memory *mem){
    for (int i = 0; i < mem->counts->size(); i++)
    {
        mem->counts->operator[](i)++;
    }
}

int pageInMemory(string name, int page, const Memory *mem)
{
    for (int i = 0; i < mem->pages->size(); i++)
    {
        if (name == mem->pages->operator[](i).process && page == mem->pages->operator[](i).num)
        {
            return i; 
        }
    }
    return -1;
}

void updateProcesses(Process process, vector<Process> &procs)
{
    for (int i = 0; i < procs.size(); i++)
    {
        if (process.name == procs[i].name)
        {
            procs[i] = process;
            return;
        }
    }
}

unsigned long translateToPhysicalAddress(int page, unsigned long offset, Memory *mem) {
    for (size_t i = 0; i < mem->pages->size(); i++) {
        if (mem->pages->operator[](i).num == page) {
            int frame = mem->pages->operator[](i).frame; 
            unsigned long baseAddress = frame * 4096; 
            return baseAddress + offset; 
        }
    }
    cerr << "Ошибка: Страница не найдена для номера страницы " << page << "." << endl;
    return -1; 
}

unsigned int countBits(unsigned int n)
{
    unsigned int count = 0;
    while (n)
    {
        count++;
        n >>= 1;
    }
    return count;
}


int main()
{
    ifstream file("input.txt");
    string line;
    vector<vector<string>> sim_data;

    while (getline(file, line))
    {
        vector<string> list = getTxtInfo(line);
        sim_data.push_back(list);
    }

    int memory_size = stoi(sim_data[0][0]);
    vector<Page> *pages = new vector<Page>(memory_size);
    vector<int> *counts = new vector<int>(memory_size);
    cout << "Total pages in memory: " << memory_size << '\n';

    for (int i = 0; i < memory_size; i++)
    {
        Page page;
        page.process = "";
        page.num = -1;
        page.frame = -1; 
        pages->operator[](i) = page;
        counts->operator[](i) = 0;
    }

    Memory *memory = new Memory;
    memory->pages = pages;
    memory->counts = counts;

    int process_number = stoi(sim_data[6][0]);
    vector<Process> processes;

    for (int i = 0; i < process_number; i++)
    {
        Process process;
        process.faults = 0;
        process.pageSize = stoi(sim_data[6 + 1 + i][1]);
        process.name = sim_data[6 + 1 + i][0];
        processes.push_back(process);
    }

    int page_size = stoi(sim_data[1][0]);
    cout << "Page size: " << page_size << '\n';

    for (int i = 6 + process_number + 1; i < sim_data.size(); i++)
    {
        Process process = getProcess(sim_data[i][0], processes);
        if (stoi(sim_data[i][1], 0, 16) == -1)
        {
            continue;
        }

        unsigned long address = stoul(sim_data[i][1], nullptr, 16);
        int page = address >> (countBits(page_size) - 1);
        unsigned long offset = address & (page_size - 1);

        int frame_index = pageInMemory(process.name, page, memory);
        if (frame_index == -1)
        {
            Page missing_page;
            missing_page.num = page;
            missing_page.process = process.name;

            int free_frame = getFreeFrame(memory);
            if (free_frame == -1)
            {
                free_frame = maxCountSlot(memory);
                accessMemory(&missing_page, memory, free_frame, 1); 
            }
            else
            {
                missing_page.frame = free_frame; 
                accessMemory(&missing_page, memory, free_frame, 0); 
            }

            process.faults++;
            updateProcesses(process, processes);
            memorySweepFIFO(memory);
        }
        else
        {
            unsigned long physical_address = translateToPhysicalAddress(page, offset, memory);
            cout << "Virtual address: " << hex << address << " translates to Physical address: " << physical_address << dec << '\n';
        }
    } 

    int total = 0;
    for (auto process : processes)
    {
        cout << "Faults from process " << process.name << " :" << process.faults << " \n";
        total += process.faults;
    }
    cout << "Total faults: " << total << " \n";

    delete pages;
    delete counts;
    delete memory;

    return 0;
}
