#ifndef ABSIM_ENTRY_H
#define ABSIM_ENTRY_H

#include "entrybase.h"

namespace ABSIM {

  /**
   * @class Entry
   * 
   * @brief 
   * 
   * @details
   * 
   * @author Edward Shields
   * @date 30/06/2021
   */
  template <typename T>
  class Entry : public EntryBase
  {
  public:
    T value; ///< Value, where the address of this will be used to fill the TTree.

    /**
     * Constructor
     * 
     * @param name of entry.
     */
    Entry(std::string name) :
      EntryBase(name,name+suffix<T>())
    {}
    ~Entry() {}

  };

  /**
   * Returns suffix for branch title for a given type.
   */
  template <typename T>
  std::string suffix();

}  // namespace ABSIM

#endif