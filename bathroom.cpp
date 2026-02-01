#include <bits/stdc++.h>
#include <iostream>
#include <mutex>
#include <semaphore>
#include <thread>
#include <condition_variable>

/*
    Implement the Bathroom problem - Unisex bathroom, there cannot be both men and women in it. No more than three employees can be in the bathroom at a time. 
    No deadlocks. For now, starvation is okay.

-----

Solution

Goal-> maintain seperation of the two genders in the same bathroom while only allowing 3 people at once 

Invariants ->
1. People of opposite gender cannot be in the bathroom at the same time.
2. No more than 3 people at a time

Scenarios ->
1. G in bathroom, NG tries to enter -> not allowed
2. G in bathroom, G tries to enter, less than 3 people in the bathroom -> allowed
3. All G left bathroom -> first to get access can enter
(Starvation is possible if even 1 G never leaves) 

------

Avoiding Starvation ->

To avoid starvation, I can have a turn variable 
Let's say that I allow at most six turns where people of the same gender enter the bathroom. Once it reaches six turns, then I will have to block that gender by only notifying the opposite gender whenever the bathroom is completely free. 


*/

using namespace std;

class UnisexBathroom {

    mutex bathroom;
    condition_variable male_allowed;
    condition_variable female_allowed;
    int counter = 0;     // I can have the counter go from -3 to +3 -> -1,-2,-3 for females occupying and positive values for males occupying
    int turn = 0; // counts the consecutive enters by the same gender

public:

    void maleEntersBathroom() {
        // called when male tries to enter the bathroom        
        unique_lock<mutex> lock(bathroom);
        male_allowed.wait(lock, [&] {
            return ((counter >=0 && counter <= 2) && (turn < 4));
        });
        counter++; 
        turn++;
    }

    void femaleEntersBathroom() {
        // called when female tries to enter the bathroom
        unique_lock<mutex> lock(bathroom);
        female_allowed.wait(lock, [&] {
            return ((counter<=0 && counter >= -2) && (turn < 4));
        });
        counter--;
        turn++;
    }

    void maleExitsBathroom() {
        unique_lock<mutex> lock(bathroom);
        counter--;
        if (counter == 0) {
            if (turn == 4) {
                turn=0;    
            }
            female_allowed.notify_all();
        } else {
            male_allowed.notify_one();
        }
    }

    void femaleExitsBathroom() {
        unique_lock<mutex> lock(bathroom);
        counter++;
        if (counter == 0) {
            if (turn == 4) {
                turn=0;    
            };
            male_allowed.notify_all();
        } else {
            female_allowed.notify_one();
        }
    }
};

// Gendered methods w time in bathroom
void Male(UnisexBathroom& c, string name, int time) {
    c.maleEntersBathroom();
    cout << name << " entered" << endl;
    this_thread::sleep_for(chrono::milliseconds(time));
    c.maleExitsBathroom();
    cout << name << " exited" <<endl;
}

void Female(UnisexBathroom& c, string name, int time) {
    c.femaleEntersBathroom();
    cout << name << " entered" <<endl;
    this_thread::sleep_for(chrono::milliseconds(time));
    c.femaleExitsBathroom();
    cout << name << " exited" <<endl;
} 

int main () {
    UnisexBathroom b;

    thread male1(Male, ref(b), "Joe", 10);
    thread male2(Male, ref(b), "Bunty", 2);
    thread male3(Male, ref(b), "Andy", 30);
    thread male4(Male, ref(b), "Vinod", 15);
    thread male5(Male, ref(b), "Subhash", 25);
    thread female1(Female, ref(b), "Mandy", 5);
    thread female2(Female, ref(b), "Sandy", 20);
    thread female3(Female, ref(b), "Hema", 40);
    thread female4(Female, ref(b), "Rekha", 100);
    thread female5(Female, ref(b), "Jaya", 10);

    male1.join();
    male2.join();
    male3.join();
    male4.join();
    male5.join();
    female1.join();
    female2.join();
    female3.join();
    female4.join();
    female5.join();

    return 0;
}