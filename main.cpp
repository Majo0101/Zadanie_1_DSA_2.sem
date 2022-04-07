#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

#define input "slovnik.txt"
#define output "out.txt"

int choose = 0;              //choice
int loop = 0;                //program loop
char set_word[36];           //longest slovak word
char read_word[30][36];      //read word from slovnik
char read_sentence[30][60];  //read sentence from slovnik

using namespace std;

ofstream out(output);

void start(){
    cout
     << endl << endl << "Choose one option" << endl
     << "1. Starting" << endl
     << "2. Containing" << endl
     << "3. Ending" << endl
     << "4. Stop" << endl;

    out
    << endl << endl << "Choose one option" << endl
    << "1. Starting" << endl
    << "2. Containing" << endl
    << "3. Ending" << endl
    << "4. Stop" << endl;

    choose = getchar();  // read choice

    if (choose < '1' || choose > '4') {
        cout << "Bad choice!!!" << endl;                                                 out << "Bad choice!!!" << endl;
    }
    else {
        cout << endl << "Your choice is: " << (char)choose << endl << endl;
                                                      out << endl << "Your choice is: " << (char)choose << endl << endl;
    }

} // menu with the char input

void number1(){
    cout << "Use small letters without diacritics" << endl;
                                                                  out << "Use small letters without diacritics" << endl;
    cout << "Enter the first three characters of the word" << endl;
                                                          out << "Enter the first three characters of the word" << endl;
    cin >> set_word;

    int i = 0;
    int result ;
    int words = 0;
    int catch_word = 0;

    cout << endl << "Results..." << endl << endl;                           out << endl << "Results..." << endl << endl;

    while(true){

        result = strncmp(set_word, read_word[i], 3);

        if (result == 0){
            if (words == 0){
                cout << read_word[i];                                                               out << read_word[i];
            }else{
                cout << endl << read_word[i];                                               out << endl << read_word[i];
            }

            words++;
            catch_word = i;
        }

        i++;

        if(i > 30)
            break;
    }

    if (words == 1){
        cout << "-"<< read_sentence[catch_word] << endl;                 out << "-"<< read_sentence[catch_word] << endl;
    }

    if (words == 0){
        cout << endl << "NO MATCH!!!" << endl;                                     out << endl << "NO MATCH!!!" << endl;
    }
} // compare first n characters

void number2(){
    cout << "Use letters without diacritics" << endl;                   out << "Use letters without diacritics" << endl;
    cout << "Enter the all characters in the word" << endl;       out << "Enter the all characters in the word" << endl;
    cin >> set_word;

    int i = 0;
    int result ;
    int check = 0;

    while(true){

        result = strcmpi(set_word , read_word[i]); //string compare

        if(result == 0){
            cout << "Results..." << endl;                                                   out << "Results..." << endl;
            cout << read_word[i]<< "-" << read_sentence[i];               out << read_word[i]<< "-" << read_sentence[i];
            check++;
        }

        i++;

        if(i > 30)
            break;
    }

    if(check <= 0){
        cout << endl << "NO MATCH!!!" << endl;                                     out << endl << "NO MATCH!!!" << endl;
    }
} // compare word

void number3(){
    cout << "Use letter without diacritics" << endl;                     out << "Use letter without diacritics" << endl;
    cout << "Enter the last character in the word" << endl;       out << "Enter the last character in the word" << endl;
    cin >> set_word;

    int i = 0;
    int result;
    int words = 0;
    int catch_word = 0;

    cout << "Results..." << endl;                                                           out << "Results..." << endl;

    while(true){

        result = strcmpi(set_word , read_word[i] + strlen(read_word[i])-1); //string compare

        if (result == 0){
            if (words == 0){
                cout << read_word[i];                                                               out << read_word[i];
            }else{
                cout << endl << read_word[i];                                               out << endl << read_word[i];
            }
            catch_word = i;
            words++;
        }
        i++;

        if (i > 30)
            break;
    }

    if (words == 1){
        cout << "-" << read_sentence[catch_word] << endl;               out << "-" << read_sentence[catch_word] << endl;
    }

    if (words == 0){
        cout << endl << "NO MATCH!!!" << endl;                                     out << endl << "NO MATCH!!!" << endl;
    }
} // compare last character

void read_slovnik(){

    int i = 0;
    int MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];  //read line from slovnik
    char *token0;
    char *token1;
    int add0 ;
    int add1 ;


    FILE *read;
    read = fopen(input , "r");

    if(!read){
        cout << "File does not exist!!" << endl;                                 out << "File does not exist!!" << endl;
        exit (-1);
    }
    else{
        while(fgets(buffer, MAX_LENGTH, read)) {

            token0 = strrchr(buffer, ';') + 1;
            if(token0[0] == ' ') token0++;
            strcpy(read_sentence[i], token0);

            token1 = strtok(buffer, ";" );
            strcpy(read_word[i], token1);

            i++;

            add0 = (int)strlen(token0);
            add1 = (int)strlen(token1);

            if(add0 > 60){
                cout << "Wrong sentence in the buffer" << endl;           out << "Wrong sentence in the buffer" << endl;
                exit(-3);
            }

            if(add1 > 36){
                cout << "Wrong word in the buffer" << endl;                   out << "Wrong word in the buffer" << endl;
                exit(-4);
            }
        }

    }

    if(fclose(read) == EOF){
        cout << "Error..." << endl;                                                           out << "Error..." << endl;
        exit(-2);
    }
    else{
        cout << "'slovnik' found..." << endl;                                       out << "'slovnik' found..." << endl;
    }
} // Slovnik

int main() {

    read_slovnik();

    for(loop=0; loop < 2; loop++ ) {

        start();

        if(choose == 49){     //choice 1
            number1();
        }

        if(choose == 50){     //choice 2
            number2();
        }

        if(choose == 51){     //choice 3
            number3();
        }

        if (choose == 52) {   //jump out from loop
            cout << "Thank you, Bye" << endl;                                           out << "Thank you, Bye" << endl;
            loop = 4;
        }

        fflush(stdin); //clear getchar

        memset(set_word,0,strlen(set_word)); //clear array

        loop--; //loop counter

    }

    out.close();

    return 0;
}
