#include "objects_list.hpp"

#include <QSignalBlocker>

namespace app::gui {

ObjectsList::ObjectsList(QListWidget* objects_list)
    : objects_list_field_{objects_list},
      objects_list_{[this](const std::vector<ObjectId>& list) { UpdateObjectsList(list); }},
      selected_object_{
          [this](const ObjectId new_object_id) { UpdateSelectedObject(new_object_id); }} {
    {
        assert(objects_list and "ObjectsList: objects_list не должен быть nullptr");
    }
}

ports::PortIn<std::vector<ObjectsList::ObjectId>>* ObjectsList::GetObjectsListPort() {
    return &objects_list_;
}

ports::PortIn<ObjectsList::ObjectId>* ObjectsList::GetObjectPort() {
    return &selected_object_;
}

void ObjectsList::UpdateObjectsList(const std::vector<ObjectId>& new_objects_list) {
    {
        assert(objects_list_field_ and
               "ObjectsList::UpdateObjectsList: objects_list_field_ не должен быть nullptr");
    }
    QSignalBlocker lock(objects_list_field_);
    objects_list_field_->clear();
    for (ssize_t row = 0; row < new_objects_list.size(); ++row) {
        objects_list_field_->insertItem(row, QString::number(new_objects_list[row]));
    }
    if (selected_object_
            .IsSubscribed()) {  // после перезаписи элементов выставить старый выбранный объект
        UpdateSelectedObject(selected_object_.GetData());
    }
}

void ObjectsList::UpdateSelectedObject(const ObjectId new_object_id) {
    {
        assert(objects_list_field_ and
               "ObjectsList::UpdateSelectedObject: objects_list_field_ не должен быть nullptr");
    }
    QSignalBlocker lock(objects_list_field_);
    int selected_row = -1;
    for (int row = 0; row < objects_list_field_->count(); ++row) {
        if (objects_list_field_->item(row)->text() == QString::number(new_object_id)) {
            selected_row = row;
            break;
        }
    }
    if (selected_row !=
        -1) {  // выбранного объекта нет в списке - нет объектов/нет выбранного объекта
        objects_list_field_->setCurrentRow(selected_row);
    }
}

}  // namespace app::gui
