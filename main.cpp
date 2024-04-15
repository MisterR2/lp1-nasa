#include <iostream>
#include <ctime>
#include <chrono>
#include <sstream>
#include <cctype>

using std::cout;
using std::cin;

using namespace std;
#include "astronaut.h"
#include "flight.h"

string generateIdentity(int length){
    ostringstream oss;
    auto now = chrono::system_clock::now();
    time_t current_time = chrono::system_clock::to_time_t(now);
    // Usar o tempo atual como uma seed para srand
    srand(static_cast<unsigned>(current_time));
    string rndId;

    for (int i = 0; i < length; ++i) {
        oss << rand() % 10;
    }

    rndId = oss.str();

    if ( Astronaut::isIdUsed(rndId) && length == 11)
    {
        return generateIdentity(length);
    }
    

    return rndId;
}

bool isInteger(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int main(){
    int option;
    string name;
    int age;
    string age_str;
    size_t space_pos;
    int newCode;
    int flightCode;
    string passengerID;

    Flight* flight = nullptr;
    Astronaut* astronaut = nullptr;

    // Criar um objeto ostringstream para construir a string
    
    
    // Obter o tempo atual
    

    do {
        // Limpar a tela do console
        system("clear");

        // Exibir o menu
        cout << "Menu:" << endl;
        cout << "1 - Cadastrar astronauta" << endl;
        cout << "2 - Cadastrar voo" << endl;
        cout << "3 - Cadastrar astronauta em voo" << endl;
        cout << "4 - Listar astronautas" << endl;
        cout << "5 - Listar Voos" << endl;
        cout << "10 - Sair" << endl;
        cout << "Escolha uma opção: ";
        
        // Obter a escolha do usuário
        cin >> option;

        // Processar a option do usuário
        switch(option) {
            case 1:
                cout << "Você escolheu a Opção 1." << endl;

                cout << "Insira o nome do astronauta: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);

                do {
                    cout << "Insira a idade do astronauta: ";
                    cin >> age_str;

                    // Verificar se a idade é um inteiro
                    if (!isInteger(age_str)) {
                        cout << "Idade inserida não é um inteiro. Por favor, insira novamente." << endl;
                        continue;
                    }

                    // Converter a idade para inteiro
                    age = stoi(age_str);

                } while (age_str.empty() || age < 0 || !isInteger(age_str));
                
                astronaut = new Astronaut(generateIdentity(11), name, age);

                break;

            case 2:
                cout << "Você escolheu a Opção 2." << endl;
                newCode = stoi(generateIdentity(3));
                flight = new Flight(newCode);
                flight->getPassengers();
                break;

            case 3:
                cout << "Você escolheu a Opção 3." << endl;
                
                cout << "Insira o código do voo: " << endl;
                cin >> flightCode;

                cout << "Insira o CPF do astronauta: " << endl;
                cin >> passengerID;

                Flight::addPassenger(flightCode, passengerID);
                break;

            case 4:
                cout << "Você escolheu a Opção 4." << endl;
                Astronaut::listAstronauts();
                break;
            case 5:
                cout << "Você escolheu a Opção 5." << endl;
                Flight::listFlights();
                break;
            case 10:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opção inválida! Tente novamente." << endl;
        }

        // Pausar a execução para que o usuário possa ver a mensagem
        cout << "Pressione Enter para continuar...";
        cin.ignore(); // Limpar o buffer de entrada
        cin.get();    // Aguardar o Enter

    } while (option != 10);

    return 0;
}
