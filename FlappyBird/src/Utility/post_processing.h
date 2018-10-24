#ifndef POST_PROCESSING_H
#define POST_PROCESSING_H

#include "raylib.h"

namespace flappybird {
	namespace postprocessing {

		enum PostproShader {
			FX_GRAYSCALE = 0,
			FX_POSTERIZATION,
			FX_DREAM_VISION,
			FX_PIXELIZER,
			FX_CROSS_HATCHING,
			FX_CROSS_STITCHING,
			FX_PREDATOR_VIEW,
			FX_SCANLINES,
			FX_FISHEYE,
			FX_SOBEL,
			FX_BLOOM,
			FX_BLUR,
			FX_FXAA
		};

		void init();
		void draw();
		void deInit();
	}
}
#endif // !POST_PROCESSING_H