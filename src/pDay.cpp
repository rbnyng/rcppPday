#include <RcppArmadillo.h>

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]
arma::vec pDayInRangeCppVec(arma::vec min, arma::vec max, double lwr_temp, double upr_temp){
  int n = min.n_elem;
  arma::vec portion_in(n);
  double A, b = M_PI*2, h = 0.5, k;
  int numSteps = 100, countInRange;
  double stepSize = 1.0 / numSteps;
  std::vector<double> x(numSteps + 1);

  for(int j = 0; j < n; j++){
    A = abs((max[j] - min[j])/2);
    k = (max[j] + min[j])/2;
    countInRange = 0;
    for (int i = 0; i <= numSteps; ++i) {
      x[i] = i * stepSize;
      double y = A*cos(b*(x[i] - h)) + k;
      if (y >= lwr_temp && y <= upr_temp)
        ++countInRange;
    }
    portion_in[j] = static_cast<double>(countInRange) / (numSteps + 1);
  }

  return portion_in;
}
