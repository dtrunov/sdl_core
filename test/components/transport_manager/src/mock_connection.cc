/*
 * \file mock_connection.cc
 * \brief
 *
 * Copyright (c) 2013, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "transport_manager/mock_connection.h"

#include <algorithm>

#include "transport_manager/mock_device_adapter.h"

namespace test {
namespace components {
namespace transport_manager {

MockConnection::MockConnection(const DeviceHandle& device_handle,
                               const ApplicationHandle& app_handle,
                               MockDeviceAdapter* adapter)
    : adapter_(adapter),
      device_handle_(device_handle),
      app_handle_(app_handle) {}

DeviceAdapter::Error MockConnection::sendData(RawMessageSptr message) {
  return DeviceAdapter::OK;
}

DeviceAdapter::Error MockConnection::disconnect() {
  ::std::pair<DeviceHandle, ApplicationHandle> connection =
      ::std::make_pair(device_handle_, app_handle_);
  if (::std::find(adapter_->connections_.begin(),
                  adapter_->connections_.end(),
                  connection) != adapter_->connections_.end()) {
//    adapter_->connections_.erase(con);
    adapter_->disconnectDone(device_handle_, app_handle_);
//      if (::std::find_if(adapter_->connections_.begin(),
//                         adapter_->connections_.end()))
    adapter_->disconnectDevice(device_handle_);
  } else {
    // TODO: add disconnect failed
  }
  return DeviceAdapter::OK;
}

}  // namespace transport_manager
}  // namespace components
}  // namespace test
