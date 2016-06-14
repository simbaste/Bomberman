#include <string>
#include "Excep.hpp"

Excep::Excep(std::string const& phrase, int numero, int niveau) throw()
    :_numero(numero),_chain(phrase),_niveau(niveau)
{
}

const char* Excep::what() const throw() 
{
   return _chain.c_str();
}

int Excep::getNiveau() const throw()

{
  return _niveau;
}

Excep::~Excep() throw(){}
