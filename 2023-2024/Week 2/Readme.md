# ООП - Практикум 01.03.2024 Седмица 2

**Задача 1:**

От стандартния вход се прочитат три числа. Запишете във файл "result.txt"сумата и произведението им. <br />
Направете функция, която извежда на стандартния изход разликата на сумата и произведението, прочетени от файла "result.txt". <br />
_Забележка:_ Коректността на данните във файла, който четете, е гарантирана. <br />

**Задача 2:**

Да се напише функция, която приема поток към текстов файл и структура, която съдържа два масива от символи ( **key и value** (всеки с максимален размер от 32 символа)). Функцията трябва да смени всяко срещане на **key** c **value** в текстовия файл. <br />
Новия тескт да се запише в друг текстов файл. <br />
Да се напише втора функция, която приема текстов файл и множество от двойки **key и value** и заменя всеки **key** в текстовия файл със съответния му **value**. <br />
_Забележка:_ Приемете, че данните са валидни и няма нито един key да е същия, като някое value на друга двойка

**Задача 3:**

Да се създаде структура pair, която представя наредена двойка от естествени числа. <br />
Да се създаде структура, която представя релация. В релацията има най-много 25 наредени двойки и структурата пази текущия си размер. <br />
Да се създаде функция writeRelationToFile(...), която записва релацията във файл с име "relation.txt"и readRelationFromFile(...), която чете релацията от файла. <br />
Следните функции ще ви бъдат полезни: <br />

- createPair()
- initPair()
- readPairFromFile()
- writePairToFile()
- addPairToRelation()

Помислете какво трябва да приемат и връщат горните функции.  
Напишете проста програма, която демонстрира работата на написаната от вас програма.

**Задача 4:**
Реализирайте структура User, която да съдържа име, имейл и парола на даден потребител. Всяко поле е с максимална дължина 128 символа. Създайте възможност за записване и четене на потребител в текстов файл. <br />

Реализирайте структура System, която има масив от User-и. Системата поддържа максимално 100 потребители. Създайте методи за запазване и прочитане на обект от тип System от файл. <br />

**Задача 5:**

Напишете програма, която взема две версии на един файл (нова и стара) и записва в трети файл всички разлики между двата файла. <br />

Третия файл трябва да е във вида:

```
еднакъв ред
- стар ред
+ нов ред
```

Примерен вход:

file1:

```
Water. Earth. Fire. Air.
Long ago, the four nations lived together in harmony.
Then everything changed when the Fire Nation attacked.
Only the Avatar, master of all four elements, could stop them,
```

file2:

```
Water. Earth. Fire. Air.
Long ago, the five nations lived together in harmony.
Then everything changed when the Water Nation attacked.
Only the Avatar, master of all four elements, could stop them,
but when the world needed him most, he vanished.
```

Примерен изход:

```
Water. Earth. Fire. Air.
- Long ago, the four nations lived together in harmony.
+ Long ago, the five nations lived together in harmony.
- Then everything changed when the Fire Nation attacked.
+ Then everything changed when the Water Nation attacked.
Only the Avatar, master of all four elements, could stop them,
but when the world needed him most, he vanished.
```
