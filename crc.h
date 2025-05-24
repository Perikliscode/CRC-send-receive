#ifndef CRC_H
#define CRC_H
using namespace std;

vector<int> Calc_CRC(vector<int> Dx,vector<int> Pol,int n,int bP,int k) {
    vector<int> Temp(n);
    for (int i = 0; i < n; i++) {
        Temp[i] = Dx[i];
    }
    //Διαίρεση με XOR για εύρεση του FCS
    for (int i = 0; i <= n-bP; i++) {
        if (Temp[i] == 1) {
            for (int j=0;j<bP;j++) {
                //XOR Πύλη
                Temp[i + j] ^= Pol[j];
            }
        }
    }
    vector<int> CRC(n-k);

    for (int i = 0; i < n - k; i++) {
        CRC[i] = Temp[k + i];
    }

    return CRC;
}

#endif //CRC_H
