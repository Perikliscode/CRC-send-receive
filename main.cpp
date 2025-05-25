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
    //
    vector<int> messages[10];//10 μηνύματα
    vector<int> D2M[10];
    vector<int> FCSM[10];
    vector<int> TM[10];

    for (int i = 0; i < 10; i++) {
        D2M[i].resize(n);
        FCSM[i].resize(n-k);
        TM[i].resize(n);
        messages[i].resize(k);
        for (int j = 0; j < k; j++) {
            messages[i].at(j) = rand() % 2;
        }
    }

    cout<<endl<<"messages = "<<endl;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < k; j++) {
            cout<<messages[i][j];
        }
        cout<<endl;
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < k; j++) {
            D2M[i].at(j) =messages[i][j];
        }
        for (int h=k;h<n;h++) {
            D2M[i].at(h) = 0;
        }
    }

    //Υπολογισμός FCS για το καθένα
    for (int i = 0; i < 10; i++) {
        FCSM[i] = Calc_CRC(D2M[i],P,n,bP,k);
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < k; j++) {
            TM[i].at(j) = D2M[i].at(j);
        }
        for (int h=0;h<n-k;h++) {
            TM[i].at(h+k) = FCSM[i].at(h);
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j=0;j<n;j++) {
            B = ((double)rand()/(double)RAND_MAX);// τυχαίος αριθμός απο 0 μέχρι 1
            if (1-B<=BER) {// Αν η ψευδοπιθανότητα είναι μικρότερη απο το BER τότε αλλοιώνεται το bit
                TM[i][j] = !TM[i][j];
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        vector<int> rem= Calc_CRC(TM[i],P,n,bP,k);
        bool error = false;
        for (int j=0;j<n-k;j++) {
            if (rem[j]!=0) {
                error = true;
            }
        }
        cout<<endl<<"received T=";

        for (int j=0;j<n;j++) {
            cout<<TM[i][j];
        }
        cout<<endl;

        if (error == true) {
            cout<< "Message "<<i<<" received with error"<<endl;
        }
        else {
            cout<<"Message "<<i<<" received with no error"<<endl;
        }
    }


    return 0;
}
