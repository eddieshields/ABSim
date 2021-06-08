#ifndef ABSIM_CONFIGSERVICE_H
#define ABSIM_CONFIGSERVICE_H

namespace ABSIM {

  class ABSim;

  class ConfigSvc
  {
  private:
    const ABSim* target_;

  public:
    ConfigSvc(const ABSim* target) :
      target_( target )
    {}
    ~ConfigSvc() {}

    template<typename Arg, typename... Args>
    void addAlgorithms(const Arg& alg, Args... algs);

    template<typename Arg>
    void addAlgorithms(const Arg& alg);
  };

}  // namespace ABSIM

#endif