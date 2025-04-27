#include <stdio.h>
#include <string>
#include <vector>
#include <limits.h> 
#include <iostream>
#include <fstream>
#include <random>
#include <time.h>

using namespace std;

struct Page{
    string process;
    int isActive;
    int frame;
};

struct Memory{
    vector<Page> *pages;
};

struct Process{
    int procSize;
    string name;
    vector<int> pages;
    unsigned int pageSize; 
};


void printPages(const vector<Page>& pages) {
    cout << "Pages:" << endl;
    for (const auto& page : pages) {
        cout << "  Process: " << page.process 
             << ", Page isActive: " << page.isActive 
             << ", Frame: " << page.frame << endl;
    }
}

void printMemory(const Memory& memory) {
    cout << "Memory:" << endl;
    cout << "  Pages:" << endl;
    if (memory.pages != nullptr) {
        printPages(*memory.pages);
    }
}
 
void printProcess(const Process& process) {
    cout << "Process Name: " << process.name << endl;
    cout << "  Page Size: " << process.pageSize << endl;
    cout << "  Pages: ";
    for (const auto& page : process.pages) {
        cout << page << " ";
    }
    cout << endl;
}
 
void printProcesses(const vector<Process>& processes) {
    cout << "Processes:" << endl;
    for (const auto& process : processes) {
        cout << "Process Name: " << process.name << endl;
        cout << "  Page Size: " << process.pageSize << endl;
        cout << "  Pages: ";
        for (const auto& page : process.pages) {
            cout << page << " ";
        }
        cout << endl;
    }
}


void freeMemory(Memory *mem, Process &proc) {
    bool found = false; 
    
    for (int i = 0; i < mem->pages->size(); i++) {
        if (mem->pages->operator[](i).process == proc.name) {
            mem->pages->operator[](i).process = ""; 
            mem->pages->operator[](i).isActive == -1; 
            found = true; 
        }
    }

    proc.pages.clear();
    if (found) {
        cout << "Process " << proc.name << " has been removed from memory." << endl;
    } else {
        cout << "Process " << proc.name << " was not found in memory." << endl;
    }
}

void findMemory(Memory *mem, Process &proc) {
    int allocPages = 0;
    int procSize = proc.procSize;

    for (int i = 0; i < mem->pages->size(); i++) {
        if (mem->pages->operator[](i).isActive == -1) { 
            if (procSize > 0) {
                procSize--;
                allocPages++;
                proc.pages.push_back(i);
                mem->pages->operator[](i).isActive = 1;  
            } else {
                break; 
            }
        }
    }

    if (allocPages == proc.procSize) {
        cout << "Allocated " << allocPages << " pages for the process." << endl;
    } else {
        proc.pages.clear(); 
        cout << "No memory available." << endl;
    }
}

void allocateMemory(Memory *mem, Process &proc) {
    for (int i = 0; i < mem->pages->size(); i++) {
        for (int j = 0; j < proc.pages.size(); j++) {
            if (proc.pages[j] == i) {
                mem->pages->operator[](i).process = proc.name;
                mem->pages->operator[](i).frame = (rand() % (0xFFFFFFFF - 0x10000000 + 1)) + 0x10000000;
                
            }
        }
    }
}

void parseAddress(int addr, int &pageNum, int &offset) {
    const int FRAME_SIZE = 0x1000; 
    offset = addr % FRAME_SIZE;
    pageNum = addr / FRAME_SIZE;
}



void translateAddress(Memory *mem, Process &proc, int &addr) {
    int pageNum, offset;
    printf("Address: Virt address=%x\n", addr);


    parseAddress(addr, pageNum, offset);
    printf("Parsed Address: pageNum=%d, offset=%d\n", pageNum, offset);

    if (pageNum < 0 || pageNum >= static_cast<int>(mem->pages->size())) {
        printf("Page fault: Invalid page number %d\n", pageNum);
        return; 
    }

    addr = mem->pages->operator[](pageNum).frame + offset; 
    printf("Translated Address: Physical address=%x\n", addr);
}

void createAddress(Memory *mem, Process &proc, int offset, int &addr) {   
    const int FRAME_SIZE = 0x1000;

    if (proc.pages.empty()) {
        return; 
    }    
    int pageindex = rand() % proc.pages.size(); 
    int pageNum = proc.pages.at(pageindex); 

    if (pageNum < 0) {
        cout << "Invalid page number for process: " << proc.name << endl;
        return;
    }

    addr = pageNum * FRAME_SIZE + offset; 
}


int main()
{
    srand(static_cast<unsigned int>(time(0)));
    const char* procNames[][3] = {
        {"proc101"},
        {"proc102"},
        {"proc103"}
    };

    const char* addressData[][2] = {
        {"proc101", "580"},
        {"proc101", "120"},
        {"proc101", "580"},
        {"proc102", "530"},
        {"proc102", "580"},
        {"proc102", "480"},
        {"proc103", "450"},
        {"proc103", "24580"},
        {"proc103", "24586"}
    };


    int memorySize = 8;
    int procNum = 3;
    vector<Page> *pages = new vector<Page>(memorySize);
    vector<bool> *status = new vector<bool>(memorySize);
    cout << "Total pages in memory: " << memorySize << '\n';

    for (int i = 0; i < memorySize; i++)
    {
        Page page;
        page.process = "NULL";
        page.isActive = -1;
        page.frame = -1; 
        pages->operator[](i) = page;
        status->operator[](i) = 0;
    }


    Memory *memory = new Memory;
    memory->pages = pages;
    // memory->isLoaded = status;
    
    vector<Process> processes;

    for (int i = 0; i < procNum; i++){
        Process process;
        process.procSize = 1 + (rand() % 4); 
        process.pageSize = 4096;
        process.name =  procNames[i][0];
        processes.push_back(process);
    }
    int dataSize = sizeof(addressData) / sizeof(addressData[0]);
    vector<int> virtAddr;

    int addr;
    

    findMemory(memory, processes[0]);
    allocateMemory(memory, processes[0]);


    findMemory(memory, processes[1]);
    allocateMemory(memory, processes[1]);

    for (int i = 0; i < processes.size(); i++){
        for (int j = 0; j < dataSize; j++){
            if(processes.operator[](i).name == addressData[j][0]){
                long offset = strtol(addressData[j][1], nullptr, 16);
                createAddress(memory, processes.operator[](i), offset, addr);
                virtAddr.push_back(addr);
            }
        }   
    }


    translateAddress(memory, processes[0], addr);
    printMemory(*memory);
    printProcesses(processes);


    freeMemory(memory, processes[0]);


    

    return 0;
}
