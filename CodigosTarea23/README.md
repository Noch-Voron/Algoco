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

1. **Compilación**:
   Primero, compile ambos archivos usando el compilador C++ de su preferencia. Por simplicidad, se utilizó el siguiente comando en el informe:
   g++ PD.cpp -o PD
3. **Ejecución**:
   Al ejecutar cualquiera de los programas, se te pedirá ingresar dos cadenas:
   
  - S1: La cadena base.
  - S2: La cadena objetivo.
  Las condiciones son las siguientes:

  - Se aceptan cadenas vacías.
  - No se aceptan cadenas con números, letras mayúsculas ni la letra "ñ".
  Las cadenas ingresadas se almacenarán en un vector de pares. Luego, se te preguntará si deseas agregar más casos de prueba. Si deseas continuar, ingresa 1. Para obtener los resultados, ingresa cualquier valor distinto de 1.

3. **Ejecución del Algoritmo**
  Dependiendo del algoritmo seleccionado (fuerza bruta o programación dinámica), los tiempos de ejecución pueden variar. Ten en cuenta que las cadenas de longitud 12 o más pueden hacer que la ejecución con el algoritmo de fuerza bruta sea lenta.

4. **Resultados**
Al finalizar la ejecución, se generará un archivo llamado resultados.txt con los siguientes datos:

  - El par de cadenas S1 y S2.
  - El tiempo de ejecución del algoritmo para ese par.
  - El resultado final del algoritmo.

Si se desea generar múltiples archivos de resultados, es necesario cambiar el nombre del archivo después de cada ejecución, de lo contrario, el archivo original será sobrescrito.
