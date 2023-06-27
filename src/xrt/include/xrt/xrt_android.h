// Copyright 2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
/*!
 * @file
 * @brief  Header holding Android-specific instance methods.
 * @author Ryan Pavlik <ryan.pavlik@collabora.com>
 * @ingroup xrt_iface
 */

#pragma once

#include "xrt/xrt_config_os.h"
#include "xrt/xrt_compiler.h"
#include "xrt/xrt_results.h"

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _JavaVM;
struct xrt_instance_android;
struct xrt_instance_info;

/*!
 * Distinguishes the possible Android lifecycle events from each other.
 *
 * Used as a bitmask when registering for callbacks.
 */
enum xrt_android_lifecycle_event
{
	XRT_ANDROID_LIVECYCLE_EVENT_ON_CREATE = 1 << 0,
	XRT_ANDROID_LIVECYCLE_EVENT_ON_DESTROY = 1 << 1,
	XRT_ANDROID_LIVECYCLE_EVENT_ON_PAUSE = 1 << 2,
	XRT_ANDROID_LIVECYCLE_EVENT_ON_RESUME = 1 << 3,
	XRT_ANDROID_LIVECYCLE_EVENT_ON_START = 1 << 4,
	XRT_ANDROID_LIVECYCLE_EVENT_ON_STOP = 1 << 5,
};

/*!
 * A callback type for a handler of Android lifecycle events.
 *
 * Return true to be removed from the callback list.
 */
typedef bool (*xrt_android_lifecycle_event_handler_t)(struct xrt_instance_android *xinst_android,
                                                      enum xrt_android_lifecycle_event event,
                                                      void *userdata);

#ifdef XRT_OS_ANDROID

/*!
 * @interface xrt_instance_android
 *
 * This is an extension of the @ref xrt_instance interface that is used only on Android.
 *
 * @sa ipc_instance_create
 */
struct xrt_instance_android
{

	/*!
	 * @name Interface Methods
	 *
	 * All Android-based implementations of the xrt_instance interface must additionally populate all these function
	 * pointers with their implementation methods. To use this interface, see the helper functions.
	 * @{
	 */
	/*!
	 * Retrieve the stored Java VM instance pointer.
	 *
	 * @note Code consuming this interface should use xrt_instance_android_get_vm()
	 *
	 * @param xinst_android Pointer to self
	 *
	 * @return The VM pointer.
	 */
	struct _JavaVM *(*get_vm)(struct xrt_instance_android *xinst_android);

	/*!
	 * Retrieve the stored activity android.content.Context jobject.
	 *
	 * For usage, cast the return value to jobject - a typedef whose definition
	 * differs between C (a void *) and C++ (a pointer to an empty class)
	 *
	 * @note Code consuming this interface should use xrt_instance_android_get_context()
	 *
	 * @param xinst_android Pointer to self
	 *
	 * @return The activity context.
	 */
	void *(*get_context)(struct xrt_instance_android *xinst_android);

	/*!
	 * Register a activity lifecycle event callback.
	 *
	 * @note Code consuming this interface should use xrt_instance_android_register_activity_lifecycle_callback()
	 *
	 * @param xinst_android Pointer to self
	 * @param callback Function pointer for callback
	 * @param event_mask bitwise-OR of one or more values from @ref xrt_android_lifecycle_event
	 * @param userdata An opaque pointer for use by the callback. Whatever you pass here will be passed to the
	 * callback when invoked.
	 *
	 * @return XRT_SUCCESS on success, other error code on error.
	 */
	xrt_result_t (*register_activity_lifecycle_callback)(struct xrt_instance_android *xinst_android,
	                                                     xrt_android_lifecycle_event_handler_t callback,
	                                                     enum xrt_android_lifecycle_event event_mask,
	                                                     void *userdata);

	/*!
	 * Remove a activity lifecycle event callback that matches the supplied parameters.
	 *
	 * @note Code consuming this interface should use xrt_instance_android_remove_activity_lifecycle_callback()
	 *
	 * @param xinst_android Pointer to self
	 * @param callback Function pointer for callback
	 * @param event_mask bitwise-OR of one or more values from @ref xrt_android_lifecycle_event
	 * @param userdata An opaque pointer for use by the callback. Whatever you pass here will be passed to the
	 * callback when invoked.
	 *
	 * @return XRT_SUCCESS on success, other error code on error.
	 */
	xrt_result_t (*remove_activity_lifecycle_callback)(struct xrt_instance_android *xinst_android,
	                                                   xrt_android_lifecycle_event_handler_t callback,
	                                                   enum xrt_android_lifecycle_event event_mask,
	                                                   void *userdata);

	/*!
	 * Destroy the instance and its owned objects.
	 *
	 * Code consuming this interface should use xrt_instance_android_destroy().
	 *
	 * @param xinst_android Pointer to self
	 */
	void (*destroy)(struct xrt_instance_android *xinst_android);
	/*!
	 * @}
	 */
};

/*!
 * @copydoc xrt_instance_android::get_vm
 *
 * Helper for calling through the function pointer.
 *
 * @public @memberof xrt_instance_android
 */
static inline struct _JavaVM *
xrt_instance_android_get_vm(struct xrt_instance_android *xinst_android)
{
	return xinst_android->get_vm(xinst_android);
}

/*!
 * @copydoc xrt_instance_android::get_context
 *
 * Helper for calling through the function pointer.
 *
 * @public @memberof xrt_instance_android
 */
static inline void *
xrt_instance_android_get_context(struct xrt_instance_android *xinst_android)
{
	return xinst_android->get_context(xinst_android);
}

/*!
 * @copydoc xrt_instance_android::register_activity_lifecycle_callback
 *
 * Helper for calling through the function pointer.
 *
 * @public @memberof xrt_instance_android
 */
static inline xrt_result_t
xrt_instance_android_register_activity_lifecycle_callback(struct xrt_instance_android *xinst_android,
                                                          xrt_android_lifecycle_event_handler_t callback,
                                                          enum xrt_android_lifecycle_event event_mask,
                                                          void *userdata)
{
	return xinst_android->register_activity_lifecycle_callback(xinst_android, callback, event_mask, userdata);
}

/*!
 * @copydoc xrt_instance_android::remove_activity_lifecycle_callback
 *
 * Helper for calling through the function pointer.
 *
 * @public @memberof xrt_instance_android
 */
static inline xrt_result_t
xrt_instance_android_remove_activity_lifecycle_callback(struct xrt_instance_android *xinst_android,
                                                        xrt_android_lifecycle_event_handler_t callback,
                                                        enum xrt_android_lifecycle_event event_mask,
                                                        void *userdata)
{
	return xinst_android->remove_activity_lifecycle_callback(xinst_android, callback, event_mask, userdata);
}

/*!
 * @copydoc xrt_instance_android::destroy
 *
 * Helper for calling through the function pointer.
 *
 * @public @memberof xrt_instance_android
 */
static inline void
xrt_instance_android_destroy(struct xrt_instance_android **xinst_android_ptr)
{
	struct xrt_instance_android *xinst_android = *xinst_android_ptr;
	if (xinst_android == NULL) {
		return;
	}

	xinst_android->destroy(xinst_android);
	*xinst_android_ptr = NULL;
}

/*!
 * @name Factory
 * @{
 */
/*!
 * Create an implementation of the xrt_instance_android interface.
 *
 * @param[in] ii A pointer to xrt_instance_info.
 * @param[out] out_inst_android A pointer to an xrt_instance_android pointer. Will be
 * populated.
 *
 * @return XRT_SUCCESS on success, other error code on error.
 *
 * @relates xrt_instance_android
 */
xrt_result_t
xrt_instance_android_create(struct xrt_instance_info *ii, struct xrt_instance_android **out_xinst_android);
/*!
 * @}
 */

#endif // XRT_OS_ANDROID

#ifdef __cplusplus
}
#endif
