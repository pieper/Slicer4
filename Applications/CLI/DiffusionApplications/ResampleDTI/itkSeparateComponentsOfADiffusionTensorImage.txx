/*=========================================================================

  Program:   Diffusion Applications
  Module:    $HeadURL: http://svn.slicer.org/Slicer4/trunk/Applications/CLI/DiffusionApplications/ResampleDTI/itkDiffusionTensor3DResample.txx $
  Language:  C++
  Date:      $Date: 2010/04/05 10:04:59 $
  Version:   $Revision: 1.1 $

  Copyright (c) Brigham and Women's Hospital (BWH) All Rights Reserved.

  See License.txt or http://www.slicer.org/copyright/copyright.txt for details.

==========================================================================*/
#ifndef __itkSeparateComponentsOfADiffusionTensorImage_txx
#define __itkSeparateComponentsOfADiffusionTensorImage_txx

#include "itkSeparateComponentsOfADiffusionTensorImage.h"

namespace itk
{

template< class TInput , class TOutput >
SeparateComponentsOfADiffusionTensorImage< TInput,TOutput >
::SeparateComponentsOfADiffusionTensorImage()
{
  this->SetNumberOfRequiredInputs( 1 ) ;
  this->SetNumberOfOutputs( 6 ) ;
  this->SetNumberOfRequiredOutputs( 6 ) ;
  for( unsigned int i = 1 ; i < this->GetNumberOfOutputs() ; i++ )//we skip output0 because it is created by default
  {
    OutputImagePointerType output
      = static_cast< OutputImageType* >( this->MakeOutput( i ).GetPointer() ) ; 
    this->ProcessObject::SetNthOutput( i , output.GetPointer() ) ;
  }
}





template< class TInput , class TOutput >
void
SeparateComponentsOfADiffusionTensorImage< TInput , TOutput >
::ThreadedGenerateData( const OutputImageRegionType &outputRegionForThread ,
                                                     int itkNotUsed(threadId) )
{
  InputIteratorType it( this->GetInput() , outputRegionForThread ) ;
  std::vector< OutputIteratorType > out ;
  for( int i = 0 ; i < 6 ; i++ )
  {
    OutputImagePointerType outputImagePtr = this->GetOutput( i ) ;
    OutputIteratorType outtemp( outputImagePtr , outputRegionForThread ) ;
    outtemp.GoToBegin() ;
    out.push_back( outtemp ) ;
  }
  InputTensorDataType inputTensor ;
  for( it.GoToBegin() ; !it.IsAtEnd() ; ++it )
  {
    inputTensor = it.Get() ;
    for( int i = 0 ; i < 6 ; i++ )
    {
      out[ i ].Set( static_cast< OutputDataType >( inputTensor[ i ] ) ) ;
      ++out[ i ] ;
    }
  }
} 



/** 
 * Inform pipeline of required output region
 */
template< class TInput , class TOutput >
void 
SeparateComponentsOfADiffusionTensorImage< TInput , TOutput >
::GenerateOutputInformation()
{
  // call the superclass' implementation of this method
  Superclass::GenerateOutputInformation();
  // get pointers to the input and output
  for( int i = 0 ; i < 6 ; i++ )
  {
    OutputImagePointerType outputPtr = this->GetOutput( i ) ;
    if( !outputPtr )
    {
      return ;
    }
    outputPtr->CopyInformation( this->GetInput() ) ;
  }
  return ;
}



/** 
 * Inform pipeline of necessary input image region
 *
 * Determining the actual input region is non-trivial, especially
 * when we cannot assume anything about the transform being used.
 * So we do the easy thing and request the entire input image.
 */
template< class TInput , class TOutput >
void 
SeparateComponentsOfADiffusionTensorImage< TInput , TOutput >
::GenerateInputRequestedRegion()
{
  // call the superclass's implementation of this method
  Superclass::GenerateInputRequestedRegion() ;

  if( !this->GetInput() )
    {
    return ;
    }
  // get pointers to the input and output
  InputImagePointerType  inputPtr  = 
      const_cast< InputImageType* >( this->GetInput() ) ;

  // Request the entire input image
  typename InputImageType::RegionType inputRegion ;
  inputRegion = inputPtr->GetLargestPossibleRegion() ;
  inputPtr->SetRequestedRegion( inputRegion ) ;
  return ;
}


}//end namespace itk
#endif
