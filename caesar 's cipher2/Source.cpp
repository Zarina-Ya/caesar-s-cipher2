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
#define BEGIN 97
#define END 122
using namespace std;



void AddingLetter(vector<string>& alphabet) {
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


void AddingElem(char elem, bool flag, vector<string>& alphabet) {
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
            if (flag) { tmp += elem; }
            else { tmp += j; }

            alphabet.push_back(tmp);

            count++;
            if (flag) break;


        }
        if (!flag) break;

    }

}


void AlphabetGeneration(vector<string>& alphabet) {

    AddingLetter(alphabet);
    AddingElem(44, true, alphabet);
    AddingElem(44, false, alphabet);
    AddingElem(32, true, alphabet);
    AddingElem(32, false, alphabet);
    AddingElem(46, true, alphabet);
    AddingElem(46, false, alphabet);
    alphabet.push_back(" .");
    alphabet.push_back(". ");
    alphabet.push_back(" ,");
    alphabet.push_back(", ");
    alphabet.push_back("  ");

    for (int i = 0; i < alphabet.size(); i++) {
        cout << alphabet[i] << " ";
    }
}


void CaesarIn(string& tmp, ofstream& output, bool& flag, vector<string>& alphabet, int key) {
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

void MYCaesarOut1(string& tmp, ofstream& output, vector<string>& alphabet, int key ) {
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
void InOROut(bool value, vector<string>& alphabet, int key) { // true - in , false - out 
       string nameFileInput = "";
       string nameFileOutput = "";
       if (value) {
          nameFileInput = "input.txt";
           nameFileOutput = "caesarin.txt";
       }
       else {
          nameFileInput = "caesarin.txt";
          nameFileOutput = "caesarout.txt";
       }
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
                    if (value) CaesarIn(tmp, output, flag, alphabet, key);
                    else MYCaesarOut1(tmp, output, alphabet, key);
                    i++;
                    output << '\n';
                    if (i == 2) { flag = true; }
                }

                if (tmp[i] == -1) {
                    tmp[i] = ' ';
                    if (value) CaesarIn(tmp, output, flag, alphabet, key);
                    //else MYCaesarOut1(tmp, output);
                    if (i == 2) { flag = true; }
                }

            }
            if (input.eof()) { break; }
            if (value) CaesarIn(tmp, output, flag, alphabet, key);
            else MYCaesarOut1(tmp, output, alphabet, key);

        }
    }
    input.close();
    output.close();
}

bool cmp(const pair<string, double>& p1, const pair<string, double>& p2)
{
    return p1.second > p2.second;
}

void mapForZarinka(vector<string>& alphabet, map<string, double>& alp_chisloZARINA, vector<pair<string, double> >& vectZarina) {

    ifstream input("zarinka.txt");
    //ifstream input("input.txt");
    ofstream output("test.txt");

    string tmp = "";
    int count = 0;
    double alpha2[837] = { 0.0 };


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
                    // output << alphabet[i];
                    break;
                }
            }
        }

    }
    for (int i = 0; i < alphabet.size(); i++) {
        alp_chisloZARINA[alphabet[i]] = (double)(((alpha2[i]) / (count / 2)));
    }

 
    copy(alp_chisloZARINA.begin(), alp_chisloZARINA.end(), back_inserter(vectZarina));

    sort(vectZarina.begin(), vectZarina.end(), cmp);

    for (int i = 0; i < vectZarina.size(); ++i)
        output << vectZarina[i].first << " : " << vectZarina[i].second << endl;

    input.close();
    output.close();
    
}


void MapStatisticsOREncrypted(bool flag, map<string, double>& alp_chislo, vector<pair<string, double> >& vectPair, vector<string>& alphabet, string NameFileInput, string NameFileOutput)
{// false - Encrypted, true - MapStatistics
  /* string NameFileInput = "";
   string NameFileOutput = "";*/
    string tmp = "";
    int count = 0;
    double alpha2[837] = { 0.0 };
   /* if (flag) {
        string  NameFileInput = "zarinka.txt";
        string  NameFileOutput = "test.txt";
    }
    else {
        NameFileInput = "caesarin.txt";
        NameFileOutput = "vadimkapidr.txt";
    }*/
    ifstream input(NameFileInput);
    ofstream output(NameFileOutput);

    if (!input.is_open() || !output.is_open())
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
        alp_chislo[alphabet[i]] = (double)(((alpha2[i]) / (count / 2)));
    }

    copy(alp_chislo.begin(), alp_chislo.end(), back_inserter(vectPair));

    sort(vectPair.begin(), vectPair.end(), cmp);

    for (int i = 0; i < vectPair.size(); ++i)
        output << vectPair[i].first << " : " << vectPair[i].second << endl;


    input.close();
    output.close();

}

/*int main() {

    setlocale(LC_ALL, "Russian");
    vector<string> alphabet;
    map<string, double> alp_chisloVADIM;
    map<string, double> alp_chisloZARINA;
    vector<pair<string, double> > vectVadim;
    vector<pair<string, double> > vectZarina;
   // MyAlphabet(alphabet);
    //mapForVadimka(alphabet, alp_chisloVADIM, vectVadim);
   //mapForZarinka(alphabet, alp_chisloZARINA, vectZarina);
    AlphabetGeneration(alphabet);
    cout << " MapStatisticsOREncrypted" << endl;
    MapStatisticsOREncrypted(true, alp_chisloZARINA, vectZarina, alphabet, "zarinka.txt","test.txt");
    //MapStatisticsOREncrypted(false, alp_chisloZARINA, vectZarina, alphabet);

    // double alpha[783] = { 0.0 };


    int k = 0;
    cout << "Сдвиг: ";
    cin >> k;
    if (k == 0 || k < 1) {
        k = rand() % 26;
        cout << "Ключ :" << k << '\n';
    }

    if (k < 1)
        return 0;


    
    cout << "IN()" << endl;


    InOROut(true, alphabet, k );



    cout << "Out()" << endl;
   
    InOROut(false , alphabet, k);
    cout << " MapStatisticsOREncrypted" << endl;
   // MapStatisticsOREncrypted(true, alp_chisloZARINA, vectZarina, alphabet);
    //readFile(vectVadim, vectZarina, alphabet);
    alp_chisloVADIM.clear();
    vectVadim.clear();
    alp_chisloZARINA.clear();
    alphabet.clear();
    vectZarina.clear();

    return 0;
}*/



#define BEGIN 97
#define END 122
using namespace std;


class Cipher {
private:
    vector<string> alphabet;
    map<string, double> alp_chisloVADIM;
    map<string, double> alp_chisloZARINA;
    vector<pair<string, double> > vectVadim;
    vector<pair<string, double> > vectZarina;
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
        MapStatisticsOREncrypted(true, alp_chisloZARINA, vectZarina);
        MapStatisticsOREncrypted(false, alp_chisloVADIM, vectVadim);
        //  MapStatistics();
         // MapEncrypted();
        cout << "IN()" << endl;

        this->nameFileInput = "input.txt";
        this->nameFileOutput = "caesarin.txt";
        InOROut(true);
        //In();


        cout << "Out()" << endl;
        this->nameFileInput = "caesarin.txt";
        this->nameFileOutput = "caesarout.txt";
        InOROut(false);
        //Out();

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
                if (flag) { tmp += elem; }
                else { tmp += j; }

                alphabet.push_back(tmp);

                count++;
                if (flag) break;


            }
            if (!flag) break;

        }

        /* for (char i = BEGIN; i <= END; i++) {
             tmp.clear();
             tmp += elem;//!
             for (char j = BEGIN; j <= END; j++) {
                 if (j != BEGIN) {
                     tmp.pop_back();
                 }
                 tmp += j;//!
                 alphabet.push_back(tmp);
                 count++;

             }
             break;
         }*/

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

        for (int i = 0; i < alphabet.size(); i++) {
            cout << alphabet[i] << " ";
        }
    }


    void CaesarIn(string& tmp, ofstream& output, bool& flag) {
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

    void MYCaesarOut1(string& tmp, ofstream& output) {
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

    /*void In() {
          ifstream input("input.txt");
          ofstream output("caesarin.txt");

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
                          CaesarIn(tmp, output, flag);
                          i++;
                          output << '\n';
                          if (i == 2) { flag = true; }
                      }

                      if (tmp[i] == -1) {
                          tmp[i] = ' ';
                          CaesarIn(tmp, output, flag);
                          if (i == 2) { flag = true; }
                      }

                  }
                  if (input.eof()) { break; }
                  CaesarIn(tmp, output, flag);

              }
          }
          input.close();
          output.close();
      }*/

    void InOROut(bool value) { // true - in , false - out 
       // string nameFileInput = "";
        //string nameFileOutput = "";
       /* if (value) {
            this->nameFileInput = "input.txt";
            this-> nameFileOutput = "caesarin.txt";
        }
        else {
           this->nameFileInput = "caesarin.txt";
           this->nameFileOutput = "caesarout.txt";
        }*/
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
                        if (value) CaesarIn(tmp, output, flag);
                        else MYCaesarOut1(tmp, output);
                        i++;
                        output << '\n';
                        if (i == 2) { flag = true; }
                    }

                    if (tmp[i] == -1) {
                        tmp[i] = ' ';
                        if (value) CaesarIn(tmp, output, flag);
                        //else MYCaesarOut1(tmp, output);
                        if (i == 2) { flag = true; }
                    }

                }
                if (input.eof()) { break; }
                if (value) CaesarIn(tmp, output, flag);
                else MYCaesarOut1(tmp, output);

            }
        }
        input.close();
        output.close();
    }

    static bool cmp(const pair<string, double>& p1, const pair<string, double>& p2)
    {
        return p1.second > p2.second;
    }


    void MapStatisticsOREncrypted(bool flag, map<string, double>& alp_chislo, vector<pair<string, double> >& vectPair)
    {// false - Encrypted, true - MapStatistics
       // string NameFileInput = "";
        //string NameFileOutput = "";
        string tmp = "";
        int count = 0;
        double alpha2[837] = { 0.0 };
        if (flag) {
            this->nameFileInput = "zarinka.txt";
            this->nameFileOutput = "test.txt";
        }
        else {
            this->nameFileInput = "caesarin.txt";
            this->nameFileOutput = "vadimkapidr.txt";
        }
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
            alp_chislo[alphabet[i]] = (double)(((alpha2[i]) / (count / 2)));
        }

        copy(alp_chislo.begin(), alp_chislo.end(), back_inserter(vectPair));

        sort(vectPair.begin(), vectPair.end(), cmp);

        for (int i = 0; i < vectPair.size(); ++i)
            output << vectPair[i].first << " : " << vectPair[i].second << endl;


        input.close();
        output.close();

    }


    void MapStatistics() {

        ifstream input("zarinka.txt");
        ofstream output("test.txt");

        string tmp = "";
        int count = 0;
        double alpha2[837] = { 0.0 };


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
            alp_chisloZARINA[alphabet[i]] = (double)(((alpha2[i]) / (count / 2)));
        }

        copy(alp_chisloZARINA.begin(), alp_chisloZARINA.end(), back_inserter(vectZarina));

        sort(vectZarina.begin(), vectZarina.end(), cmp);

        for (int i = 0; i < vectZarina.size(); ++i)
            output << vectZarina[i].first << " : " << vectZarina[i].second << endl;

        input.close();
        output.close();
    }


    void MapEncrypted() {
        ifstream input("caesarin.txt");
        ofstream output("vadimkapidr.txt");

        string tmp = "";
        int count = 0;
        double alpha2[837] = { 0.0 };


        if (!input.is_open())
            cout << "Файл не может быть открыт!\n";
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
            alp_chisloVADIM[alphabet[i]] = (double)(((alpha2[i]) / (count / 2)));
        }



        copy(alp_chisloVADIM.begin(), alp_chisloVADIM.end(), back_inserter(vectVadim));

        sort(vectVadim.begin(), vectVadim.end(), cmp);

        for (int i = 0; i < vectVadim.size(); ++i)
            output << vectVadim[i].first << " : " << vectVadim[i].second << endl;

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
        cout << " vectVadim.size = " << vectVadim.size() << endl;
        int eblo = 0;
        int xyina = 0;
        bool otvet = false;
        cout << " vectZarina.size = " << vectZarina.size() << endl;
        while (!otvet) {
            pair< string, double> tmpZ = vectZarina[eblo];
            pair< string, double> tmpV = vectVadim[0];
            int countVadim = 0;
            int countZarina = 0;

            for (int i = 0; i < alphabet.size(); i++) {
                if (tmpZ.first == alphabet[i]) {
                    countZarina = i;
                    break;
                }
            }

            for (int i = 0; i < alphabet.size(); i++) {
                if (tmpV.first == alphabet[i]) {
                    countVadim = i;
                    break;
                }
            }

            this->key = mod(countZarina - countVadim, 26);
            this->nameFileInput = "caesarin.txt";
            this->nameFileOutput = "newout.txt";
            InOROut(false);
            /* ifstream input("caesarin.txt");
             ofstream output("newout.txt");

             string buff = "";
             string tmp1 = "";

             if (!input.is_open())
                 cout << "Файл не может быть открыт!\n";
             else {
                 while (!input.eof()) {
                     tmp1.clear();
                     for (int i = 0; i < 2; i++) {
                         tmp1 += input.get();

                         if (tmp1[i] == '\n') {
                             tmp1[i] = ' ';
                             MYCaesarOut1(tmp1, output);
                             i++;
                             output << '\n';

                         }

                     }

                     if (input.eof()) {
                         break;
                     }


                     MYCaesarOut1(tmp1, output);
                 }
             }
             input.close();
             output.close();*/

            cout << "Это ваш текст ?" << endl;
            ifstream file("newout.txt");
            string s;
            while (getline(file, s))
                cout << s << endl;
            int tmpOtvet;
            cin >> tmpOtvet;
            otvet = tmpOtvet;
            if (otvet == false) {
                eblo++;

            }
        }


    }

    /* void Out() {
          ifstream input("caesarin.txt");
          ofstream output("caesarout.txt");

          string buff = "";
          string tmp1 = "";

          if (!input.is_open())
              cout << "Файл не может быть открыт!\n";
          else {
              while (!input.eof()) {
                  tmp1.clear();
                  for (int i = 0; i < 2; i++) {
                      tmp1 += input.get();

                      if (tmp1[i] == '\n') {
                          tmp1[i] = ' ';
                          MYCaesarOut1(tmp1,output);
                          i++;
                          output << '\n';

                      }

                  }

                  if (input.eof()) {
                      break;
                  }



                  MYCaesarOut1(tmp1, output);
              }
          }
          input.close();
          output.close();
      }*/


    ~Cipher() {
        alp_chisloVADIM.clear();
        vectVadim.clear();
        alp_chisloZARINA.clear();
        alphabet.clear();
        vectZarina.clear();
    }

};
