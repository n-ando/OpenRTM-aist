#ifndef CORBACDRDATASPLTYPES_H
#define CORBACDRDATASPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ccpp_CORBACdrData.h"


extern c_metaObject __CORBACdrData_OpenRTM__load (c_base base);

extern const char *OpenRTM_CORBACdrData_metaDescriptor[];
extern const int OpenRTM_CORBACdrData_metaDescriptorArrLength;
extern const int OpenRTM_CORBACdrData_metaDescriptorLength;
extern c_metaObject __OpenRTM_CORBACdrData__load (c_base base);
struct _OpenRTM_CORBACdrData ;
extern  v_copyin_result __OpenRTM_CORBACdrData__copyIn(c_base base, const struct OpenRTM::CORBACdrData *from, struct _OpenRTM_CORBACdrData *to);
extern  void __OpenRTM_CORBACdrData__copyOut(const void *_from, void *_to);
struct _OpenRTM_CORBACdrData {
    c_sequence data;
};

#undef OS_API
#endif
