#include <bits/stdc++.h>
#include <iostream>

using namespace std;

class String {
public: 
    String() : m_Data(nullptr), m_Size(0) {};
    String(const char* str) {
        // basic constructor which takes in a string and creates a copy of it of the same size
        printf("Created!\n\n");
        m_Size = strlen(str);
        m_Data = new char[m_Size];
        memcpy(m_Data, str, m_Size);
    }

    String(const String& other) {
        // copy constructor
        printf("Copied!\n");
        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
    }

    String(String&& other) noexcept {
        // move constructor
        printf("Moved!\n");
        m_Size = other.m_Size;
        m_Data = other.m_Data;
        // take care of the old object by just rewiring the pointers
        other.m_Size = 0;
        other.m_Data = nullptr;
    }

    String& operator = (String&& other) noexcept {
        // move assignment operator
        printf("Move Assigned!\n\n ");

        if (this != &other) {
            delete[] m_Data;

            m_Size = other.m_Size;
            m_Data = other.m_Data;

            other.m_Size = 0;
            other.m_Data = nullptr;
        }

        return *this;   
    }

    // destructor
    ~String() {
        printf("Destroyed!\n");
        delete[] m_Data;
    }

    void Print() {
        for (uint32_t i = 0; i < m_Size; i++) {
            printf("%c", m_Data[i]);
        }
        printf("\n");
    }

private: 
    char* m_Data;
    uint32_t m_Size;
};

class Consumer {
public:
    Consumer (const String& name) : m_Name(name) {}
    
    Consumer (String&& name) : m_Name((String&&)name) {}

    void PrintName() {
        m_Name.Print();
    }
private:
    String m_Name;
};

int main () {
    // String ashwattha = String("Ashwattha");
    // // Consumer consumer(String("Dhruva")); 
    // // consumer.PrintName();
    
    // String dest;
    // cout << "Ashwattha : ";
    // ashwattha.Print();
    // cout << "Dest : ";
    // dest.Print();

    // dest = move(ashwattha);
    // cout << "Ashwattha : ";
    // ashwattha.Print();
    // cout << "Dest : ";
    // dest.Print();

    vector<int>* vec1 = new vector<int>{1, 2, 3, 4, 5};
    vector<int> vec2 = move(*vec1);

    vec1->push_back(6);

    for (int i : vec1) {
        cout << i << " ";
    }
    
    cout << endl;
    for (int i : vec2) {
        cout << i << " ";
    }

    delete vec2;

    // cin.get();
}


