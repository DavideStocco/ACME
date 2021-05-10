/*
(***********************************************************************)
(*                                                                     *)
(* The ACME project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Davide Stocco and Enrico Bertolazzi.       *)
(*                                                                     *)
(* The ACME project and its components are supplied under the terms of *)
(* the open source BSD 2-Clause License. The contents of the ACME      *)
(* project and its components may not be copied or disclosed except in *)
(* accordance with the terms of the BSD 2-Clause License.              *)
(*                                                                     *)
(* URL: https://opensource.org/licenses/BSD-2-Clause                   *)
(*                                                                     *)
(*    Davide Stocco                                                    *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: davide.stocco@unitn.it                                   *)
(*                                                                     *)
(*    Enrico Bertolazzi                                                *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: enrico.bertolazzi@unitn.it                               *)
(*                                                                     *)
(***********************************************************************)
*/

///
/// file: acme_triangle.hh
///

#ifndef INCLUDE_ACME_TRIANGLE
#define INCLUDE_ACME_TRIANGLE

#include "acme.hh"
#include "acme_aabb.hh"
#include "acme_plane.hh"
#include "acme_point.hh"
#include "acme_segment.hh"

namespace acme
{

  /*\
   |   _        _                   _      
   |  | |_ _ __(_) __ _ _ __   __ _| | ___ 
   |  | __| '__| |/ _` | '_ \ / _` | |/ _ \
   |  | |_| |  | | (_| | | | | (_| | |  __/
   |   \__|_|  |_|\__,_|_| |_|\__, |_|\___|
   |                          |___/        
  \*/

  //! Triangle class container
  /**
   * Triangle in 3D space. The triangle is defined by three arbitrary points.
   */
  class triangle : public entity
  {
public:
    typedef std::shared_ptr<triangle const> ptr; //!< Shared pointer to triangle object
    typedef std::pair<ptr, ptr> pairptr;         //!< Pair of pointers to triangle objects
    typedef std::vector<ptr> vecptr;             //!< Vector of pointers to triangle objects
    typedef std::vector<pairptr> vecpairptr;     //!< Vector of pairs of pointers to triangle objects

private:
    point _vertex[3]; //!< Triangle vertices

public:
    //! Triangle class destructor
    ~triangle() {}

    //! Triangle copy constructor
    triangle(triangle const &) = default;

    //! Triangle move constructor
    triangle(triangle &&) = default;

    //! Triangle class constructor
    triangle() {}

    //! Triangle class constructor
    triangle(
        real x0, //<! Input x value of first triangle vertex
        real y0, //<! Input y value of first triangle vertex
        real z0, //<! Input z value of first triangle vertex
        real x1, //<! Input x value of second triangle vertex
        real y1, //<! Input y value of second triangle vertex
        real z1, //<! Input z value of second triangle vertex
        real x2, //<! Input x value of third triangle vertex
        real y2, //<! Input y value of third triangle vertex
        real z2  //<! Input z value of third triangle vertex
    );

    //! Triangle class constructor
    triangle(
        point const &point0, //!< Input first triangle vertex point
        point const &point1, //!< Input second triangle vertex point
        point const &point2  //!< Input third triangle vertex point
    );

    //! Triangle class constructor
    triangle(
        point const point[3] //!< Input triangle verices
    );

    //! Equality operator
    triangle &
    operator=(
        triangle const &input //!< Input triangle object
    );

    //! Check if objects are (almost) equal
    bool
    isApprox(
        triangle const &input //!< Input triangle object
    ) const;

    //! Get i-th triangle vertex
    point const &
    vertex(
        integer i //!< New triangle vertex
    ) const;

    //! Get i-th triangle vertex
    point &
    vertex(
        integer i //!< New triangle vertex
    );

    //! Set triangle vertices
    void
    vertices(
        point const &vertex0, //!< Input first triangle vertex
        point const &vertex1, //!< Input second triangle vertex
        point const &vertex2  //!< Input third triangle vertex
    );

    //! Set triangle vertices vertices
    void
    vertices(
        point const vertex[3] //!< New triangle vertices
    );

    //! Get triangle centroid
    point
    centroid(void) const;

    //! Get triangle edge created by i-th and j-th vertex
    segment
    edge(
        integer i, //!< Triangle i-th vertex index
        integer j  //!< Triangle j-th vertex index
    ) const;

    //! Get triangle face normal (normalized vector)
    vec3
    normal(void) const;

    //! Swap triangle vertices
    void
    swap(
        integer i, //!< Triangle i-th vertex index
        integer j  //!< Triangle j-th vertex index
    );

    //! Get minimum aabb containing the current triangle object
    void
    clamp(
        aabb &input //!< Input aabb object
    ) const;

    //! Calculate triangle perimeter length
    real
    perimeter(void)
        const;

    //! Calculate triangle area
    real
    area(void) const;

    //! Compute barycentric coordinates (u,v,w) for point
    void
    barycentric(
        point const &query_point, //!< Input point
        real &u,                  //!< Output barycentric coordinate u
        real &v,                  //!< Output barycentric coordinate v
        real &w                   //!< Output barycentric coordinate w
    ) const;

    //! Get triangle laying plane
    plane
    layingPlane(void) const;

    //! Translate triangle by vector
    void
    translate(
        vec3 const &input //!< Input translation vector
        ) override;

    //! Transform triangle with affine transformation matrix
    void
    transform(
        affine const &matrix //!< 4x4 affine transformation matrix
        ) override;

    //! Check if a point lays inside the triangle
    bool
    isInside(
        point const &query_point //!< Query point
    ) const;

    //! Check if triangle is degenerated to point or segment
    bool
    isDegenerated(void) const override;

    //! Return object hierarchical degree
    integer degree(void) const override { return 7; }

    //! Return object type as string
    std::string type(void) const override { return "triangle"; }

    //! Check whether the object is no entity
    bool isNone(void) const override { return false; }

    //! Check whether the object is a point
    bool isPoint(void) const override { return false; }

    //! Check whether the object is a line
    bool isLine(void) const override { return false; }

    //! Check whether the object is a ray
    bool isRay(void) const override { return false; }

    //! Check whether the object is a plane
    bool isPlane(void) const override { return false; }

    //! Check whether the object is a segment
    bool isSegment(void) const override { return false; }

    //! Check whether the object is a triangle
    bool isTriangle(void) const override { return true; }

    //! Check whether the object is a circle
    bool isCircle(void) const override { return false; }

    //! Check whether the object is a aabb
    bool isBox(void) const override { return false; }

  }; // class triangle

  static triangle const NaN_triangle = triangle(acme::NaN_point, acme::NaN_point, NaN_point); //!< Not-a-Number triangle type
  static triangle triangle_goat = triangle(NaN_triangle);                                     //!< Scapegoat triangle type (throwaway non-const object)

} // namespace acme

#endif

///
/// eof: acme_triangle.hh
///