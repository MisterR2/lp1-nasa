#include <iostream>
#include <ctime>
#include <chrono>
#include <sstream>
#include <cctype>
#include <typeinfo>
#include <limits>

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
    int filterFlights;
    int filterAstronauts;

    Flight* flight = nullptr;
    Astronaut* astronaut = nullptr;
    

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
        cout << "6 - Remover astronauta de voo" << endl;
        cout << "7 - Lançar voo" << endl;
        cout << "8 - Finalizar voo" << endl;
        cout << "9 - Explodir voo" << endl;
        cout << "10 - Sair" << endl;
        cout << "Escolha uma opção: ";
        
        // Obter a escolha do usuário
        cin >> option;

        // Verificar se a entrada foi inválida
        if (cin.fail()) {
            // Limpar o estado de erro
            cin.clear();
            // Ignorar a entrada inválida
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opção inválida! Por favor, insira um número." << endl;
            // Pausar a execução para que o usuário possa ver a mensagem
            cout << "Pressione Enter para continuar...";
            cin.get();
            continue; // Voltar ao início do loop
        }

        // Processar a option do usuário
        switch(option) {
            case 1:
                system("clear");
                cout << "============CADASTRO DE ASTRONAUTAS============" << endl;
                 do {
                    cout << "Insira o nome do astronauta: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, name);

                    if (name.empty()) {
                        cout << "O nome não pode estar vazio. Por favor, insira novamente." << endl;
                    }else{
                        break;
                    }
                } while (name.empty());

                do {
                    cout << "Insira a idade do astronauta: ";
                    cin >> age_str;
                    
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
                system("clear");
                cout << "============CADASTRO DE VOOS============" << endl;
                newCode = stoi(generateIdentity(3));
                flight = new Flight(newCode);
                flight->listPassengers();
                break;

            case 3:
                system("clear");
                cout << "============INSERÇÃO DE ASTRONAUTA EM VOOS============" << endl;
                
                Astronaut::listAstronauts(2);
                cout << endl;
                Flight::listFlights(2);
                cout << endl;

                cout << "Insira o código do voo (ou '0' para voltar ao menu): ";
                cin >> flightCode;
                
                if (cin.fail() || flightCode == 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                cout << "Insira o CPF do astronauta (ou '0' para voltar ao menu): ";
                cin >> passengerID;
                
                if (passengerID == "0") {
                    break; // Voltar ao menu principal
                }

                Flight::addPassenger(flightCode, passengerID);
                break;

            case 4:
                system("clear");
                cout << "============LISTAGEM DE ASTRONAUTAS============" << endl;
                cout << "Menu:" << endl;
                cout << "1 - Listar todos os astronautas" << endl;
                cout << "2 - Listar apenas astronautas disponíveis" << endl;
                cout << "3 - Listar apenas astronautas indisponíveis" << endl;
                cout << "4 - Listar apenas astronautas mortos" << endl;
                cout << "Escolha uma opção: ";

                cin >> filterAstronauts;

                if (cin.fail()) {
                    // Limpar o estado de erro
                    cin.clear();
                    // Ignorar a entrada inválida
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Opção inválida! Por favor, insira um número." << endl;
                    // Pausar a execução para que o usuário possa ver a mensagem
                    cout << "Pressione Enter para continuar...";
                    cin.get();
                    continue; // Voltar ao início do loop
                }else
                {
                    Astronaut::listAstronauts(filterAstronauts);
                }

                
                break;
            case 5:
                system("clear");
                cout << "============LISTAGEM DE VOOS============" << endl;
                cout << "Menu:" << endl;
                cout << "1 - Listar todos os voos" << endl;
                cout << "2 - Listar apenas voos planejados" << endl;
                cout << "3 - Listar apenas voos em curso" << endl;
                cout << "4 - Listar apenas voos finalizados" << endl;
                cout << "Escolha uma opção: ";
                cin >> filterFlights;

                if (cin.fail()) {
                    // Limpar o estado de erro
                    cin.clear();
                    // Ignorar a entrada inválida
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Opção inválida! Por favor, insira um número." << endl;
                    // Pausar a execução para que o usuário possa ver a mensagem
                    cout << "Pressione Enter para continuar...";
                    cin.get();
                    continue; // Voltar ao início do loop
                }else
                {
                    Flight::listFlights(filterFlights);
                }
                

                
                break;
            
            case 6:
                cout << "============REMOÇÃO DE ASTRONAUTAS DE VOOS============" << endl;
                system("clear");
                cout << "Insira o código do voo: " << endl;
                cin >> flightCode;

                cout << "Insira o CPF do astronauta: " << endl;
                cin >> passengerID;

                Flight::removePassenger(flightCode, passengerID);

                break;
            case 7:
                cout << "============LANÇAMENTO DE VOOS============" << endl;
                system("clear");
                Flight::listFlights(2);
                cout << endl;
                cout << "Insira o código do voo a ser lançado: " << endl;
                cin >> flightCode;

                Flight::launchFlight(flightCode);

                break;
            case 8:
                cout << "============FINALIZAÇÃO DE VOOS============" << endl;
                system("clear");
                Flight::listFlights(3);
                cout << endl;
                cout << "Insira o código do voo a ser finalizado: " << endl;
                cin >> flightCode;

                Flight::finishFlight(flightCode);

                break;
            case 9:
                cout << "============DETONAÇÃO DE VOOS============" << endl;
                system("clear");
                Flight::listFlights();
                cout << endl;
                cout << "Insira o código do voo a ser explodido: " << endl;
                cin >> flightCode;
            
                Flight::explodeFlight(flightCode);

                break;
            case 10:
                system("clear");
                cout << "Saindo..." << endl;
                break;
            default:
                system("clear");
                cout << "Opção inválida! Tente novamente." << endl;
                break;
        }

        // Pausar a execução para que o usuário possa ver a mensagem
        cout << "Pressione Enter para continuar...";
        cin.ignore(); // Limpar o buffer de entrada
        cin.get();    // Aguardar o Enter

    } while (option != 10);

    return 0;
}
