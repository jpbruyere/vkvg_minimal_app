#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <vkvg.h>
#include "vkengine.h"

static VkSampleCountFlags samples = VK_SAMPLE_COUNT_8_BIT;
static uint32_t width=800, height=600;
static bool paused = false;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action != GLFW_PRESS)
		return;
	switch (key) {
	case GLFW_KEY_SPACE:
		 paused = !paused;
		break;
	case GLFW_KEY_ESCAPE :
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	}
}

void draw (VkvgContext ctx) {
	//vkvg_rotate(ctx, 0.3);
	vkvg_set_source_rgb(ctx,0.1,0.1,0.1);
	vkvg_paint (ctx);

	vkvg_set_font_size(ctx,16);
	const char* text = "Hello World\0";
	vkvg_font_extents_t fe;
	vkvg_font_extents (ctx, &fe);
	vkvg_text_extents_t te;
	vkvg_text_extents (ctx, text, &te);

	float x = 100, y = 100;
	vkvg_rectangle(ctx, x, y - fe.ascent, te.width, te.height);
	vkvg_set_source_rgb(ctx,0.2,0.1,0.0);
	vkvg_fill_preserve(ctx);
	vkvg_set_source_rgb(ctx,1.0,1.0,1.0);
	vkvg_stroke(ctx);
	vkvg_move_to(ctx,x,y);
	vkvg_set_source_rgb(ctx,0.1,0.8,0.8);
	vkvg_show_text(ctx,text);
}

int main(){
	VkEngine e = vkengine_create (VK_PRESENT_MODE_MAILBOX_KHR, width, height);
	vkengine_set_key_callback (e, key_callback);
	VkvgDevice dev = vkvg_device_create_multisample(vkh_app_get_inst(e->app),
			 vkengine_get_physical_device(e), vkengine_get_device(e), vkengine_get_queue_fam_idx(e), 0, samples, false);
	VkvgSurface surf = vkvg_surface_create(dev, width, height);

	vkh_presenter_build_blit_cmd (e->renderer, vkvg_surface_get_vk_image(surf), width, height);

	while (!vkengine_should_close (e)) {
		glfwPollEvents();

		if (!vkh_presenter_draw (e->renderer)){
			vkh_presenter_get_size (e->renderer, &width, &height);
			vkvg_surface_destroy (surf);
			surf = vkvg_surface_create(dev, width, height);
			vkh_presenter_build_blit_cmd (e->renderer, vkvg_surface_get_vk_image(surf), width, height);
			vkengine_wait_idle(e);
			continue;
		}
		VkvgContext ctx = vkvg_create(surf);
		draw (ctx);
		vkvg_destroy(ctx);
	}
	vkvg_surface_destroy(surf);
	vkvg_device_destroy(dev);
	vkengine_destroy(e);
}
