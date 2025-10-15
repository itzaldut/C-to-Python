#include "mylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

double findPi(long nthrows)
{
	if (nthrows <= 0) {
        // maybe guard or fallback
        nthrows = 100 * 1000 * 1000L;
    }
    	srand48((long)time(NULL));
	long count = 0;
    	for (long i = 0; i < nthrows; ++i) {
		double x = drand48();
		double y = drand48();
		if (x*x + y*y < 1.0) {
	    		++count;
		}
    	}
    	return 4.0 * count / (double)nthrows;
 }

double magnitude(double re, double im)
{
     return sqrt(re*re + im*im);
}

int mandel_test(double c_re, double c_im, int NTRIALS)
{
	double z_re = c_re;
    	double z_im = c_im;
    	int counts = 1;
    	while (magnitude(z_re, z_im) <= 2.0 && counts < NTRIALS) {
	 	counts++;
		double re = z_re;
		double im = z_im;
		z_re = re*re - im*im + c_re;
		z_im = 2*re*im + c_im;
    	}
    	return counts;
}

void mandel(double *img, double re1, double re2,
            double im1, double im2,
            int nr, int ni, int NTRIALS)
{
	double dx = (re2 - re1) / nr;
    	double dy = (im2 - im1) / ni;
    	for (int j = 0; j < ni; ++j) {
		double im = im1 + j * dy;
		for (int i = 0; i < nr; ++i) {
	    		double re = re1 + i * dx;
	    		img[j * nr + i] = mandel_test(re, im, NTRIALS);
		}
    	}	
}

double HSVolume(int d, long N, double r)
{
    if (d < 1 || N <= 0 || r < 0) {
        return 0.0;  // or error code
    }
    long count_inside = 0;
    // We'll sample in the cube [-r, r]^d and count how many fall inside the hypersphere.
    for (long i = 0; i < N; i++) {
        double sumsq = 0.0;
        // generate d random coordinates
        for (int j = 0; j < d; j++) {
            // uniform in [-r, r]
            double x = (2.0 * drand48() - 1.0) * r;
            sumsq += x * x;
            if (sumsq > r * r) {
                // already outside, break early
                break;
            }
        }
        if (sumsq <= r * r) {
            count_inside++;
        }
    }
    double cube_vol = pow(2.0 * r, d);  // volume of [-r, r]^d
    return cube_vol * ( (double)count_inside / (double)N );
}

#ifdef __cplusplus
}
#endif

