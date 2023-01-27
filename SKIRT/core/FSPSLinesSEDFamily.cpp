/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "FSPSLinesSEDFamily.hpp"
#include "Constants.hpp"

////////////////////////////////////////////////////////////////////


FSPSLinesSEDFamily::FSPSLinesSEDFamily(SimulationItem* parent)
{
    parent->addChild(this);
    setup();
}

////////////////////////////////////////////////////////////////////

void FSPSLinesSEDFamily::setupSelfBefore()
{
    SEDFamily::setupSelfBefore();

    string name = "FSPSLinesSEDFamily_";
    _table4.open(this, name, "lambda(m),Z(1),t(yr),U(1)", "Llambda(W/m)", false);
}

////////////////////////////////////////////////////////////////////

vector<SnapshotParameter> FSPSLinesSEDFamily::parameterInfo() const
{
    return {
        SnapshotParameter::initialMass(),
        SnapshotParameter::metallicity(),
        SnapshotParameter::age(),
        SnapshotParameter::custom("ionization parameter")
        };
}

////////////////////////////////////////////////////////////////////

Range FSPSLinesSEDFamily::intrinsicWavelengthRange() const
{
    return _table4.axisRange<0>();
}

////////////////////////////////////////////////////////////////////

double FSPSLinesSEDFamily::specificLuminosity(double wavelength, const Array& parameters) const
{
    double M = parameters[0] / Constants::Msun();
    double Z = parameters[1];
    double t = parameters[2] / Constants::year();
    double U = parameters[3];

    return M * _table4(wavelength, Z, t, U);
}

////////////////////////////////////////////////////////////////////

double FSPSLinesSEDFamily::cdf(Array& lambdav, Array& pv, Array& Pv, const Range& wavelengthRange,
                          const Array& parameters) const
{
    double M = parameters[0] / Constants::Msun();
    double Z = parameters[1];
    double t = parameters[2] / Constants::year();
    double U = parameters[3];

    return M * _table4.cdf(lambdav, pv, Pv, wavelengthRange, Z, t, U);
}

////////////////////////////////////////////////////////////////////
