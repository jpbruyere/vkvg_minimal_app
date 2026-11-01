#include <vkvg.h>

static uint32_t width = 800, height = 600;

int main() {
    vkvg_device_create_info_t info = {0};

    VkvgDevice dev = vkvg_device_create(&info);
    VkvgSurface surf = vkvg_surface_create(dev, width, height);
    VkvgContext ctx = vkvg_create(surf);
    vkvg_set_source_rgb(ctx, 0.5, 0.5, 0.3);
    vkvg_paint(ctx);
    vkvg_destroy(ctx);
    vkvg_surface_write_to_png(surf, "test.png");
    vkvg_surface_destroy(surf);
    vkvg_device_destroy(dev);
}

