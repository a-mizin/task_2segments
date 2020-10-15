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