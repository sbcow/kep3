// Copyright 2023, 2024 Dario Izzo (dario.izzo@gmail.com), Francesco Biscani
// (bluescarni@gmail.com)
//
// This file is part of the kep3 library.
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef kep3_LAMBERT_PROBLEM_H
#define kep3_LAMBERT_PROBLEM_H

#include <array>
#include <cmath>
#include <vector>

#include <kep3/core_astro/constants.hpp>
#include <kep3/detail/s11n.hpp>
#include <kep3/detail/visibility.hpp>

namespace kep3
{

/// Lambert Problem
/**
 * This class represent a Lambert's problem. When instantiated it assumes a
 * prograde orbit (unless otherwise stated) and evaluates all the solutions up
 * to a maximum number of multiple revolutions. After the object is instantiated
 * the solutions can be retreived using the appropriate getters. Note that the
 * number of solutions will be N_max*2 + 1, where N_max is the maximum number of
 * revolutions.
 *
 * NOTE: The class has been tested extensively via monte carlo runs checked with
 * numerical propagation. Compared to the previous Lambert Solver in the
 * keplerian_toolbox it is 1.7 times faster (on average as defined by
 * lambert_test.cpp). With respect to Gooding algorithm it is 1.3 - 1.5 times
 * faster (zero revs - multi revs). The algorithm is described in detail in:
 *
 * Izzo, Dario. "Revisiting Lambert’s problem." Celestial Mechanics and
 * Dynamical Astronomy 121 (2015): 1-15.
 *
 * @author Dario Izzo (dario.izzo _AT_ googlemail.com)
 */

class kep3_DLL_PUBLIC lambert_problem;

// Streaming operator for the class kep_toolbox::lambert_problem.
kep3_DLL_PUBLIC std::ostream &operator<<(std::ostream &, const lambert_problem &);

class kep3_DLL_PUBLIC lambert_problem
{
    static const std::array<double, 3> default_rs;
    static const std::array<double, 3> default_rf;

public:
    friend kep3_DLL_PUBLIC std::ostream &operator<<(std::ostream &, const lambert_problem &);
    explicit lambert_problem(const std::array<double, 3> &rs = default_rs, const std::array<double, 3> &rf = default_rf,
                             double tof = kep3::pi / 2, double mu = 1., bool cw = false, unsigned multi_revs = 1);
    [[nodiscard]] const std::vector<std::array<double, 3>> &get_vs() const;
    [[nodiscard]] const std::vector<std::array<double, 3>> &get_vf() const;
    [[nodiscard]] const std::array<double, 3> &get_rs() const;
    [[nodiscard]] const std::array<double, 3> &get_rf() const;
    [[nodiscard]] const double &get_tof() const;
    [[nodiscard]] const double &get_mu() const;
    [[nodiscard]] const std::vector<double> &get_x() const;
    [[nodiscard]] const std::vector<unsigned> &get_iters() const;
    [[nodiscard]] unsigned get_Nmax() const;

private:
    unsigned householder(double, double &, unsigned, double, unsigned) const;
    void dTdx(double &, double &, double &, double, double) const;
    void x2tof(double &tof, double x0, unsigned N) const;
    void x2tof2(double &tof, double x0, unsigned N) const;
    [[nodiscard]] static double hypergeometricF(double z, double tol);
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int)
    {
        ar & m_rs;
        ar & m_rf;
        ar & m_tof;
        ar & m_mu;
        ar & m_vs;
        ar & m_vf;
        ar & m_iters;
        ar & m_x;
        ar & m_s;
        ar & m_c;
        ar & m_lambda;
        ar & m_iters;
        ar & m_Nmax;
        ar & m_has_converged;
        ar & m_multi_revs;
    }

    std::array<double, 3> m_rs, m_rf;
    double m_tof;
    double m_mu;
    std::vector<std::array<double, 3>> m_vs;
    std::vector<std::array<double, 3>> m_vf;
    std::vector<unsigned> m_iters;
    std::vector<double> m_x;
    double m_s, m_c, m_lambda;
    unsigned m_Nmax;
    bool m_has_converged;
    unsigned m_multi_revs;
};

// Streaming operator for the class kep3::lambert_problem.
kep3_DLL_PUBLIC std::ostream &operator<<(std::ostream &, const lambert_problem &);

} // namespace kep3

#endif // kep3_LAMBERT_PROBLEM_H