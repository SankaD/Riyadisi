/*
 * @(#)mwservices.h    generated by: makeheader 5.1.5  Wed Jan 23 21:50:15 2008
 *
 *		built from:	../../src/include/copyright.h
 *				../../src/include/pragma_interface.h
 *				config/license.cpp
 *				config/machine_config.cpp
 *				config/prefs.cpp
 *				container/cat.cpp
 *				container/feature_onoff.cpp
 *				container/manager.cpp
 *				container/mfile_reader.cpp
 *				container/mpath_layer.cpp
 *				container/rfsm.cpp
 *				container/std.cpp
 *				distcomp/distcomp.cpp
 *				eventqueue/UserEventQueue.cpp
 *				io/CmdWinSink.cpp
 *				io/CmdWinSinkFactory.cpp
 *				io/CmdWinSinkHandle.cpp
 *				io/MLNoOutputSink.cpp
 *				io/MLNoOutputStreamBuffer.cpp
 *				io/MLPushDefaultSink.cpp
 *				io/MLSink.cpp
 *				io/MLSinkBase.cpp
 *				io/MLStream.cpp
 *				io/MLStringSink.cpp
 *				io/capturebuf.cpp
 *				io/cdroot.cpp
 *				io/efopen.cpp
 *				io/filedir.cpp
 *				io/filestat.cpp
 *				io/history_date.cpp
 *				io/iocbk.cpp
 *				io/iofun.cpp
 *				io/ioprintf.cpp
 *				io/isdos.cpp
 *				io/keybrd.cpp
 *				io/pathset.cpp
 *				io/printca.cpp
 *				io/printmat.cpp
 *				io/printnd.cpp
 *				io/prtopaq.cpp
 *				io/prtstruc.cpp
 *				io/readline.cpp
 *				io/strserv.cpp
 *				io/uctrans.cpp
 *				io/xlate.cpp
 *				lmgr/CheckoutBlocker.cpp
 *				lmgr/LMAttrList.cpp
 *				lmgr/ProcessMutex.cpp
 *				lmgr/VendorString.cpp
 *				lmgr/activation.cpp
 *				lmgr/charconversion.cpp
 *				lmgr/lmgr.cpp
 *				lmgr/lmgrbusyreg.cpp
 *				lmgr/lmgrerror.cpp
 *				lmgr/lmgrtimer.cpp
 *				lmgr/lmisbusyobj.cpp
 *				lmgr/lmisbusyvector.cpp
 *				lmgr/lmlogobj.cpp
 *				mat_thread_req/request_queue.cpp
 *				state/feature.cpp
 *				state/memcounters.cpp
 *				state/mlcharset.cpp
 *				state/mllang.cpp
 *				state/mlmode.cpp
 *				state/mlruntime.cpp
 *				state/mlterm.cpp
 *				state/mlver.cpp
 *				state/nthreads.cpp
 *				state/shutdown_object.cpp
 *				state/sighndl.cpp
 *				state/stcbk.cpp
 *				state/javasup.cpp
 */

#if defined(_MSC_VER) || __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ > 3)
#pragma once
#endif

#ifndef mwservices_h
#define mwservices_h


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

#endif /* mwservices_h */
