#include "decaydescriptor.h"

using namespace ABSIM;

void SubDecayDescriptor::addParticle(std::string name, int_t index)
{
  particles_.push_back( name );
  indices_.push_back( index );
}

void SubDecayDescriptor::addDecay(int_t index, SubDecayDescriptor* decay)
{
  decays_.insert( std::pair<int_t,SubDecayDescriptor*>( index , decay ) );
}

void DecayDescriptor::getParticleInfo(std::string name, bool decay_particle)
{
  BasicParticleInfo info = ParticleStore::getParticle( name );
  if ( decay_particle ) {
    info.stable = false;
    info.decay_index = currentDecayIndex();
  } else {
    info.stable = true;
    info.decay_index = 0;
  }
  particle_info_.push_back( info  );
  return;
}

bool DecayDescriptor::beginDecay(std::string entry)
{
  if ( ( entry == "(" ) || ( entry == "{" ) || ( entry == "[" )  ) return true;
  return false;
}

bool DecayDescriptor::endDecay(std::string entry)
{
  if ( ( entry == ")" ) || ( entry == "}" ) || ( entry == "]" )  ) return true;
  return false;
}

bool DecayDescriptor::isDecaySign(std::string entry)
{
  if ( ( entry == "=>") || ( entry == "->" ) ) return true;
  return false;
}

void DecayDescriptor::decodeDecay(std::string decay)
{
  SubDecayDescriptor* subdecay = nullptr;
  bool decay_particle = true;
  std::istringstream ss(decay);
  std::string entry;
  while ( ss >> entry ) {
    if ( beginDecay(entry) ) {
      subdecays_.push_back( new SubDecayDescriptor() );
      SubDecayDescriptor* from = subdecay;
      subdecay = subdecays_.back();
      // Set the decay origin to previous subdecay.
      subdecay->from_ = from;
      decay_particle = true;
      continue;
    }

    if ( endDecay(entry) ) {
      // Move back a decay.
      subdecay = subdecay->from_;
      continue;
    }

    if ( isDecaySign(entry) ) continue;

    // Add particle.
    particles_.push_back( entry );
    getParticleInfo( entry , decay_particle );

    // First particle must be head.
    if ( head_ == "" ) {
      head_ = entry;

      // Add sub-decay.
      subdecays_.push_back( new SubDecayDescriptor() );
      subdecay = subdecays_.back();
      subdecay->from_ = nullptr;
      subdecay->addParticle( entry , currentIndex() );

      decay_particle = false;
      continue;
    }

    if ( decay_particle == true ) {
      subdecay->from_->addParticle( entry , currentIndex() );
      subdecay->from_->addDecay( currentIndex() , subdecay );
      subdecay->addParticle( entry , currentIndex() );
      decay_particle = false;
      continue;
    }

    subdecay->addParticle( entry , currentIndex() );
    subdecay->addDecay( currentIndex() , nullptr );
  }
  
  for (int_t i = 0; i < subdecays_.size(); i++) {
    DecayInfo info;
    info.ndaughters = subdecays_[i]->particles_.size() - 1;
    info.mother = subdecays_[i]->indices_[0];
    for (int_t j = 1; j < subdecays_[i]->particles_.size(); j++) {
      info.daughters.push_back( subdecays_[i]->indices_[j] );
    }
    decay_info_.push_back( std::move( info ) );
  }
  return;
}

std::string DecayDescriptor::print_t_subdecay(std::string& out, SubDecayDescriptor* subdecay) const
{
  out += "{ " + subdecay->particles_.front() + " => ";
  for (int_t i = 1; i < subdecay->particles_.size(); ++i) {
    int_t index = subdecay->indices_[i];
    if ( subdecay->decays_[index] != nullptr ) {
      print_t_subdecay(out, subdecay->decays_[index]);
    } else {
      out += subdecay->particles_[i] + " ";
    }
  }
  out += "} ";
  return out;
}

std::string DecayDescriptor::decay_string() const
{
  std::string out = "";
  SubDecayDescriptor* subdecay = subdecays_.front();
  out += subdecay->particles_.front() + " => ";
  for (int_t i = 1; i < subdecay->particles_.size(); ++i) {
    int_t index = subdecay->indices_[i];
    if ( subdecay->decays_[index] != nullptr ) {
      print_t_subdecay(out, subdecay->decays_[index]);
    } else {
      out += subdecay->particles_[i] + " ";
    }
  }
  return out;
}

void DecayDescriptor::Print_t() const
{
  std::cout << decay_string() << std::endl;
}