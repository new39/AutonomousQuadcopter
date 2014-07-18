/* Include files */

#include <stddef.h>
#include "blas.h"
#include "RaspPiPilot_sfun.h"
#include "c5_RaspPiPilot.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "RaspPiPilot_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c5_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c5_IN_Armed                    ((uint8_T)1U)
#define c5_IN_Disarmed                 ((uint8_T)2U)
#define c5_IN_Initializing             ((uint8_T)3U)
#define c5_IN_Flying                   ((uint8_T)1U)
#define c5_IN_sendArm                  ((uint8_T)2U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c5_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_b_debug_family_names[5] = { "length", "data2", "nargin",
  "nargout", "data" };

static const char * c5_c_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_d_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_e_debug_family_names[5] = { "length", "data2", "nargin",
  "nargout", "data" };

static const char * c5_f_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_g_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_h_debug_family_names[5] = { "length", "data2", "nargin",
  "nargout", "data" };

static const char * c5_i_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_j_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_k_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_l_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_m_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_n_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_o_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_p_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static boolean_T c5_dataWrittenToVector[9];

/* Function Declarations */
static void initialize_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance);
static void initialize_params_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance);
static void enable_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct *chartInstance);
static void disable_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct *chartInstance);
static void c5_update_debugger_state_c5_RaspPiPilot
  (SFc5_RaspPiPilotInstanceStruct *chartInstance);
static void ext_mode_exec_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c5_RaspPiPilot
  (SFc5_RaspPiPilotInstanceStruct *chartInstance);
static void set_sim_state_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_st);
static void c5_set_sim_state_side_effects_c5_RaspPiPilot
  (SFc5_RaspPiPilotInstanceStruct *chartInstance);
static void finalize_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance);
static void sf_gateway_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance);
static void c5_chartstep_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance);
static void initSimStructsc5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance);
static void c5_eml_scalar_eg(SFc5_RaspPiPilotInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData);
static real_T c5_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct *chartInstance,
  const mxArray *c5_nargout, const char_T *c5_identifier);
static real_T c5_b_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_c_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct *chartInstance,
  const mxArray *c5_data, const char_T *c5_identifier, uint8_T c5_y[256]);
static void c5_d_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, uint8_T c5_y[256]);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static uint8_T c5_e_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_length, const char_T *c5_identifier);
static uint8_T c5_f_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static boolean_T c5_g_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static void c5_info_helper(const mxArray **c5_info);
static const mxArray *c5_emlrt_marshallOut(const char * c5_u);
static const mxArray *c5_b_emlrt_marshallOut(const uint32_T c5_u);
static void c5_requestStreams(SFc5_RaspPiPilotInstanceStruct *chartInstance,
  uint8_T c5_data[256]);
static void c5_sendArmDisarmFun(SFc5_RaspPiPilotInstanceStruct *chartInstance,
  uint8_T c5_data[256]);
static void c5_sendRPYT(SFc5_RaspPiPilotInstanceStruct *chartInstance, uint8_T
  c5_data[256]);
static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static int32_T c5_h_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_f_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static uint32_T c5_i_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_temporalCounter_i1, const char_T
  *c5_identifier);
static uint32_T c5_j_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static const mxArray *c5_k_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_b_setSimStateSideEffectsInfo, const char_T
  *c5_identifier);
static const mxArray *c5_l_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_updateDataWrittenToVector(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, uint32_T c5_vectorIndex);
static void init_dsm_address_info(SFc5_RaspPiPilotInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance)
{
  int32_T *c5_sfEvent;
  uint8_T *c5_is_Armed;
  uint8_T *c5_is_active_c5_RaspPiPilot;
  uint8_T *c5_is_c5_RaspPiPilot;
  uint32_T *c5_temporalCounter_i1;
  c5_temporalCounter_i1 = (uint32_T *)ssGetDWork(chartInstance->S, 5);
  c5_is_Armed = (uint8_T *)ssGetDWork(chartInstance->S, 4);
  c5_is_c5_RaspPiPilot = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c5_is_active_c5_RaspPiPilot = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c5_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  *c5_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c5_doSetSimStateSideEffects = 0U;
  chartInstance->c5_setSimStateSideEffectsInfo = NULL;
  *c5_is_Armed = c5_IN_NO_ACTIVE_CHILD;
  *c5_temporalCounter_i1 = 0U;
  *c5_temporalCounter_i1 = 0U;
  *c5_is_active_c5_RaspPiPilot = 0U;
  *c5_is_c5_RaspPiPilot = c5_IN_NO_ACTIVE_CHILD;
}

static void initialize_params_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
  sf_call_output_fcn_enable(chartInstance->S, 0, "sendme", 0);
}

static void disable_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
  sf_call_output_fcn_disable(chartInstance->S, 0, "sendme", 0);
}

static void c5_update_debugger_state_c5_RaspPiPilot
  (SFc5_RaspPiPilotInstanceStruct *chartInstance)
{
  uint32_T c5_prevAniVal;
  uint8_T *c5_is_active_c5_RaspPiPilot;
  uint8_T *c5_is_c5_RaspPiPilot;
  uint8_T *c5_is_Armed;
  int32_T *c5_sfEvent;
  c5_is_Armed = (uint8_T *)ssGetDWork(chartInstance->S, 4);
  c5_is_c5_RaspPiPilot = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c5_is_active_c5_RaspPiPilot = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c5_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  c5_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (*c5_is_active_c5_RaspPiPilot == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 4U, *c5_sfEvent);
  }

  if (*c5_is_c5_RaspPiPilot == c5_IN_Initializing) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, *c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, *c5_sfEvent);
  }

  if (*c5_is_c5_RaspPiPilot == c5_IN_Disarmed) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *c5_sfEvent);
  }

  if (*c5_is_Armed == c5_IN_sendArm) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *c5_sfEvent);
  }

  if (*c5_is_Armed == c5_IN_Flying) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *c5_sfEvent);
  }

  if (*c5_is_c5_RaspPiPilot == c5_IN_Armed) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *c5_sfEvent);
  }

  _SFD_SET_ANIMATION(c5_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static void ext_mode_exec_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance)
{
  c5_update_debugger_state_c5_RaspPiPilot(chartInstance);
}

static const mxArray *get_sim_state_c5_RaspPiPilot
  (SFc5_RaspPiPilotInstanceStruct *chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  int32_T c5_i0;
  uint8_T c5_u[256];
  const mxArray *c5_b_y = NULL;
  uint8_T c5_hoistedGlobal;
  uint8_T c5_b_u;
  const mxArray *c5_c_y = NULL;
  real_T c5_b_hoistedGlobal;
  real_T c5_c_u;
  const mxArray *c5_d_y = NULL;
  uint8_T c5_c_hoistedGlobal;
  uint8_T c5_d_u;
  const mxArray *c5_e_y = NULL;
  uint8_T c5_d_hoistedGlobal;
  uint8_T c5_e_u;
  const mxArray *c5_f_y = NULL;
  uint8_T c5_e_hoistedGlobal;
  uint8_T c5_f_u;
  const mxArray *c5_g_y = NULL;
  uint32_T c5_f_hoistedGlobal;
  uint32_T c5_g_u;
  const mxArray *c5_h_y = NULL;
  uint8_T *c5_lengthOut;
  real_T *c5_navOn;
  uint8_T *c5_is_active_c5_RaspPiPilot;
  uint8_T *c5_is_c5_RaspPiPilot;
  uint8_T *c5_is_Armed;
  uint32_T *c5_temporalCounter_i1;
  uint8_T (*c5_dataOut)[256];
  c5_temporalCounter_i1 = (uint32_T *)ssGetDWork(chartInstance->S, 5);
  c5_navOn = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c5_lengthOut = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c5_dataOut = (uint8_T (*)[256])ssGetOutputPortSignal(chartInstance->S, 1);
  c5_is_Armed = (uint8_T *)ssGetDWork(chartInstance->S, 4);
  c5_is_c5_RaspPiPilot = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c5_is_active_c5_RaspPiPilot = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellmatrix(7, 1), false);
  for (c5_i0 = 0; c5_i0 < 256; c5_i0++) {
    c5_u[c5_i0] = (*c5_dataOut)[c5_i0];
  }

  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_u, 3, 0U, 1U, 0U, 1, 256), false);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_hoistedGlobal = *c5_lengthOut;
  c5_b_u = c5_hoistedGlobal;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 1, c5_c_y);
  c5_b_hoistedGlobal = *c5_navOn;
  c5_c_u = c5_b_hoistedGlobal;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 2, c5_d_y);
  c5_c_hoistedGlobal = *c5_is_active_c5_RaspPiPilot;
  c5_d_u = c5_c_hoistedGlobal;
  c5_e_y = NULL;
  sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 3, c5_e_y);
  c5_d_hoistedGlobal = *c5_is_c5_RaspPiPilot;
  c5_e_u = c5_d_hoistedGlobal;
  c5_f_y = NULL;
  sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 4, c5_f_y);
  c5_e_hoistedGlobal = *c5_is_Armed;
  c5_f_u = c5_e_hoistedGlobal;
  c5_g_y = NULL;
  sf_mex_assign(&c5_g_y, sf_mex_create("y", &c5_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 5, c5_g_y);
  c5_f_hoistedGlobal = *c5_temporalCounter_i1;
  c5_g_u = c5_f_hoistedGlobal;
  c5_h_y = NULL;
  sf_mex_assign(&c5_h_y, sf_mex_create("y", &c5_g_u, 7, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 6, c5_h_y);
  sf_mex_assign(&c5_st, c5_y, false);
  return c5_st;
}

static void set_sim_state_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_st)
{
  const mxArray *c5_u;
  uint8_T c5_uv0[256];
  int32_T c5_i1;
  uint8_T *c5_lengthOut;
  real_T *c5_navOn;
  uint8_T *c5_is_active_c5_RaspPiPilot;
  uint8_T *c5_is_c5_RaspPiPilot;
  uint8_T *c5_is_Armed;
  uint32_T *c5_temporalCounter_i1;
  uint8_T (*c5_dataOut)[256];
  c5_temporalCounter_i1 = (uint32_T *)ssGetDWork(chartInstance->S, 5);
  c5_navOn = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c5_lengthOut = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c5_dataOut = (uint8_T (*)[256])ssGetOutputPortSignal(chartInstance->S, 1);
  c5_is_Armed = (uint8_T *)ssGetDWork(chartInstance->S, 4);
  c5_is_c5_RaspPiPilot = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c5_is_active_c5_RaspPiPilot = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c5_u = sf_mex_dup(c5_st);
  c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 0)),
                        "dataOut", c5_uv0);
  for (c5_i1 = 0; c5_i1 < 256; c5_i1++) {
    (*c5_dataOut)[c5_i1] = c5_uv0[c5_i1];
  }

  *c5_lengthOut = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c5_u, 1)), "lengthOut");
  *c5_navOn = c5_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u,
    2)), "navOn");
  *c5_is_active_c5_RaspPiPilot = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 3)), "is_active_c5_RaspPiPilot");
  *c5_is_c5_RaspPiPilot = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 4)), "is_c5_RaspPiPilot");
  *c5_is_Armed = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c5_u, 5)), "is_Armed");
  *c5_temporalCounter_i1 = c5_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 6)), "temporalCounter_i1");
  sf_mex_assign(&chartInstance->c5_setSimStateSideEffectsInfo,
                c5_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c5_u, 7)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c5_u);
  chartInstance->c5_doSetSimStateSideEffects = 1U;
  c5_update_debugger_state_c5_RaspPiPilot(chartInstance);
  sf_mex_destroy(&c5_st);
}

static void c5_set_sim_state_side_effects_c5_RaspPiPilot
  (SFc5_RaspPiPilotInstanceStruct *chartInstance)
{
  uint32_T *c5_temporalCounter_i1;
  uint8_T *c5_is_Armed;
  uint8_T *c5_is_c5_RaspPiPilot;
  c5_temporalCounter_i1 = (uint32_T *)ssGetDWork(chartInstance->S, 5);
  c5_is_Armed = (uint8_T *)ssGetDWork(chartInstance->S, 4);
  c5_is_c5_RaspPiPilot = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  if (chartInstance->c5_doSetSimStateSideEffects != 0) {
    if (*c5_is_Armed == c5_IN_sendArm) {
      if (sf_mex_sub(chartInstance->c5_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 4) == 0.0) {
        *c5_temporalCounter_i1 = 0U;
      }
    }

    if (*c5_is_c5_RaspPiPilot == c5_IN_Initializing) {
      if (sf_mex_sub(chartInstance->c5_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 6) == 0.0) {
        *c5_temporalCounter_i1 = 0U;
      }
    }

    chartInstance->c5_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c5_setSimStateSideEffectsInfo);
}

static void sf_gateway_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance)
{
  int32_T c5_i2;
  int32_T c5_i3;
  int32_T *c5_sfEvent;
  uint32_T *c5_temporalCounter_i1;
  uint8_T *c5_lengthOut;
  boolean_T *c5_dataReceived;
  boolean_T *c5_arm;
  boolean_T *c5_disarm;
  real_T *c5_navOn;
  boolean_T *c5_prytUpdated;
  uint8_T (*c5_dataOut)[256];
  real_T (*c5_PRYTvals)[4];
  c5_temporalCounter_i1 = (uint32_T *)ssGetDWork(chartInstance->S, 5);
  c5_prytUpdated = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c5_navOn = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c5_disarm = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c5_arm = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c5_dataReceived = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c5_lengthOut = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c5_dataOut = (uint8_T (*)[256])ssGetOutputPortSignal(chartInstance->S, 1);
  c5_PRYTvals = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  c5_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  c5_set_sim_state_side_effects_c5_RaspPiPilot(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  if (*c5_temporalCounter_i1 < MAX_uint32_T) {
    (*c5_temporalCounter_i1)++;
  }

  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, *c5_sfEvent);
  for (c5_i2 = 0; c5_i2 < 4; c5_i2++) {
    _SFD_DATA_RANGE_CHECK((*c5_PRYTvals)[c5_i2], 0U);
  }

  for (c5_i3 = 0; c5_i3 < 256; c5_i3++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c5_dataOut)[c5_i3], 1U);
  }

  _SFD_DATA_RANGE_CHECK((real_T)*c5_lengthOut, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*c5_dataReceived, 3U);
  _SFD_DATA_RANGE_CHECK((real_T)*c5_arm, 4U);
  _SFD_DATA_RANGE_CHECK((real_T)*c5_disarm, 5U);
  _SFD_DATA_RANGE_CHECK(*c5_navOn, 6U);
  _SFD_DATA_RANGE_CHECK((real_T)*c5_prytUpdated, 7U);
  *c5_sfEvent = CALL_EVENT;
  c5_chartstep_c5_RaspPiPilot(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_RaspPiPilotMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c5_chartstep_c5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance)
{
  uint32_T c5_debug_family_var_map[2];
  real_T c5_nargin = 0.0;
  real_T c5_nargout = 0.0;
  uint8_T c5_uv1[256];
  int32_T c5_i4;
  int32_T c5_i5;
  uint32_T c5_b_debug_family_var_map[3];
  real_T c5_b_nargin = 0.0;
  real_T c5_b_nargout = 1.0;
  boolean_T c5_out;
  real_T c5_c_nargin = 0.0;
  real_T c5_c_nargout = 0.0;
  uint8_T c5_uv2[256];
  int32_T c5_i6;
  int32_T c5_i7;
  real_T c5_d_nargin = 0.0;
  real_T c5_d_nargout = 0.0;
  uint8_T c5_uv3[256];
  int32_T c5_i8;
  int32_T c5_i9;
  real_T c5_e_nargin = 0.0;
  real_T c5_e_nargout = 1.0;
  boolean_T c5_b_out;
  real_T c5_f_nargin = 0.0;
  real_T c5_f_nargout = 1.0;
  boolean_T c5_c_out;
  real_T c5_g_nargin = 0.0;
  real_T c5_g_nargout = 0.0;
  uint8_T c5_uv4[256];
  int32_T c5_i10;
  int32_T c5_i11;
  real_T c5_h_nargin = 0.0;
  real_T c5_h_nargout = 1.0;
  boolean_T c5_d_out;
  real_T c5_i_nargin = 0.0;
  real_T c5_i_nargout = 0.0;
  uint8_T c5_uv5[256];
  int32_T c5_i12;
  int32_T c5_i13;
  real_T c5_j_nargin = 0.0;
  real_T c5_j_nargout = 0.0;
  uint32_T c5_hoistedGlobal;
  real_T c5_x;
  real_T c5_xk;
  real_T c5_b_x;
  real_T c5_c_x;
  real_T c5_d_x;
  real_T c5_r;
  uint8_T *c5_lengthOut;
  real_T *c5_navOn;
  uint8_T *c5_is_c5_RaspPiPilot;
  uint32_T *c5_temporalCounter_i1;
  uint8_T *c5_is_active_c5_RaspPiPilot;
  boolean_T *c5_dataReceived;
  uint8_T *c5_is_Armed;
  boolean_T *c5_arm;
  boolean_T *c5_prytUpdated;
  boolean_T *c5_disarm;
  uint8_T (*c5_dataOut)[256];
  int32_T *c5_sfEvent;
  c5_temporalCounter_i1 = (uint32_T *)ssGetDWork(chartInstance->S, 5);
  c5_prytUpdated = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c5_navOn = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c5_disarm = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c5_arm = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c5_dataReceived = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c5_lengthOut = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c5_dataOut = (uint8_T (*)[256])ssGetOutputPortSignal(chartInstance->S, 1);
  c5_is_Armed = (uint8_T *)ssGetDWork(chartInstance->S, 4);
  c5_is_c5_RaspPiPilot = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c5_is_active_c5_RaspPiPilot = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c5_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, *c5_sfEvent);
  if (*c5_is_active_c5_RaspPiPilot == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 4U, *c5_sfEvent);
    *c5_is_active_c5_RaspPiPilot = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, *c5_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, *c5_sfEvent);
    *c5_is_c5_RaspPiPilot = c5_IN_Initializing;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, *c5_sfEvent);
    *c5_temporalCounter_i1 = 0U;
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_debug_family_names,
      c5_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 0U, c5_sf_marshallOut,
      c5_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 1U, c5_sf_marshallOut,
      c5_sf_marshallIn);
    *c5_navOn = 0.0;
    c5_updateDataWrittenToVector(chartInstance, 2U);
    _SFD_DATA_RANGE_CHECK(*c5_navOn, 6U);
    c5_requestStreams(chartInstance, c5_uv1);
    for (c5_i4 = 0; c5_i4 < 256; c5_i4++) {
      (*c5_dataOut)[c5_i4] = c5_uv1[c5_i4];
    }

    c5_updateDataWrittenToVector(chartInstance, 0U);
    for (c5_i5 = 0; c5_i5 < 256; c5_i5++) {
      _SFD_DATA_RANGE_CHECK((real_T)(*c5_dataOut)[c5_i5], 1U);
    }

    *c5_lengthOut = 0U;
    c5_updateDataWrittenToVector(chartInstance, 1U);
    _SFD_DATA_RANGE_CHECK((real_T)*c5_lengthOut, 2U);
    sf_call_output_fcn_call(chartInstance->S, 0, "sendme", 0);
    _SFD_SYMBOL_SCOPE_POP();
  } else {
    switch (*c5_is_c5_RaspPiPilot) {
     case c5_IN_Armed:
      CV_CHART_EVAL(4, 0, 1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U, *c5_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_i_debug_family_names,
        c5_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_nargin, 0U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_nargout, 1U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_out, 2U, c5_d_sf_marshallOut,
        c5_d_sf_marshallIn);
      c5_out = CV_EML_IF(2, 0, 0, *c5_disarm);
      _SFD_SYMBOL_SCOPE_POP();
      if (c5_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, *c5_sfEvent);
        switch (*c5_is_Armed) {
         case c5_IN_Flying:
          CV_STATE_EVAL(0, 1, 1);
          *c5_is_Armed = c5_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *c5_sfEvent);
          break;

         case c5_IN_sendArm:
          CV_STATE_EVAL(0, 1, 2);
          *c5_is_Armed = c5_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *c5_sfEvent);
          break;

         default:
          CV_STATE_EVAL(0, 1, 0);
          *c5_is_Armed = c5_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *c5_sfEvent);
          break;
        }

        _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *c5_sfEvent);
        *c5_is_c5_RaspPiPilot = c5_IN_Disarmed;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *c5_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_d_debug_family_names,
          c5_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_nargin, 0U, c5_sf_marshallOut,
          c5_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_nargout, 1U,
          c5_sf_marshallOut, c5_sf_marshallIn);
        c5_sendArmDisarmFun(chartInstance, c5_uv2);
        for (c5_i6 = 0; c5_i6 < 256; c5_i6++) {
          (*c5_dataOut)[c5_i6] = c5_uv2[c5_i6];
        }

        c5_updateDataWrittenToVector(chartInstance, 0U);
        for (c5_i7 = 0; c5_i7 < 256; c5_i7++) {
          _SFD_DATA_RANGE_CHECK((real_T)(*c5_dataOut)[c5_i7], 1U);
        }

        *c5_lengthOut = 0U;
        c5_updateDataWrittenToVector(chartInstance, 1U);
        _SFD_DATA_RANGE_CHECK((real_T)*c5_lengthOut, 2U);
        sf_call_output_fcn_call(chartInstance->S, 0, "sendme", 0);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, *c5_sfEvent);
        switch (*c5_is_Armed) {
         case c5_IN_Flying:
          CV_STATE_EVAL(0, 0, 1);
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U, *c5_sfEvent);
          _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_g_debug_family_names,
            c5_debug_family_var_map);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_d_nargin, 0U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_d_nargout, 1U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          if (CV_EML_IF(1, 1, 0, *c5_prytUpdated)) {
            c5_sendRPYT(chartInstance, c5_uv3);
            for (c5_i8 = 0; c5_i8 < 256; c5_i8++) {
              (*c5_dataOut)[c5_i8] = c5_uv3[c5_i8];
            }

            c5_updateDataWrittenToVector(chartInstance, 0U);
            for (c5_i9 = 0; c5_i9 < 256; c5_i9++) {
              _SFD_DATA_RANGE_CHECK((real_T)(*c5_dataOut)[c5_i9], 1U);
            }

            *c5_lengthOut = 0U;
            c5_updateDataWrittenToVector(chartInstance, 1U);
            _SFD_DATA_RANGE_CHECK((real_T)*c5_lengthOut, 2U);
          }

          _SFD_SYMBOL_SCOPE_POP();
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, *c5_sfEvent);
          break;

         case c5_IN_sendArm:
          CV_STATE_EVAL(0, 0, 2);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U, *c5_sfEvent);
          _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_k_debug_family_names,
            c5_b_debug_family_var_map);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_e_nargin, 0U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_e_nargout, 1U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_out, 2U,
            c5_d_sf_marshallOut, c5_d_sf_marshallIn);
          c5_b_out = CV_EML_IF(4, 0, 0, *c5_temporalCounter_i1 >= 500U);
          _SFD_SYMBOL_SCOPE_POP();
          if (c5_b_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, *c5_sfEvent);
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *c5_sfEvent);
            *c5_is_Armed = c5_IN_Flying;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *c5_sfEvent);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U, *c5_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, *c5_sfEvent);
          break;

         default:
          CV_STATE_EVAL(0, 0, 0);
          *c5_is_Armed = c5_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *c5_sfEvent);
          break;
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *c5_sfEvent);
      break;

     case c5_IN_Disarmed:
      CV_CHART_EVAL(4, 0, 2);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 0U, *c5_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_j_debug_family_names,
        c5_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_f_nargin, 0U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_f_nargout, 1U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_out, 2U, c5_d_sf_marshallOut,
        c5_d_sf_marshallIn);
      c5_c_out = CV_EML_IF(0, 0, 0, *c5_arm);
      _SFD_SYMBOL_SCOPE_POP();
      if (c5_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, *c5_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *c5_sfEvent);
        *c5_is_c5_RaspPiPilot = c5_IN_Armed;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *c5_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, *c5_sfEvent);
        *c5_is_Armed = c5_IN_sendArm;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *c5_sfEvent);
        *c5_temporalCounter_i1 = 0U;
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_f_debug_family_names,
          c5_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_g_nargin, 0U, c5_sf_marshallOut,
          c5_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_g_nargout, 1U,
          c5_sf_marshallOut, c5_sf_marshallIn);
        c5_sendArmDisarmFun(chartInstance, c5_uv4);
        for (c5_i10 = 0; c5_i10 < 256; c5_i10++) {
          (*c5_dataOut)[c5_i10] = c5_uv4[c5_i10];
        }

        c5_updateDataWrittenToVector(chartInstance, 0U);
        for (c5_i11 = 0; c5_i11 < 256; c5_i11++) {
          _SFD_DATA_RANGE_CHECK((real_T)(*c5_dataOut)[c5_i11], 1U);
        }

        *c5_lengthOut = 0U;
        c5_updateDataWrittenToVector(chartInstance, 1U);
        _SFD_DATA_RANGE_CHECK((real_T)*c5_lengthOut, 2U);
        sf_call_output_fcn_call(chartInstance->S, 0, "sendme", 0);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U, *c5_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, *c5_sfEvent);
      break;

     case c5_IN_Initializing:
      CV_CHART_EVAL(4, 0, 3);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U, *c5_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_l_debug_family_names,
        c5_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_h_nargin, 0U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_h_nargout, 1U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_d_out, 2U, c5_d_sf_marshallOut,
        c5_d_sf_marshallIn);
      c5_d_out = CV_EML_IF(1, 0, 0, *c5_dataReceived);
      _SFD_SYMBOL_SCOPE_POP();
      if (c5_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, *c5_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, *c5_sfEvent);
        *c5_is_c5_RaspPiPilot = c5_IN_Disarmed;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *c5_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_d_debug_family_names,
          c5_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_i_nargin, 0U, c5_sf_marshallOut,
          c5_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_i_nargout, 1U,
          c5_sf_marshallOut, c5_sf_marshallIn);
        c5_sendArmDisarmFun(chartInstance, c5_uv5);
        for (c5_i12 = 0; c5_i12 < 256; c5_i12++) {
          (*c5_dataOut)[c5_i12] = c5_uv5[c5_i12];
        }

        c5_updateDataWrittenToVector(chartInstance, 0U);
        for (c5_i13 = 0; c5_i13 < 256; c5_i13++) {
          _SFD_DATA_RANGE_CHECK((real_T)(*c5_dataOut)[c5_i13], 1U);
        }

        *c5_lengthOut = 0U;
        c5_updateDataWrittenToVector(chartInstance, 1U);
        _SFD_DATA_RANGE_CHECK((real_T)*c5_lengthOut, 2U);
        sf_call_output_fcn_call(chartInstance->S, 0, "sendme", 0);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U, *c5_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_c_debug_family_names,
          c5_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_j_nargin, 0U, c5_sf_marshallOut,
          c5_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_j_nargout, 1U,
          c5_sf_marshallOut, c5_sf_marshallIn);
        c5_hoistedGlobal = *c5_temporalCounter_i1;
        c5_x = (real_T)c5_hoistedGlobal * 0.01;
        c5_eml_scalar_eg(chartInstance);
        c5_xk = c5_x;
        c5_b_x = c5_xk;
        c5_eml_scalar_eg(chartInstance);
        c5_c_x = c5_b_x / 2.0;
        c5_d_x = c5_c_x;
        c5_d_x = muDoubleScalarFloor(c5_d_x);
        c5_r = c5_b_x - c5_d_x * 2.0;
        if (CV_EML_IF(4, 1, 0, c5_r == 0.0)) {
          sf_call_output_fcn_call(chartInstance->S, 0, "sendme", 0);
        }

        _SFD_SYMBOL_SCOPE_POP();
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, *c5_sfEvent);
      break;

     default:
      CV_CHART_EVAL(4, 0, 0);
      *c5_is_c5_RaspPiPilot = c5_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *c5_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, *c5_sfEvent);
}

static void initSimStructsc5_RaspPiPilot(SFc5_RaspPiPilotInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c5_eml_scalar_eg(SFc5_RaspPiPilotInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber)
{
  (void)c5_machineNumber;
  (void)c5_chartNumber;
  (void)c5_instanceNumber;
}

static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc5_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real_T c5_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct *chartInstance,
  const mxArray *c5_nargout, const char_T *c5_identifier)
{
  real_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nargout), &c5_thisId);
  sf_mex_destroy(&c5_nargout);
  return c5_y;
}

static real_T c5_b_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d0, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_nargout;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc5_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c5_nargout = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nargout), &c5_thisId);
  sf_mex_destroy(&c5_nargout);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i14;
  uint8_T c5_b_inData[256];
  int32_T c5_i15;
  uint8_T c5_u[256];
  const mxArray *c5_y = NULL;
  SFc5_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc5_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  for (c5_i14 = 0; c5_i14 < 256; c5_i14++) {
    c5_b_inData[c5_i14] = (*(uint8_T (*)[256])c5_inData)[c5_i14];
  }

  for (c5_i15 = 0; c5_i15 < 256; c5_i15++) {
    c5_u[c5_i15] = c5_b_inData[c5_i15];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 3, 0U, 1U, 0U, 1, 256), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_c_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct *chartInstance,
  const mxArray *c5_data, const char_T *c5_identifier, uint8_T c5_y[256])
{
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_data), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_data);
}

static void c5_d_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, uint8_T c5_y[256])
{
  uint8_T c5_uv6[256];
  int32_T c5_i16;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_uv6, 1, 3, 0U, 1, 0U, 1, 256);
  for (c5_i16 = 0; c5_i16 < 256; c5_i16++) {
    c5_y[c5_i16] = c5_uv6[c5_i16];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_data;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  uint8_T c5_y[256];
  int32_T c5_i17;
  SFc5_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc5_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c5_data = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_data), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_data);
  for (c5_i17 = 0; c5_i17 < 256; c5_i17++) {
    (*(uint8_T (*)[256])c5_outData)[c5_i17] = c5_y[c5_i17];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  uint8_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc5_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(uint8_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static uint8_T c5_e_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_length, const char_T *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_length), &c5_thisId);
  sf_mex_destroy(&c5_length);
  return c5_y;
}

static uint8_T c5_f_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u0, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_length;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  uint8_T c5_y;
  SFc5_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc5_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c5_length = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_length), &c5_thisId);
  sf_mex_destroy(&c5_length);
  *(uint8_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  boolean_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc5_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(boolean_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static boolean_T c5_g_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  boolean_T c5_y;
  boolean_T c5_b0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_b0, 1, 11, 0U, 0, 0U, 0);
  c5_y = c5_b0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_sf_internal_predicateOutput;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  boolean_T c5_y;
  SFc5_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc5_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c5_sf_internal_predicateOutput = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_sf_internal_predicateOutput), &c5_thisId);
  sf_mex_destroy(&c5_sf_internal_predicateOutput);
  *(boolean_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

const mxArray *sf_c5_RaspPiPilot_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  sf_mex_assign(&c5_nameCaptureInfo, sf_mex_createstruct("structure", 2, 14, 1),
                false);
  c5_info_helper(&c5_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c5_nameCaptureInfo);
  return c5_nameCaptureInfo;
}

static void c5_info_helper(const mxArray **c5_info)
{
  const mxArray *c5_rhs0 = NULL;
  const mxArray *c5_lhs0 = NULL;
  const mxArray *c5_rhs1 = NULL;
  const mxArray *c5_lhs1 = NULL;
  const mxArray *c5_rhs2 = NULL;
  const mxArray *c5_lhs2 = NULL;
  const mxArray *c5_rhs3 = NULL;
  const mxArray *c5_lhs3 = NULL;
  const mxArray *c5_rhs4 = NULL;
  const mxArray *c5_lhs4 = NULL;
  const mxArray *c5_rhs5 = NULL;
  const mxArray *c5_lhs5 = NULL;
  const mxArray *c5_rhs6 = NULL;
  const mxArray *c5_lhs6 = NULL;
  const mxArray *c5_rhs7 = NULL;
  const mxArray *c5_lhs7 = NULL;
  const mxArray *c5_rhs8 = NULL;
  const mxArray *c5_lhs8 = NULL;
  const mxArray *c5_rhs9 = NULL;
  const mxArray *c5_lhs9 = NULL;
  const mxArray *c5_rhs10 = NULL;
  const mxArray *c5_lhs10 = NULL;
  const mxArray *c5_rhs11 = NULL;
  const mxArray *c5_lhs11 = NULL;
  const mxArray *c5_rhs12 = NULL;
  const mxArray *c5_lhs12 = NULL;
  const mxArray *c5_rhs13 = NULL;
  const mxArray *c5_lhs13 = NULL;
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("mod"), "name", "name", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c5_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c5_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1375984288U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c5_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c5_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1375984288U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c5_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c5_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod"), "context",
                  "context", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1375984288U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c5_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod"), "context",
                  "context", 7);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 7);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286822326U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c5_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod"), "context",
                  "context", 8);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_round"), "name",
                  "name", 8);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_round.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1307654838U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c5_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod"), "context",
                  "context", 9);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 9);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286822312U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c5_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod"), "context",
                  "context", 10);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eps"), "name", "name", 10);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "resolved",
                  "resolved", 10);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1326731596U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c5_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_is_float_class"), "name",
                  "name", 11);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286822382U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c5_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 12);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_eps"), "name", "name", 12);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1326731596U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c5_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m"), "context",
                  "context", 13);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 13);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 13);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1326731596U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c5_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs13), "lhs", "lhs",
                  13);
  sf_mex_destroy(&c5_rhs0);
  sf_mex_destroy(&c5_lhs0);
  sf_mex_destroy(&c5_rhs1);
  sf_mex_destroy(&c5_lhs1);
  sf_mex_destroy(&c5_rhs2);
  sf_mex_destroy(&c5_lhs2);
  sf_mex_destroy(&c5_rhs3);
  sf_mex_destroy(&c5_lhs3);
  sf_mex_destroy(&c5_rhs4);
  sf_mex_destroy(&c5_lhs4);
  sf_mex_destroy(&c5_rhs5);
  sf_mex_destroy(&c5_lhs5);
  sf_mex_destroy(&c5_rhs6);
  sf_mex_destroy(&c5_lhs6);
  sf_mex_destroy(&c5_rhs7);
  sf_mex_destroy(&c5_lhs7);
  sf_mex_destroy(&c5_rhs8);
  sf_mex_destroy(&c5_lhs8);
  sf_mex_destroy(&c5_rhs9);
  sf_mex_destroy(&c5_lhs9);
  sf_mex_destroy(&c5_rhs10);
  sf_mex_destroy(&c5_lhs10);
  sf_mex_destroy(&c5_rhs11);
  sf_mex_destroy(&c5_lhs11);
  sf_mex_destroy(&c5_rhs12);
  sf_mex_destroy(&c5_lhs12);
  sf_mex_destroy(&c5_rhs13);
  sf_mex_destroy(&c5_lhs13);
}

static const mxArray *c5_emlrt_marshallOut(const char * c5_u)
{
  const mxArray *c5_y = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c5_u)), false);
  return c5_y;
}

static const mxArray *c5_b_emlrt_marshallOut(const uint32_T c5_u)
{
  const mxArray *c5_y = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 7, 0U, 0U, 0U, 0), false);
  return c5_y;
}

static void c5_requestStreams(SFc5_RaspPiPilotInstanceStruct *chartInstance,
  uint8_T c5_data[256])
{
  uint32_T c5_debug_family_var_map[5];
  uint8_T c5_length;
  uint8_T c5_data2[256];
  real_T c5_nargin = 0.0;
  real_T c5_nargout = 2.0;
  int32_T c5_i18;
  int32_T c5_i19;
  int32_T *c5_sfEvent;
  c5_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 5U, 5U, c5_b_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_length, 0U, c5_c_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_data2, 1U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 2U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 3U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_data, 4U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  CV_EML_FCN(5, 0);
  _SFD_EML_CALL(5U, *c5_sfEvent, 2);
  for (c5_i18 = 0; c5_i18 < 256; c5_i18++) {
    c5_data2[c5_i18] = 0U;
  }

  _SFD_EML_CALL(5U, *c5_sfEvent, 3);
  c5_length = 0U;
  _SFD_EML_CALL(5U, *c5_sfEvent, 4);
  for (c5_i19 = 0; c5_i19 < 256; c5_i19++) {
    c5_data[c5_i19] = c5_data2[c5_i19];
  }

  _SFD_EML_CALL(5U, *c5_sfEvent, 5);
  CV_EML_COND(5, 1, 0, true);
  CV_EML_MCDC(5, 1, 0, false);
  CV_EML_IF(5, 1, 0, false);
  _SFD_EML_CALL(5U, *c5_sfEvent, -7);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c5_sendArmDisarmFun(SFc5_RaspPiPilotInstanceStruct *chartInstance,
  uint8_T c5_data[256])
{
  uint32_T c5_debug_family_var_map[5];
  uint8_T c5_length;
  uint8_T c5_data2[256];
  real_T c5_nargin = 1.0;
  real_T c5_nargout = 2.0;
  int32_T c5_i20;
  int32_T c5_i21;
  int32_T *c5_sfEvent;
  c5_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 5U, 5U, c5_e_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_length, 0U, c5_c_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_data2, 1U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 2U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 3U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_data, 4U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  CV_EML_FCN(6, 0);
  _SFD_EML_CALL(6U, *c5_sfEvent, 2);
  for (c5_i20 = 0; c5_i20 < 256; c5_i20++) {
    c5_data2[c5_i20] = 0U;
  }

  _SFD_EML_CALL(6U, *c5_sfEvent, 3);
  c5_length = 0U;
  _SFD_EML_CALL(6U, *c5_sfEvent, 4);
  for (c5_i21 = 0; c5_i21 < 256; c5_i21++) {
    c5_data[c5_i21] = c5_data2[c5_i21];
  }

  _SFD_EML_CALL(6U, *c5_sfEvent, 5);
  CV_EML_COND(6, 1, 0, true);
  CV_EML_MCDC(6, 1, 0, false);
  CV_EML_IF(6, 1, 0, false);
  _SFD_EML_CALL(6U, *c5_sfEvent, -7);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c5_sendRPYT(SFc5_RaspPiPilotInstanceStruct *chartInstance, uint8_T
  c5_data[256])
{
  uint32_T c5_debug_family_var_map[5];
  uint8_T c5_length;
  uint8_T c5_data2[256];
  real_T c5_nargin = 4.0;
  real_T c5_nargout = 2.0;
  int32_T c5_i22;
  int32_T c5_i23;
  int32_T *c5_sfEvent;
  c5_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 5U, 5U, c5_h_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_length, 0U, c5_c_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_data2, 1U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 2U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 3U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_data, 4U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  CV_EML_FCN(7, 0);
  _SFD_EML_CALL(7U, *c5_sfEvent, 2);
  for (c5_i22 = 0; c5_i22 < 256; c5_i22++) {
    c5_data2[c5_i22] = 0U;
  }

  _SFD_EML_CALL(7U, *c5_sfEvent, 3);
  c5_length = 0U;
  _SFD_EML_CALL(7U, *c5_sfEvent, 4);
  for (c5_i23 = 0; c5_i23 < 256; c5_i23++) {
    c5_data[c5_i23] = c5_data2[c5_i23];
  }

  _SFD_EML_CALL(7U, *c5_sfEvent, 5);
  CV_EML_COND(7, 1, 0, true);
  CV_EML_MCDC(7, 1, 0, false);
  CV_EML_IF(7, 1, 0, false);
  _SFD_EML_CALL(7U, *c5_sfEvent, -8);
  _SFD_SYMBOL_SCOPE_POP();
}

static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc5_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static int32_T c5_h_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i24;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i24, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i24;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_sfEvent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc5_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c5_sfEvent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_sfEvent), &c5_thisId);
  sf_mex_destroy(&c5_sfEvent);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_f_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i25;
  real_T c5_b_inData[4];
  int32_T c5_i26;
  real_T c5_u[4];
  const mxArray *c5_y = NULL;
  SFc5_RaspPiPilotInstanceStruct *chartInstance;
  chartInstance = (SFc5_RaspPiPilotInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  for (c5_i25 = 0; c5_i25 < 4; c5_i25++) {
    c5_b_inData[c5_i25] = (*(real_T (*)[4])c5_inData)[c5_i25];
  }

  for (c5_i26 = 0; c5_i26 < 4; c5_i26++) {
    c5_u[c5_i26] = c5_b_inData[c5_i26];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static uint32_T c5_i_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_temporalCounter_i1, const char_T
  *c5_identifier)
{
  uint32_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_temporalCounter_i1),
    &c5_thisId);
  sf_mex_destroy(&c5_temporalCounter_i1);
  return c5_y;
}

static uint32_T c5_j_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint32_T c5_y;
  uint32_T c5_u1;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u1, 1, 7, 0U, 0, 0U, 0);
  c5_y = c5_u1;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static const mxArray *c5_k_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_b_setSimStateSideEffectsInfo, const char_T
  *c5_identifier)
{
  const mxArray *c5_y = NULL;
  emlrtMsgIdentifier c5_thisId;
  c5_y = NULL;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  sf_mex_assign(&c5_y, c5_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_b_setSimStateSideEffectsInfo), &c5_thisId), false);
  sf_mex_destroy(&c5_b_setSimStateSideEffectsInfo);
  return c5_y;
}

static const mxArray *c5_l_emlrt_marshallIn(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  const mxArray *c5_y = NULL;
  (void)chartInstance;
  (void)c5_parentId;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_duplicatearraysafe(&c5_u), false);
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_updateDataWrittenToVector(SFc5_RaspPiPilotInstanceStruct
  *chartInstance, uint32_T c5_vectorIndex)
{
  (void)chartInstance;
  c5_dataWrittenToVector[(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK(0, (int32_T)
    c5_vectorIndex, 0, 8, 1, 0)] = true;
}

static void init_dsm_address_info(SFc5_RaspPiPilotInstanceStruct *chartInstance)
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

static uint32_T* sf_get_sfun_dwork_checksum();
void sf_c5_RaspPiPilot_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1904518274U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1384940245U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3721821798U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3327504412U);
}

mxArray *sf_c5_RaspPiPilot_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("Tim7K7aYOU0FNLZ19SbbJF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(256);
      pr[1] = (double)(1);
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
      pr[0] = (double)(1);
      pr[1] = (double)(1);
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
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c5_RaspPiPilot_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c5_RaspPiPilot_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c5_RaspPiPilot(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x7'type','srcId','name','auxInfo'{{M[1],M[17],T\"dataOut\",},{M[1],M[18],T\"lengthOut\",},{M[1],M[44],T\"navOn\",},{M[8],M[0],T\"is_active_c5_RaspPiPilot\",},{M[9],M[0],T\"is_c5_RaspPiPilot\",},{M[9],M[3],T\"is_Armed\",},{M[11],M[0],T\"temporalCounter_i1\",S'et','os','ct'{{T\"at\",M1x2[1 31],M[1]}}}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 7, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_RaspPiPilot_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_RaspPiPilotInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc5_RaspPiPilotInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _RaspPiPilotMachineNumber_,
           5,
           8,
           6,
           0,
           19,
           1,
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
            1,
            1,
            1);
          _SFD_SET_DATA_PROPS(0,1,1,0,"PRYTvals");
          _SFD_SET_DATA_PROPS(1,2,0,1,"dataOut");
          _SFD_SET_DATA_PROPS(2,2,0,1,"lengthOut");
          _SFD_SET_DATA_PROPS(3,1,1,0,"dataReceived");
          _SFD_SET_DATA_PROPS(4,1,1,0,"arm");
          _SFD_SET_DATA_PROPS(5,1,1,0,"disarm");
          _SFD_SET_DATA_PROPS(6,2,0,1,"navOn");
          _SFD_SET_DATA_PROPS(7,1,1,0,"prytUpdated");
          _SFD_SET_DATA_PROPS(8,9,0,0,"");
          _SFD_SET_DATA_PROPS(9,9,0,0,"");
          _SFD_SET_DATA_PROPS(10,9,0,0,"");
          _SFD_SET_DATA_PROPS(11,9,0,0,"");
          _SFD_SET_DATA_PROPS(12,8,0,0,"");
          _SFD_SET_DATA_PROPS(13,9,0,0,"");
          _SFD_SET_DATA_PROPS(14,9,0,0,"");
          _SFD_SET_DATA_PROPS(15,8,0,0,"");
          _SFD_SET_DATA_PROPS(16,8,0,0,"");
          _SFD_SET_DATA_PROPS(17,8,0,0,"");
          _SFD_SET_DATA_PROPS(18,8,0,0,"");
          _SFD_EVENT_SCOPE(0,2);
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,2);
          _SFD_STATE_INFO(6,0,2);
          _SFD_STATE_INFO(7,0,2);
          _SFD_CH_SUBSTATE_COUNT(3);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,3);
          _SFD_CH_SUBSTATE_INDEX(2,4);
          _SFD_ST_SUBSTATE_COUNT(0,2);
          _SFD_ST_SUBSTATE_INDEX(0,0,1);
          _SFD_ST_SUBSTATE_INDEX(0,1,2);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
        }

        _SFD_CV_INIT_CHART(3,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(5,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(6,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(7,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(2,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(5,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(5,1,1,1,0,0,0,0,0,1,1);
        _SFD_CV_INIT_EML_FCN(5,0,"requestStreams",0,-1,205);
        _SFD_CV_INIT_EML_IF(5,1,0,101,125,-1,202);

        {
          static int condStart[] = { 105 };

          static int condEnd[] = { 125 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(5,1,0,104,125,1,0,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML(6,1,1,1,0,0,0,0,0,1,1);
        _SFD_CV_INIT_EML_FCN(6,0,"sendArmDisarmFun",0,-1,235);
        _SFD_CV_INIT_EML_IF(6,1,0,114,138,-1,232);

        {
          static int condStart[] = { 118 };

          static int condEnd[] = { 138 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(6,1,0,117,138,1,0,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML(7,1,1,1,0,0,0,0,0,1,1);
        _SFD_CV_INIT_EML_FCN(7,0,"sendRPYT",0,-1,259);
        _SFD_CV_INIT_EML_IF(7,1,0,107,131,-1,256);

        {
          static int condStart[] = { 111 };

          static int condEnd[] = { 131 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(7,1,0,110,131,1,0,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML(4,1,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(4,1,0,92,123,-1,144);
        _SFD_CV_INIT_EML(3,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(2,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(1,1,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(1,1,0,31,45,-1,174);
        _SFD_CV_INIT_EML(2,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(2,0,0,1,7,1,7);
        _SFD_CV_INIT_EML(0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(0,0,0,1,4,1,4);
        _SFD_CV_INIT_EML(4,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(4,0,0,0,12,0,12);
        _SFD_CV_INIT_EML(1,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(1,0,0,1,13,1,13);

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 256;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_b_sf_marshallOut,(MexInFcnForType)
            c5_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_d_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295;
          _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295;
          _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295;
          _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295;
          _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295;
          _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295;
          _SFD_SET_DATA_COMPILED_PROPS(17,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295;
          _SFD_SET_DATA_COMPILED_PROPS(18,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_VALUE_PTR(8,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(9,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(10,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(11,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(12,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(13,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(14,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(15,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(16,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(17,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(18,(void *)(NULL));

        {
          uint8_T *c5_lengthOut;
          boolean_T *c5_dataReceived;
          boolean_T *c5_arm;
          boolean_T *c5_disarm;
          real_T *c5_navOn;
          boolean_T *c5_prytUpdated;
          real_T (*c5_PRYTvals)[4];
          uint8_T (*c5_dataOut)[256];
          c5_prytUpdated = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c5_navOn = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c5_disarm = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c5_arm = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c5_dataReceived = (boolean_T *)ssGetInputPortSignal(chartInstance->S,
            1);
          c5_lengthOut = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c5_dataOut = (uint8_T (*)[256])ssGetOutputPortSignal(chartInstance->S,
            1);
          c5_PRYTvals = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c5_PRYTvals);
          _SFD_SET_DATA_VALUE_PTR(1U, *c5_dataOut);
          _SFD_SET_DATA_VALUE_PTR(2U, c5_lengthOut);
          _SFD_SET_DATA_VALUE_PTR(3U, c5_dataReceived);
          _SFD_SET_DATA_VALUE_PTR(4U, c5_arm);
          _SFD_SET_DATA_VALUE_PTR(5U, c5_disarm);
          _SFD_SET_DATA_VALUE_PTR(6U, c5_navOn);
          _SFD_SET_DATA_VALUE_PTR(7U, c5_prytUpdated);
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
  return "pJeXPbgpNiw7KdSt4hFzCF";
}

static void sf_check_dwork_consistency(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    const uint32_T *sfunDWorkChecksum = sf_get_sfun_dwork_checksum();
    mxArray *infoStruct = load_RaspPiPilot_optimization_info();
    mxArray* mxRTWDWorkChecksum = sf_get_dwork_info_from_mat_file(S,
      sf_get_instance_specialization(), infoStruct, 5, "dworkChecksum");
    if (mxRTWDWorkChecksum != NULL) {
      double *pr = mxGetPr(mxRTWDWorkChecksum);
      if ((uint32_T)pr[0] != sfunDWorkChecksum[0] ||
          (uint32_T)pr[1] != sfunDWorkChecksum[1] ||
          (uint32_T)pr[2] != sfunDWorkChecksum[2] ||
          (uint32_T)pr[3] != sfunDWorkChecksum[3]) {
        sf_mex_error_message("Code generation and simulation targets registered different sets of persistent variables for the block. "
                             "External or Rapid Accelerator mode simulation requires code generation and simulation targets to "
                             "register the same set of persistent variables for this block. "
                             "This discrepancy is typically caused by MATLAB functions that have different code paths for "
                             "simulation and code generation targets where these code paths define different sets of persistent variables. "
                             "Please identify these code paths in the offending block and rewrite the MATLAB code so that "
                             "the set of persistent variables is the same between simulation and code generation.");
      }
    }
  }
}

static void sf_opaque_initialize_c5_RaspPiPilot(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc5_RaspPiPilotInstanceStruct*) chartInstanceVar)
    ->S);
  chart_debug_initialization(((SFc5_RaspPiPilotInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c5_RaspPiPilot((SFc5_RaspPiPilotInstanceStruct*)
    chartInstanceVar);
  initialize_c5_RaspPiPilot((SFc5_RaspPiPilotInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c5_RaspPiPilot(void *chartInstanceVar)
{
  enable_c5_RaspPiPilot((SFc5_RaspPiPilotInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c5_RaspPiPilot(void *chartInstanceVar)
{
  disable_c5_RaspPiPilot((SFc5_RaspPiPilotInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c5_RaspPiPilot(void *chartInstanceVar)
{
  sf_gateway_c5_RaspPiPilot((SFc5_RaspPiPilotInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c5_RaspPiPilot(void *chartInstanceVar)
{
  ext_mode_exec_c5_RaspPiPilot((SFc5_RaspPiPilotInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c5_RaspPiPilot(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c5_RaspPiPilot
    ((SFc5_RaspPiPilotInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c5_RaspPiPilot();/* state var info */
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

extern void sf_internal_set_sim_state_c5_RaspPiPilot(SimStruct* S, const mxArray
  *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c5_RaspPiPilot();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c5_RaspPiPilot((SFc5_RaspPiPilotInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c5_RaspPiPilot(SimStruct* S)
{
  return sf_internal_get_sim_state_c5_RaspPiPilot(S);
}

static void sf_opaque_set_sim_state_c5_RaspPiPilot(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c5_RaspPiPilot(S, st);
}

static void sf_opaque_terminate_c5_RaspPiPilot(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_RaspPiPilotInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_RaspPiPilot_optimization_info();
    }

    finalize_c5_RaspPiPilot((SFc5_RaspPiPilotInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_RaspPiPilot((SFc5_RaspPiPilotInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_RaspPiPilot(SimStruct *S)
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
    initialize_params_c5_RaspPiPilot((SFc5_RaspPiPilotInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

mxArray *sf_c5_RaspPiPilot_get_testpoint_info(void)
{
  const char *infoEncStr[] = {
    "100 S1x3'varName','path'{{T\"is_active_c5_RaspPiPilot\",T\"is_active_c5_RaspPiPilot\"},{T\"is_c5_RaspPiPilot\",T\"is_c5_RaspPiPilot\"},{T\"is_Armed\",T\"Armed.is_Armed\"}}"
  };

  mxArray *mxTpInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  return mxTpInfo;
}

static void sf_set_sfun_dwork_info(SimStruct *S)
{
  const char *dworkEncStr[] = {
    "100 S1x6'type','isSigned','wordLength','bias','slope','exponent','isScaledDouble','isComplex','size'{{T\"int32\",,,,,,,M[0],M[]},{T\"boolean\",,,,,,,M[0],M[]},{T\"uint8\",,,,,,,M[0],M[]},{T\"uint8\",,,,,,,M[0],M[]},{T\"uint8\",,,,,,,M[0],M[]},{T\"uint32\",,,,,,,M[0],M[]}}"
  };

  sf_set_encoded_dwork_info(S, dworkEncStr, 6, 10);
}

static uint32_T* sf_get_sfun_dwork_checksum()
{
  static uint32_T checksum[4] = { 439065496U, 1520938774U, 1732640003U,
    1493309074U };

  return checksum;
}

static void mdlSetWorkWidths_c5_RaspPiPilot(SimStruct *S)
{
  ssSetModelReferenceSampleTimeDisallowInheritance(S);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_RaspPiPilot_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,5,"RTWCG"));
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,5,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,5);
    sf_mark_output_events_with_multiple_callers(S,sf_get_instance_specialization
      (),infoStruct,5,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,5,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3521147192U));
  ssSetChecksum1(S,(3656840797U));
  ssSetChecksum2(S,(3291728868U));
  ssSetChecksum3(S,(3859978395U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c5_RaspPiPilot(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c5_RaspPiPilot(SimStruct *S)
{
  SFc5_RaspPiPilotInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc5_RaspPiPilotInstanceStruct *)utMalloc(sizeof
    (SFc5_RaspPiPilotInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc5_RaspPiPilotInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c5_RaspPiPilot;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c5_RaspPiPilot;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c5_RaspPiPilot;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_RaspPiPilot;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_RaspPiPilot;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c5_RaspPiPilot;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c5_RaspPiPilot;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c5_RaspPiPilot;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_RaspPiPilot;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_RaspPiPilot;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c5_RaspPiPilot;
  chartInstance->chartInfo.extModeExec = sf_opaque_ext_mode_exec_c5_RaspPiPilot;
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

void c5_RaspPiPilot_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_RaspPiPilot(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_RaspPiPilot(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_RaspPiPilot(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_RaspPiPilot_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
