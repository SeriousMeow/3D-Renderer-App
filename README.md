# Renderer_App

Курсовой программный проект на тему "Имплементация пайплайна для визуализации трёхмерных сцен". Интерактивное приложение, основанное на [библиотеке](https://github.com/SeriousMeow/3D-Renderer)

## Сборка

```sh
mkdir build
cd build
cmake ..
make
```

Результатом сборки является исползняемый файл ```Renderer_App```

Сборка проекта протестирована на компиляторе GNU g++. На текущий момент компиляция с помощью Clang невозможна

## Документация

Для генерации документации требуется установленный Doxygen (гарантирована работа версий с 1.8.20 до 1.13.2). Для генерации документации необходимы CMake опции ```-DRenderer_App_DEVELOPER_MODE=ON``` и ```-DBUILD_DOCS=ON```, после чего используется команда

```sh
make app_docs
```
