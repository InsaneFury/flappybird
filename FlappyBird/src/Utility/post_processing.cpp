#include "post_processing.h"

namespace flappybird {
	namespace postprocessing {

#define GLSL_VERSION 330

#define MAX_POSTPRO_SHADERS 12

		static const char *postproShaderText[] = {
			"GRAYSCALE",
			"POSTERIZATION",
			"DREAM_VISION",
			"PIXELIZER",
			"CROSS_HATCHING",
			"CROSS_STITCHING",
			"PREDATOR_VIEW",
			"SCANLINES",
			"FISHEYE",
			"SOBEL",
			"BLOOM",
			"BLUR",
			"FXAA"
		};

		Shader shaders[MAX_POSTPRO_SHADERS];
		int currentShader = FX_BLOOM;

		void init() {
		// Load all postpro shaders
		// NOTE 1: All postpro shader use the base vertex shader (DEFAULT_VERTEX_SHADER)
		// NOTE 2: We load the correct shader depending on GLSL version

			// NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
			shaders[FX_GRAYSCALE] = LoadShader(0, FormatText("res/shaders/glsl330/grayscale.fs", GLSL_VERSION));
			shaders[FX_POSTERIZATION] = LoadShader(0, FormatText("res/shaders/glsl330/posterization.fs", GLSL_VERSION));
			shaders[FX_DREAM_VISION] = LoadShader(0, FormatText("res/shaders/glsl330/dream_vision.fs", GLSL_VERSION));
			shaders[FX_PIXELIZER] = LoadShader(0, FormatText("res/shaders/glsl330/pixelizer.fs", GLSL_VERSION));
			shaders[FX_CROSS_HATCHING] = LoadShader(0, FormatText("res/shaders/glsl330/cross_hatching.fs", GLSL_VERSION));
			shaders[FX_CROSS_STITCHING] = LoadShader(0, FormatText("res/shaders/glsl330/cross_stitching.fs", GLSL_VERSION));
			shaders[FX_PREDATOR_VIEW] = LoadShader(0, FormatText("res/shaders/glsl330/predator.fs", GLSL_VERSION));
			shaders[FX_SCANLINES] = LoadShader(0, FormatText("res/shaders/glsl330/scanlines.fs", GLSL_VERSION));
			shaders[FX_FISHEYE] = LoadShader(0, FormatText("res/shaders/glsl330/fisheye.fs", GLSL_VERSION));
			shaders[FX_SOBEL] = LoadShader(0, FormatText("res/shaders/glsl330/sobel.fs", GLSL_VERSION));
			shaders[FX_BLOOM] = LoadShader(0, FormatText("res/shaders/glsl330/bloom.fs", GLSL_VERSION));
			shaders[FX_BLUR] = LoadShader(0, FormatText("res/shaders/glsl330/blur.fs", GLSL_VERSION));	
			shaders[FX_FXAA] = LoadShader(0, FormatText("res/shaders/glsl330/fxaa.fs", GLSL_VERSION));
		}

		//--------------------------------------------------------------------------------------
		void draw() {
			// Render previously generated texture using selected postpro shader
			BeginShaderMode(shaders[currentShader]);	
		}
		
		void deInit() {
			// Unload all postpro shaders
			for (int i = 0; i < MAX_POSTPRO_SHADERS; i++) {
				UnloadShader(shaders[i]);
			}
		}
	}
}