#include <boost/python.hpp>
#include <string>
#include <iostream>
#include "world.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(hello)
{
  class_<World>("World", init<std::string, object>())
    .def("say", &World::say)
    ;
}
