#ifndef __c20_RaspPiPilot_h__
#define __c20_RaspPiPilot_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc20_RaspPiPilotInstanceStruct
#define typedef_SFc20_RaspPiPilotInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c20_sfEvent;
  boolean_T c20_isStable;
  boolean_T c20_doneDoubleBufferReInit;
  uint8_T c20_is_active_c20_RaspPiPilot;
} SFc20_RaspPiPilotInstanceStruct;

#endif                                 /*typedef_SFc20_RaspPiPilotInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c20_RaspPiPilot_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c20_RaspPiPilot_get_check_sum(mxArray *plhs[]);
extern void c20_RaspPiPilot_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
