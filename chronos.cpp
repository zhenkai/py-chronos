#include <boost/python.hpp>
#include "simple-chronos-socket.h"

using namespace boost::python;


BOOST_PYTHON_MODULE(chronos)
{
  // we are going to mess with GIL, the infamous Global Interpreter Lock for python.
  // so we have to add this statement 
  PyEval_InitThreads();

  class_<SimpleChronosSocket>("SimpleChronosSocket", init<std::string, object>())
    .def("publish_string", &SimpleChronosSocket::publishString)
    .def("remove", &SimpleChronosSocket::remove)
    .def("callback", &SimpleChronosSocket::passCallback)
  ;
}
