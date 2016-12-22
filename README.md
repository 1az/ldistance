# Расстояние Левенштейна
### Исходная формулировка
> Дано две строки.  
> Написать класс, который считает количество операций редактирования типа вставка, замена, удаление,
> которые приводят одну строку к другой.

> Написать класс,  
> который в бесконечном потоке символов ищет вхождения данной строки с не более чем 
> N ошибками редактирования (пропуск, вставка, замена).

### Расстояние Левенштейна
Заголовочный файл с интерфейсом: [lib/ldistance.h](https://github.com/1az/ldistance/blob/master/lib/ldistance.h).  
Алгоритимическая часть [в lib/ldistance-inl.h](https://github.com/1az/ldistance/blob/master/lib/ldistance-inl.h#L27).  
Примеры использования [в юнит-тесте](https://github.com/1az/ldistance/blob/master/ut/ldistance_ut.cpp).  

### Нечёткий поиск в потоке
Заголовочный файл с интерфейсом: [lib/fuzzy_search.h](https://github.com/1az/ldistance/blob/master/lib/fuzzy_search.h).  
Алгоритимическая часть [в lib/ldistance-inl.h](https://github.com/1az/ldistance/blob/master/lib/fuzzy_search.cpp#L38).  
Примеры использования [в юнит-тесте](https://github.com/1az/ldistance/blob/master/ut/fuzzy_search_ut.cpp).  

Алгоритм тот же, что и в расчете расстояния Левенштейна, за исключением одной поправки: стоимость пропуска любого
количества первых символов в потоке нулевая.

Для каждого символа потока возвращается не более одной найденной подстроки, заканчивающейся в этом символе. Из нескольких
вариантов выбирается самый близкий по расстоянию Левенштейна, а при равном расстоянии - самый короткий.

Для восстановления сматчившейся подстроки потока потребовалось сделать так же
[кольцевой буфер](https://github.com/1az/ldistance/blob/master/lib/ring_buffer.h).
Примеры использования [в юнит-тесте](https://github.com/1az/ldistance/blob/master/ut/ring_buffer_ut.cpp).

### Как запустить
Сборка cmake, для юнит-тестов используется [фреймворк Catch](https://github.com/philsquared/Catch).
```bash
git clone https://github.com/1az/ldistance.git && cd ldistance
cmake ./ && make
./ut/ldistance_ut -s
```
Компилятор должен поддерживать C++11.
