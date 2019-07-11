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

#include "ImageOp.h"

namespace ospray {

  /*! The debug TileOp just dumps the input tiles out as PPM files,
     with some optional filename prefix. It can also add a color to the
     tile which will be passed down the pipeline after it, for testing
     the tile pipeline itself.
     To combine the output tiles into a single
     image you can use ImageMagick's montage command:
     montage `ls *.ppm | sort -V` -geometry +0+0 -tile MxN out.jpg
     where M is the number of tiles along X, and N the number of tiles along Y
   */
  struct OSPRAY_SDK_INTERFACE DebugTileOp : public TileOp
  {
    void commit() override;

    std::unique_ptr<LiveImageOp> attach(FrameBufferView &fbView) override;

    std::string toString() const override;

    std::string prefix;
    vec3f addColor;
  };

  struct OSPRAY_SDK_INTERFACE LiveDebugTileOp : public LiveTileOp
  {
    LiveDebugTileOp(FrameBufferView &fbView,
                    const std::string &prefix,
                    const vec3f &addColor);

    void process(Tile &t) override;

    std::string prefix;
    vec3f addColor;
  };
}

