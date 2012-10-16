#include <boost/python.hpp>
#include <string>
#include <iostream>
#include "world.h"

using namespace boost::python;

World::World(std::string phrase, object obj): m_phrase(phrase), m_obj(obj) {}

void
World::say()
{
  std::cout << m_phrase << std::endl;
}

