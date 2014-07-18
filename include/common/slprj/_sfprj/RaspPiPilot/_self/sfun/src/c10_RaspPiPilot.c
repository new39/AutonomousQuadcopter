/* Include files */

#include <stddef.h>
#include "blas.h"
#include "RaspPiPilot_sfun.h"
#include "c10_RaspPiPilot.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "RaspPiPilot_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c10_debug_family_names[6] = { "nargin", "nargout", "R", "G",
  "B", "yellowIntensity" };

/* Function Declarations */
static void initialize_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance);
static void initialize_params_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance);
static void enable_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance);
static void disable_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance);
static void c10_update_debugger_state_c10_RaspPiPilot
  (SFc10_RaspPiPilotInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c10_RaspPiPilot
  (SFc10_RaspPiPilotInstanceStruct *chartInstance);
static void set_sim_state_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c10_st);
static void finalize_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance);
static void sf_gateway_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance);
static void c10_chartstep_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance);
static void initSimStructsc10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c10_machineNumber, uint32_T
  c10_chartNumber, uint32_T c10_instanceNumber);
static const mxArray *c10_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c10_inData_data[], int32_T c10_inData_sizes[2]);
static void c10_emlrt_marshallIn(SFc10_RaspPiPilotInstanceStruct *chartInstance,
  const mxArray *c10_yellowIntensity, const char_T *c10_identifier, uint8_T
  c10_y_data[], int32_T c10_y_sizes[2]);
static void c10_b_emlrt_marshallIn(SFc10_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId,
  uint8_T c10_y_data[], int32_T c10_y_sizes[2]);
static void c10_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, uint8_T c10_outData_data[],
  int32_T c10_outData_sizes[2]);
static const mxArray *c10_b_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static const mxArray *c10_c_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static real_T c10_c_emlrt_marshallIn(SFc10_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId);
static void c10_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static void c10_info_helper(const mxArray **c10_info);
static const mxArray *c10_emlrt_marshallOut(const char * c10_u);
static const mxArray *c10_b_emlrt_marshallOut(const uint32_T c10_u);
static const mxArray *c10_d_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData);
static int32_T c10_d_emlrt_marshallIn(SFc10_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId);
static void c10_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData);
static uint8_T c10_e_emlrt_marshallIn(SFc10_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c10_b_is_active_c10_RaspPiPilot, const char_T
  *c10_identifier);
static uint8_T c10_f_emlrt_marshallIn(SFc10_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId);
static void init_dsm_address_info(SFc10_RaspPiPilotInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance)
{
  chartInstance->c10_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c10_is_active_c10_RaspPiPilot = 0U;
}

static void initialize_params_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c10_update_debugger_state_c10_RaspPiPilot
  (SFc10_RaspPiPilotInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c10_RaspPiPilot
  (SFc10_RaspPiPilotInstanceStruct *chartInstance)
{
  const mxArray *c10_st;
  const mxArray *c10_y = NULL;
  int32_T c10_u_sizes[2];
  int32_T c10_u;
  int32_T c10_b_u;
  int32_T c10_loop_ub;
  int32_T c10_i0;
  uint8_T c10_u_data[76800];
  const mxArray *c10_b_y = NULL;
  uint8_T c10_hoistedGlobal;
  uint8_T c10_c_u;
  const mxArray *c10_c_y = NULL;
  int32_T (*c10_yellowIntensity_sizes)[2];
  uint8_T (*c10_yellowIntensity_data)[76800];
  c10_yellowIntensity_sizes = (int32_T (*)[2])
    ssGetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1);
  c10_yellowIntensity_data = (uint8_T (*)[76800])ssGetOutputPortSignal
    (chartInstance->S, 1);
  c10_st = NULL;
  c10_st = NULL;
  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_createcellmatrix(2, 1), false);
  c10_u_sizes[0] = (*c10_yellowIntensity_sizes)[0];
  c10_u_sizes[1] = (*c10_yellowIntensity_sizes)[1];
  c10_u = c10_u_sizes[0];
  c10_b_u = c10_u_sizes[1];
  c10_loop_ub = (*c10_yellowIntensity_sizes)[0] * (*c10_yellowIntensity_sizes)[1]
    - 1;
  for (c10_i0 = 0; c10_i0 <= c10_loop_ub; c10_i0++) {
    c10_u_data[c10_i0] = (*c10_yellowIntensity_data)[c10_i0];
  }

  c10_b_y = NULL;
  sf_mex_assign(&c10_b_y, sf_mex_create("y", c10_u_data, 3, 0U, 1U, 0U, 2,
    c10_u_sizes[0], c10_u_sizes[1]), false);
  sf_mex_setcell(c10_y, 0, c10_b_y);
  c10_hoistedGlobal = chartInstance->c10_is_active_c10_RaspPiPilot;
  c10_c_u = c10_hoistedGlobal;
  c10_c_y = NULL;
  sf_mex_assign(&c10_c_y, sf_mex_create("y", &c10_c_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c10_y, 1, c10_c_y);
  sf_mex_assign(&c10_st, c10_y, false);
  return c10_st;
}

static void set_sim_state_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c10_st)
{
  const mxArray *c10_u;
  int32_T c10_tmp_sizes[2];
  uint8_T c10_tmp_data[76800];
  int32_T c10_i1;
  int32_T c10_i2;
  int32_T c10_loop_ub;
  int32_T c10_i3;
  uint8_T (*c10_yellowIntensity_data)[76800];
  int32_T (*c10_yellowIntensity_sizes)[2];
  c10_yellowIntensity_sizes = (int32_T (*)[2])
    ssGetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1);
  c10_yellowIntensity_data = (uint8_T (*)[76800])ssGetOutputPortSignal
    (chartInstance->S, 1);
  chartInstance->c10_doneDoubleBufferReInit = true;
  c10_u = sf_mex_dup(c10_st);
  c10_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c10_u, 0)),
                       "yellowIntensity", c10_tmp_data, c10_tmp_sizes);
  ssSetCurrentOutputPortDimensions(chartInstance->S, 1, 0, c10_tmp_sizes[0]);
  ssSetCurrentOutputPortDimensions(chartInstance->S, 1, 1, c10_tmp_sizes[1]);
  c10_i1 = (*c10_yellowIntensity_sizes)[0];
  c10_i2 = (*c10_yellowIntensity_sizes)[1];
  c10_loop_ub = c10_tmp_sizes[0] * c10_tmp_sizes[1] - 1;
  for (c10_i3 = 0; c10_i3 <= c10_loop_ub; c10_i3++) {
    (*c10_yellowIntensity_data)[c10_i3] = c10_tmp_data[c10_i3];
  }

  chartInstance->c10_is_active_c10_RaspPiPilot = c10_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c10_u, 1)),
     "is_active_c10_RaspPiPilot");
  sf_mex_destroy(&c10_u);
  c10_update_debugger_state_c10_RaspPiPilot(chartInstance);
  sf_mex_destroy(&c10_st);
}

static void finalize_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance)
{
  int32_T c10_i4;
  int32_T c10_loop_ub;
  int32_T c10_i5;
  int32_T c10_i6;
  int32_T c10_i7;
  int32_T (*c10_yellowIntensity_sizes)[2];
  uint8_T (*c10_B)[76800];
  uint8_T (*c10_G)[76800];
  uint8_T (*c10_yellowIntensity_data)[76800];
  uint8_T (*c10_R)[76800];
  c10_B = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 2);
  c10_G = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 1);
  c10_yellowIntensity_sizes = (int32_T (*)[2])
    ssGetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1);
  c10_yellowIntensity_data = (uint8_T (*)[76800])ssGetOutputPortSignal
    (chartInstance->S, 1);
  c10_R = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 9U, chartInstance->c10_sfEvent);
  for (c10_i4 = 0; c10_i4 < 76800; c10_i4++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c10_R)[c10_i4], 0U);
  }

  chartInstance->c10_sfEvent = CALL_EVENT;
  c10_chartstep_c10_RaspPiPilot(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_RaspPiPilotMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  c10_loop_ub = (*c10_yellowIntensity_sizes)[0] * (*c10_yellowIntensity_sizes)[1]
    - 1;
  for (c10_i5 = 0; c10_i5 <= c10_loop_ub; c10_i5++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c10_yellowIntensity_data)[c10_i5], 1U);
  }

  for (c10_i6 = 0; c10_i6 < 76800; c10_i6++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c10_G)[c10_i6], 2U);
  }

  for (c10_i7 = 0; c10_i7 < 76800; c10_i7++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c10_B)[c10_i7], 3U);
  }
}

static void c10_chartstep_c10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance)
{
  int32_T c10_i8;
  static uint8_T c10_R[76800];
  int32_T c10_i9;
  static uint8_T c10_G[76800];
  int32_T c10_i10;
  static uint8_T c10_B[76800];
  uint32_T c10_debug_family_var_map[6];
  real_T c10_nargin = 3.0;
  real_T c10_nargout = 1.0;
  int32_T c10_yellowIntensity_sizes[2];
  static uint8_T c10_yellowIntensity_data[76800];
  int32_T c10_i11;
  uint8_T c10_b[76800];
  int32_T c10_i12;
  uint8_T c10_u0;
  uint8_T c10_u1;
  int32_T c10_i13;
  uint32_T c10_u2;
  uint32_T c10_q0;
  uint32_T c10_qY;
  uint32_T c10_u3;
  int32_T c10_k;
  real_T c10_b_k;
  real_T c10_xk;
  real_T c10_d0;
  uint8_T c10_u4;
  uint8_T c10_uv0[76800];
  int32_T c10_yellowIntensity;
  int32_T c10_b_yellowIntensity;
  int32_T c10_i14;
  int32_T c10_i15;
  int32_T c10_i16;
  int32_T c10_loop_ub;
  int32_T c10_i17;
  uint8_T (*c10_b_yellowIntensity_data)[76800];
  int32_T (*c10_b_yellowIntensity_sizes)[2];
  uint8_T (*c10_b_B)[76800];
  uint8_T (*c10_b_G)[76800];
  uint8_T (*c10_b_R)[76800];
  c10_b_B = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 2);
  c10_b_G = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 1);
  c10_b_yellowIntensity_sizes = (int32_T (*)[2])
    ssGetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1);
  c10_b_yellowIntensity_data = (uint8_T (*)[76800])ssGetOutputPortSignal
    (chartInstance->S, 1);
  c10_b_R = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 9U, chartInstance->c10_sfEvent);
  for (c10_i8 = 0; c10_i8 < 76800; c10_i8++) {
    c10_R[c10_i8] = (*c10_b_R)[c10_i8];
  }

  for (c10_i9 = 0; c10_i9 < 76800; c10_i9++) {
    c10_G[c10_i9] = (*c10_b_G)[c10_i9];
  }

  for (c10_i10 = 0; c10_i10 < 76800; c10_i10++) {
    c10_B[c10_i10] = (*c10_b_B)[c10_i10];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 6U, c10_debug_family_names,
    c10_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_nargin, 0U, c10_c_sf_marshallOut,
    c10_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_nargout, 1U, c10_c_sf_marshallOut,
    c10_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c10_R, 2U, c10_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c10_G, 3U, c10_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c10_B, 4U, c10_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c10_yellowIntensity_data, (const
    int32_T *)&c10_yellowIntensity_sizes, NULL, 0, 5, (void *)c10_sf_marshallOut,
    (void *)c10_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, 3);
  for (c10_i11 = 0; c10_i11 < 76800; c10_i11++) {
    c10_b[c10_i11] = c10_B[c10_i11];
  }

  for (c10_i12 = 0; c10_i12 < 76800; c10_i12++) {
    c10_u0 = c10_b[c10_i12];
    if (CV_SATURATION_EVAL(4, 0, 3, 0, c10_u0 > 127)) {
      c10_u1 = MAX_uint8_T;
    } else {
      c10_u1 = (uint8_T)(c10_u0 << 1);
    }

    c10_b[c10_i12] = c10_u1;
  }

  for (c10_i13 = 0; c10_i13 < 76800; c10_i13++) {
    c10_u2 = (uint32_T)c10_R[c10_i13] + (uint32_T)c10_G[c10_i13];
    if (CV_SATURATION_EVAL(4, 0, 1, 0, c10_u2 > 255U)) {
      c10_u2 = 255U;
    }

    c10_q0 = (uint8_T)c10_u2;
    c10_qY = c10_q0 - (uint32_T)c10_b[c10_i13];
    if (CV_SATURATION_EVAL(4, 0, 2, 0, c10_qY > c10_q0)) {
      c10_qY = 0U;
    }

    c10_u3 = c10_qY;
    if (CV_SATURATION_EVAL(4, 0, 2, 0, c10_u3 > 255U)) {
      c10_u3 = 255U;
    }

    c10_b[c10_i13] = (uint8_T)c10_u3;
  }

  for (c10_k = 0; c10_k < 76800; c10_k++) {
    c10_b_k = 1.0 + (real_T)c10_k;
    c10_xk = (real_T)c10_b[(int32_T)c10_b_k - 1];
    c10_d0 = muDoubleScalarRound(c10_xk / 2.0);
    if (c10_d0 < 256.0) {
      if (CV_SATURATION_EVAL(4, 0, 0, 1, c10_d0 >= 0.0)) {
        c10_u4 = (uint8_T)c10_d0;
      } else {
        c10_u4 = 0U;
      }
    } else if (CV_SATURATION_EVAL(4, 0, 0, 0, c10_d0 >= 256.0)) {
      c10_u4 = MAX_uint8_T;
    } else {
      c10_u4 = 0U;
    }

    c10_uv0[(int32_T)c10_b_k - 1] = c10_u4;
  }

  c10_yellowIntensity_sizes[0] = 320;
  c10_yellowIntensity_sizes[1] = 240;
  c10_yellowIntensity = c10_yellowIntensity_sizes[0];
  c10_b_yellowIntensity = c10_yellowIntensity_sizes[1];
  for (c10_i14 = 0; c10_i14 < 76800; c10_i14++) {
    c10_yellowIntensity_data[c10_i14] = c10_uv0[c10_i14];
  }

  _SFD_EML_CALL(0U, chartInstance->c10_sfEvent, -3);
  _SFD_SYMBOL_SCOPE_POP();
  ssSetCurrentOutputPortDimensions(chartInstance->S, 1, 0,
    c10_yellowIntensity_sizes[0]);
  ssSetCurrentOutputPortDimensions(chartInstance->S, 1, 1,
    c10_yellowIntensity_sizes[1]);
  c10_i15 = (*c10_b_yellowIntensity_sizes)[0];
  c10_i16 = (*c10_b_yellowIntensity_sizes)[1];
  c10_loop_ub = c10_yellowIntensity_sizes[0] * c10_yellowIntensity_sizes[1] - 1;
  for (c10_i17 = 0; c10_i17 <= c10_loop_ub; c10_i17++) {
    (*c10_b_yellowIntensity_data)[c10_i17] = c10_yellowIntensity_data[c10_i17];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c10_sfEvent);
}

static void initSimStructsc10_RaspPiPilot(SFc10_RaspPiPilotInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c10_machineNumber, uint32_T
  c10_chartNumber, uint32_T c10_instanceNumber)
{
  (void)c10_machineNumber;
  (void)c10_chartNumber;
  (void)c10_instanceNumber;
}

static const mxArray *c10_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c10_inData_data[], int32_T c10_inData_sizes[2])
{
  const mxArray *c10_mxArrayOutData = NULL;
  int32_T c10_b_inData_sizes[2];
  int32_T c10_loop_ub;
  int32_T c10_i18;
  int32_T c10_b_loop_ub;
  int32_T c10_i19;
  uint8_T c10_b_inData_data[76800];
  int32_T c10_u_sizes[2];
  int32_T c10_c_loop_ub;
  int32_T c10_i20;
  int32_T c10_d_loop_ub;
  int32_T c10_i21;
  uint8_T c10_u_data[76800];
  const mxArray *c10_y = NULL;
  SFc10_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc10_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  c10_b_inData_sizes[0] = c10_inData_sizes[0];
  c10_b_inData_sizes[1] = c10_inData_sizes[1];
  c10_loop_ub = c10_inData_sizes[1] - 1;
  for (c10_i18 = 0; c10_i18 <= c10_loop_ub; c10_i18++) {
    c10_b_loop_ub = c10_inData_sizes[0] - 1;
    for (c10_i19 = 0; c10_i19 <= c10_b_loop_ub; c10_i19++) {
      c10_b_inData_data[c10_i19 + c10_b_inData_sizes[0] * c10_i18] =
        c10_inData_data[c10_i19 + c10_inData_sizes[0] * c10_i18];
    }
  }

  c10_u_sizes[0] = c10_b_inData_sizes[0];
  c10_u_sizes[1] = c10_b_inData_sizes[1];
  c10_c_loop_ub = c10_b_inData_sizes[1] - 1;
  for (c10_i20 = 0; c10_i20 <= c10_c_loop_ub; c10_i20++) {
    c10_d_loop_ub = c10_b_inData_sizes[0] - 1;
    for (c10_i21 = 0; c10_i21 <= c10_d_loop_ub; c10_i21++) {
      c10_u_data[c10_i21 + c10_u_sizes[0] * c10_i20] = c10_b_inData_data[c10_i21
        + c10_b_inData_sizes[0] * c10_i20];
    }
  }

  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u_data, 3, 0U, 1U, 0U, 2,
    c10_u_sizes[0], c10_u_sizes[1]), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static void c10_emlrt_marshallIn(SFc10_RaspPiPilotInstanceStruct *chartInstance,
  const mxArray *c10_yellowIntensity, const char_T *c10_identifier, uint8_T
  c10_y_data[], int32_T c10_y_sizes[2])
{
  emlrtMsgIdentifier c10_thisId;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_yellowIntensity),
    &c10_thisId, c10_y_data, c10_y_sizes);
  sf_mex_destroy(&c10_yellowIntensity);
}

static void c10_b_emlrt_marshallIn(SFc10_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId,
  uint8_T c10_y_data[], int32_T c10_y_sizes[2])
{
  int32_T c10_i22;
  uint32_T c10_uv1[2];
  int32_T c10_i23;
  boolean_T c10_bv0[2];
  int32_T c10_tmp_sizes[2];
  uint8_T c10_tmp_data[76800];
  int32_T c10_y;
  int32_T c10_b_y;
  int32_T c10_loop_ub;
  int32_T c10_i24;
  (void)chartInstance;
  for (c10_i22 = 0; c10_i22 < 2; c10_i22++) {
    c10_uv1[c10_i22] = 320U + (uint32_T)(-80 * (int32_T)(uint32_T)c10_i22);
  }

  for (c10_i23 = 0; c10_i23 < 2; c10_i23++) {
    c10_bv0[c10_i23] = true;
  }

  sf_mex_import_vs(c10_parentId, sf_mex_dup(c10_u), c10_tmp_data, 1, 3, 0U, 1,
                   0U, 2, c10_bv0, c10_uv1, c10_tmp_sizes);
  c10_y_sizes[0] = c10_tmp_sizes[0];
  c10_y_sizes[1] = c10_tmp_sizes[1];
  c10_y = c10_y_sizes[0];
  c10_b_y = c10_y_sizes[1];
  c10_loop_ub = c10_tmp_sizes[0] * c10_tmp_sizes[1] - 1;
  for (c10_i24 = 0; c10_i24 <= c10_loop_ub; c10_i24++) {
    c10_y_data[c10_i24] = c10_tmp_data[c10_i24];
  }

  sf_mex_destroy(&c10_u);
}

static void c10_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, uint8_T c10_outData_data[],
  int32_T c10_outData_sizes[2])
{
  const mxArray *c10_yellowIntensity;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  int32_T c10_y_sizes[2];
  uint8_T c10_y_data[76800];
  int32_T c10_loop_ub;
  int32_T c10_i25;
  int32_T c10_b_loop_ub;
  int32_T c10_i26;
  SFc10_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc10_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c10_yellowIntensity = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_yellowIntensity),
    &c10_thisId, c10_y_data, c10_y_sizes);
  sf_mex_destroy(&c10_yellowIntensity);
  c10_outData_sizes[0] = c10_y_sizes[0];
  c10_outData_sizes[1] = c10_y_sizes[1];
  c10_loop_ub = c10_y_sizes[1] - 1;
  for (c10_i25 = 0; c10_i25 <= c10_loop_ub; c10_i25++) {
    c10_b_loop_ub = c10_y_sizes[0] - 1;
    for (c10_i26 = 0; c10_i26 <= c10_b_loop_ub; c10_i26++) {
      c10_outData_data[c10_i26 + c10_outData_sizes[0] * c10_i25] =
        c10_y_data[c10_i26 + c10_y_sizes[0] * c10_i25];
    }
  }

  sf_mex_destroy(&c10_mxArrayInData);
}

static const mxArray *c10_b_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  int32_T c10_i27;
  int32_T c10_i28;
  int32_T c10_i29;
  uint8_T c10_b_inData[76800];
  int32_T c10_i30;
  int32_T c10_i31;
  int32_T c10_i32;
  uint8_T c10_u[76800];
  const mxArray *c10_y = NULL;
  SFc10_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc10_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  c10_i27 = 0;
  for (c10_i28 = 0; c10_i28 < 240; c10_i28++) {
    for (c10_i29 = 0; c10_i29 < 320; c10_i29++) {
      c10_b_inData[c10_i29 + c10_i27] = (*(uint8_T (*)[76800])c10_inData)
        [c10_i29 + c10_i27];
    }

    c10_i27 += 320;
  }

  c10_i30 = 0;
  for (c10_i31 = 0; c10_i31 < 240; c10_i31++) {
    for (c10_i32 = 0; c10_i32 < 320; c10_i32++) {
      c10_u[c10_i32 + c10_i30] = c10_b_inData[c10_i32 + c10_i30];
    }

    c10_i30 += 320;
  }

  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 3, 0U, 1U, 0U, 2, 320, 240),
                false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static const mxArray *c10_c_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  real_T c10_u;
  const mxArray *c10_y = NULL;
  SFc10_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc10_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  c10_u = *(real_T *)c10_inData;
  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", &c10_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static real_T c10_c_emlrt_marshallIn(SFc10_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId)
{
  real_T c10_y;
  real_T c10_d1;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), &c10_d1, 1, 0, 0U, 0, 0U, 0);
  c10_y = c10_d1;
  sf_mex_destroy(&c10_u);
  return c10_y;
}

static void c10_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_nargout;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  real_T c10_y;
  SFc10_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc10_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c10_nargout = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_y = c10_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_nargout),
    &c10_thisId);
  sf_mex_destroy(&c10_nargout);
  *(real_T *)c10_outData = c10_y;
  sf_mex_destroy(&c10_mxArrayInData);
}

const mxArray *sf_c10_RaspPiPilot_get_eml_resolved_functions_info(void)
{
  const mxArray *c10_nameCaptureInfo = NULL;
  c10_nameCaptureInfo = NULL;
  sf_mex_assign(&c10_nameCaptureInfo, sf_mex_createstruct("structure", 2, 15, 1),
                false);
  c10_info_helper(&c10_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c10_nameCaptureInfo);
  return c10_nameCaptureInfo;
}

static void c10_info_helper(const mxArray **c10_info)
{
  const mxArray *c10_rhs0 = NULL;
  const mxArray *c10_lhs0 = NULL;
  const mxArray *c10_rhs1 = NULL;
  const mxArray *c10_lhs1 = NULL;
  const mxArray *c10_rhs2 = NULL;
  const mxArray *c10_lhs2 = NULL;
  const mxArray *c10_rhs3 = NULL;
  const mxArray *c10_lhs3 = NULL;
  const mxArray *c10_rhs4 = NULL;
  const mxArray *c10_lhs4 = NULL;
  const mxArray *c10_rhs5 = NULL;
  const mxArray *c10_lhs5 = NULL;
  const mxArray *c10_rhs6 = NULL;
  const mxArray *c10_lhs6 = NULL;
  const mxArray *c10_rhs7 = NULL;
  const mxArray *c10_lhs7 = NULL;
  const mxArray *c10_rhs8 = NULL;
  const mxArray *c10_lhs8 = NULL;
  const mxArray *c10_rhs9 = NULL;
  const mxArray *c10_lhs9 = NULL;
  const mxArray *c10_rhs10 = NULL;
  const mxArray *c10_lhs10 = NULL;
  const mxArray *c10_rhs11 = NULL;
  const mxArray *c10_lhs11 = NULL;
  const mxArray *c10_rhs12 = NULL;
  const mxArray *c10_lhs12 = NULL;
  const mxArray *c10_rhs13 = NULL;
  const mxArray *c10_lhs13 = NULL;
  const mxArray *c10_rhs14 = NULL;
  const mxArray *c10_lhs14 = NULL;
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 0);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1383880894U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c10_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 1);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c10_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs1), "lhs", "lhs",
                  1);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 2);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 2);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("uint8"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c10_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs2), "rhs", "rhs",
                  2);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs2), "lhs", "lhs",
                  2);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(""), "context", "context", 3);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("mrdivide"), "name", "name",
                  3);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("uint8"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1388463696U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1370013486U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c10_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs3), "rhs", "rhs",
                  3);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs3), "lhs", "lhs",
                  3);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 4);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 4);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c10_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs4), "rhs", "rhs",
                  4);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs4), "lhs", "lhs",
                  4);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 5);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("rdivide"), "name", "name", 5);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("uint8"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1363717480U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c10_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs5), "rhs", "rhs",
                  5);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs5), "lhs", "lhs",
                  5);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 6);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("uint8"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c10_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs6), "rhs", "rhs",
                  6);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs6), "lhs", "lhs",
                  6);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 7);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c10_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs7), "rhs", "rhs",
                  7);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs7), "lhs", "lhs",
                  7);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 8);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 8);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("uint8"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1286822396U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c10_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs8), "rhs", "rhs",
                  8);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs8), "lhs", "lhs",
                  8);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 9);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("eml_div"), "name", "name", 9);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("uint8"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 9);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1375984288U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c10_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs9), "rhs", "rhs",
                  9);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs9), "lhs", "lhs",
                  9);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 10);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 10);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("uint8"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 10);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c10_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p!eml_mixed_integer_rdivide"),
                  "context", "context", 11);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "coder.internal.is64BitInteger"), "name", "name", 11);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("uint8"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/is64BitInteger.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1368187894U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c10_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p!eml_mixed_integer_rdivide"),
                  "context", "context", 12);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "coder.internal.is64BitInteger"), "name", "name", 12);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/is64BitInteger.m"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1368187894U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c10_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p!eml_mixed_integer_rdivide"),
                  "context", "context", 13);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 13);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("uint8"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 13);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c10_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p!eml_mixed_integer_rdivide"),
                  "context", "context", 14);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 14);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut("uint8"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c10_info, c10_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c10_info, c10_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c10_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c10_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c10_info, sf_mex_duplicatearraysafe(&c10_lhs14), "lhs", "lhs",
                  14);
  sf_mex_destroy(&c10_rhs0);
  sf_mex_destroy(&c10_lhs0);
  sf_mex_destroy(&c10_rhs1);
  sf_mex_destroy(&c10_lhs1);
  sf_mex_destroy(&c10_rhs2);
  sf_mex_destroy(&c10_lhs2);
  sf_mex_destroy(&c10_rhs3);
  sf_mex_destroy(&c10_lhs3);
  sf_mex_destroy(&c10_rhs4);
  sf_mex_destroy(&c10_lhs4);
  sf_mex_destroy(&c10_rhs5);
  sf_mex_destroy(&c10_lhs5);
  sf_mex_destroy(&c10_rhs6);
  sf_mex_destroy(&c10_lhs6);
  sf_mex_destroy(&c10_rhs7);
  sf_mex_destroy(&c10_lhs7);
  sf_mex_destroy(&c10_rhs8);
  sf_mex_destroy(&c10_lhs8);
  sf_mex_destroy(&c10_rhs9);
  sf_mex_destroy(&c10_lhs9);
  sf_mex_destroy(&c10_rhs10);
  sf_mex_destroy(&c10_lhs10);
  sf_mex_destroy(&c10_rhs11);
  sf_mex_destroy(&c10_lhs11);
  sf_mex_destroy(&c10_rhs12);
  sf_mex_destroy(&c10_lhs12);
  sf_mex_destroy(&c10_rhs13);
  sf_mex_destroy(&c10_lhs13);
  sf_mex_destroy(&c10_rhs14);
  sf_mex_destroy(&c10_lhs14);
}

static const mxArray *c10_emlrt_marshallOut(const char * c10_u)
{
  const mxArray *c10_y = NULL;
  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", c10_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c10_u)), false);
  return c10_y;
}

static const mxArray *c10_b_emlrt_marshallOut(const uint32_T c10_u)
{
  const mxArray *c10_y = NULL;
  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", &c10_u, 7, 0U, 0U, 0U, 0), false);
  return c10_y;
}

static const mxArray *c10_d_sf_marshallOut(void *chartInstanceVoid, void
  *c10_inData)
{
  const mxArray *c10_mxArrayOutData = NULL;
  int32_T c10_u;
  const mxArray *c10_y = NULL;
  SFc10_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc10_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c10_mxArrayOutData = NULL;
  c10_u = *(int32_T *)c10_inData;
  c10_y = NULL;
  sf_mex_assign(&c10_y, sf_mex_create("y", &c10_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c10_mxArrayOutData, c10_y, false);
  return c10_mxArrayOutData;
}

static int32_T c10_d_emlrt_marshallIn(SFc10_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId)
{
  int32_T c10_y;
  int32_T c10_i33;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), &c10_i33, 1, 6, 0U, 0, 0U, 0);
  c10_y = c10_i33;
  sf_mex_destroy(&c10_u);
  return c10_y;
}

static void c10_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c10_mxArrayInData, const char_T *c10_varName, void *c10_outData)
{
  const mxArray *c10_b_sfEvent;
  const char_T *c10_identifier;
  emlrtMsgIdentifier c10_thisId;
  int32_T c10_y;
  SFc10_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc10_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c10_b_sfEvent = sf_mex_dup(c10_mxArrayInData);
  c10_identifier = c10_varName;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_y = c10_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c10_b_sfEvent),
    &c10_thisId);
  sf_mex_destroy(&c10_b_sfEvent);
  *(int32_T *)c10_outData = c10_y;
  sf_mex_destroy(&c10_mxArrayInData);
}

static uint8_T c10_e_emlrt_marshallIn(SFc10_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c10_b_is_active_c10_RaspPiPilot, const char_T
  *c10_identifier)
{
  uint8_T c10_y;
  emlrtMsgIdentifier c10_thisId;
  c10_thisId.fIdentifier = c10_identifier;
  c10_thisId.fParent = NULL;
  c10_y = c10_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c10_b_is_active_c10_RaspPiPilot), &c10_thisId);
  sf_mex_destroy(&c10_b_is_active_c10_RaspPiPilot);
  return c10_y;
}

static uint8_T c10_f_emlrt_marshallIn(SFc10_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c10_u, const emlrtMsgIdentifier *c10_parentId)
{
  uint8_T c10_y;
  uint8_T c10_u5;
  (void)chartInstance;
  sf_mex_import(c10_parentId, sf_mex_dup(c10_u), &c10_u5, 1, 3, 0U, 0, 0U, 0);
  c10_y = c10_u5;
  sf_mex_destroy(&c10_u);
  return c10_y;
}

static void init_dsm_address_info(SFc10_RaspPiPilotInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c10_RaspPiPilot_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3008078042U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(872741952U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1531385103U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3708407154U);
}

mxArray *sf_c10_RaspPiPilot_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("9ueuNj0eXsvdIWHFqvlzWC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(320);
      pr[1] = (double)(240);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(320);
      pr[1] = (double)(240);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(320);
      pr[1] = (double)(240);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(320);
      pr[1] = (double)(240);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c10_RaspPiPilot_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c10_RaspPiPilot_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c10_RaspPiPilot(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"yellowIntensity\",},{M[8],M[0],T\"is_active_c10_RaspPiPilot\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c10_RaspPiPilot_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc10_RaspPiPilotInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc10_RaspPiPilotInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _RaspPiPilotMachineNumber_,
           10,
           1,
           1,
           0,
           4,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_RaspPiPilotMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_RaspPiPilotMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _RaspPiPilotMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"R");
          _SFD_SET_DATA_PROPS(1,2,0,1,"yellowIntensity");
          _SFD_SET_DATA_PROPS(2,1,1,0,"G");
          _SFD_SET_DATA_PROPS(3,1,1,0,"B");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,4,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,79);
        _SFD_CV_INIT_EML_SATURATION(0,1,0,66,-1,78);
        _SFD_CV_INIT_EML_SATURATION(0,1,1,68,-1,71);
        _SFD_CV_INIT_EML_SATURATION(0,1,2,68,-1,75);
        _SFD_CV_INIT_EML_SATURATION(0,1,3,72,-1,75);

        {
          unsigned int dimVector[2];
          dimVector[0]= 320;
          dimVector[1]= 240;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 320;
          dimVector[1]= 240;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_sf_marshallOut,(MexInFcnForType)
            c10_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 320;
          dimVector[1]= 240;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 320;
          dimVector[1]= 240;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          int32_T (*c10_yellowIntensity_sizes)[2];
          uint8_T (*c10_R)[76800];
          uint8_T (*c10_yellowIntensity_data)[76800];
          uint8_T (*c10_G)[76800];
          uint8_T (*c10_B)[76800];
          c10_B = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 2);
          c10_G = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 1);
          c10_yellowIntensity_sizes = (int32_T (*)[2])
            ssGetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1);
          c10_yellowIntensity_data = (uint8_T (*)[76800])ssGetOutputPortSignal
            (chartInstance->S, 1);
          c10_R = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c10_R);
          _SFD_SET_DATA_VALUE_PTR_VAR_DIM(1U, *c10_yellowIntensity_data, (void *)
            c10_yellowIntensity_sizes);
          _SFD_SET_DATA_VALUE_PTR(2U, *c10_G);
          _SFD_SET_DATA_VALUE_PTR(3U, *c10_B);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _RaspPiPilotMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "koDbZg1ktls4pOuCLv55aE";
}

static void sf_opaque_initialize_c10_RaspPiPilot(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc10_RaspPiPilotInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c10_RaspPiPilot((SFc10_RaspPiPilotInstanceStruct*)
    chartInstanceVar);
  initialize_c10_RaspPiPilot((SFc10_RaspPiPilotInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c10_RaspPiPilot(void *chartInstanceVar)
{
  enable_c10_RaspPiPilot((SFc10_RaspPiPilotInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c10_RaspPiPilot(void *chartInstanceVar)
{
  disable_c10_RaspPiPilot((SFc10_RaspPiPilotInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c10_RaspPiPilot(void *chartInstanceVar)
{
  sf_gateway_c10_RaspPiPilot((SFc10_RaspPiPilotInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c10_RaspPiPilot(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c10_RaspPiPilot
    ((SFc10_RaspPiPilotInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c10_RaspPiPilot();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c10_RaspPiPilot(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c10_RaspPiPilot();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c10_RaspPiPilot((SFc10_RaspPiPilotInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c10_RaspPiPilot(SimStruct* S)
{
  return sf_internal_get_sim_state_c10_RaspPiPilot(S);
}

static void sf_opaque_set_sim_state_c10_RaspPiPilot(SimStruct* S, const mxArray *
  st)
{
  sf_internal_set_sim_state_c10_RaspPiPilot(S, st);
}

static void sf_opaque_terminate_c10_RaspPiPilot(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc10_RaspPiPilotInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_RaspPiPilot_optimization_info();
    }

    finalize_c10_RaspPiPilot((SFc10_RaspPiPilotInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc10_RaspPiPilot((SFc10_RaspPiPilotInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c10_RaspPiPilot(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c10_RaspPiPilot((SFc10_RaspPiPilotInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c10_RaspPiPilot(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_RaspPiPilot_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      10);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,10,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,10,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,10);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,10,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,10,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,10);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3487526368U));
  ssSetChecksum1(S,(3069466674U));
  ssSetChecksum2(S,(2677778744U));
  ssSetChecksum3(S,(780274244U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c10_RaspPiPilot(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c10_RaspPiPilot(SimStruct *S)
{
  SFc10_RaspPiPilotInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc10_RaspPiPilotInstanceStruct *)utMalloc(sizeof
    (SFc10_RaspPiPilotInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc10_RaspPiPilotInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c10_RaspPiPilot;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c10_RaspPiPilot;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c10_RaspPiPilot;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c10_RaspPiPilot;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c10_RaspPiPilot;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c10_RaspPiPilot;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c10_RaspPiPilot;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c10_RaspPiPilot;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c10_RaspPiPilot;
  chartInstance->chartInfo.mdlStart = mdlStart_c10_RaspPiPilot;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c10_RaspPiPilot;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c10_RaspPiPilot_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c10_RaspPiPilot(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c10_RaspPiPilot(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c10_RaspPiPilot(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c10_RaspPiPilot_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
