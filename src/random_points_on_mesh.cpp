#include "random_points_on_mesh.h"
#include <random>
#include <iostream>

//#define VERTEX_ONLY

void random_points_on_mesh(
  const int n,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & X)
{
  // REPLACE WITH YOUR CODE:
  X.resize(n,3);
  static std::default_random_engine generator;
#ifndef VERTEX_ONLY
  int max_face_index = F.rows();
  //from http://www.cplusplus.com/reference/random/uniform_int_distribution/
  std::uniform_int_distribution<int> rand_distribution_int(0, max_face_index);
  //from http://www.cplusplus.com/reference/random/uniform_real_distribution/
  std::uniform_real_distribution<double> rand_distribution_double(0.0, 1.0);

  for (int m = 0; m < X.rows(); m++)
  {
    int face_index = rand_distribution_int(generator);
    double alpha, beta;
    alpha = rand_distribution_double(generator);
    beta = rand_distribution_double(generator);
    if (alpha + beta > 1)
    {
      alpha = 1 - alpha;
      beta = 1 - beta;
    }
    X.row(m) = V.row(F(face_index, 0)) +
              (V.row(F(face_index, 1)) - V.row(F(face_index, 0)))*alpha +
              (V.row(F(face_index, 2)) - V.row(F(face_index, 0)))*beta;
  }

#else
  int max_vertex_index = V.rows();
  std::uniform_int_distribution<int> rand_distribution_int(0, max_vertex_index);
  for (int m = 0; m < X.rows(); m++)
  {
    int vertex_index = rand_distribution_int(generator);
    X.row(m) = V.row(vertex_index);
  }
#endif

}

