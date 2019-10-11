// ======================================================================== //
// Copyright 2009-2019 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#include "ManagedObject.h"

namespace ospray {
  namespace cpp {

    class Data : public ManagedObject<OSPData, OSP_DATA>
    {
     public:
      Data(size_t numItems,
           OSPDataType format,
           const void *init = nullptr,
           bool isShared    = false);
      template <typename T, OSPDataType TY>
      Data(ManagedObject<T, TY> obj);
      Data(OSPData existing = nullptr);
    };

    static_assert(sizeof(Data) == sizeof(OSPData),
                  "cpp::Data can't have data members!");

    // Inlined function definitions ///////////////////////////////////////////

    inline Data::Data(size_t numItems,
                      OSPDataType format,
                      const void *init,
                      bool isShared)
    {
      if (isShared) {
        ospObject = ospNewSharedData(init, format, numItems);
      } else {
        ospObject = ospNewData(format, numItems);
        auto tmp  = ospNewSharedData(init, format, numItems);
        ospCopyData(tmp, ospObject);
        ospRelease(tmp);
      }
    }

    template <typename T, OSPDataType TY>
    inline Data::Data(ManagedObject<T, TY> obj) : Data(1, TY, &obj)
    {
    }

    inline Data::Data(OSPData existing)
        : ManagedObject<OSPData, OSP_DATA>(existing)
    {
    }

  }  // namespace cpp
}  // namespace ospray
