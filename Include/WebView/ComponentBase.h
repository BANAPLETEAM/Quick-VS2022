// Copyright (C) Microsoft Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "stdafx.h"

#include <afx.h>
#include <wil/com.h>
#include <wrl.h>

#include "WebView2EnvironmentOptions.h"
#include "WebView2.h"

class ComponentBase
{
public:
    // *result defaults to 0
    virtual bool HandleWindowMessage(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam,
        LRESULT* result)
    {
        return false;
    }
    virtual ~ComponentBase() { }
};
