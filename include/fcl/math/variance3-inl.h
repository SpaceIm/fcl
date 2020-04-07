/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2011-2014, Willow Garage, Inc.
 *  Copyright (c) 2014-2016, Open Source Robotics Foundation
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Open Source Robotics Foundation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/** @author Jia Pan */

#ifndef FCL_MATH_VARIANCE3_INL_H
#define FCL_MATH_VARIANCE3_INL_H

#include "fcl/math/variance3.h"

namespace fcl
{

//==============================================================================
extern template
class FCL_EXTERN_TEMPLATE_API Variance3<double>;

//==============================================================================
template <typename S>
Variance3<S>::Variance3()
{
  // Do nothing
}

//==============================================================================
template <typename S>
Variance3<S>::Variance3(const Matrix3<S>& sigma) : Sigma(sigma)
{
  init();
}

//==============================================================================
template <typename S>
void Variance3<S>::init()
{
  eigen_old(Sigma, sigma, axis);
}

//==============================================================================
template <typename S>
Variance3<S>& Variance3<S>::sqrt()
{
  for(std::size_t i = 0; i < 3; ++i)
  {
    if(sigma[i] < 0)
      sigma[i] = 0;

    sigma[i] = std::sqrt(sigma[i]);
  }

  Sigma.noalias()
      =  sigma[0] * axis.col(0) * axis.col(0).transpose();
  Sigma.noalias()
      += sigma[1] * axis.col(1) * axis.col(1).transpose();
  Sigma.noalias()
      += sigma[2] * axis.col(2) * axis.col(2).transpose();

  return *this;
}

} // namespace fcl

#endif
