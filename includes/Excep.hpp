//
// Excep.hpp for  in /home/grenet_j/rendu/C++/cpp_indie_studio/src
// 
// Made by Jérémy Grenet
// Login   <grenet_j@epitech.net>
// 
// Started on  Sun Jun  5 20:06:08 2016 Jérémy Grenet
// Last update Sun Jun  5 22:49:16 2016 louis Dauvois
//

#ifndef EXCEP_HPP
# define EXCEP_HPP
#include <iostream>
#include <exception>

class	Excep : std::exception
{
public:
  Excep(std::string const& phrase="", int numero=0,int niveau=0) throw();

  virtual const char* what() const throw();
  int getNiveau() const throw();

  virtual ~Excep() throw();
private:
  int		_numero;               //Numéro de l'erreur
  std::string	_chain;            //Description de l'erreur
  int		_niveau;               //Niveau de l'erreur
};

#endif
