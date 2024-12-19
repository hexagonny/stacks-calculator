#include <iostream>
#include <cmath>
#include <cstdlib>
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::seconds

using std::cout;
using std::cin;

#ifdef _WIN32
    // Windows-specific code
    void setConsoleWindowSize(int width, int height) {
        std::string command = "mode con: cols=" + std::to_string(width) + " lines=" + std::to_string(height);
        system(command.c_str());
    }
#elif __unix__
    // Linux/MacOS-specific code
    void setConsoleWindowSize(int width, int height) {
        std::string command = "resize -s " + std::to_string(height) + " " + std::to_string(width);
        system(command.c_str());
    }
#endif

void sleep(int miliseconds){
    std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
}
void calculateToStacks(int stackSize){

    int totalItems;  // How many total of blocks/items.
    int stacks;  // A stack is equals to 64 or 16.
    int leftover;  // The left-over does not goes up to a stack(64/16)
    int slots;  // A stack occupies one slot.
    int dChest;  // A double chest has a maximum of 54 slots.
    int xtraItems;  // Exceeds the maximum slots of a double chest.
    int totaldChest;  // How much double chests it needs to store.

    cout<<"* Enter the total number of items: "; cin>>totalItems;
            
    // Converting decimal to stacks.
    stacks= floor(totalItems/stackSize);
    leftover= totalItems%stackSize;
    sleep(1000);

    if(totalItems<stackSize){
        cout<<"* Please enter a given that is greater than 64!\n";
        cout<<std::endl;
    }
    else if(totalItems>=stackSize){
        cout<<"|   "<<stacks<<" stack/s";

        // Converting stacks to slots.
        if(leftover>0){
            cout<<" and "<<leftover<<" item/s";
            leftover= 1;
            slots= stacks+leftover;
        }
        else if(leftover==0){
            leftover= 0;
            slots= stacks+leftover;
        }
        cout<<".\n";
        sleep(2000);
        cout<<"*   It would take up "<<slots<<" slot/s,";

        if(slots>54){
            // Converting slots to double chests(base-54).
            dChest= floor(slots/54);
            xtraItems= slots%54;
                if(xtraItems>0){
                    xtraItems= 1;
                    totaldChest= dChest+xtraItems;
                }
            cout<<" in "<<totaldChest<<" double chests.\n\n";
        }
        else if(slots<27){
            cout<<" in a single chest.\n\n";
        }
        else if(slots>27){
            cout<<" in a double chest.\n\n";
        }
    }
}
void calculateToDecimal(){
    // How much it takes to be a stack.
    int maxStackSize;

    int totalItems;  // How many total of blocks/items.
    int stacks;  // A stack is equals to 64 or 16.
    int leftover;  // The left-over does not goes up to a stack(64/16)

    cout<<"* Enter how many stacks: "; cin>>stacks;
    cout<<"* Enter leftover items: "; cin>>leftover;
    cout<<"* What maximum stack size? (16 or 64)\n";
    cout<<"= "; cin>>maxStackSize;
    cout<<std::endl;
    sleep(1000);

    if(maxStackSize == 16 || maxStackSize == 64){
        cout<<"* The value you entered is invalid!\n\n";
        return;
    }

    // Converting stacks to decimal.
    totalItems= stacks*maxStackSize+leftover;
    cout<<"* Total of "<<totalItems<<" items.\n\n";
}
int main(){
    int loop;

    setConsoleWindowSize(50, 30);
    
    do{
        int BaseNumber;
        
        cout<<"-----------------Stacks Converter-----------------\n\n";
        cout<<"* Pick a base number system. (1/2/3)\n";
        cout<<"|   base-16 - 1\n";
        cout<<"|   base-64 - 2\n";
        cout<<"|   decimal - 3\n";
        cout<<"= "; cin>>BaseNumber;
        cout<<std::endl;

        // Resets the error flags when std::cin fails to interpret the input.
        cin.clear();
        fflush(stdin);

        switch(BaseNumber){
            int stackSize;

            // base-16
            case 1:
                stackSize= 16;
                calculateToStacks(stackSize);
                break;
            // base-64
            case 2:
                stackSize=64;
                calculateToStacks(stackSize);
                break;
            // base-10
            case 3:{
                calculateToDecimal();
                break;
            }
            default:
                cout<<"* The value you entered is invalid!\n\n";
                break;
        }
        cout<<"--------------------------------------------------\n";
        sleep(1000);
        cout<<"* Rerun the program again? (1/2)\n";
        cout<<"|   No  - 1\n";
        cout<<"|   Yes - 2\n";
        cout<<"= ";cin>>loop;

        cin.clear();
        fflush(stdin);

        while(loop!=1&&loop!=2){
            cout<<"* Invalid input. Please enter 2 to continue or 1 to exit.\n";
            cout<<"= ";cin>>loop;
        }
    }while(loop!=1);
    cout<<"--------------------------------------------------\n";
    cout<<"* Program exiting...\n";
    // Loop from 1 to 3
    for (int i=1;i<=3;++i) {
        cout<<i<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}