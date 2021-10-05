# Транспортный справочник Часть А

В этой задаче и последующих её версиях вам нужно реализовать систему хранения транспортных маршрутов и обработки запросов к ней. Сначала на вход подаются запросы на создание базы данных, затем — запросы к самой базе.
### Формат ввода базы данных
В первой строке вводится количество запросов на обновление базы данных, затем — по одному на строке — вводятся сами запросы. Запросы бывают двух типов.

**Stop *X*: *latitude*, *longitude***

Остановка с названием ***X*** и координатами ***latitude*** и ***longitude***.

Гарантируется, что остановка определена не более чем в одном запросе **Stop *X***.

**Bus *X*: *описание маршрута***

Запрос на добавление автобуса номер ***X***. ***Описание маршрута*** может задаваться в одном из двух форматов (см. пример):
  1. ***stop1 - stop2 - ... - stopN***: автобус следует от ***stop1*** до ***stopN*** и обратно с указанными промежуточными остановками.

  2. ***stop1 > stop2 > ... > stopN > stop1***: кольцевой маршрут с конечной ***stop1***.
  
По сути первая версия описания маршрута эквивалентна ***stop1 > stop2 > ... > stopN-1 > stopN > stopN-1 > ... > stop2 > stop1***.

Гарантируется, что каждая из остановок маршрута определена в некотором запросе **Stop**, а сам маршрут ***X*** определён не более чем в одном запросе **Bus**.

### Формат запросов к базе данных

В первой строке вводится количество запросов к базе данных, затем — по одному на строке — вводятся сами запросы. Запросы бывают (пока что) только одного типа.

**Bus *X***

Вывести информацию об автобусе ***X*** в следующем формате:

**Bus *X*: *R* stops on route, *U* unique stops, *L* route length**

 * ***R*** — количество остановок в маршруте автобуса от ***stop1*** до ***stop1*** включительно.

 * ***U*** — количество уникальных остановок, на которых останавливается автобус. Одинаковыми считаются остановки, имеющие одинаковые названия.

 * ***L*** — длина маршрута в метрах. Для простоты будем считать, что автобус проезжает путь между двумя соседними остановками по кратчайшему расстоянию по земной поверхности . При вычислении расстояния между двумя точками на земной поверхности считайте число π равным 3.1415926535, а радиус Земли — 6371 км.
 
Величину расстояния (а также другие вещественные числа в последующих частях задачи) выводите с 6 значащими цифрами, то есть предваряя модификатором setprecision(6). (При этом ваши значения сравниваются с верными не посимвольно, а с относительной погрешностью 0,0001.)

Если автобус ***X*** не найден, выведите **Bus *X*: not found**

### Пример

**Ввод**
```
10
Stop Tolstopaltsevo: 55.611087, 37.20829
Stop Marushkino: 55.595884, 37.209755
Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye
Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka
Stop Rasskazovka: 55.632761, 37.333324
Stop Biryulyovo Zapadnoye: 55.574371, 37.6517
Stop Biryusinka: 55.581065, 37.64839
Stop Universam: 55.587655, 37.645687
Stop Biryulyovo Tovarnaya: 55.592028, 37.653656
Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164
3
Bus 256
Bus 750
Bus 751
```
**Вывод**
```
Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length
Bus 750: 5 stops on route, 3 unique stops, 20939.5 route length
Bus 751: not found
```