#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <locale>
#include <fstream>
#include <algorithm> 
#include<random>
#include<ctime>
#include <map>
#include <cstdint>
#include <cstddef>
#define BEGIN 97
#define END 122
using namespace std;

//Alp_NumStatistics
class Cipher {
private:
    vector<string> alphabet;
    map<string, double> Alp_NumEncrypted;
    map<string, double> Alp_NumStatistics;
    vector<pair<string, double> > vectEncrypted;
    vector<pair<string, double> > vectStatistics;
    string nameFileInput;
    string nameFileOutput;

    int key;

public:


    Cipher() {
      this->key = rand() % 26 + 1;

      cout << "KEY: " << this->key << endl;
      Start();
    }


    Cipher(int value) {
        this->key = value;
        Start();
    }

    void Start() {
        AlphabetGeneration();


        /// <summary>
        /// ///////////////////////////////////////////////////////////////////////////////////////////
        /// </summary>
        this->nameFileInput = "zarinka.txt";
        this->nameFileOutput = "test.txt";
        MapStatisticsOREncrypted(/*true,*/ Alp_NumStatistics, vectStatistics);
        /// <summary>
        /// //////////////////////////////////////////////////////////////////////////////////////////
        /// </summary>
        this->nameFileInput = "caesarin.txt";
        this->nameFileOutput = "vadimkapidr.txt";
        MapStatisticsOREncrypted(/*false,*/ Alp_NumEncrypted, vectEncrypted);
        
        /// <summary>
/// //////////////////////////////////////////////////////////////////////////////////////////
/// </summary>
        cout << "IN()" << endl;
        this->nameFileInput = "input.txt";
        this->nameFileOutput = "caesarin.txt";
        InOROut(true);
        /// <summary>
         /// //////////////////////////////////////////////////////////////////////////////////////////
        /// </summary>

        cout << "Out()" << endl;
        this->nameFileInput = "caesarin.txt";
        this->nameFileOutput = "caesarout.txt";
        InOROut(false);

        /// <summary>
        /// //////////////////////////////////////////////////////////////////////////////////////////
         /// </summary>
        readFile();
    }


    void AddingLetter() {
        string tmp = "";
        int count = 0;
        for (char i = BEGIN; i <= END; i++) {
            tmp.clear();
            tmp += i;
            for (char j = BEGIN; j <= END; j++) {
                if (j != BEGIN) {
                    tmp.pop_back();
                }
                tmp += j;
                alphabet.push_back(tmp);
                count++;
            }
        }
    }
    

    void AddingElem(char elem, bool flag) {
        string tmp = "";
        int count = 0;
       
        for (char i = BEGIN; i <= END; i++) {
            tmp.clear();
            if (flag) { tmp += i; }
            else { tmp += elem; }
          
            for (char j = BEGIN; j <= END; j++) {
                if (j != BEGIN) {
                    tmp.pop_back();
                }
                if (flag) {tmp += elem;}
                else { tmp += j; }

                alphabet.push_back(tmp);

                count++;
                if (flag) break;


            }
            if (!flag) break;
   
        }

    }


    void AlphabetGeneration() {
       
        AddingLetter();
        AddingElem(44, true);
        AddingElem(44, false);
        AddingElem(32, true);
        AddingElem(32, false);
        AddingElem(46, true);
        AddingElem(46, false);
        alphabet.push_back(" .");
        alphabet.push_back(". ");
        alphabet.push_back(" ,");
        alphabet.push_back(", ");
        alphabet.push_back("  ");

       /* for (int i = 0; i < alphabet.size(); i++) {
            cout << alphabet[i] << " ";
        }*/
    }


    void In(string& tmp, ofstream& output , bool& flag) {
        for (int i = 0; i < alphabet.size(); i++) {
            if (tmp.empty() || flag == true) {
                flag = false;
                break;
            }
            if (tmp == alphabet[i]) {
                i += (key % 26);
                if (i >= alphabet.size())
                    i -= alphabet.size();
                output << alphabet[i];
                break;


            }
        }
    }

    void Out(string& tmp, ofstream& output) {
        for (int i = 0; i < alphabet.size(); i++) {
            if (tmp.empty()) {
                break;
            }
            if (tmp == alphabet[i]) {
                i -= (key % 26);
                if (i < 0)
                    i += alphabet.size();
                output << alphabet[i];
                break;
            }
        }
    }

  

    void InOROut(bool value) { // true - in , false - out 
        ifstream input(nameFileInput);
        ofstream output(nameFileOutput);

        string tmp = "";
        bool flag = false;
        if (!input.is_open())
            cout << "Файл не может быть открыт!\n";
        else {
            while (!input.eof()) {
                tmp.clear();
                for (int i = 0; i < 2; i++) {
                    tmp += input.get();
                    if (tmp[i] == '\n') {
                        tmp[i] = ' ';
                        if (value) In(tmp, output, flag);
                        else Out(tmp, output);
                        i++;
                        output << '\n';
                        if (i == 2) { flag = true; }
                    }

                    if (tmp[i] == -1) {
                        tmp[i] = ' ';
                        if (value) In(tmp, output, flag);
                        if (i == 2) { flag = true; }
                    }

                }
                if (input.eof()) { break; }
                if (value) In(tmp, output, flag);
                else Out(tmp, output);

            }
        }
        input.close();
        output.close();
    }

    static bool cmp(const pair<string, double>& p1, const pair<string, double>& p2)
    {
        return p1.second > p2.second;
    }


    void MapStatisticsOREncrypted(/*bool flag ,*/ map<string, double>& Alp_Num, vector<pair<string, double> >& vectPair)
    {// false - Encrypted, true - MapStatistics
        string tmp = "";
        int count = 0;
        double alpha2[837] = { 0.0 };
       /* if (flag) {
            this->nameFileInput = "zarinka.txt";
            this->nameFileOutput = "test.txt";
        }
        else {
            this->nameFileInput = "caesarin.txt";
            this->nameFileOutput = "vadimkapidr.txt";
        }*/
        ifstream input(nameFileInput);
        ofstream output(nameFileOutput);

        if (!input.is_open())
            cout << "Ôàéë íå ìîæåò áûòü îòêðûò!\n";
        else {
            while (!input.eof()) {
                tmp.clear();
                for (int i = 0; i < 2; i++) {
                    tmp += input.get();
                    if (tmp[i] == '\n') {
                        tmp[i] = ' ';

                    }

                    if (tmp[i] == -1) {
                        tmp[i] = ' ';

                    }

                    count++;

                }
                for (int i = 0; i < alphabet.size(); i++) {
                    if (tmp.empty()) {
                        break;
                    }
                    if (tmp == alphabet[i]) {
                        alpha2[i]++;

                        break;
                    }
                }
            }

        }
      for (int i = 0; i < alphabet.size(); i++) {
            Alp_Num[alphabet[i]] = (double)(((alpha2[i]) / (count / 2)));
        }

        copy(Alp_Num.begin(), Alp_Num.end(), back_inserter(vectPair));

        sort(vectPair.begin(), vectPair.end(), cmp);

        for (int i = 0; i < vectPair.size(); ++i)
            output << vectPair[i].first << " : " << vectPair[i].second << endl;
      

        input.close();
        output.close();

    }


   
    template <typename T>
    T mod(T val, T m)
    {
        T res = val % m;
        if (res < 0)
            res = res + m;
        return res;
    }

    // Frequency Analysis Statistics
   void readFile() {
        // vector<pair<string, double> >& vectVadim /* по зашифрованному */, vector<pair<string, double> >& vectZarina /*  по общему */, vector<string>& alphabet
        cout << " vectEncrypted.size = " << vectEncrypted.size() << endl;
        int NumStat = 0;
        bool otvet = false;
        cout << " vectZarina.size = " << vectStatistics.size() << endl;
        while (!otvet) {
            pair< string, double> tmpZ = vectStatistics[NumStat];
            pair< string, double> tmpV = vectEncrypted[0];
            int countEncrypted = 0;
            int countStatistics = 0;

            for (int i = 0; i < alphabet.size(); i++) {
                if (tmpZ.first == alphabet[i]) {
                    countStatistics = i;
                    break;
                }
            }

            for (int i = 0; i < alphabet.size(); i++) {
                if (tmpV.first == alphabet[i]) {
                    countEncrypted = i;
                    break;
                }
            }
            if ((countStatistics - countEncrypted < 0)) {
                this->key = mod(countStatistics - countEncrypted, 26);
            }
            else {
                this->key = countStatistics - countEncrypted;
            }
           
            this->nameFileInput = "caesarin.txt";
            this->nameFileOutput = "newout.txt";
            InOROut(false);
      
            cout << "Это ваш текст ?" << endl;
            ifstream file("newout.txt");
            string s;
            while (getline(file, s))
                cout << s << endl;
            int tmpOtvet;
            cin >> tmpOtvet;
            otvet = tmpOtvet;
            if (otvet == false) {
                NumStat++;

            }
        }


    }

 

    ~Cipher() {
        Alp_NumEncrypted.clear();
        vectEncrypted.clear();
        Alp_NumStatistics.clear();
        alphabet.clear();
        vectStatistics.clear();
    }

};


int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    Cipher a;
    return 0;

}