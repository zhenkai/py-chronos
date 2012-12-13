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

#include "simple-chronos-socket.h"
#include <vector>

using namespace std;
using namespace boost;
using namespace Sync;


SimpleChronosSocket::SimpleChronosSocket (string syncPrefix, boost::python::object callbackObject)
  : m_ccnxHandle (new CcnxWrapper())
  , m_callbackObject (callbackObject)
  , m_syncLogic (new SyncLogic(syncPrefix,
                 bind(&SimpleChronosSocket::passCallback, this, _1)))
{
  cout << "Creating SimpleChronosSocket" << std::endl;
}

SimpleChronosSocket::~SimpleChronosSocket()
{
  cout << "Destroying SimpleChronosSocket" << std::endl;
}

void
SimpleChronosSocket::passCallback(std::string name)
{
  AcquireGIL lock;
  m_callbackObject(name);
}

void 
SimpleChronosSocket::stop()
{
  m_syncLogic->stop();
}

bool 
SimpleChronosSocket::publishString ( string prefix, uint32_t session,  string dataBuffer, int freshness)
{
  uint32_t sequence = getNextSeq(prefix, session);
  ostringstream contentNameWithSeqno;
  contentNameWithSeqno << prefix << "/" << session << "/" << sequence;
  m_ccnxHandle->publishStringData (contentNameWithSeqno.str (), dataBuffer, freshness);

  SeqNo s(session, sequence + 1);
  m_sequenceLog[prefix] = s;

  m_syncLogic->addLocalNames (prefix, session, sequence);
  return true;
}

uint32_t
SimpleChronosSocket::getNextSeq (string &prefix, uint32_t session)
{
  SequenceLog::iterator i = m_sequenceLog.find (prefix);

  if (i != m_sequenceLog.end ())
    {
      SeqNo s = i->second;
      if (s.getSession() == session)
        return s.getSeq();
    }
  return 0;
}


