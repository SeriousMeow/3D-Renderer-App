#include "view.hpp"

namespace app {

View::View(QLabel* render_region) : render_region_{render_region} {
    {
        assert(render_region and "View: render_region не может быть nullptr");
    }
}

void View::Draw(const renderer::Image& image) {
    {
        assert(render_region_ and "View: render_region не может быть nullptr");
        assert((image.GetWidth() == render_region_->size().width()) and
               "Draw: ширина изображения не совпадает с шириной области отрисовки");
        assert((image.GetHeight() == render_region_->size().height()) and
               "Draw: высота изображения не совпадает с высотой области отрисовки");
    }
    QImage intermediate_image{static_cast<int>(image.GetWidth()),
                              static_cast<int>(image.GetHeight()), QImage::Format_RGB32};

    // Изображения имеют одинаковый размер, нужно сконвертировать пиксели одного в другое
    // Чтобы избавиться от проверок со стороны Qt, запись идет сразу во внутреннюю память
    // Для Format_RGB32 пиксели хранятся строками сверху вниз
    QRgb* intermediate_data = reinterpret_cast<QRgb*>(intermediate_image.bits());
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            const renderer::Image::Pixel pixel = image.GetPixel(x, y);
            intermediate_data[y * image.GetWidth() + x] =
                qRgb(static_cast<int>(pixel.r * 225), static_cast<int>(pixel.g * 225),
                     static_cast<int>(pixel.b * 225));
        }
    }
    QPixmap output;
    render_region_->setPixmap(output.fromImage(intermediate_image));
}

}  // namespace app
