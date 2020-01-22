/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.0-dev */

#ifndef PB_PERSON_PB_H_INCLUDED
#define PB_PERSON_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _Person_PhoneType {
    Person_PhoneType_MOBILE = 0,
    Person_PhoneType_HOME = 1,
    Person_PhoneType_WORK = 2
} Person_PhoneType;
#define _Person_PhoneType_MIN Person_PhoneType_MOBILE
#define _Person_PhoneType_MAX Person_PhoneType_WORK
#define _Person_PhoneType_ARRAYSIZE ((Person_PhoneType)(Person_PhoneType_WORK+1))

/* Struct definitions */
typedef struct _Person_PhoneNumber {
    char number[16];
    bool has_type;
    Person_PhoneType type;
/* @@protoc_insertion_point(struct:Person_PhoneNumber) */
} Person_PhoneNumber;


typedef struct _Person {
    char name[64];
    int32_t id;
    bool has_email;
    char email[128];
    pb_size_t phone_count;
    Person_PhoneNumber phone[5];
/* @@protoc_insertion_point(struct:Person) */
} Person;


/* Initializer values for message structs */
#define Person_init_default                      {"", 0, false, "", 0, {Person_PhoneNumber_init_default, Person_PhoneNumber_init_default, Person_PhoneNumber_init_default, Person_PhoneNumber_init_default, Person_PhoneNumber_init_default}}
#define Person_PhoneNumber_init_default          {"", false, Person_PhoneType_HOME}
#define Person_init_zero                         {"", 0, false, "", 0, {Person_PhoneNumber_init_zero, Person_PhoneNumber_init_zero, Person_PhoneNumber_init_zero, Person_PhoneNumber_init_zero, Person_PhoneNumber_init_zero}}
#define Person_PhoneNumber_init_zero             {"", false, _Person_PhoneType_MIN}

/* Field tags (for use in manual encoding/decoding) */
#define Person_PhoneNumber_number_tag            1
#define Person_PhoneNumber_type_tag              2
#define Person_name_tag                          1
#define Person_id_tag                            2
#define Person_email_tag                         3
#define Person_phone_tag                         4

/* Struct field encoding specification for nanopb */
#define Person_FIELDLIST(X, a) \
X(a, STATIC, REQUIRED, STRING, name, 1) \
X(a, STATIC, REQUIRED, INT32, id, 2) \
X(a, STATIC, OPTIONAL, STRING, email, 3) \
X(a, STATIC, REPEATED, MESSAGE, phone, 4)
#define Person_CALLBACK NULL
#define Person_DEFAULT NULL
#define Person_phone_MSGTYPE Person_PhoneNumber

#define Person_PhoneNumber_FIELDLIST(X, a) \
X(a, STATIC, REQUIRED, STRING, number, 1) \
X(a, STATIC, OPTIONAL, UENUM, type, 2)
#define Person_PhoneNumber_CALLBACK NULL
#define Person_PhoneNumber_DEFAULT (const uint8_t*)"\x10\x01\x00"

extern const pb_msgdesc_t Person_msg;
extern const pb_msgdesc_t Person_PhoneNumber_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define Person_fields &Person_msg
#define Person_PhoneNumber_fields &Person_PhoneNumber_msg

/* Maximum encoded size of messages (where known) */
#define Person_size                              311
#define Person_PhoneNumber_size                  19

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
