#ifndef ABSIM_ENTRYBASE_H
#define ABSIM_ENTRYBASE_H

#include "event.h"

#include <string>
#include <memory>

namespace ABSIM {
  
  struct EntryBase
  {
    EntryBase(std::string name, std::string title) :
      next( nullptr ),
      name_( name ),
      title_( title )
    {}
    virtual ~EntryBase() {}

    std::unique_ptr<EntryBase> next;

    const std::string name_;
    const std::string title_;
    const char* name()  const { return name_.c_str(); }
    const char* title() const { return title_.c_str(); }

    virtual void operator()(Event& ev) = 0;

    virtual std::unique_ptr<EntryBase> clone() const = 0;
  };


  template <typename T>
  inline std::string suffix() { return "i"; }

  template <>
  inline std::string suffix<int>() { return "I"; }

  template <>
  inline std::string suffix<float>() { return "F"; }

  template <>
  inline std::string suffix<double>() { return "D"; }

}  // namespace ABSIM

#endif