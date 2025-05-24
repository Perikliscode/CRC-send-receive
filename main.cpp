#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include "crc.h"

using namespace std;

int main() {
    int k=0;
    cout<<"k:";
    cin >> k;


    //ΠΟΜΠΌΣ:
    vector<int> messageSeq(k);

    srand(time(NULL));//Για να ποικιλεί η τυχαιότητα του αριθμού
    cout<<"message = ";
    for (int i = 0; i < k; i++) {
        messageSeq[i] = rand() % 2;
        cout<<messageSeq[i];
    }

    int bP=0;
    cout<<endl<<"total bits of P:";
    cin>> bP;

    vector<int> P(bP);
    cout << "Enter P bits (space separated):";
    for (int i = 0; i < bP; i++) {
        cin >> P[i];
    }
    // Υπολογισμός 2^(n-k)D
    int n = bP + k -1;

    vector<int> D2(n);
    for (int i = 0; i < k; i++) {
        D2[i] = messageSeq[i];
    }
    for (int i = k; i < n; i++) {
        D2[i]=0;
    }
    cout<<"D2=";
    for (int i = 0; i < n; i++) {
        cout<<D2[i];
    }
    cout<<endl;
    vector<int> FCS=Calc_CRC(D2,P,n,bP,k);

   cout << endl << "FCS=";
    for (int i = 0; i <n-k; i++) {
        cout << FCS[i];
    }

    //Υπολογισμός των bits που θα στείλει ο πομπός
    vector<int> T = D2;
    for (int i = 0; i < n-k; i++) {
        T[k+i]=FCS[i];
    }
    cout << endl << "T=";
    for (int i = 0; i < n; i++) {
        cout<<T[i];
    }
    cout<<endl;

    double BER;
    cout<<"Enter Bit Error Rate (in decimal form):";
    cin>>BER;
    double B;
    //Αλλοίωση της σειράς bit
    for (int i = 0; i < n; i++) {
        B = ((double)rand()/(double)RAND_MAX);// τυχαίος αριθμός απο 0 μέχρι 1
        if (1-B<=BER) {// Αν η ψευδοπιθανότητα είναι μικρότερη απο το BER τότε αλλοιώνεται το bit
            T[i] = !T[i];
        }
    }

    //ΑΠΟΔΈΚΤΗΣ:
    cout << endl << "received T=";
    for (int i = 0; i < n; i++) {
        cout<<T[i];
    }

    //Έλεγχος του FCS
    vector<int> rem= Calc_CRC(T,P,n,bP,k);

    bool error = false;
    for (int i = 0; i <n-k; i++) {
        if (rem[i]!=0) {
            error = true;
        }
    }

    cout<<endl;
    if (error == true) {
        cout<<"Message received with error";
    }
    else {
        cout<<"Message received with no error";
        cout<<endl<<"Message is :";
        for (int i = 0; i < k; i++) {
            cout<<T[i];
        }
    }

    return 0;
}
