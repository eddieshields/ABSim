#include "particlestore.h"

using namespace ABSIM;

TDatabasePDG ParticleStore::pdg_;

std::map<std::string,BasicParticleInfo> ParticleStore::particles_ = std::map<std::string,BasicParticleInfo>();
