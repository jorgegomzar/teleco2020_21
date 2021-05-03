//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

//
// TODO generated message class
//

message PeticionLightpath
{
    int nodo_origen;
    int nodo_destino;
    double tiempo_servicio;
}


message RutaYLong
{
    int nodo_origen;
    int nodo_destino;
    double tiempo_servicio;
    int longitud_onda;
    int ruta[];
    int longitud_onda_proteccion;
    int ruta_proteccion[];
    bool proteccion_activada;
}

message CargaNodo
{
    double carga[];
    int nodo;
}

message MatrizTrafico
{
    double trafico[];
    int cambiado;
    int calcular;
}

