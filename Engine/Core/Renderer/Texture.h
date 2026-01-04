#pragma once

#include "pch.h"

namespace Gnote {
class GNOTE_API Texture {
public:
  virtual ~Texture() = default;

  virtual void Bind(uint32_t slot = 0) const = 0;
  virtual void Unbind() const = 0;
  virtual int32_t GetWidth() = 0;
  virtual int32_t GetHeight() = 0;
  virtual int32_t GetChannels() = 0;
  virtual void SetData(void *data, uint32_t size) = 0;

private:
};

class Texture2D : public Texture {
public:
  static Ref<Texture2D> Create(const std::string &filePath);
  static Ref<Texture2D> Create(uint32_t width, uint32_t height);

private:
};
} // namespace Gnote
