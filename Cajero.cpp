#include <iostream>
#include <map>

using namespace std;

void menu(pair<int,string> &);
void depositar(pair<int,string>, float);
void retirar(pair<int,string>, float);
void modificarPin(pair<int,string> &);
bool validarPin(string);
void transferir(pair<int, string> &, pair<int, string> &, float);
void clear();

map<pair<int,string>, int> limite;
map<pair<int,string>, float> usuarios;

pair<int,string> p1 = {339420, "8484"};
pair<int,string> p2 = {246562, "0312"};
pair<int,string> p3 = {123456, "1234"};

int main(){


    pair<int,string> actual;

    usuarios[p1] = 100; 
    usuarios[p2] = 500.78; 
    usuarios[p3] = 1.5; 

    limite[p1] = 3;
    limite[p2] = 3;
    limite[p3] = 3;

    int id;
    string password;

    do{

        cout << "INICIO DE SESIÓN" << endl << endl;

        cout << "Ingresa tu id o salir (91):" << endl;

        cin >> id;

        clear();

        if(id == 91){
            return 0;
        }

        cout << "Introduce tu contraseña: " << endl;

        cin >> password;

        clear();

        actual.first = id;
        actual.second = password;

        if(usuarios.find(actual) != usuarios.end()){

            cout << "Inicio de sesion exitoso" << endl;
            menu(actual);

        } else {

            cout << "Credenciales inválidas" << endl;
        }

    }while(usuarios.find(actual) == usuarios.end() || id != 91);

}

void menu(pair<int, string> &user){

    int op;
    bool flag;
    float can;
    pair<int, string> targetuser;

    do {

        clear();

        cout << "Bienvenido al Cajero DIVA." << endl;
        cout << "\n"; 
        cout << " ___________________________" << endl;
        cout << "| Menu de opciones:         |" << endl;
        cout << "| 1. Consultar Saldo        |" << endl;
        cout << "| 2. Depositar              |" << endl;
        cout << "| 3. Retirar                |" << endl;
        cout << "| 4. Cambiar PIN            |" << endl;
        cout << "| 5. Realizar Transferencia |" << endl;
        cout << "| 6. Salir                  |" << endl;
        cout << " ___________________________" << endl;

        cout << "Ingrese la opcion deseada: ";

        if(!(cin >> op)){
            cout << "opción inválida" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (op)
        {
        case 1: //Consulta de saldo

            cout << "Su saldo es de: " << usuarios[user] << endl;
            
        break;
        
        case 2: //Deposito
            do{
                cout << "Introduzca la cantidad que desea depositar:" << endl;
                cout << "(Introduzca -1 si desea regresar)" << endl;

                if(!(cin >> can)) {
                    cout << "La cantidad debe ser un número" << endl;
                    cin.ignore();
                    cin.ignore(1000, '\n');
                }
                else{
                    if(can == -1){
                        break;
                    }

                    if(can < 0){
                        cout << "La cantidad debe ser un número positivo" << endl;
                    }
                    else{

                        cout << "Desea depositar " << can << " a su cuenta?" << endl;
                        cout << "1: SI"<< endl;
                        cout << "0: NO"<< endl;

                        cin >> flag;

                        if(flag){
                            depositar(user, can);
                        }
                        else{
                            break;
                        }
                    }
                }
            }while(can<0);

        break; 

        case 3: //Retiro
            if(limite[user]<=0){
                cout << "Se ha alcanzado el limite de retiros diarios" << endl;
                break;
            }

            do{
                cout << "Introduzca la cantidad que desea retirar:" << endl;
                cout << "(Introduzca -1 si desea regresar)" << endl;

                if(!(cin >> can)) {
                    cout << "La cantidad debe ser un número" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else{

                    if(can == -1){
                        break;
                    }

                    if(can < 0){
                        cout << "La cantidad debe ser un número positivo" << endl;
                    }
                    else{
                        retirar(user, can);
                        limite[user]--;
                    }
                }
            }while(can<0);
        break;

        case 4: //Cambio de pin

            modificarPin(user);

        break;

        case 5: //Transferir

            float can;

            cout << "Introduce el ID y pin de la cuenta a la que deseas transferir transferir" << endl;
            cout << "(Introduzca -1 si desea regresar)" << endl;

            cout << "Target ID:";

            cin >> targetuser.first;

            if(targetuser.first == -1){
                break;
            }

            cout << "Target Password:";

            cin >> targetuser.second;

            if(usuarios.find(targetuser) != usuarios.end()){

                cout << "Introduce la cantidad que deseas transferir" << endl;

                cin >> can;

                transferir(user, targetuser, can);
            }else{
                cout << "Usuario no encontrado..." << endl;
            }

        break;

        case 6:
            cout << "Saliendo...";
        break;

        case 1010:

            cout << "Usuario 339420: " << usuarios[{339420, "8484"}] << endl; 
            cout << "Usuario 246562: " << usuarios[{246562, "0312"}] << endl;
            cout << "Usuario 123456: " << usuarios[{123456, "1234"}] << endl;

        break;
        
        default:
            cout << "Opción inválida" << endl;
        break;
        }

        cout << endl << endl << endl;

    } while (op != 6);
}

void depositar(pair<int, string> user, float cantidad){
    usuarios[user] += cantidad; 
    cout << "Deposito de $" << cantidad << " exitoso";
}

void retirar(pair<int, string> user, float cantidad){
    
    if(usuarios[user]>=cantidad){
        usuarios[user] -= cantidad;
        cout <<" Retiro de $" << cantidad << " exitoso" << endl; 

    }else{
        cout << "No hay saldo suficiente" << endl;
    }
    
}

void modificarPin(pair<int, string> &user){
    string oldpin;
    string newpin;
    bool f;

    do{
        cout << "Introduce el viejo pin:" << endl;
        cout << "(Introduzca -1 si desea regresar)" << endl;

        cin >> oldpin;

        if(oldpin == "-1"){
            return;
        }

        if(user.second != oldpin){
            cout << "el pin es incorrecto" << endl;
        }else{

            do{
                cout << "Introduce el nuevo pin:" << endl;
                cin >> newpin;

                f = validarPin(newpin);

                if(!f){
                    cout << "el pin debe de contener solo números" << endl;
                }
            }while(!f);

            float saldo = usuarios[user];
            usuarios.erase(user);
            user.second = newpin;
            usuarios[user] = saldo;

        }
    }while(user.second != oldpin);
}

bool validarPin(string pin){
    for(char c: pin){
        if(!isdigit(c)){
            return false;
        }
    }

    return true;
}

void transferir(pair<int, string> &from, pair<int, string> &to, float can){
    if(can<=0){
        cout << "La cantidad debe ser mayor a 0" << endl;
        return;
    }

    if(from==to){
        cout << "No se pueden realizar transferencias a una misma cuenta";
        return;
    }
    
    if(usuarios.find(to) != usuarios.end()){
        if(usuarios[from]>=can){
            usuarios[from] -= can;
            usuarios[to] += can;
            cout << "Se transfirieron "<< can <<" unidades." << endl;
            return;
        }
        else{
            cout << "El remitente no tiene suficiente saldo." << endl;
            return;
        }
    }else{
        cout << "No se encontró la cuenta destino" << endl;
        return;
    }
}

void clear(){

    cout << "\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n";

}