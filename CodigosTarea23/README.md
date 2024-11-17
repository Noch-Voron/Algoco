# Algoritmos de Fuerza Bruta y Programación Dinámica

Este repositorio contiene los códigos fuente y archivos de texto utilizados para la formulación de los informes de las tareas 2 y 3.

## Archivos principales

- **FB.cpp**: Implementación del algoritmo de **Fuerza Bruta**.
- **PD.cpp**: Implementación del algoritmo de **Programación Dinámica**.

Ambos archivos son esenciales para probar los algoritmos y tienen instrucciones de uso simples.

## Requisitos

- Tener un IDE que soporte C++ y los compiladores necesarios instalados.
- Los siguientes archivos de texto deben estar en el mismo directorio que los archivos `.cpp`:
  - `cost_delete.txt`
  - `cost_insert.txt`
  - `cost_replace.txt`
  - `cost_transpose.txt`

Estos archivos de texto son editables y se utilizan para probar diferentes combinaciones de costos en las operaciones.

### Archivo adicional

- **costs.cpp**: Este archivo genera los archivos de texto anteriores con costos constantes o aleatorios dentro de un rango especificado.

## Configuración de costos

Para el informe, se utilizó una combinación de costos priorizando un bajo costo para la transposición, y luego un costo más alto para las otras operaciones. Si se tienen los cuatro archivos de texto en el mismo directorio, se podrán realizar las pruebas sin problemas.

## Instrucciones de uso

1. **Compilación**: Primero, compile ambos archivos usando el compilador C++ de su preferencia. Por simplicidad, se utilizó el siguiente comando en el informe:
   g++ PD.cpp -o PD
2. **Ejecución**: Al ejecutar cualquiera de los programas, se te pedirá ingresar dos cadenas:
-S1: La cadena base.
-S2: La cadena objetivo.

