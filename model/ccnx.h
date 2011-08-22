/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2011 University of California, Los Angeles
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
 * Author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 */

#ifndef _CCNX_H_
#define _CCNX_H_

#include "ns3/object.h"
#include "ns3/socket.h"
#include "ns3/callback.h"

#include "ccnx-face.h"

namespace ns3 {

class Node;
class NetDevice;
class Packet;
class CcnxForwardingStrategy;

/**
 * \defgroup ccnx NDN abstraction
 *
 * This is an abstract implementation of NDN protocol
 */
/**
 * \ingroup ccnx
 * \brief Interface to manage Ccnx stack
 *
 * This class defines the API to manipulate the following aspects of
 * the Ccnx stack implementation:
 * -# register a face (CcnxFace-derived object) for use by the Ccnx
 *    layer
 * -# register forwarding strategy (CcnxForwardingStrategy-derived
 *    object) to use by Ccnx stack
 * -# export Ccnx configuration attributes
 * 
 * Each CcnxFace-derived object has conceptually a single Ccnx
 * interface associated with it.
 *
 * In addition, this class defines CCNx packet coding constants
 *
 * \see CcnxFace, CcnxForwardingStrategy
 */
class Ccnx : public Object
{
public:
  /**
   * \brief Interface ID
   *
   * \return interface ID
   */
  static TypeId GetTypeId ();

  /**
   * \brief Send a packet to a specified face
   *
   * \param face face where to send this packet
   * \param packet fully prepared CCNx packet to send
   *
   * Higher-level layers (forwarding strategy in particular) call this
   * method to send a packet down the stack to the MAC and PHY layers.
   */
  virtual void
  Send (const Ptr<CcnxFace> &face, const Ptr<Packet> &packet) = 0;

  /**
   * \brief Lower layers calls this method after demultiplexing
   *
   * Lower-layer-dependent implementation of CcnxFace will do actual work
   * to set up demultiplexing and call this function as a callback
   *
   * \param face face from which packet came from
   * \param p the packet
   */
  virtual void
  Receive (const Ptr<CcnxFace> &face, const Ptr<const Packet> &p) = 0;

  /**
   * \brief Register a new forwarding strategy to be used by this Ccnx
   * stack
   *
   * This call will replace any forwarding strategy that has been
   * previously registered.
   * 
   * \param forwardingStrategy smart pointer to CcnxForwardingStrategy
   * object
   */
  virtual void
  SetForwardingStrategy (Ptr<CcnxForwardingStrategy> forwardingStrategy) = 0;

  /**
   * \brief Get the forwarding strategy being used by this Ccnx stack
   * 
   * \returns smart pointer to CcnxForwardingStrategy object, or null
   * pointer if none
   */
  virtual Ptr<CcnxForwardingStrategy>
  GetForwardingStrategy (void) const = 0;

  /**
   * \brief Add face to CCNx stack
   *
   * \param face smart pointer to CcnxFace-derived object
   * (CcnxLocalFace, CcnxNetDeviceFace, CcnxUdpFace) \returns the
   * index of the Ccnx interface added.
   * 
   * \see CcnxLocalFace, CcnxNetDeviceFace, CcnxUdpFace
   */
  virtual uint32_t
  AddFace (const Ptr<CcnxFace> &face) = 0;

  /**
   * \brief Get current number of faces added to CCNx stack
   *
   * \returns the number of faces
   */
  virtual uint32_t
  GetNFaces (void) const = 0;

  /**
   * \param face The face number of an Ccnx interface.
   * \returns The CcnxFace associated with the Ccnx face number.
   */
  virtual Ptr<CcnxFace>
  GetFace (uint32_t face) const = 0;
};

} // namespace ns3 

#endif /* _CCNX_H_ */