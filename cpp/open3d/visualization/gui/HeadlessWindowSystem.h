// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2020 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#pragma once

#include <functional>
#include <memory>

#include "open3d/visualization/gui/WindowSystem.h"

namespace open3d {

namespace geometry {
class Image;
}  // namespace geometry

namespace visualization {
namespace gui {

struct MouseEvent;
struct KeyEvent;
struct TextInputEvent;

class HeadlessWindowSystem : public WindowSystem {
public:
    HeadlessWindowSystem();
    ~HeadlessWindowSystem();

    void Initialize() override;
    void Uninitialize() override;

    using OnDrawCallback =
            std::function<void(Window*, std::shared_ptr<geometry::Image>)>;
    void SetOnWindowDraw(OnDrawCallback callback);

    void WaitEventsTimeout(double timeout_secs) override;

    OSWindow CreateWindow(Window* o3d_window,
                          int width,
                          int height,
                          const char* title,
                          int flags) override;
    void DestroyWindow(OSWindow w) override;

    Size GetScreenSize(OSWindow w) override;

    void PostRedrawEvent(OSWindow w) override;
    void PostMouseEvent(OSWindow w, const MouseEvent& e);
    void PostKeyEvent(OSWindow w, const KeyEvent& e);
    void PostTextInputEvent(OSWindow w, const TextInputEvent& e);

    bool GetWindowIsVisible(OSWindow w) const override;
    void ShowWindow(OSWindow w, bool show) override;

    void RaiseWindowToTop(OSWindow w) override;
    bool IsActiveWindow(OSWindow w) const override;

    Point GetWindowPos(OSWindow w) const override;
    void SetWindowPos(OSWindow w, int x, int y) override;

    Size GetWindowSize(OSWindow w) const override;
    void SetWindowSize(OSWindow w, int width, int height) override;

    Size GetWindowSizePixels(OSWindow w) const override;
    void SetWindowSizePixels(OSWindow w, const Size& size) override;

    float GetWindowScaleFactor(OSWindow w) const override;

    void SetWindowTitle(OSWindow w, const char* title) override;

    Point GetMousePosInWindow(OSWindow w) const override;
    int GetMouseButtons(OSWindow w) const override;

    void CancelUserClose(OSWindow w) override;

    void* GetNativeDrawable(OSWindow w) override;

    rendering::FilamentRenderer* CreateRenderer(OSWindow w) override;

    void ResizeRenderer(OSWindow w,
                        rendering::FilamentRenderer* renderer) override;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}  // namespace gui
}  // namespace visualization
}  // namespace open3d
