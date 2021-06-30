#ifndef ABSIM_TREEWRITER_H
#define ABSIM_TREEWRITER_H

#include "event.h"

#include "entry.h"
#include "particlentry.h"
#include "linkedlist.h"
#include "functors.h"
#include "properties.h"

#include "TTree.h"

#include <string>
#include <memory>

namespace ABSIM {

  class TreeWriter
  {
  private:
    LinkedList<EntryBase> entries_;
    TTree* tree_;

  public:
    TreeWriter(std::string name, std::string title)
    {
      tree_ = new TTree(name.c_str(),title.c_str());
    }

    template <typename Fn>
    void addEntry(const Fn& fn, const std::string name);

    void fill();
    
  };


} // namespace ABSIM

#endif