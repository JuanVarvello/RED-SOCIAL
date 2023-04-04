#ifndef __REDSOCIAL_H__
#define __REDSOCIAL_H__

#include <string>
#include <set>
#include <map>


class RedSocial{
  public:
    RedSocial();    

    const std::set<int> & usuarios() const; // O(1)
    std::string obtener_alias(int id) const; // O(log n)
    const std::set<std::string> & obtener_amigos(int id) const; // O(log n)
    int cantidad_amistades() const; // O(1)

    void registrar_usuario(std::string alias, int id); // O(log n)
    void eliminar_usuario(int id); // sin requerimiento
    void amigar_usuarios(int id_A, int id_B); // sin requerimiento
    void desamigar_usuarios(int id_A, int id_B); // sin requerimiento
    
    int obtener_id(std::string alias) const; // sin requerimiento
    const std::set<std::string> & amigos_del_usuario_mas_popular() const; // O(1)

  private:

    struct user{
      std::string alias; 
      std::set<std::string> amigos;
      int cantidad_amigos = amigos.size();
    };

    std::set<int> ids; //Set de IDs de todos los usuarios
    
    std::map<int, user> id_usuario; //Vincular los IDS con los USERS(atributos)

    int amistades;
/* 
REP:

-amistades: debe ser un valor entero mayor o igual a cero.
-ids: debe ser un conjunto de valores enteros que no se repiten.
-id_usuario: debe ser un map que tenga como llaves valores enteros y como valores, variables de tipo user. 
-user:
   -alias: debe ser un string que como maximo tenga 100 caracteres.
   -amigos: debe ser un conjunto de strings donde no habra strings repetidos 
    y la longitud de cada string debe ser como maximo 100 caracteres.
  -cantidad_amigos: debe ser una cantidad entera mayor o igual a cero.
*/
};

#endif