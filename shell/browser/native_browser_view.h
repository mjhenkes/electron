// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_BROWSER_NATIVE_BROWSER_VIEW_H_
#define ELECTRON_SHELL_BROWSER_NATIVE_BROWSER_VIEW_H_

#include <vector>

#include "base/memory/raw_ptr.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_observer.h"
#include "third_party/skia/include/core/SkColor.h"

namespace gfx {
class Rect;
}

namespace electron {

enum AutoResizeFlags {
  kAutoResizeWidth = 0x1,
  kAutoResizeHeight = 0x2,
  kAutoResizeHorizontal = 0x4,
  kAutoResizeVertical = 0x8,
};

class InspectableWebContents;
class InspectableWebContentsView;

class NativeBrowserView : public content::WebContentsObserver {
 public:
  ~NativeBrowserView() override;

  // disable copy
  NativeBrowserView(const NativeBrowserView&) = delete;
  NativeBrowserView& operator=(const NativeBrowserView&) = delete;

  static NativeBrowserView* Create(
      InspectableWebContents* inspectable_web_contents);

  InspectableWebContents* GetInspectableWebContents() {
    return inspectable_web_contents_;
  }

  InspectableWebContentsView* GetInspectableWebContentsView();

  virtual void SetAutoResizeFlags(uint8_t flags) = 0;
  virtual void SetBounds(const gfx::Rect& bounds) = 0;
  virtual gfx::Rect GetBounds() = 0;
  virtual void SetBackgroundColor(SkColor color) = 0;

 protected:
  explicit NativeBrowserView(InspectableWebContents* inspectable_web_contents);
  // content::WebContentsObserver:
  void WebContentsDestroyed() override;

  raw_ptr<InspectableWebContents> inspectable_web_contents_;
};

}  // namespace electron

#endif  // ELECTRON_SHELL_BROWSER_NATIVE_BROWSER_VIEW_H_
