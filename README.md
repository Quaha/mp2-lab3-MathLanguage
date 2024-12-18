# Математический язык программирования

***На данный момент это тестовая версия кода, которая работает, и как таковых багов я не нашёл (хотя я, вероятно, плохо тестировал). На данный момент я её отправляю,
чтобы получить советы/комментарии по тому, что уже написано. В ближайшее время (до зачёта) я улучшу код, добавлю тестов и новых функций в язык.***

***Я планировал доделать и отправить лабораторную работу раньше, но из-за разъездов по олимпиадам и подобным мероприятиям, а также из-за большой нагрузки в конце семестра,
пришлось немного отложить разработку. Также в процессе возникли некоторые трудности, из-за которых приходилось переписывать много кода (идея разделить Data на несколько классов
и хранить их по void указателю оказалась плохой, использовать ООП и виртуальные классы - тоже: получалось слишком много лишнего кода***

## Что уже реализовано?

### Целые и вещественные числа и некоторые операции над ними:
Приоритет операций такой же, как в математике. Можно нетрудно добавить новые бинарные/унарные операторы
```cpp
// Сложение
5 + 3
>> 8

5 + 3.1
>> 8.1

5.0 + 3.1
>> 8.1
```

```cpp
// Вычитание
5 - 3
>> 2

5 - 3.1
>> 1.9

5.0 - 3.1
>> 1.9
```

```cpp
// Умножение
5 * 3
>> 15

5 * 0.5
>> 2.5

0.5 - 0.5
>> 0.25
```

```cpp
// Деление
5 / 2
>> 2.5

5 / 0.4
>> 12.5

0.5 / 2.5
>> 0.2
```

```cpp
// Унарный +
+5
>> 5

+5.2
>> 5.2
```

```cpp
// Унарный -
-5
>> -5

-5.2
>> -5.2
```

### Функции
Их можно перегружать по числу переменных и типам, можно создать функцию, которая принимает любое число переменных.
```cpp
// Сумма любого количества чисел
sum(-1, 2.3, 5.1)
>> 6.4
```

```cpp
// Скобки (функция контроля приоритета операций)
(5 + 3) * 2
>> 16
```

### Переменные
Здесь нет строгой типизации. Перед использованием переменной её необходимо проинициализировать, затем к ней можно обращаться и даже перезаписывать её.
Имя переменной может содержать латинский буквы, цифры и нижнее подчёркивание, но название не должно начинаться с цифры
```cpp
abba = 5
>>
abba
>> 5
abba = 3.1
>>
abba + 3
>> 6.1
```

### Написание кода
Любой написанный текст можно разделять пробелами " " и "`" как угодно - эти символы не учитываются и являются лишь визуальными разделителями
```cpp
5 6 7`8
>> 5678
```
Язык не требует указывать конец строки, однако, при желании, можно объявить конец строки как ";": всё что идёт после этого символа не обрабатывается
```cpp
5678;1234ghsdhd 30-g=sdgh3gsdh
>> 5678
```
