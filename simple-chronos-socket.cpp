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

using namespace std;
using namespace boost;
using namespace Sync;


SimpleChronosSocket::SimpleChronosSocket (const string syncPrefix, boost::python::object callbackObject)
  : m_ccnxHandle (CcnxWrapper::Create ())
  , m_callbackObject (callbackObject)
  , m_syncLogic (syncPrefix,
                 bind(&SimpleChronosSocket::passCallback, this, _1),
                 bind(&SimpleChronosSocket::nullCallback, this, _1))
  , m_syncPrefix (syncPrefix)
{
}

SimpleChronosSocket::passCallback(const std::vector<MissingDataInfo> &v)
{
  int n = v.size();
  for (int i = 0; i < n; i++)
  {
     ostringstream interestName;
     interestName << v[i].prefix << "/" << v[i].high.getSession() << "/" << v[i].high.getSeq();
     m_callbackObject(interestName.str());
  }
}

SimpleChronosSocket::SimpleChronosSocket(const SimpleChronosSocket *other) 
{
  if (other == NULL)
  {
    this = NULL;
  }
  else
  {
    this = new SimpleChronosSocket(other->syncPrefix, other->m_callbackObject);
  }
}

SimpleChronosSocket::~SimpleChronosSocket()
{
  //CcnxWrapper::Destroy ();
  //CcnxWrapper::Create ();
}

bool 
SimpleChronosSocket::publishString (const string prefix, uint32_t session, const string dataBuffer, int freshness)
{
  uint32_t sequence = getNextSeq(prefix, session);
  ostringstream contentNameWithSeqno;
  contentNameWithSeqno << prefix << "/" << session << "/" << sequence;
  m_ccnxHandle->publishStringData (contentNameWithSeqno.str (), dataBuffer, freshness);

  SeqNo s(session, sequence + 1);
  m_sequenceLog[prefix] = s;

  m_syncLogic.addLocalNames (prefix, session, sequence);
}

uint32_t
SimpleChronosSocket::getNextSeq (const string &prefix, uint32_t session)
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


