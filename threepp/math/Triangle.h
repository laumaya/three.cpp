//
// Created by byter on 06.09.17.
//

#ifndef THREEPP_TRIANGLE_H
#define THREEPP_TRIANGLE_H

#include "Vector3.h"

namespace three {
namespace math {

class Triangle 
{
  Vector3 a, b, c;
  
public:
  static Vector3 normal(const Vector3 &a, const Vector3 &b, const Vector3 &c)
  {
    Vector3 result = c - b;
    Vector3 v0 = a - b;
    result.cross( v0 );

    float resultLengthSq = result.lengthSq();
    if ( resultLengthSq > 0 ) {

      return result * ( 1 / std::sqrt( resultLengthSq ) );

    }
    return result.set( 0, 0, 0 );
  }

  // static/instance method to calculate barycentric coordinates
  // based on: http://www.blackpawn.com/texts/pointinpoly/default.html
  static Vector3 barycoordFromPoint(const Vector3 &point, const Vector3 &a, const Vector3 &b, const Vector3 &c)
  {
    Vector3 v0 = c - a;
    Vector3 v1 = b - a;
    Vector3 v2 = point - a;

    float dot00 = v0.dot( v0 );
    float dot01 = v0.dot( v1 );
    float dot02 = v0.dot( v2 );
    float dot11 = v1.dot( v1 );
    float dot12 = v1.dot( v2 );

    float denom = ( dot00 * dot11 - dot01 * dot01 );

    // collinear or singular triangle
    if ( denom == 0 ) {

      // arbitrary location outside of triangle?
      // not sure if this is the best idea, maybe should be returning undefined
      return Vector3( - 2, - 1, - 1 );
    }

    float invDenom = 1 / denom;
    float u = ( dot11 * dot02 - dot01 * dot12 ) * invDenom;
    float v = ( dot00 * dot12 - dot01 * dot02 ) * invDenom;

    // barycentric coordinates must always sum to 1
    return Vector3( 1 - u - v, v, u );
  }

  static bool containsPoint(const Vector3 &point, const Vector3 &a, const Vector3 &b, const Vector3 &c)
  {
    Vector3 result = barycoordFromPoint( point, a, b, c);

    return (result.x() >= 0) && (result.y() >= 0) && ((result.x() + result.y()) <= 1);
  }
};

}
}

#endif //THREEPP_TRIANGLE_H
