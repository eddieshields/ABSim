#include "decaydescriptor.h"

using namespace ABSIM;

void DecayDescriptor::getInfo(std::string name)
{
  BasicParticleInfo info = ParticleStore::getParticle( name );
  infos_.insert( std::pair<std::string,BasicParticleInfo>( name , info ) );
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

int DecayDescriptor::find(std::string entry)
{
  auto it = std::find(particles_.begin(),particles_.end(),entry);
  return it - particles_.begin();
}

void DecayDescriptor::decodeDecay(std::string decay)
{
  SubDecayDescriptor* subdecay = nullptr;
  bool decay_particle = true;
  std::istringstream ss(decay);
  std::string entry;
  while ( ss >> entry ) {
    // First particle must be head.
    if ( head_ == "" ) {
      head_ = entry;
      subdecays_.push_back( new SubDecayDescriptor() );
      subdecay = subdecays_.back();
      subdecay->from_ = nullptr;
      subdecay->particles_.push_back( entry );
      subdecay->index( entry ) = find( entry );
      getInfo( entry );
      decay_particle = false;
      continue;
    }

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

    particles_.push_back( entry );
    getInfo( entry );

    if ( decay_particle == true ) {
      subdecay->from_->particles_.push_back( entry );
      subdecay->particles_.push_back( entry );
      subdecay->from_->decays_.insert( std::pair<std::string,SubDecayDescriptor*>(particles_.back(),subdecay));
      decay_particle = false;
      continue;
    }

    subdecay->particles_.push_back( entry );
    subdecay->index( entry ) = find( entry );
    subdecay->decays_.insert( std::pair<std::string,SubDecayDescriptor*>(particles_.back() , nullptr) );
  }
  return;
}

std::string DecayDescriptor::print_subdecay(std::string& out, SubDecayDescriptor* subdecay) const
{
  out += "{ " + subdecay->particles_.front() + " => ";
  for (unsigned int i = 1; i < subdecay->particles_.size(); ++i) {
    std::string part = subdecay->particles_[i];
    if ( subdecay->decays_[part] != nullptr ) {
      print_subdecay(out, subdecay->decays_[part]);
    } else {
      out += part + " ";
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
  for (unsigned int i = 1; i < subdecay->particles_.size(); ++i) {
    std::string part = subdecay->particles_[i];
    if ( subdecay->decays_[part] != nullptr ) {
      print_subdecay(out, subdecay->decays_[part]);
    } else {
      out += part + " ";
    }
  }
  return out;
}

void DecayDescriptor::Print() const
{
  std::cout << decay_string() << std::endl;
}