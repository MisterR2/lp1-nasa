#include "flight.h"

Flight::Flight(int code)
{
    this->code = code;
}

int Flight::getCode()
{
    return code;
}

void Flight::getPassengers()
{   
    if (passengers.size() == 0)
    {
        cout << "Não há passageiros cadastrados para esse voo" << endl;
    }
    else
    {
        for (Astronaut astronaut : passengers) {
            cout << "Nome: " << astronaut.getName() << ", CPF: " << astronaut.getIdentity();
    }
    }
    
    
}