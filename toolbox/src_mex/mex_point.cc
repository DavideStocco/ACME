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

#include "acme.hh"
#include "acme_entity.hh"
#include "acme_point.hh"
#include "mex_utils.hh"

#define ASSERT(COND, MSG)                \
  if (!(COND))                           \
  {                                      \
    std::ostringstream ost;              \
    ost << "mex_point: " << MSG << '\n'; \
    mexErrMsgTxt(ost.str().c_str());     \
  }

#define MEX_ERROR_MESSAGE                                                      \
  "%======================================================================%\n" \
  "% mex_point: Mex wrapper for ACME point object.                        %\n" \
  "%                                                                      %\n" \
  "% CONSTRUCTOR:                                                         %\n" \
  "%   obj = mex_point( 'new' );                                          %\n" \
  "%   obj = mex_point( 'new', X, Y, Z );                                 %\n" \
  "%   obj = mex_point( 'new', [X, Y, Z] );                               %\n" \
  "%                                                                      %\n" \
  "%======================================================================%\n" \
  "%                                                                      %\n" \
  "%    Davide Stocco                                                     %\n" \
  "%    Department of Industrial Engineering                              %\n" \
  "%    University of Trento                                              %\n" \
  "%    davide.stocco@unitn.it                                            %\n" \
  "%                                                                      %\n" \
  "%    Enrico Bertolazzi                                                 %\n" \
  "%    Department of Industrial Engineering                              %\n" \
  "%    University of Trento                                              %\n" \
  "%    enrico.bertolazzi@unitn.it                                        %\n" \
  "%                                                                      %\n" \
  "%======================================================================%\n"

using namespace std;

typedef double real_type;

static void
DATA_NEW(
    mxArray *&mx_id,
    acme::point *ptr)
{
  mx_id = convertPtr2Mat<acme::point>(ptr);
}

static inline acme::point *
DATA_GET(
    mxArray const *&mx_id)
{
  return convertMat2Ptr<acme::point>(mx_id);
}

static void
DATA_DELETE(
    mxArray const *&mx_id)
{
  destroyObject<acme::point>(mx_id);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_new(int nlhs, mxArray *plhs[],
       int nrhs, mxArray const *prhs[])
{

#define CMD "mex_point( 'new', [, args] ): "
  MEX_ASSERT(nrhs == 1 || nrhs == 2 || nrhs == 4, CMD "expected 1, 2 or 4 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  MEX_ASSERT(
      mxIsChar(arg_in_0),
      CMD << "first argument must be a string, found ``" << mxGetClassName(arg_in_0) << "''\n");
  string tname = mxArrayToString(arg_in_0);

  real_type x = acme::NaN;
  real_type y = acme::NaN;
  real_type z = acme::NaN;
  if (nrhs == 2)
  {
    real_type const *matrix_ptr;
    mwSize rows, cols;
    matrix_ptr = getMatrixPointer(arg_in_1, rows, cols, CMD "Error in input matrix");
    MEX_ASSERT(rows == 3 || cols == 1, CMD "expected rows = 3 and cols = 1 found, rows = " << rows << ", cols = " << cols << '\n');
    x = matrix_ptr[0];
    y = matrix_ptr[1];
    z = matrix_ptr[2];
  }
  else if (nrhs == 4)
  {
    x = getScalarValue(arg_in_1, CMD "Error in reading x value");
    y = getScalarValue(arg_in_2, CMD "Error in reading y value");
    z = getScalarValue(arg_in_3, CMD "Error in reading z value");
  }

  acme::point *ptr = new acme::point(x, y, z);
  DATA_NEW(arg_out_0, ptr);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_delete(int nlhs, mxArray *plhs[],
          int nrhs, mxArray const *prhs[])
{
#define CMD "mex_point( 'delete', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  DATA_DELETE(arg_in_1);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getX(int nlhs, mxArray *plhs[],
        int nrhs, mxArray const *prhs[])
{

#define CMD "mex_point( 'getX', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  acme::point *self = DATA_GET(arg_in_1);
  setScalarValue(arg_out_0, self->x());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getY(int nlhs, mxArray *plhs[],
        int nrhs, mxArray const *prhs[])
{

#define CMD "mex_point( 'getY', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  acme::point *self = DATA_GET(arg_in_1);
  setScalarValue(arg_out_0, self->y());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getZ(int nlhs, mxArray *plhs[],
        int nrhs, mxArray const *prhs[])
{

#define CMD "mex_point( 'getZ', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  acme::point *self = DATA_GET(arg_in_1);
  setScalarValue(arg_out_0, self->z());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_get(int nlhs, mxArray *plhs[],
       int nrhs, mxArray const *prhs[])
{

#define CMD "mex_point( 'get', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  acme::point *self = DATA_GET(arg_in_1);
  real_type *output = createMatrixValue(arg_out_0, 3, 1);
  output[0] = self->x();
  output[1] = self->y();
  output[2] = self->z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_setX(int nlhs, mxArray *plhs[],
        int nrhs, mxArray const *prhs[])
{

#define CMD "mex_point( 'setX', OBJ, VALUE ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  acme::point *self = DATA_GET(arg_in_1);
  real_type value = getScalarValue(arg_in_2, CMD "Error in reading x value");
  self->x() = value;
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_setY(int nlhs, mxArray *plhs[],
        int nrhs, mxArray const *prhs[])
{

#define CMD "mex_point( 'setX', OBJ, VALUE ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  acme::point *self = DATA_GET(arg_in_1);
  real_type value = getScalarValue(arg_in_2, CMD "Error in reading y value");
  self->y() = value;
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_setZ(int nlhs, mxArray *plhs[],
        int nrhs, mxArray const *prhs[])
{

#define CMD "mex_point( 'setZ', OBJ, VALUE ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  acme::point *self = DATA_GET(arg_in_0);
  real_type value = getScalarValue(arg_in_1, CMD "Error in reading z value");
  self->z() = value;
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_set(int nlhs, mxArray *plhs[],
       int nrhs, mxArray const *prhs[])
{

#define CMD "mex_point( 'set', OBJ, args ): "
  MEX_ASSERT(nrhs == 3 || nrhs == 5, CMD "expected 3 or 5 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  acme::point *self = DATA_GET(arg_in_1);
  real_type x = acme::NaN;
  real_type y = acme::NaN;
  real_type z = acme::NaN;
  if (nrhs == 3)
  {
    real_type const *matrix_ptr;
    mwSize rows, cols;
    matrix_ptr = getMatrixPointer(arg_in_2, rows, cols, CMD "Error in reading input matrix");
    MEX_ASSERT(rows == 3 || cols == 1, CMD "expected rows = 3 and cols = 1 found, rows = " << rows << ", cols = " << cols << '\n');
    x = matrix_ptr[0];
    y = matrix_ptr[1];
    z = matrix_ptr[2];
  }
  else if (nrhs == 5)
  {
    x = getScalarValue(arg_in_2, CMD "Error in reading x value");
    y = getScalarValue(arg_in_3, CMD "Error in reading y value");
    z = getScalarValue(arg_in_4, CMD "Error in reading z value");
  }
  self->x() = x;
  self->y() = y;
  self->z() = z;
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_copy(int nlhs, mxArray *plhs[],
        int nrhs, mxArray const *prhs[])
{

#define CMD "mex_point( 'copy', OBJ, OTHER_OBJ ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  acme::point *self = DATA_GET(arg_in_1);
  acme::point *other = DATA_GET(arg_in_2);
  self->x() = other->x();
  self->y() = other->y();
  self->z() = other->z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_translate(int nlhs, mxArray *plhs[],
             int nrhs, mxArray const *prhs[])
{
#define CMD "mex_point( 'translate', OBJ, [X, Y, Z] ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  acme::point *self = DATA_GET(arg_in_1);
  real_type const *matrix_ptr;
  mwSize rows, cols;
  matrix_ptr = getMatrixPointer(arg_in_2, rows, cols, CMD "Error in first input matrix");
  MEX_ASSERT(rows == 3 || cols == 1, CMD "expected rows = 3 and cols = 1 found, rows = " << rows << ", cols = " << cols << '\n');
  real_type x = matrix_ptr[0];
  real_type y = matrix_ptr[1];
  real_type z = matrix_ptr[2];
  self->translate(acme::vec3(x, y, z));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_transform(int nlhs, mxArray *plhs[],
             int nrhs, mxArray const *prhs[])
{

#define CMD "mex_point( 'transform', OBJ, MATRIX ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  acme::point *self = DATA_GET(arg_in_1);
  real_type const *matrix_ptr;
  mwSize rows, cols;
  matrix_ptr = getMatrixPointer(arg_in_2, rows, cols, CMD "Error in reading affine transformation matrix");
  acme::affine matrix;

  MEX_ASSERT(rows == 4 || cols == 4, CMD "expected rows = 4 and cols = 4 found, rows = " << rows << ", cols = " << cols << '\n');
  matrix.matrix() << matrix_ptr[0], matrix_ptr[1], matrix_ptr[2], matrix_ptr[3],
      matrix_ptr[4], matrix_ptr[5], matrix_ptr[6], matrix_ptr[7],
      matrix_ptr[8], matrix_ptr[9], matrix_ptr[10], matrix_ptr[1],
      matrix_ptr[12], matrix_ptr[13], matrix_ptr[14], matrix_ptr[15];
  acme::point *out = new acme::point((*self));
  out->transform(matrix);
  DATA_NEW(arg_out_0, out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef void (*DO_CMD)(int nlhs, mxArray *plhs[],
                       int nrhs, mxArray const *prhs[]);

static map<string, DO_CMD> cmd_to_fun = {
    {"new", do_new},
    {"delete", do_delete},
    {"getX", do_getX},
    {"getY", do_getY},
    {"getZ", do_getZ},
    {"get", do_get},
    {"setX", do_setX},
    {"setY", do_setY},
    {"setZ", do_setZ},
    {"set", do_set},
    {"copy", do_copy},
    {"translate", do_translate},
    {"transform", do_transform}};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

extern "C" void
mexFunction(int nlhs, mxArray *plhs[],
            int nrhs, mxArray const *prhs[])
{
  // the first argument must be a string
  if (nrhs == 0)
  {
    mexErrMsgTxt(MEX_ERROR_MESSAGE);
    return;
  }

  try
  {
    MEX_ASSERT(mxIsChar(arg_in_0), "First argument must be a string");
    string cmd = mxArrayToString(arg_in_0);
    DO_CMD pfun = cmd_to_fun.at(cmd);
    pfun(nlhs, plhs, nrhs, prhs);
  }
  catch (exception const &e)
  {
    mexErrMsgTxt((string("mex_point Error: ") + e.what()).c_str());
  }
  catch (...)
  {
    mexErrMsgTxt("mex_point failed\n");
  }
}