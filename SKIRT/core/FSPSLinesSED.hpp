/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef FSPSLINESSED_HPP
#define FSPSLINESSED_HPP

#include "FamilySED.hpp"

////////////////////////////////////////////////////////////////////

/** FSPSLinesSED is a class that represents spectral energy distributions of simple stellar populations
    (SSPs) with the addition of nebular continuum and emission lines, parameterized on metallicity, age
    and ionization parameter, generated by the FSPS code (Conroy, Gunn, & White 2009, Conroy & Gunn 2010,
    Byler et al. 2017), assuming a Kroupa initial mass function.
    */
class FSPSLinesSED : public FamilySED
{

    ITEM_CONCRETE(FSPSLinesSED, FamilySED, "an FSPS simple stellar population with nebular emission SED")

        //PROPERTY_ENUM(imf, IMF, "the assumed initial mass function")
        ATTRIBUTE_DEFAULT_VALUE(imf, "Kroupa")

        PROPERTY_DOUBLE(metallicity, "the metallicity of the SSP")
        ATTRIBUTE_MIN_VALUE(metallicity, "[0.0001")
        ATTRIBUTE_MAX_VALUE(metallicity, "0.05]")
        ATTRIBUTE_DEFAULT_VALUE(metallicity, "0.0142")

        PROPERTY_DOUBLE(age, "the age of the SSP")
        ATTRIBUTE_QUANTITY(age, "time")
        ATTRIBUTE_MIN_VALUE(age, "[0.0001 Gyr")
        ATTRIBUTE_MAX_VALUE(age, "20 Gyr]")
        ATTRIBUTE_DEFAULT_VALUE(age,"5 Gyr")

        PROPERTY_DOUBLE(U, "the ionisation parameter of the SSP")
        ATTRIBUTE_MIN_VALUE(U, "[0.0001")
        ATTRIBUTE_MAX_VALUE(U, "0.1]")
        ATTRIBUTE_DEFAULT_VALUE(U, "0.01")

    ITEM_END()

    //============= Construction - Setup - Destruction =============

protected:
    /** This function returns a newly created SEDFamily object (which is already hooked into the
        simulation item hierachy so it will be automatically deleted) and stores the parameters for
        the specific %SED configured by the user in the specified array. */
    const SEDFamily* getFamilyAndParameters(Array& parameters) override;
};

////////////////////////////////////////////////////////////////////

#endif
