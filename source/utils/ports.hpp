/**
 * @file
 * @brief Реализация интерфеса Observer - Observable
 */

#pragma once

#include <functional>
#include <list>
#include <type_traits>
namespace app {

namespace ports {

/**
 * @brief Передача по значению
 */
struct PassByValue;

/**
 * @brief Передача по ссылке
 */
struct PassByReference;

namespace detail {

template <class DataType>
bool constexpr kIsSimpleType =
    std::is_arithmetic_v<DataType> or std::is_pointer_v<DataType> or std::is_enum_v<DataType>;

template <class DataType, class PassMethod>
struct PassTypeImpl;

template <class DataType>
struct PassTypeImpl<DataType, PassByValue> {
    using Type = DataType;
};

template <class DataType>
struct PassTypeImpl<DataType, PassByReference> {
    using Type = const DataType&;
};

/**
 * @brief Тип передаваемого значения
 *
 * @tparam DataType Тип хранимого значения
 * @tparam PassMethod Метод передачи (по значению или по ссылке)
 */
template <class DataType, class PassMethod>
using PassType = typename PassTypeImpl<DataType, PassMethod>::Type;

template <bool TypeFlag>
struct AutoPassTypeImpl;

template <>
struct AutoPassTypeImpl<true> {
    using Type = PassByValue;
};

template <>
struct AutoPassTypeImpl<false> {
    using Type = PassByReference;
};

/**
 * @brief Автоматическое определение типа передаваемого значения
 *
 * - Если тип void, то передаваемый тип void
 * - Если выполнено kIsSimpleType, то передаваемый тип по значению
 * - Во всех остальных случаях передаваемый тип по ссылке
 *
 * @tparam DataType Тип хранимого значения
 */
template <class DataType>
using AutoPassType = std::conditional_t<std::is_same_v<DataType, void>, void,
                                        typename AutoPassTypeImpl<kIsSimpleType<DataType>>::Type>;

}  // namespace detail

template <class DataType, class PassMethod>
class PortIn;

template <class DataType, class PassMethod>
class PortOut;

/**
 * @brief Принимает изменения от связанного PortOut и передает их обработчикам
 *
 * @tparam DataType Тип хранимого в PortOut значения
 * @tparam PassMethod Метод передачи (по значению или по ссылке)
 */
template <class DataType, class PassMethod = detail::AutoPassType<DataType>>
class PortIn {
    using CDataType = DataType;
    using CPassMethod = PassMethod;

    using CPortOut = PortOut<CDataType, CPassMethod>;

    using CPassType = detail::PassType<CDataType, CPassMethod>;
    using CSignature = void(CPassType);
    using CCallback = std::function<CSignature>;

    friend CPortOut;

public:
    /**
     * @brief Создание порта
     *
     * Регистрирует функции, которые должны вызываться при подписке на порт, получении обновления
     * данных и отписке от порта
     *
     * @param[in] on_subscribe Функция, вызываемая при подключении
     * @param[in] on_notify Функция, вызываемая при обновлении данных
     * @param[in] on_unsubscribe Функция, вызываемая при отключении
     */
    template <class T1, class T2, class T3>
    PortIn(T1&& on_subscribe, T2&& on_notify, T3&& on_unsubscribe)
        : on_subscribe_{std::forward<T1>(on_subscribe)},
          on_notify_{std::forward<T2>(on_notify)},
          on_unsubscribe_{std::forward<T3>(on_unsubscribe)} {
        {
            assert(on_subscribe_ and "PortIn: on_subscribe не должен быть пуст");
            assert(on_notify_ and "PortIn: on_notify не должен быть пуст");
            assert(on_unsubscribe_ and "PortIn: on_unsubscribe не должен быть пуст");
        }
    }

    PortIn(const PortIn&) = delete;
    PortIn(PortIn&&) noexcept = delete;
    PortIn& operator=(const PortIn&) = delete;
    PortIn& operator=(PortIn&&) noexcept = delete;

    ~PortIn() {
        Unsubscribe();
    }

    /**
     * @brief Отписка от подключенного порта
     */
    void Unsubscribe() {
        if (not IsSubscribed()) {
            return;
        }
        connected_to_->Detach(this);
        connected_to_ = nullptr;
    }

    /**
     * @brief Проверка наличия подписки на порт
     *
     * @return Подписан ли объект на какой-нибудь порт
     */
    bool IsSubscribed() const {
        return connected_to_ != nullptr;
    }

private:
    CPortOut* connected_to_ = nullptr;
    CCallback on_subscribe_;
    CCallback on_notify_;
    CCallback on_unsubscribe_;
};

/**
 * @brief Хранит значение и уведомляет подключенные PortIn об изменениях
 *
 * @tparam DataType Тип хранимого значения
 * @tparam PassMethod Метод передачи (по значению или по ссылке)
 */
template <class DataType, class PassMethod = detail::AutoPassType<DataType>>
class PortOut {
    using CDataType = DataType;
    using CPassMethod = PassMethod;

    using CPortIn = PortIn<CDataType, CPassMethod>;

    using CPassType = detail::PassType<CDataType, CPassMethod>;
    using CSignature = void(CPassType);
    using CCallback = std::function<CSignature>;

    friend CPortIn;

public:
    using ReturnType = CPassType;

    /**
     * @brief Интерфейс для изменения хранимых данных
     *
     * Предоставляет доступ для изменения данных, хранимых в PortOut. Гарантируется, что после
     * разрушения этого объякта произойдет уведомление всех подписчиков PortOut
     */
    class Handle {
        friend PortOut;

    public:
        Handle(const Handle& other) = delete;
        Handle(Handle&& other) = delete;
        Handle& operator=(const Handle& other) = delete;
        Handle& operator=(Handle&& other) = delete;

        ~Handle() noexcept {
            ptr_->Notify();
        }

        /**
         * @brief Получение доступа к данным
         *
         * @return Ссылка на хранение данных
         */
        DataType& AccessData() const {
            return ptr_->data_;
        }

    private:
        explicit Handle(PortOut* ptr) : ptr_{ptr} {
            {
                assert(ptr and "Handle: ptr не должен быть nullptr");
            }
        }

        PortOut* ptr_;
    };

    /**
     * @brief Создание порта
     */
    PortOut() {
    }

    /**
     * @brief Создание порта
     *
     * @param[in] data Изначальное хранимое значение
     */
    template <class T>
    PortOut(T&& data) : data_{std::forward<T>(data)} {
    }

    PortOut(const PortOut&) = delete;
    PortOut(PortOut&&) noexcept = delete;
    PortOut& operator=(const PortOut&) = delete;
    PortOut& operator=(PortOut&&) noexcept = delete;

    ~PortOut() noexcept {
        UnsubscribeAll();
    }

    /**
     * @brief Добавление подписчика
     *
     * Подписывает переданный PortIn на себя. Если ранее он был подписан на какой-либо порт,
     * отписывает его
     *
     * @param[in] port Подписчик
     */
    void Subscribe(PortIn<DataType, PassMethod>* port) {
        {
            assert(port and "Subscribe: указатель не должен быть nullptr");
        }
        if (port->IsSubscribed()) {
            port->Unsubscribe();
        }
        subscribers_.push_back(port);
        port->connected_to_ = this;
        port->on_subscribe_(data_);
    }

    /**
     * @brief Отписываение всех подписчиков
     *
     * Отписывает всех подписчиков
     */
    void UnsubscribeAll() {
        while (not subscribers_.empty()) {
            subscribers_.front()->Unsubscribe();
        }
    }

    /**
     * @brief Получение ручки для изменения данных
     *
     * Возвращает ручку для изменения хранимых данных. Требуется, чтобы объект ручки был
     * разрушен раньше объекта порта
     *
     * @return Ручка для изменения данных
     */
    Handle GetHandle() {
        return Handle(this);
    }

    /**
     * @brief Получение хранимых данных
     *
     * Возвращает хранимые данные в режиме "только для чтения" с помощью метода, переданного в
     * шаблоне PassMethod
     *
     * @return Доступ к хранимым данным
     */
    ReturnType AccessData() const {
        return data_;
    }

    /**
     * @brief Передача хранимых данных всем подписчикам
     *
     * Передает хранимые в текущий момент данные всем подписчикам, вызвав их on_notify
     */
    void Notify() const {
        for (CPortIn* subscriber : subscribers_) {
            subscriber->on_notify_(data_);
        }
    }

private:
    /**
     * @brief Отсоединение подписчика
     *
     * Отсоединяет переданного подписчика
     *
     * @param[in] port Подписчик
     */
    void Detach(CPortIn* port) {
        {
            assert(port and "Detach: port не должен быть nullptr");
        }
        port->on_unsubscribe_(data_);
        subscribers_.remove(port);
    }
    DataType data_;
    std::list<CPortIn*> subscribers_;
};
}  // namespace ports
}  // namespace app
