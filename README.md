# Расстояние Левенштейна
### Исходная формулировка
> Дано две строки.
> Написать класс, который считает количество операций редактирования типа вставка, замена, удаление,
> которые приводят одну строку к другой.

Класс тут ни к чему, так что - функция. Чтобы было чуть интереснее моя реализация принимает на вход любые контейнеры в любых комбинациях.
### Куда смотреть
Заголовочный файл с интерфейсом: lib/ldistance.h
Алгоритимическая часть [в lib/ldistance-inl.h](https://github.com/1az/ldistance/blob/master/lib/ldistance-inl.h#L27)
Примеры использования [в юнит-тесте](https://github.com/1az/ldistance/blob/master/ut/ldistance_ut.cpp)
Сборка cmake, для юнит-тестов используется [фреймворк Catch](https://github.com/philsquared/Catch)
### Как запустить
```bash
git clone https://github.com/1az/ldistance.git && cd ldistance
cmake ./ && make
./ut/ldistance_ut -s
```
Компилятор должен поддерживать C++11.
