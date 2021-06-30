#ifndef ABSIM_ENTRYBASE_H
#define ABSIM_ENTRYBASE_H

#include "event.h"

#include <string>
#include <memory>

namespace ABSIM {

  /**
   * @class EntryBase
   * 
   * @brief Abstract base class for an entry.
   * 
   * @details
   * 
   * @author Edward Shields
   * @data 20/06/2021 
   */
  class EntryBase
  {
  private:
    const std::string name_;    ///< Name of branch.
    const std::string title_;   ///< Title of branch.
  public:
    /**
     * Constructor
     * 
     * @param name Name of branch.
     * @param title Title of branch.
     */
    EntryBase(const std::string name, const std::string title) :
      name_( name ),
      title_( title)
    {}

    std::unique_ptr<EntryBase> next; ///< Next entry in LinkedList.

    /** 
     * Name of branch.
     */
    const std::string name()  const { return name_; }
    /**
     * Title of branch.
     */
    const std::string title() const { return title_; }

    /**
     * Virtual function in which a value is assigned to the address of the branch.
     * The value of this address is the looked at when the TTree is filled.
     * 
     * @param ev Event
     */
    virtual void operator()(Event& ev) = 0;
  };

}  // namespace ABSIM

#endif