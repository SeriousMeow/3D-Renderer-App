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
    const renderer::Image::Pixel* image_data = image.AccessData();
    for (size_t i = 0; i < image.GetHeight() * image.GetWidth(); ++i) {
        intermediate_data[i] = qRgb(image_data[i].r, image_data[i].g, image_data[i].b);
    }
    QPixmap output;
    render_region_->setPixmap(output.fromImage(intermediate_image));
}

}  // namespace app
