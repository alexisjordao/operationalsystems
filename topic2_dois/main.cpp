#include "../../BlackLib/v3_0/BlackGPIO/BlackGPIO.h"
#include<unistd.h>
#include<cstdlib>
#include<sys/types.h>
#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<sstream>
#include<ctime>
#include<sys/wait.h>
using namespace std;
#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"

int readAnalog(int number){
   stringstream ss;
   ss << PATH_ADC << number << "_raw";
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> number;
   fs.close();
   return number;
}

int main(int argc, char *argv[])
{
    ofstream myfile;

    // Identificador do processo
    pid_t idProcesso, idProcesso_2, idProcesso_3, idProcesso_4;

    BlackLib::BlackGPIO   ledR(BlackLib::GPIO_60,BlackLib::output, BlackLib::SecureMode);
    BlackLib::BlackGPIO   ledG(BlackLib::GPIO_50,BlackLib::output, BlackLib::SecureMode);
    BlackLib::BlackGPIO   ledB(BlackLib::GPIO_51,BlackLib::output, BlackLib::SecureMode);

    printf("Iniciando o programa\n");



    // Criando o processo
    idProcesso = fork();

    for(int i=0; i<4; i++){
    switch(idProcesso){
        case -1:       // erro na geração do processo filho
            exit(1);
        case 0:        // retorno de fork para processo filho 1
            for (int i=0;i<10;i++){
                printf("Sou o processo filho ID: %d\n",getpid());
                        ledR.setValue(BlackLib::high);
                        ledG.setValue(BlackLib::low);
                        ledB.setValue(BlackLib::low);
                        sleep(2);
                        ledR.setValue(BlackLib::low);
                        ledG.setValue(BlackLib::low);
                        ledB.setValue(BlackLib::low);

                        myfile.open ("filho_1.txt");
                        myfile << time(NULL) << endl << "Vou ligar o LED vermelho.\n";
                        myfile.close();
            }
            break;
        default:
        idProcesso_2 = fork();
        switch(idProcesso_2){
            case -1:       // erro na geração do processo filho
                exit(1);
            case 0:        // retorno de fork para processo filho 2
                for (int i=0;i<10;i++){
                    printf("Sou o processo filho ID: %d\n",getpid());
                    ledR.setValue(BlackLib::low);
                            ledG.setValue(BlackLib::high);
                            ledB.setValue(BlackLib::low);
                            sleep(3);
                            ledR.setValue(BlackLib::low);
                            ledG.setValue(BlackLib::low);
                            ledB.setValue(BlackLib::low);

                            myfile.open ("filho_2.txt");
                            myfile << time(NULL) << endl << "Vou ligar o LED verde.\n";
                            myfile.close();
                }
                break;
            default:
            idProcesso_3 = fork();
            switch(idProcesso_3){
                case -1:       // erro na geração do processo filho
                    exit(1);
                case 0:        // retorno de fork para processo filho 3
                    for (int i=0;i<10;i++){
                        printf("Sou o processo filho ID: %d\n",getpid());
                        ledR.setValue(BlackLib::low);
                                ledG.setValue(BlackLib::low);
                                ledB.setValue(BlackLib::high);
                                sleep(4);
                                ledR.setValue(BlackLib::low);
                                ledG.setValue(BlackLib::low);
                                ledB.setValue(BlackLib::low);

                                myfile.open ("filho_3.txt");
                                myfile << time(NULL) << endl << "Vou ligar o LED azul.\n";
                                myfile.close();
                    }
                    break;
                default:
                idProcesso_4 = fork();
                switch(idProcesso_4){
                    case -1:       // erro na geração do processo filho
                        exit(1);
                    case 0:        // retorno de fork para processo filho 4
                        for (int i=0;i<10;i++){
                            printf("Sou o processo filho ID: %d\n",getpid());
                            int valor = readAnalog(1);
                               cout << "O valor lido foi " << valor << " [0 a 4095]." << endl;
                               cout << "O valor corresponde a " << (valor*1.8)/4096 << "V" << endl;
                               return 0;

                               myfile.open ("filho_4.txt");
                               myfile << time(NULL) << endl << "O valor do potenciometro é: .\n";
                               myfile.close();
                            }
                        }
                        break;
    }


                wait(NULL);
                cout << "Got " << i+1 << " done" << endl;
}

        int status;

        waitpid(idProcesso,&status, 0);
        waitpid(idProcesso_2,&status, 0);
        waitpid(idProcesso_3,&status, 0);
        waitpid(idProcesso_4,&status, 0);

    printf("O processo com ID: %d finalizou!!!!\n",getpid());
    return 0;
}
}
}
