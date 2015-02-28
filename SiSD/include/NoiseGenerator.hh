/*
  \file     NoiseGenerator.hh
  \brief    Generate noise to add to signal
*/
#ifndef NOISEGENERATOR_HH_
#define NOISEGENERATOR_HH_


#include "G4Types.hh"
#include "Randomize.hh"

/*!
* \class NoiseGenerator
* \brief Generate noise to add to signal by specifying pedestal and sigma
*/
class NoiseGenerator
{
  public:
    /*!
    * \brief Constructor
    * \param ppedestal : value of the pedestal
    * \param psigma : value of sigma
    */
    NoiseGenerator(const G4double& ppedestal, const G4double& psigma);
    /*!
    * \brief Destructor
    */
    virtual ~NoiseGenerator() {};
    /*!
    * \brief Copy Constuctor
    */
    NoiseGenerator(const NoiseGenerator& rhs);
    /*!
    * \brief Operator ()
    */
    virtual G4double operator() ();
    /*!
    * \brief Operator =
    */
    inline NoiseGenerator& operator= (const NoiseGenerator& rhs)
    {
          pedestal = rhs.pedestal;
          sigma = rhs.sigma;
          return *this;
    }
    /*!
    * \brief Get pedestal
    * \return Pedestal value
    */
    G4double GetPedestal() {return pedestal;}
    /*!
    * \brief Get sigma
    * \return Sigma value
    */
    G4double GetSigma() {return sigma;}

  private:
    G4double pedestal;
    G4double sigma;
    G4RandGauss randomGauss;
};

#endif
