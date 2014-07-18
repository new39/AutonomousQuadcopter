/* Include files */

#include <stddef.h>
#include "blas.h"
#include "RaspPiPilot_sfun.h"
#include "c16_RaspPiPilot.h"
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
static const char * c16_debug_family_names[6] = { "nargin", "nargout", "R", "G",
  "B", "greenIntensity" };

/* Function Declarations */
static void initialize_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance);
static void initialize_params_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance);
static void enable_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance);
static void disable_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance);
static void c16_update_debugger_state_c16_RaspPiPilot
  (SFc16_RaspPiPilotInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c16_RaspPiPilot
  (SFc16_RaspPiPilotInstanceStruct *chartInstance);
static void set_sim_state_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c16_st);
static void finalize_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance);
static void sf_gateway_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance);
static void c16_chartstep_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance);
static void initSimStructsc16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c16_machineNumber, uint32_T
  c16_chartNumber, uint32_T c16_instanceNumber);
static const mxArray *c16_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c16_inData_data[], int32_T c16_inData_sizes[2]);
static void c16_emlrt_marshallIn(SFc16_RaspPiPilotInstanceStruct *chartInstance,
  const mxArray *c16_greenIntensity, const char_T *c16_identifier, uint8_T
  c16_y_data[], int32_T c16_y_sizes[2]);
static void c16_b_emlrt_marshallIn(SFc16_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId,
  uint8_T c16_y_data[], int32_T c16_y_sizes[2]);
static void c16_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, uint8_T c16_outData_data[],
  int32_T c16_outData_sizes[2]);
static const mxArray *c16_b_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData);
static const mxArray *c16_c_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData);
static real_T c16_c_emlrt_marshallIn(SFc16_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId);
static void c16_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData);
static const mxArray *c16_d_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData);
static int32_T c16_d_emlrt_marshallIn(SFc16_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId);
static void c16_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData);
static uint8_T c16_e_emlrt_marshallIn(SFc16_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c16_b_is_active_c16_RaspPiPilot, const char_T
  *c16_identifier);
static uint8_T c16_f_emlrt_marshallIn(SFc16_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId);
static void init_dsm_address_info(SFc16_RaspPiPilotInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance)
{
  chartInstance->c16_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c16_is_active_c16_RaspPiPilot = 0U;
}

static void initialize_params_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c16_update_debugger_state_c16_RaspPiPilot
  (SFc16_RaspPiPilotInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c16_RaspPiPilot
  (SFc16_RaspPiPilotInstanceStruct *chartInstance)
{
  const mxArray *c16_st;
  const mxArray *c16_y = NULL;
  int32_T c16_u_sizes[2];
  int32_T c16_u;
  int32_T c16_b_u;
  int32_T c16_loop_ub;
  int32_T c16_i0;
  uint8_T c16_u_data[76800];
  const mxArray *c16_b_y = NULL;
  uint8_T c16_hoistedGlobal;
  uint8_T c16_c_u;
  const mxArray *c16_c_y = NULL;
  int32_T (*c16_greenIntensity_sizes)[2];
  uint8_T (*c16_greenIntensity_data)[76800];
  c16_greenIntensity_sizes = (int32_T (*)[2])
    ssGetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1);
  c16_greenIntensity_data = (uint8_T (*)[76800])ssGetOutputPortSignal
    (chartInstance->S, 1);
  c16_st = NULL;
  c16_st = NULL;
  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_createcellmatrix(2, 1), false);
  c16_u_sizes[0] = (*c16_greenIntensity_sizes)[0];
  c16_u_sizes[1] = (*c16_greenIntensity_sizes)[1];
  c16_u = c16_u_sizes[0];
  c16_b_u = c16_u_sizes[1];
  c16_loop_ub = (*c16_greenIntensity_sizes)[0] * (*c16_greenIntensity_sizes)[1]
    - 1;
  for (c16_i0 = 0; c16_i0 <= c16_loop_ub; c16_i0++) {
    c16_u_data[c16_i0] = (*c16_greenIntensity_data)[c16_i0];
  }

  c16_b_y = NULL;
  sf_mex_assign(&c16_b_y, sf_mex_create("y", c16_u_data, 3, 0U, 1U, 0U, 2,
    c16_u_sizes[0], c16_u_sizes[1]), false);
  sf_mex_setcell(c16_y, 0, c16_b_y);
  c16_hoistedGlobal = chartInstance->c16_is_active_c16_RaspPiPilot;
  c16_c_u = c16_hoistedGlobal;
  c16_c_y = NULL;
  sf_mex_assign(&c16_c_y, sf_mex_create("y", &c16_c_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c16_y, 1, c16_c_y);
  sf_mex_assign(&c16_st, c16_y, false);
  return c16_st;
}

static void set_sim_state_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c16_st)
{
  const mxArray *c16_u;
  int32_T c16_tmp_sizes[2];
  uint8_T c16_tmp_data[76800];
  int32_T c16_i1;
  int32_T c16_i2;
  int32_T c16_loop_ub;
  int32_T c16_i3;
  uint8_T (*c16_greenIntensity_data)[76800];
  int32_T (*c16_greenIntensity_sizes)[2];
  c16_greenIntensity_sizes = (int32_T (*)[2])
    ssGetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1);
  c16_greenIntensity_data = (uint8_T (*)[76800])ssGetOutputPortSignal
    (chartInstance->S, 1);
  chartInstance->c16_doneDoubleBufferReInit = true;
  c16_u = sf_mex_dup(c16_st);
  c16_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c16_u, 0)),
                       "greenIntensity", c16_tmp_data, c16_tmp_sizes);
  ssSetCurrentOutputPortDimensions(chartInstance->S, 1, 0, c16_tmp_sizes[0]);
  ssSetCurrentOutputPortDimensions(chartInstance->S, 1, 1, c16_tmp_sizes[1]);
  c16_i1 = (*c16_greenIntensity_sizes)[0];
  c16_i2 = (*c16_greenIntensity_sizes)[1];
  c16_loop_ub = c16_tmp_sizes[0] * c16_tmp_sizes[1] - 1;
  for (c16_i3 = 0; c16_i3 <= c16_loop_ub; c16_i3++) {
    (*c16_greenIntensity_data)[c16_i3] = c16_tmp_data[c16_i3];
  }

  chartInstance->c16_is_active_c16_RaspPiPilot = c16_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c16_u, 1)),
     "is_active_c16_RaspPiPilot");
  sf_mex_destroy(&c16_u);
  c16_update_debugger_state_c16_RaspPiPilot(chartInstance);
  sf_mex_destroy(&c16_st);
}

static void finalize_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance)
{
  int32_T c16_i4;
  int32_T c16_loop_ub;
  int32_T c16_i5;
  int32_T c16_i6;
  int32_T c16_i7;
  int32_T (*c16_greenIntensity_sizes)[2];
  uint8_T (*c16_B)[76800];
  uint8_T (*c16_G)[76800];
  uint8_T (*c16_greenIntensity_data)[76800];
  uint8_T (*c16_R)[76800];
  c16_B = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 2);
  c16_G = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 1);
  c16_greenIntensity_sizes = (int32_T (*)[2])
    ssGetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1);
  c16_greenIntensity_data = (uint8_T (*)[76800])ssGetOutputPortSignal
    (chartInstance->S, 1);
  c16_R = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 15U, chartInstance->c16_sfEvent);
  for (c16_i4 = 0; c16_i4 < 76800; c16_i4++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c16_R)[c16_i4], 0U);
  }

  chartInstance->c16_sfEvent = CALL_EVENT;
  c16_chartstep_c16_RaspPiPilot(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_RaspPiPilotMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  c16_loop_ub = (*c16_greenIntensity_sizes)[0] * (*c16_greenIntensity_sizes)[1]
    - 1;
  for (c16_i5 = 0; c16_i5 <= c16_loop_ub; c16_i5++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c16_greenIntensity_data)[c16_i5], 1U);
  }

  for (c16_i6 = 0; c16_i6 < 76800; c16_i6++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c16_G)[c16_i6], 2U);
  }

  for (c16_i7 = 0; c16_i7 < 76800; c16_i7++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c16_B)[c16_i7], 3U);
  }
}

static void c16_chartstep_c16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance)
{
  int32_T c16_i8;
  static uint8_T c16_R[76800];
  int32_T c16_i9;
  static uint8_T c16_G[76800];
  int32_T c16_i10;
  static uint8_T c16_B[76800];
  uint32_T c16_debug_family_var_map[6];
  real_T c16_nargin = 3.0;
  real_T c16_nargout = 1.0;
  int32_T c16_greenIntensity_sizes[2];
  uint8_T c16_greenIntensity_data[76800];
  int32_T c16_i11;
  uint32_T c16_q0;
  uint32_T c16_qY;
  uint32_T c16_u0;
  uint8_T c16_b_G[76800];
  int32_T c16_greenIntensity;
  int32_T c16_b_greenIntensity;
  int32_T c16_i12;
  int32_T c16_i13;
  int32_T c16_i14;
  int32_T c16_loop_ub;
  int32_T c16_i15;
  uint8_T (*c16_b_greenIntensity_data)[76800];
  int32_T (*c16_b_greenIntensity_sizes)[2];
  uint8_T (*c16_b_B)[76800];
  uint8_T (*c16_c_G)[76800];
  uint8_T (*c16_b_R)[76800];
  c16_b_B = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 2);
  c16_c_G = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 1);
  c16_b_greenIntensity_sizes = (int32_T (*)[2])
    ssGetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1);
  c16_b_greenIntensity_data = (uint8_T (*)[76800])ssGetOutputPortSignal
    (chartInstance->S, 1);
  c16_b_R = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 15U, chartInstance->c16_sfEvent);
  for (c16_i8 = 0; c16_i8 < 76800; c16_i8++) {
    c16_R[c16_i8] = (*c16_b_R)[c16_i8];
  }

  for (c16_i9 = 0; c16_i9 < 76800; c16_i9++) {
    c16_G[c16_i9] = (*c16_c_G)[c16_i9];
  }

  for (c16_i10 = 0; c16_i10 < 76800; c16_i10++) {
    c16_B[c16_i10] = (*c16_b_B)[c16_i10];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 6U, c16_debug_family_names,
    c16_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_nargin, 0U, c16_c_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_nargout, 1U, c16_c_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c16_R, 2U, c16_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c16_G, 3U, c16_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c16_B, 4U, c16_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c16_greenIntensity_data, (const
    int32_T *)&c16_greenIntensity_sizes, NULL, 0, 5, (void *)c16_sf_marshallOut,
    (void *)c16_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 3);
  for (c16_i11 = 0; c16_i11 < 76800; c16_i11++) {
    c16_q0 = c16_G[c16_i11];
    c16_qY = c16_q0 - (uint32_T)c16_B[c16_i11];
    if (CV_SATURATION_EVAL(4, 0, 0, 0, c16_qY > c16_q0)) {
      c16_qY = 0U;
    }

    c16_u0 = c16_qY;
    if (CV_SATURATION_EVAL(4, 0, 0, 0, c16_u0 > 255U)) {
      c16_u0 = 255U;
    }

    c16_b_G[c16_i11] = (uint8_T)c16_u0;
  }

  c16_greenIntensity_sizes[0] = 320;
  c16_greenIntensity_sizes[1] = 240;
  c16_greenIntensity = c16_greenIntensity_sizes[0];
  c16_b_greenIntensity = c16_greenIntensity_sizes[1];
  for (c16_i12 = 0; c16_i12 < 76800; c16_i12++) {
    c16_greenIntensity_data[c16_i12] = c16_b_G[c16_i12];
  }

  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, -3);
  _SFD_SYMBOL_SCOPE_POP();
  ssSetCurrentOutputPortDimensions(chartInstance->S, 1, 0,
    c16_greenIntensity_sizes[0]);
  ssSetCurrentOutputPortDimensions(chartInstance->S, 1, 1,
    c16_greenIntensity_sizes[1]);
  c16_i13 = (*c16_b_greenIntensity_sizes)[0];
  c16_i14 = (*c16_b_greenIntensity_sizes)[1];
  c16_loop_ub = c16_greenIntensity_sizes[0] * c16_greenIntensity_sizes[1] - 1;
  for (c16_i15 = 0; c16_i15 <= c16_loop_ub; c16_i15++) {
    (*c16_b_greenIntensity_data)[c16_i15] = c16_greenIntensity_data[c16_i15];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U, chartInstance->c16_sfEvent);
}

static void initSimStructsc16_RaspPiPilot(SFc16_RaspPiPilotInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c16_machineNumber, uint32_T
  c16_chartNumber, uint32_T c16_instanceNumber)
{
  (void)c16_machineNumber;
  (void)c16_chartNumber;
  (void)c16_instanceNumber;
}

static const mxArray *c16_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c16_inData_data[], int32_T c16_inData_sizes[2])
{
  const mxArray *c16_mxArrayOutData = NULL;
  int32_T c16_b_inData_sizes[2];
  int32_T c16_loop_ub;
  int32_T c16_i16;
  int32_T c16_b_loop_ub;
  int32_T c16_i17;
  uint8_T c16_b_inData_data[76800];
  int32_T c16_u_sizes[2];
  int32_T c16_c_loop_ub;
  int32_T c16_i18;
  int32_T c16_d_loop_ub;
  int32_T c16_i19;
  uint8_T c16_u_data[76800];
  const mxArray *c16_y = NULL;
  SFc16_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc16_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c16_mxArrayOutData = NULL;
  c16_b_inData_sizes[0] = c16_inData_sizes[0];
  c16_b_inData_sizes[1] = c16_inData_sizes[1];
  c16_loop_ub = c16_inData_sizes[1] - 1;
  for (c16_i16 = 0; c16_i16 <= c16_loop_ub; c16_i16++) {
    c16_b_loop_ub = c16_inData_sizes[0] - 1;
    for (c16_i17 = 0; c16_i17 <= c16_b_loop_ub; c16_i17++) {
      c16_b_inData_data[c16_i17 + c16_b_inData_sizes[0] * c16_i16] =
        c16_inData_data[c16_i17 + c16_inData_sizes[0] * c16_i16];
    }
  }

  c16_u_sizes[0] = c16_b_inData_sizes[0];
  c16_u_sizes[1] = c16_b_inData_sizes[1];
  c16_c_loop_ub = c16_b_inData_sizes[1] - 1;
  for (c16_i18 = 0; c16_i18 <= c16_c_loop_ub; c16_i18++) {
    c16_d_loop_ub = c16_b_inData_sizes[0] - 1;
    for (c16_i19 = 0; c16_i19 <= c16_d_loop_ub; c16_i19++) {
      c16_u_data[c16_i19 + c16_u_sizes[0] * c16_i18] = c16_b_inData_data[c16_i19
        + c16_b_inData_sizes[0] * c16_i18];
    }
  }

  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_create("y", c16_u_data, 3, 0U, 1U, 0U, 2,
    c16_u_sizes[0], c16_u_sizes[1]), false);
  sf_mex_assign(&c16_mxArrayOutData, c16_y, false);
  return c16_mxArrayOutData;
}

static void c16_emlrt_marshallIn(SFc16_RaspPiPilotInstanceStruct *chartInstance,
  const mxArray *c16_greenIntensity, const char_T *c16_identifier, uint8_T
  c16_y_data[], int32_T c16_y_sizes[2])
{
  emlrtMsgIdentifier c16_thisId;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c16_greenIntensity),
    &c16_thisId, c16_y_data, c16_y_sizes);
  sf_mex_destroy(&c16_greenIntensity);
}

static void c16_b_emlrt_marshallIn(SFc16_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId,
  uint8_T c16_y_data[], int32_T c16_y_sizes[2])
{
  int32_T c16_i20;
  uint32_T c16_uv0[2];
  int32_T c16_i21;
  boolean_T c16_bv0[2];
  int32_T c16_tmp_sizes[2];
  uint8_T c16_tmp_data[76800];
  int32_T c16_y;
  int32_T c16_b_y;
  int32_T c16_loop_ub;
  int32_T c16_i22;
  (void)chartInstance;
  for (c16_i20 = 0; c16_i20 < 2; c16_i20++) {
    c16_uv0[c16_i20] = 320U + (uint32_T)(-80 * (int32_T)(uint32_T)c16_i20);
  }

  for (c16_i21 = 0; c16_i21 < 2; c16_i21++) {
    c16_bv0[c16_i21] = true;
  }

  sf_mex_import_vs(c16_parentId, sf_mex_dup(c16_u), c16_tmp_data, 1, 3, 0U, 1,
                   0U, 2, c16_bv0, c16_uv0, c16_tmp_sizes);
  c16_y_sizes[0] = c16_tmp_sizes[0];
  c16_y_sizes[1] = c16_tmp_sizes[1];
  c16_y = c16_y_sizes[0];
  c16_b_y = c16_y_sizes[1];
  c16_loop_ub = c16_tmp_sizes[0] * c16_tmp_sizes[1] - 1;
  for (c16_i22 = 0; c16_i22 <= c16_loop_ub; c16_i22++) {
    c16_y_data[c16_i22] = c16_tmp_data[c16_i22];
  }

  sf_mex_destroy(&c16_u);
}

static void c16_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, uint8_T c16_outData_data[],
  int32_T c16_outData_sizes[2])
{
  const mxArray *c16_greenIntensity;
  const char_T *c16_identifier;
  emlrtMsgIdentifier c16_thisId;
  int32_T c16_y_sizes[2];
  uint8_T c16_y_data[76800];
  int32_T c16_loop_ub;
  int32_T c16_i23;
  int32_T c16_b_loop_ub;
  int32_T c16_i24;
  SFc16_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc16_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c16_greenIntensity = sf_mex_dup(c16_mxArrayInData);
  c16_identifier = c16_varName;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c16_greenIntensity),
    &c16_thisId, c16_y_data, c16_y_sizes);
  sf_mex_destroy(&c16_greenIntensity);
  c16_outData_sizes[0] = c16_y_sizes[0];
  c16_outData_sizes[1] = c16_y_sizes[1];
  c16_loop_ub = c16_y_sizes[1] - 1;
  for (c16_i23 = 0; c16_i23 <= c16_loop_ub; c16_i23++) {
    c16_b_loop_ub = c16_y_sizes[0] - 1;
    for (c16_i24 = 0; c16_i24 <= c16_b_loop_ub; c16_i24++) {
      c16_outData_data[c16_i24 + c16_outData_sizes[0] * c16_i23] =
        c16_y_data[c16_i24 + c16_y_sizes[0] * c16_i23];
    }
  }

  sf_mex_destroy(&c16_mxArrayInData);
}

static const mxArray *c16_b_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData)
{
  const mxArray *c16_mxArrayOutData = NULL;
  int32_T c16_i25;
  int32_T c16_i26;
  int32_T c16_i27;
  uint8_T c16_b_inData[76800];
  int32_T c16_i28;
  int32_T c16_i29;
  int32_T c16_i30;
  uint8_T c16_u[76800];
  const mxArray *c16_y = NULL;
  SFc16_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc16_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c16_mxArrayOutData = NULL;
  c16_i25 = 0;
  for (c16_i26 = 0; c16_i26 < 240; c16_i26++) {
    for (c16_i27 = 0; c16_i27 < 320; c16_i27++) {
      c16_b_inData[c16_i27 + c16_i25] = (*(uint8_T (*)[76800])c16_inData)
        [c16_i27 + c16_i25];
    }

    c16_i25 += 320;
  }

  c16_i28 = 0;
  for (c16_i29 = 0; c16_i29 < 240; c16_i29++) {
    for (c16_i30 = 0; c16_i30 < 320; c16_i30++) {
      c16_u[c16_i30 + c16_i28] = c16_b_inData[c16_i30 + c16_i28];
    }

    c16_i28 += 320;
  }

  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_create("y", c16_u, 3, 0U, 1U, 0U, 2, 320, 240),
                false);
  sf_mex_assign(&c16_mxArrayOutData, c16_y, false);
  return c16_mxArrayOutData;
}

static const mxArray *c16_c_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData)
{
  const mxArray *c16_mxArrayOutData = NULL;
  real_T c16_u;
  const mxArray *c16_y = NULL;
  SFc16_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc16_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c16_mxArrayOutData = NULL;
  c16_u = *(real_T *)c16_inData;
  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_create("y", &c16_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c16_mxArrayOutData, c16_y, false);
  return c16_mxArrayOutData;
}

static real_T c16_c_emlrt_marshallIn(SFc16_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId)
{
  real_T c16_y;
  real_T c16_d0;
  (void)chartInstance;
  sf_mex_import(c16_parentId, sf_mex_dup(c16_u), &c16_d0, 1, 0, 0U, 0, 0U, 0);
  c16_y = c16_d0;
  sf_mex_destroy(&c16_u);
  return c16_y;
}

static void c16_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData)
{
  const mxArray *c16_nargout;
  const char_T *c16_identifier;
  emlrtMsgIdentifier c16_thisId;
  real_T c16_y;
  SFc16_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc16_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c16_nargout = sf_mex_dup(c16_mxArrayInData);
  c16_identifier = c16_varName;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_y = c16_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c16_nargout),
    &c16_thisId);
  sf_mex_destroy(&c16_nargout);
  *(real_T *)c16_outData = c16_y;
  sf_mex_destroy(&c16_mxArrayInData);
}

const mxArray *sf_c16_RaspPiPilot_get_eml_resolved_functions_info(void)
{
  const mxArray *c16_nameCaptureInfo = NULL;
  c16_nameCaptureInfo = NULL;
  sf_mex_assign(&c16_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c16_nameCaptureInfo;
}

static const mxArray *c16_d_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData)
{
  const mxArray *c16_mxArrayOutData = NULL;
  int32_T c16_u;
  const mxArray *c16_y = NULL;
  SFc16_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc16_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c16_mxArrayOutData = NULL;
  c16_u = *(int32_T *)c16_inData;
  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_create("y", &c16_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c16_mxArrayOutData, c16_y, false);
  return c16_mxArrayOutData;
}

static int32_T c16_d_emlrt_marshallIn(SFc16_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId)
{
  int32_T c16_y;
  int32_T c16_i31;
  (void)chartInstance;
  sf_mex_import(c16_parentId, sf_mex_dup(c16_u), &c16_i31, 1, 6, 0U, 0, 0U, 0);
  c16_y = c16_i31;
  sf_mex_destroy(&c16_u);
  return c16_y;
}

static void c16_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData)
{
  const mxArray *c16_b_sfEvent;
  const char_T *c16_identifier;
  emlrtMsgIdentifier c16_thisId;
  int32_T c16_y;
  SFc16_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc16_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c16_b_sfEvent = sf_mex_dup(c16_mxArrayInData);
  c16_identifier = c16_varName;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_y = c16_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c16_b_sfEvent),
    &c16_thisId);
  sf_mex_destroy(&c16_b_sfEvent);
  *(int32_T *)c16_outData = c16_y;
  sf_mex_destroy(&c16_mxArrayInData);
}

static uint8_T c16_e_emlrt_marshallIn(SFc16_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c16_b_is_active_c16_RaspPiPilot, const char_T
  *c16_identifier)
{
  uint8_T c16_y;
  emlrtMsgIdentifier c16_thisId;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_y = c16_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c16_b_is_active_c16_RaspPiPilot), &c16_thisId);
  sf_mex_destroy(&c16_b_is_active_c16_RaspPiPilot);
  return c16_y;
}

static uint8_T c16_f_emlrt_marshallIn(SFc16_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId)
{
  uint8_T c16_y;
  uint8_T c16_u1;
  (void)chartInstance;
  sf_mex_import(c16_parentId, sf_mex_dup(c16_u), &c16_u1, 1, 3, 0U, 0, 0U, 0);
  c16_y = c16_u1;
  sf_mex_destroy(&c16_u);
  return c16_y;
}

static void init_dsm_address_info(SFc16_RaspPiPilotInstanceStruct *chartInstance)
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

void sf_c16_RaspPiPilot_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3356361433U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2659833689U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2621720185U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3074626605U);
}

mxArray *sf_c16_RaspPiPilot_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("sWjI0FVpyYISU3bV5y0fEH");
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

mxArray *sf_c16_RaspPiPilot_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c16_RaspPiPilot_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c16_RaspPiPilot(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"greenIntensity\",},{M[8],M[0],T\"is_active_c16_RaspPiPilot\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c16_RaspPiPilot_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc16_RaspPiPilotInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc16_RaspPiPilotInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _RaspPiPilotMachineNumber_,
           16,
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
          _SFD_SET_DATA_PROPS(1,2,0,1,"greenIntensity");
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
        _SFD_CV_INIT_EML(0,1,1,0,0,1,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,68);
        _SFD_CV_INIT_EML_SATURATION(0,1,0,64,-1,67);

        {
          unsigned int dimVector[2];
          dimVector[0]= 320;
          dimVector[1]= 240;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c16_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 320;
          dimVector[1]= 240;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c16_sf_marshallOut,(MexInFcnForType)
            c16_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 320;
          dimVector[1]= 240;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c16_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 320;
          dimVector[1]= 240;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c16_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          int32_T (*c16_greenIntensity_sizes)[2];
          uint8_T (*c16_R)[76800];
          uint8_T (*c16_greenIntensity_data)[76800];
          uint8_T (*c16_G)[76800];
          uint8_T (*c16_B)[76800];
          c16_B = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 2);
          c16_G = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 1);
          c16_greenIntensity_sizes = (int32_T (*)[2])
            ssGetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1);
          c16_greenIntensity_data = (uint8_T (*)[76800])ssGetOutputPortSignal
            (chartInstance->S, 1);
          c16_R = (uint8_T (*)[76800])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c16_R);
          _SFD_SET_DATA_VALUE_PTR_VAR_DIM(1U, *c16_greenIntensity_data, (void *)
            c16_greenIntensity_sizes);
          _SFD_SET_DATA_VALUE_PTR(2U, *c16_G);
          _SFD_SET_DATA_VALUE_PTR(3U, *c16_B);
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
  return "UO1sXsSAndDSeCVw44H2tB";
}

static void sf_opaque_initialize_c16_RaspPiPilot(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc16_RaspPiPilotInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c16_RaspPiPilot((SFc16_RaspPiPilotInstanceStruct*)
    chartInstanceVar);
  initialize_c16_RaspPiPilot((SFc16_RaspPiPilotInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c16_RaspPiPilot(void *chartInstanceVar)
{
  enable_c16_RaspPiPilot((SFc16_RaspPiPilotInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c16_RaspPiPilot(void *chartInstanceVar)
{
  disable_c16_RaspPiPilot((SFc16_RaspPiPilotInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c16_RaspPiPilot(void *chartInstanceVar)
{
  sf_gateway_c16_RaspPiPilot((SFc16_RaspPiPilotInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c16_RaspPiPilot(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c16_RaspPiPilot
    ((SFc16_RaspPiPilotInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c16_RaspPiPilot();/* state var info */
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

extern void sf_internal_set_sim_state_c16_RaspPiPilot(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c16_RaspPiPilot();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c16_RaspPiPilot((SFc16_RaspPiPilotInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c16_RaspPiPilot(SimStruct* S)
{
  return sf_internal_get_sim_state_c16_RaspPiPilot(S);
}

static void sf_opaque_set_sim_state_c16_RaspPiPilot(SimStruct* S, const mxArray *
  st)
{
  sf_internal_set_sim_state_c16_RaspPiPilot(S, st);
}

static void sf_opaque_terminate_c16_RaspPiPilot(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc16_RaspPiPilotInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_RaspPiPilot_optimization_info();
    }

    finalize_c16_RaspPiPilot((SFc16_RaspPiPilotInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc16_RaspPiPilot((SFc16_RaspPiPilotInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c16_RaspPiPilot(SimStruct *S)
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
    initialize_params_c16_RaspPiPilot((SFc16_RaspPiPilotInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c16_RaspPiPilot(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_RaspPiPilot_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      16);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,16,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,16,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,16);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,16,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,16,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,16);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3810918882U));
  ssSetChecksum1(S,(2756186117U));
  ssSetChecksum2(S,(1066845931U));
  ssSetChecksum3(S,(3788726000U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c16_RaspPiPilot(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c16_RaspPiPilot(SimStruct *S)
{
  SFc16_RaspPiPilotInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc16_RaspPiPilotInstanceStruct *)utMalloc(sizeof
    (SFc16_RaspPiPilotInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc16_RaspPiPilotInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c16_RaspPiPilot;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c16_RaspPiPilot;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c16_RaspPiPilot;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c16_RaspPiPilot;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c16_RaspPiPilot;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c16_RaspPiPilot;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c16_RaspPiPilot;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c16_RaspPiPilot;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c16_RaspPiPilot;
  chartInstance->chartInfo.mdlStart = mdlStart_c16_RaspPiPilot;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c16_RaspPiPilot;
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

void c16_RaspPiPilot_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c16_RaspPiPilot(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c16_RaspPiPilot(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c16_RaspPiPilot(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c16_RaspPiPilot_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}