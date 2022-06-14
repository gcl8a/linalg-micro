#pragma once

#include <matrix_uC.h>

class SampleMatrix : public TMatrix<double>
/*SampleMatrix assumes that the samples vectors are in the columns. i.e., there
  are <rows> number of samples
*/
{
 protected:
  TVector<double> mean;
  TMatrix<double> covariance;

 public:
  SampleMatrix( void ) : TMatrix<double>(TMatrix<double>::Eye(4)) { }

  SampleMatrix( int vec_len, int samples )
    : TMatrix<double>( vec_len, samples ), mean( vec_len ), covariance( vec_len, vec_len ) { }

  SampleMatrix( const SampleMatrix & sm ) : TMatrix<double>( sm ), mean( sm.mean ),
    covariance( sm.covariance )
    { }

  SampleMatrix & operator = ( const SampleMatrix & sm )
    {
      TMatrix<double>::operator = ( sm );
      mean = sm.mean;
      covariance = sm.covariance;
      return * this;
    }

  ~SampleMatrix( void ) { }

  /*		int CalcMultiStats(dvector&, dmatrix&);

  };  */

  double CalcMahalanobis( const TVector<double> & t ) const
    {
      TVector<double> mean;
      TMatrix<double> cov;
      CalcMultiStats( mean, cov );
      double mahal = ( mean - t ).Dot( cov.FindInverse() * ( mean - t ) );

      return mahal;
    }

  int CalcMultiStats( TVector<double> & mean, TMatrix<double> & covariance ) const
    //calculates the mean and covariance of [columns] number of samples of [rows] dimensions
    {
      int N = CountColumns();
      int M = CountRows();

      //find the mean
      mean = TVector<double>( M );
      for ( int i = 0; i < N; i++ )
	{ mean += GetColumn( i ); }
      mean /= N;

      TMatrix<double> cov( M, N );
      //find the covariance
      for ( int i = 0; i < N; i++ )
	{
	  //subtract the mean
	  cov.SetColumn( i, GetColumn( i ) - mean );
	}

      covariance = cov * cov.MakeTranspose() * ( 1.0 / ( double )( N - 1 ) );

      return N;
    }
};
