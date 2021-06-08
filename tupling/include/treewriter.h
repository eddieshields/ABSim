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

    void addParticleEntry(std::string name, std::string variable, unsigned int i);

    template <typename Fn>
    void addEntry(std::string name)
    {
      ParticleEntry<Fn,real_t>* entry =  new ParticleEntry<Fn,real_t>(name,0);
      tree_->Branch(entry->name(),&entry->value_,entry->title());
      entries_.add( entry );
    }

    template <typename ENTRY>
    void addEntry(ENTRY* entry)
    {
      tree_->Branch(entry->name(),&entry->value_,entry->title());
      entries_.add( entry );
    }

    void fill(Event& ev)
    {
      EntryBase* entry = entries_.head().get();
      while ( entry ) {
        entry->operator()(ev);
        entry = entry->next.get();
      }
      tree_->Fill();
    }

    TTree* tree() { return tree_; }

  };

} // namespace ABSIM

#endif