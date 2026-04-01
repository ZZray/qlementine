// SPDX-FileCopyrightText: Olivier Cléro <oclero@hotmail.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <QBitmap>
#include <QEvent>
#include <QIcon>
#include <QMouseEvent>
#include <QPixmap>
#include <QSizeF>
#include <QVariant>
#include <QtGlobal>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QEnterEvent>
#endif

namespace oclero::qlementine {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
using EnterEvent = QEnterEvent;
#else
using EnterEvent = QEvent;
#endif

inline QPointF mouseEventPosition(const QMouseEvent* event) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  return event->position();
#else
  return event->localPos();
#endif
}

inline QSizeF pixmapDeviceIndependentSize(const QPixmap& pixmap) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  return pixmap.deviceIndependentSize();
#else
  const auto pixelRatio = pixmap.devicePixelRatio();
  if (pixelRatio <= 0.) {
    return QSizeF{ pixmap.size() };
  }
  return QSizeF{ pixmap.width() / pixelRatio, pixmap.height() / pixelRatio };
#endif
}

inline bool isDevicePixelRatioChangeEvent(const QEvent::Type type) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  return type == QEvent::DevicePixelRatioChange;
#else
  Q_UNUSED(type);
  return false;
#endif
}

inline int variantTypeId(const QVariant& variant) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  return variant.typeId();
#else
  return variant.userType();
#endif
}

inline QPixmap iconPixmap(
  const QIcon& icon, const QSize& size, qreal devicePixelRatio, QIcon::Mode mode, QIcon::State state = QIcon::Off) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  return icon.pixmap(size, devicePixelRatio, mode, state);
#else
  const auto pixmapSize = QSize{
    qMax(1, qRound(size.width() * devicePixelRatio)),
    qMax(1, qRound(size.height() * devicePixelRatio)),
  };
  auto pixmap = icon.pixmap(pixmapSize, mode, state);
  pixmap.setDevicePixelRatio(devicePixelRatio);
  return pixmap;
#endif
}

inline QBitmap bitmapFromPixmap(const QPixmap& pixmap) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  return QBitmap::fromPixmap(pixmap);
#else
  return QBitmap{ pixmap };
#endif
}
} // namespace oclero::qlementine
