#ifndef DE__OSM3S___OVERPASS_API__OSM_BACKEND__NODE_SKELETON_UPDATER_H
#define DE__OSM3S___OVERPASS_API__OSM_BACKEND__NODE_SKELETON_UPDATER_H


#include "new_basic_updater.h"

#include <vector>


namespace Node_Skeleton_Updater
{
  // Adds to the result all coordinates from nodes whose ids appear in pre_event_refs
  /* Precondition:
   * pre_event_refs contains each id at most once.
   */
  void collect_relevant_coords_current(
      const Node_Pre_Event_Refs& pre_event_refs,
      const std::vector< Node_Skeleton >& current,
      Coord_Dates& result);
  /* Assertions:
   * For each coord there is at most one object r with r.coord == coord in the result.
   * An object r is contained in the result if and only if
   * there is an object s in the result before the function call with r.ccord == s.coord
   * or there is a pair (e, n) from pre_event_refs and current with e.id == n.id and n.coord == r.coord.
   * It is r.date == min\{s.date|s in result beforehand and s.coord == r.coord\}\cup\{e.date|(e, n) from (pre_event_refs, current) with e.id == n.id and n.coord == r.coord\}
   */
}


namespace Node_Skeleton_Updater
{
  // Adds to the result all coordinates from nodes whose ids appear in pre_event_refs
  /* Precondition:
   * pre_event_refs contains each id at most once.
   */
  void collect_relevant_coords_attic(
      const Node_Pre_Event_Refs& pre_event_refs,
      const std::vector< Attic< Node_Skeleton > >& attic,
      Coord_Dates& result);
  /* Assertions:
   * For each coord there is at most one object r with r.coord == coord in the result.
   * An object r is contained in the result if and only if
   * there is an object s in the result before the function call with r.ccord == s.coord
   * or there is a pair (e, n) from pre_event_refs and attic with e.id == n.id, e.date < n.end and n.coord == r.coord.
   * It is r.date == min\{s.date|s in result beforehand and s.coord == r.coord\}\cup\{e.date|(e, n) from (pre_event_refs, attic) with e.id == n.id and n.coord == r.coord\}
   *
   * NB: Could be optimized away if we know beforehand
   * that no current_meta in this idx is younger than the oldest date from pre_event_refs.
   */
}


namespace Node_Skeleton_Updater
{
  // Keeps from all the objects in the idx only those that are relevant for the event list
  /* Precondition:
   * pre_event_refs contains each id at most once.
   * coord_dates_per_idx contains each id at most once.
   */
  std::vector< Node_Skeleton > extract_relevant_current(
      const Node_Pre_Event_Refs& pre_event_refs,
      Id_Dates& coord_sharing_ids,
      const Coord_Dates& coord_dates_per_idx,
      const std::vector< Node_Skeleton >& current);
  /* Assertions:
  * An object r is in the result if and only if it is in attic and
  * - its id is in pre_event_refs  or
  * - its coordinate is in coord_dates_per_idx
  * NB: an extra condition could be applied to avoid too old objects,
  * but is avoided at the moment for the sake of simplicity.
  *
  * An object r is in coord_sharing_ids if r.id is not in pre_event_refs
  * but the coord of the object e with e.id == r.id is in coord_dates_per_idx.
  */
}


namespace Node_Skeleton_Updater
{
  // Keeps from all the objects in the idx only those that are relevant for the event list
  /* Precondition:
   * pre_event_refs contains each id at most once.
   * coord_dates_per_idx contains each id at most once.
   */
  std::vector< Attic< Node_Skeleton > > extract_relevant_attic(
      const Node_Pre_Event_Refs& pre_event_refs,
      Id_Dates& coord_sharing_ids,
      const Coord_Dates& coord_dates_per_idx,
      const std::vector< Attic< Node_Skeleton > >& attic);
  /* Assertions:
  * An object r is in the result if and only if it is in attic and
  * - its id is in pre_event_refs  or
  * - its coordinate is in coord_dates_per_idx
  * NB: an extra condition could be applied to avoid too old objects,
  * but is avoided at the moment for the sake of simplicity.
  *
  * An object r is in coord_sharing_ids if r.id is not in pre_event_refs
  * but the coord of the object e with e.id == r.id is in coord_dates_per_idx.
  */
}


#endif