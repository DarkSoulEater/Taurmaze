# Taurmaze - 2D рогалик написанный на С++

## Описание структуры проекта
* [asset](https://github.com/DarkSoulEater/Taurmaze/tree/master/assets) - папка с медиа файлами игры 
* [doc](https://github.com/DarkSoulEater/Taurmaze/tree/master/doc) - папка с [дизайн-документом](https://github.com/DarkSoulEater/Taurmaze/blob/master/doc/game_design_document.pdf) игры
* [src](https://github.com/DarkSoulEater/Taurmaze/tree/master/src) - папка с исходными файлами

## Структура исходных файлов
* [UI](https://github.com/DarkSoulEater/Taurmaze/tree/master/src/UI) - папка с классами пользовательского интерфейса
* [core](https://github.com/DarkSoulEater/Taurmaze/tree/master/src/core) - папка с классами ядра игрового движка
* [game](https://github.com/DarkSoulEater/Taurmaze/tree/master/src/game) - папка с классами игровой логики
* [util](https://github.com/DarkSoulEater/Taurmaze/tree/master/src/util) - папка с классами для контроля ресурсов

## Строение ядра игровго движка
  [Ядро](https://github.com/DarkSoulEater/Taurmaze/blob/master/src/core/Core.h) отвечает за всю внутреню логику, не касающююся конкретной игры (управление вводом, объектами, сценами, отрисовка кадров и тд.). При запуске [ядро](https://github.com/DarkSoulEater/Taurmaze/blob/master/src/core/Core.h) переходит в бесконечный цикл, который работает, пока открыта игра. Один проход цикла отвечает за обработку одного тика игры и отрисовки одного кадра. Для работы с движком используется такое понятие, как ["Объект"](https://github.com/DarkSoulEater/Taurmaze/blob/master/src/core/Object.h) - это любая сущность игры (персонаж, кнопка, монетка и тд.), все что будет отнаследованно от класса [Object](https://github.com/DarkSoulEater/Taurmaze/blob/master/src/core/Object.h) будет автоматически отрисовываться и также имеет некотрые полезные встроенные методы для взаимодействия с движком.
  
  Основной контроль логики объектов происходит через "События". Каждый кадр [ядро](https://github.com/DarkSoulEater/Taurmaze/blob/master/src/core/Core.h) отправляет всем объектам несколько событий в разное время, таким образом объекты обновляют свою информацию о мире и взаимодействуют друг с другом. Контроль событий объектами осуществляется через виртуальные функции, каждый класс отнаследованный от [Object](https://github.com/DarkSoulEater/Taurmaze/blob/master/src/core/Object.h) может самостоятельно переопределить необходимые функции для правильной реакции на события.
  
  [Ядро](https://github.com/DarkSoulEater/Taurmaze/blob/master/src/core/Core.h) дает возможность получить доступ к вводу пользователя через удобный интерфейс ["input"](https://github.com/DarkSoulEater/Taurmaze/blob/master/src/util/input.h), автоматически отрисовывает все объекты на сцене, дает возможность создания нескольких сцен и переключения между ними.
