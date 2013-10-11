/*
 * @(#)mwutil.h    generated by: makeheader 5.1.5  Thu Jan 17 14:32:54 2008
 *
 *		built from:	../../src/include/copyright.h
 *				../../src/include/pragma_interface.h
 *				include/msg_typedefs.h
 *				include/err_typedefs.h
 *				cputime.cpp
 *				cycles.cpp
 *				dconvert.cpp
 *				demangle.cpp
 *				dynload.cpp
 *				emptystr.cpp
 *				enum_str.cpp
 *				expmatch.cpp
 *				f2cstr.cpp
 *				fgets.cpp
 *				filelink.cpp
 *				format.cpp
 *				fp_conv.cpp
 *				fpu.cpp
 *				getcwd.cpp
 *				hash.cpp
 *				incrfcn.cpp
 *				int_conv.cpp
 *				logfile.cpp
 *				lower.cpp
 *				multibyte.cpp
 *				mwclasses.cpp
 *				perfcount.cpp
 *				printf.cpp
 *				purifytools.cpp
 *				regexp.cpp
 *				set.cpp
 *				special_nans.cpp
 *				stacktrc.cpp
 *				strcat.cpp
 *				strcmp.cpp
 *				strcmpi.cpp
 *				strcpy.cpp
 *				strdup.cpp
 *				strlen.cpp
 *				strrep.cpp
 *				strrstr.cpp
 *				strtok.cpp
 *				sysinfo.cpp
 *				timeinfo.cpp
 *				tmpnam.cpp
 *				tolower.cpp
 *				upper.cpp
 *				utStreamUtilities.cpp
 *				ut_alloca.cpp
 *				utassert.cpp
 *				utcrc.cpp
 *				utsignal.cpp
 *				wallclok.cpp
 *				array/array.cpp
 *				basic/basic_contexts.cpp
 *				checksum/md5checksum.cpp
 *				coll/functional.cpp
 *				coll/hash_map.cpp
 *				coll/hashrank.cpp
 *				cpputils/attacher.cpp
 *				cpputils/chunkedptr.cpp
 *				cpputils/countlist.cpp
 *				cpputils/safepointer.cpp
 *				cpputils/stat_ref_ok.cpp
 *				cpputils/static_init.cpp
 *				cpputils/stl_allocator.cpp
 *				dsbuffer/dsbuffer.cpp
 *				dtoa/dtoa.cpp
 *				dtoa/fpc.cpp
 *				dtoa/g_fmt.cpp
 *				err/error_context.cpp
 *				except/cmnHooks.cpp
 *				except/cmnSystemCalls.cpp
 *				except/errIdentifiable.cpp
 *				except/errInternalException.cpp
 *				except/errStackThrowable.cpp
 *				except/errStackTrace.cpp
 *				except/errSystemError.cpp
 *				except/errThrowable.cpp
 *				except/errUserException.cpp
 *				except/exceptCleanup.cpp
 *				except/exceptTypedefs.cpp
 *				except/instCpuCounter.cpp
 *				except/instInstrument.cpp
 *				except/instStopwatch.cpp
 *				except/logBasicSystemHandler.cpp
 *				except/logDataOutput.cpp
 *				except/logDebugOutputHandler.cpp
 *				except/logExternalizable.cpp
 *				except/logFilter.cpp
 *				except/logFormattable.cpp
 *				except/logFormatter.cpp
 *				except/logHandler.cpp
 *				except/logLevel.cpp
 *				except/logLogger.cpp
 *				except/logObjectOutput.cpp
 *				except/logObjectOutputStream.cpp
 *				except/logOutputStreamHandler.cpp
 *				except/logStreamHandler.cpp
 *				except/logTerminalHandler.cpp
 *				except/logXmlFormatter.cpp
 *				except/msgMsgCodeException.cpp
 *				except/msgMsgFormat.cpp
 *				except/usrReport.cpp
 *				except/usrRunning.cpp
 *				except/usrStartup.cpp
 *				except/usrStrategy.cpp
 *				ghash/ghash.cpp
 *				gtable/gtable.cpp
 *				hashtool/hashtool.cpp
 *				icuext/uchar.cpp
 *				icuext/uconv.cpp
 *				icuext/uctype.cpp
 *				icuext/uerror.cpp
 *				icuext/uhash.cpp
 *				icuext/umisc.cpp
 *				icuext/urecognize.cpp
 *				icuext/uspecial.cpp
 *				icuext/ustdio.cpp
 *				icuext/ustring.cpp
 *				icuext/utf.cpp
 *				icuext/utf8str.cpp
 *				icuext/xfacade.cpp
 *				ihash/ihash.cpp
 *				interval/fsi.cpp
 *				lcctype/codeconv.cpp
 *				lcctype/utctype.cpp
 *				lcmgmt/eventhandler.cpp
 *				lcmgmt/lccat.cpp
 *				lcmgmt/lcdata.cpp
 *				lcmgmt/lcdbevthandler.cpp
 *				lcmgmt/lcinit.cpp
 *				lcmgmt/mllocale.cpp
 *				lcmgmt/mllocaleimpl.cpp
 *				lcmgmt/parserhandler.cpp
 *				linebuf/linebuf.cpp
 *				mem/memory_context.cpp
 *				memmgr/freestore.cpp
 *				memmgr/mem32.cpp
 *				memmgr/mem32aligned.cpp
 *				memmgr/memalloc.cpp
 *				memmgr/memcache.cpp
 *				memmgr/memcount.cpp
 *				memmgr/memdebug.cpp
 *				memmgr/memutil.cpp
 *				msg/message_context.cpp
 *				nh/namehash.cpp
 *				nh/symtab.cpp
 *				profile/profile.cpp
 *				sort/qsort.cpp
 *				strbuf/string_buffer.cpp
 *				threads/atomic.cpp
 *				threads/mwatomic.cpp
 *				threads/mwbarrier.cpp
 *				threads/mwconcurrent.cpp
 *				threads/mwcondition.cpp
 *				threads/mwcountedbody.cpp
 *				threads/mwcountedpointer.cpp
 *				threads/mwevent.cpp
 *				threads/mwmonitor.cpp
 *				threads/mwmutex_lwm.cpp
 *				threads/mwmutexlock.cpp
 *				threads/mwobjmgr.cpp
 *				threads/mwpointer.cpp
 *				threads/mwrcrsvmtx.cpp
 *				threads/mwsemaphore.cpp
 *				threads/mwsingleton.cpp
 *				threads/mwthdspc.cpp
 *				threads/mwthread.cpp
 *				threads/mwthreadid.cpp
 *				threads/mwtimeunit.cpp
 *				threads/ut_thread.cpp
 *				tse/tse.cpp
 *				warn/warning_context.cpp
 *				warn/warnmgr.cpp
 *				memmgr/mmm_lexer.cpp
 */

#if defined(_MSC_VER) || __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ > 3)
#pragma once
#endif

#ifndef mwutil_h
#define mwutil_h


/*
 * Copyright 1984-2003 The MathWorks, Inc.
 * All Rights Reserved.
 */



/* Copyright 2003-2006 The MathWorks, Inc. */

/* Only define EXTERN_C if it hasn't been defined already. This allows
 * individual modules to have more control over managing their exports.
 */
#ifndef EXTERN_C

#ifdef __cplusplus
  #define EXTERN_C extern "C"
#else
  #define EXTERN_C extern
#endif

#endif


/* $Revision: 1.16.4.5 $ */

#ifndef msg_typedefs_h
#define msg_typedefs_h

#ifdef __cplusplus
    extern "C" {
#endif

typedef int (*fn_puts)(const char *s, void *x);
typedef void (*fn_void)(void);

#define _element(X) X,

#define ut_define_module_mnemonics(m) \
  enum { m##_START=m##_INDEX<<16, m##_message_mnemonics(_element) m##_END}

#define _message_mnemonic(mnemonic, string) mnemonic,
#define _message_string(mnemonic, string) string,
#define _message_mnemonic_string(mnemonic, string) #mnemonic,

#define _concat(X, Y, Z) X##Y##Z

#define _define_module_tables_(language, table, m) \
static int const _concat(table,_codes_,m)[] \
  = {  _concat(m,language,messages)(_message_mnemonic) -1}; \
static _string const _concat(table,_strings_,m)[] \
  = {  _concat(m,language,messages)(_message_string) };

#define _define_module_code_strings_(language, table, m) \
static _string const _concat(table,_code_strings_,m)[] \
  = {  _concat(m,language,messages)(_message_mnemonic_string) }; \

#define _first(X, Y) X
#define _second(X, Y) Y

#define _define_module_tables(language_and_table, m) \
  _define_module_tables_(_first language_and_table, _second language_and_table, m)
#define _define_module_code_strings(language_and_table, m) \
  _define_module_code_strings_(_first language_and_table, _second language_and_table, m)

#define _table_element_(language, table, m) _concat(table,_strings_,m),

#define _table_element(language_and_table, m) \
  _table_element_(_first language_and_table, _second language_and_table, m)

#define _values_element_(language, table, m) _concat(table,_codes_,m),

#define _values_element(language_and_table, m) \
  _values_element_(_first language_and_table, _second language_and_table, m)

#define _values_string_element_(language, table, m) _concat(table,_code_strings_,m),

#define _values_string_element(language_and_table, m) \
  _values_string_element_(_first language_and_table, _second language_and_table, m)

#define _max_code_element(table, m) m##_END - m##_START - 1,

#define _component_element(table, m) #m


#define _module_element(Y,X) X##_INDEX,

#define ut_define_language_tables(language, table) \
  message_modules(_define_module_tables, (language, table)) \
  static int const table##_modules[] \
    = { message_modules(_module_element, table) -1 }; \
  static _int_table const table##_codes[] \
    = { message_modules(_values_element, (language, table)) }; \
  static _string_table const table##_strings[] \
    = { message_modules(_table_element, (language, table)) }; \
  static int const table##_code_count[] \
    = { message_modules(_max_code_element, table) }

#define ut_define_primary_messages(table) \
  message_module(_define_module_tables,(_,table)) \
  message_module(_define_module_code_strings,(_,table)) \
  static _primary_table const table \
    = { message_module(_max_code_element, table) \
        message_module(_module_element, table) \
        message_module(_values_element,(_,table)) \
        message_module(_values_string_element,(_,table)) \
        message_module(_table_element,(_,table)) \
        message_module(_component_element,(_,table)) }

#define ut_define_secondary_messages(language, table) \
  ut_define_language_tables(_##language##_, table); \
  static _language_table const table \
    = { table##_modules, \
        table##_codes, \
        table##_strings, \
        table##_code_count }

#define msg_INDEX 0
typedef const char *_string;
typedef _string const *_string_table;
typedef int const *_int_table;

typedef struct {
  int const *modules;             /* array of modules associated with this language table */
  _int_table const *codes;        /* array of message code tables associated with this language table */
  _string_table const *strings;   /* array of message strings associated with this language table */
  _int_table code_count;          /* array of the number of messages in each message string table */
} _language_table;

typedef struct {
  int code_count;
  int module;
  _int_table codes;
  _string_table code_strings;
  _string_table strings;
  _string component_string;
} _primary_table;

typedef const _language_table *language_table;
typedef const _primary_table *primary_table;

#include <stddef.h>  /* This has size_t */
#include <stdio.h>   /* required for FILE */
#include <stdarg.h>  /* required for va_list, etc. */

/*
 * _hole_type enumerator identifies the hole type (%s and %U)
 */
typedef enum {
    STANDARD_HOLE_TYPE,          /* ID for the standard hole types */
    STRING_HOLE_TYPE,            /* ID for %s string holes */
    FUNCTION_HOLE_TYPE           /* ID for %U holes */
} _hole_type;

/*
 * _hole_seen enumerator identifes the 'seen' status of a hole
 */
typedef enum {
    HOLE_NOT_SEEN,
    HOLE_SEEN
} _hole_seen;

/*
 * _hole_info - information associated with a hole - char * for a
 * string hole, a va_list for a function hole
 */
typedef struct __hole_info {
    _hole_type   hole_type;      /* the type of this hole */
    union {
	/*
	 * fields used only when adding secondary strings
	 */
        _hole_seen hole_seen;    /* seen status, used to mark this hole as visited */
	
	/*
	 * fields used only when processing messages
	 */
	char    *hole_string;    /* string for %s fields */
	va_list  hole_ap;        /* arglist for %U fields */
    } hole;
} _hole_info;

typedef struct _message_context {
  int highest_module;          /* The maximum used module index for the items in the strings_list */
  int max_module;              /* The current allocation for items in the strings_list */
  int *code_count;
  int *ref_count;              /* reference count for each primary table - must be zero to nullify */
  _string_table *code_strings; /* table with mneumonic code strings */
  _string * component_string;  /* name of component as a string */
  int current_language;        /* The currently active language index */
  int max_holes;
  int max_specification;
  int max_hole_text;
  char *specification;         /* specifications for non-%s fields */
  _hole_info *hole_infos;      /* information for hole fields */
  char *hole_text;             /* text for non-%s fields */
  int secondary_count;
  const char **keys;           /* array of keys for the secondary language tables */
                               /* The 0 index is the primary table,
                                * 1..secondary_count are for secondary languages
                                */
  _string_table **strings_list;
} _message_context, *message_context;

typedef unsigned long message_code;

/* function types */
typedef void *(*fn_malloc)(size_t);
typedef void *(*fn_realloc)(void *p, size_t);
typedef void (*fn_free)(void *p);

/*
 * This is the type of a functional argument to printm.
 * Its job is to "print" a string of n characters (in practice,
 * either to a file or to message buffer).
 * Characters to print _may_ include null bytes!
 */
typedef
int (*fn_putsn)(  /* Returns number of characters printed >= 0, else some error */
  void *x,        /* "Destination" info, e.g., FILE *, or &buffer */
  const char *s,  /* Source string (ptr to chars to print) */ 
  int n           /* Number of chars to print from s */
  );
/*
 * This is the type of a function that asks whether a putsn is "hot",
 * i.e., whether it is capable of handling hot-links to files.
 * The x argument is the same as the x argument to a fn_putsn.
 */
typedef
bool (*fn_is_hot)(
  void *x
  );

/*
 * typedef for the custom format specifier formatting function
 */
typedef
int (*fn_fmtfcn)(      /* returns the number of chars putsn'd after processing*/
  fn_putsn putsn,
  void *x,             /* destination info, e.g., FILE *, or &buffer */
  va_list *ap);        /* var args list to custom format specifier, on return
                          this is advanced past the custom format varargs */

/*
 * Below are a typedef and a function conforming to the fn_puts typedef that 
 * in turn calls a fn_putsn function, stored in the putsn_to_puts_args structure.
 */
typedef struct _putsn_to_puts_args
{
  fn_putsn putsn;
  void *   x;
} _putsn_to_puts_args, * putsn_to_puts_args;

typedef struct _puts_to_putsn_args
{
  fn_puts puts;
  void *   x;
} _puts_to_putsn_args, * puts_to_putsn_args;


typedef void (*fn_handler)( void *x, message_code code, ... );

#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* msg_typedefs_h */


/* $Revision: 1.17.4.7 $ */

#ifndef err_typedefs_h
#define err_typedefs_h

#define err_INDEX 1
#define ERR_NO_ERROR 0

/* types */
#ifdef __cplusplus
extern "C" {
#endif
typedef void (*fn_protectv)(void *);
typedef void (*fn_protectxv)( void *, void *);
#ifdef __cplusplus
}
#endif

#define ut_declare_protect_function(f, t) void (*f)(t)
#define ut_declare_protectx_function(f, t1, t2) void (*f)(t1, t2)

#define _protect_list_common_fields(t) \
  struct _generic_protect_list *next; /* should come first for more efficient reference */ \
  t *p;

#define _protect_list_common( t, t1)  { \
  _protect_list_common_fields(t) \
  ut_declare_protect_function(f, t1); \
}

typedef struct _generic_protect_list _protect_list_common( void *, void *)
  *generic_protect_list;

#define _protect_list(t, t1) struct _protect_list_common( t, t1)

/* The f field is deliberately put in a different position in the the following type,
   to maximize catastrophe if the wrong type is used.  */
#define _protectx_list(t, t1, t2) struct { \
  _protect_list_common_fields(t) \
  t1 x; /* the first argument to f */ \
  ut_declare_protectx_function(f, t1, t2); \
}

typedef _protectx_list(void *, void *, void *) *generic_protectx_list;

#ifdef __cplusplus
extern "C" {
#endif
typedef void (*fn_error_handler)(void *x, const char * id, int code);
#ifdef __cplusplus
}
#endif

typedef struct _error_context {
  generic_protect_list top; /* should come first for more efficient reference */
  struct _try_catch_list *try_catch_top;
  struct _try_catch_list *active_catch;
  message_context msg;
  fn_putsn putsn;
  void *x; /* the first argument to putsn and is_hot */
  fn_is_hot is_hot;
  fn_error_handler error_handler;
  void *xerr; /* The first argument to error_handler */
} _error_context, *error_context;

#ifdef __cplusplus
extern "C" {
#endif
typedef void (*try_function)(error_context err, void *p);
typedef int (*catch_function)(error_context err, void *p, message_code code, va_list ap);
typedef int (*catch_function_id)(error_context err, void *p, const char * id, 
                                 message_code code, va_list ap);
#ifdef __cplusplus
}
#endif

typedef struct _try_catch_list {
  struct _try_catch_list *next;
  generic_protect_list top;
  void *p;
  catch_function catch_fcn;
  catch_function_id catch_fcn_id;
  message_code code;
} _try_catch_list; 
typedef _try_catch_list *try_catch_list;

/* macros */

#define ut_errassertalways(err, condition) (condition) ? (void)0 : ut_fault(err, #condition, __FILE__, __LINE__) 

#ifndef NDEBUG
#define ut_assert_fault(err, condition) ut_fault(err, condition, __FILE__, __LINE__)
#define ut_errassert(err, condition) (condition) ? (void)0 : ut_assert_fault(err, #condition)
#define NNDEBUGC(X) X,
#define NNDEBUG(X) X
#define YNDEBUG(X)
#define YNNDEBUG(X) 
#else
#define ut_assert_fault(err, condition) ((void) err)
#define ut_errassert( err, condition ) ((void) err)
#define NNDEBUGC(X)
#define NNDEBUG(X)
#define YNDEBUG(X) X
#define YNNDEBUG(X) X, 
#endif


#if (defined(DEBUG) || (defined(DEBUG_ERROR_CONTEXT) && DEBUG_ERROR_CONTEXT != 0))
#undef DEBUG_ERROR_CONTEXT
#define DEBUG_ERROR_CONTEXT(X) X
#else
#undef DEBUG_ERROR_CONTEXT
#define DEBUG_ERROR_CONTEXT(X)
#endif

#define _protect_value_common(err, type, value, protectfn, _list, tag)   \
  typedef void (*ut_fn_protect_##tag)(type);                             \
  typedef _list _List##tag;                                              \
  DEBUG_ERROR_CONTEXT(generic_protect_list _local_top##tag;)             \
  _List##tag _error_context_link##tag;                                   \
  _List##tag *_error_context_link##tag##addr = &_error_context_link##tag;\
  _error_context_link##tag.next = (err)->top;                            \
  _error_context_link##tag.p = value;                                    \
  ut_errassert(err, sizeof(type)==sizeof(void *));                       \
  _error_context_link##tag.f = protectfn;

#define _protect_common(err, type, name, value, protectfn, _list, tag)  \
  type name = value;                                                    \
  _protect_value_common(err, type, &name, protectfn, _list, tag)

#define LOCAL_TOP(tag) DEBUG_ERROR_CONTEXT(_local_top##tag =)

#define ut_protect(err, type, name, value, protectfn) {                                 \
  _protect_common(err, type, name, value, protectfn, _protect_list(type, type), name )  \
  (err)->top = LOCAL_TOP(name) (generic_protect_list)_error_context_link##name##addr;

#define ut_protectv(err, type, name, value, protectfn) {                                 \
  _protect_common(err, type, name, value, protectfn, _protect_list(type, void *), name ) \
  (err)->top = LOCAL_TOP(name) (generic_protect_list)_error_context_link##name##addr;

#define ut_protectx(err, type, name, value, protectfn, typex, protectx) {                  \
  _protect_common(err, type, name, value,                                                  \
                  protectfn, _protectx_list(type, typex, type),name)                       \
  _error_context_link##name.x = protectx;                                                  \
  (err)->top                                                                               \
    = LOCAL_TOP(name) (generic_protect_list)((uintptr_t)_error_context_link##name##addr | 1);

#define ut_protectxv(err, type, name, value, protectfn, typex, protectx) {              \
  _protect_common(err, type, name, value,                                               \
                  protectfn, _protectx_list(type, typex, void *), name)                 \
  _error_context_link##name.x = protectx;                                               \
  (err)->top = LOCAL_TOP(name)                                                          \
                 (generic_protect_list)((uintptr_t)_error_context_link##name##addr | 1);

#define ut_protect_value(err, type, value, protectfn) {                                    \
  _protect_value_common(err, type, &(value), protectfn, _protect_list(type, type), value ) \
  (err)->top = LOCAL_TOP(value) (generic_protect_list)_error_context_link##value##addr;

#define ut_protectv_value(err, type, value, protectfn) {                                \
  _protect_value_common(err, type, &(value),                                            \
                        protectfn, _protect_list(type, void *), value )                 \
  (err)->top = LOCAL_TOP(value) (generic_protect_list)_error_context_link##value##addr;

#define ut_protectx_value(err, type, value, protectfn, typex, protectx) {                \
  _protect_value_common(err, type, &(value), protectfn,                                  \
                        _protectx_list(type, typex, type), value)                        \
  _error_context_link##value.x = protectx;                                               \
  (err)->top = LOCAL_TOP(value)                                                          \
                 (generic_protect_list)((uintptr_t)_error_context_link##value##addr | 1);

#define ut_protectxv_value(err, type, value, protectfn, typex, protectx) {               \
  _protect_value_common(err, type, &(value),                                             \
                        protectfn, _protectx_list(type, typex, void *), value)           \
  _error_context_link##value.x = protectx;                                               \
  (err)->top = LOCAL_TOP(value)                                                          \
                 (generic_protect_list)((uintptr_t)_error_context_link##value##addr | 1);

#define ut_protect_value_tag(err, type, value, protectfn, tag) {                         \
  _protect_value_common(err, type, &(value), protectfn, _protect_list(type, type), tag ) \
 (err)->top = LOCAL_TOP(tag) (generic_protect_list)_error_context_link##tag##addr;

#define ut_protectv_value_tag(err, type, value, protectfn, tag) {                          \
  _protect_value_common(err, type, &(value), protectfn, _protect_list(type, void *), tag ) \
  (err)->top = LOCAL_TOP(tag) (generic_protect_list)_error_context_link##tag##addr;

#define ut_protectx_value_tag(err, type, value, protectfn, typex, protectx, tag) {        \
  _protect_value_common(err, type, &(value),                                              \
                        protectfn, _protectx_list(type, typex, type), tag)                \
  _error_context_link##tag.x = protectx;                                                  \
 (err)->top                                                                               \
   = LOCAL_TOP(tag) (generic_protect_list)((uintptr_t)_error_context_link##tag##addr | 1);

#define ut_protectxv_value_tag(err, type, value, protectfn, typex, protectx, tag) {       \
 _protect_value_common(err, type, &(value),                                               \
                       protectfn, _protectx_list(type, typex, void *), tag)               \
 _error_context_link##tag.x = protectx;                                                   \
 (err)->top                                                                               \
   = LOCAL_TOP(tag) (generic_protect_list)((uintptr_t)_error_context_link##tag##addr | 1);

#define ut_cast_to_generic_protectx_list(p) (generic_protectx_list)((uintptr_t)(p) ^ 1)

#define ut_preserve(err,tag) (err)->top = (err)->top->next
#define ut_destroy(err,tag) { \
  register error_context err_ = err; \
  err_->top->f(*(err_->top->p)); \
  ut_preserve(err_,tag); \
  } (void)0
#define ut_preservex(err,tag) (err)->top = (ut_cast_to_generic_protectx_list((err)->top))->next
#define ut_destroyx(err,tag) { \
  register generic_protectx_list px = ut_cast_to_generic_protectx_list((err)->top); \
  (err)->top = px->next; \
  px->f(px->x, *(px->p)); \
  } (void)0

#define _fast_ut_preserve(err,tag)
#define _fast_ut_destroy(err,tag) _error_context_link##tag.f(*_error_context_link##tag.p);
#define _fast_ut_preservex(err,tag)
#define _fast_ut_destroyx(err,tag) \
  _error_context_link##tag.f(_error_context_link##tag.x, *(_error_context_link##tag.p));
#define _incorrect_magic(err,tag) \
  if (_local_top##tag != (err)->top) { \
    (err)->top = _local_top##tag; \
    ut_error(err, INCORRECT_MAGIC, __FILE__, __LINE__); \
  }

#define ut_unprotect_unreachable } 

#define ut_unprotect(err, tag, magic) \
  DEBUG_ERROR_CONTEXT(_incorrect_magic(err,tag)) \
  (err)->top = _error_context_link##tag.next; \
  _fast_##magic(err,tag) \
}

#define ut_unprotect_and_return(err, tag, magic, expr) \
  DEBUG_ERROR_CONTEXT(_incorrect_magic(err,tag)) \
  (err)->top = _error_context_link##tag.next; \
  _fast_##magic(err,tag) \
  return expr; \
}

#define ut_protect_f _error_context_link.f

#define ut_prevent_further_cleanup(err) { \
  _try_catch_list _link; \
  ut_prevent_further_cleanup_fcn(err, &_link);

#define ut_allow_further_cleanup(err) \
  ut_allow_further_cleanup_fcn(err, &_link); \
}
 
#endif /* err_typedefs_h */


/*
 * load library into memory
 */
EXTERN_C void *utLoadLibrary(
    const char	*fullname,	/* _full_ library path name */
    int		*errorStatus	/* return variable for error code */
    );


/*
 * Check whether shared library is loaded without loading it
 * Takes basename. Returns true if the library is loaded 
 */
EXTERN_C bool utIsLibraryLoaded(const char *name);


/*
 * Return handle for already loaded library
 */
EXTERN_C void *utLoadModule(const char *basename);


/*
 * lookup symbol in a loaded library
 */
EXTERN_C void *utFindSymbolInLibrary(
    void        *handle,	/* handle returned by utLoadLibrary */
    const char  *symbol         /* symbol name to look up */
    );


/*
 * unload a previously loaded library
 */
EXTERN_C int utUnloadLibrary(
    void        *handle		/* handle returned by utLoadLibrary */
    );


/*
 * Retrieve last error in dynamic loader utility routines
 */
EXTERN_C const char *utLastLibraryError(void);


/* Macros to implement relational floating point comparisons
 * with zeros when the comparee might be NaN.
 * This is a work around for a PC compiler bug in both Microsoft VC++
 * and WATCOM. 
 * -- CBM, 9/22/97.
 *
 * The comparsion values on the PC when the comparee is a NaN are:
 * 
 *	1. NaN < 0  <== true
 *      2. NaN <= 0 <== true
 *      3. NaN > 0  <== false
 *      4. NaN >= 0 <== false
 *      5. NaN == 0 <== true
 *      6. NaN != 0 <== false
 * 
 * When comparing with NaNs, except the != operation all others should 
 * be false. However, this is not the case on the PC. So we have the 
 * following macros that work around this problem for cases 1,2,5 and 6.
 * -- NBM 9/26/97
 */

/*
 * MSVC++ 7.0 now complies with IEEE rules for comparisons with NaN.
 */
#if defined(_WIN32) && (_MSC_VER < 1300)
#define utNEZero(x) (((x) < 0.0) || ((x) > 0.0))
#define utEQZero(x) (((x) >= 0.0) && ((x) <= 0.0))
#define utLTZero(x) (((x) < 0.0) && !utIsNaN(x))
#define utLEZero(x) (((x) <= 0.0) && !utIsNaN(x))

#else
#define utNEZero(x) ((x) != 0.0)
#define utEQZero(x) ((x) == 0.0)
#define utLTZero(x) ((x) < 0.0)
#define utLEZero(x) ((x) <= 0.0)
#endif

/* Since the > and >= are correct for the NaN case it is
 * outside the ifdef code. Cleve and I decided to add them
 * to maintain the consistency of syntax.
 */
#define utGTZero(x) ((x) > 0.0)
#define utGEZero(x) ((x) >= 0.0)


/*
 * Predicate to determine whether a double is an int.
 * -0 is not considered an int, because converting it back
 * does not yield the same double.
 */
EXTERN_C bool utDblIsInt(double x);




/*
 * Use unique NaNs as flags for special values
 * These values should never be generated by Matlab as valid NaNs.
 *
 * The low-order word is all zeros.
 */

#define UT_SPECIAL_NAN 0x7ff5c5c0

#define UT_NAN_NEVER_TOUCHED (UT_SPECIAL_NAN + 0x1)
#define UT_NAN_FORLOOP_EMPTY (UT_SPECIAL_NAN + 0x2)


#define UT_SET_NAN_VALUE(lval, jqnan) ut_SET_BOTH(lval, jqnan, 0)

/*
 * since the x86 fpu can change the leading mastissa bit on QNaNs, we check for
 * equality with and without the bit set.
 */
#define UT_QNAN_BITMASK 0x00080000
#define UT_IS_NAN_VALUE(val, jqnan)                                                                     \
    (*(((int*)&(val))+(CPU_NUM_FORMAT==FIEEE_BE)) == 0x0 &&                                             \
     (*(((int*)&(val))+(CPU_NUM_FORMAT==FIEEE_LE))|UT_QNAN_BITMASK) == ((jqnan)|UT_QNAN_BITMASK))




# define utAssert(test)              /* do nothing */
# define utAssertStr(test, message)  /* do nothing */
# define utAssertAlways(message)     /* do nothing */

#endif /* mwutil_h */
