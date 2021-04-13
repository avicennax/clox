#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "value.h"

#define OBJ_TYPE(value)        (AS_OBJ(value)->type)
#define IS_STRING(value)       isObjType(value, OBJ_STRING)

typedef enum {
  OBJ_STRING,
} ObjType;

struct Obj {
  ObjType type;
};

/*
Note how the first bytes of ObjString exactly line up with Obj. 
This is not a coincidence—C mandates it. This is designed to enable 
a clever pattern: You can take a pointer to a struct and safely 
convert it to a pointer to its first field and back.
*/
struct ObjString {
  Obj obj;
  int length;
  char* chars;
};

ObjString* copyString(const char* chars, int length);

static inline bool isObjType(Value value, ObjType type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif