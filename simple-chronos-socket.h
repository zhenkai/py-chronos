/* -*- Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2012 University of California, Los Angeles
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Zhenkai Zhu <zhenkai@cs.ucla.edu>
 *         Chaoyi Bian <bcy@pku.edu.cn>
 *	   Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 */

#ifndef SIMPLE_CHRONOS_SOCKET_H
#define SIMPLE_CHRONOS_SOCKET_H

#include <boost/python.hpp>
#include <sync-logic.h>
#include <boost/function.hpp>
#include <boost/unordered_map.hpp>
#include <sync-seq-no.h>
#include <sync-ccnx-wrapper.h>
#include <utility>
#include <map>
#include <vector>
#include <sstream>

using namespace Sync;

/**
 * \ingroup sync
 * @brief A simple interface to interact with client code
 */
class SimpleChronosSocket
{
public:
  SimpleChronosSocket (std::string syncPrefix, boost::python::object callbackObject);
  ~SimpleChronosSocket ();

  bool publishString (std::string prefix, uint32_t session, std::string dataBuffer, int freshness);

  void remove (std::string prefix) {m_syncLogic->remove(prefix);}

  
private:
  void 
  passCallback( std::string name); 

  uint32_t
  getNextSeq (std::string &prefix, uint32_t session);


private:
  typedef boost::unordered_map<std::string, SeqNo> SequenceLog;
  boost::python::object m_callbackObject;
  SequenceLog m_sequenceLog;
  CcnxWrapperPtr m_ccnxHandle;
  boost::shared_ptr<SyncLogic>      m_syncLogic; 
};


#endif // SIMPLE_CHRONOS_SOCKET_H
