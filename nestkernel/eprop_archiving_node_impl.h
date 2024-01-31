/*
 *  eprop_archiving_node_impl.h
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef EPROP_ARCHIVING_NODE_IMPL_H
#define EPROP_ARCHIVING_NODE_IMPL_H

#include "eprop_archiving_node.h"

// Includes from nestkernel:
#include "kernel_manager.h"

// Includes from sli:
#include "dictutils.h"

namespace nest
{

template < typename HistEntryT >
EpropArchivingNode< HistEntryT >::EpropArchivingNode()
  : Node()
  , eprop_indegree_( 0 )
{
}

template < typename HistEntryT >
EpropArchivingNode< HistEntryT >::EpropArchivingNode( const EpropArchivingNode& n )
  : Node( n )
  , eprop_indegree_( n.eprop_indegree_ )
{
}

template < typename HistEntryT >
long
EpropArchivingNode< HistEntryT >::get_shift() const
{
  return offset_gen_ + delay_in_rec_;
}

template < typename HistEntryT >
void
EpropArchivingNode< HistEntryT >::register_eprop_connection()
{
  ++eprop_indegree_;

  const long shift = get_shift();

  const auto it_hist = get_update_history( shift );

  if ( it_hist == update_history_.end() or it_hist->t_ != shift )
  {
    update_history_.insert( it_hist, HistEntryEpropUpdate( shift, 1 ) );
  }
  else
  {
    ++it_hist->access_counter_;
  }
}

template < typename HistEntryT >
void
EpropArchivingNode< HistEntryT >::write_update_to_history( const long t_previous_update,
  const long t_current_update,
  const long eprop_isi_trace_cutoff,
  const bool erase )
{
  if ( eprop_indegree_ == 0 )
  {
    return;
  }

  const long shift = get_shift();

  const auto it_hist_curr = get_update_history( t_current_update + shift );

  if ( it_hist_curr != update_history_.end() and it_hist_curr->t_ == t_current_update + shift )
  {
    ++it_hist_curr->access_counter_;
  }
  else
  {
    update_history_.insert( it_hist_curr, HistEntryEpropUpdate( t_current_update + shift, 1 ) );
    if ( erase )
    {
      erase_unneeded_eprop_history( eprop_isi_trace_cutoff );
    }
  }

  const auto it_hist_prev = get_update_history( t_previous_update + shift );

  if ( it_hist_prev != update_history_.end() and it_hist_prev->t_ == t_previous_update + shift )
  {
    // If an entry exists for the previous update time, decrement its access counter
    --it_hist_prev->access_counter_;
  }

  if ( erase )
  {
    erase_unneeded_update_history();
  }
}

template < typename HistEntryT >
std::vector< HistEntryEpropUpdate >::iterator
EpropArchivingNode< HistEntryT >::get_update_history( const long time_step )
{
  return std::lower_bound( update_history_.begin(), update_history_.end(), time_step );
}

template < typename HistEntryT >
typename std::vector< HistEntryT >::iterator
EpropArchivingNode< HistEntryT >::get_eprop_history( const long time_step )
{
  return std::lower_bound( eprop_history_.begin(), eprop_history_.end(), time_step );
}

template < typename HistEntryT >
void
EpropArchivingNode< HistEntryT >::erase_used_eprop_history( const long eprop_isi_trace_cutoff )
{
  if ( eprop_history_.empty()  // nothing to remove
    or update_history_.empty() // no time markers to check
  )
  {
    return;
  }

  const long t_prev = ( update_history_.end() - 2 )->t_;
  const long t_curr = ( update_history_.end() - 1 )->t_;

  const auto it_eprop_hist_erase_from = get_eprop_history( t_prev + eprop_isi_trace_cutoff );
  const auto it_eprop_hist_erase_to = get_eprop_history( t_curr );
  eprop_history_.erase( it_eprop_hist_erase_from, it_eprop_hist_erase_to ); // erase found entries since no longer used

  const auto it_eprop_hist_from = get_eprop_history( 0 );
  const auto it_eprop_hist_to = get_eprop_history( update_history_.begin()->t_ - 1 );

  eprop_history_.erase( it_eprop_hist_from, it_eprop_hist_to ); // erase found entries since no longer used
}

template < typename HistEntryT >
void
EpropArchivingNode< HistEntryT >::erase_used_update_history()
{
  auto it_hist = update_history_.begin();
  while ( it_hist != update_history_.end() )
  {
    if ( it_hist->access_counter_ == 0 )
    {
      // erase() invalidates the iterator, but returns a new, valid iterator
      it_hist = update_history_.erase( it_hist );
    }
    else
    {
      ++it_hist;
    }
  }
}

} // namespace nest

#endif // EPROP_ARCHIVING_NODE_IMPL_H