#include <boost/python.hpp>
#include "py_boost_function.hpp"
#include <sync/sync-app-socket.h>
#include <sync/sync-logic.h>
#include <sync/sync-ccnx-wrapper.h>
#include <sync-seq-no.h>

using namespace boost::python;
using namespace Sync;

template<class T>
struct vector_item
{
  typedef std::vector<T> Vector;

  static size_t size(Vector &self) { return self.size(); }
  static bool empty(Vector &self) { return self.empty(); }
  static void push_back(Vector &self, const T& x) { return self.push_back(x); }
};

BOOST_PYTHON_MODULE(chronos)
{

  def_function<void (const std::vector<MissingDataInfo> &, SyncAppSocket *)> 
  (
    "new_data_callback_t",
    "A callback function used for process new data"
  );

  def_function<void (const std::string)>
  (
    "remove_callback_t",
    "A callback function to process remove event"
  );

  def_function<void (std::string, const char *buf, size_t len)>
  (
    "raw_data_callback_t",
    "A callback function used by CcnxWrapper to process raw data"
  );

  def_function<void (std::string)>
  (
    "interest_callback_t",
    "A callback function to process Interest"
  );

  class_<SyncAppSocket>("SyncAppSocket", init<const std::string, boost::function< void (const std::vector<MissingDataInfo> &, SyncAppSocket * ) >, boost::function< void ( const std::string &/*prefix*/ ) > >())
    .def("get_next_seq", &SyncAppSocket::getNextSeq())
    .def("get_root_digest", &SyncAppSocket::getRootDigest())
    .def("publish_raw", &SyncAppSocket::publishRaw(const std::string &, uint32_t, const char *, size_t, int))
    .def("remove", &SyncAppSocket::remove(const std::string &))
    .def("fetch_raw", &SyncAppSocket::fetchRaw(const std::string &, const SeqNo &, boost::function<void (std::string, const char *buf, size_t len)> ))
    ;

  class_<SeqNo>("SeqNo", init<uint32_t seq>())
    .def("get_seq", &SyncAppSocket::getSeq())
    ;
  
  class_<MissingDataInfo>("MissingDataInfo")
    .def_readWrite("prefix", &MissingDataInfo::prefix)
    .def_readWrite("low", &MissingDataInfo::low)
    .def_readWrite("high", &MissingDataInfo::high)
    ;

}
