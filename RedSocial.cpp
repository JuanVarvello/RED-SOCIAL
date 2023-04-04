#include "RedSocial.h"
#include <string>
#include <set>

using namespace std;

RedSocial::RedSocial(){
    amistades = 0; //inicializo cant de AMISTADES
}

const set<int> & RedSocial::usuarios() const{
    return this->ids;
}
string RedSocial::obtener_alias(int id) const{
    auto it = (this->id_usuario).find(id); //busco en el MAP la LLAVE(ID) que me da el valor USER(SUS ATRIBUTOS: ALIAS) y asigno USER a IT.
    string _alias = it->second.alias; //busco el atributo ALIAS del USER
    return _alias;
}
const set<string> & RedSocial::obtener_amigos(int id) const{
    auto it = (this->id_usuario).find(id); //busco en el MAP la LLAVE(ID) que me da el valor USER(SUS ATRIBUTOS: ALIAS) y asigno USER a IT.
    return it->second.amigos; //devuelvo sus AMIGOS
}
int RedSocial::cantidad_amistades() const{
    return this->amistades; //Devuelvo las AMISTADES
}

void RedSocial::registrar_usuario(string alias, int id){
    set<string> amigos; 
    user usuario_X;
    usuario_X.alias = alias; //asigno atributos de USER
    usuario_X.amigos = amigos;
    (this->ids).insert(id); //registro el ID
    id_usuario.insert(make_pair(id, usuario_X)); //vinculo ID con es USER
}

void RedSocial::eliminar_usuario(int id){ 
    
    //elimino el ID del usuario del set de IDs
    auto it1 = (this->ids).begin();
    while(it1 != ids.end()){
        if((*it1) == id){
            it1 = ids.erase(it1);
        }else{
            ++it1;
        }
    }

    //obtengo datos del usuario a eliminar
    string alias_a_eliminar = obtener_alias(id);
    set<string> amistades_a_borrar = obtener_amigos(id); 
    
    //tengo que entrar a todos los USUARIOS que sean sus amigos para eliminar el ALIAS de sus listas de amigos.

    auto it2 = amistades_a_borrar.begin();

    while(it2 != amistades_a_borrar.end()){

        int id2 = obtener_id(*it2); // obtengo el ID de los amigos del usuario a eliminar
        auto it3 = (this->id_usuario).find(id2); // encuentro sus ubicaciones dentro del MAP
        auto it4 = (it3->second.amigos).begin(); // accedo a sus listas de amigos.
        
        //itero dentro de las listas hasta encontrar el ALIAS del usuario que quiero eliminar
        while(it4 != (it3->second.amigos).end()){
            if(*it4 == alias_a_eliminar){
                (it3->second.cantidad_amigos)-- ;
                (this->amistades)--;
                (it3->second.amigos).erase(*it4); //elimino el ALIAS de lista de amigos.
                break; //como el ALIAS se repite una sola vez, puedo pasar al siguiente amigo.
            }else{
                it4++;
            }
        }

        it2++;
    }

    // Una vez finalizado, elimino del MAP la clave y el valor del usuario a eliminar
    auto it6 = (this->id_usuario).find(id);
    id_usuario.erase(it6);
}

void RedSocial::amigar_usuarios(int id_A, int id_B){
    auto itA = id_usuario.find(id_A); //ENCUENTRO USUARIO A
    auto itB = id_usuario.find(id_B); //ENCUENTRO USUARIO B

    (itA->second.amigos).insert(itB->second.alias); //AGREGO A LISTA DE AMIGOS DE A EL ALIAS DEL USUARIO B
    (itA->second.cantidad_amigos)++; //INCREMENTO CANTIDAD DE AMIGOS DE A
    (itB->second.amigos).insert(itA->second.alias); //AGREGO B LISTA DE AMIGOS DE A EL ALIAS DEL USUARIO A
    (itB->second.cantidad_amigos)++; //INCREMENTO CANTIDAD DE AMIGOS DE B
    
    (this->amistades)++; //INCREMENTO LA CANTIDAD DE AMISTADES

}
void RedSocial::desamigar_usuarios(int id_A, int id_B){
    auto itA = id_usuario.find(id_A); //ENCUENTRO USUARIO A
    auto itB = id_usuario.find(id_B); //ENCUENTRO USUARIO B

    (itA->second.amigos).erase(itB->second.alias); //BORRO EL ALIAS DEL USUARIO B DE LA LISTA DE AMIGOS DE A
    (itA->second.cantidad_amigos)--; //DECREMENTO CANTIDAD DE AMIGOS DE A
    (itB->second.amigos).erase(itA->second.alias); //BORRO EL ALIAS DEL USUARIO A DE LA LISTA DE AMIGOS DE B
    (itB->second.cantidad_amigos)--; //DECREMENTO CANTIDAD DE AMIGOS DE B

    (this->amistades)--; //DECREMENTO LA CANTIDAD DE AMISTADES

}

int RedSocial::obtener_id(string alias) const{

    int id;
    auto it = this->id_usuario.begin(); //posiciono el IT en el INICIO

    while(it != id_usuario.end()){ //recorro todos los usuarios

        if(it->second.alias == alias){ //si el alias del USUARIO es igual al DADO, devuelvo su ID
            id = it->first;
            break; //ya encontrado el ID, corto la busqueda.
        }
        it++;
    }

    return id;
}

const set<string> & RedSocial::amigos_del_usuario_mas_popular() const{

    //USO 2 ITERADORES PARA COMPARAR LOS USUARIOS
    auto it1 = (this->id_usuario).begin();
    auto it2 = (this->id_usuario).begin();
    it2++;

    int id_mas_popular;

    //COMPARO EL TAMAÑO DE LAS LISTAS DE AMIGOS DE LOS USUARIOS
    while(it1 != id_usuario.end() && it2 != id_usuario.end()){

        if((it1->second.cantidad_amigos) > (it2->second.cantidad_amigos)){ //AMIGOS DE 1 > AMIGOS DE 2
            id_mas_popular = it1->first;
            it2++;
        }else{ //AMIGOS DE 1 < AMIGOS DE 2
            id_mas_popular = it2->first;
            it1++;
        }
    }
    return obtener_amigos(id_mas_popular);
}