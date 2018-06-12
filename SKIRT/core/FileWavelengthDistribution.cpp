/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "FileWavelengthDistribution.hpp"
#include "FatalError.hpp"
#include "NR.hpp"
#include "Random.hpp"
#include "Range.hpp"
#include "TextInFile.hpp"
#include "WavelengthRangeInterface.hpp"

//////////////////////////////////////////////////////////////////////

void FileWavelengthDistribution::setupSelfBefore()
{
    WavelengthDistribution::setupSelfBefore();

    // read the wavelengths and probabilities from the input file
    TextInFile infile(this, _filename, "wavelength probability distribution");
    infile.addColumn("wavelength", "wavelength", "micron");
    infile.addColumn("probability density", "specific", "W/m");
    Array inlambdav, inpv;
    infile.readAllColumns(inlambdav, inpv);
    infile.close();

    // determine the intersected wavelength range
    Range range(inlambdav[0], inlambdav[inlambdav.size()-1]);
    range.intersect(interface<WavelengthRangeInterface>()->wavelengthRange());
    if (range.empty()) throw FATALERROR("Wavelength distribution range does not overlap source wavelength range");

    // construct the regular and cumulative distributions in the intersected range
    NR::cdfLogLog(_lambdav, _pv, _Pv, inlambdav, inpv, range);
}

//////////////////////////////////////////////////////////////////////

double FileWavelengthDistribution::probability(double wavelength) const
{
    int i = NR::locateFail(_lambdav, wavelength);
    if (i < 0) return 0.;
    return NR::interpolateLogLog(wavelength, _lambdav[i], _lambdav[i+1], _pv[i], _pv[i+1]);
}

//////////////////////////////////////////////////////////////////////

double FileWavelengthDistribution::generateWavelength() const
{
    return random()->cdfLogLog(_lambdav, _pv, _Pv);
}

//////////////////////////////////////////////////////////////////////