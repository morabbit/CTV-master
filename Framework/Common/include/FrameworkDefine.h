#pragma once
#ifndef __FRAMEWORKDEFINE_H
#define __FRAMEWORKDEFINE_H

#include "FrameworkErrorCode.h"

#define STATUS_SUCCESS(status)											\
{																		\
   if(status != SUCCESSED)												\
   {																	\
       return;															\
   }																	\
}

#define CHECK_STATUS_AND_RETURN_FALSE_IF_FAILED(status)	             	\
{																		\
   if(status != SUCCESSED)												\
   {																	\
       return false;								     				\
   }																	\
}


#define CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status)	         	\
{																		\
   if(status != SUCCESSED)												\
   {																	\
       return status;								     				\
   }																	\
}

#define CHECK_STATUS_AND_RETURN_OBJ_IF_FAILED(status, obj)              \
{                                                                       \
   if(status != SUCCESSED)                                              \
   {                                                                    \
       return obj;                                                      \
   }                                                                    \
}

#define CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(status,msg, obj)  \
{                                                                       \
   if(status != SUCCESSED)                                              \
   {                                                                    \
       __err_msg__ << msg;                                              \
       return obj;                                                      \
   }                                                                    \
}

#define CHECK_POINTER_AND_RETURN_FAIL_IF_NULL(ptr)                          \
if(ptr == nullptr)                                                          \
{                                                                           \
    PRINT_ERR("%s():%d NULL pointer error: [" #ptr "]",                     \
        __func__, __LINE__);                                                \
    return FRAMEWORK_STATUS_FAIL;                                           \
}


#define CHECK_EXPRESSION_AND_GOTO_EXIT(exp, errMsgfmt, ...)                 \
{                                                                           \
    if (!(exp))                                                             \
    {                                                                       \
        PRINT_ERR(errMsgfmt, __VA_ARGS__);                                  \
        goto Exit;                                                          \
    }                                                                       \
}
#define CHECK_EXPRESSION_AND_RETURN_CODE(exp, errCode, errMsgfmt, ...)      \
{                                                                           \
    if (!(exp))                                                             \
    {                                                                       \
         PRINT_ERR(errMsgfmt, __VA_ARGS__);                                 \
         return errCode;                                                    \
    }                                                                       \
}

#define CHECK_EXPRESSION_AND_RETURN_FAIL(exp, errMsgfmt, ...)               \
{                                                                           \
    if (!(exp))                                                             \
    {                                                                       \
         PRINT_ERR(errMsgfmt, __VA_ARGS__);                                 \
         return STATUS_FAILED;                                             \
    }                                                                       \
}

#endif // !__FRAMEWORKDEFINE_H
