# Hash-таблицы

## Задачи:
* написать Hash-таблицу
* написать 7 Hash-функций;
* написать 3 оптимизации;
    * asm-вставка
    * intrinsics-функции
    * функция из *.asm

## Ход работы
# Hash-функции:
## 1) Обработка текста
программа [text_handler.cpp](handle_text/text_handler.cpp) обрабатывает файл [TEXT_FILE](general/dsl.h) в файл [HANDLED_FILE](general/dsl.h) для дальнейшего считывания.
## 2) Считывание текста из **HANDLED_FILE**
## 3) Создание Hash-таблиц с помощью Hash-функций (Размер таблиц - [HASH_TABLE_SIZE](general/dsl.h))

|hash всегда 0|hash = ASCII коду первого символа слова|
|:--:|:--:|
|<img src="graphs/const.png"   alt="drawing" width="300"/> | <img src="graphs/first_ascii.png" alt="drawing" width="300"/>|
| Hash = длина слова | Hash = сумма ASCII кодов каждого символа в строке |
|<img src="graphs/length.png" alt="drawing" width="300"/> | <img src="graphs/ascii_sum.png"  alt="drawing" width="300"/>|
|Hash = сдвиг по кругу вправо от предыдущего хеша | Hash = сдвиг по кругу влево от предыдущего хеша|
|<img src="graphs/right.png"     alt="drawing" width="300"/> | <img src="graphs/left.png"    alt="drawing" width="300"/>|
|Crc32|
|<img src="graphs/crc32.png"     alt="drawing" width="300"/>|

medium value - среднее медианное значение.
 ## 3) Время выполнения

С помощью инструмента Valgrind засекаем время работы всех функций. Получаем
![hah](img/kcache.png)

Как мы видим, самые "прожорливые" функции, которые поддаются оптимизации - **strlen**, **strcmp** и **crc32**. Ими мы и займемся!!!

Оцениваем время по поиску 4 700  000 элементов.

|без оптимизации|-O3|
|:--:|:--:|
|<img src="graphs/const.png"   alt="drawing" width="300"/> | <img src="graphs/first_ascii.png" alt="drawing" width="300"/>|
| -O3 и crc32 | -O3, Len и crc32 |
|<img src="graphs/length.png" alt="drawing" width="300"/> | <img src="graphs/ascii_sum.png"  alt="drawing" width="300"/>|
|-O3, len, crc32 и my_strcmp|
|<img src="graphs/crc32.png"     alt="drawing" width="300"/>|
