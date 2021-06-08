#include "treewriter.h"

using namespace ABSIM;

void TreeWriter::addParticleEntry(std::string name, std::string variable, unsigned int i)
{
  std::string entry_name = "_" + name + "_" + variable + "_";
  addEntry<M2>(name);
}