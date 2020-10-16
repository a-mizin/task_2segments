###Задание

Есть класс трёхмерного вектора:

class Vector3D  <br />
{               <br />
double X;       <br />
double Y;       <br />
double Z;       <br />
...             <br />
}

и трёхмерного отрезка, заданного двумя Vector3D:

class Segment3D  <br />
{                <br />
Vector3D start;  <br />
Vector3D end;    <br />
...              <br />
}                <br />

Требуется написать функцию Intersect, которая будет находить точку Vector3D пересечения двух
заданных на вход Segment3D.

### Решение
geometrylib -- исходный файл с фанкцией Intersect и другими вспомогательными функциями.<br />
segmentlib -- класс Segment3D<br />
vectorlib -- класс Vector3D<br />
test -- набор юнит-тестов, написанных на gtest<br />

#### Описание функции Intersect
segment1, segment2 - данные отрезки.<br />
Если отрезки пересекаются, функция возвращает точку пересечения, иначе бросается исключение.<br />

1) Для того, чтобы отрезки пересекались необходимо, чтобы они лежали в одной плоскости.
Проверить это можно посчитав определитель матрицы из трех векторов: направляющие вектора 
каждого из отрезков и, например, вектор, соединяющий начала этих отрезков. Если определитель
матрицы равен нулю, то набор таких векторов линейно зависим, т.е. эти вектора лежат в одной 
плоскости.

2) Задать отрезок по двум точкам можно с помощью выпуклой комбинации, т.е.
    A, B - точки, u*A + (1 - u)B = C, 0 <= u <= 1, тогда C лежит на отрезке AB.
Пусть два отрезка AB и CD пересекаются в точке X. Тогда имеет место система из следующий двух 
уравнений:<br />
    u*A + (1 - u)B = X<br />
    v*D + (1 - v)D = X, где 0 <= u, v <= 1<br />
Соответственно, зная два отрезка и прировняв одно уравнение системы к другому, мы можем найти 
u, v. Затем посмотреть, что если 0 <= u, v <= 1, то отрезки пересекаются в точке u*A + (1 - u)B,
иначе отрезки не пересекаются. 

3) Однако решить полученную систему не всегда удастся. Например, если отрезки коллинеарные. В этом
случае требуется рассмотреть несколько частных случаев.


