// Copyright 2020-2023, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
// Author: Rylie Pavlik <rylie.pavlik@collabora.com>
// Inline implementations: do not include on its own!

#pragma once

#include "android.content.h"
#include "java.util.h"
#include <string>

namespace wrap {
namespace android::content::pm {
inline os::Bundle PackageItemInfo::getMetaData() const {
    assert(!isNull());
    return get(Meta::data().metaData, object());
}

inline std::string PackageItemInfo::getName() const {
    assert(!isNull());
    return get(Meta::data().name, object());
}

inline std::string PackageItemInfo::getPackageName() const {
    assert(!isNull());
    return get(Meta::data().packageName, object());
}

inline ApplicationInfo ComponentInfo::getApplicationInfo() const {
    assert(!isNull());
    return get(Meta::data().applicationInfo, object());
}

inline std::string ApplicationInfo::getNativeLibraryDir() const {
    assert(!isNull());
    return get(Meta::data().nativeLibraryDir, object());
}

inline std::string ApplicationInfo::getPublicSourceDir() const {
    assert(!isNull());
    return get(Meta::data().publicSourceDir, object());
}

inline ApplicationInfo PackageInfo::getApplicationInfo() const {
    assert(!isNull());
    return get(Meta::data().applicationInfo, object());
}

inline std::string PackageInfo::getPackageName() const {
    assert(!isNull());
    return get(Meta::data().packageName, object());
}

inline std::string Signature::toCharsString() const {
    assert(!isNull());
    return object().call<std::string>(Meta::data().toCharsString);
}

inline Signature PackageInfo::getSignature() const {
    assert(!isNull());
    jobject signatures_obj = jni::env()->GetObjectField(object().getHandle(), Meta::data().signaturesId);
    jobjectArray signatures_array = reinterpret_cast<jobjectArray>(signatures_obj);
    jobject signature_obj = jni::env()->GetObjectArrayElement(signatures_array, 0);
    return Signature(signature_obj);
}

inline ServiceInfo ResolveInfo::getServiceInfo() const {
    assert(!isNull());
    return get(Meta::data().serviceInfo, object());
}

inline PackageInfo PackageManager::getPackageInfo(std::string const &name,
                                                  int32_t flags) {
    assert(!isNull());
    return PackageInfo(
        object().call<jni::Object>(Meta::data().getPackageInfo, name, flags));
}

inline ApplicationInfo
PackageManager::getApplicationInfo(std::string const &packageName,
                                   int32_t flags) {
    assert(!isNull());
    return ApplicationInfo(object().call<jni::Object>(
        Meta::data().getApplicationInfo, packageName, flags));
}

inline java::util::List
PackageManager::queryIntentServices(Intent const &intent, int32_t flags) {
    assert(!isNull());
    return java::util::List(object().call<jni::Object>(
        Meta::data().queryIntentServices, intent.object(), flags));
}

} // namespace android::content::pm
} // namespace wrap
