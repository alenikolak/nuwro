#ifndef _RES_KINEMATICS_H
#define _RES_KINEMATICS_H

#include "event1.h"

//! store kinematics used by RES
struct res_kinematics {
  static const double Wmin;              //!< invariant mass threshold
  static const double avg_nucleon_mass;  //!< average nucleon mass
  static const double pythia_threshold;  //!< do not use PYTHIA below this W

  res_kinematics(const event& e);  //!< initialize basic kinmatics

  bool generate_kinematics(const double& res_dis_cut);  //!< set the rest of kinematics

  //! check it neutrino energy is above thresholds
  inline bool is_above_threshold() {
    return neutrino.E() > ((Wmin + lepton_mass) * (Wmin + lepton_mass) - effective_mass2) / 2.0 / effective_mass;
  }

  //! check if W is above PYTHIA threshold
  inline bool is_above_pythia_threshold() {
    // PYTHIA does not work in this region and special treatment is required
    return W > pythia_threshold;
  }

  particle neutrino;  //!< initial neutrino
  particle target;    //!< target nucleon
  particle lepton;    //!< outgoing lepton (note: not in LAB frame)

  double lepton_mass;   //!< outgoing lepton mass
  double lepton_mass2;  //!< outgoing lepton mass squared

  double effective_mass;   //!< effective mass of a nucleon
  double effective_mass2;  //!< effective mass squared

  double W;   //!< invariant mass
  double W2;  //!< invariant mass squared

  vect q;  //!< four-momentum transfer

  vec hadron_speed;  //!< the speed of hadronic system

  double jacobian;  //!< integration over z
};

//! get the value of binding energy according to setting from params
double get_binding_energy(const params& p, const vec& momentum);

#endif