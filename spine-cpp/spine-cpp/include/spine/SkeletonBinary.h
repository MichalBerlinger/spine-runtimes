/******************************************************************************
 * Spine Runtimes Software License v2.5
 *
 * Copyright (c) 2013-2016, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable, and
 * non-transferable license to use, install, execute, and perform the Spine
 * Runtimes software and derivative works solely for personal or internal
 * use. Without the written permission of Esoteric Software (see Section 2 of
 * the Spine Software License Agreement), you may not (a) modify, translate,
 * adapt, or develop new applications using the Spine Runtimes or otherwise
 * create derivative works or improvements of the Spine Runtimes or (b) remove,
 * delete, alter, or obscure any trademarks or any copyright, trademark, patent,
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
 * USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef Spine_SkeletonBinary_h
#define Spine_SkeletonBinary_h

#include <spine/TransformMode.h>
#include <spine/Vector.h>

#include <string>

namespace Spine {
    class SkeletonData;
    class Atlas;
    class AttachmentLoader;
    class LinkedMesh;
    class Skin;
    class Attachment;
    class VertexAttachment;
    class Animation;
    class CurveTimeline;
    
    class SkeletonBinary {
    public:
        static const int BONE_ROTATE;
        static const int BONE_TRANSLATE;
        static const int BONE_SCALE;
        static const int BONE_SHEAR;
        
        static const int SLOT_ATTACHMENT;
        static const int SLOT_COLOR;
        static const int SLOT_TWO_COLOR;
        
        static const int PATH_POSITION;
        static const int PATH_SPACING;
        static const int PATH_MIX;
        
        static const int CURVE_LINEAR;
        static const int CURVE_STEPPED;
        static const int CURVE_BEZIER;
        
        static const TransformMode TRANSFORM_MODE_VALUES[5];
        
        SkeletonBinary(Vector<Atlas*>& atlasArray);
        
        SkeletonBinary(AttachmentLoader* attachmentLoader);
        
        ~SkeletonBinary();
        
        SkeletonData* readSkeletonData(const unsigned char* binary, const int length);
        
        SkeletonData* readSkeletonDataFile(const char* path);
        
    private:
        struct DataInput {
            const unsigned char* cursor;
            const unsigned char* end;
        };
        
        AttachmentLoader* _attachmentLoader;
        Vector<LinkedMesh*> _linkedMeshes;
        std::string _error;
        float _scale;
        const bool _ownsLoader;
        
        void setError(const char* value1, const char* value2);
        
        char* readString(DataInput* input);
        
        float readFloat(DataInput* input);
        
        unsigned char readByte(DataInput* input);
        
        signed char readSByte(DataInput* input);
        
        int readBoolean(DataInput* input);
        
        int readInt(DataInput* input);
        
        void readColor(DataInput* input, float *r, float *g, float *b, float *a);
        
        int readVarint(DataInput* input, bool optimizePositive);
        
        Skin* readSkin(DataInput* input, const char* skinName, SkeletonData* skeletonData, bool nonessential);
        
        Attachment* readAttachment(DataInput* input, Skin* skin, int slotIndex, const char* attachmentName, SkeletonData* skeletonData, bool nonessential);
        
        void readVertices(DataInput* input, VertexAttachment* attachment, int vertexCount);
        
        Vector<float> readFloatArray(DataInput *input, int n, float scale);
        
        Vector<short> readShortArray(DataInput *input);
        
        Animation* readAnimation(const char* name, DataInput* input, SkeletonData *skeletonData);
        
        void readCurve(DataInput* input, int frameIndex, CurveTimeline* timeline);
    };
}

#endif /* Spine_SkeletonBinary_h */